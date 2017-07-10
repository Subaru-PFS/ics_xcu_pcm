#ifndef _pcm_portcontrol
#define _pcm_portcontrol
#include <PCM_MACProm.h>
#include <stddef.h>
#define vNormal   'N'
#define vBattery  'B'
#define vLow      'L'
#define hysteresis 0.25

#define LVth   eeRAMcopy.eeData.LVThreshold
#define OBth   eeRAMcopy.eeData.onBattThreshold
#define LVth2  eeRAMcopy.eeData.ch2Threshold
#define LVMask eeRAMcopy.eeData.LVmask
#define PUMask eeRAMcopy.eeData.PUmask


unsigned int8 IOCtrl;
char voltageStatus = vNormal; // Battery backed up voltage
char voltageStatus2 = vNormal; //Aux bus

void portControlInit()
{
   IOCtrl=PUMask;
}

void setLowVoltageFlags()
{
   float voltage = readAnalogValues(VIEvoltage,0);  
   switch (voltageStatus)
   {
   case vLow:
      if (voltage >= LVth + hysteresis)
      {
         voltageStatus = vBattery;
      }
      if (voltage >= OBth + hysteresis)
      {
         voltageStatus = vNormal;
      }
      break;
   case vBattery:
      if (voltage < LVth)
      {
         voltageStatus = vLow;
      }
      else if (voltage >= OBth + hysteresis)
      {
         voltageStatus = vNormal;
      }
      break;
   default:
      if (voltage < OBth)
      {
         voltageStatus = vBattery;
      }
      if (voltage < LVth)
      {
         voltageStatus = vLow;
      }
      break;
   }
   
   voltage = readAnalogValues(VIEvoltage,1);    
   if (voltage >= LVth2 + hysteresis)
   {
      voltageStatus2 = vNormal;
   }
   else if (voltage < LVth2)
   {
      voltageStatus2 = vLow;
   }

}

void getIOStatus(char* result)
{
   strcpy(result,"NN00000000"); // get the status of the power ports
   result[0]=voltageStatus;
   result[1]=voltageStatus2;
   
   for(int8 i=0;i<8;i++)
   {
      if (bit_test(IOCtrl,i)==TRUE)
      {
         if(voltageStatus==vLow && bit_test(LVMask,i)==FALSE)
         {
            result[9-i]='x';
         }
         else
         {
            result[9-i]='1';
         }
      }
      else if (voltageStatus==vLow && bit_test(LVMask,i)==FALSE)
      {
         result[9-i]='o';
      }    
   }
}

void setIO()
{
   setLowVoltageFlags();
   unsigned int8 ioVal=IOCtrl;
   if (voltageStatus == vLow) ioVal &=LVMask;
   if (bit_test(ioVal,0)) output_high(CTRL_0); else output_low(CTRL_0);
   if (bit_test(ioVal,1)) output_high(CTRL_1); else output_low(CTRL_1);
   if (bit_test(ioVal,2)) output_high(CTRL_2); else output_low(CTRL_2);
   if (bit_test(ioVal,3)) output_high(CTRL_3); else output_low(CTRL_3);
   if (bit_test(ioVal,4)) output_high(CTRL_4); else output_low(CTRL_4);
   if (bit_test(ioVal,5)) output_high(CTRL_5); else output_low(CTRL_5);
   if (bit_test(ioVal,6)) output_high(CTRL_6); else output_low(CTRL_6);
   if (bit_test(ioVal,7)) output_high(CTRL_7); else output_low(CTRL_7);
}

void updateIO(unsigned int8 channel, BOOLEAN enableOP)
{
   if (channel == 0) // all channels
   {
      if (enableOP) IOCtrl = 0xFF; else IOCtrl=0x00;
   }
   else if(enableOP)
   {
      bit_set(IOCtrl,channel-1);
   }
   else
   {
      bit_clear(IOCtrl,channel-1);
   }
   setIO();  
}
#endif
