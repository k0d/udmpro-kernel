/*
 * Copyright 2018, Amazon.com, Inc. or its affiliates. All Rights Reserved
 */

/**
 *  @{
 * @file   al_hal_ddrc_regs.h
 *
 * @brief ddrc registers
 *
 * This file was auto-generated by RegGen v1.2.1
 *
 */

#ifndef __AL_HAL_DDRC_REGS_H__
#define __AL_HAL_DDRC_REGS_H__

#include "al_hal_plat_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Unit Registers
 */

struct al_ddrc_global {
	/* [0x0] IOCache Revision */
	uint32_t ver;
	/*
	 * [0x4] Allow non-secure access to secure registers.
	 * Each bit disables security for one register
	 * This register is accessible only in secure mode
	 * Reset: 0xffffffff  Access: RW
	 */
	uint32_t sec_ovrd;
	/* [0x8] General config registers */
	uint32_t cntrl1;
	/* [0xc] */
	uint32_t crc_retry;
	/* [0x10] */
	uint32_t lp;
	/* [0x14] */
	uint32_t pmu;
	/* [0x18] AXI write termination control */
	uint32_t termination;
	/* [0x1c] */
	uint32_t rsrvd_0;
	/* [0x20] */
	uint32_t urgent;
	/* [0x24] */
	uint32_t rsrvd_1;
	/* [0x28] */
	uint32_t arurgent_timeout;
	/* [0x2c] */
	uint32_t awurgent_timeout;
	/* [0x30] */
	uint32_t rsrvd_2[24];
	/*
	 * [0x90] For ECO
	 * Reset: 0x0         Access: RW
	 */
	uint32_t rsv_config0;
	/*
	 * [0x94] For ECO
	 * Reset: 0x0         Access: RW
	 */
	uint32_t rsv_config1;
	/*
	 * [0x98] For ECO
	 * Reset: 0xffffffff  Access: RW
	 */
	uint32_t rsv_config2;
	/*
	 * [0x9c] For ECO
	 * Reset: 0xffffffff  Access: RW
	 */
	uint32_t rsv_config3;
	/* [0xa0] */
	uint32_t rsrvd_3[24];
};

/*
 * Interrupt Controller
 */
struct al_ddrc_mem {
	/* [0x0] shut down for memories */
	uint32_t sd;
	/* [0x4] */
	uint32_t rsrvd_0[15];
};

