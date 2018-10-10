# MPU9250Library
This is a library of MPU9250 devices (Inertial and Magnetic Array Sensors) for Particle Photon

## Supported MPU9250 devices

## Usage

Set up the hardware:
- A MPU9250 device with I2C Protocol

Flash the [mpu9250 example](examples/mpu9250Example.cpp).

Adapt it to your needs while keeping this general structure:

```cpp
MPU9250 margSensor();
int16_t dataSensor[10];

void setup() {
  margSensor.begin();
}
void loop() {
  margSensor.Read9Axis(dataSensor);
  // The sensor values is stored in dataSensor[x] as follows:
  // dataSensor[0] ~ dataSensor[2] (Acceleration X Axis - Acceleration Y Axis - Acceleration Z Axis)
  // dataSensor[3] (Temperature)
  // dataSensor[4] ~ dataSensor[6] (AngularRate X Axis - AngularRate Y Axis - AngularRate Z Axis)
  // dataSensor[7] ~ dataSensor[9] ( MagneticComponent X Axis - MagneticComponent Y Axis - MagneticComponent Z Axis)
}
```

## Documentation

### `MPU9250`

```
// IMPORTANT: Create dataSensor array for to store all readings
int16_t dataSensor[10];
```

### `begin`

`margSensor.begin();`

Sets up the the operating mode of mpu9250 devices.

### `getGyroOffsets`

```
int16_t GyroOffsets[3]; //we will save the readings of the offsets in this array
margSensor.getGyroOffsets(GyroOffsets);
Serial.printlnf("GyroOffset X:  %d", GyroOffsets[0]);
Serial.printlnf("GyroOffset Y:  %d", GyroOffsets[1]);
Serial.printlnf("GyroOffset Z:  %d", GyroOffsets[2]);
```

This function allows us to read the offsets gyroscope Register and store them in the pointer GyroOffsets

### `getAccelOffsets`

```
int16_t AccelOffsets[3]; //we will save the readings of the offsets in this array
margSensor.getAccelOffsets(AccelOffsets);
Serial.printlnf("AccelOffset X:  %d", AccelOffsets[0]);
Serial.printlnf("AccelOffset Y:  %d", AccelOffsets[1]);
Serial.printlnf("AccelOffset Z:  %d", AccelOffsets[2]);
```

This function allows us to read the offsets accelerometer Register and store them in the pointer AccelOffsets

### `setGyroOffsetX`
### `setGyroOffsetY`
### `setGyroOffsetZ`

```
int16_t gxOffset = 543;
int16_t gyOffset = 25;
int16_t gzOffset = -78;

margSensor.setGyroOffsetX(gxOffset);
margSensor.setGyroOffsetY(gyOffset);
margSensor.setGyroOffsetZ(gzOffset);

```

These functions set up gyroscope offset register.

### `setAccelOffsetX`
### `setAccelOffsetY`
### `setAccelOffsetZ`

```
int16_t axOffset = 2890;
int16_t ayOffset = -13125;
int16_t azOffset = -768;

margSensor.setAccelOffsetX(axOffset);
margSensor.setAccelOffsetY(ayOffset);
margSensor.setAccelOffsetZ(azOffset);

```

These functions set up accelerometer offset register.

### `setGyroScale`

```
/* ============================
    Select Gyroscope Scale:
    0 = ±250dps =
    1 = ±500 dps =
    2 = ±1000 dps =
    3 = ±2000 dps =
    ===============================*/
 margSensor.setGyroScale(3);// +-2000 dps
```

This function set up gyroscope scale register.

### `setAccelScale`

```
/* ============================
    Select Accelerometer scale:
    0 = ±2g
    1 = ±4g
    2 = ±8g
    3 = ±16g
    ===============================*/
 margSensor.setAccelScale(1);// +-4g
```

This function set up accelerometer scale register.

## Nuances

## References

- MPU-9250 Product Specification Revision 1.1(http://www.invensense.com/wp-content/uploads/2015/02/PS-MPU-9250A-01-v1.1.pdf) (Invensense)
- MPU-9250 Register Map and Descriptions Revision 1.6(https://www.invensense.com/wp-content/uploads/2015/02/RM-MPU-9250A-00-v1.6.pdf) (Invensense)
- AK8963 Datasheet(https://www.akm.com/akm/en/file/datasheet/AK8963C.pdf) (Asahi Kasei)

## License
Copyright 2018-2022 JDVR, Juan David Velasquez Rosero

Released under the LGPL license
