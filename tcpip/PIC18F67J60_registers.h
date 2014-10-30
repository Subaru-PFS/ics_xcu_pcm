#byte TOSU = 0xFFF

#word TOS = 0xFFD
#byte TOSH = 0xFFE
#byte TOSL = 0xFFD

typedef union 
 {
   union {
      struct {
         unsigned int STKPTR0:5;
         unsigned int :1;
         unsigned int STKUNF:1;
         unsigned int STKFUL:1;
      };
      struct {
         unsigned int STKPTR:5;
      };

      struct {
         unsigned int :7;
         unsigned int STKOVF:1;
      };
   };
} STKPTRBITS;
STKPTRBITS STKPTRbits;
#byte STKPTRbits = 0xFFC
#byte STKPTR = 0xFFC

#byte PCLATU = 0xFFB

#byte PCLATH = 0xFFA

#byte PCL = 0xFF9

typedef union 
 {
      struct {
         unsigned int TBLPTRU0:5;
         unsigned int ACSS:1;
      };
      struct {
         unsigned int TBLPTRU:5;
      };
} TBLPTRUBITS;
TBLPTRUBITS TBLPTRUbits;
#byte TBLPTRUbits = 0xFF8
#byte TBLPTRU = 0xFF8

#word TBLPTR = 0xFF6
#byte TBLPTRH = 0xFF7
#byte TBLPTRL = 0xFF6

#byte TABLAT = 0xFF5

#word PROD = 0xFF3
#byte PRODH = 0xFF4
#byte PRODL = 0xFF3

typedef struct 
 {
   union {
      struct {
         unsigned int :1;
         unsigned int INT0F:1;
         unsigned int T0IF:1;
         unsigned int :1;
         unsigned int INT0E:1;
         unsigned int T0IE:1;
         unsigned int GIEL:1;
         unsigned int GIEH:1;
      };

   union {
      struct {
         unsigned int :6;
         unsigned int PEIE:1;
         unsigned int GIE:1;
      };
   };

      struct {
         unsigned int RBIF:1;
         unsigned int INT0IF:1;
         unsigned int TMR0IF:1;
         unsigned int RBIE:1;
         unsigned int INT0IE:1;
         unsigned int TMR0IE:1;
         unsigned int PEIE_GIEL:1;
         unsigned int GIE_GIEH:1;
      };
   };
} INTCONBITS;
INTCONBITS INTCONbits;
#byte INTCONbits = 0xFF2
#byte INTCON = 0xFF2

typedef union 
 {
   union {
      struct {
         unsigned int RBIP:1;
         unsigned int INT3IP:1;
         unsigned int TMR0IP:1;
         unsigned int INTEDG3:1;
         unsigned int INTEDG2:1;
         unsigned int INTEDG1:1;
         unsigned int INTEDG0:1;
         unsigned int RBPU:1;
      };
      struct {
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int INTEDG:4;
      };

      struct {
         unsigned int :2;
         unsigned int T0IP:1;
      };
   };
} INTCON2BITS;
INTCON2BITS INTCON2bits;
#byte INTCON2bits = 0xFF1
#byte INTCON2 = 0xFF1

typedef struct 
 {
   union {
      struct {
         unsigned int INT1F:1;
         unsigned int INT2F:1;
         unsigned int INT3F:1;
         unsigned int INT1E:1;
         unsigned int INT2E:1;
         unsigned int INT3E:1;
         unsigned int INT1P:1;
         unsigned int INT2P:1;
      };

      struct {
         unsigned int INT1IF:1;
         unsigned int INT2IF:1;
         unsigned int INT3IF:1;
         unsigned int INT1IE:1;
         unsigned int INT2IE:1;
         unsigned int INT3IE:1;
         unsigned int INT1IP:1;
         unsigned int INT2IP:1;
      };
   };
} INTCON3BITS;
INTCON3BITS INTCON3bits;
#byte INTCON3bits = 0xFF0
#byte INTCON3 = 0xFF0

#byte INDF0 = 0xFEF

#byte POSTINC0 = 0xFEE

#byte POSTDEC0 = 0xFED

#byte PREINC0 = 0xFEC

#byte PLUSW0 = 0xFEB

#word FSR0 = 0xFE9
#byte FSR0H = 0xFEA
#byte FSR0L = 0xFE9

#byte WREG = 0xFE8

#byte INDF1 = 0xFE7

#byte POSTINC1 = 0xFE6

#byte POSTDEC1 = 0xFE5

#byte PREINC1 = 0xFE4

#byte PLUSW1 = 0xFE3

#word FSR1 = 0xFE1
#byte FSR1H = 0xFE2
#byte FSR1L = 0xFE1

#byte BSR = 0xFE0

#byte INDF2 = 0xFDF

#byte POSTINC2 = 0xFDE

#byte POSTDEC2 = 0xFDD

#byte PREINC2 = 0xFDC

#byte PLUSW2 = 0xFDB

#word FSR2 = 0xFD9
#byte FSR2H = 0xFDA
#byte FSR2L = 0xFD9

typedef struct 
 {
   unsigned int C:1;
   unsigned int DC:1;
   unsigned int Z:1;
   unsigned int OV:1;
   unsigned int N:1;
} STATUSBITS;
STATUSBITS STATUSbits;
#byte STATUSbits = 0xFD8
#byte STATUS = 0xFD8

#word TMR0 = 0xFD6
#byte TMR0H = 0xFD7
#byte TMR0L = 0xFD6

typedef union 
 {
      struct {
         unsigned int T0PS0:3;
         unsigned int PSA:1;
         unsigned int T0SE:1;
         unsigned int T0CS:1;
         unsigned int T08BIT:1;
         unsigned int TMR0ON:1;
      };
      struct {
         unsigned int T0PS:3;
      };
} T0CONBITS;
T0CONBITS T0CONbits;
#byte T0CONbits = 0xFD5
#byte T0CON = 0xFD5

