#ifndef _pcm_cmd
#define _pcm_cmd

#include <PCM_CmdHandler.h>
#include <PCM_EZHRTask.h>
#include <PCM_ADCTask.h>
#include <PCM_MACProm.h>
#include <PCM_Serial.h>

//////////////////////////////////////////////////////////////////////
/*********************************************************************
* executeCmd ROUTINE                                                 *
* Used to manege TCPIP communication... Hardware is Controlled       *
* via TCPIP                                                          *
*********************************************************************/
void executeCmd(char *cmd, TCP_SOCKET s)
{
   char command[2] = {NULL};
   char *data; //pointer to that start of cmd data
   //char ack[14] = "CMD FAILED"; // Acknowledge string
   unsigned int8 uID = 0;
   char retData[20]="Success";

//!   TICK_TYPE Tick_Start = TickGet();
   
   if (cmd[0] == startCharacter)
   {
      command[0] = cmd[1];
      command[1] = cmd[2];
      data = cmd+3;
      //printf(data);
   }

   /**************************************************************************/
   switch (command[0])
   {
   /**************************************************************************/
   case powerOff:               // Port Power Disable
      switch (command[1])
      {
      case pOffAll:
         output_low(CTRL_0);
         output_low(CTRL_1);
         output_low(CTRL_2);
         output_low(CTRL_3);
         output_low(CTRL_4);
         output_low(CTRL_5);
         output_low(CTRL_6);
         output_low(CTRL_7);
         break;
      case pOffPort1:
         output_low(CTRL_0);
         break;
      case pOffPort2:
         output_low(CTRL_1);
         break;
      case pOffPort3:
         output_low(CTRL_2);
         break;
      case pOffPort4:
         output_low(CTRL_3);
         break;
      case pOffPort5:
         output_low(CTRL_4);
         break;
      case pOffPort6:
         output_low(CTRL_5);
         break;
      case pOffPort7:
         output_low(CTRL_6);
         break;
      case pOffPort8:
         output_low(CTRL_7);
         break;
      default:
         sprintf(retData,"%s","Error: P_OFF");
         break;   
      }
      TCPPutArray(s,retData,strlen(retData));
      TCPFlush(s);
      break;
   /**************************************************************************/        
   case powerOn:               // Port Power enable
      switch (command[1])
      {
      case pOnAll:
         output_high(CTRL_0);
         output_high(CTRL_1);
         output_high(CTRL_2);
         output_high(CTRL_3);
         output_high(CTRL_4);
         output_high(CTRL_5);
         output_high(CTRL_6);
         output_high(CTRL_7);
         break;
      case pOnPort1:
         output_high(CTRL_0);
         break;
      case pOnPort2:
         output_high(CTRL_1);
         break;
      case pOnPort3:
         output_high(CTRL_2);
         break;
      case pOnPort4:
         output_high(CTRL_3);
         break;
      case pOnPort5:
         output_high(CTRL_4);
         break;
      case pOnPort6:
         output_high(CTRL_5);
         break;
      case pOnPort7:
         output_high(CTRL_6);
         break;
      case pOnPort8:
         output_high(CTRL_7);
         break;
      default:
         sprintf(retData,"%s","Error: P_ON");
         break; 
      }
      TCPPutArray(s,retData,strlen(retData));
      TCPFlush(s);
      break;
   /**************************************************************************/
   case write: // Write Functions
   char ezCmdTerminator[3]="R";
   ezCmdTerminator[1] = 0x0D;
   ezCmdTerminator[2] = NULL;
      switch (command[1])
      {
      case wrReg: // Write to Register
         uID = data[0]-49;
         unsigned int16 iValue = atoi(data+2);
         float fValue = atof(data+2);
         if(uID < numEZHR)                              
         {
            switch (data[1])
            {
            case wrRUnitScaler: // Write Unitscaler
               if (fValue !=0)
               {
                  ramEZHR[uID].unitScaler = fValue;
                  EZHRsettingsChanged = TRUE;
               }
               else
               {
                  sprintf(retData,"%s","Error: WR_US");
               }
               break;
            case wrRHoldCurrent: // Write Hold Current 
               if (iValue<=50)
               {
                  ramEZHR[uID].IHold = iValue;
                  EZHRsettingsChanged = TRUE;
                  data[1] ='h';
               }
               else
               {
                  sprintf(retData,"%s","Error: WR_HC");
               }
               break;
            case wrRSlowCurrent: // Write Slow Current
               if (iValue<=100)
               {
                  ramEZHR[uID].ISlow = iValue;
                  EZHRsettingsChanged = TRUE;
                  data[1] = 'l';
               }
               else
               {
                  sprintf(retData,"%s","Error: WR_SC");
               }
               break;
            case wrRFastCurrent: // Write Fast Current
               if (iValue<=100)
               {
                  ramEZHR[uID].IFast = iValue;
                  EZHRsettingsChanged = TRUE;
                  data[1]='m';
               }
               else
               {
                  sprintf(retData,"%s","Error: WR_FC");
               }
               break;
            case wrRAcceleration: // Write Accelleration Rate
               if (iValue>0 && iValue <=20)
               {
                  ramEZHR[uID].accRate = iValue;
                  EZHRsettingsChanged = TRUE;
                  data[1]='L';
               }
               else
               {
                  sprintf(retData,"%s","Error: WR_ACC");
               }
               break;
            case wrRStartRate: // Write Start Velocity
               if (iValue>=200 && iValue<=2500)
               {
                  ramEZHR[uID].vStart = iValue;
                  EZHRsettingsChanged = TRUE;
                  data[1]='v';
               }
               else
               {
                  sprintf(retData,"%s","Error: WR_SR");
               }
               break;
            case wrRRunRate: // Write Run Velocity
               if (iValue>=50 && iValue<=10000)
               {
                  ramEZHR[uID].vRun = iValue;
                  EZHRsettingsChanged = TRUE;
                  data[1]='V';
               }
               else
               {
                  sprintf(retData,"%s","Error: WR_RR");
               }
               break;
            case wrRStopRate: // Write Stop Velocity
               if (iValue>=200 && iValue<=2500)
               {
                  ramEZHR[uID].vStop = iValue;
                  EZHRsettingsChanged = TRUE;
                  data[1]='c';
               }
               else
               {
                  sprintf(retData,"%s","Error: WR_HR");
               }
               break;
            case wrRStepDivision: // Write Step Division
               switch (iValue)
               {
               case 2:
               case 4:
               case 8:
               case 16:
               case 32:
               case 64:
               case 128:
               case 256:
                  ramEZHR[uID].mStepDiv = iValue;
                  EZHRsettingsChanged = TRUE;
                  data[1]='j';
                  break;
               default:
                  sprintf(retData,"%s","Error: WR_SD");
               break;
               }
            default:
               sprintf(retData,"%s","Error: WR_SD");
               break;    
            } 
            if (EZHRsettingsChanged && data[1]!='0')
            {                     
               data = data-1;
               data[0] = '/';
               #ifdef ezhr4axis
               sprintf(cmd,"/1aM%cR\r",data[1]);
               serialGetS(cmd, 150, TRUE);
               data[1]='1';;
               #endif
               serialGetS(data,20,FALSE);
               strcat(data,ezCmdTerminator);
               serialGetS(data,20,TRUE);
               serialGetS(data,20,FALSE);             
            }
//!            serialSelect(e232);
//!            printf("%f ",ramEZHR[1].unitScaler);
//!            printf("%u ",ramEZHR[1].IHold);
//!            printf("%u ",ramEZHR[1].ISlow);
//!            printf("%u ",ramEZHR[1].IFast);
//!            printf("%u ",ramEZHR[1].accRate);
//!            printf("%Lu ",ramEZHR[1].vStart);
//!            printf("%Lu ",ramEZHR[1].vRun);
//!            printf("%Lu ",ramEZHR[1].vStop);
//!            printf("%Lu ",ramEZHR[1].mStepDiv);            
         }
         else
         {
            sprintf(retData,"%s","Error: WR_REG");
         }
         break;
      case wrRS232:             // Write to RS232    
         serialGetS(data, 200, FALSE);
         //TCPPutArray(s,retData,strlen(retData));
         //TCPFlush(s);
         break;
      case wrRS485:             // Write to RS485
         serialGetS(data, 200, FALSE);
         //TCPPutArray(s,retData,strlen(retData));
         //TCPFlush(s);
         break;
      case wrEthernetSwitch:              // Write to Micrel Register (eeProm)
         int8 micRegAdd = aHexWordToByte(data);
         if (micRegAdd <110)
         {
            int8 micRegData = aHexWordToByte(data+2);       
            eeWriteByte(micRegAdd, micRegData);
         }
         else
         {
            sprintf(retData,"%s","Error: WR_ETH");
         }
         break;
      case wrUDPdataRate:
         UDPSampleRate = (unsigned int8)data[0]*TICKS_PER_MILLISECOND;
         eeWriteUDPRate((int8)atoi(data));
         break;
      default: 
         sprintf(retData,"%s","Error: WR_REG");
         break;
      }   
      TCPPutArray(s,retData,strlen(retData));
      TCPFlush(s);
      break;
      
   case read:               // Read Functions
      switch (command[1])
      {
      case rdReg:             // Read from Register
         uID = data[0]-49;
         if(uID < numEZHR)  
         {
            switch (data[1])
            {
            case rdRUnitScaler: // Read Unitscaler
               sprintf(retData,"%.3f",ramEZHR[uID].unitScaler);
               TCPPutArray(s,retData,strlen(retData));
               TCPFlush(s);
               break;
            case rdRHoldCurrent: // Read Hold Current   
               sprintf(retData, "%u",ramEZHR[uID].IHold);
               TCPPutArray(s,retData,strlen(retData));
               TCPFlush(s);
               break;
            case rdRSlowCurrent: // Read Slow Current
               sprintf(retData,"%u",ramEZHR[uID].ISlow);
               TCPPutArray(s,retData,strlen(retData));
               TCPFlush(s);
               break;
            case rdRFastCurrent: // Read Fast Current
               sprintf(retData,"%u",ramEZHR[uID].IFast);
               TCPPutArray(s,retData,strlen(retData));
               TCPFlush(s);
               break;
            case rdRAcceleration: // Read Accelleration Rate
               sprintf(retData,"%u",ramEZHR[uID].accRate);
               TCPPutArray(s,retData,strlen(retData));
               TCPFlush(s);
               break;
            case rdRStartRate: // Read Start Velocity
               sprintf(retData,"%Lu",ramEZHR[uID].vStart);
               TCPPutArray(s,retData,strlen(retData));
               TCPFlush(s);
               break;
            case rdRRunRate: // Read Run Velocity
               sprintf(retData,"%Lu",ramEZHR[uID].vRun);
               TCPPutArray(s,retData,strlen(retData));
               TCPFlush(s);
               break;
            case rdRStopRate: // Read Stop Velocity
               sprintf(retData,"%Lu",ramEZHR[uID].vStop);
               TCPPutArray(s,retData,strlen(retData));
               TCPFlush(s);
               break;
            case rdRStepDivision: // Read Step Division
               sprintf(retData,"%Lu",ramEZHR[uID].mStepDiv);
               TCPPutArray(s,retData,strlen(retData));
               TCPFlush(s);
               break;
            default:
                sprintf(retData,"%s","Error: RD_REG");
                TCPPutArray(s,retData,strlen(retData));
                TCPFlush(s);
                break;
            }     
         }  
         else
         {
            sprintf(retData,"%s","Error: RD_REG");
            TCPPutArray(s,retData,strlen(retData));
            TCPFlush(s);
         }
         break; 
         
      case rdRS232:             // Read from RS232
         if (serialGetS(data, 300, FALSE))
         {
            TCPPutArray(s,UART_BUFFER,strlen(UART_BUFFER));
            TCPFlush(s);
         }
         else
         {
            sprintf(retData,"%s","Error: RD_232");
            TCPPutArray(s,retData,strlen(retData));
            TCPFlush(s);
         }
         break;
      case rdRS485:            // Read from RS485
         if (serialGetS(data, 300, TRUE))
         {
            TCPPutArray(s,UART_BUFFER,strlen(UART_BUFFER));
            TCPFlush(s);
         }
         else
         {
            sprintf(retData,"%s","Error: RD_485");
            TCPPutArray(s,retData,strlen(retData));
            TCPFlush(s);
         }
         break;
      case rdEthernetSwitch:
         char rData[3];
         int rInt=eeReadByte(aHexWordToByte(data));
         sprintf(rData,"%X",rInt);
         TCPPutArray(s,rData,3);
         TCPFlush(s);
         break;   
      case rdUDPdataRate:
         unsigned int8 rate = eeReadUDPRate();
         sprintf(retData,"%U",rate);
         TCPPutArray(s,retData,strlen(retData));
         TCPFlush(s);
         break;
      case rdResetStatus:
         sprintf(retData,"%U",resetStatus);
         TCPPutArray(s,retData,strlen(retData));
         TCPFlush(s);
         break;
      default:
         sprintf(retData,"%s","Error: RD");
         TCPPutArray(s,retData,strlen(retData));
         TCPFlush(s);
         break;
      }
      break;
   case homeEZHR:               // EZRH Homing
      uID = command[1]-48;
      if (uID<=numEZHR)
      {
         switch (command[1])
         {
         case homeAll:
            sprintf(data,"/_Z5000000R\r");
            serialGetS(data, 0, TRUE);
            ackGlobalCommand(s); // send an acknowledge that command was issued
            break;
         default:  
            #ifdef ezhr4axis
            sprintf(cmd,"/1aM%cR\r",command[1]);
            serialGetS(cmd, 150, TRUE);
            sprintf(data,"/1Z5000000R\r");
            #else
            sprintf(data,"/%cZ5000000R\r",command[1]);
            #endif
            //serialGetS(data, 30, TRUE); deleted in favor of returning a result
            ////printf("/%cZR\r",command[1]);
            if (serialGetS(data, 350, TRUE))
            {
               TCPPutArray(s,UART_BUFFER,strlen(UART_BUFFER));
               TCPFlush(s);
            }
            else
            {
               sprintf(retData,"%s","Error: HOME");
               TCPPutArray(s,retData,strlen(retData));
               TCPFlush(s);
            }
            break;
         }  
      }
      else
      {
         sprintf(retData,"%s","Error: HOME");
         TCPPutArray(s,retData,strlen(retData));
         TCPFlush(s);
      }
      break;
   case moveAbsEZHR:               // EZRH Move Absolute
      uID = command[1]-49;
      if (uID<numEZHR)
      {
         unsigned int32 absPosition;
         absPosition = (int32)(atof(data)* ((float)ramEZHR[uID].mStepDiv /  ramEZHR[uID].unitScaler));
         #ifdef ezhr4axis
         sprintf(data,"/1aM%cA%LuR\r",command[1],absPosition);
         StackTask();
         #else
         sprintf(data,"/%cA%LuR\r",command[1],absPosition);
         #endif
         //serialGetS(data,30,TRUE); removed - replaced with below to return result from motor driver
         if (serialGetS(data, 350, TRUE))
         {
            TCPPutArray(s,UART_BUFFER,strlen(UART_BUFFER));
            TCPFlush(s);
         } 
         else
         {
            sprintf(retData,"%s","Error: MOVE_ABS");
            TCPPutArray(s,retData,strlen(retData));
            TCPFlush(s);
         }
      }
      else
      {
         sprintf(retData,"%s","Error: MOVE_ABS");
         TCPPutArray(s,retData,strlen(retData));
         TCPFlush(s);
      }
      
      break;
   case runEZHR:               // EZRH Run 
      //serialSelect(e485TX);
      uID = command[1]-48;
      if (uID<=numEZHR)
      {
      switch (command[1])
         {
         case runAll:
            sprintf(data,"/_R\r");
            serialGetS(data, 0, TRUE);
            break;
         default:
            sprintf(data,"/%cR\r",command[1]);
            serialGetS(data, 0, TRUE);
            break;
         }
      }
      else
      {
         sprintf(retData,"%s","Error: RUN");
         TCPPutArray(s,retData,strlen(retData));
         TCPFlush(s);
      }
      
      break;
   case stopEZHR:   
      uID = command[1]-48;
      if (uID<=numEZHR)// EZHR Stop
      switch (command[1])
      {
      case stopAll:
         sprintf(data,"/_T\r");
         serialGetS(data, 0, TRUE);
         ackGlobalCommand(s);
         break;
      default:
         uID = command[1]-49;
         if (uID<numEZHR)
         {
            #ifdef ezhr4axis
            sprintf(cmd,"/1aM%cR\r",command[1]);
            serialGetS(cmd, 150, TRUE);
            StackTask();
            sprintf(data,"/1T\r");
            #else
            sprintf(data,"/%cT\r",command[1]);
            #endif
            if (serialGetS(data,350,TRUE))
            {
               TCPPutArray(s,UART_BUFFER,strlen(UART_BUFFER));
               TCPFlush(s);
            }
           else
           {
              sprintf(retData,"%s","Error: STOP");
              TCPPutArray(s,retData,strlen(retData));
              TCPFlush(s);
           }
         }
         break;
      }
      else
      {
         sprintf(retData,"%s","Error: STOP");
         TCPPutArray(s,retData,strlen(retData));
         TCPFlush(s);
      }
      //serialSelect(e485TX);
      break;

   
   case reset:               // Resets
      switch (command[1])
      {
      case resetSystem: // Reset the system
         reset_cpu();
         break;
      case resetEthernet: // Reset the Ethernet switch only
         reset_cpu(); // soft reset (ports remain powered)
         break;
      default:   
         sprintf(retData,"%s","Error: RESET");
         TCPPutArray(s,retData,strlen(retData));
         TCPFlush(s);
      }
      break;
      
   case dataManagement:               // Parameter Data
      switch (command[1])
      {
      case saveEZHRParams: // Save
         saveEZHRtoROM();
         break;
      case loadEZHRParams: // Load
         loadEZHRfromROM();
         break;
      default:
         sprintf(retData,"%s","Error: DATA_MGMT");
         break;
      }
      TCPPutArray(s,retData,strlen(retData));
      TCPFlush(s);
      break;
   
   default:
      sprintf(retData,"%s","Error: CMD");
      TCPPutArray(s,retData,strlen(retData));
      TCPFlush(s);
      break;
   }
}
//////////////

#endif
