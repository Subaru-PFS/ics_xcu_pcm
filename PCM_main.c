#include <PCM_main.h>
#include <PCM_TCPTask.h>
#include <PCM_UDPTask.h>

/************************************************************************
* START OF ISR's                                                        *
************************************************************************/
// Note: Some interupts are handled elsewhere
/////////////////////////////////////////////////////////////////////////
#int_SSP
void ssp_interupt ()
{

}   

// END OF ISR's
/////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////
/************************************************************************
* START OF MAIN                                                         *
************************************************************************/
void main()
{
   TICK_TYPE CurrentTick,PreviousUDPTick,PreviousSATick;
   resetStatus = (RCON & 0b00111111) | !(STKPTR & 0b11000000); // Get the Reset Status
   RCON = RCON | 0b00111111; //Reset RCON Reset flags... (Reset Register)
   STKPTR = STKPTR & 0b00111111; // Clear Stack Overflow/Underflow flags
   PortInit(); 
   OutputInit();  
   restart_wdt();
   romEZHRInit();    //set up default ezhr settings
   eeROMinit();      //set up default eprom settings
   IPAddressInit();  //set up MAC and default IP addresses
   delay_ms(500); 
   ADCInit();        //set up ADC ports
   SerialInit();     //set up serial ports
   TickInit();       //set up tick timer
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   StackInit();   
   WritePHYReg(ERXFCON,EthernetRXfilterSetting); // Allow only uni & multi
   SetLEDConfig(E_LED_CONFIG);   // swap LED's 
   output_high(E_SW_PWR_DN);     // Power Ethernet Switch
   output_high(E_SW_RST);
   output_low(RS485_TXEN);
   output_high(RS485_RXDIS);
   output_high(RS232_F_OFF);
   output_high(RS232_F_ON);
   CurrentTick = PreviousUDPTick = get_ticks();
   UDPSampleRate = eeReadUDPRate() * TICKS_PER_MILLISECOND;
   
   while(TRUE)
   {
      CurrentTick = get_ticks();
      restart_wdt();
      StackTask();
      restart_wdt();
      MyTCPTask();//handles TCP connections
      restart_wdt();
      
      if(CurrentTick-PreviousUDPTick >= UDPSampleRate)
      {
         currentRoutine=UDPTASK;
         BOOL UDPDone = MyUDPTask();
         if(UDPDone) 
         {
            PreviousUDPTick=CurrentTick;
         }
      }
      StackApplications();
   }
}
// END OF MAIN
/////////////////////////////////////////////////////////////////////////
