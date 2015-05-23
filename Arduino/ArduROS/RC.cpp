#include <Arduino.h>
#include "RC.h"

int CH_MAX[3]= {2000,2000,2000};
int CH_MIN[3]= {1000,1000,1000};

int intPin[3] = {0,1,4};

int time[3],pos[3];

void rf0();
void rf1();
void rf2();

void ff0();
void ff1();
void ff2();

void (*rf_handle[3])(void) = {rf0,rf1,rf2};
void (*ff_handle[3])() = {ff0,ff1,ff2};

void rf(int i)
{
  time[i] = micros();
  attachInterrupt(intPin[i], ff_handle[i], FALLING);

}
void  ff(int i)
{
  pos[i] = micros()-time[i];
  attachInterrupt(intPin[i], rf_handle[i], RISING);
}

void rf0(){rf(0);}
void rf1(){rf(1);}
void rf2(){rf(2);}

void ff0(){ff(0);}
void ff1(){ff(1);}
void ff2(){ff(2);}


void initRC()
{
  rf0();
  rf1();
  rf2();
}

float getChannel(int i)
{
  return ((float)pos[i]- CH_MIN[i])/(CH_MAX[i] - CH_MIN[i]);
}


