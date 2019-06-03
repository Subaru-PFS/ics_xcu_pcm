#ifndef _PCM_serial
#define _PCM_serial

typedef enum {e232, e485TX, e485RX}port;
#define UART_BUFFER_SIZE 60
#define UART_EOT_CHAR  0x03 //ETX
#define UART_EOT_CHAR1 0x0D //Carriage Return
#define UART_EOT_CHAR2 0x0A //Line Feed
#define UART_SOT_CHAR  0xFF //Line turnaround
#define line_turnaround_char 0xFF
//#define UART_IGNORE_CHAR1 '' //0x60
//#define UART_IGNORE_CHAR2 0
//#define UART_SOT_CHAR 0x60 

#bit UART_TXBuffer_Empty = 0x0FAC.1
char UART_BUFFER[UART_BUFFER_SIZE] = {0};
unsigned int8 UART_BUFFER_PTR = UART_BUFFER_SIZE;
BOOL UART_BUFFER_OVERFLOW = FALSE; 
BOOL UART_GOT_STRING = FALSE;
char rxChar = NULL;

//#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,restart_wdt)

#use rs232(parity=E,xmit=PIN_C6,rcv=PIN_C7,bits=8,restart_wdt,stream=STR8E1)
#use rs232(parity=O,xmit=PIN_C6,rcv=PIN_C7,bits=8,restart_wdt,stream=STR8O1)
#use rs232(parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,restart_wdt,stream=STR8N1)
#use rs232(parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stop=2,restart_wdt,stream=STR8N2)
#use rs232(parity=E,xmit=PIN_C6,rcv=PIN_C7,bits=8,stop=2,restart_wdt,stream=STR8E2)
#use rs232(parity=O,xmit=PIN_C6,rcv=PIN_C7,bits=8,stop=2,restart_wdt,stream=STR8O2)

// UART RX Data Interupt ////////////////////////////////////////////////
#int_RDA
void  RDA_isr() 
{
   while(kbhit())
   {  
      rxChar = getch();
      if(UART_BUFFER_PTR<UART_BUFFER_SIZE-1)
      {
         switch (rxChar)
         {
            case UART_EOT_CHAR:
            case UART_EOT_CHAR1:
            case UART_EOT_CHAR2: // CAPTURE COMPLETE
               UART_BUFFER_PTR=UART_BUFFER_SIZE;//disable capture
               UART_GOT_STRING = TRUE;
               break;
            case UART_SOT_CHAR: // START OF TEXT, RESET POINTER
               UART_BUFFER_PTR=0; // reset start of text loacation
               UART_BUFFER[UART_BUFFER_PTR] = NULL;// null terminate string
               break;
            default: // ADD CHARACTER TO BUFFER AND NULL TERMINATE
               UART_BUFFER[UART_BUFFER_PTR]=rxChar;
               UART_BUFFER_PTR+=1;
               UART_BUFFER[UART_BUFFER_PTR]=NULL; // null terminate string
               break;
         }   
      }
   }
}   
      
//!      
//!      
//!      
//!      
//!      if(UART_BUFFER_PTR < UART_BUFFER_SIZE) // if ptr = size then do nothing
//!      {
//!         //UART_BUFFER[UART_BUFFER_PTR] = getch();
//!         
//!         if (UART_BUFFER[UART_BUFFER_PTR] == UART_EOT_CHAR || UART_EOT_CHAR2) //|| UART_BUFFER[UART_BUFFER_PTR] == ASCII_ETX) 
//!         {
//!
//!            UART_BUFFER[UART_BUFFER_PTR] = NULL;
//!            UART_GOT_STRING = TRUE;
//!            UART_BUFFER_PTR = UART_BUFFER_SIZE; //set ptr = size
//!         }
//!         else if (UART_BUFFER[0] == '/')
//!         {
//!            UART_BUFFER_PTR+=1;
//!            if (UART_BUFFER_PTR >= UART_BUFFER_SIZE-2)
//!            {
//!               UART_BUFFER[UART_BUFFER_PTR+1] = NULL;
//!               UART_GOT_STRING = TRUE;
//!               UART_BUFFER_PTR = UART_BUFFER_SIZE; //set ptr = size
//!            }
//!         }
//!      }
//!      else
//!      {
//!         getch(); // discard incoming data
//!      }  
//!    }   
//!}

//////////////////////////////////////////////////////////////////////  
/*********************************************************************
* serialInit ROUTINE                                                 *
* Sets up serial port                                                *
*********************************************************************/
//////////////////////////////////////////////////////////////////////  
void SerialInit()
{
   enable_interrupts(INT_RDA);
   output_low(RS485_TXEN);
   output_high(RS485_RXDIS);
   output_high(RS232_F_OFF);
   output_high(RS232_F_ON);
}

