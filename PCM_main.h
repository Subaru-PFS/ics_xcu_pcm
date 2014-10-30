#include <18F67J60.h>
#device ADC=10
#define schDebug

#define numEZHR 3
#define numMPT100 1
#define ezhr4axis // otherwise setting is for ezhr 23

unsigned int8 resetStatus;
// messed with this with Craig
enum 
      {
      STACKTASK, TCPTASK, 
      TCPTASKINIT, TCPTASKNEW,
      TCPTASKLISTENING, TCPTASKCONNECTED,
      TCPTASKDISCONNECT,TCPTASKFORCEDISCONNECT,
      UDPTASK, UDPTASKNEW, UDPTASKOPENING,
      UDPTASKOPEN, UDPTASKDONE,
      STACKTASKDCHPCLIENT, STACKTASKDHCPCLIENTTRIS, STACKTASKDHCPCLIENTTRISEXIT,
      STACKTASKCALLDHCPTASK, DHCPTASK,
      DHCPTASK1, DHCPTASK2, DHCPTASK3, DHCPTASK4,
      DHCPTASK5, DHCPTASK6, DHCPTASK7, DHCPTASK8,
      STACKTASKTCP, STACKTASKTCP2,
      STACKTASKUDP, STACKTASKUDP2,
      STACKTASKUDPDISCARD, STACKTASKWFCSTRIS,
      STACKTASKCCSRX, STACKTASKICMP, STACKTASKARP,
      STACKAPP, MACDISCARDRX, MACDISCARDRX2,STACKTASKMACGETHEADER,
      MACGETHEADER, MACGETHEADER2, MACGETHEADER3, MACGETHEADER4, 
      MACGETHEADER5, MACGETHEADER6, MACGETHEADER7, MACGETHEADER8, 
      MACGETHEADER9, MACGETHEADER10, MACGETHEADER11,
      MACDISCARDRX3, MACDISCARDRX4
      } currentRoutine;

/*
TCP/IP Stack enabled.
Many TCP/IP configuration settings (servers enabled, ports used,
etc) are defined in TCPIPConfig.h.
Many hardware configuration settings (SPI port and GPIO pins used)
are defined in HardwareProfile.h.
*/

#include "tcpip/p18cxxx.h"
//#FUSES NOWDT
#FUSES WDT                      //Watch Dog Timer
#FUSES WDT4096                  //Watch Dog Timer uses 1:4096 Postscale

#use delay(crystal=25MHz,restart_wdt)
#use timer(tick=100us,bits=32,NOISR)
#use fast_IO(ALL)

#define TICK_TYPE unsigned int32
#define TICKS_PER_MILLISECOND (TICKS_PER_SECOND/1000)
unsigned int16 UDPSampleRate = 20*TICKS_PER_MILLISECOND;

#if defined(__PCH__)
   #define GetSystemClock()       getenv("CLOCK")
   #define GetInstructionClock()  (GetSystemClock()/4)
   #define GetPeripheralClock()   (unsigned int32)GetInstructionClock()
#else
   #define GetSystemClock()       getenv("CLOCK")
   #define GetInstructionClock()  (GetSystemClock()/2)
   #define GetPeripheralClock()   (GetSystemClock()/2)
#endif

#define MIN(a,b)  ((a > b) ? b : a)

#define EthernetRXfilterSetting 0b10000010 // allow Unicast and Multicast only

#include <math.h>
#include <stdint.h>
#include "tcpip/StackTsk2.h"
#include "tcpip/TCPIP Stack/TCPIPConfig.h"
#include "tcpip/TCPIP Stack/HardwareProfile.h"
#include "tcpip/StackTsk2.c"
#include <PCM_PortDefinitions.h>
//!BOOL exeADCtask = TRUE;
//!BOOL exeEZHRtask = TRUE;
#define E_LED_CONFIG  (int16)0b0011011101000010  // Ethernet LED Configuration



typedef struct EZHR23 {
   float          unitScaler;
   unsigned int8  IHold;
   unsigned int8  ISlow;
   unsigned int8  IFast;
   unsigned int8  accRate;
   unsigned int16 vStart;
   unsigned int16 vRun;
   unsigned int16 vStop;
   unsigned int16 mStepDiv;
} ezSettings;

#ORG 0x10000, 0x103FF{} // reserve 1 block at this location for settings
#define romEZHR 0x10000
//!ROM struct EZHR23 romEZHR[numEZHR]=
//!   {
//!      0.018,0,30,50,20,200,1500,200,2,
//!      0.010,0,30,50,20,200,1500,200,2,
//!      0.018,0,30,50,20,200,1500,200,2
//!   };
//!//#ORG 0x800   
#ORG default



//#ORG default


