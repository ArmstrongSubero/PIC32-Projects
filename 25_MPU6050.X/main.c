/*
 * File: Main.c
 * Author: Armstrong Subero
 * Processor: PIC32MX270F256D w/Ext OSC @ 4MHz, PLL to 48 MHz, 3.3v
 * Program: 25_MPU6050
 * Compiler: XC32 (v1.44, MPLAX X v4.00)
 * Program Version: 1.0
 *                             
 * Program Description: This Program Allows PIC32MX270F256D to use the MPU6050
 *                      I2C module. There is also the use of a Madgwick filter
 *                      to perform sensor fusion,though the output is not as 
 *                      stable as tested on other platforms.   
 * 
 * Hardware Description: A MPU6050 sensor is connected to I2C1 
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     03/04/2018    Initial Release.
 * 
 *                      
 * Created September 18th, 2018, 8:43 PM
 */

/*******************************************************************************
 Includes and defines
*******************************************************************************/
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "PIC32MX270_STD.h"
#include "Delay.h"
#include "uart1.h"
#include "i2c.h"
#include <string.h>

#define MPU6050_ADDRESS                 0x68 // MPU6050 Address
#define MPU6050_RA_XG_OFFS_TC           0x00
#define MPU6050_RA_YG_OFFS_TC           0x01
#define MPU6050_RA_ZG_OFFS_TC           0x02
#define MPU6050_RA_X_FINE_GAIN          0x03
#define MPU6050_RA_Y_FINE_GAIN          0x04
#define MPU6050_RA_Z_FINE_GAIN          0x05
#define MPU6050_RA_XA_OFFS_H            0x06
#define MPU6050_RA_XA_OFFS_L_TC         0x07
#define MPU6050_RA_YA_OFFS_H            0x08
#define MPU6050_RA_YA_OFFS_L_TC         0x09
#define MPU6050_RA_ZA_OFFS_H            0x0A
#define MPU6050_RA_ZA_OFFS_L_TC         0x0B
#define MPU6050_RA_XG_OFFS_USRH         0x13
#define MPU6050_RA_XG_OFFS_USRL         0x14
#define MPU6050_RA_YG_OFFS_USRH         0x15
#define MPU6050_RA_YG_OFFS_USRL         0x16
#define MPU6050_RA_ZG_OFFS_USRH         0x17
#define MPU6050_RA_ZG_OFFS_USRL         0x18
#define MPU6050_RA_SMPLRT_DIV           0x19
#define MPU6050_RA_CONFIG               0x1A
#define MPU6050_RA_GYRO_CONFIG          0x1B
#define MPU6050_RA_ACCEL_CONFIG         0x1C
#define MPU6050_RA_FF_THR               0x1D
#define MPU6050_RA_FF_DUR               0x1E
#define MPU6050_RA_MOT_THR              0x1F
#define MPU6050_RA_MOT_DUR              0x20
#define MPU6050_RA_ZRMOT_THR            0x21
#define MPU6050_RA_ZRMOT_DUR            0x22
#define MPU6050_RA_FIFO_EN              0x23
#define MPU6050_RA_I2C_MST_CTRL         0x24
#define MPU6050_RA_I2C_SLV0_ADDR        0x25
#define MPU6050_RA_I2C_SLV0_REG         0x26
#define MPU6050_RA_I2C_SLV0_CTRL        0x27
#define MPU6050_RA_I2C_SLV1_ADDR        0x28
#define MPU6050_RA_I2C_SLV1_REG         0x29
#define MPU6050_RA_I2C_SLV1_CTRL        0x2A
#define MPU6050_RA_I2C_SLV2_ADDR        0x2B
#define MPU6050_RA_I2C_SLV2_REG         0x2C
#define MPU6050_RA_I2C_SLV2_CTRL        0x2D
#define MPU6050_RA_I2C_SLV3_ADDR        0x2E
#define MPU6050_RA_I2C_SLV3_REG         0x2F
#define MPU6050_RA_I2C_SLV3_CTRL        0x30
#define MPU6050_RA_I2C_SLV4_ADDR        0x31
#define MPU6050_RA_I2C_SLV4_REG         0x32
#define MPU6050_RA_I2C_SLV4_DO          0x33
#define MPU6050_RA_I2C_SLV4_CTRL        0x34
#define MPU6050_RA_I2C_SLV4_DI          0x35
#define MPU6050_RA_I2C_MST_STATUS       0x36
#define MPU6050_RA_INT_PIN_CFG          0x37
#define MPU6050_RA_INT_ENABLE           0x38
#define MPU6050_RA_DMP_INT_STATUS       0x39
#define MPU6050_RA_INT_STATUS           0x3A
#define MPU6050_RA_ACCEL_XOUT_H         0x3B
#define MPU6050_RA_ACCEL_XOUT_L         0x3C
#define MPU6050_RA_ACCEL_YOUT_H         0x3D
#define MPU6050_RA_ACCEL_YOUT_L         0x3E
#define MPU6050_RA_ACCEL_ZOUT_H         0x3F
#define MPU6050_RA_ACCEL_ZOUT_L         0x40
#define MPU6050_RA_TEMP_OUT_H           0x41
#define MPU6050_RA_TEMP_OUT_L           0x42
#define MPU6050_RA_GYRO_XOUT_H          0x43
#define MPU6050_RA_GYRO_XOUT_L          0x44
#define MPU6050_RA_GYRO_YOUT_H          0x45
#define MPU6050_RA_GYRO_YOUT_L          0x46
#define MPU6050_RA_GYRO_ZOUT_H          0x47
#define MPU6050_RA_GYRO_ZOUT_L          0x48
#define MPU6050_RA_EXT_SENS_DATA_00     0x49
#define MPU6050_RA_EXT_SENS_DATA_01     0x4A
#define MPU6050_RA_EXT_SENS_DATA_02     0x4B
#define MPU6050_RA_EXT_SENS_DATA_03     0x4C
#define MPU6050_RA_EXT_SENS_DATA_04     0x4D
#define MPU6050_RA_EXT_SENS_DATA_05     0x4E
#define MPU6050_RA_EXT_SENS_DATA_06     0x4F
#define MPU6050_RA_EXT_SENS_DATA_07     0x50
#define MPU6050_RA_EXT_SENS_DATA_08     0x51
#define MPU6050_RA_EXT_SENS_DATA_09     0x52
#define MPU6050_RA_EXT_SENS_DATA_10     0x53
#define MPU6050_RA_EXT_SENS_DATA_11     0x54
#define MPU6050_RA_EXT_SENS_DATA_12     0x55
#define MPU6050_RA_EXT_SENS_DATA_13     0x56
#define MPU6050_RA_EXT_SENS_DATA_14     0x57
#define MPU6050_RA_EXT_SENS_DATA_15     0x58
#define MPU6050_RA_EXT_SENS_DATA_16     0x59
#define MPU6050_RA_EXT_SENS_DATA_17     0x5A
#define MPU6050_RA_EXT_SENS_DATA_18     0x5B
#define MPU6050_RA_EXT_SENS_DATA_19     0x5C
#define MPU6050_RA_EXT_SENS_DATA_20     0x5D
#define MPU6050_RA_EXT_SENS_DATA_21     0x5E
#define MPU6050_RA_EXT_SENS_DATA_22     0x5F
#define MPU6050_RA_EXT_SENS_DATA_23     0x60
#define MPU6050_RA_MOT_DETECT_STATUS    0x61
#define MPU6050_RA_I2C_SLV0_DO          0x63
#define MPU6050_RA_I2C_SLV1_DO          0x64
#define MPU6050_RA_I2C_SLV2_DO          0x65
#define MPU6050_RA_I2C_SLV3_DO          0x66
#define MPU6050_RA_I2C_MST_DELAY_CTRL   0x67
#define MPU6050_RA_SIGNAL_PATH_RESET    0x68
#define MPU6050_RA_MOT_DETECT_CTRL      0x69
#define MPU6050_RA_USER_CTRL            0x6A
#define MPU6050_RA_PWR_MGMT_1           0x6B
#define MPU6050_RA_PWR_MGMT_2           0x6C
#define MPU6050_RA_BANK_SEL             0x6D
#define MPU6050_RA_MEM_START_ADDR       0x6E
#define MPU6050_RA_MEM_R_W              0x6F
#define MPU6050_RA_DMP_CFG_1            0x70
#define MPU6050_RA_DMP_CFG_2            0x71
#define MPU6050_RA_FIFO_COUNTH          0x72
#define MPU6050_RA_FIFO_COUNTL          0x73
#define MPU6050_RA_FIFO_R_W             0x74
#define MPU6050_RA_WHO_AM_I             0x75

