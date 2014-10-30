#ifndef _pcm_portdefinitions
#define _pcm_portdefinitions

// OUTPUT DEFINITIONS
#define E_LED_ACT    PIN_A0   //Ethernet LEDS
#define E_LED_LINK   PIN_A1   
#define RS485_TXEN   PIN_A5   //RS485 transmit enable
#define MUX_0        PIN_B0   //Multiplexer select lines
#define MUX_1        PIN_B1 
#define MUX_2        PIN_B2
#define MUX_3        PIN_B3
#define E_SW_PWR_DN  PIN_B4   //Ethernet switch control
#define E_SW_RST     PIN_B5
#define RS485_RXDIS  PIN_C0   //RS485 receive enable
#define U_ACT        PIN_C5   //UART activity LED/General purpose LED
#define CTRL_1       PIN_D0   //Port 6 power control
#define CTRL_0       PIN_D1   //Port 7 power control
#define CTRL_7       PIN_E0   //Port 0 power control
#define CTRL_6       PIN_E1   //Port 1 power control
#define CTRL_5       PIN_E2   //Port 2 power control
#define CTRL_4       PIN_E3   //Port 3 power control
#define CTRL_3       PIN_E4   //Port 4 power control
#define CTRL_2       PIN_E5   //Port 5 power control
#define RS232_F_ON   PIN_F7   //Force RS 232 driver on
#define RS232_F_OFF  PIN_G4   //Force RS 232 driver off

// INPUT DEFINITIONS
#define RS232_RDY      PIN_C2   //RS232 line driver ready

// ANALOG DEFINITIONS
#define MUX_IN       PIN_A2   //Analog MUX input
#define A_REF        PIN_A3   //Analog reference
#define PSIA         PIN_F1   //Analog pressure transducer
#define TEMPERATURE  PIN_F2   //Analog temperature transducer
#define LOW_CURRENT  PIN_F3   //Analog current, 12V supply
#define HIGH_CURRENT PIN_F4   //Analog current, 36V supply
#define LOW_VOLTAGE  PIN_F5   //Analog voltage, 12V supply
#define HIG_VOLTAGE  PIN_F6   //Analog voltage, 36V supply

// UNUSED IO PINS
/*
PIN_A4   N/C
PIN_B6   ICD PGC pin
PIN_B7   ICD DATA pin
PIN_C1   N/C
PIN_D2   ICD DIAGNOSTIC pin
*/

// INITIAL TRIS DEFINITIONS - 0 sets pin as output
#define TRIS_A       0b11001100
#define TRIS_B       0b11000000
#define TRIS_C       0b11011100
#define TRIS_D       0b11111100
#define TRIS_E       0b11000000
#define TRIS_F       0b01111111
#define TRIS_G       0b11101111

// INITIAL PORT VALUES
#define INIVAL_A     0b00000000
#define INIVAL_B     0b00000000 // hold ethernet switch in reset state
#define INIVAL_C     0b00000000
#define INIVAL_D     0b00000000
#define INIVAL_E     0b00000000
#define INIVAL_F     0b10000000  //enable RS232 driver
#define INIVAL_G     0b00010000

/*********************************************************************  
* PortInit ROUTINE                                                    *
* Select 232 or 485                                                  *
*********************************************************************/

void PortInit()
{
   set_tris_a(TRIS_A);  // set initial IO pin direction
   set_tris_b(TRIS_B);
   set_tris_c(TRIS_C);
   set_tris_d(TRIS_D);
   set_tris_e(TRIS_E);
   set_tris_f(TRIS_F);
   set_tris_g(TRIS_G);
}      
void OutputInit() 
{
   output_a(INIVAL_A);  //set initial output pin values
   output_b(INIVAL_B);
   output_c(INIVAL_C);
   output_d(INIVAL_D);
   output_e(INIVAL_E);
   output_f(INIVAL_F);
   output_g(INIVAL_G);    
}
#endif
