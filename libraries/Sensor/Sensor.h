#include "Scheduler.h"
#include "I2Cdev.h"

#include "MPU6050_6Axis_MotionApps20.h"

/*
//for debugging porpuses
#include <StandardCplusplus.h>
#include <serstream>
using namespace std;
namespace std
{
  extern ohserialstream cout;
}
*/

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

class Sensor : public Process {
public:
	Sensor(): mpu() {}

	bool init() {
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

void update() {
	// if programming failed, don't try to do anything
	if (!dmpReady) return;

	Serial.print(F("a")); // +

	// get current FIFO count
	fifoCount = mpu.getFIFOCount();
	Serial.print(F("b"));

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
		Serial.print(F("c"));

		// if there are more than on packet, will read all of them and keep the newest
		lastBuferReadCount = 0;
		while (fifoCount >= packetSize)
		{
			// read a packet from FIFO
			Serial.print(F("d")); // ++
			mpu.getFIFOBytes(fifoBuffer, packetSize);
			lastBuferReadCount += 1;

			// track FIFO count here in case there is > 1 packet available
			// (this lets us immediately read more without waiting for an interrupt)
			fifoCount -= packetSize;
			//fifoCount = mpu.getFIFOCount(); // It is slower than subtracting the packet size, but in case new data comes in it will allow to read it.
		}
		Serial.print(F("e"));
		// Update Quaternion, Euler angles and Yay Pich Roll angles
		mpu.dmpGetQuaternion(&q, fifoBuffer);
		mpu.dmpGetGravity(&gravity, &q);
		mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
	}
	float* ypr = get_ypr();
	int ofc = overflowCount;
	int pm = pullMissCount;
	int pem = pullEmptyMissCount;
	int rc = lastBuferReadCount;
	//cout <<"- "<<ypr[0]<<" - "<<ypr[1]<<" - "<<ypr[2]<<" - "<<" - overflow: "<<ofc<<" - empty miss: "<<pem<<" - miss: "<<pm<<" - readCount: "<<rc<< endl;
	//cout <<"- "<<ypr[0]<<" - "<<ypr[1]<<" - "<<ypr[2]<<" - "<<" - overflow: "<<ofc<<" - empty miss: "<<pem<<" - miss: "<<pm<<" - readCount: "<<rc<< endl;
	Serial.print(F(" - "));
	Serial.print(ofc);
	Serial.print(F(" - "));
	Serial.print(pm);
	Serial.print(F(" - "));
	Serial.print(pem);
	Serial.print(F(" - "));
	Serial.print(rc);

	Serial.println(F(""));
}

	float* get_ypr()
	{
		return ypr;
	}

	int pullMissCount = 0;
	int pullEmptyMissCount = 0;
	int overflowCount = 0;
	int lastBuferReadCount = 0;

private:
	MPU6050 mpu;

	// MPU control/status vars
	bool dmpReady = false;  // set true if DMP init was successful
	uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
	uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
	uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
	uint16_t fifoCount;     // count of all bytes currently in FIFO
	uint8_t fifoBuffer[64]; // FIFO storage buffer

	// orientation/motion vars
	Quaternion q;           // [w, x, y, z]         quaternion container
	VectorInt16 aa;         // [x, y, z]            accel sensor measurements
	VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
	VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
	VectorFloat gravity;    // [x, y, z]            gravity vector
	float euler[3];         // [psi, theta, phi]    Euler angle container
	float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
};