// +/-2 16384, +/-4 8192, +/-8 4096, +/-16 2048
// Value for calculating G's
#define G_CALC_VAL    8192.0

#define LED LATBbits.LATB14

// Volatile Variables
volatile int   GYRO_XOUT, GYRO_YOUT, GYRO_ZOUT;
volatile int   ACCEL_XOUT, ACCEL_YOUT, ACCEL_ZOUT;

// Global variables
double acc_x;
double acc_y;
double acc_z;
double gyro_x;
double gyro_y;
double gyro_z;

int info;
char buf[25];
int cal_var = 0;

double   gyro_x_offset;
double   gyro_y_offset;
double   gyro_z_offset;

char gyro_x_out[10];
char gyro_y_out[10];
char gyro_z_out[10];
char accel_x_out[10];
char accel_y_out[10];
char accel_z_out[10];

// quaternion values
char q0_t[10];
char q1_t[10];
char q2_t[10];
char q3_t[10];


#include "MadgwickAHRS.h"
/*******************************************************************************
* Function Name: void initMain (void)
*
* Specification: initializes main
*
*******************************************************************************/
void initMain(void)
{  
    uc_init();                  // initialize microcontroller
    TRISBbits.TRISB14 = 0;      // set PINB1 as output
    
    // unlock PPS
    systemReg_Unlock();
    CFGCONbits.IOLOCK = 0;

    RPC5Rbits.RPC5R = 0x0001;   //RC5->UART1 TX

    // lock PPS
    CFGCONbits.IOLOCK = 1; 
    systemReg_Lock();
    
    i2c_master_setup();        // initialize master I2C
    UART1_Initialize();        // initialize UART
}


