/* MPU9250 library by Juan David Velasquez Rosero
 */

#include "MPU9250.h"

//--------- Configure the pinsCS as Output (Select Node Sensor - Active LOW) -------------------
MPU9250::MPU9250(){

}
// --------- This function is used to Write 1 data byte "data" in the Register Address "reg" for the Device Address "dir"-------------
void MPU9250::WriteRegister(byte dir, byte reg, byte data){
      Wire.beginTransmission(dir);
      Wire.write(reg);
      Wire.write(data);
      Wire.endTransmission();
}

// --------- This function is used to Read "numReg" bytes starting in Register Address "reg" for the Device Address "dir", and store the reading data in "data" pointer  -------------
void MPU9250::ReadRegisters(byte dir,byte reg,byte *data,int numReg){
      Wire.beginTransmission(dir);
      Wire.write(reg);
      Wire.endTransmission();
      Wire.requestFrom(dir, numReg);
      if (Wire.available() == numReg)
      {
        for(int i=0;i<numReg;i++)data[i] = Wire.read();
      }
}
// --------- This function is used to  -------------
void MPU9250::begin(){
    WriteRegister(MPU9250_DIR,PWR_MGMT_1,0x80);// H_RESET bit is congifure as 1. Reset the internal registers and restores the default settings
    delay(100);
    WriteRegister(MPU9250_DIR,PWR_MGMT_1,0x01); // CLKSEL bits is configure as 001. Auto selects the best available clock source – PLL if ready, else use the Internal oscillator 20Mhz
    WriteRegister(MPU9250_DIR,CONFIG,0x01); // FIFO Overwriting, DLPF_CFG[2:0] 001 (with FCHOICE_B= 00) == Bandwidth (184 Hz) , Delay (2.9 ms) and Fs (1 kHz)
    WriteRegister(MPU9250_DIR,GYRO_CONFIG,0x00); //Fchoice_b[1:0] = 00
    WriteRegister(MPU9250_DIR,INT_PIN_CFG,0x32);//MAG CONECTADO (BYPASS_EN bit is configure as 1 // the host application processor will be able to directly access the auxiliary I2C bus of the MPU-9250 )
    WriteRegister(MPU9250_DIR,PWR_MGMT_2,0x00); // ACTIVATE all gyros and accelerometers. (Active LOW bits)
    WriteRegister(MPU9250_DIR,FIFO_EN,0x00); //FIFO FUNCTIONALITY OFF
    WriteRegister(MPU9250_DIR,USER_CTRL,0x40);//I2C_MST_EN bit is configure as 1, Enable the I2C Master I/F module; pins ES_DA and ES_SCL are isolated from pins SDA/SDI and SCL/ SCLK. (con 1 separo los pines ES_DA y ES_SCL de SDA y SCL y con 0 los junto )
    WriteRegister(AK8963,CNTL2,0x01);//Reset Magnetometer Registers
    delay(100);
    WriteRegister(AK8963,CNTL1,0x16); // Magnetometer .... BIT = 1 (16-bit output) and MODE[3:0] = 0110 (Continuous measurement mode 2 = 100Hz)
}

// ----------------------  GET OFFSETS ---------------------------
//----------------------------------------------------------------
//----------------------------------------------------------------

//-------------- Get Gyro offsets ----------------------
void MPU9250::getGyroOffsets(int16_t *offsets){
    byte dataOffsets[6];
    ReadRegisters(MPU9250_DIR,XG_OFFSET_H,dataOffsets,6);

    offsets[0]=(dataOffsets[0]<<8) | dataOffsets[1];
    offsets[1]=(dataOffsets[2]<<8) | dataOffsets[3];
    offsets[2]=(dataOffsets[4]<<8) | dataOffsets[5];
}

//-------------- Get Accel offsets ----------------------
void MPU9250::getAccelOffsets(int16_t *offsets){
    byte dataOffsetX[2];
    byte dataOffsetY[2];
    byte dataOffsetZ[2];

    ReadRegisters(MPU9250_DIR,XA_OFFSET_H,dataOffsetX,2);
    ReadRegisters(MPU9250_DIR,YA_OFFSET_H,dataOffsetY,2);
    ReadRegisters(MPU9250_DIR,ZA_OFFSET_H,dataOffsetZ,2);

    offsets[0]=(dataOffsetX[0]<<8) | dataOffsetX[1];
    offsets[1]=(dataOffsetY[0]<<8) | dataOffsetY[1];
    offsets[2]=(dataOffsetZ[0]<<8) | dataOffsetZ[1];
}

