#IFNDEF _pcm_mpt
#DEFINE _pcm_mpt
#include <PCM_Serial.h>

#define mb2torr 0.750061683
#define cmdLen 30

unsigned int8 MPT100CalcChecksum(char *cmd)
{
   unsigned int8 checkSum = 0;
   int i =0;
   while (*cmd>0)
   {
      checkSum+=*cmd;
      i+=1;
      cmd+=1;
      if(i==12) break;
   }
   return checkSum;
}

float MPT100CalcPressure(char *data)
{
   return 0;
}


BOOL MPT100getPressureTask(UDP_SOCKET s)
{ 
   BOOL result = FALSE;
   static unsigned int8 UID=1;
   if (numMPT100 != 0)
   {
      float Mantissa;
      float Exponent;
      
      
      char cmd[cmdLen] = {NULL};
      char cSum[6] = {NULL};
      sprintf(cmd, "%03u0074002=?",UID);
      sprintf(cSum, "%03u\r",MPT100CalcChecksum(cmd));
      strcat(cmd,cSum);
      if (serialGetS(cmd, 300, TRUE))
      {       
         if (UDPIsPutReady(s)>100)
         {
            char mData[5]={NULL};
            char eData[3]={NULL};
            char *ptr = UART_BUFFER+10;
            strncpy(mData,ptr,4);
            ptr = UART_BUFFER+14;
            strncpy(eData,ptr,2);

            Mantissa = atof (mData);
            Exponent = atof (eData)-23;
            
            float Pressure = Mantissa*pow(10,Exponent) * mb2torr;
            printf(UDPPut,"VP%u:%e", UID, Pressure);
            UDPFlush();
         }
      }
      UID +=1;
      if (UID >numMPT100) 
      {
         UID = 1;
         result = TRUE;
      }   
   }
   return result;
}




#ENDIF
