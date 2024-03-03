#include <Arduino.h>
#include "ioChan.h"


void ioChannel::constructorCore(ioChanTypeEnum nType, int nPin, int *eValPtr, float *eValPtrFlt) {
  ioOutString = "ioOutString";
  ioErr = IO_ERR_NONE0;
  ioStatus = IO_ST_DEF;

  ioType = nType;
  ioPin = nPin;
  ioExtVarPtr = eValPtr;
  ioExtVarPtrFlt = eValPtrFlt;



  ioUnits = IOUNIT_NA;
  ioFilter = IO_FILT_NONE;

  ioGain = 0;
  ioOffset = 0;

  ioRawVal = 0;
  ioRawValRem = 0;

  ioEngVal = 0;
  ioEngValFilt = 0;

  ioEngValOff = 0;
  ioCalEngMax = 0;
  ioCalEngMin = 0;

  ioMinEngVal = 0;
  ioMaxEngVal = MAX_AIN;
  ioEngValOn = 0;
  ioLowRed = ioMinEngVal;
  ioLowYel = ioMinEngVal;
  ioHiYel = ioMaxEngVal;
  ioHiRed = ioMaxEngVal;
  ioInVal = NULL;
  ioOutVal = NULL;

  ioIntpTemp = 0;

  ioInvert = 0;

  ioServo = NULL;

  ioLowRed = 0;
  ioAccumLR = 0;

  ioLowYel = 0;
  ioAccumLY = 0;

  ioHiYel = 0;
  ioAccumHY = 0;

  ioHiRed = 0;
  ioAccumHR = 0;

  ioInVal = NULL;
  ioOutVal = NULL;
  ioInvert = 0;

  ioRawPWM = 0;
  ioDutyCycleIn = 0;
  ioDutyCycleOut = 0;

  ioIntpTemp = 0;
  ioErr = IO_ERR_NONE1;
}

