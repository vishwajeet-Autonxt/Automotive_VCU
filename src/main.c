/* #include "sdk_project_config.h"
#include "S32K144.h"
#include "clocks_and_modes.h"
#include "PTOSwitchCtrl.h"
#include "MainSwitch.h"
#include "SteeringPositionCtrl.h"
#include "IgnitionCtrl.h"

volatile int exit_code = 0;

#define PTA ((GPIO_Type *)PTA_BASE)
#define PTB ((GPIO_Type *)PTB_BASE)
#define PTC ((GPIO_Type *)PTC_BASE)
#define PTD ((GPIO_Type *)PTD_BASE)
#define PTE ((GPIO_Type *)PTE_BASE)


/*void ADC_init(void)
{
    PCC->PCCn[PCC_ADC0_INDEX] |= PCC_PCCn_CGC_MASK;
    ADC0->SC1[0] = ADC_SC1_ADCH(31);  // Disable module
    ADC0->CFG1 = ADC_CFG1_ADIV(3) | ADC_CFG1_MODE(1); // 12-bit
}

int main(void)
{
    WDOG_disable();
    SOSC_init_8MHz();
    SPLL_init_160MHz();
    NormalRUNmode_80MHz();

    PORT_init();
   // ADC_init();

    SteeringPosition_Init();
    IgnitionCtrl_Init();

    Key_Inputs in = {0};
    Key_Outputs out = {0};

    while (1)
    {
        // === Read Inputs ===
   /*     in.ignition_pos1  = (GPIO_Type->PDIR & (1 << 0)) != 0;
        in.ignition_pos2  = (GPIO_Type->PDIR & (1 << 1)) != 0;
        in.gear_neutral   = (GPIO_Type->PDIR & (1 << 2)) != 0;
        in.fault_detected = (GPIO_Type->PDIR & (1 << 3)) != 0;
        in.motor_ready    = (GPIO_Type->PDIR & (1 << 4)) != 0;

        in.ignition_pos1  = (PTC->PDIR & (1 << 0)) != 0;  // Read PTC0
        in.ignition_pos2  = (PTC->PDIR & (1 << 1)) != 0;  // Read PTC1
        in.gear_neutral   = (PTC->PDIR & (1 << 2)) != 0;  // Read PTC2
        in.fault_detected = (PTC->PDIR & (1 << 3)) != 0;  // Read PTC3
        in.motor_ready    = (PTC->PDIR & (1 << 4)) != 0;  // Read PTC4

        ADC0->SC1[0] = ADC_SC1_ADCH(6); // Start ADC conversion
        while ((ADC0->SC1[0] & ADC_SC1_COCO_MASK) == 0);
        uint16_t adc_val = ADC0->R[0];
        in.battery_voltage = (adc_val * 5.0f / 4095.0f) * 4.0f; // Assuming voltage divider

        // === Control Logic ===
        IgnitionCtrl_Update(&in, &out);

        // === Outputs ===
        if (out.discharge_switch)
            PTD->PSOR = (1 << 0);
        else
            PTD->PCOR = (1 << 0);

        if (out.motor_start_switch)
            PTD->PSOR = (1 << 1);
        else
            PTD->PCOR = (1 << 1);

    }

    return exit_code;
}
*/
#include "sdk_project_config.h"
#include <interrupt_manager.h>
#include <stdint.h>
#include <stdbool.h>
#include "can_pal.h"
#include "peripherals_can_pal1.h"
/******************************************************************************
 * Definitions
 ******************************************************************************/

/* This example is setup to work by default with EVB. To use it with other boards
   please comment the following line
*/

#define EVB

#ifdef EVB
    #define LED_PORT        PORTD
    #define GPIO_PORT       PTD
    #define PCC_INDEX       PCC_PORTD_INDEX
    #define LED0            15U
    #define LED1            16U
    #define BTN_GPIO        PTC
    #define BTN1_PIN        13U
    #define BTN2_PIN        12U
    #define BTN_PORT        PORTC
    #define BTN_PORT_IRQn   PORTC_IRQn
#else
    #define LED_PORT        PORTC
    #define GPIO_PORT       PTC
    #define PCC_INDEX       PCC_PORTC_INDEX
    #define LED0            0U
    #define LED1            1U
    #define BTN_GPIO        PTC
    #define BTN1_PIN        13U
    #define BTN2_PIN        12U
    #define BTN_PORT        PORTC
    #define BTN_PORT_IRQn   PORTC_IRQn
#endif

/* Use this define to specify if the application runs as master or slave */
#define MASTER
/* #define SLAVE */

/* Definition of the TX and RX message buffers depending on the bus role */
#if defined(MASTER)
    #define TX_MAILBOX  (1UL)
    #define TX_MSG_ID   (1UL)
    #define RX_MAILBOX  (0UL)
    #define RX_MSG_ID   (2UL)
#elif defined(SLAVE)
    #define TX_MAILBOX  (0UL)
    #define TX_MSG_ID   (2UL)
    #define RX_MAILBOX  (1UL)
    #define RX_MSG_ID   (1UL)
#endif

typedef enum
{
    LED0_CHANGE_REQUESTED = 0x00U,
    LED1_CHANGE_REQUESTED = 0x01U
} can_commands_list;

uint8_t ledRequested = (uint8_t)LED0_CHANGE_REQUESTED;

/******************************************************************************
 * Function prototypes
 ******************************************************************************/
void buttonISR(void);
void BoardInit(void);
void GPIOInit(void);

/******************************************************************************
 * Functions
 ******************************************************************************/

/**
 * Button interrupt handler
 */
