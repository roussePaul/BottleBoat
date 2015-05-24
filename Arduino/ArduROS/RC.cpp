#include <Arduino.h>
#include "RC.h"


int rc_CH_MAX[3]= {2000,2000,2000};
int rc_CH_MIN[3]= {1000,1000,1000};
int CH_SWITCH[3]= {200,200,200};

int intPin[3] = {0,1,4};

unsigned long rc_time[3],rc_hold[3];
int rc_pos[3];
int rc_dig[3];

void rf0();
void rf1();
void rf2();

void ff0();
void ff1();
void ff2();

void (*rf_handle[3])(void) = {rf0,rf1,rf2};
void (*ff_handle[3])() = {ff0,ff1,ff2};

int getDigital(int p,int i)
{
  if(p<rc_CH_MIN[i]+CH_SWITCH[i])
    return 0;
  if(p>rc_CH_MAX[i]-CH_SWITCH[i])
    return 1;
    
    return -1;
}

void rf(int i)
{
  rc_time[i] = micros();
  attachInterrupt(intPin[i], ff_handle[i], FALLING);

}
void  ff(int i)
{
  int lastdig = rc_dig[i];
  rc_pos[i] = micros()-rc_time[i];
  rc_dig[i] = getDigital(rc_pos[i],i);
  
  if(lastdig!=rc_dig[i])
    rc_hold[i] = micros();
    
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
  
  rc_hold[0] = micros();
  rc_hold[1] = micros();
  rc_hold[2] = micros();
}

float getChannel(int i)
{
  return ((float)rc_pos[i]- rc_CH_MIN[i])/(rc_CH_MAX[i] - rc_CH_MIN[i]);
}

boolean isChannelHigh(int i)
{
  return  rc_dig[i]==1 && (micros()-rc_hold[i])>1000000;
}
boolean isChannelLow(int i)
{
  return  rc_dig[i]==0 && (micros()-rc_hold[i])>1000000;
}