void ioChannel::initGains() {
  ioErr = IO_ERR_NONE2;
  switch (ioType)
  {
    default:
      break;

    case IO_TYPE_AIN_3V3_1800:
      ioUnits = IOUNIT_NA;
      ioGain = 176; //<--Gain * 10,000
      ioOffset = 0; //<--Offset * 10,000
      ioMinEngVal = ioOffset;
      ioMaxEngVal = (MAX_AIN * ioGain) + ioOffset;
      ioMaxEngVal /= (100);
      ioStatus = IO_ST_AIN_OFFLINE;
      ioErr = IO_ERR_AIN_NOM;
      break;

    case IO_TYPE_AIN_3V3_255:
      ioUnits = IOUNIT_NA;

      ioGain = 254; //<--Gain * 10,000
      ioOffset = 0; //<--Offset * 10,000
      ioMinEngVal = ioOffset;
      ioMaxEngVal = (MAX_AIN * ioGain) + ioOffset;
      ioStatus = IO_ST_AIN_OFFLINE;
      ioErr = IO_ERR_AIN_NOM;
      break;

    case IO_TYPE_AIN_3V3_3V3:
      ioUnits = IOUNIT_VOLTS;

      ioGain = 29;   //<--Gain * 10,000
      ioOffset = -3; //<--Offset * 10,000
      ioMinEngVal = ioOffset;
      ioMaxEngVal = (MAX_AIN * ioGain) + ioOffset;
      ioStatus = IO_ST_AIN_OFFLINE;
      ioErr = IO_ERR_AIN_NOM;
      break;

    case IO_TYPE_AIN_NORM:
    case IO_TYPE_AIN_5V_3V3:
      ioUnits = IOUNIT_VOLTS;

      ioGain = 49;  //<--Gain * 10,000
      ioOffset = 0; //<--Offset * 10,000
      ioMinEngVal = ioOffset;
      ioMaxEngVal = (MAX_AIN * ioGain) + ioOffset;

      ioStatus = IO_ST_AIN_OFFLINE;
      ioErr = IO_ERR_AIN_NOM;
      break;

    case IO_TYPE_AIN_10V_3V3:
      ioUnits = IOUNIT_VOLTS;

      ioGain = 98;  //<--Gain * 10,000
      ioOffset = 0; //<--Offset * 10,000
      ioMinEngVal = ioOffset;
      ioMaxEngVal = (MAX_AIN * ioGain) + ioOffset;

      ioStatus = IO_ST_AIN_OFFLINE;
      ioErr = IO_ERR_AIN_NOM;
      break;

    case IO_TYPE_AIN_12V_3V3:
      ioUnits = IOUNIT_VOLTS;

      ioGain = 117; //<--Gain * 10,000
      ioOffset = 0; //<--Offset * 10,000
      ioMinEngVal = ioOffset;
      ioMaxEngVal = (MAX_AIN * ioGain) + ioOffset;

      ioStatus = IO_ST_AIN_OFFLINE;
      ioErr = IO_ERR_AIN_NOM;
      break;

      //----Top R = 20kOhm, Bottom R = 5k scaled to a 0-3v range
    case IO_TYPE_AIN_15V_3V3:
      ioUnits = IOUNIT_VOLTS;

      ioGain = 144; //<--Gain * 10,000
      ioOffset = 0; //<--Offset * 10,000
      ioMinEngVal = ioOffset;
      ioMaxEngVal = (MAX_AIN * ioGain) + ioOffset;

      ioStatus = IO_ST_AIN_OFFLINE;
      ioErr = IO_ERR_AIN_NOM;
      ioLowRed = 10000; // 10v
      ioLowYel = 11000; // 11v
      ioHiYel = 14500;  // 14.5v
      ioHiRed = 14900;  // 14.9v

      break;

    case IO_TYPE_AIN_31V_3V3:
      ioUnits = IOUNIT_VOLTS;

      ioGain = 263; //<--Gain * 10,000
      ioOffset = 0; //<--Offset * 10,000
      ioMinEngVal = ioOffset;
      ioMaxEngVal = (MAX_AIN * ioGain) + ioOffset;

      ioStatus = IO_ST_AIN_OFFLINE;
      ioErr = IO_ERR_AIN_NOM;
      break;

    case IO_TYPE_AIN_LM35_3V3:
      ioUnits = IOUNIT_TEMP_C;

      ioGain = -3;
      ioOffset = 768;
      // ioGain = -300;    //<--Gain * 10,000
      // ioOffset = 76800; //<--Offset * 10,000

      ioMinEngVal = ioOffset;
      ioMaxEngVal = (MAX_AIN * ioGain) + ioOffset;
      ioStatus = IO_ST_AIN_OFFLINE;
      ioErr = IO_ERR_AIN_NOM;
      break;

    case IO_TYPE_AIN_NTC_90K_3950_3V3:
      ioUnits = IOUNIT_TEMP_C;

      ioGain = 1;   //<--Gain * 10,000
      ioOffset = 1; //<--Offset * 10,000

      ioMinEngVal = ioOffset;
      ioMaxEngVal = MAX_AIN;
      ioStatus = IO_ST_AIN_OFFLINE;
      ioErr = IO_ERR_AIN_NOM;
      break;

    case IO_TYPE_AIN_THERM_STIEN_3V3:

      ioUnits = IOUNIT_TEMP_C;

      ioGain = STEIN_GAIN;
      ioOffset = STEIN_OFFSET;
      ioMinEngVal = ioOffset;
      ioMaxEngVal = MAX_AIN;
      ioStatus = IO_ST_AIN_OFFLINE;
      ioErr = IO_ERR_AIN_NOM;
      break;

    case IO_TYPE_AIN_THERM_3V3:

      ioUnits = IOUNIT_TEMP_C;

      ioGain = 1;   //<--Gain * 10,000
      ioOffset = 1; //<--Offset * 10,000

      ioMinEngVal = ioOffset;
      ioMaxEngVal = MAX_AIN;
      ioStatus = IO_ST_AIN_OFFLINE;
      ioErr = IO_ERR_AIN_NOM;
      break;

    case IO_TYPE_AIN_RAW:
      ioGain = 1;
      ioOffset = 0;
      ioMinEngVal = ioOffset;
      ioMaxEngVal = (MAX_AIN * ioGain) + ioOffset;
      ioStatus = IO_ST_AIN_OFFLINE;
      ioErr = IO_ERR_AIN_NOM;
      break;

    case IO_TYPE_AIN_INTERP_USER:
      ioStatus = IO_ST_AIN_OFFLINE;
      ioErr = IO_ERR_AIN_NOM;
      break;

    case IO_TYPE_DIN_BIN:
    case IO_TYPE_DIN_PWM:
    case IO_TYPE_DIN_PPM:
      ioStatus = IO_ST_DIN_PWM_OFFLINE;
      ioErr = IO_ERR_DIN_NOM;
      ioCalEngMin = RX_IN_MIN;
      ioCalEngMax = RX_IN_MAX;
      break;

    case IO_TYPE_DIN_PPM_SC:
      ioStatus = IO_ST_DIN_PWM_OFFLINE;
      ioErr = IO_ERR_DIN_NOM;
      ioCalEngMin = SERVO_POS_MIN;
      ioCalEngMax = SERVO_POS_MAX;
      break;

    case IO_TYPE_DIN_PWM_REV:
    case IO_TYPE_DIN_PPM_REV:
      ioInvert = 1;
      ioStatus = IO_ST_DIN_PWM_OFFLINE;
      ioErr = IO_ERR_DIN_NOM;
      ioCalEngMin = RX_IN_MAX;
      ioCalEngMax = RX_IN_MIN;
      break;

    case IO_TYPE_DIN_PPM_REV_SC:
      ioInvert = 1;
      ioStatus = IO_ST_DIN_PWM_OFFLINE;
      ioErr = IO_ERR_DIN_NOM;
      ioCalEngMin = SERVO_POS_MAX;
      ioCalEngMax = SERVO_POS_MIN;
      break;

    case IO_TYPE_DIO_NOM:
      ioStatus = IO_ST_DIO_OFFLINE;
      ioErr = IO_ERR_DIO_NOM;
      break;

    case IO_TYPE_DOUT_PWM_INV:
      ioStatus = IO_ST_DOUT_PWM_OFFLINE;
      ioErr = IO_ERR_DOUT_PWM_NOM;
      ioMinEngVal = 0;
      ioMaxEngVal = PWM_ENG_MAX;
      ioEngValOn = PWM_ENG_MAX;
      ioEngValOff = 0;
      ioInvert = 1;
      break;

    case IO_TYPE_DOUT_PWM:
      ioStatus = IO_ST_DOUT_PWM_OFFLINE;
      ioErr = IO_ERR_DOUT_PWM_NOM;
      ioMinEngVal = 0;
      ioMaxEngVal = PWM_ENG_MAX;
      ioEngValOn = PWM_ENG_MAX;
      ioEngValOff = 0;
      break;

    case IO_TYPE_DOUT_SERVO_180:
      ioStatus = IO_ST_DOUT_SERVO_OFFLINE;
      ioErr = IO_ERR_DOUT_SERVO_NOM;
      ioMinEngVal = SERVO_POS_MIN;
      ioMaxEngVal = SERVO_POS_MAX;
      ioEngValOn = PWM_ENG_MAX;
      ioEngValOff = 0;
      break;

    case IO_TYPE_DOUT_SERVO_CONT:
    case IO_TYPE_DOUT_SERVO_CONT_REV:
      ioStatus = IO_ST_DOUT_SERVO_OFFLINE;
      ioErr = IO_ERR_DOUT_SERVO_NOM;
      ioMinEngVal = SERVO_SPD_REV_MAX;
      ioMaxEngVal = SERVO_SPD_FWD_MAX;
      ioEngValOn = PWM_ENG_MAX;
      ioEngValOff = 0;
      break;
  }


}