typedef union 
 {
      struct {
         unsigned int SCS0:2;
         unsigned int :1;
         unsigned int OSTS:1;
         unsigned int :3;
         unsigned int IDLEN:1;
      };
      struct {
         unsigned int SCS:2;
         unsigned int :1;
         unsigned int :1;
         unsigned int :3;
      };
} OSCCONBITS;
OSCCONBITS OSCCONbits;
#byte OSCCONbits = 0xFD3
#byte OSCCON = 0xFD3

typedef struct 
 {
   unsigned int :2;
   unsigned int RXEN:1;
   unsigned int TXRTS:1;
   unsigned int CSUMEN:1;
   unsigned int DMAST:1;
   unsigned int RXRST:1;
   unsigned int TXRST:1;
} ECON1BITS;
ECON1BITS ECON1bits;
#byte ECON1bits = 0xFD2
#byte ECON1 = 0xFD2

typedef struct 
 {
   union {
      struct {
         unsigned int SWDTE:1;
      };

      struct {
         unsigned int SWDTEN:1;
      };
   };
} WDTCONBITS;
WDTCONBITS WDTCONbits;
#byte WDTCONbits = 0xFD1
#byte WDTCON = 0xFD1

typedef struct 
 {
   unsigned int BOR:1;
   unsigned int POR:1;
   unsigned int PD:1;
   unsigned int TO:1;
   unsigned int RI:1;
   unsigned int :2;
   unsigned int IPEN:1;
} RCONBITS;
RCONBITS RCONbits;
#byte RCONbits = 0xFD0
#byte RCON = 0xFD0

#word TMR1 = 0xFCE
#byte TMR1H = 0xFCF
#byte TMR1L = 0xFCE

typedef union 
 {
   union {
      struct {
         unsigned int TMR1ON:1;
         unsigned int TMR1CS:1;
         unsigned int T1SYNC:1;
         unsigned int T1OSCEN:1;
         unsigned int T1CKPS0:2;
         unsigned int T1RUN:1;
         unsigned int RD16:1;
      };
      struct {
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int T1CKPS:2;
      };

      struct {
         unsigned int :2;
         unsigned int T1INSYNC:1;
      };
   };
} T1CONBITS;
T1CONBITS T1CONbits;
#byte T1CONbits = 0xFCD
#byte T1CON = 0xFCD

#byte TMR2 = 0xFCC

#byte PR2 = 0xFCB

typedef union 
 {
   union {
      struct {
         unsigned int T2CKPS0:2;
         unsigned int TMR2ON:1;
         unsigned int TOUTPS0:4;
      };
      struct {
         unsigned int T2CKPS:2;
         unsigned int :1;
         unsigned int TOUTPS:4;
      };

      struct {
         unsigned int :3;
         unsigned int T2OUTPS0:4;
      };
   };
      struct {
         unsigned int :3;
         unsigned int T2OUTPS:4;
      };
} T2CONBITS;
T2CONBITS T2CONbits;
#byte T2CONbits = 0xFCA
#byte T2CON = 0xFCA

#byte SSP1BUF = 0xFC9

#byte SSP1ADD = 0xFC8

typedef struct 
 {
   union {
      struct {
         unsigned int :2;
         unsigned int READ_WRITE:1;
         unsigned int :2;
         unsigned int DATA_ADDRESS:1;
      };

   union {
      struct {
         unsigned int :2;
         unsigned int WRITE:1;
         unsigned int :2;
         unsigned int ADDRESS:1;
      };
   };

   union {
      struct {
         unsigned int :2;
         unsigned int R_W:1;
         unsigned int :2;
         unsigned int D_A:1;
      };
   };

   union {
      struct {
         unsigned int :2;
         unsigned int I2C_READ:1;
         unsigned int I2C_START:1;
         unsigned int I2C_STOP:1;
         unsigned int I2C_DAT:1;
      };
   };

   union {
      struct {
         unsigned int BF:1;
         unsigned int UA:1;
         unsigned int R:1;
         unsigned int S:1;
         unsigned int P:1;
         unsigned int D:1;
         unsigned int CKE:1;
         unsigned int SMP:1;
      };
   };

      struct {
         unsigned int :2;
         unsigned int W:1;
         unsigned int :2;
         unsigned int A:1;
      };
   };
} SSP1STATBITS;
SSP1STATBITS SSP1STATbits;
#byte SSP1STATbits = 0xFC7
#byte SSP1STAT = 0xFC7

typedef union 
 {
      struct {
         unsigned int SSPM0:4;
         unsigned int CKP:1;
         unsigned int SSPEN:1;
         unsigned int SSPOV:1;
         unsigned int WCOL:1;
      };
      struct {
         unsigned int SSPM:4;
      };
} SSP1CON1BITS;
SSP1CON1BITS SSP1CON1bits;
#byte SSP1CON1bits = 0xFC6
#byte SSP1CON1 = 0xFC6

typedef union 
 {
   union {
      struct {
         unsigned int :1;
         unsigned int ADMSK0:5;
      };
      struct {
         unsigned int :1;
         unsigned int ADMSK:5;
      };

   union {
      struct {
         unsigned int :1;
         unsigned int ADMSK1:5;
      };
   };

      struct {
         unsigned int SEN:1;
         unsigned int RSEN:1;
         unsigned int PEN:1;
         unsigned int RCEN:1;
         unsigned int ACKEN:1;
         unsigned int ACKDT:1;
         unsigned int ACKSTAT:1;
         unsigned int GCEN:1;
      };
   };
} SSP1CON2BITS;
SSP1CON2BITS SSP1CON2bits;
#byte SSP1CON2bits = 0xFC5
#byte SSP1CON2 = 0xFC5

#word ADRES = 0xFC3
#byte ADRESH = 0xFC4
#byte ADRESL = 0xFC3

typedef union 
 {
   union {
      struct {
         unsigned int ADON:1;
         unsigned int GO:1;
         unsigned int CHS0:4;
      };
      struct {
         unsigned int :1;
         unsigned int :1;
         unsigned int CHS:4;
      };

   union {
      struct {
         unsigned int :1;
         unsigned int DONE:1;
         unsigned int :5;
         unsigned int ADCAL:1;
      };
   };

      struct {
         unsigned int :1;
         unsigned int GO_DONE:1;
      };
   };
} ADCON0BITS;
ADCON0BITS ADCON0bits;
#byte ADCON0bits = 0xFC2
#byte ADCON0 = 0xFC2

