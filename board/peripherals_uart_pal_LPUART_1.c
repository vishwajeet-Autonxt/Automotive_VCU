/***********************************************************************************************************************
 * This file was generated by the S32 Configuration Tools. Any manual edits made to this file
 * will be overwritten if the respective S32 Configuration Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Peripherals v9.0
processor: S32K144
package_id: S32K144_LQFP100
mcu_data: s32sdk_s32k1xx_rtm_402
processor_version: 0.0.0
functionalGroups:
- name: BOARD_InitPeripherals
  UUID: a6d43dcb-893a-49cd-9d9d-0bb26ff0f05b
  called_from_default_init: true
  selectedCore: core0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/*******************************************************************************
 * Included files 
 ******************************************************************************/
#include "peripherals_uart_pal_LPUART_1.h"

/*******************************************************************************
 * uart_pal_LPUART_1 initialization code
 ******************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'uart_pal_LPUART_1'
- type: 'uart_pal_config'
- mode: 'general'
- custom_name_enabled: 'true'
- type_id: 'uart_pal'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'LPUART_1'
- config_sets:
  - uart_pal:
    - uartPalInst:
      - name: 'uart_instance_lu1'
      - readonly: 'false'
      - instType: 'UART_INST_TYPE_LPUART'
    - uartCfgArray:
      - 0:
        - uartCommonConfig:
          - name: 'LPUART_1_uart_pal_config0'
          - readonly: 'true'
          - baudRate: '115200'
          - parityMode: 'UART_PARITY_DISABLED'
          - bitCount: 'UART_8_BITS_PER_CHAR'
          - stopBitCount: 'UART_ONE_STOP_BIT'
          - transferType: 'UART_USING_INTERRUPTS'
          - rxDMAChannel: '0'
          - txDMAChannel: '1'
          - rxCallback: 'rxCallback'
          - rxCallbackParam: 'NULL'
          - txCallback: 'NULL'
          - txCallbackParam: 'NULL'
          - extension: 'NULL'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/**
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 8.7, External variable could be made static.
 * The external variables will be used in other source files in application code.
 *
 */

uart_instance_t uart_instance_lu1 = {
  .instType = UART_INST_TYPE_LPUART,
  .instIdx = 1
};

const uart_user_config_t LPUART_1_uart_pal_config0 = {
  .baudRate = 115200UL,
  .parityMode = UART_PARITY_DISABLED,
  .bitCount = UART_8_BITS_PER_CHAR,
  .stopBitCount = UART_ONE_STOP_BIT,
  .transferType = UART_USING_INTERRUPTS,
  .rxDMAChannel = 0UL,
  .txDMAChannel = 1UL,
  .rxCallback = rxCallback,
  .rxCallbackParam = NULL,
  .txCallback = NULL,
  .txCallbackParam = NULL,
  .extension = NULL
};