/*---------------------------------------------------------------------------*/
ioChannel::ioChannel(){
  constructorCore(IO_TYPE_UNCONFIG, 0, NULL, NULL);
  initGains();

  initChan();
}

//-----------------------------------------------------------------------------
ioChannel::ioChannel(ioChanTypeEnum nType, int nPin, int *eValPtr)
{
  constructorCore(nType, nPin, eValPtr, NULL);

  initGains();

  initChan();
}

//-----------------------------------------------------------------------------
ioChannel::ioChannel(ioChanTypeEnum nType, int nPin, float *eValPtrFlt)
{
  constructorCore(nType, nPin, NULL, eValPtrFlt);

  initGains();

  initChan();
}

//-----------------------------------------------------------------------------
void ioChannel::initChan() {
  switch (ioType) {
    default:
      break;

    case IO_TYPE_AIN_NORM:
    case IO_TYPE_AIN_RAW:
    case IO_TYPE_AIN_3V3_255:
    case IO_TYPE_AIN_3V3_1800:
    case IO_TYPE_AIN_3V3_3V3:
    case IO_TYPE_AIN_5V_3V3:
    case IO_TYPE_AIN_10V_3V3:
    case IO_TYPE_AIN_12V_3V3:
    case IO_TYPE_AIN_15V_3V3:
    case IO_TYPE_AIN_31V_3V3:
    case IO_TYPE_AIN_INTERP_USER:
    case IO_TYPE_AIN_INTERP_OAT_C:
    case IO_TYPE_AIN_INTERP_OAT_F:
    case IO_TYPE_AIN_INTERP_COOLANT_C:
    case IO_TYPE_AIN_INTERP_COOLANT_F:
    case IO_TYPE_AIN_THERM_3V3:
    case IO_TYPE_AIN_THERM_STIEN_3V3:
      ioErr = IO_ERR_CFG;
      ioStatus = IO_ST_AIN_OFFLINE;
      pinMode(ioPin, INPUT);
      break;


    case IO_TYPE_AIN_NTC_90K_3950_3V3:
    case IO_TYPE_AIN_LM35_3V3:
      ioStatus = IO_ST_AIN_OFFLINE;
      pinMode(ioPin, INPUT);
      // analogReadAveraging(16);
      break;
      break;

    case IO_TYPE_DIN_BIN:
    case IO_TYPE_DIN_BIN_R:
    case IO_TYPE_DIN_PWM:
    case IO_TYPE_DIN_PPM:
    case IO_TYPE_DIN_PPM_SC:
    case IO_TYPE_DIN_PWM_REV:
    case IO_TYPE_DIN_PPM_REV:
    case IO_TYPE_DIN_PPM_REV_SC:
      ioStatus = IO_ST_DIN_PWM_NOM;
      pinMode(ioPin, INPUT);
      break;

    case IO_TYPE_DIO_NOM:
      ioStatus = IO_ST_DIO_NOM;
      pinMode(ioPin, INPUT);
      break;

    case IO_TYPE_DOUT_PWM:
    case IO_TYPE_DOUT_PWM_INV:
      ioStatus = IO_ST_DOUT_PWM_NOM;
      pinMode(ioPin, OUTPUT);
      break;


    case IO_TYPE_DOUT_SERVO_180:
    case IO_TYPE_DOUT_SERVO_CONT:
    case IO_TYPE_DOUT_SERVO_CONT_REV:
      ioServo = new Servo;
      ioServo->attach(ioPin);
      break;

  }
}