int MPU6050_Write(int mpaddr, int add, int Data)
{
    i2c_master_start();
    i2c_master_send(mpaddr);
    i2c_master_send(add);
    i2c_master_send(Data);
    i2c_master_stop();
}

int MPU6050_Read(unsigned short addr, int raddr)
{
    int rdata;
    
    i2c_master_start();
    i2c_master_send(addr);
    i2c_master_send(raddr);
    i2c_master_restart();
    i2c_master_send(0xD1);
    rdata = i2c_master_recv();
    i2c_master_ack(1);
    i2c_master_stop();
    
    return rdata;  
}

// Initializes the IMU
void MPU6050_Init(void)
{
    // Wakeup from sleep
    MPU6050_Write(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, 0x00);
    
    // sample rate = 8kHz / 1 + 7999 = 1 Hz
    MPU6050_Write(MPU6050_ADDRESS,  MPU6050_RA_SMPLRT_DIV, 7999);

    // Write Accelerometer to +\- 4g
   MPU6050_Write(MPU6050_ADDRESS, MPU6050_RA_ACCEL_CONFIG, 0x00);

   // gyro scale of 2000 degrees/s
   MPU6050_Write(MPU6050_ADDRESS, MPU6050_RA_GYRO_CONFIG, 0x18);

   // Disable Frame Sync, Set Digital Low pass filter to 256Hz DLPF
   MPU6050_Write(MPU6050_ADDRESS, MPU6050_RA_CONFIG, 0x00);

    // Disable sensor output to FIFO buffer
   MPU6050_Write(MPU6050_ADDRESS, MPU6050_RA_FIFO_EN, 0x00);

    // AUX I2C setup, single master control
   MPU6050_Write(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_CTRL, 0x00);
   
    // Setup INT pin and AUX I2C pass through
   MPU6050_Write(MPU6050_ADDRESS, MPU6050_RA_INT_PIN_CFG, 0x00);

    // Enable data ready interrupt
   MPU6050_Write(MPU6050_ADDRESS, MPU6050_RA_INT_ENABLE, 0x00);
}

