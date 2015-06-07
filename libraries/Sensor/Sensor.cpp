#include <Sensor.h>

bool Sensor::init()
{
    int errcode;
    Wire.begin();
    imu = RTIMU::createIMU(&settings);                        // create the imu object
    Serial.print("ArduinoIMU starting using device "); Serial.println(imu->IMUName());
    if ((errcode = imu->IMUInit()) < 0) {
        Serial.print("Failed to init IMU: "); Serial.println(errcode);
    }
    if (imu->getCalibrationValid())
        Serial.println("Using compass calibration");
    else
        Serial.println("No valid compass calibration data");
    fusion.setSlerpPower(0.02);
    fusion.setGyroEnable(true);
    fusion.setAccelEnable(true);
    fusion.setCompassEnable(true);
    return errcode;
}

void Sensor::call()
{  
  while (imu->IMURead()) {                                // get the latest data if ready yet
    // can the gyrobiasvalid function return false after it was true? dont know so will test it
    biasValid = imu->IMUGyroBiasValid();
    if (prevBiasValid == true && biasValid == false)
    {
      biasValidChanged = true; // will this flag ever be raised?
    }
    prevBiasValid = biasValid;

    fusion.newIMUData(imu->getGyro(), imu->getAccel(), imu->getCompass(), imu->getTimestamp());
  }
}

void Sensor::print()
{  
    RTMath::displayRollPitchYaw("Pose:", (RTVector3&)fusion.getFusionPose()); // fused output
    Serial.println();
}

bool Sensor::ready() // the imu might not be ready for a few seconds after init
{
  return biasValid;
}