void buttonISR(void)
{
    /* Check if one of the buttons was pressed */
    uint32_t buttonsPressed = PINS_DRV_GetPortIntFlag(BTN_PORT) &
                                           ((1 << BTN1_PIN) | (1 << BTN2_PIN));
    bool sendFrame = false;

    if(buttonsPressed != 0)
    {

        /* Set FlexCAN TX value according to the button pressed */
        switch (buttonsPressed)
        {
            case (1 << BTN1_PIN):
                ledRequested = LED0_CHANGE_REQUESTED;
                sendFrame = true;
                /* Clear interrupt flag */
                PINS_DRV_ClearPinIntFlagCmd(BTN_PORT, BTN1_PIN);
                break;
            case (1 << BTN2_PIN):
                ledRequested = LED1_CHANGE_REQUESTED;
                sendFrame = true;
                /* Clear interrupt flag */
                PINS_DRV_ClearPinIntFlagCmd(BTN_PORT, BTN2_PIN);
                break;
            default:
                PINS_DRV_ClearPortIntFlagCmd(BTN_PORT);
                break;
        }

        if (sendFrame)
        {
            /* Set information about the data to be sent
             *  - Standard message ID
             *  - Bit rate switch enabled to use a different bitrate for the data segment
             *  - Flexible data rate enabled
             *  - Use zeros for FD padding
             */
            can_buff_config_t buffCfg =  {
                .enableFD = true,
                .enableBRS = true,
                .fdPadding = 0U,
                .idType = CAN_MSG_ID_STD,
                .isRemote = false
            };

            /* Configure TX buffer with index TX_MAILBOX*/
            CAN_ConfigTxBuff(&can_pal1_instance, TX_MAILBOX, &buffCfg);


            /* Prepare message to be sent */
            can_message_t message = {
                .cs = 0U,
                .id = TX_MSG_ID,
                .data[0] = ledRequested,
                .length = 1U
            };

            /* Send the information via CAN */
            CAN_Send(&can_pal1_instance, TX_MAILBOX, &message);
        }
    }
}

/*
 * @brief : Initialize clocks, pins and power modes
 */
void BoardInit(void)
{

    /* Initialize and configure clocks
     *  -   Setup system clocks, dividers
     *  -   Configure FlexCAN clock, GPIO
     *  -   see clock manager component for more details
     */
    CLOCK_DRV_Init(&clockMan1_InitConfig0);


    /* Initialize pins
     *  -   Init FlexCAN and GPIO pins
     *  -   See PinSettings component for more info
     */
    PINS_DRV_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);
}

/*
 * @brief Function which configures the LEDs and Buttons
 */
void GPIOInit(void)
{
    /* Output direction for LEDs */
    PINS_DRV_SetPinsDirection(GPIO_PORT, (1 << LED1) | (1 << LED0));

    /* Set Output value LEDs */
    PINS_DRV_ClearPins(GPIO_PORT, (1 << LED1) | (1 << LED0));

    /* Setup button pin */
    PINS_DRV_SetPinsDirection(BTN_GPIO, ~((1 << BTN1_PIN)|(1 << BTN2_PIN)));

    /* Setup button pins interrupt */
    PINS_DRV_SetPinIntSel(BTN_PORT, BTN1_PIN, PORT_INT_RISING_EDGE);
    PINS_DRV_SetPinIntSel(BTN_PORT, BTN2_PIN, PORT_INT_RISING_EDGE);

    /* Install buttons ISR */
    INT_SYS_InstallHandler(BTN_PORT_IRQn, &buttonISR, NULL);

    /* Enable buttons interrupt */
    INT_SYS_EnableIRQ(BTN_PORT_IRQn);
}

volatile int exit_code = 0;

/*!
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - __start (startup asm routine)
 * - __init_hardware()
 * - main()
 *     - Common_Init()
 *     - Peripherals_Init()
*/
int main(void)
{
    /* Do the initializations required for this application */
    BoardInit();
    GPIOInit();

    CAN_Init(&can_pal1_instance, &can_pal1_Config0);

    /* Set information about the data to be sent
     *  - Standard message ID
     *  - Bit rate switch enabled to use a different bitrate for the data segment
     *  - Flexible data rate enabled
     *  - Use zeros for FD padding
     */
    can_buff_config_t buffCfg =  {
        .enableFD = true,
        .enableBRS = true,
        .fdPadding = 0U,
        .idType = CAN_MSG_ID_STD,
        .isRemote = false
    };

    /* Configure RX buffer with index RX_MAILBOX */
    CAN_ConfigRxBuff(&can_pal1_instance, RX_MAILBOX, &buffCfg, RX_MSG_ID);

    while(1)
    {
        /* Define receive buffer */
        can_message_t recvMsg;

        /* Start receiving data in RX_MAILBOX. */
        CAN_Receive(&can_pal1_instance, RX_MAILBOX, &recvMsg);

        /* Wait until the previous FlexCAN receive is completed */
        while(CAN_GetTransferStatus(&can_pal1_instance, RX_MAILBOX) == STATUS_BUSY);

        /* Check the received message ID and payload */
        if((recvMsg.data[0] == LED0_CHANGE_REQUESTED) &&
                recvMsg.id == RX_MSG_ID)
        {
            /* Toggle output value LED1 */
            PINS_DRV_TogglePins(GPIO_PORT, (1 << LED0));
        }
        else if((recvMsg.data[0] == LED1_CHANGE_REQUESTED) &&
                recvMsg.id == RX_MSG_ID)
        {
            /* Toggle output value LED0 */
            PINS_DRV_TogglePins(GPIO_PORT, (1 << LED1));
        }
    }

    for(;;) {
      if(exit_code != 0) {
        break;
      }
    }
    return exit_code;
}



