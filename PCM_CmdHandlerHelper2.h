#ORG 0x018000, 0x0180FF {} // save space for ADCParams Storage
#define rom_adcParams 0x018000
#define intRef 0
#define extRef 1

typedef struct ADCparams{int8 refSource;int8 MUXchannel;int8 ADCchannel; float adcOffset;float adcScaler;};
struct ADCparams adcParams[]=       {                                     
                                       {extRef,0,10,0,0.05},// BusA voltage
                                       {extRef,0,11,0,0.05},// BusB 
                                       {extRef,0,2,0,0.05}, // ch1
                                       {extRef,2,2,0,0.05}, // ch2 
                                       {extRef,4,2,0,0.05}, // ch3 
                                       {extRef,6,2,0,0.05}, // ch4
                                       {extRef,8,2,0,0.05}, // ch5
                                       {extRef,10,2,0,0.05}, // ch6
                                       {extRef,12,2,0,0.05}, // ch7
                                       {extRef,14,2,0,0.05}, // ch8
                                       {intRef,0,8,1.23,0.012}, // BusA current
                                       {intRef,0,9,1.23,0.012},// BusB 
                                       {extRef,1,2,0,0.0094},// ch1
                                       {extRef,3,2,0,0.0094},// ch2
                                       {extRef,5,2,0,0.0094},// ch3
                                       {extRef,7,2,0,0.0094},// ch4
                                       {extRef,9,2,0,0.0094},// ch5
                                       {extRef,11,2,0,0.0094}, // ch6
                                       {extRef,13,2,0,0.0094}, // ch7
                                       {extRef,15,2,0,0.0094}, // ch8
                                       {extRef,0,7,-461.69,-0.298}, // temperature
                                       {extRef,0,6,3.75,0.0366}  // pressure    
                                    };    

typedef enum VIEtype {VIEvoltage=0, VIEcurrent=10, VIEenvironment=20};
float readAnalogValues(VIEtype VIE, int16 index, int8 numSamples=1, BOOLEAN rawData = FALSE)
{
      index+=VIE;
      int8 reference = adcParams[index].refSource;
      int8 MUXch = adcParams[index].MUXchannel;
      int8 ADCch = adcParams[index].ADCchannel;
      float scaler=adcParams[index].adcScaler;
      float offset=adcParams[index].adcOffset;
      
      if(rawData)
      {
         scaler = 1;
         offset = 0;
      } 
      
      if (numSamples<=0) numSamples=1;
      
      if (reference ==intRef)
      {
         setup_adc_ports(AN0_TO_AN11|VSS_VDD);
      }
      else
      {
         setup_adc_ports(AN0_TO_AN11|VSS_VREF); 
      }
      
      set_adc_MUX(MUXch);
      set_adc_channel(ADCch); 
      
      float adcVal=0;
      unsigned int8 i=0;
      
      for(i=0;i<numSamples;i++)
      {
         adcVal += adc_to_float(read_adc(),scaler,offset);
      }
      adcVal/=(float)numSamples;
      return adcVal;
}


void saveADCParams()
{
   char* ptr = &adcParams[0];
   write_program_memory(rom_adcParams,ptr,sizeof(adcParams));
}

void loadADCParams()
{
   char* ptr = &adcParams[0];
   read_program_memory(rom_adcParams,ptr,sizeof(adcParams));
}

void iniADCParams()
{
   if (read_program_eeprom(rom_adcParams) >1)
   {
      saveADCParams();
   }
   else
   {
      loadADCParams();
   }
}

unsigned int8 sByteToUint(char* stringByte)
{
   unsigned int8 result=0;
   for(int i=0;i<8;i++)
   {    
      if(stringByte[i]=='1') bit_set(result,7-i);  
   }
   return result;
}

void uIntToSbyte(char* returnString, unsigned int8 binaryByte)
{
   unsigned int8 result=0;
   for(int i=0;i<8;i++)
   {    
      if(bit_test(binaryByte,i))
      {
         returnString[7-i] = '1';
      }
      else
      {
         returnString[7-i] = '0';
      }
      returnString[8]="\0";
   }
}

#org default