typedef union 
 {
      struct {
         unsigned int PCFG0:4;
         unsigned int VCFG0:2;
      };
      struct {
         unsigned int PCFG:4;
         unsigned int VCFG:2;
      };
} ADCON1BITS;
ADCON1BITS ADCON1bits;
#byte ADCON1bits = 0xFC1
#byte ADCON1 = 0xFC1

typedef union 
 {
      struct {
         unsigned int ADCS0:3;
         unsigned int ACQT0:3;
         unsigned int :1;
         unsigned int ADFM:1;
      };
      struct {
         unsigned int ADCS:3;
         unsigned int ACQT:3;
      };
} ADCON2BITS;
ADCON2BITS ADCON2bits;
#byte ADCON2bits = 0xFC0
#byte ADCON2 = 0xFC0

#word CCPR1 = 0xFBE
#byte CCPR1H = 0xFBF
#byte CCPR1L = 0xFBE

typedef struct 
 {
   union {
      struct {
         unsigned int :4;
         unsigned int CCP1Y:1;
         unsigned int CCP1X:1;
      };

      struct {
         unsigned int CCP1M0:4;
         unsigned int DC1B0:2;
         unsigned int P1M0:2;
      };
   };
      struct {
         unsigned int CCP1M:4;
         unsigned int DC1B:2;
         unsigned int P1M:2;
      };
} CCP1CONBITS;
CCP1CONBITS CCP1CONbits;
#byte CCP1CONbits = 0xFBD
#byte CCP1CON = 0xFBD

#word CCPR2 = 0xFBB
#byte CCPR2H = 0xFBC
#byte CCPR2L = 0xFBB

typedef struct 
 {
   union {
      struct {
         unsigned int :4;
         unsigned int CCP2Y:1;
         unsigned int CCP2X:1;
      };

      struct {
         unsigned int CCP2M0:4;
         unsigned int DC2B0:2;
         unsigned int P2M0:2;
      };
   };
      struct {
         unsigned int CCP2M:4;
         unsigned int DC2B:2;
         unsigned int P2M:2;
      };
} CCP2CONBITS;
CCP2CONBITS CCP2CONbits;
#byte CCP2CONbits = 0xFBA
#byte CCP2CON = 0xFBA

#word CCPR3 = 0xFB8
#byte CCPR3H = 0xFB9
#byte CCPR3L = 0xFB8

typedef union 
 {
   union {
      struct {
         unsigned int CCP3M0:4;
         unsigned int DC3B0:2;
         unsigned int P3M0:2;
      };
      struct {
         unsigned int CCP3M:4;
         unsigned int DC3B:2;
         unsigned int P3M:2;
      };

      struct {
         unsigned int :4;
         unsigned int CCP3Y:1;
         unsigned int CCP3X:1;
      };
   };
} CCP3CONBITS;
CCP3CONBITS CCP3CONbits;
#byte CCP3CONbits = 0xFB7
#byte CCP3CON = 0xFB7

typedef union 
 {
   union {
      struct {
         unsigned int PSS1BD0:2;
         unsigned int PSS1AC0:2;
         unsigned int ECCP1AS0:3;
         unsigned int ECCP1ASE:1;
      };
      struct {
         unsigned int PSS1BD:2;
         unsigned int PSS1AC:2;
         unsigned int ECCP1AS:3;
      };

      struct {
         unsigned int PSSBD0:2;
         unsigned int PSSAC0:2;
         unsigned int ECCPAS0:3;
         unsigned int ECCPASE:1;
      };
   };
      struct {
         unsigned int PSSBD:2;
         unsigned int PSSAC:2;
         unsigned int ECCPAS:3;
      };
} ECCP1ASBITS;
ECCP1ASBITS ECCP1ASbits;
#byte ECCP1ASbits = 0xFB6
#byte ECCP1AS = 0xFB6

typedef union 
 {
      struct {
         unsigned int CVR0:4;
         unsigned int CVRSS:1;
         unsigned int CVRR:1;
         unsigned int CVROE:1;
         unsigned int CVREN:1;
      };
      struct {
         unsigned int CVR:4;
      };
} CVRCONBITS;
CVRCONBITS CVRCONbits;
#byte CVRCONbits = 0xFB5
#byte CVRCON = 0xFB5

typedef union 
 {
      struct {
         unsigned int CM0:3;
         unsigned int CIS:1;
         unsigned int C1INV:1;
         unsigned int C2INV:1;
         unsigned int C1OUT:1;
         unsigned int C2OUT:1;
      };
      struct {
         unsigned int CM:3;
      };
} CMCONBITS;
CMCONBITS CMCONbits;
#byte CMCONbits = 0xFB4
#byte CMCON = 0xFB4

#word TMR3 = 0xFB2
#byte TMR3H = 0xFB3
#byte TMR3L = 0xFB2

typedef struct 
 {
   union {
      struct {
         unsigned int :2;
         unsigned int T3INSYNC:1;
      };

      struct {
         unsigned int TMR3ON:1;
         unsigned int TMR3CS:1;
         unsigned int T3SYNC:1;
         unsigned int T3CCP1:1;
         unsigned int T3CKPS0:2;
         unsigned int T3CCP2:1;
         unsigned int RD16:1;
      };
   };
      struct {
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int T3CKPS:2;
      };
} T3CONBITS;
T3CONBITS T3CONbits;
#byte T3CONbits = 0xFB1
#byte T3CON = 0xFB1

#byte SPBRG1 = 0xFAF
#byte SPBRG = 0xFAF

#byte RCREG1 = 0xFAE
#byte RCREG = 0xFAE

#byte TXREG1 = 0xFAD
#byte TXREG = 0xFAD