//-----------------------------------------------------------------------------
void ioChannel::procInChan() {
  ioStatus = IO_ST_DEF;
  ioErr = IO_ERR_AIN_NOM;

  switch (ioType) {
    default:
    case IO_TYPE_UNCONFIG:
      break;

    case IO_TYPE_AIN_NORM:
    case IO_TYPE_AIN_RAW:
    case IO_TYPE_AIN_3V3_255:
    case IO_TYPE_AIN_3V3_1800:
    case IO_TYPE_AIN_3V3_3V3:
    case IO_TYPE_AIN_5V_3V3:
    case IO_TYPE_AIN_10V_3V3:
    case IO_TYPE_AIN_12V_3V3:
    case IO_TYPE_AIN_15V_3V3:
    case IO_TYPE_AIN_31V_3V3:
    case IO_TYPE_AIN_LM35_3V3:
    case IO_TYPE_AIN_INTERP:
    case IO_TYPE_AIN_INTERP_USER:
    case IO_TYPE_AIN_INTERP_OAT_C:
    case IO_TYPE_AIN_INTERP_COOLANT_C:
    case IO_TYPE_AIN_INTERP_OAT_F:
    case IO_TYPE_AIN_INTERP_COOLANT_F:
    case IO_TYPE_AIN_THERM_3V3:
    case IO_TYPE_AIN_THERM_STIEN_3V3:
    case IO_TYPE_AIN_NTC_90K_3950_3V3:

      procAinChan();
      break;

    case IO_TYPE_DIN_BIN:
    case IO_TYPE_DIN_BIN_R:
    case IO_TYPE_DIN_PWM:
    case IO_TYPE_DIN_PWM_REV:
    case IO_TYPE_DIN_PPM:
    case IO_TYPE_DIN_PPM_REV:
    case IO_TYPE_DIN_PPM_SC:
    case IO_TYPE_DIN_PPM_REV_SC:
      procPwmInChan();
      break;

    case IO_TYPE_DIO_NOM:
      break;
  }

}


