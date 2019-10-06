//Release Date: 06-10-2019
//svy123@gmail.com

/*===========================================================================
DAC7611 device library code is placed under the MIT License
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

#ifndef DAC_H
#define DAC_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

class DAC7612 {
  public:
    DAC7612(int N_CS = 2, int CLK = 3, int SDI = 4, int N_LOADDACSD = 5);

    void sendDAC(int value, int type);
    void sendZero2DAC(int type);
    void begin(void);
    void clr(void);

  private:

    void advance_bit(int dataBit);
    void SSR(void);
    void formatData(int value);
    int sdata[14];
    int _N_CS;
    int _CLK;
    int _SDI;
    int _N_LOADDACS;
};

#endif
