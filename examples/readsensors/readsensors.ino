// Example usage for MPU9250 library by Juan David Velasquez Rosero.

#include "MPU9250.h"
#include <application.h>

#define GYRO_CONVERSION_FS_SEL_0    (250*2)/65535
#define GYRO_CONVERSION_FS_SEL_1    (500*2)/65535
#define GYRO_CONVERSION_FS_SEL_2    (1000*2)/65535
#define GYRO_CONVERSION_FS_SEL_3    (2000*2)/65535

#define ACCEL_CONVERSION_FS_SEL_0    (2*2)/65535
#define ACCEL_CONVERSION_FS_SEL_1    (4*2)/65535
#define ACCEL_CONVERSION_FS_SEL_2    (8*2)/65535
#define ACCEL_CONVERSION_FS_SEL_3    (16*2)/65535

#define MAG_CONVERSION_16_BITS      (4912*2)/65535

MPU9250 margSensor();
int16_t dataSensor[10]; //[NumSensors] (3gyros - 3 Accel - 1 Temp - 3 Mag)

float
    gx,gy,gz,
    ax,ay,az,
    mx,my,mz;

void setup() {
    //Congifuro y comienzo la comunicacion i2c y Serial
     Wire.setSpeed(CLOCK_SPEED_400KHZ);
     Wire.begin();
     Serial.begin(921600);

    //Establesco la configuracion inicial begin()
    margSensor.begin();

    //Set Offsets Giroscopios y acelerometros
    margSensor.setGyroOffsetX(0);
    margSensor.setGyroOffsetY(0);
    margSensor.setGyroOffsetZ(0);
    margSensor.setAccelOffsetX(0);
    margSensor.setAccelOffsetY(0);
    margSensor.setAccelOffsetZ(0);

    /* ============================
    Seleccione escala de Giroscopios:
    0 = ±250dps =
    1 = ±500 dps =
    2 = ±1000 dps =
    3 = ±2000 dps =
    ===============================*/
    margSensor.setGyroScale(3);// +-2000 dps

    /* ============================
    Seleccione escala de Acelerometros:
    0 = ±2g
    1 = ±4g
    2 = ±8g
    3 = ±16g
    ===============================*/
    margSensor.setAccelScale(1);// +-4g
    /*=======================================================
     Configuracion de Filtro Pasa Bajas para Acelerometros
     Value = 3dB BW[Hz]     Rate[Khz]       Delay(ms)
        0  =    1046            4            0.503
        1  =     218            1            1.88
        2  =     218            1            1.88
        3  =      99            1            2.88
        4  =    44.8            1            4.88
        5  =    21.2            1            8.87
        6  =    10.2            1           16.83
        7  =    5.05            1           32.48
        8  =     420            1            1.38
    =========================================================*/
    margSensor.setAccelDLPF(2);
}

void loop() {
    margSensor.Read9Axis(dataSensor);
    dataSensorPrint();
}

//---------------------------- Comunicacion Serial Matlab ------------------------------
void dataSensorPrint(){
  // The sensor values is stored in dataSensor[x] as follows:
  // dataSensor[0] ~ dataSensor[2] (Acceleration X Axis - Acceleration Y Axis - Acceleration Z Axis)
  // dataSensor[3] (Temperature)
  // dataSensor[4] ~ dataSensor[6] (AngularRate X Axis - AngularRate Y Axis - AngularRate Z Axis)
  // dataSensor[7] ~ dataSensor[9] ( MagneticComponent X Axis - MagneticComponent Y Axis - MagneticComponent Z Axis)
    Serial.print(dataSensor[0]); Serial.print("\t");
    Serial.print(dataSensor[1]); Serial.print("\t");
    Serial.print(dataSensor[2]); Serial.print("\t");

    Serial.print(dataSensor[4]); Serial.print("\t");
    Serial.print(dataSensor[5]); Serial.print("\t");
    Serial.print(dataSensor[6]); Serial.print("\t");

    Serial.print(dataSensor[7]); Serial.print("\t");
    Serial.print(dataSensor[8]); Serial.print("\t");
    Serial.println(dataSensor[9]);
}

void SensorConversion(){
    ax=(dataSensor[0])*ACCEL_CONVERSION_FS_SEL_1;
    ay=(dataSensor[1])*ACCEL_CONVERSION_FS_SEL_1;
    az=(dataSensor[2])*ACCEL_CONVERSION_FS_SEL_1;

    gx=(dataSensor[4])*GYRO_CONVERSION_FS_SEL_1;
    gy=(dataSensor[5])*GYRO_CONVERSION_FS_SEL_1;
    gz=(dataSensor[6])*GYRO_CONVERSION_FS_SEL_1;

    mx=(dataSensor[7])*MAG_CONVERSION_16_BITS;
    my=(dataSensor[8])*MAG_CONVERSION_16_BITS;
    mz=(dataSensor[9])*MAG_CONVERSION_16_BITS;
}