struct al_ddrc_channel {
	/* [0x0] */
	uint32_t cntrl;
	/* [0x4] */
	uint32_t hold_reset;
	/* [0x8] */
	uint32_t status;
	/* [0xc] */
	uint32_t rsrvd_0;
	/* [0x10] */
	uint32_t int_cause;
	/* [0x14] */
	uint32_t rsrvd_1;
	/*
	 * [0x18] DDR Cause Interrupt Mask Register
	 * Reset: 0x0         Access: RW
	 */
	uint32_t cause_mask;
	/* [0x1c] */
	uint32_t rsrvd_2;
	/* [0x20] */
	uint32_t address_map;
	/* [0x24] */
	uint32_t rsrvd_3[3];
	/*
	 * [0x30] DDR Read Reorder buffer ID mask.
	 * If incoming read transaction ID ANDed with mask is equal Reorder_ID_Value, then the
	 * transaction is mapped to the DDR controller bypass channel.
	 * Setting this register to 0 will disable the check
	 * Reset: 0x0         Access: RW
	 */
	uint32_t reorder_id_mask_0;
	/*
	 * [0x34] DDR Read Reorder buffer ID value
	 * If incoming read transaction ID ANDed with Reorder_ID_Mask is equal to this register,
	 * then the transaction is mapped to the DDR controller bypass channel
	 * Reset: 0x0         Access: RW
	 */
	uint32_t reorder_id_value_0;
	/* [0x38] */
	uint32_t reorder_id_ch_en_0;
	/* [0x3c] */
	uint32_t rsrvd_4;
	/*
	 * [0x40] DDR Read Reorder buffer ID mask.
	 * If incoming read transaction ID ANDed with mask is equal Reorder_ID_Value, then the
	 * transaction is mapped to the DDR controller bypass channel.
	 * Setting this register to 0 will disable the check
	 * Reset: 0x0         Access: RW
	 */
	uint32_t reorder_id_mask_1;
	/*
	 * [0x44] DDR Read Reorder buffer ID value
	 * If incoming read transaction ID ANDed with Reorder_ID_Mask is equal to this register,
	 * then the transaction is mapped to the DDR controller bypass channel
	 * Reset: 0x0         Access: RW
	 */
	uint32_t reorder_id_value_1;
	/* [0x48] */
	uint32_t reorder_id_ch_en_1;
	/* [0x4c] */
	uint32_t rsrvd_5;
	/*
	 * [0x50] DDR Read Reorder buffer ID mask.
	 * If incoming read transaction ID ANDed with mask is equal Reorder_ID_Value, then the
	 * transaction is mapped to the DDR controller bypass channel.
	 * Setting this register to 0 will disable the check
	 * Reset: 0x0         Access: RW
	 */
	uint32_t reorder_id_mask_2;
	/*
	 * [0x54] DDR Read Reorder buffer ID value
	 * If incoming read transaction ID ANDed with Reorder_ID_Mask is equal to this register,
	 * then the transaction is mapped to the DDR controller bypass channel
	 * Reset: 0x0         Access: RW
	 */
	uint32_t reorder_id_value_2;
	/* [0x58] */
	uint32_t reorder_id_ch_en_2;
	/* [0x5c] */
	uint32_t rsrvd_6;
	/*
	 * [0x60] DDR Read Reorder buffer ID mask.
	 * If incoming read transaction ID ANDed with mask is equal Reorder_ID_Value, then the
	 * transaction is mapped to the DDR controller bypass channel.
	 * Setting this register to 0 will disable the check
	 * Reset: 0x0         Access: RW
	 */
	uint32_t reorder_id_mask_3;
	/*
	 * [0x64] DDR Read Reorder buffer ID value
	 * If incoming read transaction ID ANDed with Reorder_ID_Mask is equal to this register,
	 * then the transaction is mapped to the DDR controller bypass channel
	 * Reset: 0x0         Access: RW
	 */
	uint32_t reorder_id_value_3;
	/* [0x68] */
	uint32_t reorder_id_ch_en_3;
	/* [0x6c] */
	uint32_t rsrvd_7;
	/*
	 * [0x70] DDR Read Reorder buffer ID mask.
	 * If incoming read transaction ID ANDed with mask is equal Reorder_ID_Value, then the
	 * transaction is mapped to the DDR controller bypass channel.
	 * Setting this register to 0 will disable the check
	 * Reset: 0x0         Access: RW
	 */
	uint32_t reorder_id_mask_4;
	/*
	 * [0x74] DDR Read Reorder buffer ID value
	 * If incoming read transaction ID ANDed with Reorder_ID_Mask is equal to this register,
	 * then the transaction is mapped to the DDR controller bypass channel
	 * Reset: 0x0         Access: RW
	 */
	uint32_t reorder_id_value_4;
	/* [0x78] */
	uint32_t reorder_id_ch_en_4;
	/* [0x7c] */
	uint32_t rsrvd_8;
	/*
	 * [0x80] DDR Read Reorder buffer ID mask.
	 * If incoming read transaction ID ANDed with mask is equal Reorder_ID_Value, then the
	 * transaction is mapped to the DDR controller bypass channel.
	 * Setting this register to 0 will disable the check
	 * Reset: 0x0         Access: RW
	 */
	uint32_t reorder_id_mask_5;
	/*
	 * [0x84] DDR Read Reorder buffer ID value
	 * If incoming read transaction ID ANDed with Reorder_ID_Mask is equal to this register,
	 * then the transaction is mapped to the DDR controller bypass channel
	 * Reset: 0x0         Access: RW
	 */
	uint32_t reorder_id_value_5;
	/* [0x88] */
	uint32_t reorder_id_ch_en_5;
	/* [0x8c] */
	uint32_t rsrvd_9;
	/*
	 * [0x90] DDR Read Reorder buffer ID mask.
	 * If incoming read transaction ID ANDed with mask is equal Reorder_ID_Value, then the
	 * transaction is mapped to the DDR controller bypass channel.
	 * Setting this register to 0 will disable the check
	 * Reset: 0x0         Access: RW
	 */
	uint32_t reorder_id_mask_6;
	/*
	 * [0x94] DDR Read Reorder buffer ID value
	 * If incoming read transaction ID ANDed with Reorder_ID_Mask is equal to this register,
	 * then the transaction is mapped to the DDR controller bypass channel
	 * Reset: 0x0         Access: RW
	 */
	uint32_t reorder_id_value_6;
	/* [0x98] */
	uint32_t reorder_id_ch_en_6;
	/* [0x9c] */
	uint32_t rsrvd_10;
	/*
	 * [0xa0] DDR Read Reorder buffer ID mask.
	 * If incoming read transaction ID ANDed with mask is equal Reorder_ID_Value, then the
	 * transaction is mapped to the DDR controller bypass channel.
	 * Setting this register to 0 will disable the check
	 * Reset: 0x0         Access: RW
	 */
	uint32_t reorder_id_mask_7;
	/*
	 * [0xa4] DDR Read Reorder buffer ID value
	 * If incoming read transaction ID ANDed with Reorder_ID_Mask is equal to this register,
	 * then the transaction is mapped to the DDR controller bypass channel
	 * Reset: 0x0         Access: RW
	 */
	uint32_t reorder_id_value_7;
	/* [0xa8] */
	uint32_t reorder_id_ch_en_7;
	/* [0xac] */
	uint32_t rsrvd_11[5];
	/*
	 * [0xc0] DDR Address Map mask selection.
	 * All address bits in set positions are XOR'ed to generate the DDR bit (bit 0 of mask
	 * corresponds to bit 5 in system address).
	 * When set to 0 - use controller address mapping
	 * Reset: 0x0         Access: RW
	 */
	uint32_t addrmap_cs0;
	/*
	 * [0xc4] DDR Address Map mask selection.
	 * All address bits in set positions are XOR'ed to generate the DDR bit (bit 0 of mask
	 * corresponds to bit 5 in system address).
	 * When set to 0 - use controller address mapping
	 * Reset: 0x0         Access: RW
	 */
	uint32_t addrmap_cs1;
	/*
	 * [0xc8] DDR Address Map mask selection.
	 * All address bits in set positions are XOR'ed to generate the DDR bit (bit 0 of mask
	 * corresponds to bit 5 in system address).
	 * When set to 0 - use controller address mapping
	 * Reset: 0x0         Access: RW
	 */
	uint32_t addrmap_cid0;
	/*
	 * [0xcc] DDR Address Map mask selection.
	 * All address bits in set positions are XOR'ed to generate the DDR bit (bit 0 of mask
	 * corresponds to bit 5 in system address).
	 * When set to 0 - use controller address mapping
	 * Reset: 0x0         Access: RW
	 */
	uint32_t addrmap_cid1;
	/*
	 * [0xd0] DDR Address Map mask selection.
	 * All address bits in set positions are XOR'ed to generate the DDR bit (bit 0 of mask
	 * corresponds to bit 5 in system address).
	 * When set to 0 - use controller address mapping
	 * Reset: 0x0         Access: RW
	 */
	uint32_t addrmap_bg0;
	/*
	 * [0xd4] DDR Address Map mask selection.
	 * All address bits in set positions are XOR'ed to generate the DDR bit (bit 0 of mask
	 * corresponds to bit 5 in system address).
	 * When set to 0 - use controller address mapping
	 * Reset: 0x0         Access: RW
	 */
	uint32_t addrmap_bg1;
	/*
	 * [0xd8] DDR Address Map mask selection.
	 * All address bits in set positions are XOR'ed to generate the DDR bit (bit 0 of mask
	 * corresponds to bit 5 in system address).
	 * When set to 0 - use controller address mapping
	 * Reset: 0x0         Access: RW
	 */
	uint32_t addrmap_ba0;
	/*
	 * [0xdc] DDR Address Map mask selection.
	 * All address bits in set positions are XOR'ed to generate the DDR bit (bit 0 of mask
	 * corresponds to bit 5 in system address).
	 * When set to 0 - use controller address mapping
	 * Reset: 0x0         Access: RW
	 */
	uint32_t addrmap_ba1;
	/* [0xe0] */
	uint32_t rsrvd_12[8];
	/* [0x100] */
	uint32_t mrr_control_status;
	/*
	 * [0x104] Counter Configuration Register
	 * MRR Read Data
	 * 8 bits per device (counted as x4 devices)
	 * [7:0] - Device 0
	 * [15:8] - Device 1
	 * [23:16] - Device 2
	 * [31:24] - Device 3
	 * Reset: 0x0         Access: RO
	 */
	uint32_t mrr_0;
	/*
	 * [0x108] Counter Configuration Register
	 * MRR Read Data
	 * 8 bits per device (counted as x4 devices)
	 * [7:0] - Device 4
	 * [15:8] - Device 5
	 * [23:16] - Device 6
	 * [31:24] - Device 7
	 * Reset: 0x0         Access: RO
	 */
	uint32_t mrr_1;
	/*
	 * [0x10c] Counter Configuration Register
	 * MRR Read Data
	 * 8 bits per device (counted as x4 devices)
	 * [7:0] - Device 8
	 * [15:8] - Device 9
	 * [23:16] - Device 10
	 * [31:24] - Device 11
	 * Reset: 0x0         Access: RO
	 */
	uint32_t mrr_2;
	/*
	 * [0x110] Counter Configuration Register
	 * MRR Read Data
	 * 8 bits per device (counted as x4 devices)
	 * [7:0] - Device 12
	 * [15:8] - Device 13
	 * [23:16] - Device 14
	 * [31:24] - Device 15
	 * Reset: 0x0         Access: RO
	 */
	uint32_t mrr_3;
	/*
	 * [0x114] Counter Configuration Register
	 * MRR Read Data
	 * 8 bits per device (counted as x4 devices)
	 * [7:0] - Device 16
	 * [15:8] - Device 17
	 * Reset: 0x0         Access: RO
	 */
	uint32_t mrr_4;
	/* [0x118] */
	uint32_t rsrvd_13[6];
	/* [0x130] */
	uint32_t phy_smode_control;
	/* [0x134] */
	uint32_t phy_smode_status;
	/* [0x138] */
	uint32_t rsrvd_14[50];
};

