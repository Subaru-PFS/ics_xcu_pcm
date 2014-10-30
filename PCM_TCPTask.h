#ifndef _pcm_tcp
#define _pcm_tcp

NODE_INFO remNode;
#include <TCPIPConfig.h>
#include <PCM_CmdHandler.c>
#include <PCM_MACProm.h>

/*********************************************************************
* IPAddressInit ROUTINE                                              *
* Used to intialize the Ethernet MAC address                         *
*********************************************************************/
void IPAddressInit(void)
{
   AppConfig.Flags.bIsDHCPEnabled = TRUE;
   DHCPEnable(0); //enable nicWide stack support.
   
   //MAC address of this unit
   MY_MAC_BYTE1=MY_DEFAULT_MAC_BYTE1;
   MY_MAC_BYTE2=MY_DEFAULT_MAC_BYTE2;
   MY_MAC_BYTE3=MY_DEFAULT_MAC_BYTE3;
   MY_MAC_BYTE4=MY_DEFAULT_MAC_BYTE4;
   MY_MAC_BYTE5=MY_DEFAULT_MAC_BYTE5;
   MY_MAC_BYTE6=MY_DEFAULT_MAC_BYTE6;
   
   eeGetMACAddress(MY_MAC_BYTE1); // Overwrie MAC with real MAC address

   //IP address of this unit
   MY_IP_BYTE1=MY_DEFAULT_IP_ADDR_BYTE1;
   MY_IP_BYTE2=MY_DEFAULT_IP_ADDR_BYTE2;
   MY_IP_BYTE3=MY_DEFAULT_IP_ADDR_BYTE3;
   MY_IP_BYTE4=MY_DEFAULT_IP_ADDR_BYTE4;

   //network gateway
   MY_GATE_BYTE1=MY_DEFAULT_GATE_BYTE1;
   MY_GATE_BYTE2=MY_DEFAULT_GATE_BYTE2;
   MY_GATE_BYTE3=MY_DEFAULT_GATE_BYTE3;
   MY_GATE_BYTE4=MY_DEFAULT_GATE_BYTE4;

   //subnet mask
   MY_MASK_BYTE1=MY_DEFAULT_MASK_BYTE1;
   MY_MASK_BYTE2=MY_DEFAULT_MASK_BYTE2;
   MY_MASK_BYTE3=MY_DEFAULT_MASK_BYTE3;
   MY_MASK_BYTE4=MY_DEFAULT_MASK_BYTE4;
}
//////////////////////////////////////////////////////////////////////

/*********************************************************************
* TCPConnectedTask ROUTINE                                           *
* Checks and responds to RX Data                                     *
*********************************************************************/

BOOL TCPConnectedTask(TCP_SOCKET s)
{
   char rxData[60]={NULL};
   BOOL result = FALSE;
   int8 i = 0;
   if (TCPIsPutReady(s)>60)
   {
      while (TCPIsGetReady(s))
      {
         TCPGet(s,&rxData[i]);
         i+=1;
         if (i==60) 
         {
            break;
         }   
      } 
      if(i>0)
      {
         rxData[i] = NULL;
         TCPDiscard(s);
         executeCmd(&rxData, s);
         result = TRUE;
      }   
   }
   return result;
}  
//////////////////////////////////////////////////////////////////////

/*********************************************************************
* MyTCPTask ROUTINE                                                  *
* Manages sockets                                                    *
*********************************************************************/

void MyTCPTask() 
{
   static TICK lastTick[NUM_LISTEN_SOCKETS];
   static TCP_SOCKET socket[NUM_LISTEN_SOCKETS];
   static enum 
   {
      MYTCP_STATE_INIT=0, MYTCP_STATE_NEW, MYTCP_STATE_LISTENING,
      MYTCP_STATE_CONNECTED, MYTCP_STATE_DISCONNECT
   } state[NUM_LISTEN_SOCKETS];
   TICK currTick;
   BOOL alive;
   unsigned int8 i;

   currTick=TickGet();

   for (i=0; i<NUM_LISTEN_SOCKETS; i++)
   {
      switch (state[i])
      {
         case MYTCP_STATE_INIT:
            currentRoutine=TCPTASKINIT;
            socket[i] = INVALID_SOCKET;
            state[i] = MYTCP_STATE_NEW;
            break;
         case MYTCP_STATE_NEW:   
            currentRoutine=TCPTASKNEW;
            socket[i] = TCPOpen(0, TCP_OPEN_SERVER, TCP_LISTEN_PORT, TCP_PURPOSE_DEFAULT);
            if (socket[i] != INVALID_SOCKET)
            {
               state[i] = MYTCP_STATE_LISTENING;
            }
            break; 
         case MYTCP_STATE_LISTENING:
            currentRoutine=TCPTASKLISTENING;
            if (TCPIsConnected(socket[i])) 
            {
               state[i]=MYTCP_STATE_CONNECTED;
               lastTick[i]=currTick;
            }
            break;  
         case MYTCP_STATE_CONNECTED:
            currentRoutine=TCPTASKCONNECTED;
            if (currTick-lastTick[i] > (TICKS_PER_SECOND * (TICK)10))
            {
               TCPDisconnect(socket[i]);
               state[i]=MYTCP_STATE_DISCONNECT;
               lastTick[i] = currTick;
            }
            else if (TCPIsConnected(socket[i]))
            {
               alive=TCPConnectedTask(socket[i]);
               if(alive) lastTick[i]=currTick; 
            }
            else
            {
               state[i]=MYTCP_STATE_LISTENING;
            }
            break;  
         case MYTCP_STATE_DISCONNECT:
            if (currTick-lastTick[i] > (TICKS_PER_SECOND * (TICK)5))
            {
               TCPDisconnect(socket[i]);
               state[i] = MYTCP_STATE_LISTENING;
            }
            else if (!TCPIsConnected(socket[i]))
            {
               state[i]=MYTCP_STATE_LISTENING;
            }
            break;
      } 
   }
}
//////////////////////////////////////////////////////////////////////
#endif