typedef struct 
 {
   union {
      struct {
         unsigned int TX9D:1;
         unsigned int TRMT:1;
         unsigned int BRGH:1;
         unsigned int SENDB:1;
         unsigned int SYNC:1;
         unsigned int TXEN:1;
         unsigned int TX9:1;
         unsigned int CSRC:1;
      };

   union {
      struct {
         unsigned int TXD8:1;
         unsigned int :5;
         unsigned int TX8_9:1;
      };
   };

      struct {
         unsigned int TX9D1:1;
         unsigned int TRMT1:1;
         unsigned int BRGH1:1;
         unsigned int SENDB1:1;
         unsigned int SYNC1:1;
         unsigned int TXEN1:1;
         unsigned int TX8:1;
         unsigned int CSRC1:1;
      };
   };
} TXSTA1BITS;
TXSTA1BITS TXSTA1bits;
#byte TXSTA1bits = 0xFAC
#byte TXSTAbits = 0xFAC
#byte TXSTA1 = 0xFAC
#byte TXSTA = 0xFAC

typedef struct 
 {
   union {
      struct {
         unsigned int RCD8:1;
         unsigned int :5;
         unsigned int RC9:1;
      };

   union {
      struct {
         unsigned int :6;
         unsigned int RC8:1;
      };
   };

   union {
      struct {
         unsigned int RX9D1:1;
         unsigned int OERR1:1;
         unsigned int FERR1:1;
         unsigned int ADDEN1:1;
         unsigned int CREN1:1;
         unsigned int SREN1:1;
         unsigned int RC8_9:1;
         unsigned int SPEN1:1;
      };
   };

      struct {
         unsigned int RX9D:1;
         unsigned int OERR:1;
         unsigned int FERR:1;
         unsigned int ADDEN:1;
         unsigned int CREN:1;
         unsigned int SREN:1;
         unsigned int RX9:1;
         unsigned int SPEN:1;
      };
   };
} RCSTA1BITS;
RCSTA1BITS RCSTA1bits;
#byte RCSTA1bits = 0xFAB
#byte RCSTAbits = 0xFAB
#byte RCSTA1 = 0xFAB
#byte RCSTA = 0xFAB

#byte EECON2 = 0xFA7

typedef struct 
 {
   unsigned int :1;
   unsigned int WR:1;
   unsigned int WREN:1;
   unsigned int WRERR:1;
   unsigned int FREE:1;
} EECON1BITS;
EECON1BITS EECON1bits;
#byte EECON1bits = 0xFA6
#byte EECON1 = 0xFA6

typedef struct 
 {
   unsigned int CCP3IP:1;
   unsigned int CCP4IP:1;
   unsigned int CCP5IP:1;
   unsigned int TMR4IP:1;
} IPR3BITS;
IPR3BITS IPR3bits;
#byte IPR3bits = 0xFA5
#byte IPR3 = 0xFA5

typedef struct 
 {
   unsigned int CCP3IF:1;
   unsigned int CCP4IF:1;
   unsigned int CCP5IF:1;
   unsigned int TMR4IF:1;
} PIR3BITS;
PIR3BITS PIR3bits;
#byte PIR3bits = 0xFA4
#byte PIR3 = 0xFA4

typedef struct 
 {
   unsigned int CCP3IE:1;
   unsigned int CCP4IE:1;
   unsigned int CCP5IE:1;
   unsigned int TMR4IE:1;
} PIE3BITS;
PIE3BITS PIE3bits;
#byte PIE3bits = 0xFA3
#byte PIE3 = 0xFA3

typedef struct 
 {
   union {
      struct {
         unsigned int CCP2IP:1;
         unsigned int TMR3IP:1;
         unsigned int :1;
         unsigned int BCL1IP:1;
         unsigned int WOLIP:1;
         unsigned int ETHIP:1;
         unsigned int CMIP:1;
         unsigned int OSCFIP:1;
      };

      struct {
         unsigned int :3;
         unsigned int BCLIP:1;
      };
   };
} IPR2BITS;
IPR2BITS IPR2bits;
#byte IPR2bits = 0xFA2
#byte IPR2 = 0xFA2

typedef struct 
 {
   union {
      struct {
         unsigned int :3;
         unsigned int BCLIF:1;
      };

      struct {
         unsigned int CCP2IF:1;
         unsigned int TMR3IF:1;
         unsigned int :1;
         unsigned int BCL1IF:1;
         unsigned int WOLIF:1;
         unsigned int ETHIF:1;
         unsigned int CMIF:1;
         unsigned int OSCFIF:1;
      };
   };
} PIR2BITS;
PIR2BITS PIR2bits;
#byte PIR2bits = 0xFA1
#byte PIR2 = 0xFA1

typedef struct 
 {
   union {
      struct {
         unsigned int CCP2IE:1;
         unsigned int TMR3IE:1;
         unsigned int :1;
         unsigned int BCL1IE:1;
         unsigned int WOLIE:1;
         unsigned int ETHIE:1;
         unsigned int CMIE:1;
         unsigned int OSCFIE:1;
      };

      struct {
         unsigned int :3;
         unsigned int BCLIE:1;
      };
   };
} PIE2BITS;
PIE2BITS PIE2bits;
#byte PIE2bits = 0xFA0
#byte PIE2 = 0xFA0

typedef struct 
 {
   union {
      struct {
         unsigned int TMR1IP:1;
         unsigned int TMR2IP:1;
         unsigned int CCP1IP:1;
         unsigned int SSP1IP:1;
         unsigned int TX1IP:1;
         unsigned int RC1IP:1;
         unsigned int ADIP:1;
      };

      struct {
         unsigned int :3;
         unsigned int SSPIP:1;
         unsigned int TXIP:1;
         unsigned int RCIP:1;
      };
   };
} IPR1BITS;
IPR1BITS IPR1bits;
#byte IPR1bits = 0xF9F
#byte IPR1 = 0xF9F