struct al_ddrc_regs {
	/* [0x0] */
	struct al_ddrc_global global;
	/* [0x100] Interrupt Controller */
	struct al_ddrc_mem mem;
	/* [0x140] */
	uint32_t rsrvd_0[1456];
	/* [0x1800] */
	struct al_ddrc_channel channel;
	/* [0x1a00] */
	uint32_t rsrvd_1[2432];
};


/*
 * Registers Fields
 */

/**** ver register ****/
/*
 * Revision number (Minor)
 * Reset: 0x1         Access: RO
 */
#define DDRC_GLOBAL_VER_DEVICE_REV_ID_MASK 0x0000FFFF
#define DDRC_GLOBAL_VER_DEVICE_REV_ID_SHIFT 0
/*
 * Revision number (Major)
 * Reset: 0x3         Access: RO
 */
#define DDRC_GLOBAL_VER_DEVICE_ID_MASK   0xFFFF0000
#define DDRC_GLOBAL_VER_DEVICE_ID_SHIFT  16

/**** cntrl1 register ****/
/*
 * Threshold for LPR queue.
 * When LPR queue in DDRC is filled with more then this threshold ddrc limits CCI transactions to a
 * specific QOS value (ddr_hp_qos)
 * Reset: 0x15        Access: RW
 */
