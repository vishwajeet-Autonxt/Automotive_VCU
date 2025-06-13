/*
 * PTOSwitchCtrl.c
 *
 *  Created on: 21-May-2025
 *      Author: Vishwajeet_Jagtap
 */

 #include "clock.h"
 #include "PTOSwitchCtrl.h"

 #define PTD15 15 /* RED LED*/
 #define PTD16 16 /* GREEN LED*/
 #define PTD0 0   /* BLUE LED */
 volatile uint32_t adcResultInMv_pot = 0;
 uint32_t adcResultInMv_Vrefsh = 0;

 void PORT_init (void) {
 PCC->PCCn[PCC_PORTD_INDEX ]|=PCC_PCCn_CGC_MASK;   /* Enable clock for PORTD */
 PORTD->PCR[PTD0]  =  0x00000100;  /* Port D0: MUX = GPIO */
 PORTD->PCR[PTD15] =  0x00000100;  /* Port D15: MUX = GPIO */
 PORTD->PCR[PTD16] =  0x00000100;  /* Port D16: MUX = GPIO */
 PTD->PDDR |= 1<<PTD0;
 PTD->PDDR |= 1<<PTD15;
 PTD->PDDR |= 1<<PTD16;
}

 void WDOG_disable (void){
 WDOG->CNT=0xD928C520;
 /* Port D0:  Data Direction= output */
 /* Port D15: Data Direction= output */
 /* Port D16: Data Direction= output */
 /* Unlock watchdog */
 WDOG->TOVAL=0x0000FFFF;   /* Maximum timeout value */
 WDOG->CS = 0x00002100;    /* Disable watchdog */
 }

 void ADC_init(void)  {
   PCC->PCCn[PCC_ADC0_INDEX] &=~ PCC_PCCn_CGC_MASK;  /* Disable clock to change PCS */
   PCC->PCCn[PCC_ADC0_INDEX] |= PCC_PCCn_PCS(1);     /* PCS=1: Select SOSCDIV2 */
   PCC->PCCn[PCC_ADC0_INDEX] |= PCC_PCCn_CGC_MASK;   /* Enable bus clock in ADC */
   ADC0->SC1[0] =0x00001F;         /* ADCH=1F: Module is disabled for conversions*/
                                    /* AIEN=0: Interrupts are disabled */
    ADC0->CFG1 = 0x000000004;       /* ADICLK=0: Input clk=ALTCLK1=SOSCDIV2 */
                                    /* ADIV=0: Prescaler=1 */
                                    /* MODE=1: 12-bit conversion */
    ADC0->CFG2 = 0x00000000C;       /* SMPLTS=12(default): sample time is 13 ADC clks */
    ADC0->SC2 = 0x00000000;         /* ADTRG=0: SW trigger */
                                    /* ACFE,ACFGT,ACREN=0: Compare func disabled */
                                    /* DMAEN=0: DMA disabled */
                                    /* REFSEL=0: Voltage reference pins= VREFH, VREEFL */
    ADC0->SC3 = 0x00000000;         /* CAL=0: Do not start calibration sequence */
                                    /* ADCO=0: One conversion performed */
                                    /* AVGE,AVGS=0: HW average function disabled */
 }

 void convertAdcChan(uint16_t adcChan) {   /* For SW trigger mode, SC1[0] is used */
   ADC0->SC1[0]&=~ADC_SC1_ADCH_MASK;      /* Clear prior ADCH bits */
   ADC0->SC1[0] = ADC_SC1_ADCH(adcChan);   /* Initiate Conversion*/
  }

  uint8_t adc_complete(void)  {
   return ((ADC0->SC1[0] & ADC_SC1_COCO_MASK)>>ADC_SC1_COCO_SHIFT); /* Wait for completion */
  }

  uint32_t read_adc_chx(void)  {
   uint16_t adc_result=0;
   adc_result=ADC0->R[0];      /* For SW trigger mode, R[0] is used */
   return  (uint32_t) ((5000*adc_result)/0xFFF); /* Convert result to mv for 0-5V range */
  }

 int PTOSwitch_Init(void)
 {
 WDOG_disable();        /* Disable WDOG*/
 SOSC_init_8MHz();      /* Initialize system oscillator for 8 MHz xtal  */
 SPLL_init_160MHz();    /* Initialize SPLL to 160 MHz with 8 MHz SOSC */
 NormalRUNmode_80MHz(); /* Init clocks: 80 MHz sysclk & core, 40 MHz bus, 20 MHz flash */
 PORT_init();           /* Init port clocks and gpio outputs */
 ADC_init();            /* ADC resolution 12 bit */

 for(;;) {
    convertAdcChan(12);                   /* Convert Channel AD12 to pot on EVB */
    while(adc_complete()==0){}            /* Wait for conversion complete flag */
    adcResultInMv_pot = read_adc_chx();       /* Get channel's conversion results in mv */
    if (adcResultInMv_pot > 3750) {       /* If result > 3.75V */
      PTD->PSOR |= 1<<PTD0 | 1<<PTD16;    /* turn off blue, green LEDs */
      PTD->PCOR |= 1<<PTD15;              /* turn on red LED */
    }
    else if (adcResultInMv_pot > 2500) {  /* If result > 3.75V */
      PTD->PSOR |= 1<<PTD0 | 1<<PTD15;    /* turn off blue, red LEDs */
      PTD->PCOR |= 1<<PTD16;           /* turn on green LED */
    }
    else if (adcResultInMv_pot > 1250) {       /* If result > 3.75V */
      PTD->PSOR |= 1<<PTD15 | 1<<PTD16;   /* turn off red, green LEDs */
      PTD->PCOR |= 1<<PTD0;           /* turn on blue LED */
    }
    else {
      PTD->PSOR |= 1<<PTD0 | 1<< PTD15 | 1<<PTD16; /* Turn off all LEDs */
    }
    convertAdcChan(29);                   /* Convert chan 29, Vrefsh */
    while(adc_complete()==0){}            /* Wait for conversion complete flag */
    adcResultInMv_Vrefsh = read_adc_chx();       /* Get channel's conversion results in mv */
  }
 }


