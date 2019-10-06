#include <Arduino.h>
#include <DAC7612.h>

DAC7612 dac(2,3,4,5);  //N_CS - 2, CLK - 3, SDI - 4, N_LOADDACS - 5
int dacVal = 0;
int i = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dac.begin();	//initialise DAC
  dac.sendZero2DAC(2);  //reset DAC to 0
  Serial.println("DAC init succesfull");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0)
  {
    dacVal = Serial.parseInt();
    if (dacVal > 4095) {
      dacVal = 4095;
    }
    else if (dacVal < 0) {
      dacVal = 0;
    }
    dac.sendDAC(dacVal, i);	//send values to DACi
    Serial.print("DAC Value for ");
    Serial.print(i);
    Serial.print(" is : ");
    Serial.println(dacVal);
    delay(3000);
    i++;
    if (i > 2) {
      i = 0;
    }
  }
}