typedef struct 
 {
   union {
      struct {
         unsigned int :3;
         unsigned int SSPIF:1;
      };

   union {
      struct {
         unsigned int :4;
         unsigned int TXIF:1;
         unsigned int RCIF:1;
      };
   };

      struct {
         unsigned int TMR1IF:1;
         unsigned int TMR2IF:1;
         unsigned int CCP1IF:1;
         unsigned int SSP1IF:1;
         unsigned int TX1IF:1;
         unsigned int RC1IF:1;
         unsigned int ADIF:1;
      };
   };
} PIR1BITS;
PIR1BITS PIR1bits;
#byte PIR1bits = 0xF9E
#byte PIR1 = 0xF9E

typedef struct 
 {
   union {
      struct {
         unsigned int :3;
         unsigned int SSPIE:1;
         unsigned int TXIE:1;
         unsigned int RCIE:1;
      };

      struct {
         unsigned int TMR1IE:1;
         unsigned int TMR2IE:1;
         unsigned int CCP1IE:1;
         unsigned int SSP1IE:1;
         unsigned int TX1IE:1;
         unsigned int RC1IE:1;
         unsigned int ADIE:1;
      };
   };
} PIE1BITS;
PIE1BITS PIE1bits;
#byte PIE1bits = 0xF9D
#byte PIE1 = 0xF9D

typedef union 
 {
      struct {
         unsigned int :4;
         unsigned int PPRE:1;
         unsigned int PPST0:1;
         unsigned int PLLEN:1;
         unsigned int PPST1:1;
      };
      struct {
         unsigned int :4;
      };
} OSCTUNEBITS;
OSCTUNEBITS OSCTUNEbits;
#byte OSCTUNEbits = 0xF9B
#byte OSCTUNE = 0xF9B

typedef struct 
 {
   unsigned int TRISG0:1;
   unsigned int TRISG1:1;
   unsigned int TRISG2:1;
   unsigned int TRISG3:1;
   unsigned int TRISG4:1;
   unsigned int TRISG5:1;
   unsigned int TRISG6:1;
   unsigned int TRISG7:1;
} TRISGBITS;
TRISGBITS TRISGbits;
#byte TRISGbits = 0xF98
#byte TRISG = 0xF98

typedef struct 
 {
   unsigned int TRISF0:1;
   unsigned int TRISF1:1;
   unsigned int TRISF2:1;
   unsigned int TRISF3:1;
   unsigned int TRISF4:1;
   unsigned int TRISF5:1;
   unsigned int TRISF6:1;
   unsigned int TRISF7:1;
} TRISFBITS;
TRISFBITS TRISFbits;
#byte TRISFbits = 0xF97
#byte TRISF = 0xF97

typedef struct 
 {
   unsigned int TRISE0:1;
   unsigned int TRISE1:1;
   unsigned int TRISE2:1;
   unsigned int TRISE3:1;
   unsigned int TRISE4:1;
   unsigned int TRISE5:1;
   unsigned int TRISE6:1;
   unsigned int TRISE7:1;
} TRISEBITS;
TRISEBITS TRISEbits;
#byte TRISEbits = 0xF96
#byte TRISE = 0xF96

typedef struct 
 {
   unsigned int TRISD0:1;
   unsigned int TRISD1:1;
   unsigned int TRISD2:1;
   unsigned int TRISD3:1;
   unsigned int TRISD4:1;
   unsigned int TRISD5:1;
   unsigned int TRISD6:1;
   unsigned int TRISD7:1;
} TRISDBITS;
TRISDBITS TRISDbits;
#byte TRISDbits = 0xF95
#byte TRISD = 0xF95

typedef struct 
 {
   unsigned int TRISC0:1;
   unsigned int TRISC1:1;
   unsigned int TRISC2:1;
   unsigned int TRISC3:1;
   unsigned int TRISC4:1;
   unsigned int TRISC5:1;
   unsigned int TRISC6:1;
   unsigned int TRISC7:1;
} TRISCBITS;
TRISCBITS TRISCbits;
#byte TRISCbits = 0xF94
#byte TRISC = 0xF94

typedef struct 
 {
   unsigned int TRISB0:1;
   unsigned int TRISB1:1;
   unsigned int TRISB2:1;
   unsigned int TRISB3:1;
   unsigned int TRISB4:1;
   unsigned int TRISB5:1;
   unsigned int TRISB6:1;
   unsigned int TRISB7:1;
} TRISBBITS;
TRISBBITS TRISBbits;
#byte TRISBbits = 0xF93
#byte TRISB = 0xF93

typedef struct 
 {
   unsigned int TRISA0:1;
   unsigned int TRISA1:1;
   unsigned int TRISA2:1;
   unsigned int TRISA3:1;
   unsigned int TRISA4:1;
   unsigned int TRISA5:1;
   unsigned int TRISA6:1;
   unsigned int TRISA7:1;
} TRISABITS;
TRISABITS TRISAbits;
#byte TRISAbits = 0xF92
#byte TRISA = 0xF92

typedef struct 
 {
   unsigned int LATG0:1;
   unsigned int LATG1:1;
   unsigned int LATG2:1;
   unsigned int LATG3:1;
   unsigned int LATG4:1;
   unsigned int LATG5:1;
   unsigned int LATG6:1;
   unsigned int LATG7:1;
} LATGBITS;
LATGBITS LATGbits;
#byte LATGbits = 0xF8F
#byte LATG = 0xF8F

typedef struct 
 {
   unsigned int LATF0:1;
   unsigned int LATF1:1;
   unsigned int LATF2:1;
   unsigned int LATF3:1;
   unsigned int LATF4:1;
   unsigned int LATF5:1;
   unsigned int LATF6:1;
   unsigned int LATF7:1;
} LATFBITS;
LATFBITS LATFbits;
#byte LATFbits = 0xF8E
#byte LATF = 0xF8E

typedef struct 
 {
   unsigned int LATE0:1;
   unsigned int LATE1:1;
   unsigned int LATE2:1;
   unsigned int LATE3:1;
   unsigned int LATE4:1;
   unsigned int LATE5:1;
   unsigned int LATE6:1;
   unsigned int LATE7:1;
} LATEBITS;
LATEBITS LATEbits;
#byte LATEbits = 0xF8D
#byte LATE = 0xF8D