#define DDRC_GLOBAL_CNTRL1_DDRC_LPR_Q_THRESHOLD_MASK 0x0000007F
#define DDRC_GLOBAL_CNTRL1_DDRC_LPR_Q_THRESHOLD_SHIFT 0
/*
 * QOS lower bound for ddr high priority setting, access above this limit is mapped to high priority
 * Reset: 0x7         Access: RW
 */
#define DDRC_GLOBAL_CNTRL1_DDR_HP_QOS_MASK 0x00000F00
#define DDRC_GLOBAL_CNTRL1_DDR_HP_QOS_SHIFT 8
/*
 * When HP buffer is full HP access is mapped to this QOS value
 * Reset: 0x6         Access: RW
 */
#define DDRC_GLOBAL_CNTRL1_DDR_HP_FULL_MAP_QOS_MASK 0x0000F000
#define DDRC_GLOBAL_CNTRL1_DDR_HP_FULL_MAP_QOS_SHIFT 12
/*
 * Should be configured to (DDR #high priority credits)
 * Reset: 0x23        Access: RW
 */
#define DDRC_GLOBAL_CNTRL1_HIGH_PRIO_THRESHOLD_MASK 0x007F0000
#define DDRC_GLOBAL_CNTRL1_HIGH_PRIO_THRESHOLD_SHIFT 16
/*
 * This should be set high only if DDRC splits unaligned wrap read transcations into internal 2
 * transcations.
 * Reset: 0x0         Access: RW
 */
#define DDRC_GLOBAL_CNTRL1_SPLITS_UNALIGNED_WRAP (1 << 24)
/*
 * Set this bit to allow using the AUTOPRE logic in the DDRC
 * Reset: 0x1         Access: RW
 */
#define DDRC_GLOBAL_CNTRL1_AUTOPRE_CHICKEN (1 << 29)
/*
 * Set this bit to disable wdata onchip parity bug fix
 * Reset: 0x0         Access: RW
 */
#define DDRC_GLOBAL_CNTRL1_WDATA_PAR_CHICKEN (1 << 30)
/*
 * If set, disables ECC uncorrectable error injection on write part of RMW in case of encountering
 * uncorrectable ECC error on read part.
 * Should be enabled when initializing ECC in DRAM using writes on AXI port.
 * Reset: 0x0         Access: RW
 */
#define DDRC_GLOBAL_CNTRL1_RMW_UNCORR_INJECT_DIS (1 << 31)

/**** crc_retry register ****/
/*
 * Threshold for number of crc retry events that trigger the error interrupt
 * Reset: 0xffff      Access: RW
 */
#define DDRC_GLOBAL_CRC_RETRY_INTERRUPT_THRSLD_MASK 0x0000FFFF
#define DDRC_GLOBAL_CRC_RETRY_INTERRUPT_THRSLD_SHIFT 0

/**** lp register ****/
/*
 * Indication for DDRC internal quese empty. Software should write 1'b1 to this bit (set) then poll
 * this bit. When this is cleared by HW the internal DDRC queues are empty.
 * Reset: 0x1         Access: RW, W1toSet
 */
#define DDRC_GLOBAL_LP_CAM_FIFOS_IN_USE  (1 << 0)

/**** pmu register ****/
/* Reset: 0x0         Access: RW */
#define DDRC_GLOBAL_PMU_PERF_SEL_IOCACHE (1 << 0)
/*
 * selects 1 out of rank/cid/bank/bg bits into the configuration for 16 PMU counters
 * Reset: 0x0         Access: RW
 */
