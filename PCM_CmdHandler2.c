#ifndef _pcm_cmd2
#define _pcm_cmd2

#include <PCM_EZHRTask.h>
#include <PCM_ADCTask.h>
#include <PCM_MACProm.h>
#include <PCM_Serial.h>
#include <PCM_CmdHandler2.h>
#include <PCM_CmdHandlerHelper2.h>
#include <PCM_PortControl.h>

#define numParam 4
#define lenParam 60


char params[numParam][lenParam];
char retData[100];
 
                                         
enum mainMenu {_send_rs485,_send_rs232,_setPowerEn,_getPowerEn,_readVoltage,_readCurrent,_calVoltage,_calCurrent,_readEnviroment,_calEnvironment,_saveCalData,_getEthernet,_setEthernet,_getMask,_setMask,_getThreshold,_setThreshold,_getSerConf,_setSerConf,_getRevision,_getSerialNumber,_softReset,_getRebootStatus};
char rom mainMenuItems[][8]=                   {send_rs485,
                                                send_rs232,
                                                setPowerEn,
                                                getPowerEn,
                                                readVoltage,
                                                readCurrent,
                                                calVoltage,
                                                calCurrent,
                                                readEnvironment,
                                                calEnvironment,
                                                saveCalData,
                                                getEthernet,
                                                setEthernet,
                                                getMask,
                                                setMask,
                                                getThreshold,
                                                setThreshold,
                                                getSerial,
                                                setSerial,
                                                getRevision,
                                                getSerialNumber,
                                                softReset,
                                                getRebootStatus,
                                               "\0"};

enum serialSubMenu_baud {_ss4800,_ss9600,_ss19200,_ss38400,_ss57600,_ss115200};
char rom serialSubMenuItems_baud[][8]=         {ss_4800,
                                                ss_9600,
                                                ss_19200,
                                                ss_38400,
                                                ss_57600,
                                                ss_115200,
                                                "\0"};
                                                
enum serialSubMenu_bits {_ss8n1,_ss8e1,_ss8o1,_ss8n2,_ss8e2,_ss8o2};
char rom serialSubMenuItems_bits[][8]=         {ss_8n1,
                                                ss_8e1,
                                                ss_8o1,
                                                ss_8n2,
                                                ss_8o2,
                                                ss_8e2,
                                                "\0"};                                                
                                               
enum pEnSubMenu {_pe_all,_pe_ch1,_pe_ch2,_pe_ch3,_pe_ch4,_pe_ch5,_pe_ch6,_pe_ch7,_pe_ch8};
char rom pEnSubMenuItems[][8]=                 {pe_all,
                                                pe_ch1,
                                                pe_ch2,
                                                pe_ch3,
                                                pe_ch4,
                                                pe_ch5,
                                                pe_ch6,
                                                pe_ch7,
                                                pe_ch8,
                                                "\0"};
                                                
enum pEnSubSubMenu {_pe_on,_pe_off,_pe_cycle};
char rom pEnSubSubMenuItems[][8]=              {pe_on,
                                                pe_off,
                                                pe_cycle,
                                                "\0"};

enum VISubMenu {_rp_bus0,_rp_bus1,_rp_ch1,_rp_ch2,_rp_ch3,_rp_ch4,_rp_ch5,_rp_ch6,_rp_ch7,_rp_ch8,_rp_all};
char rom VISubMenuItems[][8]=                  {rp_bus0,
                                                rp_bus1,
                                                rp_ch1,
                                                rp_ch2,
                                                rp_ch3,
                                                rp_ch4,
                                                rp_ch5,
                                                rp_ch6,
                                                rp_ch7,
                                                rp_ch8,
                                                rp_all,
                                                "\0"};
enum VISubSubMenu {_rp_rawData};
char rom VISubSubMenuItems[][8]=               {rp_rawData,
                                                "\0"};
 
