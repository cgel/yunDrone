#include <Sensor.h>

Sensor::Sensor(): mpu(), pullMissCount(0), pullEmptyMissCount(0), overflowCount(0), lastBuferReadCount(0), dmpReady(false) {}

bool Sensor::init() {
	// join I2C bus (I2Cdev library doesn't do this automatically)
	#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
		Wire.begin();
		TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)
	#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
		Fastwire::setup(400, true);
	#endif

	// initialize device
	mpu.initialize();

	// load and configure the DMP
	devStatus = mpu.dmpInitialize(); 

	// supply your own gyro offsets here, scaled for min sensitivity
	mpu.setXGyroOffset(220);
	mpu.setYGyroOffset(76);
	mpu.setZGyroOffset(-85);
	mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

	// make sure it worked (returns 0 if so)
	if (devStatus == 0) {
		// turn on the DMP, now that it's ready
		mpu.setDMPEnabled(true);

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

void Sensor::update() {
	// if programming failed, don't try to do anything
	if (!dmpReady) return;

	// get current FIFO count
	fifoCount = mpu.getFIFOCount();

	// check for overflow (this should never happen unless our code is too inefficient)
	if (fifoCount == 1024) {
		// reset so we can continue cleanly
		mpu.resetFIFO();
		overflowCount += 1;
	} else if (fifoCount == 0) {
		pullEmptyMissCount += 1;
	} else if (fifoCount < packetSize) {
		pullMissCount += 1;
	} else { // in this case the fifo has one or more packets

		// if there are more than on packet, will read all of them and keep the newest
		lastBuferReadCount = 0;
		while (fifoCount >= packetSize)
		{
			// read a packet from FIFO
			mpu.getFIFOBytes(fifoBuffer, packetSize);
			lastBuferReadCount += 1;

			// track FIFO count here in case there is > 1 packet available
			// (this lets us immediately read more without waiting for an interrupt)
			fifoCount -= packetSize;
			//fifoCount = mpu.getFIFOCount(); // It is slower than subtracting the packet size, but in case new data comes in it will allow to read it.
		}
		// Update Quaternion, Euler angles and Yay Pich Roll angles
		mpu.dmpGetGyro(ypr_vel, fifoBuffer);
		mpu.dmpGetQuaternion(&q, fifoBuffer);
		mpu.dmpGetGravity(&gravity, &q);
		mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
	}
}

float* Sensor::get_ypr()
{
	return ypr;
}

int* Sensor::get_ypr_vel()
{
	return ypr_vel;
}