#define DDRC_GLOBAL_PMU_PERF_SEL_B3_MASK 0x00000030
#define DDRC_GLOBAL_PMU_PERF_SEL_B3_SHIFT 4
/*
 * selects 1 out of rank/cid/bank/bg bits into the configuration for 16 PMU counters
 * Reset: 0x0         Access: RW
 */
#define DDRC_GLOBAL_PMU_PERF_SEL_B2_MASK 0x000000C0
#define DDRC_GLOBAL_PMU_PERF_SEL_B2_SHIFT 6
/*
 * selects 1 out of rank/cid/bank/bg bits into the configuration for 16 PMU counters
 * Reset: 0x0         Access: RW
 */
#define DDRC_GLOBAL_PMU_PERF_SEL_B1_MASK 0x00000300
#define DDRC_GLOBAL_PMU_PERF_SEL_B1_SHIFT 8
/*
 * selects 1 out of rank/cid/bank/bg bits into the configuration for 16 PMU counters
 * Reset: 0x0         Access: RW
 */
#define DDRC_GLOBAL_PMU_PERF_SEL_B0_MASK 0x00000C00
#define DDRC_GLOBAL_PMU_PERF_SEL_B0_SHIFT 10
/*
 * Selects whether to count ACT operation in the PMU counters for bank performance
 * Reset: 0x1         Access: RW
 */
#define DDRC_GLOBAL_PMU_ALLOW_COUNT_ACT_BYPASS (1 << 12)
/*
 * Selects whether to count read bypass operation in the PMU counters for bank performance
 * Reset: 0x1         Access: RW
 */
#define DDRC_GLOBAL_PMU_ALLOW_COUNT_RD_BYPASS (1 << 13)
/*
 * Selects whether to count write operation in the PMU counters for bank performance
 * Reset: 0x1         Access: RW
 */
#define DDRC_GLOBAL_PMU_ALLOW_COUNT_OP_IS_WR (1 << 14)
/*
 * Selects whether to count read operation in the PMU counters for bank performance
 * Reset: 0x1         Access: RW
 */
#define DDRC_GLOBAL_PMU_ALLOW_COUNT_OP_IS_RD (1 << 15)
/*
 * Selects how to map bank performance events on the input bus event to local PMU (2'b00 - don't map
 * 16 byte events, 2'b01 - map them over bytes 1&0 of the pmu_events, 2'b1x - map them over bytes
 * 3&2 of the pmu_events)
 * Reset: 0x0         Access: RW
 */
#define DDRC_GLOBAL_PMU_PERF_BANK_LOC_SEL_MASK 0x00030000
#define DDRC_GLOBAL_PMU_PERF_BANK_LOC_SEL_SHIFT 16

/**** termination register ****/
/*
 * Set this bit high to allow usage of awpoison logic in the DDRC
 * Reset: 0x1         Access: RW
 */
#define DDRC_GLOBAL_TERMINATION_WR_POISON (1 << 0)
/*
 * Set this bit when DDRC is in low power and IOCACHE is used. This sets the AXI B channel to
 * respond correctly
 * Reset: 0x1         Access: RW
 */
#define DDRC_GLOBAL_TERMINATION_ACTIVATE (1 << 1)
/*
 * In case AXI termination is used this configuration enables the parity check. In case of parity
 * failure if this bit is set then the AXI write response will be SLVERR
 * Reset: 0x1         Access: RW
 */
#define DDRC_GLOBAL_TERMINATION_PARITY_RESP (1 << 2)

/**** urgent register ****/
/*
 * Threshold for urgent assertion for LPR.
 * When LPR credit is smaller than this configuration, urgent signal will be asserted
 * Reset: 0x0         Access: RW
 */
#define DDRC_GLOBAL_URGENT_LPR_THRESHOLD_MASK 0x0000007F
#define DDRC_GLOBAL_URGENT_LPR_THRESHOLD_SHIFT 0
/*
 * Threshold for urgent assertion for HPR.
 * When HPR credit is smaller than this configuration, urgent signal will be asserted
 * Reset: 0x0         Access: RW
 */
#define DDRC_GLOBAL_URGENT_HPR_THRESHOLD_MASK 0x00007F00
#define DDRC_GLOBAL_URGENT_HPR_THRESHOLD_SHIFT 8
/*
 * Threshold for urgent assertion for WR.
 * When WR credit is smaller than this configuration, urgent signal will be asserted
 * Reset: 0x0         Access: RW
 */
#define DDRC_GLOBAL_URGENT_WR_THRESHOLD_MASK 0x007F0000
#define DDRC_GLOBAL_URGENT_WR_THRESHOLD_SHIFT 16

/**** arurgent_timeout register ****/
/*
 * Number of cycles to keep urgent signal low after assertion
 * Reset: 0x0         Access: RW
 */