enum envSubMenu {_re_temp,_re_pressure,_re_all};
char rom envSubMenuItems[][8]=                 {re_temp,
                                                re_pressure,
                                                re_all,
                                                "\0"};                                               
enum envSubSubMenu {_re_rawData};
char rom envSubSubMenuItems[][8]=              {re_rawData,
                                                "\0"};
                                               
enum maskSubMenu {_gm_boot,_gm_low};
char rom maskSubMenuItems[][8]=                {gm_boot,
                                                gm_low,
                                                "\0"};
                                                
enum thresholdSubmenu {_gt_batt,_gt_low,_gt_auxLow};
char rom thresholdSubMenuItems[][8]=           {gt_batt,
                                                gt_low,
                                                gt_auxLow,
                                                "\0"};
                                                
//!enum configSerialSubMenu {_gs_baud,_gs_timeout};
//!char rom configSerialSubMenuItems[][8]=        {gs_baud,
//!                                                gs_timeout,
//!                                                "\0"};

enum softResetSubMenu {_sr_system,_sr_ethernet};
char rom softResetSubMenuItems[][8]=            {sr_system,
                                                sr_ethernet,
                                                "\0"};

//Get Menu Index...//

int8 getMenuIndex(char*Param,rom char*menu, int size=8)
{
   int i = 0;
   int j = 0;
   while(menu[0] !='\0')
   {
      char test[8];
      
      for(j=0;j<size;j++) // copy test string to ram
      {
         test[j]=menu[j];
      }
      
      if(strcmp(test,Param)==0) // compare test string with passed Param
      {
         return i;
      }
      i++;
      menu+=size;
   }
   return noRecordFound;
}

int8 getSerialSubParam(char*Param, rom char*menu, size=8)
{
   int i = 0;
   int j = 0;
   while(menu[0] !='\0')
   {
      char test[8];
      
      for(j=0;j<size;j++) // copy test string to ram
      {
         test[j]=menu[j];
      }
      
      char *ptr;
      ptr=strstr(Param,test);//search for substring
         
      if(ptr!=NULL) 
      {
         return i;
      }
      i++;
      menu+=size;
   }
   return noRecordFound;
}
int16 getSerialTimeout(char*Param)
{
   int16 ret=0;
   char *ptr;
   ptr=strchr(Param, 'T');
   if(ptr != NULL)
   {
      ptr+=1;
      ret=atoi(ptr);
   }
   return ret;
}


void sendSerial(BOOLEAN RS485)
{  
   unsigned int16 timeout =getSerialTimeout(params[1]);
   if (timeout <500) timeout=500;
   if (timeout >5000) timeout=5000;
   
   int32 baud=9600;
   unsigned int8 result = getSerialSubParam(params[1], serialSubMenuItems_baud); 
   switch (result)
   {
      case _ss4800:
         baud=4800;
         break;
      case _ss19200:
         baud=19200;
         break;
      case _ss38400:
         baud=38400;
         break;
      case _ss57600:
         baud=57600;
         break;
      case _ss115200:
         baud=115200;
         break;  
      default: //9600 baud
         baud=9600;
         break;
   }
   
   
   result = getSerialSubParam(params[1], serialSubMenuItems_bits); 
   
   switch (result)
   {
      case _ss8e1:
         setup_uart(baud,STR8E1);
         break;
      case _ss8o1:
         setup_uart(baud,STR8O1);
         break;   
       case _ss8n2:
         setup_uart(baud,STR8N2);
         break;
      case _ss8e2:
         setup_uart(baud,STR8E2);
         break;
      case _ss8o2:
         setup_uart(baud,STR8O2);
         break;  
      default: //8n1
         setup_uart(baud,STR8N1);
         break;
   }

   BOOL sRet= serialGetSs(params[2], retData, timeout, RS485);
   if (sRet == FALSE)
   {
      sprintf(retData,"%s", noResponse);
   }
}

