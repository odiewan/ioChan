#ifndef ioChannel_h__
#define ioChannel_h__
#include <stdint.h>
#include <Arduino.h>
#include "Servo.h"

#define C_TO_KELVIIN          273.15
#define ROOM_TEMP_C           25.0
#define TRIM_C                6.0


#define ACCUM_HR_MAX          250
#define ACCUM_HY_MAX          250
#define ACCUM_LY_MAX          250
#define ACCUM_LR_MAX          250

#define AIN_RAW_OFFSET        0
#define AIN_OAT_OFFSET        50

#define DWELL_MAX             1885
#define DWELL_MIN             1115
#define DWELL_RANGE           771

#define MAX_AIN               1023.0
//#define MAX_AIN               1023

#define ON                    1
#define OFF                   0

#define PING_MAX_INTV         18400

#define PULSE_PER_CM          22000
#define PULSE_IN_TIMEOUT      200

#define PWM_8_MAX             255
#define PWM_10_MAX            1023
#define PWM_16_MAX            65535

// PWM Duty cycle (0-255) per PWM ENG (0-10000) -> 10000/255 = 39.21
#define PWM_DC_PER_PWM_ENG    39

#define PWM_ENG_MAX           10000

#define RX_IN_MAX             2137.0
#define RX_IN_MIN             905.0
#define RX_IN_RANGE           (RX_IN_MAX - RX_IN_MIN)

#define SERVO_CMD_MIN         0
#define SERVO_CMD_MAX         180

#define SERVO_POS_MAX         1800
#define SERVO_POS_MID         900
#define SERVO_POS_MIN         0
#define SERVO_POS_RANGE       (SERVO_POS_MAX - SERVO_POS_MIN)

#define SERVO_SPD_FWD_MAX     180
#define SERVO_SPD_REV_MAX     0
#define SERVO_SPD_ZERO        90

#define S1_WEIGHT             10.0
#define S2_WEIGHT             7.0
#define WEIGHT_TOTAL          S1_WEIGHT + S2_WEIGHT

//---NOTE: Teensy board analog inputs are not 5v tolerant. The predefined
//         scalings (5v, 12v, 15v, 31v) assume a voltage divider that scales
//         to 3.3v
enum ioChanTypeEnum {
  IO_TYPE_UNCONFIG,
  IO_TYPE_AIN_NORM,               // Linear conversion using gain and offset
  IO_TYPE_AIN_RAW,                // No gain or offset, eng Val = raw val

  IO_TYPE_AIN_3V3_1800,           // 0-3.3v scaled to 0-1800 for use as a servo cmd value
  IO_TYPE_AIN_3V3_255,           // 0-3.3v scaled to 0-255

  IO_TYPE_AIN_3V3_3V3,            // 0-3.3v scaled to 3.3v 10bit Analog
  IO_TYPE_AIN_5V_3V3,             // 0-5v scaled to 3.3v 10bit Analog
  IO_TYPE_AIN_10V_3V3,            // 0-10v scaled to 3.3v 10bit Analog
  IO_TYPE_AIN_12V_3V3,            // 0-12v scaled to 3.3v 10bit Analog
  IO_TYPE_AIN_15V_3V3,            // 0-15v scaled to 3.3v 10bit Analog
  IO_TYPE_AIN_31V_3V3,            // 0-31v scaled to 3.3v 10bit Analog

  IO_TYPE_AIN_THERM_3V3,             // Narrow linear approx Vishay NTCLE100E3103 NTC
  IO_TYPE_AIN_LM35_3V3,           // Using linear integrated LM35 circuit, 1degC/10mv
  IO_TYPE_AIN_THERM_STIEN_3V3,    // Using 10k thermistor with Steinhart-Hart

  IO_TYPE_AIN_INTERP,             // Interpolated conversion using lookup chart
  IO_TYPE_AIN_INTERP_USER,        // Interpolated conversion using user lookup chart
  IO_TYPE_AIN_INTERP_OAT_C,       // Interp using OAT C lookup chart for Vishay NTCLE100E3103 NTC
  IO_TYPE_AIN_INTERP_COOLANT_C,   // Interpolated conversion using Coolant C lookup chart
  IO_TYPE_AIN_INTERP_OAT_F,       /* Interpolated conversion using OAT C lookup chart for
                                     Vishay NTCLE100E3103 NTC
                                     which is 10K at 25 degrees Celsius */
  IO_TYPE_AIN_INTERP_COOLANT_F,   // Interpolated conversion using Coolant F lookup chart

