#IFNDEF _pcm_mac
#DEFINE _pcm_mac

#include <stddef.h>
#include <stdlib.h>

#define I2C_SCL   PIN_C3
#define I2C_SDA   PIN_C4

//!#define lvMaskAdd 112
//!#define strMaskAdd 113
//!#define pwrMaskAdd 114
//!#define lvThreshold 116

#use i2c(MULTI_MASTER,sda=PIN_C4,scl=PIN_C3,FORCE_HW,SLOW,RESTART_WDT)

//!// Default ROM Settings for Micrel Switch
//!const unsigned int8 defaultROMSettings[]=
//!{
//!0x95,0x00,0x4C,0x04,    // Global Switch Settings (reg 0 - 15)
//!0xF0,0x00,0x00,0x4A,
//!0x24,0x28,0x24,0x00,
//!0x00,0x00,0x00,0x00,
//!
//!0x00,0x1F,0x06,0x00,    // Port 1 Switch Settings (reg 16 - 31)
//!0x01,0x00,0x00,0x00,
//!0x00,0x00,0x00,0x00,
//!0x5F,0x00,0x00,0x00,
//!
//!0x00,0x1F,0x06,0x00,    // Port 2 Switch Settings (reg 32 - 47)
//!0x01,0x00,0x00,0x00,
//!0x00,0x00,0x00,0x00,
//!0x5F,0x00,0x00,0x00,
//!
//!0x00,0x1F,0x06,0x00,    // Port 3 Switch Settings (reg 48 - 63)
//!0x01,0x00,0x00,0x00,
//!0x00,0x00,0x00,0x00,
//!0x5F,0x00,0x00,0x00,
//!
//!0x00,0x1F,0x06,0x00,    // Port 4 Switch Settings (reg 64 - 79)
//!0x01,0x00,0x00,0x00,
//!0x00,0x00,0x00,0x00,
//!0x5F,0x00,0x00,0x00,
//!
//!0x00,0x1F,0x06,0x00,    // Port 5 Switch Settings (reg 80 - 95)
//!0x01,0x00,0x00,0x00,
//!0x00,0x00,0x00,0x00,
//!0x5F,0x00,0x00,0x00,
//!
//!0x00,0x00,0x00,0x00,    // Advanced Control Settings (reg 96 - 109)
//!0x00,0x00,0x00,0x00,
//!0x00,0x10,0xA1,0xFF,
//!0xFF,0xFF,0x00,0x00,    // 110 - 111, Unused Bytes
//!
//!0x0F,0x0F,0x83,0x08,    // LVMask,StrobeMask,PowerUpMask, Spare
//!0x8F,0x71,0x83,0x3C,    // LVThreshold
//!0x8F,0x71,0x83,0x20,
//!0x8F,0x71,0x00,0x50     // last byte contains refresh rate
//!};
//!
//!struct eedata
//!   {  unsigned int8 micrelReg[112];
//!      unsigned int8 LVmask;int8 PUmask;
//!      float LVThreshold;   
//!      float onBattThreshold;
//!      float ch2Threshold;
//!      unsigned int8 unused;
//!      unsigned int8 refreshRate;
//!   };
   
union
{   
   struct eedata
   {  unsigned int8 micrelReg[112];
      unsigned int8 LVmask;
      unsigned int8 PUmask;
      float LVThreshold;   
      float onBattThreshold;
      float ch2Threshold;
      unsigned int8 unused;
      unsigned int8 refreshRate;
   }eeData;
   unsigned int8 intData[128];   
}eeRAMcopy= {{{
            0x95,0x00,0x4C,0x04,    // Global Switch Settings (reg 0 - 15)
            0xF0,0x00,0x00,0x4A,
            0x24,0x28,0x24,0x00,
            0x00,0x00,0x00,0x00,
            
            0x00,0x1F,0x06,0x00,    // Port 1 Switch Settings (reg 16 - 31)
            0x01,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,
            0x5F,0x00,0x00,0x00,
            
            0x00,0x1F,0x06,0x00,    // Port 2 Switch Settings (reg 32 - 47)
            0x01,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,
            0x5F,0x00,0x00,0x00,
            
            0x00,0x1F,0x06,0x00,    // Port 3 Switch Settings (reg 48 - 63)
            0x01,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,
            0x5F,0x00,0x00,0x00,
            
            0x00,0x1F,0x06,0x00,    // Port 4 Switch Settings (reg 64 - 79)
            0x01,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,
            0x5F,0x00,0x00,0x00,
            
            0x00,0x1F,0x06,0x00,    // Port 5 Switch Settings (reg 80 - 95)
            0x01,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,
            0x5F,0x00,0x00,0x00,
            
            0x00,0x00,0x00,0x00,    // Advanced Control Settings (reg 96 - 109)
            0x00,0x00,0x00,0x00,
            0x00,0x10,0xA1,0xFF,
            0xFF,0xFF,0x00,0x00},   // 110 - 111, Unused Bytes
            
            0b01010101,        // Low Voltage Mask
            0b00000100,            // PU Mask
            18.0,                   // Low Voltage Threshold
            23.5,                   // On Battery Threshold
            22.0,                   // channel 2 low voltage threshold
            0x00,                   // unused
            0x50                    // last byte contains refresh rate
            }};