// Read the raw accel vlaue from the IMU
int MPU6050_Accel_Raw(char axis)
{
    //Variables for high and low accel values
    int   ACCEL_XOUT_H, ACCEL_XOUT_L, ACCEL_YOUT_H;
    int   ACCEL_YOUT_L, ACCEL_ZOUT_H, ACCEL_ZOUT_L;

    // Read accelerometer values out from H and L registers
    ACCEL_XOUT_H = MPU6050_Read(MPU6050_ADDRESS, MPU6050_RA_ACCEL_XOUT_H);
    ACCEL_XOUT_L = MPU6050_Read(MPU6050_ADDRESS, MPU6050_RA_ACCEL_XOUT_L);
    ACCEL_YOUT_H = MPU6050_Read(MPU6050_ADDRESS, MPU6050_RA_ACCEL_YOUT_H);
    ACCEL_YOUT_L = MPU6050_Read(MPU6050_ADDRESS, MPU6050_RA_ACCEL_YOUT_L);
    ACCEL_ZOUT_H = MPU6050_Read(MPU6050_ADDRESS, MPU6050_RA_ACCEL_ZOUT_H);
    ACCEL_ZOUT_L = MPU6050_Read(MPU6050_ADDRESS, MPU6050_RA_ACCEL_ZOUT_L);
    
    // Convert received data
    ACCEL_XOUT = ( ACCEL_XOUT_H<<8 | ACCEL_XOUT_L );
    ACCEL_YOUT = ( ACCEL_YOUT_H<<8 | ACCEL_YOUT_L );
    ACCEL_ZOUT = ( ACCEL_ZOUT_H<<8 | ACCEL_ZOUT_L );
    

    // Return value to user based on reqiested axis
    switch (axis)
    {
        case 'X':
            return ACCEL_XOUT;    //  Accel X Axis
            break;
        case 'Y':
            return ACCEL_YOUT;    // Accel Y Axis
            break;
        case 'Z':
            return ACCEL_ZOUT;    //  Accel Z Axis
            break;
        default:
            return 0;
    }
}


// Read the accel value and convert to G's
double MPU6050_Read_Accel(char axis)
{
    // Variables for high and low accel values
    int  ACCEL_XOUT_H, ACCEL_XOUT_L, ACCEL_YOUT_H;
    int  ACCEL_YOUT_L, ACCEL_ZOUT_H, ACCEL_ZOUT_L;
    
    float  GFORCEX;
    float  GFORCEY;
    float  GFORCEZ;

    // Read accelerometer values out from H and L registers
    ACCEL_XOUT_H = MPU6050_Read(MPU6050_ADDRESS, MPU6050_RA_ACCEL_XOUT_H);
    ACCEL_XOUT_L = MPU6050_Read(MPU6050_ADDRESS, MPU6050_RA_ACCEL_XOUT_L);
    ACCEL_YOUT_H = MPU6050_Read(MPU6050_ADDRESS, MPU6050_RA_ACCEL_YOUT_H);
    ACCEL_YOUT_L = MPU6050_Read(MPU6050_ADDRESS, MPU6050_RA_ACCEL_YOUT_L);
    ACCEL_ZOUT_H = MPU6050_Read(MPU6050_ADDRESS, MPU6050_RA_ACCEL_ZOUT_H);
    ACCEL_ZOUT_L = MPU6050_Read(MPU6050_ADDRESS, MPU6050_RA_ACCEL_ZOUT_L);

    // Convert received data
    ACCEL_XOUT = ( ACCEL_XOUT_H<<8 | ACCEL_XOUT_L );
    ACCEL_YOUT = ( ACCEL_YOUT_H<<8 | ACCEL_YOUT_L );
    ACCEL_ZOUT = ( ACCEL_ZOUT_H<<8 | ACCEL_ZOUT_L );
    
    // Calculate G-Force Data
    GFORCEX = (ACCEL_XOUT  / G_CALC_VAL);
    GFORCEY = (ACCEL_YOUT  / G_CALC_VAL);
    GFORCEZ = (ACCEL_ZOUT  / G_CALC_VAL);

    // Return G's value to user
    switch (axis)
    {
        case 'X':
            return GFORCEX;    //  Gforce X Axis
            break;
        case 'Y':
            return GFORCEY;    // Gforce Y Axis
            break;
        case 'Z':
            return GFORCEZ;    //  Gforce Z Axis
            break;
        default:
            return 0;
    }
}

