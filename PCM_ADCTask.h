#IFNDEF _pcm_adc
#DEFINE _pcm_adc

#define VscalerPorts    20.375
#define VOSPorts        0
#define VscalerMain     20.375
#define VOSMain         0
#define IscalerPorts    106.01
#define IOSPorts        0
#define IscalerMain     61.440
#define IOSMain         0.07
#define Pscaler         27.307
#define POS             3.75
#define Tscaler         -3.359
#define TOS             -461.69
/*********************************************************************
* ADC Interupt                                                  `    *
*********************************************************************/
#int_AD
void  AD_isr(void) 
{

}
/////////////////////////////////////////////////////////////////////

/*********************************************************************
* ADCInit ROUTINE                                                    *
* Sets up the ADC                                                    *
*********************************************************************/
void ADCInit()
{
   setup_adc_ports(AN0_TO_AN11|VSS_VREF);
   setup_adc(ADC_CLOCK_INTERNAL|ADC_TAD_MUL_20);
   enable_interrupts(INT_AD);
}
//////////////////////////////////////////////////////////////////////

/*********************************************************************
* set_adc_MUX ROUTINE                                                *
* Sets the MUX channel based on the Low Nibble of ADCTaskID          *
*********************************************************************/
void set_adc_MUX(int8 taskID)
{
   if (bit_test(taskID,0))   // set MUX select address
   output_high(MUX_0);
   else 
   output_low(MUX_0);

   if (bit_test(taskID,1))
   output_low(MUX_1);
   else 
   output_high(MUX_1);

   if (bit_test(taskID,2))
   output_low(MUX_2);
   else 
   output_high(MUX_2);

   if (bit_test(taskID,3))
   output_low(MUX_3);
   else 
   output_high(MUX_3);  
   
   set_adc_channel(2);
   delay_us(10);
}
//////////////////////////////////////////////////////////////////////

/*********************************************************************
* adc_to_decimal ROUTINE                                             *
* Assumes a linear function...                                       *
* Returns a scaled float value                                       *
* scales output using divFactor and Offset values                    *
*********************************************************************/
float adc_to_float(unsigned int32 rawADCvalue,float gain, float offset)
{
   float myflt = rawADCvalue;

   myflt=(myflt*gain)-offset;
     
   return(myflt);
}
//////////////////////////////////////////////////////////////////////

/*********************************************************************
* ADCTask ROUTINE                                                    *
* Each time it's called a different analog signal is read            *
* Uses ADCtaskID count to determine which port to read from          *
* Requires set_adc_MUX and adc_to_decimal                            *
*********************************************************************/
BOOL ADCtask(UDP_SOCKET s)
{   
   static int8 ADC_Task_ID = 0;
   char adc_str[];
   float adc_flt;
   char id[4];
   char returnData[20];
   BOOL result = FALSE;

   restart_wdt();
   int8 varID = (ADC_Task_ID+2)/2;
   switch(ADC_Task_ID)
   { 
      case 0:                         // IO Port Voltage Channels
      case 2:
      case 4:
      case 6:
      case 8:
      case 10:
      case 12:
      case 14:
         sprintf(id,"V%d:",varID);
         set_adc_MUX(ADC_Task_ID);
         adc_flt = adc_to_float(read_adc(),VscalerPorts,VOSPorts);
         break;  
      
      case 1:                       // IO Port Current Channels
      case 3:
      case 5:
      case 7:
      case 9:
      case 11:
      case 13:
      case 15:
         sprintf(id,"I%d:", varID);
         set_adc_MUX(ADC_Task_ID);
         adc_flt = adc_to_float(read_adc(),IscalerPorts,IOSPorts); 
         break;               
      case 16:                      // 16: read board 12V voltage
         strcpy(id,"VL:");
         set_adc_channel(10);
         adc_flt = adc_to_float(read_adc(),VscalerMain,VOSMain); 
         break;
      case 17:                      // 17: read board 12V current
         strcpy(id,"IL:");
         set_adc_channel(8);
         adc_flt = adc_to_float(read_adc(),IscalerMain,IOSMain); 
         break;
      case 18:                      // 18: read 36V voltage
         strcpy(id,"VH:");
         set_adc_channel(11);
         adc_flt = adc_to_float(read_adc(),VscalerMain,VOSMain); 
         break;
      case 19:                      // 19: read 36V current
         strcpy(id,"IH:");
         set_adc_channel(9);
         adc_flt = adc_to_float(read_adc(),IscalerMain,IOSMain); 
         break;
      case 20:  
         strcpy(id,"P:");// 20: read PSIA
         set_adc_channel(6);
         adc_flt = adc_to_float(read_adc(),Pscaler,POS); 
         break;
      case 21:                      // 21: read Temperature
         strcpy(id,"T:");
         set_adc_channel(7);
         adc_flt = adc_to_float(read_adc(),Tscaler,TOS); // scale to centigrade, 188 = c, - adiitional 273 = k
         break;
   }      
   if (UDPIsPutReady(s))
   {
      printf(UDPPut,"%s%.2g%s", id,adc_flt,"\r");
      UDPFlush();
   }
  
   ADC_Task_ID+=1;
   if (ADC_Task_ID>21) 
   {
      ADC_Task_ID=0;
      result = TRUE;
   }
   return result;
}   
//////////////////////////////////////////////////////////////////////


#ENDIF