void setPowerEnable()
{
   unsigned int8 chID = getMenuIndex(params[1], pEnSubMenuItems);
   unsigned int8 stateID = getMenuIndex(params[2], pEnSubSubMenuItems);
   if (chID == noRecordFound)
   {
      sprintf(retData,"%s",badChannel); 
   }
   else
   {
      if (stateID==noRecordFound)
      {
         sprintf(retData,"%s",badParam);
      }
      else if(stateID==_pe_on)
      {
         updateIO(chID,TRUE);
         getIOStatus(retData);
      }
      else if(stateID==_pe_off)
      {
         updateIO(chID,FALSE);
         getIOStatus(retData);
      }
      else if(chID>0 && chID<9 && bit_test(IOCtrl,(chID-1)))
      {
        updateIO(chID,FALSE);
        delay_ms(1000);
        updateIO(chID,TRUE);
        getIOStatus(retData);
      }
   }
}

void readVoltages()
{
   unsigned int8 chID = getMenuIndex(params[1], VISubMenuItems);
   unsigned int8 readRawData = getMenuIndex(params[3],VISubSubMenuItems);
   unsigned int8 numSamples = atoi(params[2]);
   BOOLEAN rdRawData = FALSE;
   if (readRawData==_rp_rawData) rdRawData=TRUE;
   
   switch(chID)
   {
      case _rp_all:
         sprintf(retData,"%f",readAnalogValues(VIEvoltage, 0, numSamples, rdRawData));
         char temp[10];
         for (int i=1;i<10; i++)
         {
            sprintf(temp,", %f",readAnalogValues(VIEvoltage, i, numSamples, rdRawData));
            strcat(retData,temp);
            //StackApplications();
         }   
         break;
      case noRecordFound:
         sprintf(retData,"%s",badParam);
         break;
      default:
         sprintf(retData,"%f",readAnalogValues(VIEvoltage, chID, numSamples, rdRawData));
         break;
   }
}

void readCurrents()
{
   unsigned int8 chID = getMenuIndex(params[1], VISubMenuItems);
   unsigned int8 readRawData = getMenuIndex(params[3],VISubSubMenuItems);
   unsigned int8 numSamples = atoi(params[2]);
   BOOLEAN rdRawData = FALSE;
   if (readRawData==_rp_rawData) rdRawData=TRUE;
 
   switch(chID)
   {
      case _rp_all:
         sprintf(retData,"%f",readAnalogValues(VIEcurrent, 0, numSamples, rdRawData));
         char temp[10];
         for (int i = 1;i < 10; i++)
         {
            float data = readAnalogValues(VIEcurrent, i, numSamples, rdRawData);
            sprintf(temp,", %f", data);
            strcat(retData,temp);
            //StackApplications();
         }   
         break;
      case noRecordFound:
         sprintf(retData,"%s",badParam);
         break;
      default:
         sprintf(retData,"%f",readAnalogValues(VIEcurrent, chID, numSamples, rdRawData));
         break;
   }
}

void readEnvironments()
{
   unsigned int8 chID = getMenuIndex(params[1], envSubMenuItems);
   unsigned int8 readRawData = getMenuIndex(params[3],VISubSubMenuItems);
   unsigned int8 numSamples = atoi(params[2]);
   BOOLEAN rdRawData = FALSE;
   if (readRawData==_rp_rawData) rdRawData=TRUE;
   
   switch(chID)
   {
      case _re_all:
         sprintf(retData,"%f",readAnalogValues(VIEenvironment, 0, numSamples, rdRawData));
         char temp[10];
         for (int i=1;i<2; i++)
         {
            sprintf(temp,", %f",readAnalogValues(VIEenvironment, i, numSamples, rdRawData));
            strcat(retData,temp);
         }   
         break;
      case noRecordFound:
         sprintf(retData,"%s",badParam);
         break;
      default:
         sprintf(retData,"%f",readAnalogValues(VIEenvironment, chID, numSamples, rdRawData));
         break;
   }
}

