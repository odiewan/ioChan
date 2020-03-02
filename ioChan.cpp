#include <ioChan.h>

/*-----------------------------------------------------------------------------
 *
 *
 *
 *---------------------------------------------------------------------------*/
ioChannel::ioChannel() {

  ioOutString = "ioOutString";
  ioErr = IO_ERR_NONE;

  ioType = IO_TYPE_UNCONFIG;
  ioUnits = IOUNIT_NA;
  ioFilter = IO_FILT_NONE;
  ioPin = 0;
  ioStatus = IO_ST_DEF;
  ioGain = 0;
  ioOffset = 0;

  ioRawVal = 0;
  ioRawValRem = 0;

  ioEngVal = 0;
  ioMinEngVal = 0;
  ioMaxEngVal = 0;
  ioEngValOn = 0;
  ioEngValOff = 0;
  ioCalEngMax = 0;
  ioCalEngMin = 0;

  ioExtVar = NULL;
  ioServo = NULL;

  ioFixedPoints = 0;
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
};

/*-----------------------------------------------------------------------------
 *
 *
 *
 *---------------------------------------------------------------------------*/
ioChannel::ioChannel(ioChanTypeEnum nType, char nPin, long* eVal) {
  ioType = nType;
  ioUnits = IOUNIT_NA;
  ioFilter = IO_FILT_NONE;
  ioPin = nPin;
  ioExtVar = eVal;

  ioFixedPoints = 2;

  ioRawVal = 0;
  ioRawValRem = 0;
  ioRawPWM = 0;

  ioEngVal = 0;

  ioDutyCycleIn = 0;
  ioDutyCycleOut = 0;

  ioAccumLR = 0;
  ioAccumHR = 0;
  ioAccumLY = 0;
  ioAccumHY = 0;

  ioMinEngVal = 0;
  ioMaxEngVal = MAX_AIN;
  ioEngValOn = 0;
  ioEngValOff = 0;
  ioGain = 0;
  ioOffset = 0;
  ioLowRed = ioMinEngVal;
  ioLowYel = ioMinEngVal;
  ioHiYel = ioMaxEngVal;
  ioHiRed = ioMaxEngVal;
  ioInVal = NULL;
  ioOutVal = NULL;

  ioIntpTemp = 0;

  ioInvert = 0;

  switch (ioType) {
    default:
      break;

    case IO_TYPE_AIN_3V3_1800:
      ioUnits = IOUNIT_NA;
      ioFixedPoints = 0;
      ioGain = 176;    //<--Gain * 10,000
      ioOffset = 0;   //<--Offset * 10,000
      ioMinEngVal = ioOffset;
      ioMaxEngVal = (MAX_AIN * ioGain) + ioOffset;
      ioMaxEngVal /= (long)(100);
      ioStatus = IO_ST_AIN_OFFLINE;
      ioErr = IO_ERR_AIN_NOM;
      break;

    case IO_TYPE_AIN_3V3_3V3:
      ioUnits = IOUNIT_VOLTS;
      ioFixedPoints = 3;
      ioGain = 29;    //<--Gain * 10,000
      ioOffset = -3;   //<--Offset * 10,000
      ioMinEngVal = ioOffset;
      ioMaxEngVal = (MAX_AIN * ioGain) + ioOffset;
      ioMaxEngVal /= (long)(10 ^ ioFixedPoints);
      ioStatus = IO_ST_AIN_OFFLINE;
      ioErr = IO_ERR_AIN_NOM;
      break;

    case IO_TYPE_AIN_NORM:
    case IO_TYPE_AIN_5V_3V3:
      ioUnits = IOUNIT_VOLTS;
      ioFixedPoints = 3;
      ioGain = 49;    //<--Gain * 10,000
      ioOffset = 0;   //<--Offset * 10,000
      ioMinEngVal = ioOffset;
      ioMaxEngVal = (MAX_AIN * ioGain) + ioOffset;
      ioMaxEngVal /= (long)(10 ^ ioFixedPoints);
      ioStatus = IO_ST_AIN_OFFLINE;
      ioErr = IO_ERR_AIN_NOM;
      break;

    case IO_TYPE_AIN_10V_3V3:
      ioUnits = IOUNIT_VOLTS;
      ioFixedPoints = 3;
      ioGain = 98;   //<--Gain * 10,000
      ioOffset = 0;   //<--Offset * 10,000
      ioMinEngVal = ioOffset;
      ioMaxEngVal = (MAX_AIN * ioGain) + ioOffset;
      ioMaxEngVal /= (long)(10 ^ ioFixedPoints);
      ioStatus = IO_ST_AIN_OFFLINE;
      ioErr = IO_ERR_AIN_NOM;
      break;

    case IO_TYPE_AIN_12V_3V3:
      ioUnits = IOUNIT_VOLTS;
      ioFixedPoints = 3;
      ioGain = 117;   //<--Gain * 10,000
      ioOffset = 0;   //<--Offset * 10,000
      ioMinEngVal = ioOffset;
      ioMaxEngVal = (MAX_AIN * ioGain) + ioOffset;
      ioMaxEngVal /= (long)(10 ^ ioFixedPoints);
      ioStatus = IO_ST_AIN_OFFLINE;
      ioErr = IO_ERR_AIN_NOM;
      break;

      //----Top R = 20kOhm, Bottom R = 5k scaled to a 0-3v range
    case IO_TYPE_AIN_15V_3V3:
      ioUnits = IOUNIT_VOLTS;
      ioFixedPoints = 3;
      ioGain = 144;   //<--Gain * 10,000
      ioOffset = 0;   //<--Offset * 10,000
      ioMinEngVal = ioOffset;
      ioMaxEngVal = (MAX_AIN * ioGain) + ioOffset;
      ioMaxEngVal /= (long)(10 ^ ioFixedPoints);
      ioStatus = IO_ST_AIN_OFFLINE;
      ioErr = IO_ERR_AIN_NOM;
      ioLowRed = 10000;       // 10v
      ioLowYel = 11000;       // 11v
      ioHiYel = 14500;        // 14.5v
      ioHiRed = 14900;        // 14.9v

      break;

    //----Top R = 20kOhm, Bottom R = 5k scaled to a 0-5v range
    case IO_TYPE_AIN_15V_5V:
      ioUnits = IOUNIT_VOLTS;
      ioFixedPoints = 3;
      ioGain = 224;   //<--Gain * 10,000
      ioOffset = 0;   //<--Offset * 10,000
      ioMinEngVal = ioOffset;
      ioMaxEngVal = (MAX_AIN * ioGain) + ioOffset;
      ioMaxEngVal /= (long)(10 ^ ioFixedPoints);
      ioStatus = IO_ST_AIN_OFFLINE;
      ioErr = IO_ERR_AIN_NOM;
      ioLowRed = 10000;       // 10v
      ioLowYel = 11000;       // 11v
      ioHiYel = 14500;        // 14.5v
      ioHiRed = 14900;        // 14.9v

      break;


    case IO_TYPE_AIN_31V_3V3:
      ioUnits = IOUNIT_VOLTS;
      ioFixedPoints = 3;
      ioGain = 263;   //<--Gain * 10,000
      ioOffset = 0;   //<--Offset * 10,000
      ioMinEngVal = ioOffset;
      ioMaxEngVal = (MAX_AIN * ioGain) + ioOffset;
      ioMaxEngVal /= (long)(10 ^ ioFixedPoints);
      ioStatus = IO_ST_AIN_OFFLINE;
      ioErr = IO_ERR_AIN_NOM;
      break;

    case IO_TYPE_AIN_NTC_5V:
      ioUnits = IOUNIT_TEMP_C;
      ioFixedPoints = 2;
      ioGain = 95;   //<--Gain * 10,000
      ioOffset =  16000;   //<--Offset * 10,000
      ioMinEngVal = ioOffset;
      ioMaxEngVal = (MAX_AIN * ioGain) + ioOffset;
      ioMaxEngVal /= (long)(10 ^ ioFixedPoints);
      ioStatus = IO_ST_AIN_OFFLINE;
      ioErr = IO_ERR_AIN_NOM;
      break;


    case IO_TYPE_AIN_LM35_3V3:
      ioUnits = IOUNIT_TEMP_C;
      ioFixedPoints = 1;
      ioGain = -300;    //<--Gain * 10,000
      ioOffset = 76800;   //<--Offset * 10,000

      ioMinEngVal = ioOffset;
      ioMaxEngVal = (MAX_AIN * ioGain) + ioOffset;
      ioMaxEngVal /= (long)(10 ^ ioFixedPoints);
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



  genDispStr();
  initChan();
};

/*-----------------------------------------------------------------------------
 *
 *
 *
 *---------------------------------------------------------------------------*/
void ioChannel::initChan() {
  switch (ioType) {
    default:
      break;

    case IO_TYPE_AIN_NORM:
    case IO_TYPE_AIN_RAW:
    case IO_TYPE_AIN_3V3_1800:
    case IO_TYPE_AIN_3V3_3V3:
    case IO_TYPE_AIN_5V_3V3:
    case IO_TYPE_AIN_10V_3V3:
    case IO_TYPE_AIN_12V_3V3:
    case IO_TYPE_AIN_15V_3V3:
    case IO_TYPE_AIN_31V_3V3:
    case IO_TYPE_AIN_3V3_5V:
    case IO_TYPE_AIN_5V_5V:
    case IO_TYPE_AIN_12V_5V:
    case IO_TYPE_AIN_15V_5V:
    case IO_TYPE_AIN_31V_5V:
    case IO_TYPE_AIN_NTC_5V:
    case IO_TYPE_AIN_INTERP_USER:
    case IO_TYPE_AIN_INTERP_OAT_C:
    case IO_TYPE_AIN_INTERP_OAT_F:
    case IO_TYPE_AIN_INTERP_COOLANT_C:

    case IO_TYPE_AIN_INTERP_COOLANT_F:
      ioStatus = IO_ST_AIN_NOMINAL;
      pinMode(ioPin, INPUT);
//      analogReference(DEFAULT);
      break;

    case IO_TYPE_AIN_LM35_3V3:
      ioStatus = IO_ST_AIN_NOMINAL;
      pinMode(ioPin, INPUT);
      analogReference(INTERNAL);
//      analogReadRes(16);
      analogReadAveraging(16);
      break;
      break;

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
};

/*-----------------------------------------------------------------------------
 *
 *
 *
 *---------------------------------------------------------------------------*/
void ioChannel::procInChan(void) {
  ioStatus = IO_ST_DEF;
  ioStatus = IO_ERR_NONE;
  switch (ioType) {
    default:
    case IO_TYPE_UNCONFIG:
      break;

    case IO_TYPE_AIN_NORM:
    case IO_TYPE_AIN_RAW:
    case IO_TYPE_AIN_3V3_1800:
    case IO_TYPE_AIN_3V3_3V3:
    case IO_TYPE_AIN_5V_3V3:
    case IO_TYPE_AIN_10V_3V3:
    case IO_TYPE_AIN_12V_3V3:
    case IO_TYPE_AIN_15V_3V3:
    case IO_TYPE_AIN_31V_3V3:
    case IO_TYPE_AIN_3V3_5V:
    case IO_TYPE_AIN_5V_5V:
    case IO_TYPE_AIN_12V_5V:
    case IO_TYPE_AIN_15V_5V:
    case IO_TYPE_AIN_31V_5V:
    case IO_TYPE_AIN_NTC_5V:
    case IO_TYPE_AIN_LM35_3V3:
    case IO_TYPE_AIN_INTERP:
    case IO_TYPE_AIN_INTERP_USER:
    case IO_TYPE_AIN_INTERP_OAT_C:
    case IO_TYPE_AIN_INTERP_COOLANT_C:
    case IO_TYPE_AIN_INTERP_OAT_F:
    case IO_TYPE_AIN_INTERP_COOLANT_F:
      procAinChan();
      break;

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

};

/*-----------------------------------------------------------------------------
 *
 *
 *
 *---------------------------------------------------------------------------*/
void ioChannel::procPwmInChan(void) {
  long static tempVal = 0;


  tempVal = pulseIn(ioPin, HIGH, PULSE_IN_TIMEOUT);

  if(tempVal > 0) {
    ioRawVal = tempVal;

    if(ioInvert) {
      ioEngVal = RX_IN_MIN + (RX_IN_MAX - ioRawVal);

      if(ioEngVal > ioCalEngMin)
        ioCalEngMin = ioEngVal;

      if(ioEngVal < ioCalEngMax)
        ioCalEngMax = ioEngVal;
    }
    else {
      ioEngVal = ioRawVal;

      if(ioEngVal > ioCalEngMax)
        ioCalEngMin = ioEngVal;

      if(ioEngVal < ioCalEngMin)
        ioCalEngMax = ioEngVal;
    }

    switch(ioType) {
      default:
      case IO_TYPE_DIN_PWM:
      case IO_TYPE_DIN_PPM:
      case IO_TYPE_DIN_PWM_REV:
      case IO_TYPE_DIN_PPM_REV:
        break;

      case IO_TYPE_DIN_PPM_SC:
      case IO_TYPE_DIN_PPM_REV_SC:
        tempVal = (ioEngVal - RX_IN_MIN) * 100;
        tempVal /= RX_IN_RANGE;

        ioEngVal = tempVal * (SERVO_POS_RANGE / 10);
        ioEngVal /= 10;

        break;

    }
  }
  else
    ioEngVal = 0;
//  ioEngVal = ((ioRawVal - DWELL_MIN)/3);

  /* copy engineering value to final consumer */
  if(ioExtVar != NULL)
    *ioExtVar = ioEngVal;
};

/*-----------------------------------------------------------------------------
 *
 *
 *
 *
 *---------------------------------------------------------------------------*/
long ioChannel::filterAin(long ainIn) {
  static long ainShadow = 0;
  static long ainOut = 0;

  switch(ioFilter) {
    default:
    case IO_FILT_NONE:
    case IO_FILT_MOVING_AVG:
      ainOut = ainIn;
      break;
    case IO_FILT_WEIGHTED_AVG:
      ainOut = (ainIn * S1_WEIGHT) + (ainShadow * S2_WEIGHT)/WEIGHT_TOTAL;
      break;
  }


  ainShadow = ainIn;
  return ainOut;
};

/*-----------------------------------------------------------------------------
 *
 *
 *
 *
 *---------------------------------------------------------------------------*/
void ioChannel::procAinChan(void) {
  /* Grab the raw value */
  ioRawVal = analogRead(ioPin);

  ioRawValRem = MAX_AIN - ioRawVal;

  ioStatus = IO_ST_AIN_OFFLINE;
  switch(ioType) {
    default:
    case IO_TYPE_AIN_RAW:
      ioEngVal = (long)ioRawVal;
      ioStatus = IO_ST_AIN_RAW;
      break;

    case IO_TYPE_AIN_3V3_1800:
      ioStatus = IO_ST_AIN_V;
      /* if the gain is non-zero, covert from raw units to eng units */
      if(ioGain != 0) {
        /* Gain is stored at gain * 100 */
        ioEngVal = (long)(ioRawVal * ioGain) + ioOffset;
        ioEngVal /= (long)(100);
      }
      /* Otherwise, just assign raw units to engineering units */
      else
        ioEngVal = filterAin((long)ioRawVal);
//        ioEngVal = (long)ioRawVal;
      break;

    case IO_TYPE_AIN_NORM:
    case IO_TYPE_AIN_3V3_3V3:
    case IO_TYPE_AIN_5V_3V3:
    case IO_TYPE_AIN_10V_3V3:
    case IO_TYPE_AIN_12V_3V3:
    case IO_TYPE_AIN_15V_3V3:
    case IO_TYPE_AIN_31V_3V3:
    case IO_TYPE_AIN_3V3_5V:
    case IO_TYPE_AIN_5V_5V:
    case IO_TYPE_AIN_12V_5V:
    case IO_TYPE_AIN_15V_5V:
    case IO_TYPE_AIN_31V_5V:
      ioStatus = IO_ST_AIN_V;
      /* if the gain is non-zero, covert from raw units to eng units */
      if(ioGain != 0) {
        /* Gain is stored at gain * 100 */
        ioEngVal = (long)(ioRawVal * ioGain) + ioOffset;
        ioEngVal /= (long)(10 ^ ioFixedPoints);
//        ioEngVal = filterAin((long)ioEngVal);
      }
      /* Otherwise, just assign raw units to engineering units */
      else
        ioEngVal = filterAin((long)ioRawVal);
//        ioEngVal = (long)ioRawVal;
      break;

    case IO_TYPE_AIN_LM35_3V3:
      ioStatus = IO_ST_AIN_V;
      /* if the gain is non-zero, covert from raw units to eng units */
      if(ioGain != 0) {
        /* Gain is stored at gain * 100 */
        ioEngVal = ioRawVal * ioGain + ioOffset;
        ioEngVal /= (long)(10 ^ ioFixedPoints);
//        ioEngVal = filterAin((long)ioEngVal);
      }
      /* Otherwise, just assign raw units to engineering units */
      else
        ioEngVal = filterAin((long)ioRawVal);
//        ioEngVal = (long)ioRawVal;
      break;
    case IO_TYPE_AIN_NTC_5V:
      ioStatus = IO_ST_AIN_V;
      /* if the gain is non-zero, covert from raw units to eng units */
      if(ioGain != 0) {
        /* Gain is stored at gain * 100 */
        ioEngVal = (long)(ioRawValRem * ioGain) + ioOffset;
        ioEngVal /= (long)(10 ^ ioFixedPoints);
      }
      /* Otherwise, just assign raw units to engineering units */
      else
        ioEngVal = filterAin((long)ioRawVal);
//        ioEngVal = (long)ioRawVal;
      break;

    case IO_TYPE_AIN_INTERP_USER:
    case IO_TYPE_AIN_INTERP_OAT_C:
    case IO_TYPE_AIN_INTERP_COOLANT_C:
    case IO_TYPE_AIN_INTERP_OAT_F:
    case IO_TYPE_AIN_INTERP_COOLANT_F:
      break;
  }

  /* copy engineering value to final consumer */
  if(ioExtVar != NULL)
    *ioExtVar = ioEngVal;

  /* Handle alarm level detection */
  alarmsAIN();
};

/*-----------------------------------------------------------------------------
 *
 *
 *
 *---------------------------------------------------------------------------*/
void ioChannel::procIOChan(void) {
};



/*-----------------------------------------------------------------------------
 *
 *
 *
 *---------------------------------------------------------------------------*/
void ioChannel::procDoutChanPWM() {
  ioEngVal = *ioExtVar;

  //---Set the ioChan status---
  ioStatus = IO_ERR_DOUT_PWM_A;


  //---Invert the output---0
  if(ioInvert == 1) {
    ioRawVal = (PWM_ENG_MAX - ioEngVal) / (unsigned long)PWM_DC_PER_PWM_ENG;
    ioStatus = IO_ERR_DOUT_PWM_B;
  }
  //---Not inverted output---
  else {
    ioRawVal = ioEngVal / (unsigned long)PWM_DC_PER_PWM_ENG;
    ioStatus = IO_ERR_DOUT_PWM_C;
  }

  if(ioRawVal > PWM_8_MAX)
    ioRawVal = PWM_8_MAX;
  else if(ioRawVal < 0)
    ioRawVal = 1;

  //---Set the actual output---
  analogWrite(ioPin, ioRawVal);
};

/*-----------------------------------------------------------------------------
 *
 *
 *
 *---------------------------------------------------------------------------*/
void ioChannel::procServoOutChan(void) {

  ioStatus = IO_ST_DOUT_SERVO_OFFLINE;
  ioRawVal = *ioExtVar;
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
};

/*-----------------------------------------------------------------------------
 *
 *
 *
 *---------------------------------------------------------------------------*/
void ioChannel::procOutChan(void) {
  ioStatus = IO_ST_DEF;
  ioStatus = IO_ERR_NONE;
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

};

/*-----------------------------------------------------------------------------
 *
 *----------------------------------------------------------------------------*/
void ioChannel::alarmsAIN(void) {
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

};

/*-----------------------------------------------------------------------------
 *
 *----------------------------------------------------------------------------*/
void ioChannel::genDispStr(void) {
  switch(ioType) {
    default:
    case IO_TYPE_UNCONFIG:
      break;

    case IO_TYPE_AIN_NORM:
    case IO_TYPE_AIN_RAW:
    case IO_TYPE_AIN_3V3_3V3:
    case IO_TYPE_AIN_5V_3V3:
    case IO_TYPE_AIN_10V_3V3:
    case IO_TYPE_AIN_12V_3V3:
    case IO_TYPE_AIN_15V_3V3:
    case IO_TYPE_AIN_31V_3V3:
    case IO_TYPE_AIN_3V3_5V:
    case IO_TYPE_AIN_5V_5V:
    case IO_TYPE_AIN_12V_5V:
    case IO_TYPE_AIN_15V_5V:
    case IO_TYPE_AIN_31V_5V:
    case IO_TYPE_AIN_NTC_5V:
    case IO_TYPE_AIN_LM35_3V3:
    case IO_TYPE_AIN_INTERP:
    case IO_TYPE_AIN_INTERP_USER:
    case IO_TYPE_AIN_INTERP_OAT_C:
    case IO_TYPE_AIN_INTERP_COOLANT_C:
    case IO_TYPE_AIN_INTERP_OAT_F:
    case IO_TYPE_AIN_INTERP_COOLANT_F:
      genDispAINStr();
      break;

    case IO_TYPE_AIN_3V3_1800:
    case IO_TYPE_DOUT_SERVO_180:
    case IO_TYPE_DOUT_SERVO_CONT:
      genDispSvoStr();
      break;

  }
};

/*-----------------------------------------------------------------------------
 *
 *----------------------------------------------------------------------------*/
void ioChannel::genDispSvoStr(void) {
  static String tempOutStr;

  tempOutStr = String(ioEngVal);
//  tempOutStr = String(ioEngVal) + ":" + String(ioStatus);

  ioOutString = tempOutStr;
};

/*-----------------------------------------------------------------------------
 *
 *----------------------------------------------------------------------------*/
void ioChannel::genDispAINStr(void) {
  char padLen = 0;
  unsigned int strLen = 0;
  unsigned int idx = 0;
  unsigned long tempVal = 0;
  String engVarStr = "";
  String negStr = "";
  String zeroPad = "";
  String LHStr = "0";
  String RHStr = "";
  String UnitStr = "";
  String tmpStr3 = "";

  tempVal = abs(ioEngVal);
  engVarStr = String(tempVal);
  strLen = engVarStr.length();
  //---Output string format: LHStr.RHStr---
  //---Three cases:
  //    Eng var has less digits than ioFixedPoints:
  //      * pad RHStr to equal ioFixedPoints
  //      * LHStr equals "0"

  if(ioEngVal < 0)
    negStr = "-";

  if(strLen < ioFixedPoints) {
    padLen = ioFixedPoints - strLen;

    for(char i = 0; i < padLen; i++)
      zeroPad += "0";

    RHStr = zeroPad + engVarStr;
    LHStr = "0";
  }
  //    Eng var has equal digits than ioFixedPoints---
  //      * RHStr = engVal
  //      * LHStr equals "0"
  else if(strLen == ioFixedPoints) {
    RHStr = engVarStr;
    LHStr = "0";
  }
  //    Eng var has more digits than ioFixedPoints---
  //      * RHStr equals ioFixedPoints number of chars from the right of EngVal
  //      * LHStr equals everything to the left of RHStr
  else {
    idx = strLen - ioFixedPoints;
    RHStr = engVarStr.substring(idx);
    LHStr = engVarStr.substring(0, idx);
  }

  switch(ioUnits) {
    case IOUNIT_NA:
    default:
      break;

    case IOUNIT_VOLTS:
      UnitStr = " V";
      break;

    case IOUNIT_AMPS:
      UnitStr = " A";
      break;

    case IOUNIT_TEMP_F:
      UnitStr = " F";
      break;

    case IOUNIT_TEMP_C:
      UnitStr = " C";
      break;

    case IOUNIT_TEMP_HZ:
      UnitStr = " Hz";
      break;

    case IOUNIT_TEMP_PERCENT:
      UnitStr = " %";
      break;

    case IOUNIT_TEMP_TIME:
      UnitStr = " S";
      break;
  }

  ioOutString = negStr + LHStr + "." + RHStr + UnitStr;
};


/*-----------------------------------------------------------------------------
 *
 *----------------------------------------------------------------------------*/
String ioChannel::getDispStr(void) {
  genDispStr();
  return ioOutString;
};

/*-----------------------------------------------------------------------------
 *
 *
 *
 *---------------------------------------------------------------------------*/
char ioChannel::getChanStat(void) {
  return ioStatus;
};

/*-----------------------------------------------------------------------------
 *
 *
 *
 *---------------------------------------------------------------------------*/
long ioChannel::getEngVal(void) {
  return ioEngVal;
};

/*-----------------------------------------------------------------------------
 *
 *
 *
 *---------------------------------------------------------------------------*/
long ioChannel::getRawVal(void) {
  return ioRawVal;
};