// Converts single ascii Hex character (0 thru 9, A (or a) thru F (or f) to byte
int8 aHexCharToByte(char asciiByte)
{
   
   int8 result = 0;
   if (asciiByte >= 48 && asciiByte <58) // 0 thru 9
   {
      result = asciiByte - 48;
   }
   else if (asciiByte >= 65 && asciiByte <71) // A thru F
   {
      result = asciiByte - 55;
   }
   else if (asciiByte >= 97 && asciiByte <103) // a thru f
   {
      result = asciiByte - 87;
   }
   else
   {
      result = 0;
   }
   return result;
}

// converts hex word to byte... uses aHexChartoByte
int8 aHexWordToByte(char *asciiWord)
{
   int8 result = aHexCharToByte(*asciiWord);
   result = result<<4;
   asciiWord+=1;
   result += aHexCharToByte(*asciiWord);
   return result;
}

// readByte
unsigned int8 eeReadByte(unsigned int8 address)
{
   i2c_start();
   i2c_write(0xA0);     // Device address
   i2c_write(address);     // Read address location
   i2c_start();         // Restart
   i2c_write(0xA1);     // to change data direction
   unsigned int8 data = i2c_read(0);
   i2c_stop();
   delay_us(500);
   return data;
}

float eeReadFloat(unsigned int8 address)
{
   union tempData 
   {
      float flt;
      int8  chr[4];
   }tempData;   
   for (int i=0;i<4;i++)
   {
      tempData.chr[i]=eeReadByte(address+i);
   }   
   return tempData.flt;   
}

void eeCopyROMtoRAM()
{  
   i2c_start();
   i2c_write(0xA0);     // Device address
   i2c_write(0x00);     // Set address point
   i2c_start();         // Restart
   i2c_write(0xA1);     // Set to read
   int8 i=0;
   for(i=0;i<127; i++)
   {
      eeRAMcopy.intData[i]=i2c_read(1);
      //delay_us(50);
   }
   eeRAMcopy.intData[i]=i2c_read(0);;
   i2c_stop();
   delay_us(500);
}   

// copies the RAM copy to ROM
void eeSaveRAMtoROM()
{
   for(int8 i=0;i<128; i+=8)
   {
      i2c_start();
      i2c_write(0xA0);     // Device address
      i2c_write(i); 
      for(int8 j=0;j<=7;j++)
      {
         i2c_write(eeRAMcopy.intData[i+j]);         // 
      }
      i2c_stop();
      delay_ms(20);
   }
}

//*****************************************************************************
void eeWriteByte(unsigned int8 Address, unsigned int8 Data)
{
   restart_wdt();
   i2c_start();
   i2c_write(0xA0);     // Device address
   i2c_write(Address);  // write address location
   i2c_write(Data);         // 
   i2c_stop();
   delay_ms(20);
}
//*****************************************************************************
void eeWriteFloat (int8 Address, float Data)
{
   union tempData 
   {
      float flt;
      char  chr[4];
   }tempData;  
   tempData.flt=Data;
   for (int i=0;i<4;i++)
   {
      eeWriteByte(Address+i,tempData.chr[i]);
   }   
}   
//******************************************************************************
// get Node Name from EEPROM for DHCP request
void eeGetMACAddress(int8& pData)
{
   i2c_start();
   i2c_write(0xA0);     // Device address
   i2c_write(0xFA);     // Set address point
   i2c_start();         // Restart
   i2c_write(0xA1);     // Set to read
   int8 i=0;
   for (i=0; i<5; i++)
   {
      *(&pData+i)=i2c_read(1);
   }
   *(&pData+i)=i2c_read(0);
   i2c_stop();
}

// initilaize Rom with defualt Micrel Settings
void eeROMinit()
{
   if (eeReadByte(0)!=0x95)
   {
      eeSaveRAMtoROM();  
   }
   else
   {
      eeCopyROMtoRAM();
   }    
}

void eeWriteUDPRate (unsigned int8 rate_ms)
{
   eeWriteByte(127, rate_ms);
}

unsigned int8 eeReadUDPRate()
{
   return eeReadByte(127);
}

#ENDIF