  IO_TYPE_DIN_BIN,                // Simple digital, pull up nominally high
  IO_TYPE_DIN_BIN_R,              // Simple digital, pull up nominally low (reversed)
  IO_TYPE_DIN_PWM,                // PWM Input, normal sense, no scaling
  IO_TYPE_DIN_PWM_REV,            // PWM Input, reversed sense, no scaling
  IO_TYPE_DIN_PPM,                // 1024res, 22ms, RC RX PPM input, normal sense, no scaling
  IO_TYPE_DIN_PPM_REV,            // 1024res, 22ms, RC RX PPM input, reverse sense, no scaling
  IO_TYPE_DIN_PPM_SC,             // 1024res, 22ms, RC RX PPM input, normal sense, scaled 0-1800
  IO_TYPE_DIN_PPM_REV_SC,         // 1024res, 22ms, RC RX PPM input, rev sense, scaled 1800-0

  IO_TYPE_DIO_NOM,

  IO_TYPE_DOUT_PWM,
  IO_TYPE_DOUT_PWM_INV,
  IO_TYPE_DOUT_SERVO_180,
  IO_TYPE_DOUT_SERVO_CONT,
  IO_TYPE_DOUT_SERVO_CONT_REV,
  NUM_IO_TYPES
};

enum ioFilterType {
  IO_FILT_NONE,
  IO_FILT_WEIGHTED_AVG,
  IO_FILT_MOVING_AVG,
  NUM_IO_FILTERS
};

enum ioErrState {
  IO_ERR_NONE,
  IO_ERR_CFG,
  IO_ERR_AIN_NOM,                 // 1
  IO_ERR_AIN_MIN,                 // 2
  IO_ERR_AIN_MAX,                 // 3
  IO_ERR_AIN_IMPLAUSIBLE_LOW,     // 4
  IO_ERR_AIN_IMPLAUSIBLE_MAX,     // 5
  IO_ERR_AIN_SHORT,               // 6
  IO_ERR_AIN_OPEN,                // 7
  IO_ERR_AIN_STALE,               // 8

  IO_ERR_DIN_NOM,                 // 9
  IO_ERR_DIN_ERR,                 // 10
  IO_ERR_DIN_UNAVAIL,             // 11

  IO_ERR_DIO_NOM,                 // 12
  IO_ERR_DIO_OUT_ERR_A,           // 13
  IO_ERR_DIO_OUT_ERR_B,           // 14
  IO_ERR_DIO_OUT_ERR_C,           // 15
  IO_ERR_DIO_UNAVAIL,             // 16

  IO_ERR_DOUT_PWM_NOM,            // 17
  IO_ERR_DOUT_PWM_A,              // 18
  IO_ERR_DOUT_PWM_B,              // 19
  IO_ERR_DOUT_PWM_C,              // 20
  IO_ERR_DOUT_PWM_ERR,            // 21
  IO_ERR_DOUT_PWM_UNAVAIL,        // 22

  IO_ERR_DOUT_SERVO_NOM,          // 23
  IO_ERR_DOUT_SERVO_180_NOM,      // 24
  IO_ERR_DOUT_SERVO_180_ERR,      // 25
  IO_ERR_DOUT_SERVO_CONT_NOM,     // 26
  IO_ERR_DOUT_SERVO_CONT_ERR,     // 27
  IO_ERR_DOUT_SERVO_CONT_REV_NOM, // 28
  IO_ERR_DOUT_SERVO_CONT_REV_ERR  // 29
};

//---Channel States-----------------
enum ioChanState {
  IO_ST_NA,
  IO_ST_DEF,
  IO_ST_AIN_OFFLINE,
  IO_ST_AIN_NOMINAL,
  IO_ST_AIN_RAW,                  
  IO_ST_AIN_V,                    
  IO_ST_AIN_3V3,                  
  IO_ST_AIN_5v,                   
  IO_ST_AIN_10V,                  
  IO_ST_AIN_12V,                  
  IO_ST_AIN_15V,                  
  IO_ST_AIN_LOW_RED,              
  IO_ST_AIN_LOW_YEL,              
  IO_ST_AIN_HI_RED,               
  IO_ST_AIN_HI_YEL,               

