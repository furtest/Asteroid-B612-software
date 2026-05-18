#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

#include "bno.h"
#include "EEPROM.h"

int bno_get_new_events(bno_data_t &data, Adafruit_BNO055 bno)
{
	bno.getEvent(&data.orientation, Adafruit_BNO055::VECTOR_EULER);
	bno.getEvent(&data.ang_velocity, Adafruit_BNO055::VECTOR_GYROSCOPE);
	bno.getEvent(&data.linear_accel, Adafruit_BNO055::VECTOR_LINEARACCEL);
	bno.getEvent(&data.magnetometer, Adafruit_BNO055::VECTOR_MAGNETOMETER);
	bno.getEvent(&data.accelerometer, Adafruit_BNO055::VECTOR_ACCELEROMETER);
	bno.getEvent(&data.gravity, Adafruit_BNO055::VECTOR_GRAVITY);

	data.temperature = bno.getTemp();

	return 0;
}

int bno_get_calibration(bno_calibration_t &data, Adafruit_BNO055 bno)
{
	bno.getCalibration(&data.system, &data.gyro, &data.accel, &data.mag);
	return 0;
}

int bno_get_offsets(bno_calibration_t &data, Adafruit_BNO055 bno)
{
	bno.getSensorOffsets(data.calibration_data);
	return 0;
}

int bno_calibrate_sensor(Adafruit_BNO055 bno)
{
	int i = 0;
	sensors_event_t event;
	bno_calibration_t cal_data;
	while (!bno.isFullyCalibrated())
	{
		bno.getEvent(&event);

		if(i == 10){
			i = 0;
			bno_get_calibration(cal_data, bno);

			Serial.print("Sys:");
			Serial.print(cal_data.system, DEC);
			Serial.print(" G:");
			Serial.print(cal_data.gyro, DEC);
			Serial.print(" A:");
			Serial.print(cal_data.accel, DEC);
			Serial.print(" M:");
			Serial.print(cal_data.mag, DEC);

			/* New line for the next sample */
			Serial.println("");
		}
		i++;

		/* Wait the specified delay before requesting new data */
		delay(BNO055_SAMPLERATE_DELAY_MS);
	}
	return 0;
}

int bno_save_offsets(Adafruit_BNO055 bno, int eeprom_addr)
{
	sensor_t sensor;
	bno.getSensor(&sensor);
	long bno_id = sensor.sensor_id;
	EEPROM.put(eeprom_addr, bno_id);

	eeprom_addr += sizeof(long);
	bno_calibration_t cal_data;
	bno_get_offsets(cal_data, bno);
	EEPROM.put(eeprom_addr, cal_data.calibration_data);
	return 0;
}

int bno_restore_offsets(Adafruit_BNO055 bno, int eeprom_addr)
{
	bno_calibration_t cal_data;
	sensor_t sensor;
	bno.getSensor(&sensor);
	long bno_id;
	EEPROM.get(eeprom_addr, bno_id);
	if(bno_id != sensor.sensor_id){
		return 1;
	}

	eeprom_addr += sizeof(long);
	EEPROM.get(eeprom_addr, cal_data.calibration_data);
	bno.setSensorOffsets(cal_data.calibration_data);
	return 0;
}

void bno_print_event(sensors_event_t &event) {
	double x = -1000000, y = -1000000 , z = -1000000;
	switch (event.type) {
		case SENSOR_TYPE_ACCELEROMETER:
			Serial.print("Accl:");
			break;
		case SENSOR_TYPE_LINEAR_ACCELERATION:
			Serial.print("Linear:");
			break;
		case SENSOR_TYPE_GRAVITY:
			Serial.print("Gravity:");
			break;
		case SENSOR_TYPE_ORIENTATION:
			Serial.print("Orient:");
			break;
		case SENSOR_TYPE_MAGNETIC_FIELD:
			Serial.print("Mag:");
			break;
		case SENSOR_TYPE_GYROSCOPE:
			Serial.print("Gyro:");
			break;
		case SENSOR_TYPE_ROTATION_VECTOR:
			Serial.print("Rot:");
			break;
		default:
			Serial.print("Unk:");
			break;
	}

	switch (event.type) {
		case SENSOR_TYPE_ACCELEROMETER:
		case SENSOR_TYPE_LINEAR_ACCELERATION:
		case SENSOR_TYPE_GRAVITY:
			x = event.acceleration.x;
			y = event.acceleration.y;
			z = event.acceleration.z;
			break;
		case SENSOR_TYPE_ORIENTATION:
			x = event.orientation.x;
			y = event.orientation.y;
			z = event.orientation.z;
			break;
		case SENSOR_TYPE_MAGNETIC_FIELD:
			x = event.magnetic.x;
			y = event.magnetic.y;
			z = event.magnetic.z;
			break;
		case SENSOR_TYPE_GYROSCOPE:
		case SENSOR_TYPE_ROTATION_VECTOR:
			x = event.gyro.x;
			y = event.gyro.y;
			z = event.gyro.z;
			break;
	}

	Serial.print("\tx= ");
	Serial.print(x);
	Serial.print(" |\ty= ");
	Serial.print(y);
	Serial.print(" |\tz= ");
	Serial.println(z);
}
