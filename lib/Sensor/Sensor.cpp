#include <Sensor.h>

bool Sensors::init()
{
	Fastwire::setup(400, true);

	// initialize device
	mpu.initialize();

	// verify connection
	bool conectionStatus = mpu.testConnection(); 

	// load and configure the DMP (Digital Motion Processing)
	devStatus = mpu.dmpInitialize();

	// supply your own gyro offsets here, scaled for min sensitivity
	mpu.setXGyroOffset(220);
	mpu.setYGyroOffset(76);
	mpu.setZGyroOffset(-85);
	mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

	// make sure it worked (devStatus is 0 if so)
	if (devStatus == 0) {
		// turn on the DMP, now that it's ready
		mpu.setDMPEnabled(true);

		// enable Arduino interrupt detection
		attachInterrupt(0, dmpDataReady, RISING);
		mpuIntStatus = mpu.getIntStatus();

		// set our DMP Ready flag so the main loop() function knows it's okay to use it
		dmpReady = true;

		// get expected DMP packet size for later comparison
		packetSize = mpu.dmpGetFIFOPacketSize();
		return 0;
	} else {
		// ERROR!
		// 1 = initial memory load failed
		// 2 = DMP configuration updates failed
		// (if it's going to break, usually the code will be 1)
		return 1;
	}
}

void Sensors::update()
{
	// read the mpu. If there are new reading update rpy[] if there are not return rpy[] whitout update.

	// check if there is an MPU interrupt or extra packet(s) available
	if (!mpuInterrupt && fifoCount < packetSize) 
	{
		//if there is not:
		return;
	}

	// reset interrupt flag and get INT_STATUS byte
	mpuInterrupt = false;
	mpuIntStatus = mpu.getIntStatus();

	// get current FIFO count
	fifoCount = mpu.getFIFOCount();

	// check for overflow (this should never happen unless our code is too inefficient)
	if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
		// reset so we can continue cleanly
		mpu.resetFIFO();

	// otherwise, check for DMP data ready interrupt (this should happen frequently)
	} else if (mpuIntStatus & 0x02) {
		// wait for at least one package, should be a VERY short wait
		while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

		// there are one ore more packets read all of them and keep the last one
		while (fifoCount - packetSize > packetSize) 
		{
		// read a packet from FIFO
		mpu.getFIFOBytes(fifoBuffer, packetSize);
		
		// track FIFO count here in case there is > 1 packet available
		fifoCount -= packetSize;
		} // There is the possibility that while reading the FIFO in the while loop new packets have entered. If it happens we do not read them untill the next update
		


		// display Euler angles in degrees
		mpu.dmpGetQuaternion(&q, fifoBuffer);
		mpu.dmpGetGravity(&gravity, &q);
		mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
	}
}

float[] Sensors::get_ypr()
{
	return rpy;
}