typedef enum updateADCParamsMode {adcV=0, adcC=10, adcE=20};
void updateADCParams(updateADCParamsMode mode)
{
   unsigned int8 index = getMenuIndex(params[1], VISubMenuItems);
   
   switch(index)
   {
      case noRecordFound:
      case _rp_all:
         sprintf(retData,badParam);
         break;
      default:
         adcParams[index+mode].adcOffset=atof(params[2]);
         adcParams[index+mode].adcScaler=atof(params[3]);   
         sprintf(retData,"%s",success);
   }
}

void getMaskByte()
{
   unsigned int8 index = getMenuIndex(params[1], maskSubMenuItems);
   unsigned int8 i=0;
   switch(index)
   {
   case _gm_boot:
      uIntToSbyte(retData,eeRAMcopy.eeData.PUmask);
      break;
   case _gm_low: 
      uIntToSbyte(retData,eeRAMcopy.eeData.LVmask);
      break;
   default:
       sprintf(retData,"%s",badParam);
       break;
   }
}

void setMaskByte()
{
   unsigned int8 index = getMenuIndex(params[1], maskSubMenuItems);
   switch (index)
   {
      case _gm_boot:
         eeRAMcopy.eeData.PUmask = sByteToUint(params[2]);
         uIntToSbyte(retData,eeRAMcopy.eeData.PUmask);
         eeWriteByte(offsetof(struct eedata,PUmask), eeRAMcopy.eeData.PUmask);
         break;
      case _gm_low:
         eeRAMcopy.eeData.LVmask = sByteToUint(params[2]);
         uIntToSbyte(retData,eeRAMcopy.eeData.LVmask);
         eeWriteByte(offsetof(struct eedata,LVmask), eeRAMcopy.eeData.LVmask);
         break;
      default:
         sprintf(retData,"%s",badParam);
         break;   
   }
}

void getThresholdValue()
{
   unsigned int8 index = getMenuIndex(params[1], thresholdSubMenuItems);
   switch (index)
   {
      case _gt_batt:
         sprintf(retData,"%f", eeRAMcopy.eeData.onBattThreshold);
         break;
      case _gt_low:
         sprintf(retData,"%f", eeRAMcopy.eeData.LVThreshold);
         break;
      case _gt_auxLow:
         sprintf(retData,"%f", eeRAMcopy.eeData.ch2Threshold);
         break;
      default:
         sprintf(retData,"%s", badParam);
         break;
   }   
}

void setThresholdValue()
{
   unsigned int8 index = getMenuIndex(params[1], thresholdSubMenuItems);
   switch (index)
   {
      case _gt_batt:
         eeRAMcopy.eeData.onBattThreshold=atof(params[2]);
         eeWriteFloat(offsetof(struct eedata,onBattThreshold), eeRAMcopy.eeData.onBattThreshold);
         sprintf(retData,"%f", eeRAMcopy.eeData.onBattThreshold);
         break;
      case _gt_low:
         eeRAMcopy.eeData.LVThreshold=atof(params[2]);
         eeWriteFloat(offsetof(struct eedata,LVThreshold), eeRAMcopy.eeData.LVThreshold);
         sprintf(retData,"%f", eeRAMcopy.eeData.LVThreshold);
         break;
      case _gt_auxLow:
         eeRAMcopy.eeData.ch2Threshold=atof(params[2]);
         eeWriteFloat(offsetof(struct eedata,ch2Threshold), eeRAMcopy.eeData.ch2Threshold);
         sprintf(retData,"%f", eeRAMcopy.eeData.ch2Threshold);
         break;
      default:
         sprintf(retData,"%s", badParam);
         break;
   }  
}