// Read the raw gyro data from the IMU
int MPU6050_Gyro_Raw(char axis)
{
    int  GYRO_XOUT_H, GYRO_XOUT_L;
    int  GYRO_YOUT_H, GYRO_YOUT_L;
    int  GYRO_ZOUT_H ,GYRO_ZOUT_L;

    /* Read data from gyroscope */
    GYRO_XOUT_H = MPU6050_Read(MPU6050_ADDRESS, MPU6050_RA_GYRO_XOUT_H);
    GYRO_XOUT_L = MPU6050_Read(MPU6050_ADDRESS, MPU6050_RA_GYRO_XOUT_L);

    GYRO_YOUT_H = MPU6050_Read(MPU6050_ADDRESS, MPU6050_RA_GYRO_YOUT_H);
    GYRO_YOUT_L = MPU6050_Read(MPU6050_ADDRESS, MPU6050_RA_GYRO_YOUT_L);
    
    GYRO_ZOUT_H = MPU6050_Read(MPU6050_ADDRESS, MPU6050_RA_GYRO_ZOUT_H);
    GYRO_ZOUT_L = MPU6050_Read(MPU6050_ADDRESS, MPU6050_RA_GYRO_ZOUT_L);

    // Convert received data
    GYRO_XOUT = ( GYRO_XOUT_H << 8 | GYRO_XOUT_L );
    GYRO_YOUT = ( GYRO_YOUT_H << 8 | GYRO_YOUT_L );
    GYRO_ZOUT = ( GYRO_ZOUT_H << 8 | GYRO_ZOUT_L );

    // Return value to user
    switch (axis)
    {
        case 'X':
            return GYRO_XOUT;    // Gyro X Axis
            break;
        case 'Y':
            return GYRO_YOUT;    //  Gyro Y Axis
            break;
        case 'Z':
            return GYRO_ZOUT;    //  Gyro Z Axis
            break;
        default:
            return 0;
    }
}



/*******************************************************************************
* Function Name: void main (void)
*
* Specification: main function
*
*******************************************************************************/
void main(void) {
    
    initMain();                         // initializes main function
    __XC_UART = 1;                      // configure printf to use UART1
   
    MPU6050_Init();
    delay_ms(1000);
    int v;
  
    buf[0] =  MPU6050_RA_WHO_AM_I;
    i2c_master_start();
    i2c_master_send(0xD0);
    i2c_master_send(MPU6050_RA_WHO_AM_I);
    i2c_master_restart();
    i2c_master_send(0xD1);
    v = i2c_master_recv();
    i2c_master_ack(1);
    i2c_master_stop();
    

    if(v == 0x68)
    {
        printf("Working");
    }
    else
    {
        printf("Not working");
    }
    
    
     // Calculate gyro offset
      for (cal_var = 0; cal_var <= 1000; cal_var++)
      {
        gyro_x_offset += MPU6050_Gyro_Raw('X');
        gyro_y_offset += MPU6050_Gyro_Raw('Y');
        gyro_z_offset += MPU6050_Gyro_Raw('Z');
        
        delay_ms(1);
      }
      
      // Determine gyro offset for 64 read values
      gyro_x_offset /= 1000;
      gyro_y_offset /= 1000;
      gyro_z_offset /= 1000;
    
    
    printf("\n");
    
    while(1)
    {
       // Read gyro values and convert to Radians per second
       gyro_x  =  (MPU6050_Gyro_Raw('X')  - gyro_x_offset)  / 939.650784f;
       gyro_y  =  (MPU6050_Gyro_Raw('Y')  - gyro_y_offset)  / 939.650784f;
       gyro_z  =  (MPU6050_Gyro_Raw('Z')  - gyro_z_offset)  / 939.650784f;
       
       // Read accel values  and convert relative to 1G
       acc_x = MPU6050_Read_Accel('X') / 2.0f;
       acc_y = MPU6050_Read_Accel('Y') / 2.0f;
       acc_z = MPU6050_Read_Accel('Z') / 2.0f;

       
       /////////////////////////////////////
       // Apply Madgwick filter on values
       ////////////////////////////////////
       MadgwickAHRSupdateIMU(gyro_x, gyro_y, gyro_z, acc_x, acc_y, acc_z);
       
       ///////////////////////////////////////
       // Send unit quaternion values as csv
       ///////////////////////////////////////
       sprintf(q3_t, "%7.2f,%7.2f,%7.2f,%7.2f\n", q0, q1, q2,q3);
       printf(q3_t);
                
       delay_ms(8);
  
    }
 
}