typedef struct 
 {
   unsigned int LATD0:1;
   unsigned int LATD1:1;
   unsigned int LATD2:1;
   unsigned int LATD3:1;
   unsigned int LATD4:1;
   unsigned int LATD5:1;
   unsigned int LATD6:1;
   unsigned int LATD7:1;
} LATDBITS;
LATDBITS LATDbits;
#byte LATDbits = 0xF8C
#byte LATD = 0xF8C

typedef struct 
 {
   unsigned int LATC0:1;
   unsigned int LATC1:1;
   unsigned int LATC2:1;
   unsigned int LATC3:1;
   unsigned int LATC4:1;
   unsigned int LATC5:1;
   unsigned int LATC6:1;
   unsigned int LATC7:1;
} LATCBITS;
LATCBITS LATCbits;
#byte LATCbits = 0xF8B
#byte LATC = 0xF8B

typedef struct 
 {
   unsigned int LATB0:1;
   unsigned int LATB1:1;
   unsigned int LATB2:1;
   unsigned int LATB3:1;
   unsigned int LATB4:1;
   unsigned int LATB5:1;
   unsigned int LATB6:1;
   unsigned int LATB7:1;
} LATBBITS;
LATBBITS LATBbits;
#byte LATBbits = 0xF8A
#byte LATB = 0xF8A

typedef struct 
 {
   unsigned int LATA0:1;
   unsigned int LATA1:1;
   unsigned int LATA2:1;
   unsigned int LATA3:1;
   unsigned int LATA4:1;
   unsigned int LATA5:1;
   unsigned int LATA6:1;
   unsigned int LATA7:1;
} LATABITS;
LATABITS LATAbits;
#byte LATAbits = 0xF89
#byte LATA = 0xF89

typedef struct 
 {
   unsigned int RG0:1;
   unsigned int RG1:1;
   unsigned int RG2:1;
   unsigned int RG3:1;
   unsigned int RG4:1;
   unsigned int RG5:1;
   unsigned int RG6:1;
   unsigned int RG7:1;
} PORTGBITS;
PORTGBITS PORTGbits;
#byte PORTGbits = 0xF86
#byte PORTG = 0xF86

typedef struct 
 {
   unsigned int RF0:1;
   unsigned int RF1:1;
   unsigned int RF2:1;
   unsigned int RF3:1;
   unsigned int RF4:1;
   unsigned int RF5:1;
   unsigned int RF6:1;
   unsigned int RF7:1;
} PORTFBITS;
PORTFBITS PORTFbits;
#byte PORTFbits = 0xF85
#byte PORTF = 0xF85

typedef struct 
 {
   unsigned int RE0:1;
   unsigned int RE1:1;
   unsigned int RE2:1;
   unsigned int RE3:1;
   unsigned int RE4:1;
   unsigned int RE5:1;
   unsigned int RE6:1;
   unsigned int RE7:1;
} PORTEBITS;
PORTEBITS PORTEbits;
#byte PORTEbits = 0xF84
#byte PORTE = 0xF84

typedef struct 
 {
   unsigned int RD0:1;
   unsigned int RD1:1;
   unsigned int RD2:1;
   unsigned int RD3:1;
   unsigned int RD4:1;
   unsigned int RD5:1;
   unsigned int RD6:1;
   unsigned int RD7:1;
} PORTDBITS;
PORTDBITS PORTDbits;
#byte PORTDbits = 0xF83
#byte PORTD = 0xF83

typedef struct 
 {
   unsigned int RC0:1;
   unsigned int RC1:1;
   unsigned int RC2:1;
   unsigned int RC3:1;
   unsigned int RC4:1;
   unsigned int RC5:1;
   unsigned int RC6:1;
   unsigned int RC7:1;
} PORTCBITS;
PORTCBITS PORTCbits;
#byte PORTCbits = 0xF82
#byte PORTC = 0xF82

typedef struct 
 {
   unsigned int RB0:1;
   unsigned int RB1:1;
   unsigned int RB2:1;
   unsigned int RB3:1;
   unsigned int RB4:1;
   unsigned int RB5:1;
   unsigned int RB6:1;
   unsigned int RB7:1;
} PORTBBITS;
PORTBBITS PORTBbits;
#byte PORTBbits = 0xF81
#byte PORTB = 0xF81

typedef struct 
 {
   unsigned int RA0:1;
   unsigned int RA1:1;
   unsigned int RA2:1;
   unsigned int RA3:1;
   unsigned int RA4:1;
   unsigned int RA5:1;
   unsigned int RA6:1;
   unsigned int RA7:1;
} PORTABITS;
PORTABITS PORTAbits;
#byte PORTAbits = 0xF80
#byte PORTA = 0xF80

#byte SPBRGH1 = 0xF7F

typedef struct 
 {
   union {
      struct {
         unsigned int ABDEN:1;
         unsigned int WUE:1;
         unsigned int :1;
         unsigned int BRG16:1;
         unsigned int TXCKP:1;
         unsigned int RXDTP:1;
         unsigned int RCIDL:1;
         unsigned int ABDOVF:1;
      };

      struct {
         unsigned int :4;
         unsigned int SCKP:1;
         unsigned int :1;
         unsigned int RCMT:1;
      };
   };
} BAUDCON1BITS;
BAUDCON1BITS BAUDCON1bits;
#byte BAUDCON1bits = 0xF7E
#byte BAUDCON1 = 0xF7E

#word ERDPT = 0xF7A
#byte ERDPTH = 0xF7B
#byte ERDPTL = 0xF7A

typedef union 
 {
   union {
      struct {
         unsigned int P1DC0:7;
         unsigned int P1RSEN:1;
      };
      struct {
         unsigned int P1DC:7;
      };

      struct {
         unsigned int PDC0:7;
         unsigned int PRSEN:1;
      };
   };
      struct {
         unsigned int PDC:7;
      };
} ECCP1DELBITS;
ECCP1DELBITS ECCP1DELbits;
#byte ECCP1DELbits = 0xF79
#byte ECCP1DEL = 0xF79