//-----------------------------------------------------------------------------
void ioChannel::procPwmInChan() {
  static unsigned long tempVal = 0;
  ioStatus = IO_ST_DIN_OFFLINE;

  switch(ioType) {
    default:
    case IO_TYPE_DIN_BIN:
    case IO_TYPE_DIN_BIN_R:
      ioRawVal = digitalRead(ioPin);
      ioStatus = IO_ST_DIN_NOM;
      if (ioInvert == 1) {
        ioEngVal = !ioRawVal;
        ioStatus = IO_ST_DIN;
      }
      else {
        ioEngVal = ioRawVal;
        ioStatus = IO_ST_DIN_R;
      }

      break;

    case IO_TYPE_DIN_PPM:
    case IO_TYPE_DIN_PPM_REV:
      ioStatus = IO_ST_DIN_PPM_NOM;
      ioStatus = IO_ST_DIN_PPM_NOM_REV;

    case IO_TYPE_DIN_PWM:
    case IO_TYPE_DIN_PWM_REV:
      ioStatus = IO_ST_DIN_PWM_NOM;
      tempVal = pulseIn(ioPin, HIGH, PULSE_IN_TIMEOUT);

      ioRawVal = tempVal;
      ioEngVal = ioRawVal;
      if (ioInvert) {
        ioEngVal = RX_IN_MIN + (RX_IN_MAX - ioEngVal);
        ioStatus = IO_ST_DIN_PWM_NOM_REV;
      }

      break;

    case IO_TYPE_DIN_PPM_SC:
    case IO_TYPE_DIN_PPM_REV_SC:
      ioStatus = IO_ST_DIN_SVO_OFFLINE;
      //---Get raw pulsewidth in uSeconds
      tempVal = pulseIn(ioPin, HIGH);

      //---Save raw value
      ioRawVal = tempVal;

      //---normalize to 0-100)
      ioEngVal = ((float)tempVal - RX_IN_MIN) / RX_IN_RANGE * 100;

      //ioEngVal = ioEngVal * (SERVO_POS_RANGE / 10);
      //ioEngVal /= 1000;
      ioStatus = IO_ST_DIN_SVO_NOM;

      break;

  }

  //---filter eng val----
  if (ioInvert) {
    ioEngVal = RX_IN_MIN + (RX_IN_MAX - ioEngVal);

    if (ioEngVal > ioCalEngMin)
      ioCalEngMin = ioEngVal;

    if (ioEngVal < ioCalEngMax)
      ioCalEngMax = ioEngVal;
  }
  else {

    if (ioEngVal > ioCalEngMax)
      ioCalEngMin = ioEngVal;

    if (ioEngVal < ioCalEngMin)
      ioCalEngMax = ioEngVal;
  }


  /* copy engineering value to final consumer */
  if(ioExtVarPtr != NULL)
    *ioExtVarPtr = (int)ioEngVal;
  else
    ioStatus = IO_ST_CFG_ERR;
}