void getEthernetConfig()
{
   unsigned int8 address = atoi(params[1]);
   unsigned int8 length = atoi(params[2]);
   unsigned int8 checkSum = 0-address-length;
   char* rdPtr = retData;
   
   sprintf(rdPtr,"%X",address);
   rdPtr+=2;
   sprintf(rdPtr,"%X",length);
   rdPtr+=2;
   if(length <=16 && address+length  < sizeof(eeRAMcopy.eeData.micrelReg))
   {
      for (int i = 0; i<length; i++)
      {
         checkSum-=eeRAMcopy.eeData.micrelReg[address+i];
         sprintf(rdPtr,"%X",eeRAMcopy.eeData.micrelReg[address+i]);
         rdPtr+=2;
      }
      sprintf(rdPtr,"%X",checkSum);
   }
   else
   {
      sprintf(retData,"%s",badParam);
   }
}

void setEthernetConfig()
{ 
   union
   {   
      unsigned int8 intVal[19]; 
      struct
      {  unsigned int8 address;
         unsigned int8 length;
         unsigned int8 data[17];
      }record;       
   }bData= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
   
   
   unsigned int8 dataPtr=0;
   char* asciiWord = &params[1];
   unsigned int8 checkSum=0;
   
   while (asciiWord !='\0' && dataPtr<19)
   {
      bData.intVal[dataPtr]=aHexWordToByte(asciiWord);
      asciiWord+=2;
      dataPtr+=1;
   }
   
   int8 lastAddress = bData.record.address + bData.record.length;
   //check that register addresses are valid
   if (lastAddress < sizeof(eeRAMcopy.eeData.micrelReg) && bData.record.length<=16)
   {
      // check that the data is valid by summing data + checksum
      for(int i=0;i<19;i++)
      {
         checkSum+=bData.intVal[i]; // all values should add up to 0
      }
      if (checkSum==0)
      {
         for(unsigned int i=0;i <bData.record.length;i++)
         {
            eeRAMcopy.eeData.micrelReg[bData.record.address+i]=bData.record.data[i];
            eeWriteByte(bData.record.address+i, bData.record.data[i]);
         }
         sprintf(retData,"%s",success);  
      } 
      else
      {
         sprintf(retData,"%s",badParam);
      }  
   }
   else
   {
      sprintf(retData,"%s",badParam);
   }
}

void getSerialConfig()
{

}

void setSerialConfig()
{

}

void getSerNum()
{
   int8 sn[6];
   eeGetMACAddress(sn[0]);
   for (int i=0;i<6;i++)
   {
      sprintf(&retData[i*2],"%X",sn[i]);
   }   
}

void systemReset(TCP_SOCKET s)
{
   unsigned int8 index = getMenuIndex(params[1], softResetSubMenuItems);
   switch (index)
   {
      case _sr_system:
         sprintf(retData,"%s",success);
         TCPPutArray(s,retData,strlen(retData));
         TCPFlush(s);
         delay_ms(500);
         reset_cpu();
         
         break;
      case _sr_ethernet:
         output_low(E_SW_RST);
         delay_ms(100);
         output_high(E_SW_RST);
         sprintf(retData,"%s",success);
         break;
   }
}

void rebootStatus()
{
   float now= get_ticks();
   now = now/ticksPerSecond;
   switch (restart_cause())
   {
      case WDT_TIMEOUT:
      case WDT_FROM_SLEEP:
         sprintf(retData,"%Lu, %f seconds ago",watchdog, now);
         break;
      case MCLR_FROM_RUN: 
      case MCLR_FROM_SLEEP:
         sprintf(retData,"%s, %f seconds ago",external, now);
         break;
      case NORMAL_POWER_UP:
         sprintf(retData,"%s, %f seconds ago",normal, now);
         break;
      case BROWNOUT_RESTART:
         sprintf(retData,"%s, %f seconds ago",brownout, now);
         break;
      case RESET_INSTRUCTION:
         sprintf(retData,"%s, %f seconds ago",software, now);
         break;
   }   

}