#define DDRC_GLOBAL_ARURGENT_TIMEOUT_LOW_MASK 0x0000FFFF
#define DDRC_GLOBAL_ARURGENT_TIMEOUT_LOW_SHIFT 0
/*
 * Maximum number of cycles to assert urgent signal
 * Reset: 0x0         Access: RW
 */
#define DDRC_GLOBAL_ARURGENT_TIMEOUT_HIGH_MASK 0xFFFF0000
#define DDRC_GLOBAL_ARURGENT_TIMEOUT_HIGH_SHIFT 16

/**** awurgent_timeout register ****/
/*
 * Number of cycles to keep urgent signal low after assertion
 * Reset: 0x0         Access: RW
 */
#define DDRC_GLOBAL_AWURGENT_TIMEOUT_LOW_MASK 0x0000FFFF
#define DDRC_GLOBAL_AWURGENT_TIMEOUT_LOW_SHIFT 0
/*
 * Maximum number of cycles to assert urgent signal
 * Reset: 0x0         Access: RW
 */
#define DDRC_GLOBAL_AWURGENT_TIMEOUT_HIGH_MASK 0xFFFF0000
#define DDRC_GLOBAL_AWURGENT_TIMEOUT_HIGH_SHIFT 16

/**** sd register ****/
/*
 * Shut down control for WDATA RAM
 * Reset: 0x0         Access: RW
 */
#define DDRC_MEM_SD_WDATA_MASK           0x00000003
#define DDRC_MEM_SD_WDATA_SHIFT          0
/*
 * Shut down control for CRC retry RAM
 * Reset: 0x0         Access: RW
 */
#define DDRC_MEM_SD_CRC_MASK             0x0000000C
#define DDRC_MEM_SD_CRC_SHIFT            2
/*
 * Shut down control for ELA memory in PMDTU
 * Reset: 0x0         Access: RW
 */
#define DDRC_MEM_SD_ELA                  (1 << 4)

/**** cntrl register ****/
/*
 * Controller Idle
 * Indicates to the DDR PHY, if set, that the memory controller is idle
 * Reset: 0x0         Access: RW
 */
#define DDRC_CHANNEL_CNTRL_DDR_PHY_CTL_IDLE (1 << 0)
/*
 * Disable clear exclusive monitor request from DDR controller to CPU
 * Clear request is triggered whenever an exlusive monitor inside the DDR controller is being
 * invalidated.
 * Reset: 0x0         Access: RW
 */
#define DDRC_CHANNEL_CNTRL_DDR_EXMON_REQ_DIS (1 << 1)

/**** hold_reset register ****/
/*
 * DDR Control and PHY memory mapped registers reset control
 * 0 - Reset is deasserted.
 * 1 - Reset is asserted (active).
 * Reset: 0x0         Access: RW
 */
#define DDRC_CHANNEL_HOLD_RESET_APB_SYNC_RESET (1 << 0)
/*
 * DDR Control Core reset control
 * 0 - Reset is deasserted.
 * 1 - Reset is asserted.
 * This field must be set to 0 to start the initialization process after configuring the DDR
 * Controller registers.
 * Reset: 0x1         Access: RW
 */
#define DDRC_CHANNEL_HOLD_RESET_CORE_SYNC_RESET (1 << 1)
/*
 * DDR Control AXI Interface reset control
 * 0 - Reset is deasserted.
 * 1 - Reset is asserted.
 * This field must not be set to 0 while core_sync_reset is set to 1.
 * Reset: 0x1         Access: RW
 */
#define DDRC_CHANNEL_HOLD_RESET_AXI_SYNC_RESET (1 << 2)
/*
 * DDR PUB Controller reset control
 * 0 - Reset is deasserted.
 * 1 - Reset is asserted.
 * This field must be set to 0 to start the initialization process after configuring the PUB
 * Controller registers.
 * Reset: 0x0         Access: RW
 */
#define DDRC_CHANNEL_HOLD_RESET_PUB_CTL_SYNC_RESET (1 << 3)
/*
 * DDR PUB SDR Controller reset control
 * 0 - Reset is deasserted.
 * 1 - Reset is asserted.
 * This field must be set to 0 to start the initialization process after configuring the PUB
 * Controller registers.
 * Reset: 0x0         Access: RW
 */
#define DDRC_CHANNEL_HOLD_RESET_PUB_SDR_SYNC_RESET (1 << 4)

/**** status register ****/
/*
 * Bypass Mode: Indicates if set that the PHY is in PLL bypass mod
 * Reset: 0x0         Access: RO
 */
#define DDRC_CHANNEL_STATUS_DDR_PHY_BYP_MODE (1 << 0)
/*
 * Number of available AXI transactions (used positions) in the DDR controller read address FIFO.
 * Reset: 0x0         Access: RO
 */