//-----------------------------------------------------------------------------
float ioChannel::filterAin(float ainIn) {
  static float ainShadow = 0;
  static float ainOut = 0;

  switch(ioFilter) {
    default:
    case IO_FILT_NONE:
    case IO_FILT_MOVING_AVG:
      ainOut = ainIn;
      break;
    case IO_FILT_WEIGHTED_AVG:
      ainOut = ((ainIn * S1_WEIGHT) + (ainShadow * S2_WEIGHT))/(WEIGHT_TOTAL *2);
      break;
  }


  ainShadow = ainIn;
  return ainOut;
}


//-----------------------------------------------------------------------------
void ioChannel::procAinChan() {

  /* Grab the raw value */
  ioRawVal = analogRead(ioPin);

  ioRawValRem = MAX_AIN - ioRawVal;

  ioStatus = IO_ST_AIN_OFFLINE;
  switch(ioType) {
    default:
    case IO_TYPE_AIN_RAW:
      ioEngVal = ioRawVal;
      ioStatus = IO_ST_AIN_RAW;
      break;

    case IO_TYPE_AIN_3V3_255:
    case IO_TYPE_AIN_3V3_1800:
      ioStatus = IO_ST_AIN_3V3;
      /* if the gain is non-zero, covert from raw units to eng units */
      if(ioGain > 0) {
        /* Gain is stored at gain * 100 */

        ioEngVal = (float)(ioRawVal/MAX_AIN) * ioGain;
        ioEngVal += ioOffset;
      }
      /* Otherwise, just assign raw units to engineering units */
      // else
      //   // ioEngVal = filterAin(ioRawVal);
      break;

    case IO_TYPE_AIN_NORM:
    case IO_TYPE_AIN_3V3_3V3:
    case IO_TYPE_AIN_5V_3V3:
    case IO_TYPE_AIN_10V_3V3:
    case IO_TYPE_AIN_12V_3V3:
    case IO_TYPE_AIN_15V_3V3:
    case IO_TYPE_AIN_31V_3V3:
    case IO_TYPE_AIN_LM35_3V3:
      ioStatus = IO_ST_AIN_RAW;
      /* if the gain is non-zero, covert from raw units to eng units */
      if(ioGain != 0)
        ioEngVal = (ioRawVal * ioGain) + ioOffset;
      else
        ioEngVal = filterAin(ioRawVal);
      break;

    case IO_TYPE_AIN_THERM_STIEN_3V3:
      //Assumes thermistor is wired from analog ground to ain w/ resistor to 3.3 analog reference
      ioStatus = IO_ST_AIN_STEIN;
      ioEngVal = (ioRawVal * STEIN_GAIN) + STEIN_OFFSET;

      // thermIn01 = (1023/thermIn00) - 1;
      // thermIn02 = 10000 / thermIn01;
      // ioEngVal = thermIn02;

      // thermIn03 = log(thermIn02);
      // thermIn04 = thermIn03 / 3950.0;

      // thermIn05 =thermIn04 + (1.0 /(ROOM_TEMP_C + TRIM_C + C_TO_KELVIIN ));
      // thermIn06 = 1.0 / thermIn05;
      // ioEngVal = thermIn06;
      // // ioEngVal = thermIn06 - (C_TO_KELVIIN);
      ioEngValFilt = filterAin(ioEngVal);

      break;


    case IO_TYPE_AIN_THERM_3V3:
    case IO_TYPE_AIN_NTC_90K_3950_3V3:
      ioStatus = IO_ST_AIN_THERM;
      /* if the gain is non-zero, covert from raw units to eng units */
      if (ioGain != 0) {
        /* Gain is stored at gain * 100 */
        ioEngVal = (ioRawVal * ioGain) + ioOffset;
      }
      /* Otherwise, just assign raw units to engineering units */
      else
        ioEngVal = filterAin(ioRawVal);
      break;

    case IO_TYPE_AIN_INTERP_USER:
    case IO_TYPE_AIN_INTERP_OAT_C:
    case IO_TYPE_AIN_INTERP_COOLANT_C:
    case IO_TYPE_AIN_INTERP_OAT_F:
    case IO_TYPE_AIN_INTERP_COOLANT_F:
      ioStatus = IO_ST_DEF;

      break;
  }

  /* copy engineering value to final consumer */
  if(ioExtVarPtr != NULL)
    *ioExtVarPtr = ioEngVal;

  if(ioExtVarPtrFlt != NULL)
    *ioExtVarPtrFlt = ioEngVal;

  /* Handle alarm level detection */
  // alarmsAIN();
}

