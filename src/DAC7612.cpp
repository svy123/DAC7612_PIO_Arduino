//Release Date: 06-10-2019
//svy123@gmail.com

/*===========================================================================
DAC7612 device library code is placed under the MIT license
Copyright (c) 2019 svy123

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
===========================================================================*/

#include "DAC7612.h"
#include "Arduino.h"

DAC7612::DAC7612(int N_CS, int CLK, int SDI, int N_LOADDACS){
  _N_CS = N_CS;
  _CLK = CLK;
  _SDI = SDI;
  _N_LOADDACS = N_LOADDACS;
}

void DAC7612::begin(void)
{
  pinMode(_N_CS, OUTPUT);
  pinMode(_CLK, OUTPUT);
  pinMode(_SDI, OUTPUT);
  pinMode(_N_LOADDACS, OUTPUT);

  digitalWrite(_N_CS, HIGH);
  digitalWrite(_CLK, HIGH);
  digitalWrite(_N_LOADDACS, LOW);
  digitalWrite(_SDI, LOW);
}

void DAC7612::sendDAC(int value, int type)
{
  value = constrain(value, 0, 4095);
  type = constrain(type, 0, 2);

  switch (type) {
  case 0:
    sdata[0] = 1;
    sdata[1] = 0;
    break;
  case 1:
    sdata[0] = 1;
    sdata[1] = 1;
    break;
  case 2:
    sdata[0] = 0;
    sdata[1] = 0;
    break;
  default:
    sdata[0] = 0;
    sdata[1] = 0;
    break;
  }

  formatData(value);
  digitalWrite(_N_LOADDACS, HIGH);
  delayMicroseconds(1);
  digitalWrite(_N_CS, LOW);
  delayMicroseconds(1);
  advance_bit(sdata[0]);
  advance_bit(sdata[1]);
  for(int i=13;i>=2;i--)
  {
   advance_bit(sdata[i]);
  }
  Serial.println();
  SSR();
  clr();
}

void DAC7612::sendZero2DAC(int type)
{
  type = constrain(type, 0, 2);

  switch (type) {
  case 0:
    sdata[0] = 1;
    sdata[1] = 0;
    break;
  case 1:
    sdata[0] = 1;
    sdata[1] = 1;
    break;
  case 2:
    sdata[0] = 0;
    sdata[1] = 0;
    break;
  default:
    sdata[0] = 0;
    sdata[1] = 0;
    break;
  }

  digitalWrite(_N_LOADDACS, HIGH);
  delayMicroseconds(1);
  digitalWrite(_N_CS, LOW);
  delayMicroseconds(1);
  advance_bit(sdata[0]);
  advance_bit(sdata[1]);
  for(int i=13;i>=2;i--)
  {
   advance_bit(0);
  }
  Serial.println();
  SSR();
  clr();
}

void DAC7612::advance_bit(int dataBit)
{
    digitalWrite(_CLK, LOW);
    digitalWrite(_SDI, dataBit);
    digitalWrite(_CLK, HIGH);
    delayMicroseconds(1);
}

void DAC7612::SSR(void)
{
    digitalWrite(_N_CS, HIGH);
    delayMicroseconds(1);
    digitalWrite(_N_LOADDACS, LOW);
    delayMicroseconds(1);
    digitalWrite(_N_LOADDACS, HIGH);
}

void DAC7612::formatData(int value)
{
      int i = 0;
      int tmp = value;
      while(tmp != 0)
      {
        sdata[i+2] = tmp%2;
        tmp/=2;
        i++;
      }
}

void DAC7612::clr(void)
{
    for (int i = 0; i < 14; i++)
    {
      sdata[i] = 0;
    }
}