#define DDRC_CHANNEL_STATUS_RAQ_WCOUNT_MASK 0x00000030
#define DDRC_CHANNEL_STATUS_RAQ_WCOUNT_SHIFT 4
/*
 * Number of available AXI transactions (used positions) in the DDR controller write address FIFO
 * Reset: 0x0         Access: RO
 */
#define DDRC_CHANNEL_STATUS_WAQ_WCOUNT_0_MASK 0x000000C0
#define DDRC_CHANNEL_STATUS_WAQ_WCOUNT_0_SHIFT 6
/*
 * Number of available Low priority read CAM slots (free positions) in  the DDR controller.
 * Each slots holds a DRAM burst
 * Reset: 0x0         Access: RO
 */
#define DDRC_CHANNEL_STATUS_LPR_CREDIT_CNT_MASK 0x00007F00
#define DDRC_CHANNEL_STATUS_LPR_CREDIT_CNT_SHIFT 8
/*
 * Number of available High priority read CAM slots (free positions) in  the DDR controller.
 * Each slots holds a DRAM burst
 * Reset: 0x0         Access: RO
 */
#define DDRC_CHANNEL_STATUS_HPR_CREDIT_CNT_MASK 0x003F8000
#define DDRC_CHANNEL_STATUS_HPR_CREDIT_CNT_SHIFT 15
/*
 * Number of available write CAM slots (free positions) in  the DDR controller.
 * Each slots holds a DRAM burst
 * Reset: 0x0         Access: RO
 */
#define DDRC_CHANNEL_STATUS_WR_CREDIT_CNT_MASK 0x1FC00000
#define DDRC_CHANNEL_STATUS_WR_CREDIT_CNT_SHIFT 22

/**** int_cause register ****/
/*
 * This interrupt is asserted when a correctable ECC error is detected
 * Reset: 0x0         Access: RW, W0toClr
 */
#define DDRC_CHANNEL_INT_CAUSE_ECC_CORRECTED_ERR (1 << 0)
/*
 * This interrupt is asserted when a uncorrectable ECC error is detected
 * Reset: 0x0         Access: RW, W0toClr
 */
#define DDRC_CHANNEL_INT_CAUSE_ECC_UNCORRECTED_ERR (1 << 1)
/*
 * This interrupt is asserted when a parity or CRC error is detected on the DFI interface
 * Reset: 0x0         Access: RW, W0toClr
 */
#define DDRC_CHANNEL_INT_CAUSE_DFI_ALERT_ERR (1 << 2)
/*
 * On-Chip Write data parity error interrupt on output
 * Reset: 0x0         Access: RW, W0toClr
 */
#define DDRC_CHANNEL_INT_CAUSE_PAR_WDATA_OUT_ERR (1 << 3)
/*
 * This interrupt is asserted when a parity error due to MRS is detected on the DFI interface
 * Reset: 0x0         Access: RW, W0toClr
 */
#define DDRC_CHANNEL_INT_CAUSE_DFI_ALERT_ERR_FATL (1 << 4)
/*
 * This interrupt is asserted when the CRC/parity retry counter reaches it maximum value
 * Reset: 0x0         Access: RW, W0toClr
 */
#define DDRC_CHANNEL_INT_CAUSE_DFI_ALERT_ERR_MAX_REACHED (1 << 5)
/*
 * AXI Read address parity error interrupt.
 * This interrupt is asserted when an on-chip parity error occurred on the DDR controller AXI read
 * address.
 * Reset: 0x0         Access: RW, W0toClr
 */
#define DDRC_CHANNEL_INT_CAUSE_PAR_RADDR_ERR (1 << 6)
/*
 * AXI Read data parity error interrupt.
 * This interrupt is asserted when an on-chip parity error occurred on the DDR controller AXI read
 * data
 * Reset: 0x0         Access: RW, W0toClr
 */
#define DDRC_CHANNEL_INT_CAUSE_PAR_RDATA_ERR (1 << 7)
/*
 * AXI Write address parity error interrupt.
 * This interrupt is asserted when an on-chip parity error occurred on the DDR controller AXI write
 * address.
 * Reset: 0x0         Access: RW, W0toClr
 */
#define DDRC_CHANNEL_INT_CAUSE_PAR_WADDR_ERR (1 << 8)
/*
 * AXI Write data parity error interrupt on input.
 * This interrupt is asserted when an on-chip parity error occurred on the DDR controller AXI write
 * data
 * Reset: 0x0         Access: RW, W0toClr
 */
#define DDRC_CHANNEL_INT_CAUSE_PAR_WDATA_IN_ERR (1 << 9)

/**** address_map register ****/
/*
 * swap system address [19:17] with system address [16:14]
 * Reset: 0x0         Access: RW
 */
#define DDRC_CHANNEL_ADDRESS_MAP_SWAP_EN (1 << 30)

