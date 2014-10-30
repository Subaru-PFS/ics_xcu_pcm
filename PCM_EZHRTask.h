#IFNDEF _pcm_ezhr
#DEFINE _pcm_ezhr
#include <PCM_Serial.h>

BOOL EZHRsettingsChanged = FALSE;

struct EZHR23 ramEZHR[numEZHR]=
{
   0.018,0,30,50,20,200,1500,200,2,
   0.010,0,30,50,20,200,1500,200,2,
   0.018,0,30,50,20,200,1500,200,2
};

//////////////////////////////////////////////////////////////////////
/*********************************************************************
* EZHRTask ROUTINE                                                   *
* Each time it's called a different EZHR Status/Position is read     *
* Uses ADCtaskID count to determine which port to read from          *
* Requires set_adc_MUX and adc_to_decimal                            *
*********************************************************************/
BOOL EZHRtask(UDP_SOCKET s)
{
   static int8 ezhrID = 1;
   static int8 ezhrTask = 0; //a

   char cmd[12];
   float scaledPosition =-1;
   BOOL result = FALSE;

   restart_wdt();   
   if(numEZHR!=0)
   {
      #ifdef ezhr4axis
      sprintf(cmd,"/1aM%dR\r", ezhrID);
      serialGetS(cmd, 200, TRUE);
      delay_ms(3);
      #endif
      switch (ezhrTask)
      {  
      case 0:
         #ifdef ezhr4axis
         sprintf(cmd,"/1?6\r"); // get drive divide ratio
         #else
         sprintf(cmd,"/%d?6\r", ezhrID); // get drive divide ratio
         #endif
         if (serialGetS(cmd, 300, TRUE))
         {
            float divRate = atof(UART_BUFFER+3);
            //float divRate = atof(UART_BUFFER);
            ramEZHR[ezhrID-1].mStepDiv = (int16)atoi(UART_BUFFER+3);
            //ramEZHR[ezhrID-1].mStepDiv = (int16)atoi(UART_BUFFER);
            if (UDPIsPutReady(s)>100)
            {
               printf(UDPPut,"MD%u:%s\r",ezhrID,UART_BUFFER+3);
               //printf(UDPPut,"MD%u:%s\r",ezhrID,UART_BUFFER);
               UDPFlush();
            }
         }
         break;
      case 1:
         #ifdef ezhr4axis
         sprintf(cmd,"/1?4\r"); // get limit data
         #else
         sprintf(cmd,"/%d?4\r", ezhrID); // get limit data
         #endif
         if (serialGetS(cmd, 300, TRUE))
         {       
            if (UDPIsPutReady(s)>100)
            {
               printf(UDPPut,"ML%u:%s\r",ezhrID,UART_BUFFER+3);
               //printf(UDPPut,"ML%u:%s\r",ezhrID,UART_BUFFER);
               UDPFlush();
            }
         }
         break;
      case 2:
         #ifdef ezhr4axis
         sprintf(cmd,"/1?8\r"); // get encoder count
         #else
         sprintf(cmd,"/%d?8\r", ezhrID); // get encoder count
         #endif
         if (serialGetS(cmd, 300, TRUE))
         {
            scaledPosition = atof(UART_BUFFER+3);
            //scaledPosition = atof(UART_BUFFER);
            //scaledPosition = scaledPosition * (ramEZHR[ezhrID-1].unitScaler /(float)ramEZHR[ezhrID-1].mStepDiv);
            #ifdef ezhr4axis
            scaledPosition = scaledPosition * (ramEZHR[ezhrID-1].unitScaler /(float)ramEZHR[ezhrID-1].mStepDiv);
            #else
            scaledPosition = scaledPosition * (ramEZHR[ezhrID-1].unitScaler /4);
            #endif
         }
         if (UDPIsPutReady(s)>100)
         {
            printf(UDPPut,"M%u:%f\r",ezhrID,scaledPosition);
            UDPFlush();
         }
         break; 
      case 3:
         #ifdef ezhr4axis
         sprintf(cmd,"/1?0\r"); // get step count
         #else
         sprintf(cmd,"/%d?0\r", ezhrID); // get step count
         #endif
         if (serialGetS(cmd, 300, TRUE))
         {
            scaledPosition = atof(UART_BUFFER+3);
            //scaledPosition = atof(UART_BUFFER);
            scaledPosition = scaledPosition * (ramEZHR[ezhrID-1].unitScaler /(float)ramEZHR[ezhrID-1].mStepDiv);
         }
         if (UDPIsPutReady(s)>100)
         {
            printf(UDPPut,"m%u:%f\r",ezhrID,scaledPosition);
            UDPFlush();
         }
         break;
   } 
      
      ezhrTask+=1;
      if (ezhrTask>3)
      {
         ezhrTask=0;
         ezhrID+=1;
         if (ezhrID > numEZHR)
         {
            ezhrID=1;
            result = TRUE;
         }
      }
   }
   else
   {
      result=TRUE;
   }
   return result;  
}


/*********************************************************************
* loadEZHRfromRom ROUTINE                                            *
*********************************************************************/
void loadEZHRfromROM()
{
   read_program_memory(romEZHR,ramEZHR,sizeof(ramEZHR));
}
/*********************************************************************
* saveEZHRtoRom ROUTINE                                              *
*********************************************************************/
void saveEZHRtoROM()
{
   write_program_memory(romEZHR,ramEZHR,sizeof(ramEZHR));
}

void ackGlobalCommand(TCP_SOCKET s)
{
   TCPPut(s,0x2F);
   TCPPut(s,0x30);
   TCPPut(s,0x0F);
   TCPFlush(s);
}

/*********************************************************************
* initRomEZHR                                                        *
*********************************************************************/
void romEZHRInit()
{
   int16 val=0;
   int16 *ptr = &val;
   
   
   read_program_memory(romEZHR,ptr,sizeof(val));
   if (val==0xFFFF) // if rom is unitialized, initialize rom with ram data
   {
      saveEZHRtoROM();
   }
   else // initalize ram with rom data
   {
      loadEZHRfromROM();
   }
}


#ENDIF