//////////////////////////////////////////////////////////////////////  
/*********************************************************************
* serialSelectROUTINE                                                *
* Select 232 or 485                                                  *
*********************************************************************/
void serialSelect(port p)
{
   if (p == e232)
   {
      while (!UART_TXBuffer_Empty){restart_wdt();}// do not switch until TX buffer is empty
      output_low(RS485_TXEN); // Disable RS485
      output_high(RS485_RXDIS);
      output_high(RS232_F_ON); //enable RS232
      output_high(RS232_F_OFF);
   }    
   else if (p == e485TX)
   {
      while (!UART_TXBuffer_Empty){restart_wdt();}
      output_low(RS232_F_OFF); // Disable RS32
      output_low(RS232_F_ON);
      output_high(RS485_RXDIS);
      output_high(RS485_TXEN); // Enable RS485 to send
      printf(line_turnaround_char);
   }
   else
   {
      if (RS485_TXEN)
      {
         printf(line_turnaround_char);
      }
      while (!UART_TXBuffer_Empty){restart_wdt();}
      output_low(RS232_F_OFF); // Disable RS32
      output_low(RS232_F_ON);
      output_low(RS485_RXDIS);
      output_low(RS485_TXEN); // Enable RS485 to recieve
   }
}
//////////////////////////////////////////////////////////////////////
BOOL validateChkSum(char *cmd)
{
   return (TRUE);
}
//////////////////////////////////////////////////////////////////////
//char calcChkSum (char *str){
//////////////////////////////////////////////////////////////////////
/*********************************************************************
* SerialGetS ROUTINE                                                 *
* Requests Data on RS485...                                          *
* putStr is the data Request String                                  *
* TO_Ticks is the time in 10ms intervals to wait for a response      *
* Return TRUE if response recieved                                   *
* Reponse String is in UART_BUFFER                                   *
*********************************************************************/  

BOOL serialGetS(char *putStr, TICK_TYPE TO_Ticks, BOOL RS485)
{
   //TO_Ticks *=TICKS_PER_MILLISECOND;
   output_high(U_ACT);
   
   UART_GOT_STRING = FALSE;
   UART_BUFFER_PTR = 0; // reset the pointer to allow packet receipt
   UART_BUFFER[0]=0;
   
   if(RS485)
   {
      serialSelect(e485TX);
      delay_us(1000);
      printf("%s",putStr);
      delay_us(100);
      serialSelect(e485RX);
   }
   else
   {
      serialSelect(e232);
      delay_us(500);
      printf("%s",putStr);
   }
   
   TICK_TYPE Tick_Start = TickGet();
   
   while ((TickGetDiff(TickGet(), Tick_Start) 
   <= TO_Ticks) && !UART_GOT_STRING)
   {
      StackTask();
   }
   
   UART_BUFFER_PTR = UART_BUFFER_SIZE; // Disable rx data
   output_low(U_ACT);
   return(UART_GOT_STRING);  
}

BOOL serialGetSs(char* putStr, char* retStr, unsigned int32 TO_Ticks, BOOL RS485)
{
   TO_Ticks *= TICKS_PER_MILLISECOND;
   output_high(U_ACT);
   
   UART_GOT_STRING = FALSE;
   UART_BUFFER_PTR = 0; // reset the pointer to allow packet receipt
   UART_BUFFER[0]=0;
   
   if(RS485)
   {
      serialSelect(e485TX);
      delay_us(1000);
      printf("%s\r\n",putStr);
      delay_us(100);
      serialSelect(e485RX);
   }
   else
   {
      serialSelect(e232);
      delay_us(500);
      printf("%s\r\n",putStr);
   }
   
   unsigned int32 Tick_Start = TickGet();
   BOOL timeout = FALSE;
   while (!timeout && !UART_GOT_STRING)
   {
      StackTask();
      unsigned int32 expiredTicks = TickGet()-Tick_Start;
      if (expiredTicks > (unsigned int32)TO_Ticks ) timeout = TRUE;   
   }
   
   if(UART_GOT_STRING)
   {
      UART_BUFFER_PTR = UART_BUFFER_SIZE; // Disable rx data
      strcpy(retStr,UART_BUFFER);
   }
   else
   {
      strcpy(retStr,"\0");
   }
   output_low(U_ACT);
   return(UART_GOT_STRING);  
}
   

#endif