/**** reorder_id_ch_en_0 register ****/
/*
 * DDR Read Reorder buffer ID channel enable
 * Selects for which virtual channels this mask and ID would be applied.
 * Reset: 0xff        Access: RW
 */
#define DDRC_CHANNEL_REORDER_ID_CH_EN_0_BITWISE_MASK 0x000000FF
#define DDRC_CHANNEL_REORDER_ID_CH_EN_0_BITWISE_SHIFT 0

/**** reorder_id_ch_en_1 register ****/
/*
 * DDR Read Reorder buffer ID channel enable
 * Selects for which virtual channels this mask and ID would be applied.
 * Reset: 0xff        Access: RW
 */
#define DDRC_CHANNEL_REORDER_ID_CH_EN_1_BITWISE_MASK 0x000000FF
#define DDRC_CHANNEL_REORDER_ID_CH_EN_1_BITWISE_SHIFT 0

/**** reorder_id_ch_en_2 register ****/
/*
 * DDR Read Reorder buffer ID channel enable
 * Selects for which virtual channels this mask and ID would be applied.
 * Reset: 0xff        Access: RW
 */
#define DDRC_CHANNEL_REORDER_ID_CH_EN_2_BITWISE_MASK 0x000000FF
#define DDRC_CHANNEL_REORDER_ID_CH_EN_2_BITWISE_SHIFT 0

/**** reorder_id_ch_en_3 register ****/
/*
 * DDR Read Reorder buffer ID channel enable
 * Selects for which virtual channels this mask and ID would be applied.
 * Reset: 0xff        Access: RW
 */
#define DDRC_CHANNEL_REORDER_ID_CH_EN_3_BITWISE_MASK 0x000000FF
#define DDRC_CHANNEL_REORDER_ID_CH_EN_3_BITWISE_SHIFT 0

/**** reorder_id_ch_en_4 register ****/
/*
 * DDR Read Reorder buffer ID channel enable
 * Selects for which virtual channels this mask and ID would be applied.
 * Reset: 0xff        Access: RW
 */
#define DDRC_CHANNEL_REORDER_ID_CH_EN_4_BITWISE_MASK 0x000000FF
#define DDRC_CHANNEL_REORDER_ID_CH_EN_4_BITWISE_SHIFT 0

/**** reorder_id_ch_en_5 register ****/
/*
 * DDR Read Reorder buffer ID channel enable
 * Selects for which virtual channels this mask and ID would be applied.
 * Reset: 0xff        Access: RW
 */
#define DDRC_CHANNEL_REORDER_ID_CH_EN_5_BITWISE_MASK 0x000000FF
#define DDRC_CHANNEL_REORDER_ID_CH_EN_5_BITWISE_SHIFT 0

/**** reorder_id_ch_en_6 register ****/
/*
 * DDR Read Reorder buffer ID channel enable
 * Selects for which virtual channels this mask and ID would be applied.
 * Reset: 0xff        Access: RW
 */
#define DDRC_CHANNEL_REORDER_ID_CH_EN_6_BITWISE_MASK 0x000000FF
#define DDRC_CHANNEL_REORDER_ID_CH_EN_6_BITWISE_SHIFT 0

/**** reorder_id_ch_en_7 register ****/
/*
 * DDR Read Reorder buffer ID channel enable
 * Selects for which virtual channels this mask and ID would be applied.
 * Reset: 0xff        Access: RW
 */
#define DDRC_CHANNEL_REORDER_ID_CH_EN_7_BITWISE_MASK 0x000000FF
#define DDRC_CHANNEL_REORDER_ID_CH_EN_7_BITWISE_SHIFT 0

/**** mrr_control_status register ****/
/*
 * DDR4 Mode Register Read Data Valid
 * Reset: 0x0         Access: RO
 */
#define DDRC_CHANNEL_MRR_CONTROL_STATUS_VLD (1 << 0)
/*
 * MRR Ack, when asserted it clears the mrr_val indication and ready to load new MRR data. Write 1
 * to clear and then 0
 * Reset: 0x0         Access: WO
 */
#define DDRC_CHANNEL_MRR_CONTROL_STATUS_ACK (1 << 16)

/**** phy_smode_control register ****/
/*
 * DDR PHY special mode
 * Reset: 0x0         Access: RW
 */
#define DDRC_CHANNEL_PHY_SMODE_CONTROL_CTL_MASK 0x0000FFFF
#define DDRC_CHANNEL_PHY_SMODE_CONTROL_CTL_SHIFT 0

/**** phy_smode_status register ****/
/*
 * DDR PHY special mode
 * Reset: 0x0         Access: RO
 */
#define DDRC_CHANNEL_PHY_SMODE_STATUS_STT_MASK 0x0000FFFF
#define DDRC_CHANNEL_PHY_SMODE_STATUS_STT_SHIFT 0

#ifdef __cplusplus
}
#endif

#endif

/** @} */