#byte TMR4 = 0xF78

#byte PR4 = 0xF77

typedef union 
 {
      struct {
         unsigned int T4CKPS0:2;
         unsigned int TMR4ON:1;
         unsigned int T4OUTPS0:4;
      };
      struct {
         unsigned int T4CKPS:2;
         unsigned int :1;
         unsigned int T4OUTPS:4;
      };
} T4CONBITS;
T4CONBITS T4CONbits;
#byte T4CONbits = 0xF76
#byte T4CON = 0xF76

#word CCPR4 = 0xF74
#byte CCPR4H = 0xF75
#byte CCPR4L = 0xF74

typedef struct 
 {
   union {
      struct {
         unsigned int :4;
         unsigned int CCP4Y:1;
         unsigned int CCP4X:1;
      };

      struct {
         unsigned int CCP4M0:4;
         unsigned int DC4B0:2;
      };
   };
      struct {
         unsigned int CCP4M:4;
         unsigned int DC4B:2;
      };
} CCP4CONBITS;
CCP4CONBITS CCP4CONbits;
#byte CCP4CONbits = 0xF73
#byte CCP4CON = 0xF73

#word CCPR5 = 0xF71
#byte CCPR5H = 0xF72
#byte CCPR5L = 0xF71

typedef struct 
 {
   union {
      struct {
         unsigned int :4;
         unsigned int CCP5Y:1;
         unsigned int CCP5X:1;
      };

      struct {
         unsigned int CCP5M0:4;
         unsigned int DC5B0:2;
      };
   };
      struct {
         unsigned int CCP5M:4;
         unsigned int DC5B:2;
      };
} CCP5CONBITS;
CCP5CONBITS CCP5CONbits;
#byte CCP5CONbits = 0xF70
#byte CCP5CON = 0xF70

typedef union 
 {
   union {
      struct {
         unsigned int PSSBD0:2;
         unsigned int PSSAC0:2;
         unsigned int ECCPAS0:3;
         unsigned int ECCPASE:1;
      };
      struct {
         unsigned int PSSBD:2;
         unsigned int PSSAC:2;
         unsigned int ECCPAS:3;
      };

      struct {
         unsigned int PSS3BD0:2;
         unsigned int PSS3AC0:2;
         unsigned int ECCP3AS0:3;
         unsigned int ECCP3ASE:1;
      };
   };
      struct {
         unsigned int PSS3BD:2;
         unsigned int PSS3AC:2;
         unsigned int ECCP3AS:3;
      };
} ECCP3ASBITS;
ECCP3ASBITS ECCP3ASbits;
#byte ECCP3ASbits = 0xF6A
#byte ECCP3AS = 0xF6A

typedef union 
 {
   union {
      struct {
         unsigned int P3DC0:7;
         unsigned int P3RSEN:1;
      };
      struct {
         unsigned int P3DC:7;
      };

      struct {
         unsigned int PDC0:7;
         unsigned int PRSEN:1;
      };
   };
      struct {
         unsigned int PDC:7;
      };
} ECCP3DELBITS;
ECCP3DELBITS ECCP3DELbits;
#byte ECCP3DELbits = 0xF69
#byte ECCP3DEL = 0xF69

typedef union 
 {
   union {
      struct {
         unsigned int PSSBD0:2;
         unsigned int PSSAC0:2;
         unsigned int ECCPAS0:3;
         unsigned int ECCPASE:1;
      };
      struct {
         unsigned int PSSBD:2;
         unsigned int PSSAC:2;
         unsigned int ECCPAS:3;
      };

      struct {
         unsigned int PSS2BD0:2;
         unsigned int PSS2AC0:2;
         unsigned int ECCP2AS0:3;
         unsigned int ECCP2ASE:1;
      };
   };
      struct {
         unsigned int PSS2BD:2;
         unsigned int PSS2AC:2;
         unsigned int ECCP2AS:3;
      };
} ECCP2ASBITS;
ECCP2ASBITS ECCP2ASbits;
#byte ECCP2ASbits = 0xF68
#byte ECCP2AS = 0xF68

typedef union 
 {
   union {
      struct {
         unsigned int P2DC0:7;
         unsigned int P2RSEN:1;
      };
      struct {
         unsigned int P2DC:7;
      };

      struct {
         unsigned int PDC0:7;
         unsigned int PRSEN:1;
      };
   };
      struct {
         unsigned int PDC:7;
      };
} ECCP2DELBITS;
ECCP2DELBITS ECCP2DELbits;
#byte ECCP2DELbits = 0xF67
#byte ECCP2DEL = 0xF67

#byte EDATA = 0xF61

typedef struct 
 {
   unsigned int RXERIF:1;
   unsigned int TXERIF:1;
   unsigned int :1;
   unsigned int TXIF:1;
   unsigned int LINKIF:1;
   unsigned int DMAIF:1;
   unsigned int PKTIF:1;
} EIRBITS;
EIRBITS EIRbits;
#byte EIRbits = 0xF60
#byte EIR = 0xF60

typedef struct 
 {
   unsigned int :5;
   unsigned int ETHEN:1;
   unsigned int PKTDEC:1;
   unsigned int AUTOINC:1;
} ECON2BITS;
ECON2BITS ECON2bits;
#byte ECON2bits = 0xEFE
#byte ECON2 = 0xEFE

typedef struct 
 {
   unsigned int PHYRDY:1;
   unsigned int TXABRT:1;
   unsigned int RXBUSY:1;
   unsigned int :1;
   unsigned int LATECOL:1;
   unsigned int :1;
   unsigned int BUFER:1;
} ESTATBITS;
ESTATBITS ESTATbits;
#byte ESTATbits = 0xEFD
#byte ESTAT = 0xEFD

