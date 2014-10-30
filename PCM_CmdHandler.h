#define startCharacter '~'
#define endCharacter '\n'
#define delimiterCharacter ','

#define recEmpty 0
#define recActive 1
#define recFull '#'
#define cmdReady recFull

#define noRecordFound 255

// All commands start with '~' and end with [CR]

// POWER OFF example: 
// ~01[CR]  //power off port 1
// ~00[CR]  //power off all ports
#define powerOff              '0'
   #define pOffAll            '0'
   #define pOffPort1          '1'
   #define pOffPort2          '2'
   #define pOffPort3          '3'
   #define pOffPort4          '4'
   #define pOffPort5          '5'
   #define pOffPort6          '6'
   #define pOffPort7          '7'
   #define pOffPort8          '8' 
   
// POWER ON example: 
// ~11[CR]  //power on port 1
// ~10[CR]  //power on all ports
#define powerOn               '1'
   #define pOnAll             '0'
   #define pOnPort1           '1'
   #define pOnPort2           '2'
   #define pOnPort3           '3'
   #define pOnPort4           '4'
   #define pOnPort5           '5'
   #define pOnPort6           '6'
   #define pOnPort7           '7'
   #define pOnPort8           '8'  
   
// WRITE example:
// write register... ~201025[CR] //write to register, drive 1, reg 0, value5
// write to RS485... ~22[payload][CR] // write payload to RS485
#define write                 '2'
   #define wrReg              '0'   // EZHR registers
      #define wrRUnitScaler   '0'
      #define wrRHoldCurrent  '1'
      #define wrRSlowCurrent  '2'
      #define wrRFastCurrent  '3'
      #define wrRAcceleration '4'
      #define wrRStartRate    '5'
      #define wrRRunRate      '6'
      #define wrRStopRate     '7'
      #define wrRStepDivision '8'
   #define wrRS232            '1'
   #define wrRS485            '2'
   #define wrEthernetSwitch   '3'
   #define wrUDPdataRate      '4'
      
// WRITE example:
// write register... ~3010[CR] //read from register, drive 1, reg 0
// write to RS485... ~32[command][CR] // request data from RS485      
#define read                  '3'
   #define rdReg              '0'
      #define rdRUnitScaler   '0'
      #define rdRHoldCurrent  '1'
      #define rdRSlowCurrent  '2'
      #define rdRFastCurrent  '3'
      #define rdRAcceleration '4'
      #define rdRStartRate    '5'
      #define rdRRunRate      '6'
      #define rdRStopRate     '7'
      #define rdRStepDivision '8'
   #define rdRS232            '1'
   #define rdRS485            '2'
   #define rdEthernetSwitch   '3' 
   #define rdUDPdataRate      '4'
   #define rdResetStatus      '5'
   
#define homeEZHR              '4'
   #define homeAll            '0'
   
#define moveAbsEZHR           '5'

#define runEZHR               '6'
   #define runAll             '0'

#define stopEZHR              '7'
   #define stopAll            '0'

#define reset                 'R'
   #define resetSystem        '0'
   #define resetEthernet      '1'
   
#define dataManagement        'D'
   #define loadEZHRParams     'L'
   #define saveEZHRParams     'S'
   
   
   
   