//MAIN COMMAND HANDLER//
void executeCmd(char *rxData, TCP_SOCKET s)
{
   enum cmsStat {cs_invalid, cs_valid, cs_overrun};
   unsigned int8 cmdStatus =cs_invalid;
  
   /////////////////////// Parse rxData to build command...////////////////////
   
   unsigned int paramNum = 0;
   unsigned int chrNum = 0;
   char tempChr = 0;
   int i=0; 
   
   while (cmdStatus != cs_overrun && tempChr != EOLCharacter && i<60)
   {
      tempChr = rxData[i];
      if (tempChr==SOLCharacter)
      {
         chrNum = 0;
         paramNum = 0;
         cmdStatus = cs_valid;
      }
      if (cmdStatus!=cs_invalid)
      {
         switch(tempChr)
         {
            case SOLCharacter:
            case '\r':
               break;
            case delimiterCharacter:
               if (paramNum==2 && (params[0][0]=='#' || params[0][0]=='@'))
               // special case for serial comms - ignore delimiters in serial data
               {
                  params[paramNum][chrNum]=tempChr;
                  chrNum++;
                  if (chrNum >= lenParam) 
                  {
                     cmdStatus=cs_overrun;
                  }   
               }
               else
               // case for standard commands
               {
                  params[paramNum][chrNum]="\0";
                  chrNum=0;   
                  
                  paramNum++;
                  if (paramNum >=numParam) 
                  {
                     cmdStatus=cs_overrun;
                  }
               }   
               break;
            case EOLCharacter:
               params[paramNum][chrNum]="\0";
               break;  
            default:
               params[paramNum][chrNum]=tempChr;
               chrNum++;
               if (chrNum >= lenParam) cmdStatus=cs_overrun;
               break;     
         }        
      }  
      i++;
   }
   
   /////////////// Parse first Parameter...////////////////////////////////////
   if (cmdStatus != cs_invalid)
   {
      if (cmdStatus==cs_overrun)
      {
               sprintf(retData,"%s",overrun);
      }
      else
      {
         int8 menuIndex;
         menuIndex = getMenuIndex(params[0], mainMenuItems);
           
         switch(menuIndex)     
         {   
            case _send_rs485:
               sendSerial(TRUE);
               break;
            case _send_rs232:
               sendSerial(FALSE);
               break;
            case _setPowerEn:
               setPowerEnable();
               break;
            case _getPowerEn:
               getIOStatus(retData);
               break;
            case _readVoltage:
               readVoltages();
               break;   
            case _readCurrent:
               readCurrents();
               break;
            case _calVoltage:
               updateADCParams(adcV);
               break;
            case _calCurrent:
               updateADCParams(adcC);
               break;
            case _readEnviroment:
               readEnvironments();
               break;
            case _calEnvironment:   
               updateADCParams(adcE);
               break;
            case _saveCalData:
               saveADCParams();
               sprintf(retData,"%s",success);
               break;
            case _getMask:
               getMaskByte();
               break;
            case _setMask:
               setMaskByte();
               break;
            case _getThreshold:
               getThresholdValue();
               break;
            case _setThreshold:
               setThresholdValue();
               break;
            case _getEthernet:
               getEthernetConfig();
               break;
            case _setEthernet:
               setEthernetConfig();
               break;
            case _getSerConf:
               getSerialConfig();
               break;
            case _setSerConf:
               setSerialConfig();
               break;
            case _getRevision:
               sprintf(retData,"%s",revision);
               break;
            case _getSerialNumber:
               getSerNum();
               break;
            case _softReset:
               systemReset(s);
               break;
            case _getRebootStatus:
               rebootStatus();
               break;
            default:
               sprintf(retData,"%s",badCmd);
               break;
         }    
      }    
      TCPPutArray(s,retData,strlen(retData));
      TCPFlush(s);
      params[0]="\0";
      params[1]="\0";
      params[2]="\0";
      params[3]="\0";
   }
}
#endif