typedef struct 
 {
   union {
      struct {
         unsigned int RXERIE:1;
         unsigned int TXERIE:1;
         unsigned int :1;
         unsigned int TXIE:1;
         unsigned int LINKIE:1;
         unsigned int DMAIE:1;
         unsigned int PKTIE:1;
      };

      struct {
         unsigned int :3;
         unsigned int ETXIE:1;
      };
   };
} EIEBITS;
EIEBITS EIEbits;
#byte EIEbits = 0xEFB
#byte EIE = 0xEFB

#word EDMACS = 0xEF6
#byte EDMACSH = 0xEF7
#byte EDMACSL = 0xEF6

#word EDMADST = 0xEF4
#byte EDMADSTH = 0xEF5
#byte EDMADSTL = 0xEF4

#word EDMAND = 0xEF2
#byte EDMANDH = 0xEF3
#byte EDMANDL = 0xEF2

#word EDMAST = 0xEF0
#byte EDMASTH = 0xEF1
#byte EDMASTL = 0xEF0

#word ERXWRPT = 0xEEE
#byte ERXWRPTH = 0xEEF
#byte ERXWRPTL = 0xEEE

#word ERXRDPT = 0xEEC
#byte ERXRDPTH = 0xEED
#byte ERXRDPTL = 0xEEC

#word ERXND = 0xEEA
#byte ERXNDH = 0xEEB
#byte ERXNDL = 0xEEA

#word ERXST = 0xEE8
#byte ERXSTH = 0xEE9
#byte ERXSTL = 0xEE8

#word ETXND = 0xEE6
#byte ETXNDH = 0xEE7
#byte ETXNDL = 0xEE6

#word ETXST = 0xEE4
#byte ETXSTH = 0xEE5
#byte ETXSTL = 0xEE4

#word EWRPT = 0xEE2
#byte EWRPTH = 0xEE3
#byte EWRPTL = 0xEE2

#byte EPKTCNT = 0xED9

typedef struct 
 {
   unsigned int BCEN:1;
   unsigned int MCEN:1;
   unsigned int HTEN:1;
   unsigned int MPEN:1;
   unsigned int PMEN:1;
   unsigned int CRCEN:1;
   unsigned int ANDOR:1;
   unsigned int UCEN:1;
} ERXFCONBITS;
ERXFCONBITS ERXFCONbits;
#byte ERXFCONbits = 0xED8
#byte ERXFCON = 0xED8

#word EPMO = 0xED4
#byte EPMOH = 0xED5
#byte EPMOL = 0xED4

#word EPMCS = 0xED0
#byte EPMCSH = 0xED1
#byte EPMCSL = 0xED0

#byte EPMM7 = 0xECF

#byte EPMM6 = 0xECE

#byte EPMM5 = 0xECD

#byte EPMM4 = 0xECC

#byte EPMM3 = 0xECB

#byte EPMM2 = 0xECA

#byte EPMM1 = 0xEC9

#byte EPMM0 = 0xEC8

#byte EHT7 = 0xEC7

#byte EHT6 = 0xEC6

#byte EHT5 = 0xEC5

#byte EHT4 = 0xEC4

#byte EHT3 = 0xEC3

#byte EHT2 = 0xEC2

#byte EHT1 = 0xEC1

#byte EHT0 = 0xEC0

#word MIRD = 0xEB8
#byte MIRDH = 0xEB9
#byte MIRDL = 0xEB8

#word MIWR = 0xEB6
#byte MIWRH = 0xEB7
#byte MIWRL = 0xEB6

#byte MIREGADR = 0xEB4

typedef struct 
 {
   unsigned int MIIRD:1;
   unsigned int MIISCAN:1;
} MICMDBITS;
MICMDBITS MICMDbits;
#byte MICMDbits = 0xEB2
#byte MICMD = 0xEB2

#word MAMXFL = 0xEAA
#byte MAMXFLH = 0xEAB
#byte MAMXFLL = 0xEAA

#word MAIPG = 0xEA6
#byte MAIPGH = 0xEA7
#byte MAIPGL = 0xEA6

#byte MABBIPG = 0xEA4

typedef struct 
 {
   unsigned int :4;
   unsigned int NOBKOFF:1;
   unsigned int BPEN:1;
   unsigned int DEFER:1;
} MACON4BITS;
MACON4BITS MACON4bits;
#byte MACON4bits = 0xEA3
#byte MACON4 = 0xEA3

typedef union 
 {
      struct {
         unsigned int FULDPX:1;
         unsigned int FRMLNEN:1;
         unsigned int HFRMEN:1;
         unsigned int PHDREN:1;
         unsigned int TXCRCEN:1;
         unsigned int PADCFG0:3;
      };
      struct {
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int :1;
         unsigned int PADCFG:3;
      };
} MACON3BITS;
MACON3BITS MACON3bits;
#byte MACON3bits = 0xEA2
#byte MACON3 = 0xEA2

typedef struct 
 {
   unsigned int MARXEN:1;
   unsigned int PASSALL:1;
   unsigned int RXPAUS:1;
   unsigned int TXPAUS:1;
} MACON1BITS;
MACON1BITS MACON1bits;
#byte MACON1bits = 0xEA0
#byte MACON1 = 0xEA0

#word EPAUS = 0xE98
#byte EPAUSH = 0xE99
#byte EPAUSL = 0xE98

typedef union 
 {
      struct {
         unsigned int FCEN0:2;
         unsigned int FULDPXS:1;
      };
      struct {
         unsigned int FCEN:2;
      };
} EFLOCONBITS;
EFLOCONBITS EFLOCONbits;
#byte EFLOCONbits = 0xE97
#byte EFLOCON = 0xE97

typedef struct 
 {
   unsigned int BUSY:1;
   unsigned int SCAN:1;
   unsigned int NVALID:1;
   unsigned int LINKFL:1;
} MISTATBITS;
MISTATBITS MISTATbits;
#byte MISTATbits = 0xE8A
#byte MISTAT = 0xE8A

#byte MAADR2 = 0xE85

#byte MAADR1 = 0xE84

#byte MAADR4 = 0xE83

#byte MAADR3 = 0xE82

#byte MAADR6 = 0xE81

#byte MAADR5 = 0xE80