  IO_ST_DIN_OFFLINE,           
  IO_ST_DIN_NOM,
  IO_ST_DIN,                      
  IO_ST_DIN_R,                    

  IO_ST_DIN_PWM_OFFLINE,          
  IO_ST_DIN_PWM_NOM,              
  IO_ST_DIN_PWM_NOM_REV,          

  IO_ST_DIN_PPM_OFFLINE,
  IO_ST_DIN_PPM_NOM,
  IO_ST_DIN_PPM_NOM_REV,

  IO_ST_DIN_SVO_OFFLINE,
  IO_ST_DIN_SVO_NOM,

  IO_ST_DIO_OFFLINE,              
  IO_ST_DIO_NOM,                  
  IO_ST_DIO_IN_ON,                
  IO_ST_DIO_IN_OFF,               
  IO_ST_DIO_OUT_ON,               
  IO_ST_DIO_OUT_OFF,              

  IO_ST_DOUT_PWM_OFFLINE,         
  IO_ST_DOUT_PWM_NOM,             
  IO_ST_DOUT_PWM_NOM_INV,         

  IO_ST_DOUT_SERVO_OFFLINE,       
  IO_ST_DOUT_SERVO_NOM,           
  IO_ST_DOUT_SERVO_180_OFFLINE,   
  IO_ST_DOUT_SERVO_180_NOM,       
  IO_ST_DOUT_SERVO_180_MIN,       
  IO_ST_DOUT_SERVO_180_ZERO,      
  IO_ST_DOUT_SERVO_180_MAX,       

  IO_ST_DOUT_SERVO_CONT_OFFLINE,  
  IO_ST_DOUT_SERVO_CONT_NOM,      
  IO_ST_DOUT_SERVO_CONT_REV_MAX,  
  IO_ST_DOUT_SERVO_CONT_ZERO,     
  IO_ST_DOUT_SERVO_CONT_FWD_MAX,  
  IO_ST_CFG_ERR,                  
  NUM_IO_STATES
};




enum dispAINSwEnum {
  DISP_AIN_NORM,      // Normal Display: just the engineering value
  DISP_AIN_RAW,
  DISP_AIN_ENG_RAW,   // Displays the engineering value with out fixed points
  DISP_AIN_ENG_VOLT  // Displays the eng value with fixed pts and the voltage
};

enum ioUnitsEnum {
  IOUNIT_NA,
  IOUNIT_VOLTS,
  IOUNIT_AMPS,
  IOUNIT_TEMP_C,
  IOUNIT_TEMP_F,
  IOUNIT_TEMP_HZ,
  IOUNIT_TEMP_PERCENT,
  IOUNIT_TEMP_TIME
};

class ioChannel {
  public:
    int ioRawVal;
    int ioRawValRem; //=== 1023 - ioRawVal
    float ioEngVal;
    float ioEngValFilt;
    int ioFilter;
    float ioGain;
    int ioOffset;
    int ioIntpTemp;
    String ioOutString;
    int ioPin;
    int ioStatus;
    int ioType;
    int ioErr;
    int ioUnits;
    int ioInvert;

    ioChannel();

    ioChannel(ioChanTypeEnum nType, int nPin, int* eValPtr);

    void initChan(void);

    void procInChan(void);
    void procOutChan(void);

    int getRawVal(void);

    int getChanStat(void);
    float getEngVal(void);

  private:
    int *ioExtVarPtr;

    unsigned int ioRawPWM;
    unsigned int ioDutyCycleIn;
    unsigned int ioDutyCycleOut;

    int ioAccumLR;
    int ioAccumHR;
    int ioAccumLY;
    int ioAccumHY;

    int ioCalEngMin;
    int ioCalEngMax;
    int ioMinEngVal;
    int ioMaxEngVal;
    int ioEngValOn;
    int ioEngValOff;

    int ioLowRed;
    int ioLowYel;
    int ioHiYel;
    int ioHiRed;
    int *ioInVal;
    int *ioOutVal;

    Servo *ioServo;

    void procDoutChanPWM();
    void procServoOutChan(void);

    void procPwmInChan(void);
    void procIOChan(void);
    void procAinChan(void);
    void alarmsAIN(void);
    float filterAin(float ainIn);
};

#endif
