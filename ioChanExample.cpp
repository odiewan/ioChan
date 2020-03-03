#include <ioChan.h>
#include <Wire.h>
#include <Arduino.h>
#include <Servo.h>


#define STAT_OUT_PIN      LED_BUILTIN /* 13 */
#define OAT_IN_PIN       A9
#define SVO_OUT_PIN     10
#define BTN_MD_PIN      2
#define BTN_L_PIN       8
#define BTN_R_PIN       12

long OATVar;
long svoPanVar;

ioChannel OATChan;
ioChannel svoPanChan;

//-----------------------------------------------------------------
//
//-----------------------------------------------------------------
void setup() {
  int i = 30;
  int serialOk = 0;


  Serial.begin(115200);

  while(i > 0 && serialOk == 0) {
    i--;
    if(Serial)
      serialOk = 1;
    delay(250);
  }

  Serial.println("Serial Ready");


  OATChan = ioChannel(IO_TYPE_AIN_LM35_3V3, OAT_IN_PIN, &OATVar);
  svoPanChan = ioChannel(IO_TYPE_DOUT_SERVO_180, SVO_OUT_PIN, &svoPanVar);

  svoPanChan.initChan();
}


//-----------------------------------------------------------------
//
//-----------------------------------------------------------------
void loop() {

  OATChan.procInChan();

  Serial.print("OAT:");
  Serial.print(OATVar);

  svoPanChan.procOutChan();

  delay(100);
}