//-----------------------------------------------------------------------------
void ioChannel::procIOChan() {
}




//-----------------------------------------------------------------------------
void ioChannel::procDoutChanPWM() {
  ioRawVal = *ioExtVarPtr;

  //---Set the ioChan status---
  ioErr = IO_ERR_DOUT_PWM_A;


  //---Invert the output---0
  if(ioInvert == 1) {
    ioEngVal = (int)((PWM_ENG_MAX - ioRawVal));
    ioErr = IO_ERR_DOUT_PWM_B;
  }
  //---Not inverted output---
  else {
    // ioEngVal = ioRawVal;
    ioEngVal = (int)(ioRawVal);
    ioErr = IO_ERR_DOUT_PWM_C;
  }

  if(ioEngVal > PWM_8_MAX)
    ioEngVal = PWM_8_MAX;
  else if(ioEngVal < 0)
    ioEngVal = 1;

  //---Set the actual output---
  analogWrite(ioPin, ioEngVal);
};


//-----------------------------------------------------------------------------
void ioChannel::procServoOutChan() {

  ioErr = IO_ST_DOUT_SERVO_OFFLINE;
  ioRawVal = *ioExtVarPtr;
  ioEngVal = ioRawVal/10;

  // Clip position to 0 to 180deg for standard servo
  if(ioType == IO_TYPE_DOUT_SERVO_180) {

    ioStatus = IO_ST_DOUT_SERVO_180_OFFLINE;
    if(ioEngVal > SERVO_POS_MAX) {
      ioStatus = IO_ST_DOUT_SERVO_180_MAX;
      ioEngVal = SERVO_POS_MAX;
    }
    else if(ioEngVal < SERVO_POS_MIN) {
      ioStatus = IO_ST_DOUT_SERVO_180_MIN;
      ioEngVal = SERVO_POS_MIN;

    }
    else
      ioStatus = IO_ST_DOUT_SERVO_180_NOM;


  }
  //--- For continuous servo, position = speed: Clip to 0 to 180
  else if(ioType == IO_TYPE_DOUT_SERVO_CONT) {
    //---For continuous forward, input is -90 to 90 and rescaled to 0 to 180
    ioEngVal = ioEngVal + 90;

    ioStatus = IO_ST_DOUT_SERVO_CONT_OFFLINE;
    if(ioEngVal > SERVO_SPD_FWD_MAX) {
      ioStatus = IO_ST_DOUT_SERVO_CONT_FWD_MAX;
      ioEngVal = SERVO_SPD_FWD_MAX;
    }
    else if(ioEngVal < SERVO_SPD_REV_MAX) {
      ioStatus = IO_ST_DOUT_SERVO_CONT_REV_MAX;
      ioEngVal = SERVO_SPD_REV_MAX;
    }
    else
      ioStatus = IO_ST_DOUT_SERVO_CONT_NOM;

  }
  else if(ioType == IO_TYPE_DOUT_SERVO_CONT_REV) {
    //---For continuous reverse, input is -90 to 90 and rescaled to 180 to 0
    ioEngVal = ioEngVal + 90;

    ioEngVal = 180 - ioEngVal;

    ioStatus = IO_ST_DOUT_SERVO_CONT_OFFLINE;
    if(ioEngVal > SERVO_SPD_FWD_MAX) {
      ioStatus = IO_ST_DOUT_SERVO_CONT_FWD_MAX;
      ioEngVal = SERVO_SPD_FWD_MAX;
    }
    else if(ioEngVal < SERVO_SPD_REV_MAX) {
      ioStatus = IO_ST_DOUT_SERVO_CONT_REV_MAX;
      ioEngVal = SERVO_SPD_REV_MAX;
    }
    else
      ioStatus = IO_ST_DOUT_SERVO_CONT_NOM;

  }
  else {
    ioStatus = IO_ST_DOUT_SERVO_OFFLINE;
    return;
  }


  if(ioEngVal > SERVO_CMD_MAX)
    ioEngVal = SERVO_CMD_MAX;

  if(ioEngVal < SERVO_CMD_MIN)
    ioEngVal = SERVO_CMD_MIN;

  ioServo->write(ioEngVal);
}


