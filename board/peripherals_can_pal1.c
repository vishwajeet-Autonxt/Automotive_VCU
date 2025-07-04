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
  UUID: eae3375a-b4e1-467a-9ee1-fd1b1e14d641
  called_from_default_init: true
  selectedCore: core0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/*******************************************************************************
 * Included files 
 ******************************************************************************/
#include "peripherals_can_pal1.h"

/*******************************************************************************
 * can_pal1 initialization code
 ******************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'can_pal1'
- type: 'can_pal_config'
- mode: 'general'
- custom_name_enabled: 'true'
- type_id: 'can_pal'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'CAN0'
- config_sets:
  - can_pal:
    - can_instance_t2:
      - name: 'can_pal1_instance'
      - readonly: 'false'
      - instType: 'CAN_INST_TYPE_FLEXCAN'
    - can_user_config_t2:
      - name: 'can_pal1_Config0'
      - readonly: 'true'
      - maxBuffNum: '2'
      - mode: 'CAN_NORMAL_MODE'
      - peClkSrc: 'CAN_CLK_SOURCE_OSC'
      - enableFD: 'true'
      - payloadSize: 'CAN_PAYLOAD_SIZE_16'
      - can_bitrate2ts: 'true'
      - flexcan_cfg_time_segments2:
        - nominalBitrate:
          - rJumpwidth: '1'
          - bitrate: '500'
          - samplingPoint: '87.5'
        - dataBitrate_:
          - rJumpwidth: '1'
          - bitrate: '1000'
          - samplingPoint: '75'
    - can_fifo_ext2:
      - isRxFIFO_Enable: 'false'
      - name: 'can_pal1_rx_fifo_ext0'
      - struct_extension:
        - readonly: 'false'
        - numIdFilters: 'FLEXCAN_RX_FIFO_ID_FILTERS_8'
        - idFormat: 'FLEXCAN_RX_FIFO_ID_FORMAT_A'
        - idFilterTable: 'NULL'
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

can_instance_t can_pal1_instance = {
  .instType = CAN_INST_TYPE_FLEXCAN,
  .instIdx = 0UL
};

const can_user_config_t can_pal1_Config0 = {
  .maxBuffNum = 2UL,
  .mode = CAN_NORMAL_MODE,
  .peClkSrc = CAN_CLK_SOURCE_OSC,
  .enableFD = true,
  .payloadSize = CAN_PAYLOAD_SIZE_16,
  .nominalBitrate = {
    .propSeg = 7UL,
    .phaseSeg1 = 4UL,
    .phaseSeg2 = 1UL,
    .preDivider = 0UL,
    .rJumpwidth = 1UL
  },
  .dataBitrate = {
    .propSeg = 3UL,
    .phaseSeg1 = 1UL,
    .phaseSeg2 = 1UL,
    .preDivider = 0UL,
    .rJumpwidth = 1UL
  },
  .extension = NULL
};


