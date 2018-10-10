#pragma once

/* MPU9250 library by Juan David Velasquez Rosero
 */

// This will load the definition for common Particle variable types
#include "Particle.h"

#define MPU9250_DIR 0x68

#define SELF_TEST_X_GYRO 0x00
#define SELF_TEST_Y_GYRO 0x01
#define SELF_TEST_Z_GYRO 0x02

#define SELF_TEST_X_ACCEL 0x0D
#define SELF_TEST_Y_ACCEL 0x0E
#define SELF_TEST_Z_ACCEL 0x0F

#define XG_OFFSET_H 0x13
#define XG_OFFSET_L 0x14
#define YG_OFFSET_H 0x15
#define YG_OFFSET_L 0x16
#define ZG_OFFSET_H 0x17
#define ZG_OFFSET_L 0x18

#define SMPLRT_DIV 0x19
#define CONFIG 0x1A
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define ACCEL_CONFIG2 0x1D
#define LP_ACCEL_ODR 0x1E
#define WOM_THR 0x1F

#define FIFO_EN 0x23

#define I2C_MST_CTRL 0x24
#define I2C_SLAV0_ADDR 0x25
#define I2C_SLAV0_REG 0x26
#define I2C_SLAV0_CTRL 0x27

#define I2C_MST_STATUS 0X36
#define INT_PIN_CFG 0x37
#define INT_ENABLE 0x38
#define INT_STATUS 0x3A

#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40
#define TEMP_OUT_H 0x41
#define TEMP_OUT_L 0x42
#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44
#define GYRO_YOUT_H 0x45
#define GYRO_YOUT_L 0x46
#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48

#define I2C_MTS_DELAY_CTRL 0x67
#define SIGNAL_PATH_RESET 0x68
#define MOT_DETECT_CTRL 0x69
#define USER_CTRL 0x6A
#define PWR_MGMT_1 0x6B
#define PWR_MGMT_2 0x6C

#define FIFO_COUNTH 0x72
#define FIFO_COUNTL 0x73
#define FIFO_R_W 0x74

#define WHO_I_AM 0x75

#define XA_OFFSET_H 0x77
#define XA_OFFSET_L 0x78
#define YA_OFFSET_H 0x7A
#define YA_OFFSET_L 0x7B
#define ZA_OFFSET_H 0x7D
#define ZA_OFFSET_L 0x7E


//------------------------------------ MAGNETOMETER REGISTERS ------------------------------------------------
#define AK8963 0x0C

#define WIA 0x00
#define INFO 0x01
#define ST1 0x02

#define HXL 0x03
#define HXH 0x04
#define HYL 0x05
#define HYH 0x06
#define HZL 0x07
#define HZH 0x08

#define ST1 0x09
#define CNTL1 0x0A
#define CNTL2 0x0B
#define I2CDIS 0xFH

class MPU9250 {

 public:

  MPU9250();

    void WriteRegister(byte dir, byte reg, byte data);

    void ReadRegisters(byte dir,byte reg,byte *data,int numReg);

    void begin();

    void getGyroOffsets(int16_t *offsets);

    void getAccelOffsets(int16_t *offsets);

    void setGyroOffsetX(int16_t gxo);

    void setGyroOffsetY(int16_t gyo);

    void setGyroOffsetZ(int16_t gzo);

    void setAccelOffsetX(int16_t axo);

    void setAccelOffsetY(int16_t ayo);

    void setAccelOffsetZ(int16_t azo);

    void setGyroScale(byte scale);

    void setAccelScale(byte scale);

    void setAccelDLPF(char mode);

    void Read9Axis(int16_t *axisOut);
};