//-----------------------------------------------------------------------------
void ioChannel::procOutChan() {
  ioStatus = IO_ST_DEF;
  ioErr = IO_ERR_AIN_NOM;
  switch (ioType) {
    default:
    case IO_TYPE_AIN_NORM:
    case IO_TYPE_AIN_RAW:
    case IO_TYPE_AIN_INTERP:
      break;

    case IO_TYPE_DIN_PWM:
    case IO_TYPE_DIO_NOM:
      break;


    case IO_TYPE_DOUT_PWM:
    case IO_TYPE_DOUT_PWM_INV:
      ioStatus = IO_ST_DOUT_PWM_NOM;
      procDoutChanPWM();
      break;

    case IO_TYPE_DOUT_SERVO_180:
    case IO_TYPE_DOUT_SERVO_CONT:
      procServoOutChan();
      break;
  }

}


//-----------------------------------------------------------------------------
void ioChannel::alarmsAIN() {
  //---High Red Level---
  if(ioEngVal > ioHiRed)
    ioAccumHR++;
  else
    ioAccumHR--;

  //---High Yellow Level---
  if(ioEngVal > ioHiYel)
    ioAccumHY++;
  else
    ioAccumHY--;

  //---Low Red Level---
  if(ioEngVal < ioLowRed)
    ioAccumLR++;
  else
    ioAccumLR--;

  //---Low Yellow Level---
  if(ioEngVal < ioLowYel)
    ioAccumLY++;
  else
    ioAccumLY--;


  //---Set the alarm state to nominal and let the alarm accumulators
  //---override it---
  ioStatus = IO_ST_AIN_NOMINAL;


  //---If the HY accumulator is saturated, set the HY alarm state---
  if(ioAccumHY > ACCUM_HY_MAX) {
    ioAccumHY = ACCUM_HY_MAX;
    ioStatus = IO_ST_AIN_HI_YEL;
  }
  else if(ioAccumHY < 0)
    ioAccumHY = 0;

  //---If the HR accumulator is saturated, set the HR alarm state---
  if(ioAccumHR > ACCUM_HR_MAX) {
    ioAccumHR = ACCUM_HR_MAX;
    ioStatus = IO_ST_AIN_HI_RED;
  }
  else if(ioAccumHR < 0)
    ioAccumHR = 0;

  //---If the LY accumulator is saturated, set the LY alarm state---
  if(ioAccumLY > ACCUM_LY_MAX) {
    ioAccumLY = ACCUM_LY_MAX;
    ioStatus = IO_ST_AIN_LOW_YEL;
  }
  else if(ioAccumLY < 0)
    ioAccumLY = 0;

//---If the LR accumulator is saturated, set the LR alarm state---
  if(ioAccumLR > ACCUM_LR_MAX) {
    ioAccumLR = ACCUM_LR_MAX;
    ioStatus = IO_ST_AIN_LOW_RED;
  }
  else if(ioAccumLR < 0)
    ioAccumLR = 0;

}




//-----------------------------------------------------------------------------
int ioChannel::getChanStat() {
  return ioStatus;
}


//-----------------------------------------------------------------------------
float ioChannel::getEngVal() {
  return ioEngVal;
}


//-----------------------------------------------------------------------------
int ioChannel::getRawVal() {
  return ioRawVal;
}

String ioChannel::getDispStr() {
  ioOutString = String(ioEngVal);
  return ioOutString;
}

