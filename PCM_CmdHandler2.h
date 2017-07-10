#define SOLCharacter '~'
#define EOLCharacter '\n'
#define ignoreCharacter 'Wr'
#define delimiterCharacter ','

#define recEmpty 0
#define recActive 1
#define recFull '#'
#define cmdReady recFull

#define noRecordFound 255

// All commands start with '~' and end with [CR]

//command set
/*------------------------------
command structure is as follows:
[startCharacter][cmd],[subcmd],[data][CR]
for example:
~sb,dft,ch0[CR]
set default biasses for channel 0

~sb,Pp,5.124
-------------------------------*/

// get code revision
#define getRevision "gr"         // returns code revision
#define getSerialNumber "gs"     // return MAC address
  
// Enable the power supplies   
#define setPowerEn   "se" // must include 0 or 1 for off or on
#define getPowerEn   "ge"
   #define pe_ch1    "ch1"
   #define pe_ch2    "ch2"
   #define pe_ch3    "ch3"
   #define pe_ch4    "ch4"
   #define pe_ch5    "ch5"
   #define pe_ch6    "ch6"
   #define pe_ch7    "ch7"
   #define pe_ch8    "ch8"
   #define pe_all    "all"
      #define pe_on     "on"
      #define pe_off    "off"
      #define pe_cycle  "cycle"

// Read port power
#define calVoltage   "calV"
#define calCurrent   "calC"
#define readVoltage  "rdV"
#define readCurrent  "rdC"
   #define rp_bus0            "bus0"
   #define rp_bus1            "bus1"
   #define rp_ch1             "ch1"
   #define rp_ch2             "ch2"
   #define rp_ch3             "ch3"
   #define rp_ch4             "ch4"
   #define rp_ch5             "ch5"
   #define rp_ch6             "ch6"
   #define rp_ch7             "ch7"
   #define rp_ch8             "ch8"
   #define rp_all             "all"
      // param[2] optional integer number for number of samples
         #define  rp_rawData        "rawData" //param[3] (read voltages only) 
      // params[2] and [3] contain floats for offset and gain for calibration 


// Read temperature, pressure
#define readEnvironment    "rdEnv"
#define calEnvironment     "calEnv"
   #define re_temp            "temp"
   #define re_pressure        "pres"
   #define re_all             "all"
     // param[2] optional integer number for number of samples
      #define re_rawData         "rawData" //param[3] optional to read raw data
     // params[2] and [3] contain floats for offset and gain for calibration 

#define saveCalData     "sCal"


// Port Masks ---
#define getMask         "gMask"
#define setMask         "sMask"
   #define gm_boot      "boot"
   #define gm_low       "low"

// Thresholds
#define getThreshold    "gThr"
#define setThreshold    "sThr"
   #define gt_batt      "batt"
   #define gt_low       "low"
   #define gt_auxLow    "auxLow"

// Ethernet Switch Settings

#define getEthernet     "gEth"
#define setEthernet     "sEth"
   // param 2 == regID
   // param 3 == byte value
  
// Serial Settings  
#define getSerial       "gSer"
#define setSerial       "sSer"
   //param2 baudrate... eg 9600
   //param3 bits parity stop... eg 8N1
   //param4 default timeout for response in ms... eg 500

   
// send serial data   
#define send_rs485      "@"   // command must start with '@'
#define send_rs232      "#"   // command must start with '#' 
   //param2 otional baud rate + optional data format + optional Timeout 
   //default is 9600_8n1
   #define ss_4800      "4800"
   #define ss_9600      "9600"
   #define ss_19200     "19200"
   #define ss_38400     "38400"
   #define ss_57600     "57600"
   #define ss_115200    "115200"
   
   #define ss_8n1       "_8n1"
   #define ss_8e1       "_8e1"
   #define ss_8o1       "_8o1"
   #define ss_8n2       "_8n2"
   #define ss_8e2       "_8e2"
   #define ss_8o2       "_8o2"
   
   //for optional timeout append T plus the time in ms (i.e. T2000)
   //example ~@,9600_8N1T2000,/1aM1P1000R
   
   // Param3 is data to send
   

// perform system reset
#define softReset       "reset"
   #define sr_system       "sys"
   #define sr_ethernet     "eth"
   //#define sr_peripherals  "per"
   
// get reason for last reboot and time since last boot
#define getRebootStatus  "gStatus"
   //response messages
   #define normal "Power on Reboot"
   #define watchdog "Watchdog Reboot"
   #define software "Soft Reboot"
   #define brownout "Brownout Reboot"
   #define external "MCLR Reboot"

   
/*****************************************************************************/
/* RESPONSE MESSAGES                                                            */
/*****************************************************************************/

#define badCmd          "INVALID COMMAND\n"
#define badParam        "INVALID PARAMETER\n"
#define badChannel      "INVALID CHANNEL\n"
#define outOfRange      "OUT OF RANGE\n"
#define overrun         "BUFFER OVERRUN\n"
#define success         "SUCCESS\n"
#define noResponse      "NO RESPONSE\n"
#define tbd             "NOT IMPLEMENTED YET\n"
