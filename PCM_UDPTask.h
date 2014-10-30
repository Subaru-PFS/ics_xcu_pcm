#ifndef _pcm_udp
#define _pcm_udp
/*********************************************************************
* MyUDPTask ROUTINE                                                  *
* Manages sockets                                                    *
*********************************************************************/
#include <PCM_EZHRTask.h>
#include <PCM_ADCTask.h> 
#include <PCM_MPT100Task.h>


#define statusP1    LATD,0   //Port 6 power control
#define statusP0    LATD,1   //Port 7 power control
#define statusP7    LATE,0   //Port 0 power control
#define statusP6    LATE,1   //Port 1 power control
#define statusP5    LATE,2   //Port 2 power control
#define statusP4    LATE,3   //Port 3 power control
#define statusP3    LATE,4   //Port 4 power control
#define statusP2    LATE,5   //Port 5 power control

void UDPOpenTask(UDP_SOCKET s)
{
   static unsigned int8 taskID = 0;
   BOOL taskComplete=FALSE;
   
   
   switch (taskID)
   {
      case 0:
         taskComplete = ADCtask(s);
         if(taskComplete) 
         {
            taskID+=1;
         }
         break;
      case 1:   
         taskComplete = EZHRtask(s);
         if(taskComplete) 
         {
            taskID+=1;
         }
         break;
      case 2:   
         unsigned int32 IOStatus=0; // send the status of the power ports 
         if (bit_test(statusP0)) bit_set(IOStatus,0);
         if (bit_test(statusP1)) bit_set(IOStatus,1);
         if (bit_test(statusP2)) bit_set(IOStatus,2);
         if (bit_test(statusP3)) bit_set(IOStatus,3);
         if (bit_test(statusP4)) bit_set(IOStatus,4);
         if (bit_test(statusP5)) bit_set(IOStatus,5);
         if (bit_test(statusP6)) bit_set(IOStatus,6);
         if (bit_test(statusP7)) bit_set(IOStatus,7);
         if (UDPIsPutReady(s)>100)
         {
            printf(UDPPut,"IO:%lu%s", IOStatus,"\r");
            UDPFlush();
         }
         taskID+=1;
         break;
      case 3:   
         
         taskComplete = MPT100getPressureTask(s);
         if(taskComplete) 
         {
            taskID=0;
         }
         break;
         
   }
}

BOOL MyUDPTask()
{
   static UDP_SOCKET mySocket;
   static enum 
   {
      MYUDP_STATE_NEW=0, MYUDP_STATE_OPENING,
      MYUDP_STATE_OPEN, MYUDP_STATE_DONE
   } state;
      
   BOOL done = FALSE;
   
   switch (state)
   {
      case MYUDP_STATE_NEW:
         currentRoutine=UDPTASKNEW;
         mySocket = UDPOpen(UDP_SOURCE_PORT,NULL,UDP_DEST_PORT);
         state = MYUDP_STATE_OPENING;
         break;
      case MYUDP_STATE_OPENING:
         currentRoutine=UDPTASKOPENING;
         if (UDPIsOpened(mySocket)) state= MYUDP_STATE_OPEN;
         break;
      case MYUDP_STATE_OPEN: 
         currentRoutine=UDPTASKOPEN;
//!         if (UDPIsPutReady(mySocket)>100) 
//!         {
            UDPOpenTask(mySocket);
            //state=MYUDP_STATE_DONE;
            done=TRUE;
//!         }             
         break;
      case MYUDP_STATE_DONE:
          currentRoutine=UDPTASKDONE;
          UDPClose(mySocket);
          output_low(U_ACT);
          state = MYUDP_STATE_NEW;
          done = TRUE;
          break;
   }  
   return done;
}

#endif