// ----------------------  SET OFFSETS ---------------------------
//----------------------------------------------------------------
//----------------------------------------------------------------
void MPU9250::setGyroOffsetX(int16_t gxo){
    WriteRegister(MPU9250_DIR,XG_OFFSET_H,((gxo>>8) & 0xFF));
    WriteRegister(MPU9250_DIR,XG_OFFSET_L,(gxo&0xFF));
}

void MPU9250::setGyroOffsetY(int16_t gyo){
    WriteRegister(MPU9250_DIR,YG_OFFSET_H,((gyo>>8) & 0xFF));
    WriteRegister(MPU9250_DIR,YG_OFFSET_L,(gyo&0xFF));
}

void MPU9250::setGyroOffsetZ(int16_t gzo){
    WriteRegister(MPU9250_DIR,ZG_OFFSET_H,((gzo>>8) & 0xFF));
    WriteRegister(MPU9250_DIR,ZG_OFFSET_L,(gzo&0xFF));
}

void MPU9250::setAccelOffsetX(int16_t axo){
    WriteRegister(MPU9250_DIR,XA_OFFSET_H, (0xED | ((axo>>8) & 0xFF)) );
    WriteRegister(MPU9250_DIR,XA_OFFSET_L, (0xB6 | (axo&0xFF)) );
}

void MPU9250::setAccelOffsetY(int16_t ayo){
    WriteRegister(MPU9250_DIR,YA_OFFSET_H,( 0xE7 | ((ayo>>8) & 0xFF)) );
    WriteRegister(MPU9250_DIR,YA_OFFSET_L,( 0x30 | (ayo&0xFF) ));
}

void MPU9250::setAccelOffsetZ(int16_t azo){
    WriteRegister(MPU9250_DIR,ZA_OFFSET_H,( 0x24 | ((azo>>8) & 0xFF)) );
    WriteRegister(MPU9250_DIR,ZA_OFFSET_L,( 0x80 | (azo&0xFF) ));
}

// ----------------------  SET SCALE -----------------------------
//----------------------------------------------------------------
//----------------------------------------------------------------
void MPU9250::setGyroScale(byte scale){
    WriteRegister(MPU9250_DIR,GYRO_CONFIG, (scale & 0x3)<<3 );
    byte dd[1];
    ReadRegisters(MPU9250_DIR,GYRO_CONFIG,dd,1);
    Serial.println(dd[0]);
}

void MPU9250::setAccelScale(byte scale){
    WriteRegister(MPU9250_DIR,ACCEL_CONFIG, (scale & 0x3)<<3 ) ;
}

void MPU9250::setAccelDLPF(char mode){
    if(mode==0)WriteRegister(MPU9250_DIR,ACCEL_CONFIG2, 0x98 ) ;
    if((mode>0) & (mode<9))WriteRegister(MPU9250_DIR,ACCEL_CONFIG2, 0x90 | ((mode-1)&0x7) ) ;
}

//----------------------------------------- READ SENSOR ARRAY ----------------------------------------------------
//----------------------------------------------------------------------------------------------------------------

void MPU9250::Read9Axis(int16_t *axisOut){
    //--------------------ACCEL, GYRO y TEMP---------------------
    byte data[14];
    memset(data,0,sizeof(data));
    ReadRegisters(MPU9250_DIR,ACCEL_XOUT_H,data,14);

    for(int i=0;i<7;i++){
        axisOut[i]= (data[2*i]<<8) | data[2*i + 1];
    }

    //--------------------------MAGNETOMETRO-----------------------
    byte data2[7];
    memset(data2,0,sizeof(data2));
    ReadRegisters(AK8963,HXL,data2,7);

    for(int i=0;i<3;i++){
        axisOut[7+i] = ((data2[2*i+1]<<8) | data2[2*i]);
    }
}
