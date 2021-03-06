/*******************************************************************************
Copyright (C) 2015 Annapurna Labs Ltd.

This file may be licensed under the terms of the Annapurna Labs Commercial
License Agreement.

Alternatively, this file can be distributed under the terms of the GNU General
Public License V2 as published by the Free Software Foundation and can be
found at http://www.gnu.org/licenses/gpl-2.0.html

Alternatively, redistribution and use in source and binary forms, with or
without modification, are permitted provided that the following conditions are
met:

    *     Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.

    *     Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in
the documentation and/or other materials provided with the
distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*******************************************************************************/

/**
 * @defgroup group_eth_api API
 * Ethernet Controller HAL driver API
 * @ingroup group_eth
 * @{
 * @file   al_mod_hal_eth.h
 *
 * @brief Header file for Unified GbE and 10GbE Ethernet Controllers This is a
 * common header file that covers both Standard and Advanced Controller
 *
 *
 */

#ifndef __AL_HAL_ETH_H__
#define __AL_HAL_ETH_H__

#include "al_mod_hal_common.h"
#include "al_mod_hal_udma.h"
#include "al_mod_hal_eth_common.h"
#include "al_mod_hal_eth_alu.h"
#include "al_mod_hal_eth_mac.h"
#include "al_mod_hal_eth_epe.h"
#include "al_mod_hal_eth_defs.h"
#ifdef AL_ETH_EX
#include "al_mod_hal_eth_ex.h"
#endif

#if defined(AL_ETH_EX) && defined(AL_DEV_ID)
#if (AL_DEV_ID == AL_DEV_ID_ALPINE_V3)
#define AL_ETH_EX_HAS_EXT_METADATA
#include "al_mod_hal_eth_ex_internal_v4.h"
#endif
#endif

/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif
/* *INDENT-ON* */

#define AL_ETH_HAS_DESC_API

#if defined(AL_ETH_EX) && (AL_DEV_ID >= AL_DEV_ID_ALPINE_V3)
#define AL_ETH_HAS_CSP_API
#endif

#ifndef AL_ETH_PKT_MAX_BUFS
#ifndef AL_ETH_EX
#define AL_ETH_PKT_MAX_BUFS 19
#else
#define AL_ETH_PKT_MAX_BUFS 30
#endif
#endif

#define AL_ETH_UDMA_TX_QUEUES 4
#define AL_ETH_UDMA_RX_QUEUES 4
#define AL_ETH_UDMA_TX_QUEUES_BY_REV(rev_id) \
	(((rev_id) >= AL_ETH_REV_ID_4) ? 16 : 4)
#define AL_ETH_UDMA_RX_QUEUES_BY_REV(rev_id) \
	(((rev_id) >= AL_ETH_REV_ID_4) ? 16 : 4)

#define AL_ETH_UDMA_HW_QUEUES_V3 DMA_MAX_Q_V3
#define AL_ETH_UDMA_HW_QUEUES_V4 DMA_MAX_Q_V4
#define AL_ETH_UDMA_HW_QUEUES_MAX DMA_MAX_Q_V4

#define AL_ETH_UDMA_HW_QUEUES_BY_REV(rev_id) \
	(((rev_id) >= AL_ETH_REV_ID_4) ? AL_ETH_UDMA_HW_QUEUES_V4 : AL_ETH_UDMA_HW_QUEUES_V3)

#define AL_ETH_UDMA_MAX_ADV_REV_ID_4	4

/* PCI Adapter Device/Revision ID */
#define AL_ETH_DEV_ID_STANDARD		0x0001
#define AL_ETH_DEV_ID_ADVANCED		0x0002
#define AL_ETH_REV_ID_1			1 /* Alpine V1 */
#define AL_ETH_REV_ID_2			2 /* Alpine V2 basic */
#define AL_ETH_REV_ID_3			3 /* Alpine V2 advanced */
#define AL_ETH_REV_ID_4			4 /* Alpine V3 advanced */

/* PCI BARs */
#define AL_ETH_UDMA_BAR			0
#define AL_ETH_EC_BAR			4
#define AL_ETH_MAC_BAR			2

#define AL_ETH_MAX_FRAME_LEN		10240
#define AL_ETH_MIN_FRAME_LEN		60

#define AL_ETH_TSO_MSS_MAX_IDX		8
/**
 * Addressing RMN: 11632
 * See al_mod_eth_tx_pkt_prepare() for further details
 */
#define AL_ETH_TSO_MSS_MIN_VAL		64
/*TODO: update with correct value*/
#define AL_ETH_TSO_MSS_MAX_VAL		(AL_ETH_MAX_FRAME_LEN - 200)
#define AL_ETH_TSO_METACACHE_LINE_SIZE	4 /* Size of 32bit words */

#define GPIO_SPD_NOT_AVAILABLE 	-1

/* If a new protocol is added to the default  EPE table, need to update
 * the AL_ETH_EPE_LAST_USED_ENTRY macro */
enum AL_ETH_PROTO_ID {
	AL_ETH_PROTO_ID_UNKNOWN     = 0,
	AL_ETH_PROTO_ID_IPv4	    = 8,
	AL_ETH_PROTO_ID_IPv6	    = 11,
	AL_ETH_PROTO_ID_TCP	    = 12,
	AL_ETH_PROTO_ID_UDP	    = 13,
	AL_ETH_PROTO_ID_USR_DEF     = 14, /** User Defined protocols */
	AL_ETH_PROTO_ID_USR_DEF2    = 15,
	AL_ETH_PROTO_ID_USR_DEF3    = 16,
	AL_ETH_PROTO_ID_USR_DEF4    = 17,
	AL_ETH_PROTO_ID_DEFAULT	    = 31, /** Default for undetected protocol */
	AL_ETH_PROTO_ID_ANY	    = 32, /**< for sw usage only */
};

#define AL_ETH_PROTOCOLS_NUM		(AL_ETH_EPE_TABLE_SIZE)
/* If a new protocol is added to the EPE table, need to update the following macro */
#define AL_ETH_EPE_LAST_USED_ENTRY	14
/* This macro represents the number of entries excluding the default entry at the end */
#define AL_ETH_EPE_ENTRIES_NUM		(AL_ETH_EPE_LAST_USED_ENTRY + 1)
#define AL_ETH_EPE_TABLE_SIZE		32

enum AL_ETH_TX_TUNNEL_MODE {
	AL_ETH_NO_TUNNELING	= 0,
	AL_ETH_TUNNEL_NO_UDP	= 1, /* NVGRE / IP over IP */
	AL_ETH_TUNNEL_WITH_UDP	= 3,	/* VXLAN */
};

#define AL_ETH_RX_THASH_TABLE_SIZE	(1 << 8)
#define AL_ETH_RX_FSM_TABLE_SIZE	(1 << 7)
#define AL_ETH_RX_CTRL_TABLE_SIZE	(1 << 11)
#define AL_ETH_RX_HASH_KEY_NUM		10
#define AL_ETH_FWD_MAC_NUM			32
#define AL_ETH_FWD_MAC_HASH_NUM			256
#define AL_ETH_FWD_PBITS_TABLE_NUM	(1 << 3)
#define AL_ETH_FWD_PRIO_TABLE_NUM	(1 << 3)
#define AL_ETH_FWD_VID_TABLE_NUM	(1 << 12)
#define AL_ETH_FWD_DSCP_TABLE_NUM	(1 << 8)
#define AL_ETH_FWD_TC_TABLE_NUM	(1 << 8)

#define AL_ETH_EC_IOFIC_OFFSET		0x1c00
#define AL_ETH_MAC_IOFIC_OFFSET		0x800

/* ETH_EC IOFIC group A */
#define AL_ETH_EC_IOFIC_GROUP_A_MAC_INT_IN			AL_BIT(3)
#define AL_ETH_EC_IOFIC_GROUP_A_ERR_MSW_IN_SOP_IN_PKT		AL_BIT(4)
#define AL_ETH_EC_IOFIC_GROUP_A_ERR_MSW_IN_EOP_IN_IDLE		AL_BIT(5)
#define AL_ETH_EC_IOFIC_GROUP_A_ERR_FWD_OUT_EOP_META_EMPTY	AL_BIT(6)
#define AL_ETH_EC_IOFIC_GROUP_A_ERR_FWD_IN_SOP_IN_PKT		AL_BIT(7)
#define AL_ETH_EC_IOFIC_GROUP_A_ERR_FWD_IN_EOP_IN_IDLE		AL_BIT(8)
#define AL_ETH_EC_IOFIC_GROUP_A_ERR_RPE_3_OUT_EOP_HDR_EMPTY	AL_BIT(9)
#define AL_ETH_EC_IOFIC_GROUP_A_ERR_RPE_3_IN_SOP_IN_PKT		AL_BIT(10)
#define AL_ETH_EC_IOFIC_GROUP_A_ERR_RPE_3_IN_EOP_IN_IDLE	AL_BIT(11)
#define AL_ETH_EC_IOFIC_GROUP_A_ERR_RPE_2_OUT_EOP_HDR_EMPTY	AL_BIT(12)
#define AL_ETH_EC_IOFIC_GROUP_A_ERR_RPE_2_IN_SOP_IN_PKT		AL_BIT(13)
#define AL_ETH_EC_IOFIC_GROUP_A_ERR_RPE_2_IN_EOP_IN_IDLE	AL_BIT(14)
#define AL_ETH_EC_IOFIC_GROUP_A_ERR_RPE_1_OUT_EOP_HDR_EMPTY	AL_BIT(15)
#define AL_ETH_EC_IOFIC_GROUP_A_ERR_RPE_1_IN_SOP_IN_PKT		AL_BIT(16)
#define AL_ETH_EC_IOFIC_GROUP_A_ERR_RPE_1_IN_EOP_IN_IDLE	AL_BIT(17)
#define AL_ETH_EC_IOFIC_GROUP_A_ERR_RXF_OUT_EOP_HDR_EMPTY	AL_BIT(18)
#define AL_ETH_EC_IOFIC_GROUP_A_ERR_LBF_IN_SOP_IN_PKT		AL_BIT(19)
#define AL_ETH_EC_IOFIC_GROUP_A_ERR_LBF_IN_EOP_IN_IDLE		AL_BIT(20)
#define AL_ETH_EC_IOFIC_GROUP_A_ERR_RXF_IN_SOP_IN_PKT		AL_BIT(21)
#define AL_ETH_EC_IOFIC_GROUP_A_ERR_RXF_IN_EOP_IN_IDLE		AL_BIT(22)
#define AL_ETH_EC_IOFIC_GROUP_A_ERR_FAF_2_OUT_EOP_HDR_EMPTY	AL_BIT(23)
#define AL_ETH_EC_IOFIC_GROUP_A_ERR_FAF_2_IN_SOP_IN_PKT		AL_BIT(24)
#define AL_ETH_EC_IOFIC_GROUP_A_ERR_FAF_2_IN_EOP_IN_IDLE	AL_BIT(25)
#define AL_ETH_EC_IOFIC_GROUP_A_ERR_FAF_1_OUT_EOP_HDR_EMPTY	AL_BIT(26)
#define AL_ETH_EC_IOFIC_GROUP_A_ERR_FAF_1_IN_SOP_IN_PKT		AL_BIT(27)
#define AL_ETH_EC_IOFIC_GROUP_A_ERR_FAF_1_IN_EOP_IN_IDLE	AL_BIT(28)

/** ETH v4 */
#define AL_ETH_V4_EC_IOFIC_GROUP_A_MAC_INT_NUM				4
#define AL_ETH_V4_EC_IOFIC_GROUP_A_MAC_INT_IN_0				AL_BIT(3)
#define AL_ETH_V4_EC_IOFIC_GROUP_A_MAC_INT_IN_1				AL_BIT(17)
#define AL_ETH_V4_EC_IOFIC_GROUP_A_MAC_INT_IN_2				AL_BIT(30)
#define AL_ETH_V4_EC_IOFIC_GROUP_A_MAC_INT_IN_3				AL_BIT(31)
#define AL_ETH_V4_EC_IOFIC_GROUP_A_EC_ERR_MSW_IN_SOP_IN_PKT		AL_BIT(4)
#define AL_ETH_V4_EC_IOFIC_GROUP_A_EC_ERR_MSW_IN_EOP_IN_IDLE		AL_BIT(5)
#define AL_ETH_V4_EC_IOFIC_GROUP_A_EC_ERR_FWD_OUT_EOP_META_EMPTY	AL_BIT(6)
#define AL_ETH_V4_EC_IOFIC_GROUP_A_EC_ERR_FWD_IN_SOP_IN_PKT		AL_BIT(7)
#define AL_ETH_V4_EC_IOFIC_GROUP_A_EC_ERR_FWD_IN_EOP_IN_IDLE		AL_BIT(8)
#define AL_ETH_V4_EC_IOFIC_GROUP_A_RMP_INT				AL_BIT(9)
#define AL_ETH_V4_EC_IOFIC_GROUP_A_EC_RFW_PKT_HDR_FIFO_MEM_PAR_ERR_0	AL_BIT(10)
#define AL_ETH_V4_EC_IOFIC_GROUP_A_EC_RFW_PKT_HDR_FIFO_MEM_PAR_ERR_1	AL_BIT(11)
#define AL_ETH_V4_EC_IOFIC_GROUP_A_EC_RFW_META_FIFO_MEM_PAR_ERR_0	AL_BIT(12)
#define AL_ETH_V4_EC_IOFIC_GROUP_A_EC_RFW_META_FIFO_MEM_PAR_ERR_1	AL_BIT(13)
#define AL_ETH_V4_EC_IOFIC_GROUP_A_EC_RFW_META_FIFO_MEM_PAR_ERR_2	AL_BIT(14)
#define AL_ETH_V4_EC_IOFIC_GROUP_A_EC_RFW_DATA_FIFO_MEM_PAR_ERR_0	AL_BIT(15)
#define AL_ETH_V4_EC_IOFIC_GROUP_A_EC_RFW_DATA_FIFO_MEM_PAR_ERR_1	AL_BIT(16)
#define AL_ETH_V4_EC_IOFIC_GROUP_A_EC_ERR_RXF_OUT_EOP_HDR_EMPTY		AL_BIT(18)
#define AL_ETH_V4_EC_IOFIC_GROUP_A_EC_ERR_LBF_IN_SOP_IN_PKT		AL_BIT(19)
#define AL_ETH_V4_EC_IOFIC_GROUP_A_EC_ERR_LBF_IN_EOP_IN_IDLE		AL_BIT(20)
#define AL_ETH_V4_EC_IOFIC_GROUP_A_EC_ERR_RXF_IN_SOP_IN_PKT		AL_BIT(21)
#define AL_ETH_V4_EC_IOFIC_GROUP_A_EC_ERR_RXF_IN_EOP_IN_IDLE		AL_BIT(22)
#define AL_ETH_V4_EC_IOFIC_GROUP_A_EC_ERR_FAF_2_OUT_EOP_HDR_EMPTY	AL_BIT(23)
#define AL_ETH_V4_EC_IOFIC_GROUP_A_EC_ERR_FAF_2_IN_SOP_IN_PKT		AL_BIT(24)
#define AL_ETH_V4_EC_IOFIC_GROUP_A_EC_ERR_FAF_2_IN_EOP_IN_IDLE		AL_BIT(25)
#define AL_ETH_V4_EC_IOFIC_GROUP_A_EC_ERR_FAF_1_OUT_EOP_HDR_EMPTY	AL_BIT(26)
#define AL_ETH_V4_EC_IOFIC_GROUP_A_EC_ERR_FAF_1_IN_SOP_IN_PKT		AL_BIT(27)
#define AL_ETH_V4_EC_IOFIC_GROUP_A_EC_ERR_FAF_1_IN_EOP_IN_IDLE		AL_BIT(28)

/* ETH_EC IOFIC group B */
#define AL_ETH_EC_IOFIC_GROUP_B_ERR_TMI_IN_SOP_IN_PKT		AL_BIT(0)
#define AL_ETH_EC_IOFIC_GROUP_B_ERR_TMI_IN_EOP_IN_IDLE		AL_BIT(1)
#define AL_ETH_EC_IOFIC_GROUP_B_ERR_TFW_OUT_EOP_HDR_EMPTY	AL_BIT(2)
#define AL_ETH_EC_IOFIC_GROUP_B_ERR_TFW_IN_SOP_IN_PKT		AL_BIT(3)
#define AL_ETH_EC_IOFIC_GROUP_B_ERR_TFW_IN_EOP_IN_IDLE		AL_BIT(4)
#define AL_ETH_EC_IOFIC_GROUP_B_ERR_TFW_OUT_S			AL_BIT(5)
#define AL_ETH_EC_IOFIC_GROUP_B_ERR_TPM_NO_SOP			AL_BIT(6)
#define AL_ETH_EC_IOFIC_GROUP_B_ERR_TPM_SPOOF_0			AL_BIT(7)
#define AL_ETH_EC_IOFIC_GROUP_B_ERR_TPM_SPOOF_1			AL_BIT(8)
#define AL_ETH_EC_IOFIC_GROUP_B_ERR_TPM_SPOOF_2			AL_BIT(9)
#define AL_ETH_EC_IOFIC_GROUP_B_ERR_TPM_SPOOF_3			AL_BIT(10)
#define AL_ETH_EC_IOFIC_GROUP_B_ERR_TPE_OUT_EOP_HDR_EMPTY	AL_BIT(12)
#define AL_ETH_EC_IOFIC_GROUP_B_ERR_TPE_IN_SOP_IN_PKT		AL_BIT(13)
#define AL_ETH_EC_IOFIC_GROUP_B_ERR_TPE_IN_EOP_IN_IDLE		AL_BIT(14)
#define AL_ETH_EC_IOFIC_GROUP_B_ERR_TSO_CNT_END_OF_SEQ		AL_BIT(15)
#define AL_ETH_EC_IOFIC_GROUP_B_ERR_TSO_LAST_IN_SHDR		AL_BIT(16)
#define AL_ETH_EC_IOFIC_GROUP_B_ERR_TSO_CNT_END_OF_PKT_4	AL_BIT(17)
#define AL_ETH_EC_IOFIC_GROUP_B_ERR_TSO_CNT_END_OF_PKT_3	AL_BIT(18)
#define AL_ETH_EC_IOFIC_GROUP_B_ERR_TSO_CNT_END_OF_PKT_2	AL_BIT(19)
#define AL_ETH_EC_IOFIC_GROUP_B_ERR_TSO_CNT_END_OF_PKT_1	AL_BIT(20)
#define AL_ETH_EC_IOFIC_GROUP_B_ERR_TSO_NO_SOP			AL_BIT(21)
#define AL_ETH_EC_IOFIC_GROUP_B_ERR_RX_SAD_3_PARITY		AL_BIT(22)
#define AL_ETH_EC_IOFIC_GROUP_B_ERR_RX_SAD_2_PARITY		AL_BIT(23)
#define AL_ETH_EC_IOFIC_GROUP_B_ERR_RX_SAD_1_PARITY		AL_BIT(24)
#define AL_ETH_EC_IOFIC_GROUP_B_ERR_RX_SAD_0_PARITY		AL_BIT(25)
#define AL_ETH_EC_IOFIC_GROUP_B_ERR_TX_SAD_3_PARITY		AL_BIT(26)
#define AL_ETH_EC_IOFIC_GROUP_B_ERR_TX_SAD_2_PARITY		AL_BIT(27)
#define AL_ETH_EC_IOFIC_GROUP_B_ERR_TX_SAD_1_PARITY		AL_BIT(28)
#define AL_ETH_EC_IOFIC_GROUP_B_ERR_TX_SAD_0_PARITY		AL_BIT(29)
#define AL_ETH_V3_EC_IOFIC_GROUP_B_ERR_HS_CTRL_TABLE_3_PARITY	AL_BIT(22)
#define AL_ETH_V3_EC_IOFIC_GROUP_B_ERR_HS_CTRL_TABLE_2_PARITY	AL_BIT(23)
#define AL_ETH_V3_EC_IOFIC_GROUP_B_ERR_HS_CTRL_TABLE_1_PARITY	AL_BIT(24)
#define AL_ETH_V3_EC_IOFIC_GROUP_B_ERR_HS_CTRL_TABLE_0_PARITY	AL_BIT(25)
#define AL_ETH_V3_EC_IOFIC_GROUP_B_RDMA_INT			AL_BIT(29)
/** ETH v4 */
#define AL_ETH_V4_EC_IOFIC_GROUP_B_EC_ERR_TMI_IN_SOP_IN_PKT		AL_BIT(0)
#define AL_ETH_V4_EC_IOFIC_GROUP_B_EC_ERR_TMI_IN_EOP_IN_IDLE		AL_BIT(1)
#define AL_ETH_V4_EC_IOFIC_GROUP_B_EC_ERR_TFW_OUT_EOP_HDR_EMPTY		AL_BIT(2)
#define AL_ETH_V4_EC_IOFIC_GROUP_B_EC_ERR_TFW_IN_SOP_IN_PKT		AL_BIT(3)
#define AL_ETH_V4_EC_IOFIC_GROUP_B_EC_ERR_TFW_IN_EOP_IN_IDLE		AL_BIT(4)
#define AL_ETH_V4_EC_IOFIC_GROUP_B_TFW_OUT_S_ERR			AL_BIT(5)
#define AL_ETH_V4_EC_IOFIC_GROUP_B_EC_ERR_TPM_NO_SOP_ERR		AL_BIT(6)
#define AL_ETH_V4_EC_IOFIC_GROUP_B_EC_ERR_TPM_SPOOF_ERR_0		AL_BIT(7)
#define AL_ETH_V4_EC_IOFIC_GROUP_B_EC_ERR_TPM_SPOOF_ERR_1		AL_BIT(8)
#define AL_ETH_V4_EC_IOFIC_GROUP_B_EC_ERR_TPM_SPOOF_ERR_2		AL_BIT(9)
#define AL_ETH_V4_EC_IOFIC_GROUP_B_EC_ERR_TPM_SPOOF_ERR_3		AL_BIT(10)
/*#define AL_ETH_V4_EC_IOFIC_GROUP_B_EC_ERR_TPM_NO_SOP_ERR		AL_BIT(11) TODO duplicate */
#define AL_ETH_V4_EC_IOFIC_GROUP_B_EC_ERR_TPE_OUT_EOP_HDR_EMPTY		AL_BIT(12)
#define AL_ETH_V4_EC_IOFIC_GROUP_B_EC_ERR_TPE_IN_SOP_IN_PKT		AL_BIT(13)
#define AL_ETH_V4_EC_IOFIC_GROUP_B_EC_ERR_TPE_IN_EOP_IN_IDLE		AL_BIT(14)
#define AL_ETH_V4_EC_IOFIC_GROUP_B_EC_ERR_TSO_CNT_END_OF_SEG		AL_BIT(15)
#define AL_ETH_V4_EC_IOFIC_GROUP_B_EC_ERR_TSO_LAST_IN_SHDR		AL_BIT(16)
#define AL_ETH_V4_EC_IOFIC_GROUP_B_EC_ERR_TSO_CNT_END_OF_PKT_4		AL_BIT(17)
#define AL_ETH_V4_EC_IOFIC_GROUP_B_EC_ERR_TSO_CNT_END_OF_PKT_3		AL_BIT(18)
#define AL_ETH_V4_EC_IOFIC_GROUP_B_EC_ERR_TSO_CNT_END_OF_PKT_2		AL_BIT(19)
#define AL_ETH_V4_EC_IOFIC_GROUP_B_EC_ERR_TSO_CNT_END_OF_PKT_1		AL_BIT(20)
#define AL_ETH_V4_EC_IOFIC_GROUP_B_EC_ERR_TSO_NO_SOP_ERR		AL_BIT(21)
#define AL_ETH_V4_EC_IOFIC_GROUP_B_EC_HS_CTRL_TABLE_PAR_ERR_3		AL_BIT(22)
#define AL_ETH_V4_EC_IOFIC_GROUP_B_EC_HS_CTRL_TABLE_PAR_ERR_2		AL_BIT(23)
#define AL_ETH_V4_EC_IOFIC_GROUP_B_EC_HS_CTRL_TABLE_PAR_ERR_1		AL_BIT(24)
#define AL_ETH_V4_EC_IOFIC_GROUP_B_EC_HS_CTRL_TABLE_PAR_ERR_0		AL_BIT(25)
#define AL_ETH_V4_EC_IOFIC_GROUP_B_EC_RFW_IN_PIPE_DATA_FIFO_PAR_ERR_0	AL_BIT(26)
#define AL_ETH_V4_EC_IOFIC_GROUP_B_EC_RFW_IN_PIPE_DATA_FIFO_PAR_ERR_1	AL_BIT(27)
#define AL_ETH_V4_EC_IOFIC_GROUP_B_EC_ERR_TFW_OUT_SOP_INFO_EMPTY	AL_BIT(28)

/* ETH_EC IOFIC group C */
#define AL_ETH_EC_IOFIC_GROUP_C_TFW_EOP_FIFO_1_PARITY		AL_BIT(2)
#define AL_ETH_EC_IOFIC_GROUP_C_TFW_SOP_FIFO_1_PARITY		AL_BIT(3)
#define AL_ETH_EC_IOFIC_GROUP_C_RXF_EOP_FIFO_2_PARITY		AL_BIT(4)
#define AL_ETH_EC_IOFIC_GROUP_C_RXF_SOP_FIFO_2_PARITY		AL_BIT(5)
#define AL_ETH_EC_IOFIC_GROUP_C_RXF_EOP_FIFO_1_PARITY		AL_BIT(6)
#define AL_ETH_EC_IOFIC_GROUP_C_RXF_SOP_FIFO_1_PARITY		AL_BIT(7)
#define AL_ETH_EC_IOFIC_GROUP_C_TFW_VLAN_TABLE_1_PARITY		AL_BIT(8)
#define AL_ETH_EC_IOFIC_GROUP_C_RFW_CTRL_TABLE_1_PARITY		AL_BIT(9)
#define AL_ETH_EC_IOFIC_GROUP_C_RFW_VLAN_TABLE_1_PARITY		AL_BIT(10)
#define AL_ETH_EC_IOFIC_GROUP_C_RFW_FLOW_TABLE_1_PARITY		AL_BIT(11)
#define AL_ETH_EC_IOFIC_GROUP_C_RFW_THASH_TABLE_1_PARITY	AL_BIT(12)
#define AL_ETH_EC_IOFIC_GROUP_C_RFW_MHASH_TABLE_1_PARITY	AL_BIT(13)
#define AL_ETH_EC_IOFIC_GROUP_C_RFW_LRO_TABLE_2_2_PARITY	AL_BIT(14)
#define AL_ETH_EC_IOFIC_GROUP_C_RFW_LRO_TABLE_2_1_PARITY	AL_BIT(15)
#define AL_ETH_EC_IOFIC_GROUP_C_RFW_LRO_TABLE_2_0_PARITY	AL_BIT(16)
#define AL_ETH_EC_IOFIC_GROUP_C_RFW_LRO_TABLE_1_2_PARITY	AL_BIT(17)
#define AL_ETH_EC_IOFIC_GROUP_C_RFW_LRO_TABLE_1_1_PARITY	AL_BIT(18)
#define AL_ETH_EC_IOFIC_GROUP_C_RFW_LRO_TABLE_1_0_PARITY	AL_BIT(19)
#define AL_ETH_EC_IOFIC_GROUP_C_TFW_DATA_FIFO_2_PARITY		AL_BIT(20)
#define AL_ETH_EC_IOFIC_GROUP_C_TFW_DATA_FIFO_1_PARITY		AL_BIT(21)
#define AL_ETH_EC_IOFIC_GROUP_C_RXF_DATA_FIFO_2_2_PARITY	AL_BIT(22)
#define AL_ETH_EC_IOFIC_GROUP_C_RXF_DATA_FIFO_2_1_PARITY	AL_BIT(23)
#define AL_ETH_EC_IOFIC_GROUP_C_RXF_DATA_FIFO_1_2_PARITY	AL_BIT(24)
#define AL_ETH_EC_IOFIC_GROUP_C_RXF_DATA_FIFO_1_1_PARITY	AL_BIT(25)
#define AL_ETH_EC_IOFIC_GROUP_C_TSO_META_CACHE_1_4_PARITY	AL_BIT(26)
#define AL_ETH_EC_IOFIC_GROUP_C_TSO_META_CACHE_1_3_PARITY	AL_BIT(27)
#define AL_ETH_EC_IOFIC_GROUP_C_TSO_META_CACHE_1_2_PARITY	AL_BIT(28)
#define AL_ETH_EC_IOFIC_GROUP_C_TSO_META_CACHE_1_1_PARITY	AL_BIT(29)
#define AL_ETH_V3_EC_IOFIC_GROUP_C_TFW_GCP_TABLE_2_PARITY	AL_BIT(14)
#define AL_ETH_V3_EC_IOFIC_GROUP_C_TFW_GCP_TABLE_1_PARITY	AL_BIT(15)
#define AL_ETH_V3_EC_IOFIC_GROUP_C_TFW_GCP_TABLE_0_PARITY	AL_BIT(16)
#define AL_ETH_V3_EC_IOFIC_GROUP_C_RFW_GCP_TABLE_2_PARITY	AL_BIT(17)
#define AL_ETH_V3_EC_IOFIC_GROUP_C_RFW_GCP_TABLE_1_PARITY	AL_BIT(18)
#define AL_ETH_V3_EC_IOFIC_GROUP_C_RFW_GCP_TABLE_0_PARITY	AL_BIT(19)

/** ETH v4 */
#define AL_ETH_V4_EC_IOFIC_GROUP_C_EC_SEC_INT_OUTPUT_0			AL_BIT(0)
#define AL_ETH_V4_EC_IOFIC_GROUP_C_EC_SEC_INT_OUTPUT_1			AL_BIT(1)
#define AL_ETH_V4_EC_IOFIC_GROUP_C_EC_TFW_EOP_FIFO_1_PAR_ERR		AL_BIT(2)
#define AL_ETH_V4_EC_IOFIC_GROUP_C_EC_TFW_SOP_FIFO_1_PAR_ERR		AL_BIT(3)
#define AL_ETH_V4_EC_IOFIC_GROUP_C_EC_TFW_GCP_TABLE_LO_PAR_ERR_3	AL_BIT(4)
#define AL_ETH_V4_EC_IOFIC_GROUP_C_EC_RFW_GCP_TABLE_LO_PAR_ERR_3	AL_BIT(5)
#define AL_ETH_V4_EC_IOFIC_GROUP_C_EC_SEC_INT_OUTPUT_2			AL_BIT(6)
#define AL_ETH_V4_EC_IOFIC_GROUP_C_EC_SEC_INT_OUTPUT_3			AL_BIT(7)
#define AL_ETH_V4_EC_IOFIC_GROUP_C_EC_TFW_VLAN_TABLE_1_PAR_ERR		AL_BIT(8)
#define AL_ETH_V4_EC_IOFIC_GROUP_C_EC_RFW_CTRL_TABLE_1_PAR_ERR		AL_BIT(9)
#define AL_ETH_V4_EC_IOFIC_GROUP_C_EC_RFW_VLAN_TABLE_1_PAR_ERR		AL_BIT(10)
#define AL_ETH_V4_EC_IOFIC_GROUP_C_EC_RFW_FLOW_TABLE_1_PAR_ERR		AL_BIT(11)
#define AL_ETH_V4_EC_IOFIC_GROUP_C_EC_RFW_THASH_TABLE_1_PAR_ERR		AL_BIT(12)
#define AL_ETH_V4_EC_IOFIC_GROUP_C_EC_RFW_MHASH_TABLE_1_PAR_ERR		AL_BIT(13)
#define AL_ETH_V4_EC_IOFIC_GROUP_C_EC_TFW_GCP_TABLE_LO_PAR_ERR_2	AL_BIT(14)
#define AL_ETH_V4_EC_IOFIC_GROUP_C_EC_TFW_GCP_TABLE_LO_PAR_ERR_1	AL_BIT(15)
#define AL_ETH_V4_EC_IOFIC_GROUP_C_EC_TFW_GCP_TABLE_LO_PAR_ERR_0	AL_BIT(16)
#define AL_ETH_V4_EC_IOFIC_GROUP_C_EC_RFW_GCP_TABLE_LO_PAR_ERR_2	AL_BIT(17)
#define AL_ETH_V4_EC_IOFIC_GROUP_C_EC_RFW_GCP_TABLE_LO_PAR_ERR_1	AL_BIT(18)
#define AL_ETH_V4_EC_IOFIC_GROUP_C_EC_RFW_GCP_TABLE_LO_PAR_ERR_0	AL_BIT(19)
#define AL_ETH_V4_EC_IOFIC_GROUP_C_EC_TFW_DATA_FIFO_2_PAR_ERR_0		AL_BIT(20)
#define AL_ETH_V4_EC_IOFIC_GROUP_C_EC_TFW_DATA_FIFO_1_PAR_ERR_0		AL_BIT(21)
#define AL_ETH_V4_EC_IOFIC_GROUP_C_EC_TFW_DATA_FIFO_2_PAR_ERR_1		AL_BIT(22)
#define AL_ETH_V4_EC_IOFIC_GROUP_C_EC_TFW_DATA_FIFO_1_PAR_ERR_1		AL_BIT(23)
#define AL_ETH_V4_EC_IOFIC_GROUP_C_EC_TSO_META_CACHE_1_4_PAR_ERR	AL_BIT(27)
#define AL_ETH_V4_EC_IOFIC_GROUP_C_EC_TSO_META_CACHE_1_3_PAR_ERR	AL_BIT(28)
#define AL_ETH_V4_EC_IOFIC_GROUP_C_EC_TSO_META_CACHE_1_2_PAR_ERR	AL_BIT(29)
#define AL_ETH_V4_EC_IOFIC_GROUP_C_EC_TSO_META_CACHE_1_1_PAR_ERR	AL_BIT(30)

/* ETH_EC IOFIC group D */
#define AL_ETH_EC_IOFIC_GROUP_D_ERR_TIMESTAMP_FIFO_OVERRUN	AL_BIT(0)
#define AL_ETH_EC_IOFIC_GROUP_D_ERR_ROCE_WR_INT			AL_BIT(28)
#define AL_ETH_EC_IOFIC_GROUP_D_ERR_ROCE_RR_INT			AL_BIT(30)
/* V4 */
#define AL_ETH_V4_EC_IOFIC_GROUP_D_ERR_TIMESTAMP_FIFO_OVERRUN	AL_BIT(0)

/** ETH v4 Secondary IOFIC */
/* Group A */
#define AL_ETH_V4_EC_SEC_IOFIC_GROUP_A_EC_TFW_GCP_TABLE_HI_PAR_ERR_0			AL_BIT(0)
#define AL_ETH_V4_EC_SEC_IOFIC_GROUP_A_EC_TFW_GCP_TABLE_HI_PAR_ERR_1			AL_BIT(1)
#define AL_ETH_V4_EC_SEC_IOFIC_GROUP_A_EC_TFW_GCP_TABLE_HI_PAR_ERR_2			AL_BIT(2)
#define AL_ETH_V4_EC_SEC_IOFIC_GROUP_A_EC_TFW_GCP_TABLE_HI_PAR_ERR_3			AL_BIT(3)
#define AL_ETH_V4_EC_SEC_IOFIC_GROUP_A_EC_TFW_GCP_TABLE_HI_PAR_ERR_4			AL_BIT(4)
#define AL_ETH_V4_EC_SEC_IOFIC_GROUP_A_EC_TFW_GCP_TABLE_HI_PAR_ERR_5			AL_BIT(5)
#define AL_ETH_V4_EC_SEC_IOFIC_GROUP_A_EC_TFW_GCP_TABLE_HI_PAR_ERR_6			AL_BIT(6)
#define AL_ETH_V4_EC_SEC_IOFIC_GROUP_A_EC_TFW_GCP_TABLE_HI_PAR_ERR_7			AL_BIT(7)
#define AL_ETH_V4_EC_SEC_IOFIC_GROUP_A_EC_RFW_GCP_TABLE_HI_PAR_ERR_0			AL_BIT(8)
#define AL_ETH_V4_EC_SEC_IOFIC_GROUP_A_EC_RFW_GCP_TABLE_HI_PAR_ERR_1			AL_BIT(9)
#define AL_ETH_V4_EC_SEC_IOFIC_GROUP_A_EC_RFW_GCP_TABLE_HI_PAR_ERR_2			AL_BIT(10)
#define AL_ETH_V4_EC_SEC_IOFIC_GROUP_A_EC_RFW_GCP_TABLE_HI_PAR_ERR_3			AL_BIT(11)
#define AL_ETH_V4_EC_SEC_IOFIC_GROUP_A_EC_RFW_GCP_TABLE_HI_PAR_ERR_4			AL_BIT(12)
#define AL_ETH_V4_EC_SEC_IOFIC_GROUP_A_EC_RFW_GCP_TABLE_HI_PAR_ERR_5			AL_BIT(13)
#define AL_ETH_V4_EC_SEC_IOFIC_GROUP_A_EC_RFW_GCP_TABLE_HI_PAR_ERR_6			AL_BIT(14)
#define AL_ETH_V4_EC_SEC_IOFIC_GROUP_A_EC_RFW_GCP_TABLE_HI_PAR_ERR_7			AL_BIT(15)
#define AL_ETH_V4_EC_SEC_IOFIC_GROUP_A_EC_RFF_DATA_FIFO_LO_MEM_PAR_ERR			AL_BIT(18)
#define AL_ETH_V4_EC_SEC_IOFIC_GROUP_A_EC_RFF_DATA_FIFO_HI_MEM_PAR_ERR			AL_BIT(19)
#define AL_ETH_V4_EC_SEC_IOFIC_GROUP_A_EC_RFF_RFW_SR_RESULT_FIFO_MEM_PAR_ERR_0		AL_BIT(20)
#define AL_ETH_V4_EC_SEC_IOFIC_GROUP_A_EC_RFF_RFW_SR_RESULT_FIFO_MEM_PAR_ERR_1		AL_BIT(21)
#define AL_ETH_V4_EC_SEC_IOFIC_GROUP_A_EC_RFF_RFW_SR_RESULT_FIFO_MEM_PAR_ERR_2		AL_BIT(22)
#define AL_ETH_V4_EC_SEC_IOFIC_GROUP_A_EC_RFF_RFW_SR_RESULT_FIFO_MEM_PAR_ERR_3		AL_BIT(23)
#define AL_ETH_V4_EC_SEC_IOFIC_GROUP_A_EC_RFF_PARSE_RES_FIFO_MEM_PAR_ERR_0		AL_BIT(24)
#define AL_ETH_V4_EC_SEC_IOFIC_GROUP_A_EC_RFF_PARSE_RES_FIFO_MEM_PAR_ERR_1		AL_BIT(25)
#define AL_ETH_V4_EC_SEC_IOFIC_GROUP_A_EC_RFF_PARSE_RES_FIFO_MEM_PAR_ERR_2		AL_BIT(26)
#define AL_ETH_V4_EC_SEC_IOFIC_GROUP_A_EC_RFF_PARSE_RES_FIFO_MEM_PAR_ERR_3		AL_BIT(27)
#define AL_ETH_V4_EC_SEC_IOFIC_GROUP_A_EC_RFF_PARSE_RES_FIFO_MEM_PAR_ERR_4		AL_BIT(28)
#define AL_ETH_V4_EC_SEC_IOFIC_GROUP_A_EC_RFF_PARSE_RES_FIFO_MEM_PAR_ERR_5		AL_BIT(29)
#define AL_ETH_V4_EC_SEC_IOFIC_GROUP_A_EC_RFF_PARSE_RES_FIFO_MEM_PAR_ERR_6		AL_BIT(30)

struct al_mod_eth_capabilities {
	al_mod_bool	speed_10_HD;
	al_mod_bool	speed_10_FD;
	al_mod_bool speed_100_HD;
	al_mod_bool speed_100_FD;
	al_mod_bool speed_1000_HD;
	al_mod_bool speed_1000_FD;
	al_mod_bool speed_10000_HD;
	al_mod_bool speed_10000_FD;
	al_mod_bool pfc; /**< priority flow control */
	al_mod_bool eee; /**< Energy Efficient Ethernet */
};

/** flow control mode */
enum al_mod_eth_flow_control_type {
	AL_ETH_FLOW_CONTROL_TYPE_LINK_PAUSE,
	AL_ETH_FLOW_CONTROL_TYPE_PFC,
	AL_ETH_FLOW_CONTROL_TYPE_MAX,
};

/** Tx to Rx switching decision type */
enum al_mod_eth_tx_switch_dec_type {
	AL_ETH_TX_SWITCH_TYPE_MAC = 0,
	AL_ETH_TX_SWITCH_TYPE_VLAN_TABLE = 1,
	AL_ETH_TX_SWITCH_TYPE_VLAN_TABLE_AND_MAC = 2,
	AL_ETH_TX_SWITCH_TYPE_BITMAP = 3
};

/** Tx to Rx VLAN ID selection type */
enum al_mod_eth_tx_switch_vid_sel_type {
	AL_ETH_TX_SWITCH_VID_SEL_TYPE_VLAN1 = 0,
	AL_ETH_TX_SWITCH_VID_SEL_TYPE_VLAN2 = 1,
	AL_ETH_TX_SWITCH_VID_SEL_TYPE_NEW_VLAN1 = 2,
	AL_ETH_TX_SWITCH_VID_SEL_TYPE_NEW_VLAN2 = 3,
	AL_ETH_TX_SWITCH_VID_SEL_TYPE_DEFAULT_VLAN1 = 4,
	AL_ETH_TX_SWITCH_VID_SEL_TYPE_FINAL_VLAN1 = 5
};

/** Rx descriptor configurations */
/* Note: when selecting rx descriptor field to inner packet, then that field
* will be set according to inner packet when packet is tunneled, for non-tunneled
* packets, the field will be set according to the packets header */

/** selection of the LRO_context_value result in the Metadata */
enum al_mod_eth_rx_desc_lro_context_val_res {
	AL_ETH_LRO_CONTEXT_VALUE = 0, /**< LRO_context_value */
	AL_ETH_L4_OFFSET = 1, /**< L4_offset */
};

/** selection of the L4 offset in the Metadata */
enum al_mod_eth_rx_desc_l4_offset_sel {
	AL_ETH_L4_OFFSET_OUTER = 0, /**< set L4 offset of the outer packet */
	AL_ETH_L4_OFFSET_INNER = 1, /**< set L4 offset of the inner packet */
};

/** which L3/L4 default checksum */
enum al_mod_eth_rx_desc_l3_l4_default_chk {
	AL_ETH_L3_L4_HEADER_OUTER = 0, /**< use outer headers */
	AL_ETH_L3_L4_HEADER_INNER = 1, /**< use inner headers when exists*/
};

/** selection of the L4 checksum result in the Metadata */
enum al_mod_eth_rx_desc_l4_chk_res_sel {
	AL_ETH_L4_DEFAULT_CHK = 0, /**< L4 default checksum */
	AL_ETH_L4_INNER_OUTER_CHK = 1, /**< Logic AND between outer and inner
					    L4 checksum result */
};

/** selection of the L3 checksum result in the Metadata */
enum al_mod_eth_rx_desc_l3_chk_res_sel {
	AL_ETH_L3_CHK_TYPE_0 = 0, /**< L3 default checksum */
	AL_ETH_L3_CHK_TYPE_1 = 1, /**< L3 checksum or RoCE/FCoE CRC,
				       based on outer header */
	AL_ETH_L3_CHK_TYPE_2 = 2, /**< If tunnel exist = 0,
					  L3 checksum or RoCE/FCoE CRC,
					  based on outer header.
				       Else,
					  logic AND between outer L3 checksum
					  (Ipv4) and inner CRC (RoCE or FcoE) */
	AL_ETH_L3_CHK_TYPE_3 = 3, /**< combination of the L3 checksum result and
				       CRC result,based on the checksum and
				       RoCE/FCoE CRC input selections. */
};

/** selection of the L3 protocol index in the Metadata */
enum al_mod_eth_rx_desc_l3_proto_idx_sel {
	AL_ETH_L3_PROTO_IDX_OUTER = 0, /**< set L3 proto index of the outer packet */
	AL_ETH_L3_PROTO_IDX_INNER = 1, /**< set L3 proto index of the inner packet */
};

/** selection of the L3 offset in the Metadata */
enum al_mod_eth_rx_desc_l3_offset_sel {
	AL_ETH_L3_OFFSET_OUTER = 0, /**< set L3 offset of the outer packet */
	AL_ETH_L3_OFFSET_INNER = 1, /**< set L3 offset of the inner packet */
};


/** selection of the L4 protocol index in the Metadata */
enum al_mod_eth_rx_desc_l4_proto_idx_sel {
	AL_ETH_L4_PROTO_IDX_OUTER = 0, /**< set L4 proto index of the outer packet */
	AL_ETH_L4_PROTO_IDX_INNER = 1, /**< set L4 proto index of the inner packet */
};

/** selection of the frag indication in the Metadata */
enum al_mod_eth_rx_desc_frag_sel {
	AL_ETH_FRAG_OUTER = 0, /**< set frag of the outer packet */
	AL_ETH_FRAG_INNER = 1, /**< set frag of the inner packet */
};

/** Ethernet Rx completion descriptor */
typedef struct {
	uint32_t ctrl_meta;
	uint32_t len;
	uint32_t word2;
	uint32_t word3;
	uint32_t word4;
	uint32_t word5;
	uint32_t word6;
	uint32_t word7;
} al_mod_eth_rx_cdesc;

/** Flow Contol parameters */
struct al_mod_eth_flow_control_params{
	enum al_mod_eth_flow_control_type type; /**< flow control type */
	al_mod_bool		obay_enable; /**< stop tx when pause received */
	al_mod_bool		gen_enable; /**< generate pause frames */
	uint16_t	rx_fifo_th_high;
	uint16_t	rx_fifo_th_low;
	uint16_t	quanta;
	uint16_t	quanta_th;
	uint16_t	prio_q_map[4][8]; /**< for each UDMA, defines the mapping between
					   * PFC priority and queues(in bit mask).
					   * same mapping used for obay and generation.
					   * for example:
					   * if prio_q_map[1][7] = 0xC, then TX queues 2
					   * and 3 of UDMA 1 will be stopped when pause
					   * received with priority 7, also, when RX queues
					   * 2 and 3 of UDMA 1 become almost full, then
					   * pause frame with priority 7 will be sent.
					   *
					   *note:
					   * 1) if specific a queue is not used, the caller must
					   * make set the prio_q_map to 0 otherwise that queue
					   * will make the controller keep sending PAUSE packets.
					   * 2) queues of unused UDMA must be treated as above.
					   * 3) when working in LINK PAUSE mode, only entries at
					   * priority 0 will be considered.
					   */

	al_mod_bool skip_flow_ctrl_efc;	/** To MAC verification purposes only */
};

/* Packet Tx flags */
#define AL_ETH_TX_FLAGS_IPV4_L3_CSUM	AL_BIT(13) /**< Enable IPv4 header checksum calculation */
#define AL_ETH_TX_FLAGS_L4_CSUM		AL_BIT(14) /**< Enable TCP/UDP checksum calculation */
#define AL_ETH_TX_FLAGS_L4_PARTIAL_CSUM	AL_BIT(17) /**< L4 partial checksum calculation */
#define AL_ETH_TX_FLAGS_L2_MACSEC_PKT	AL_BIT(16) /**< L2 Packet type 802_3 or 802_3_MACSEC, V2 */
#define AL_ETH_TX_FLAGS_ENCRYPT		AL_BIT(16) /**< Enable TX packet encryption, V3 */
#define AL_ETH_TX_FLAGS_PACKET_DROP	AL_BIT(16) /** Force packet drop
							(For outstanding configuration packets) */
#define AL_ETH_TX_FLAGS_L2_DIS_FCS	AL_BIT(15) /**< Disable CRC calculation*/
#define AL_ETH_TX_FLAGS_TS		AL_BIT(21) /**< Timestamp the packet */

#define AL_ETH_TX_FLAGS_INT		AL_M2S_DESC_INT_EN
#define AL_ETH_TX_FLAGS_NO_SNOOP	AL_M2S_DESC_NO_SNOOP_H

/** this structure used for tx packet meta data */
struct al_mod_eth_meta_data{
	uint8_t store :1; /**< store the meta into the queues cache */
	uint8_t words_valid :4; /**< valid bit per word */

	uint8_t l3_header_len; /**< in bytes */
	uint8_t l3_header_offset;
	uint8_t l4_header_len; /**< in words(32-bits) */

	/* rev 0, 1, 2, 3 specific */
	uint8_t vlan1_cfi_sel:2;
	uint8_t vlan2_vid_sel:2;
	uint8_t vlan2_cfi_sel:2;
	uint8_t vlan2_pbits_sel:2;
	uint8_t vlan2_ether_sel:2;

	uint16_t vlan1_new_vid:12;
	uint8_t vlan1_new_cfi :1;
	uint8_t vlan1_new_pbits :3;
	uint16_t vlan2_new_vid:12;
	uint8_t vlan2_new_cfi :1;
	uint8_t vlan2_new_pbits :3;

	/* rev 0 specific */
	uint8_t mss_idx_sel:3; /**< for TSO, select the register that holds the MSS */

	/* rev 1 specific */
	uint8_t	ts_index:4; /**< index of regiser where to store the tx timestamp */
	uint16_t mss_val:14; /**< for TSO, set a valid mss value. Otherwise set to 0 */
	uint8_t outer_l3_offset; /**< for tunneling mode. up to 64 bytes */
	uint8_t outer_l3_len; /**< for tunneling mode. up to 128 bytes */
};

/* Packet Rx flags when adding buffer to receive queue */

/**<
 * Target-ID to be assigned to the packet descriptors
 * Requires Target-ID in descriptor to be enabled for the specific UDMA
 * queue.
 */
#define AL_ETH_RX_FLAGS_TGTID_MASK	AL_FIELD_MASK(15, 0)
#define AL_ETH_RX_FLAGS_NO_SNOOP	AL_M2S_DESC_NO_SNOOP_H
#define AL_ETH_RX_FLAGS_INT		AL_M2S_DESC_INT_EN
#define AL_ETH_RX_FLAGS_DUAL_BUF	AL_BIT(31)

/* Packet Rx flags set by HW when receiving packet */
#define AL_ETH_RX_ERROR			AL_BIT(16) /**< layer 2 errors (FCS, bad len, etc) */
#define AL_ETH_RX_IPV4_FRAG		AL_BIT(15)
#define AL_ETH_RX_FLAGS_L4_CSUM_ERR	AL_BIT(14)
#define AL_ETH_RX_FLAGS_L3_CSUM_ERR	AL_BIT(13)

/* Packet Rx flags - word 0 in Rx completion descriptor */
#define AL_ETH_RX_FLAGS_V4_ICRC			AL_BIT(23)

/* Packet Rx flags - word 3 in Rx completion descriptor */
#define AL_ETH_RX_FLAGS_CRC						AL_BIT(31)
#define AL_ETH_RX_FLAGS_L3_CSUM_2				AL_BIT(30)
#define AL_ETH_RX_FLAGS_L4_CSUM_2				AL_BIT(29)
#define AL_ETH_RX_FLAGS_SW_SRC_PORT_SHIFT		13
#define AL_ETH_RX_FLAGS_SW_SRC_PORT_MASK		AL_FIELD_MASK(15, 13)
#define AL_ETH_RX_FLAGS_LRO_CONTEXT_VAL_SHIFT	3
#define AL_ETH_RX_FLAGS_LRO_CONTEXT_VAL_MASK	AL_FIELD_MASK(10, 3)
#define AL_ETH_RX_FLAGS_L4_OFFSET_SHIFT			3
#define AL_ETH_RX_FLAGS_L4_OFFSET_MASK			AL_FIELD_MASK(10, 3)
#define AL_ETH_RX_FLAGS_PRIORITY_SHIFT			0
#define AL_ETH_RX_FLAGS_PRIORITY_MASK			AL_FIELD_MASK(2, 0)

/** packet structure. used for packet transmission and reception */
struct al_mod_eth_pkt{
	uint32_t flags; /**< see flags above, depends on context(tx or rx) */
	uint32_t flags_ex; /* see flags above (word 3 in Rx completion descriptor) */
	/* l3 & l4 protocols index are not present in the ETHv4 default RX desc configuration */
	enum AL_ETH_PROTO_ID l3_proto_idx;
	enum AL_ETH_PROTO_ID l4_proto_idx;
	uint8_t source_vlan_count:2;

	/* rev 0, 1, 2, 3 specific */
	uint8_t vlan_mod_add_count:2;
	uint8_t vlan_mod_del_count:2;
	uint8_t vlan_mod_v1_ether_sel:2;
	uint8_t vlan_mod_v1_vid_sel:2;
	uint8_t vlan_mod_v1_pbits_sel:2;

	/* rev 1 specific */
	enum AL_ETH_TX_TUNNEL_MODE tunnel_mode;
	enum AL_ETH_PROTO_ID outer_l3_proto_idx; /**< for tunneling mode */

	/**
	 * Indicating packet type
	 * rev 3 - relevant only when CRC/Checkeum engine is enabled
	 *  through 'gen_crc_checksum_en_mask'
	 */
	unsigned int protocol_number;

	/**
	 * Enable CRC/Checksum calculation and replacement (one per engine)
	 * The CRC/Checksum parameters are determined based on the protocol_number defined below
	 * The Enable bit determined if the calculated CRC/Checksum result is used to replace
	 * existing packet fields
	 * The engine only replaces exisiting packet fields and doesn't add byte count
	 */
	unsigned int gen_crc_checksum_en_mask;

	/**<
	 * Target-ID to be assigned to the packet descriptors
	 * Requires Target-ID in descriptor to be enabled for the specific UDMA
	 * queue.
	 */
	uint16_t tgtid;

	uint32_t rx_header_len; /**< header buffer length of rx packet, not used */
	struct al_mod_eth_meta_data *meta; /**< if null, then no meta added */
#ifdef AL_ETH_RX_DESC_RAW_GET
	uint32_t rx_desc_raw[8];
#endif
	/**
	 * rev 4 - 32 bit. rev 0, 1, 2, 3 - 16 bit
	 *
	 * If packet is IPv4 fragmented:
	 *  Intermediate L4 Checksum value for fragmented IP is passed instead of 16bit hash
	 *  In that case, the L4 csum error (bit 14) should be ignored.
	 */
	uint32_t rxhash;

	uint16_t l3_offset;

#ifdef AL_ETH_EX_HAS_EXT_METADATA
	struct al_mod_eth_tx_metadata_proprietary *tx_meta_proprietary;
#endif

#ifdef AL_ETH_EX_HAS_EXT_METADATA
	struct al_mod_eth_ext_metadata *ext_meta_data;
#endif

	uint8_t num_of_bufs;
	struct al_mod_buf	bufs[AL_ETH_PKT_MAX_BUFS];
};

struct al_mod_ec_regs;

#define AL_ETH_HAS_ADAPTER_HANDLE
/** Adapter handle init params */
struct al_mod_eth_adapter_handle_init_params {
	uint8_t rev_id; /**<PCI adapter revision ID */
	uint8_t dev_id; /**<PCI adapter device ID */
	uint8_t udma_id; /**< the id of the UDMA used by this adapter */
	enum al_mod_eth_common_mode common_mode; /**< Ethernet common mode */
	al_mod_bool internal_switching; /**< Loopback mode */
	void __iomem *udma_regs_base;
	struct al_mod_ec_regs __iomem *ec_regs_base;
	struct al_mod_eth_mac_regs __iomem *mac_regs_base;
	char *name; /**< the upper layer must keep the string area */
	uint8_t serdes_lane;
	/** MAC common registers base address */
	void __iomem *mac_common_regs;
	/** MAC common registers lock/unlock callback */
	int (*mac_common_regs_lock)(void *handle, al_mod_bool lock);
	/** MAC v4 common registers lock/unlock handle */
	void __iomem *mac_common_regs_lock_handle;
	/** DME (Differential manchester encoding) downsample */
	struct al_mod_hal_eth_an_lt_dme_downsample_conf *dme_conf;
	al_mod_bool vf_handle;
	/** ETH common registers base address */
	struct al_mod_eth_common_regs __iomem *eth_common_regs_base;
};

/** Ethernet Adapter private data structure used by this driver */
struct al_mod_hal_eth_adapter{
	uint8_t rev_id; /**<PCI adapter revision ID */
	uint8_t dev_id; /**<PCI adapter device ID */
	uint8_t original_rev_id; /**< Original PCI adapter device ID as found in PCI adapter
					used to differentiate if we are eth v2 or eth v4 std */
	uint8_t udma_id; /**< the id of the UDMA used by this adapter */
	uint32_t config_ver; /**< Current HW configuration version. Used for live update of configuration */
	enum al_mod_eth_common_mode common_mode; /**< Ethernet common mode */
	al_mod_bool internal_switching; /**< Loopback mode */
	void __iomem *udma_regs_base;
	struct al_mod_ec_regs __iomem *ec_regs_base;
	void __iomem *ec_ints_base;
	void __iomem *sec_ec_ints_base;
	struct al_mod_eth_mac_regs __iomem *mac_regs_base;
	void __iomem *mac_ints_base;
	struct al_mod_eth_common_regs __iomem *eth_common_regs_base;

	struct al_mod_eth_mac_obj mac_obj; /**< MAC object */

	char *name; /**< the upper layer must keep the string area */

	struct al_mod_udma tx_udma;
	/*	uint8_t tx_queues;*//* number of tx queues */
	struct al_mod_udma rx_udma;
	/*	uint8_t rx_queues;*//* number of tx queues */

	uint8_t		enable_rx_parser; /**< config and enable rx parsing */

	enum al_mod_eth_flow_control_type fc_type; /**< flow control*/

	enum al_mod_eth_mac_mode mac_mode;
	enum al_mod_eth_mdio_if	mdio_if; /**< which mac mdio interface to use */
	enum al_mod_eth_mdio_type mdio_type; /**< mdio protocol type */
	al_mod_bool	shared_mdio_if; /**< when AL_TRUE, the mdio interface is shared with other controllers.*/
	uint8_t curr_lt_unit;
	uint8_t serdes_lane;
};

#define AL_ETH_ADAPTER_PARAMS_HAS_UNIT_ADAPTER		1

/** parameters from upper layer */
struct al_mod_eth_adapter_params{
	uint8_t rev_id; /**<PCI adapter revision ID */
	uint8_t dev_id; /**<PCI adapter device ID */
	uint8_t udma_id; /**< the id of the UDMA used by this adapter */
	enum al_mod_eth_common_mode common_mode; /**< Ethernet common mode */
	al_mod_bool internal_switching; /**< Loopback mode */
	uint8_t	enable_rx_parser; /**< when true, the rx epe parser will be enabled */
	void __iomem *udma_regs_base; /**< UDMA register base address */
	void __iomem *ec_regs_base; /**< Ethernet controller registers base address
				     * can be null if the function is virtual
				     */
	void __iomem *mac_regs_base; /**< Ethernet MAC registers base address
				      * can be null if the function is virtual
				      */
	/** MAC common registers base address, NULL if MAC Ver < 4 */
	void __iomem *mac_common_regs;
	/** MAC common registers lock/unlock callback */
	int (*mac_common_regs_lock)(void *handler, al_mod_bool lock);
	/** MAC common registers lock/unlock handle */
	void __iomem *mac_common_regs_lock_handle;
	/** ETH common registers base address (NULL for rev_id < 4) - Must not
	 * be used concurrently from different contexts. Users should handle
	 * locking if required.
	 */
	void __iomem *eth_common_regs_base;

	char *name; /**< the upper layer must keep the string area */

	uint8_t serdes_lane; /**< serdes lane (relevant to 25G macs only) */

	struct al_mod_unit_adapter *unit_adapter; /* The unit_adapter instance */
	unsigned int	func_num; /* function number */
	al_mod_bool skip_adapter_init; /* if true unit adapter initialization will not be done */
	al_mod_bool force_adapter_init; /* if true unit adapter initialization will be done
				     * even if called by VF */
	al_mod_bool force_ec_init; /* allows forcing EC initialization for udma_id other than 0 */
	al_mod_bool app_int_unmask_bypass; /* Bypass external application interrupt unmask */
};

/* adapter management */
/**
 * initialize the ethernet adapter handle
 * @param adapter the adapter to initialize
 * @param params handle init params
 *
 * This function does not initialize the adapter for TX/RX.
 * Functions that can be called after calling this are :
 *  al_mod_eth_adapter_init
 *  al_mod_eth_board_params_get_ex & al_mod_eth_board_params_set_ex
 */
void al_mod_eth_adapter_handle_init(struct al_mod_hal_eth_adapter *adapter,
	struct al_mod_eth_adapter_handle_init_params *params);

/**
 * reset all the ethernet adapter tables
 *
 * @param adapter pointer to the private structure
 */
void al_mod_eth_adpater_tables_reset(struct al_mod_hal_eth_adapter *adapter);

/**
 * initialize the ethernet adapter's DMA
 * - initialize the adapter data structure
 * - initialize the Tx and Rx UDMA
 * - enable the Tx and Rx UDMA, the rings will be still disabled at this point.
 *
 * @param adapter pointer to the private structure
 * @param params the parameters passed from upper layer
 *
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_adapter_init(struct al_mod_hal_eth_adapter *adapter, struct al_mod_eth_adapter_params *params);

/**
 * Ethernet performance mode configuration
 *
 * Supported since ETHv4
 *
 * @param adapter
 *		Ethernet adapter handle
 * @param mode
 *		Performance mode
 *
 * @return none
 */
void al_mod_eth_perf_mode_config(struct al_mod_hal_eth_adapter *adapter,
	enum al_mod_eth_perf_mode mode);

/**
 * stop the DMA of the ethernet adapter
 *
 * @param adapter pointer to the private structure
 *
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_adapter_stop(struct al_mod_hal_eth_adapter *adapter);

int al_mod_eth_adapter_reset(struct al_mod_hal_eth_adapter *adapter);

/** interrupt controller level (primary/secondary) */
enum al_mod_eth_iofic_level {
	AL_ETH_IOFIC_LEVEL_PRIMARY = 0,
	AL_ETH_IOFIC_LEVEL_SECONDARY
};

/**
 * Get Ethernet controller iofic regs base address
 *
 * @param adapter pointer to the private structure
 * @param level level of iofic (primary / secondary)
 *
 * @return base address
 */
void __iomem *al_mod_eth_iofic_regs_base_get(struct al_mod_hal_eth_adapter *adapter,
		enum al_mod_eth_iofic_level level);

/**
 * Get Ethernet controller EC regs base
 *
 * @param adapter pointer to the private structure
 *
 * @return base address
 */
void __iomem *al_mod_eth_ec_regs_base_get(struct al_mod_hal_eth_adapter *adapter);

/**
 * Get Ethernet adapter common mode
 *
 * @param adapter pointer to the private structure
 *
 * @return mode
 */
enum al_mod_eth_common_mode al_mod_eth_common_mode_get(struct al_mod_hal_eth_adapter *adapter);

/**
 * Get internal MAC object
 *
 * @param adapter pointer to the private structure
 *
 * @return pointer to internal mac object
 */
struct al_mod_eth_mac_obj *al_mod_eth_mac_obj_get(struct al_mod_hal_eth_adapter *adapter);

/**
 * Get internal MAC object
 *
 * @param adapter pointer to the private structure
 *
 * @return adapter revision ID
 */
unsigned int al_mod_eth_rev_id_get(struct al_mod_hal_eth_adapter *adapter);

/**
 * Get internal MAC object
 *
 * @param adapter pointer to the private structure
 *
 * @return adapter device ID
 */
unsigned int al_mod_eth_dev_id_get(struct al_mod_hal_eth_adapter *adapter);

/**
 * Get serdes lane number
 *
 * @param adapter pointer to the private structure
 *
 * @return adapter serdes lane
 */
unsigned int al_mod_eth_get_serdes_lane(struct al_mod_hal_eth_adapter *adapter);

/**
 * Get Ethernet EPE (Ethernet Parser Engine) registers base
 *
 * @param adapter pointer to the private structure
 *
 * @return EPE registres base
 */
void __iomem *al_mod_eth_epe_regs_get(struct al_mod_hal_eth_adapter *adapter);

/**
 * enable the ec and mac interrupts
 *
 * @param adapter pointer to the private structure
 *
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_ec_mac_ints_config(struct al_mod_hal_eth_adapter *adapter);

/**
 * ec and mac interrupt service routine
 * read and print asserted interrupts
 *
 * @param adapter pointer to the private structure
 *
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_ec_mac_isr(struct al_mod_hal_eth_adapter *adapter);

/* Q management */
/**
 * Configure and enable a queue ring
 *
 * @param adapter pointer to the private structure
 * @param type tx or rx
 * @param qid queue index
 * @param q_params queue parameters
 *
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_queue_config(struct al_mod_hal_eth_adapter *adapter, enum al_mod_udma_type type, uint32_t qid,
			struct al_mod_udma_q_params *q_params);


/**
 * enable a queue if it was previously disabled
 *
 * @param adapter pointer to the private structure
 * @param type tx or rx
 * @param qid queue index
 *
 * @return -EPERM (not implemented yet).
 */
int al_mod_eth_queue_enable(struct al_mod_hal_eth_adapter *adapter, enum al_mod_udma_type type, uint32_t qid);

/**
 * disable a queue
 * @param adapter pointer to the private structure
 * @param type tx or rx
 * @param qid queue index
 *
 * @return -EPERM (not implemented yet).
 */
int al_mod_eth_queue_disable(struct al_mod_hal_eth_adapter *adapter, enum al_mod_udma_type type, uint32_t qid);

/* MAC layer */

/**
 * get the adapter capabilities (speed, duplex,..)
 * this function must not be called before configuring the mac mode using al_mod_eth_mac_config()
 * @param adapter pointer to the private structure.
 * @param caps pointer to structure that will be updated by this function
 *
 * @return 0 on success. negative errno on failure.
 */
int al_mod_eth_capabilities_get(struct al_mod_hal_eth_adapter *adapter, struct al_mod_eth_capabilities *caps);

/**
 * configure minimum and maximum rx packet length
 *
 * @param adapter pointer to the private structure
 * @param min_rx_len minimum rx packet length
 * @param max_rx_len maximum rx packet length
 * both length limits in bytes and it includes the MAC Layer header and FCS.
 * @return 0 on success, otherwise on failure.
 */
int al_mod_eth_rx_pkt_limit_config(struct al_mod_hal_eth_adapter *adapter, uint32_t min_rx_len, uint32_t max_rx_len);

/* TX */
/**
 * get number of free tx descriptors
 *
 * @param adapter adapter handle
 * @param qid queue index
 *
 * @return num of free descriptors.
 */
static INLINE uint32_t al_mod_eth_tx_available_get(struct al_mod_hal_eth_adapter *adapter,
					       uint32_t qid)
{
	struct al_mod_udma_q *udma_q;

	al_mod_udma_q_handle_get(&adapter->tx_udma, qid, &udma_q);

	return al_mod_udma_available_get(udma_q);
}

/**
 * prepare packet descriptors in tx queue.
 *
 * This functions prepares the descriptors for the given packet in the tx
 * submission ring. the caller must call al_mod_eth_tx_pkt_action() below
 * in order to notify the hardware about the new descriptors.
 *
 * @param tx_dma_q pointer to UDMA tx queue
 * @param pkt the packet to transmit
 *
 * @return number of descriptors used for this packet, 0 if no free
 * room in the descriptors ring
 */
int al_mod_eth_tx_pkt_prepare(struct al_mod_udma_q *tx_dma_q, struct al_mod_eth_pkt *pkt);


/**
 * Trigger the DMA about previously added tx descriptors.
 *
 * @param tx_dma_q pointer to UDMA tx queue
 * @param tx_descs number of descriptors to notify the DMA about.
 * the tx_descs can be sum of descriptor numbers of multiple prepared packets,
 * this way the caller can use this function to notify the DMA about multiple
 * packets.
 */
void al_mod_eth_tx_dma_action(struct al_mod_udma_q *tx_dma_q, uint32_t tx_descs);

/**
 * get number of completed tx descriptors, upper layer should derive from
 * this information which packets were completed.
 *
 * @param tx_dma_q pointer to UDMA tx queue
 *
 * @return number of completed tx descriptors.
 */
int al_mod_eth_comp_tx_get(struct al_mod_udma_q *tx_dma_q);

/* RX */
/**
 * Config the RX descriptor fields
 *
 * @param adapter pointer to the private structure
 * @param lro_sel select LRO context or l4 offset
 * @param l4_offset_sel select l4 offset source
 * @param l3_offset_sel select l3 offset source
 * @param l3_l4_default_sel select the default header
 * @param l4_sel  select the l4 checksum result
 * @param l3_sel  select the l3 checksum result
 * @param l3_proto_sel select the l3 protocol index source
 * @param l4_proto_sel select the l4 protocol index source
 * @param frag_sel select the frag indication source
 */
void al_mod_eth_rx_desc_config(
			struct al_mod_hal_eth_adapter *adapter,
			enum al_mod_eth_rx_desc_lro_context_val_res lro_sel,
			enum al_mod_eth_rx_desc_l4_offset_sel l4_offset_sel,
			enum al_mod_eth_rx_desc_l3_offset_sel l3_offset_sel,
			enum al_mod_eth_rx_desc_l3_l4_default_chk l3_l4_default_sel,
			enum al_mod_eth_rx_desc_l4_chk_res_sel l4_sel,
			enum al_mod_eth_rx_desc_l3_chk_res_sel l3_sel,
			enum al_mod_eth_rx_desc_l3_proto_idx_sel l3_proto_sel,
			enum al_mod_eth_rx_desc_l4_proto_idx_sel l4_proto_sel,
			enum al_mod_eth_rx_desc_frag_sel frag_sel);

/**
 * Configure RX header split
 *
 * @param adapter pointer to the private structure
 * @param enable header split when AL_TRUE
 * @param header_len length in bytes of the header split, this value used when
 * CTRL TABLE header split len select is set to
 * AL_ETH_CTRL_TABLE_HDR_SPLIT_LEN_SEL_REG, in this case the controller will
 * store the first header_split_len bytes into buf2, then the rest (if any) into buf1.
 * when CTRL_TABLE header split len select set to other value, then the header_len
 * determined according to the parser, and the header_split_len parameter is not
 * used.
 *
 * return 0 on success. otherwise on failure.
 */
int al_mod_eth_rx_header_split_config(struct al_mod_hal_eth_adapter *adapter, al_mod_bool enable, uint32_t header_len);

/**
 * enable / disable header split in the udma queue.
 * length will be taken from the udma configuration to enable different length per queue.
 *
 * @param adapter pointer to the private structure
 * @param enable header split when AL_TRUE
 * @param qid the queue id to enable/disable header split
 * @param header_len in what len the udma will cut the header
 *
 * return 0 on success.
 */
int al_mod_eth_rx_header_split_force_len_config(struct al_mod_hal_eth_adapter *adapter,
					al_mod_bool enable,
					uint32_t qid,
					uint32_t header_len);

/**
 * add buffer to receive queue
 *
 * @param rx_dma_q pointer to UDMA rx queue
 * @param buf pointer to data buffer
 * @param flags bitwise of AL_ETH_RX_FLAGS
 * @param header_buf this is not used for far and header_buf should be set to
 * NULL.
 *
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_rx_buffer_add(struct al_mod_udma_q *rx_dma_q,
			      struct al_mod_buf *buf, uint32_t flags,
			      struct al_mod_buf *header_buf);

/**
 * notify the hw engine about rx descriptors that were added to the receive queue
 *
 * @param rx_dma_q pointer to UDMA rx queue
 * @param descs_num number of rx descriptors
 */
void al_mod_eth_rx_buffer_action(struct al_mod_udma_q *rx_dma_q,
				uint32_t descs_num);

/**
 * get packet from RX completion ring
 *
 * @param rx_dma_q pointer to UDMA rx queue
 * @param pkt pointer to a packet data structure, this function fills this
 * structure with the information about the received packet. the buffers
 * structures filled only with the length of the data written into the buffer,
 * the address fields are not updated as the upper layer can retrieve this
 * information by itself because the hardware uses the buffers in the same order
 * were those buffers inserted into the ring of the receive queue.
 * this structure should be allocated by the caller function.
 *
 * @return return number of descriptors or 0 if no completed packet found.
 */
 uint32_t al_mod_eth_pkt_rx(struct al_mod_udma_q *rx_dma_q, struct al_mod_eth_pkt *pkt);

/**
 * update rx parser entry
 *
 * @param adapter pointer to the private structure
 * @param idx the protocol index to update
 * @param reg_entry contents of parser register entry
 * @param control_entry entry contents of control table entry
 *
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_rx_parser_entry_update(struct al_mod_hal_eth_adapter *adapter, uint32_t idx,
		struct al_mod_eth_epe_p_reg_entry *reg_entry,
		struct al_mod_eth_epe_control_entry *control_entry);

/**
 * get rx ethernet parser engine entry
 * added to support master HAL compilations
 *
 * @param adapter pointer to the private structure
 * @param idx the protocol index to update
 * @param reg_entry contents of parser register entry
 * @param control_entry entry contents of control table entry
 * @param control_table_idx control table index
 */
void al_mod_eth_epe_entry_get(struct al_mod_hal_eth_adapter *adapter, uint32_t idx,
			struct al_mod_eth_epe_p_reg_entry *reg_entry,
			struct al_mod_eth_epe_control_entry *control_entry,
			unsigned int control_table_idx);

/**
 * set rx ethernet parser engine entry
 * This is the same as al_mod_eth_rx_parser_entry_update
 * and is added to support old master HAL compilations
 *
 * @param adapter pointer to the private structure
 * @param idx the protocol index to update
 * @param reg_entry contents of parser register entry
 * @param control_entry entry contents of control table entry
  */
void al_mod_eth_epe_entry_set(struct al_mod_hal_eth_adapter *adapter, uint32_t idx,
			  struct al_mod_eth_epe_p_reg_entry *reg_entry,
			  struct al_mod_eth_epe_control_entry *control_entry);

/* Flow Steering and filtering */
int al_mod_eth_thash_table_set(struct al_mod_hal_eth_adapter *adapter, uint32_t idx, uint8_t udma, uint32_t queue);

/* FSM table bits */
/** FSM table has 7 bits input address:
 *  bits[2:0] are the outer packet's type (IPv4, TCP...)
 *  bits[5:3] are the inner packet's type
 *  bit[6] is set when packet is tunneled.
 *
 * The output of each entry:
 *  bits[1:0] - input selection: selects the input for the thash (2/4 tuple, inner/outer)
 *  bit[2] - selects whether to use thash output, or default values for the queue and udma
 *  bits[6:3] default UDMA mask: the UDMAs to select when bit 2 above was unset
 *  bits[9:5] default queue: the queue index to select when bit 2 above was unset
 */

#define AL_ETH_FSM_ENTRY_IPV4_TCP	   0
#define AL_ETH_FSM_ENTRY_IPV4_UDP	   1
#define AL_ETH_FSM_ENTRY_IPV6_TCP	   2
#define AL_ETH_FSM_ENTRY_IPV6_UDP	   3
#define AL_ETH_FSM_ENTRY_IPV6_NO_UDP_TCP   4
#define AL_ETH_FSM_ENTRY_IPV4_NO_UDP_TCP   5
#define AL_ETH_FSM_ENTRY_IPV4_FRAGMENTED   6
#define AL_ETH_FSM_ENTRY_NOT_IP		   7

#define AL_ETH_FSM_ENTRY_OUTER(idx)	   ((idx) & 7)
#define AL_ETH_FSM_ENTRY_INNER(idx)	   (((idx) >> 3) & 7)
#define AL_ETH_FSM_ENTRY_TUNNELED(idx)	   (((idx) >> 6) & 1)

/* FSM DATA format */
#define AL_ETH_FSM_DATA_OUTER_2_TUPLE	0
#define AL_ETH_FSM_DATA_OUTER_4_TUPLE	1
#define AL_ETH_FSM_DATA_INNER_2_TUPLE	2
#define AL_ETH_FSM_DATA_INNER_4_TUPLE	3

#define AL_ETH_FSM_DATA_HASH_SEL	(1 << 2)

#define AL_ETH_FSM_DATA_DEFAULT_Q_SHIFT		7
#define AL_ETH_FSM_DATA_DEFAULT_UDMA_SHIFT	3

/* set fsm table entry */
int al_mod_eth_fsm_table_set(struct al_mod_hal_eth_adapter *adapter, uint32_t idx, uint32_t entry);

enum AL_ETH_FWD_CTRL_IDX_VLAN_TABLE_OUT {
	AL_ETH_FWD_CTRL_IDX_VLAN_TABLE_OUT_0 = 0,
	AL_ETH_FWD_CTRL_IDX_VLAN_TABLE_OUT_1 = 1,
	AL_ETH_FWD_CTRL_IDX_VLAN_TABLE_OUT_ANY = 2,
};

enum AL_ETH_FWD_CTRL_IDX_TUNNEL {
	AL_ETH_FWD_CTRL_IDX_TUNNEL_NOT_EXIST = 0,
	AL_ETH_FWD_CTRL_IDX_TUNNEL_EXIST = 1,
	AL_ETH_FWD_CTRL_IDX_TUNNEL_ANY = 2,
};

enum AL_ETH_FWD_CTRL_IDX_VLAN {
	AL_ETH_FWD_CTRL_IDX_VLAN_NOT_EXIST = 0,
	AL_ETH_FWD_CTRL_IDX_VLAN_EXIST = 1,
	AL_ETH_FWD_CTRL_IDX_VLAN_ANY = 2,
};

enum AL_ETH_FWD_CTRL_IDX_MAC_TABLE {
	AL_ETH_FWD_CTRL_IDX_MAC_TABLE_NO_MATCH = 0,
	AL_ETH_FWD_CTRL_IDX_MAC_TABLE_MATCH = 1,
	AL_ETH_FWD_CTRL_IDX_MAC_TABLE_ANY = 2,
};

enum AL_ETH_FWD_CTRL_IDX_MAC_DA_TYPE {
	AL_ETH_FWD_CTRL_IDX_MAC_DA_TYPE_UC = 0, /**< unicast */
	AL_ETH_FWD_CTRL_IDX_MAC_DA_TYPE_MC = 1, /**< multicast */
	AL_ETH_FWD_CTRL_IDX_MAC_DA_TYPE_BC = 2, /**< broadcast */
	AL_ETH_FWD_CTRL_IDX_MAC_DA_TYPE_ANY = 4, /**< for sw usage */
};

/**
 * This structure defines the index or group of indeces within the control table.
 * each field has special enum value (with _ANY postfix) that indicates all
 * possible values of that field.
 */
struct al_mod_eth_fwd_ctrl_table_index {
	enum AL_ETH_FWD_CTRL_IDX_VLAN_TABLE_OUT	vlan_table_out;
	enum AL_ETH_FWD_CTRL_IDX_TUNNEL tunnel_exist;
	enum AL_ETH_FWD_CTRL_IDX_VLAN vlan_exist;
	enum AL_ETH_FWD_CTRL_IDX_MAC_TABLE mac_table_match;
	enum AL_ETH_PROTO_ID		protocol_id;
	enum AL_ETH_FWD_CTRL_IDX_MAC_DA_TYPE mac_type;
};

enum AL_ETH_CTRL_TABLE_PRIO_SEL {
	AL_ETH_CTRL_TABLE_PRIO_SEL_PBITS_TABLE	= 0,
	AL_ETH_CTRL_TABLE_PRIO_SEL_DSCP_TABLE	= 1,
	AL_ETH_CTRL_TABLE_PRIO_SEL_TC_TABLE	= 2,
	AL_ETH_CTRL_TABLE_PRIO_SEL_REG1		= 3,
	AL_ETH_CTRL_TABLE_PRIO_SEL_REG2		= 4,
	AL_ETH_CTRL_TABLE_PRIO_SEL_REG3		= 5,
	AL_ETH_CTRL_TABLE_PRIO_SEL_REG4		= 6,
	AL_ETH_CTRL_TABLE_PRIO_SEL_REG5		= 7,
	AL_ETH_CTRL_TABLE_PRIO_SEL_REG6		= 7,
	AL_ETH_CTRL_TABLE_PRIO_SEL_REG7		= 9,
	AL_ETH_CTRL_TABLE_PRIO_SEL_REG8		= 10,
	AL_ETH_CTRL_TABLE_PRIO_SEL_VAL_3	= 11,
	AL_ETH_CTRL_TABLE_PRIO_SEL_VAL_0	= 12,
};
/** where to select the initial queue from */
enum AL_ETH_CTRL_TABLE_QUEUE_SEL_1 {
	AL_ETH_CTRL_TABLE_QUEUE_SEL_1_PRIO_TABLE	= 0,
	AL_ETH_CTRL_TABLE_QUEUE_SEL_1_THASH_TABLE	= 1,
	AL_ETH_CTRL_TABLE_QUEUE_SEL_1_MAC_TABLE		= 2,
	AL_ETH_CTRL_TABLE_QUEUE_SEL_1_MHASH_TABLE	= 3,
	AL_ETH_CTRL_TABLE_QUEUE_SEL_1_REG1		= 4,
	AL_ETH_CTRL_TABLE_QUEUE_SEL_1_REG2		= 5,
	AL_ETH_CTRL_TABLE_QUEUE_SEL_1_REG3		= 6,
	AL_ETH_CTRL_TABLE_QUEUE_SEL_1_REG4		= 7,
	AL_ETH_CTRL_TABLE_QUEUE_SEL_1_VAL_3		= 12,
	AL_ETH_CTRL_TABLE_QUEUE_SEL_1_VAL_0		= 13,
};

/** target queue will be built up from the priority and initial queue */
enum AL_ETH_CTRL_TABLE_QUEUE_SEL_2 {
	AL_ETH_CTRL_TABLE_QUEUE_SEL_2_PRIO_TABLE	= 0, /**< target queue is the output of priority table */
	AL_ETH_CTRL_TABLE_QUEUE_SEL_2_PRIO		= 1, /**< target queue is the priority */
	AL_ETH_CTRL_TABLE_QUEUE_SEL_2_PRIO_QUEUE	= 2, /**< target queue is initial queue[0], priority[1] */
	AL_ETH_CTRL_TABLE_QUEUE_SEL_2_NO_PRIO		= 3, /**< target queue is the initial */
};

enum AL_ETH_CTRL_TABLE_UDMA_SEL {
	AL_ETH_CTRL_TABLE_UDMA_SEL_THASH_TABLE		= 0,
	AL_ETH_CTRL_TABLE_UDMA_SEL_THASH_AND_VLAN	= 1,
	AL_ETH_CTRL_TABLE_UDMA_SEL_VLAN_TABLE		= 2,
	AL_ETH_CTRL_TABLE_UDMA_SEL_VLAN_AND_MAC		= 3,
	AL_ETH_CTRL_TABLE_UDMA_SEL_MAC_TABLE		= 4,
	AL_ETH_CTRL_TABLE_UDMA_SEL_MAC_AND_MHASH	= 5,
	AL_ETH_CTRL_TABLE_UDMA_SEL_MHASH_TABLE		= 6,
	AL_ETH_CTRL_TABLE_UDMA_SEL_REG1			= 7,
	AL_ETH_CTRL_TABLE_UDMA_SEL_REG2			= 8,
	AL_ETH_CTRL_TABLE_UDMA_SEL_REG3			= 9,
	AL_ETH_CTRL_TABLE_UDMA_SEL_REG4			= 10,
	AL_ETH_CTRL_TABLE_UDMA_SEL_REG5			= 11,
	AL_ETH_CTRL_TABLE_UDMA_SEL_REG6			= 12,
	AL_ETH_CTRL_TABLE_UDMA_SEL_REG7			= 13,
	AL_ETH_CTRL_TABLE_UDMA_SEL_REG8			= 14,
	AL_ETH_CTRL_TABLE_UDMA_SEL_VAL_0		= 15,
};

enum AL_ETH_CTRL_TABLE_HDR_SPLIT_LEN_SEL {
	AL_ETH_CTRL_TABLE_HDR_SPLIT_LEN_SEL_0		= 0,
	AL_ETH_CTRL_TABLE_HDR_SPLIT_LEN_SEL_REG		= 1, /**< select header len from the hdr_split register (set by al_mod_eth_rx_header_split_config())*/
	AL_ETH_CTRL_TABLE_HDR_SPLIT_LEN_SEL_OUTER_L3_OFFSET = 2,
	AL_ETH_CTRL_TABLE_HDR_SPLIT_LEN_SEL_OUTER_L4_OFFSET = 3,
	AL_ETH_CTRL_TABLE_HDR_SPLIT_LEN_SEL_TUNNEL_START_OFFSET = 4,
	AL_ETH_CTRL_TABLE_HDR_SPLIT_LEN_SEL_INNER_L3_OFFSET = 5,
	AL_ETH_CTRL_TABLE_HDR_SPLIT_LEN_SEL_INNER_L4_OFFSET = 6,
};

struct al_mod_eth_fwd_ctrl_table_entry {
	enum AL_ETH_CTRL_TABLE_PRIO_SEL		prio_sel;
	enum AL_ETH_CTRL_TABLE_QUEUE_SEL_1	queue_sel_1; /**< queue id source */
	enum AL_ETH_CTRL_TABLE_QUEUE_SEL_2	queue_sel_2; /**< mix queue id with priority */
	enum AL_ETH_CTRL_TABLE_UDMA_SEL		udma_sel;
	enum AL_ETH_CTRL_TABLE_HDR_SPLIT_LEN_SEL hdr_split_len_sel;
	al_mod_bool 	filter; /**< set to AL_TRUE to enable filtering */
};
/**
 * Configure default control table entry
 *
 * @param adapter pointer to the private structure
 * @param use_table set to AL_TRUE if control table is used, when set to AL_FALSE
 * then control table will be bypassed and the entry value will be used.
 * @param entry defines the value to be used when bypassing control table.
 *
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_ctrl_table_def_set(struct al_mod_hal_eth_adapter *adapter,
			      al_mod_bool use_table,
			      struct al_mod_eth_fwd_ctrl_table_entry *entry);

/**
 * Configure control table entry
 *
 * @param adapter pointer to the private structure
 * @param index the entry index within the control table.
 * @param entry the value to write to the control table entry
 *
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_ctrl_table_set(struct al_mod_hal_eth_adapter *adapter,
			  struct al_mod_eth_fwd_ctrl_table_index *index,
			  struct al_mod_eth_fwd_ctrl_table_entry *entry);

int al_mod_eth_ctrl_table_raw_set(struct al_mod_hal_eth_adapter *adapter, uint32_t idx, uint32_t entry);
int al_mod_eth_ctrl_table_raw_get(struct al_mod_hal_eth_adapter *adapter, uint32_t idx, uint32_t *entry);
int al_mod_eth_ctrl_table_def_raw_set(struct al_mod_hal_eth_adapter *adapter, uint32_t val);
int al_mod_eth_ctrl_table_def_raw_get(struct al_mod_hal_eth_adapter *adapter, uint32_t *val);

/**
 * Configure hash key initial registers
 * Those registers define the initial key values, those values used for
 * the THASH and MHASH hash functions.
 *
 * @param adapter pointer to the private structure
 * @param idx the register index
 * @param val the register value
 *
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_hash_key_set(struct al_mod_hal_eth_adapter *adapter, uint32_t idx, uint32_t val);

struct al_mod_eth_fwd_mac_table_entry {
	uint8_t		addr[6]; /**< byte 0 is the first byte seen on the wire */
	uint8_t		mask[6];
	al_mod_bool		tx_valid;
	uint8_t		tx_target;
	al_mod_bool		rx_valid;
	uint8_t		udma_mask; /**< target udma */
	uint8_t		qid; /**< target queue */
	al_mod_bool		filter; /**< set to AL_TRUE to enable filtering */
};

/**
 * Configure mac table entry
 * The HW traverse this table and looks for match from lowest index,
 * when the packets MAC DA & mask == addr, and the valid bit is set, then match occurs.
 *
 * @param adapter pointer to the private structure
 * @param idx the entry index within the mac table.
 * @param entry the contents of the MAC table entry
 *
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_fwd_mac_table_set(struct al_mod_hal_eth_adapter *adapter, uint32_t idx,
				struct al_mod_eth_fwd_mac_table_entry *entry);

int al_mod_eth_fwd_mac_addr_raw_set(struct al_mod_hal_eth_adapter *adapter, uint32_t idx,
				uint32_t addr_lo, uint32_t addr_hi, uint32_t mask_lo, uint32_t mask_hi);
int al_mod_eth_fwd_mac_ctrl_raw_set(struct al_mod_hal_eth_adapter *adapter, uint32_t idx, uint32_t ctrl);

int al_mod_eth_mac_addr_store(void * __iomem ec_base, uint32_t idx, uint8_t *addr);
int al_mod_eth_mac_addr_read(void * __iomem ec_base, uint32_t idx, uint8_t *addr);

/**
 * Configure pbits table entry
 * The HW uses this table to translate between vlan pbits field to priority.
 * The vlan pbits is used as the index of this table.
 *
 * @param adapter pointer to the private structure
 * @param idx the entry index within the table.
 * @param prio the priority to set for this entry
 *
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_fwd_pbits_table_set(struct al_mod_hal_eth_adapter *adapter, uint32_t idx, uint8_t prio);

/**
 * Configure priority table entry
 * The HW uses this table to translate between priority to queue index.
 * The priority is used as the index of this table.
 *
 * @param adapter pointer to the private structure
 * @param prio the entry index within the table.
 * @param qid the queue index to set for this entry (priority).
 *
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_fwd_priority_table_set(struct al_mod_hal_eth_adapter *adapter, uint8_t prio, uint8_t qid);

/**
 * Configure DSCP table entry
 * The HW uses this table to translate between IPv4 DSCP field to priority.
 * The IPv4 byte 1 (DSCP+ECN) used as index to this table.
 *
 * @param adapter pointer to the private structure
 * @param idx the entry index within the table.
 * @param prio the queue index to set for this entry (priority).
 *
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_fwd_dscp_table_set(struct al_mod_hal_eth_adapter *adapter, uint32_t idx, uint8_t prio);

/**
 * Configure TC table entry
 * The HW uses this table to translate between IPv6 TC field to priority.
 * The IPv6 TC used as index to this table.
 *
 * @param adapter pointer to the private structure
 * @param idx the entry index within the table.
 * @param prio the queue index to set for this entry (priority).
 *
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_fwd_tc_table_set(struct al_mod_hal_eth_adapter *adapter, uint32_t idx, uint8_t prio);

/**
 * Configure MAC HASH table entry
 * The HW uses 8 bits from the hash result on the MAC DA as index to this table.
 *
 * @param adapter pointer to the private structure
 * @param idx the entry index within the table.
 * @param udma_mask the target udma to set for this entry.
 * @param qid the target queue index to set for this entry.
 *
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_fwd_mhash_table_set(struct al_mod_hal_eth_adapter *adapter, uint32_t idx, uint8_t udma_mask, uint8_t qid);

struct al_mod_eth_fwd_vid_table_entry {
	uint8_t	control:1; /**< used as input for the control table */
	uint8_t filter:1; /**< set to 1 to enable filtering */
	uint8_t udma_mask:4; /**< target udmas */
};

/**
 * Configure default vlan table entry
 *
 * @param adapter pointer to the private structure
 * @param use_table set to AL_TRUE if vlan table is used, when set to AL_FALSE
 * then vid table will be bypassed and the default_entry value will be used.
 * @param default_entry defines the value to be used when bypassing vid table.
 * @param default_vlan defines the value will be used when untagget packet
 * received. this value will be used only for steering and filtering control,
 * the packet's data will not be changed.
 *
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_fwd_vid_config_set(struct al_mod_hal_eth_adapter *adapter, al_mod_bool use_table,
			      struct al_mod_eth_fwd_vid_table_entry *default_entry,
			      uint32_t default_vlan);
/**
 * Configure vlan table entry
 *
 * @param adapter pointer to the private structure
 * @param idx the entry index within the vlan table. The HW uses the vlan id
 * field of the packet when accessing this table.
 * @param entry the value to write to the vlan table entry
 *
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_fwd_vid_table_set(struct al_mod_hal_eth_adapter *adapter, uint32_t idx,
			     struct al_mod_eth_fwd_vid_table_entry *entry);


/**
 * Configure default UDMA register
 * When the control table entry udma selection set to AL_ETH_CTRL_TABLE_UDMA_SEL_REG<n>,
 * then the target UDMA will be set according to the register n of the default
 * UDMA registers.
 *
 * @param adapter pointer to the private structure
 * @param idx the index of the default register.
 * @param udma_mask the value of the register.
 *
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_fwd_default_udma_config(struct al_mod_hal_eth_adapter *adapter, uint32_t idx,
				   uint8_t udma_mask);

/**
 * Configure default queue register
 * When the control table entry queue selection 1 set to AL_ETH_CTRL_TABLE_QUEUE_SEL_1_REG<n>,
 * then the target queue will be set according to the register n of the default
 * queue registers.
 *
 * @param adapter pointer to the private structure
 * @param idx the index of the default register.
 * @param qid the value of the register.
 *
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_fwd_default_queue_config(struct al_mod_hal_eth_adapter *adapter, uint32_t idx,
				   uint8_t qid);

/**
 * Configure default priority register
 * When the control table entry queue selection 1 set to AL_ETH_CTRL_TABLE_PRIO_SEL_1_REG<n>,
 * then the target priority will be set according to the register n of the default
 * priority registers.
 *
 * @param adapter pointer to the private structure
 * @param idx the index of the default register.
 * @param prio the value of the register.
 *
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_fwd_default_priority_config(struct al_mod_hal_eth_adapter *adapter, uint32_t idx,
				   uint8_t prio);



/* filter undetected MAC DA */
#define AL_ETH_RFW_FILTER_UNDET_MAC          (1 << 0)
/* filter specific MAC DA based on MAC table output */
#define AL_ETH_RFW_FILTER_DET_MAC            (1 << 1)
/* filter all tagged */
#define AL_ETH_RFW_FILTER_TAGGED             (1 << 2)
/* filter all untagged */
#define AL_ETH_RFW_FILTER_UNTAGGED           (1 << 3)
/* filter all broadcast */
#define AL_ETH_RFW_FILTER_BC                 (1 << 4)
/* filter all multicast */
#define AL_ETH_RFW_FILTER_MC                 (1 << 5)
/* filter packet based on parser drop */
#define AL_ETH_RFW_FILTER_PARSE              (1 << 6)
/* filter packet based on VLAN table output */
#define AL_ETH_RFW_FILTER_VLAN_VID           (1 << 7)
/* filter packet based on control table output */
#define AL_ETH_RFW_FILTER_CTRL_TABLE         (1 << 8)
/* filter packet based on protocol index */
#define AL_ETH_RFW_FILTER_PROT_INDEX         (1 << 9)
/* filter packet based on WoL decision */
#define AL_ETH_RFW_FILTER_WOL		     (1 << 10)


struct al_mod_eth_filter_params {
	al_mod_bool		enable;
	uint32_t	filters; /**< bitmask of AL_ETH_RFW_FILTER.. for filters to enable */
	al_mod_bool		filter_proto[AL_ETH_PROTOCOLS_NUM]; /**< set AL_TRUE for protocols to filter */
};

struct al_mod_eth_filter_override_params {
	uint32_t	filters; /**< bitmask of AL_ETH_RFW_FILTER.. for filters to override */
	uint8_t		udma; /**< target udma id */
	uint8_t		qid; /**< target queue id */
};

/**
 * Configure the receive filters
 * this function enables/disables filtering packets and which filtering
 * types to apply.
 * filters that indicated in tables (MAC table, VLAN and Control tables)
 * are not configured by this function. This functions only enables/disables
 * respecting the filter indication from those tables.
 *
 * @param adapter pointer to the private structure
 * @param params the parameters passed from upper layer
 *
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_filter_config(struct al_mod_hal_eth_adapter *adapter, struct al_mod_eth_filter_params *params);

/**
 * Configure the receive override filters
 * This function controls whither to force forwarding filtered packets
 * to a specific UDMA/queue. The override filters apply only for
 * filters that enabled by al_mod_eth_filter_config().
 *
 * @param adapter pointer to the private structure
 * @param params override config parameters
 *
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_filter_override_config(struct al_mod_hal_eth_adapter *adapter,
				  struct al_mod_eth_filter_override_params *params);


int al_mod_eth_switching_config_set(struct al_mod_hal_eth_adapter *adapter, uint8_t udma_id, uint8_t forward_all_to_mac, uint8_t enable_int_switching,
					enum al_mod_eth_tx_switch_vid_sel_type vid_sel_type,
					enum al_mod_eth_tx_switch_dec_type uc_dec,
					enum al_mod_eth_tx_switch_dec_type mc_dec,
					enum al_mod_eth_tx_switch_dec_type bc_dec);
int al_mod_eth_switching_default_bitmap_set(struct al_mod_hal_eth_adapter *adapter, uint8_t udma_id, uint8_t udma_uc_bitmask,
						uint8_t udma_mc_bitmask,uint8_t udma_bc_bitmask);
int al_mod_eth_flow_control_config(struct al_mod_hal_eth_adapter *adapter, struct al_mod_eth_flow_control_params *params);

/** Ethernet eee structure */
struct al_mod_eth_eee_params {
	uint8_t enable;
	uint32_t tx_eee_timer;	/** time in cycles the interface delays prior */
				/** to entering eee state */
	uint32_t min_interval;	/** minimum interval in cycles between two eee states */
	uint32_t stop_cnt;	/** time in cycles to stop Tx mac interface */
				/** after getting out of eee state */
	al_mod_bool fast_wake;	/** fast_wake is only applicable to 40/50G, */
				/** otherwise the mode is deep_sleep */
};

/**
 * configure EEE mode
 * @param adapter pointer to the private structure.
 * @param params pointer to the eee input parameters.
 *
 * @return return 0 on success. otherwise on failure.
 */
int al_mod_eth_eee_config(struct al_mod_hal_eth_adapter *adapter, struct al_mod_eth_eee_params *params);

/**
 * get EEE configuration
 * @param adapter pointer to the private structure.
 * @param params pointer to the eee output parameters.
 *
 * @return return 0 on success. otherwise on failure.
 */
int al_mod_eth_eee_get(struct al_mod_hal_eth_adapter *adapter, struct al_mod_eth_eee_params *params);

int al_mod_eth_vlan_mod_config(struct al_mod_hal_eth_adapter *adapter, uint8_t udma_id, uint16_t udma_etype, uint16_t vlan1_data, uint16_t vlan2_data);

/* Timestamp
 * This is a generic time-stamp mechanism that can be used as generic to
 * time-stamp every received or transmit packet it can also support IEEE 1588v2
 * PTP time synchronization protocol.
 * In addition to time-stamp, an internal system time is maintained. For
 * further accuracy, the chip support transmit/receive clock synchronization
 * including recovery of master clock from one of the ports and distributing it
 * to the rest of the ports - that is outside the scope of the Ethernet
 * Controller - please refer to Annapurna Labs Alpine Hardware Wiki
 */

/* Timestamp management APIs */

/**
 * prepare the adapter for timestamping packets.
 * Rx timestamps requires using 8 words (8x4 bytes) rx completion descriptor
 * size as the timestamp value added into word 4.
 *
 * This function should be called after al_mod_eth_mac_config() and before
 * enabling the queues.
 * @param adapter pointer to the private structure.
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_ts_init(struct al_mod_hal_eth_adapter *adapter);

/* Timestamp data path APIs */

/*
 * This is the size of the on-chip array that keeps the time-stamp of the
 * latest transmitted packets
 */
#define AL_ETH_PTH_TX_SAMPLES_NUM	16

/**
 * read Timestamp sample value of previously transmitted packet.
 *
 * The adapter includes AL_ETH_PTH_TX_SAMPLES_NUM timestamp samples for tx
 * packets, those samples shared for all the UDMAs and queues. the al_mod_eth_pkt
 * data structure includes the index of which sample to use for the packet
 * to transmit. It's the caller's responsibility to manage those samples,
 * for example, when using an index, the caller must make sure the packet
 * is completed and the tx time is sampled before using that index for
 * another packet.
 *
 * This function should be called after the completion indication of the
 * tx packet. however, there is a little chance that the timestamp sample
 * won't be updated yet, thus this function must be called again when it
 * returns -EAGAIN.
 * @param adapter pointer to the private structure.
 * @param ts_index the index (out of 16) of the timestamp register
 * @param timestamp the timestamp value in 2^18 femtoseconds resolution.
 * @return -EAGAIN if the sample was not updated yet. 0 when the sample
 * was updated and no errors found.
 */
int al_mod_eth_tx_ts_val_get(struct al_mod_hal_eth_adapter *adapter, uint8_t ts_index,
			 uint32_t *timestamp);

/* Timestamp PTH (PTP Timestamp Handler) control and times management */
/** structure for describing PTH epoch time */
struct al_mod_eth_pth_time {
	uint32_t	seconds; /**< seconds */
	uint64_t	femto; /**< femto seconds */
};

/**
 * Read the systime value
 * This API should not be used to get the timestamp of packets.
 * The HW maintains 50 bits for the sub-seconds portion in femto resolution,
 * but this function reads only the 32 MSB bits since the LSB provides
 * sub-nanoseconds accuracy, which is not needed.
 * @param adapter pointer to the private structure.
 * @param systime pointer to structure where the time will be stored.
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_pth_systime_read(struct al_mod_hal_eth_adapter *adapter,
			    struct al_mod_eth_pth_time *systime);

/**
 * Set the clock period to a given value.
 * The systime will be incremented by this value on each posedge of the
 * adapters internal clock which driven by the SouthBridge clock.
 * @param adapter pointer to the private structure.
 * @param clk_period the clock period in femto seconds.
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_pth_clk_period_write(struct al_mod_hal_eth_adapter *adapter,
				uint64_t clk_period);

/**< enum for methods when updating systime using triggers */
enum al_mod_eth_pth_update_method {
	AL_ETH_PTH_UPDATE_METHOD_SET = 0, /**< Set the time in int/ext update time */
	AL_ETH_PTH_UPDATE_METHOD_INC = 1, /**< increment */
	AL_ETH_PTH_UPDATE_METHOD_DEC = 2, /**< decrement */
	AL_ETH_PTH_UPDATE_METHOD_ADD_TO_LAST = 3, /**< Set to last time + int/ext update time.*/
};

/**< systime internal update trigger types */
enum al_mod_eth_pth_int_trig {
	AL_ETH_PTH_INT_TRIG_OUT_PULSE_0 = 0, /**< use output pulse as trigger */
	AL_ETH_PTH_INT_TRIG_REG_WRITE = 1, /**< use the int update register
					    * write as a trigger
					    */
};

/**< parameters for internal trigger update */
struct al_mod_eth_pth_int_update_params {
	al_mod_bool		enable; /**< enable internal trigger update */
	enum al_mod_eth_pth_update_method	method; /**< internal trigger update
						 * method
						 */
	enum al_mod_eth_pth_int_trig	trigger; /**< which internal trigger to
						  * use
						  */
};

/**
 * Configure the systime internal update
 *
 * @param adapter pointer to the private structure.
 * @param params the configuration of the internal update.
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_pth_int_update_config(struct al_mod_hal_eth_adapter *adapter,
				 struct al_mod_eth_pth_int_update_params const *params);

/**
 * set internal update time
 *
 * The update time used when updating the systime with
 * internal update method.
 *
 * @param adapter pointer to the private structure.
 * @param time the internal update time value
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_pth_int_update_time_set(struct al_mod_hal_eth_adapter *adapter,
				   struct al_mod_eth_pth_time const *time);

/**< parameters for external trigger update */
struct al_mod_eth_pth_ext_update_params {
	uint8_t		triggers; /**< bitmask of external triggers to enable */
	enum al_mod_eth_pth_update_method	method; /**< external trigger update
						 * method
						 */
};

/**
 * Configure the systime external update.
 * external update triggered by external signals such as GPIO or pulses
 * from other eth controllers on the SoC.
 *
 * @param adapter pointer to the private structure.
 * @param params the configuration of the external update.
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_pth_ext_update_config(struct al_mod_hal_eth_adapter *adapter,
				 struct al_mod_eth_pth_ext_update_params const *params);

/**
 * set external update time
 *
 * The update time used when updating the systime with
 * external update method.
 * @param adapter pointer to the private structure.
 * @param time the external update time value
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_pth_ext_update_time_set(struct al_mod_hal_eth_adapter *adapter,
				   struct al_mod_eth_pth_time const *time);
/**
 * set the read compensation delay
 *
 * When reading the systime, the HW adds this value to compensate
 * read latency.
 *
 * @param adapter pointer to the private structure.
 * @param subseconds the read latency delay in femto seconds.
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_pth_read_compensation_set(struct al_mod_hal_eth_adapter *adapter,
				     uint64_t subseconds);
/**
 * set the internal write compensation delay
 *
 * When updating the systime due to an internal trigger's event, the HW adds
 * this value to compensate latency.
 *
 * @param adapter pointer to the private structure.
 * @param subseconds the write latency delay in femto seconds.
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_pth_int_write_compensation_set(struct al_mod_hal_eth_adapter *adapter,
					  uint64_t subseconds);

/**
 * set the external write compensation delay
 *
 * When updating the systime due to an external trigger's event, the HW adds
 * this value to compensate pulse propagation latency.
 *
 * @param adapter pointer to the private structure.
 * @param subseconds the write latency delay in femto seconds.
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_pth_ext_write_compensation_set(struct al_mod_hal_eth_adapter *adapter,
					  uint64_t subseconds);

/**
 * set the sync compensation delay
 *
 * When the adapter passes systime from PTH to MAC to do the packets
 * timestamping, the sync compensation delay is added to systime value to
 * compensate the latency between the PTH and the MAC.
 *
 * @param adapter pointer to the private structure.
 * @param subseconds the sync latency delay in femto seconds.
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_pth_sync_compensation_set(struct al_mod_hal_eth_adapter *adapter,
				     uint64_t subseconds);

#define AL_ETH_PTH_PULSE_OUT_NUM	8
struct al_mod_eth_pth_pulse_out_params {
	uint8_t		index; /**< id of the pulse (0..7) */
	al_mod_bool		enable;
	al_mod_bool		periodic; /**< when true, generate periodic pulse (PPS) */
	uint8_t		period_sec; /**< for periodic pulse, this is seconds
				     * portion of the period time
				     */
	uint32_t	period_us; /**< this is microseconds portion of the
				      * period
				      */
	struct al_mod_eth_pth_time	start_time; /**< when to start pulse triggering */
	uint64_t	pulse_width; /**< pulse width in femto seconds */
};

/**
 * Configure an output pulse
 * This function configures an output pulse coming from the internal System
 * Time. This is typically a 1Hhz pulse that is used to synchronize the
 * rest of the components of the system. This API configure the Ethernet
 * Controller pulse. An additional set up is required to configure the chip
 * General Purpose I/O (GPIO) to enable the chip output pin.
 *
 * @param adapter pointer to the private structure.
 * @param params output pulse configuration.
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_pth_pulse_out_config(struct al_mod_hal_eth_adapter *adapter,
				struct al_mod_eth_pth_pulse_out_params const *params);

struct al_mod_eth_ec_stats{
	/* Rx Frequency adjust FIFO input  packets */
	uint32_t faf_in_rx_pkt;
	/* Rx Frequency adjust FIFO input  short error packets */
	uint32_t faf_in_rx_short;
	/* Rx Frequency adjust FIFO input  long error packets */
	uint32_t faf_in_rx_long;
	/* Rx Frequency adjust FIFO output  packets */
	uint32_t faf_out_rx_pkt;
	/* Rx Frequency adjust FIFO output  short error packets */
	uint32_t faf_out_rx_short;
	/* Rx Frequency adjust FIFO output  long error packets */
	uint32_t faf_out_rx_long;
	/* Rx Frequency adjust FIFO output  drop packets */
	uint32_t faf_out_drop;
	/* Number of packets written into the Rx FIFO (without FIFO error indication) */
	uint32_t rxf_in_rx_pkt;
	/* Number of error packets written into the Rx FIFO (with FIFO error indication, */
	/* FIFO full indication during packet reception) */
	uint32_t rxf_in_fifo_err;
	/* Number of packets read from Rx FIFO 1 */
	uint32_t lbf_in_rx_pkt;
	/* Number of packets read from Rx FIFO 2 (loopback FIFO) */
	uint32_t lbf_in_fifo_err;
	/* Rx FIFO output drop packets from FIFO 1 */
	uint32_t rxf_out_rx_1_pkt;
	/* Rx FIFO output drop packets from FIFO 2 (loop back) */
	uint32_t rxf_out_rx_2_pkt;
	/* Rx FIFO output drop packets from FIFO 1 */
	uint32_t rxf_out_drop_1_pkt;
	/* Rx FIFO output drop packets from FIFO 2 (loop back) */
	uint32_t rxf_out_drop_2_pkt;
	/* Rx Parser 1, input packet counter */
	uint32_t rpe_1_in_rx_pkt;
	/* Rx Parser 1, output packet counter */
	uint32_t rpe_1_out_rx_pkt;
	/* Rx Parser 2, input packet counter */
	uint32_t rpe_2_in_rx_pkt;
	/* Rx Parser 2, output packet counter */
	uint32_t rpe_2_out_rx_pkt;
	/* Rx Parser 3 (MACsec), input packet counter */
	uint32_t rpe_3_in_rx_pkt;
	/* Rx Parser 3 (MACsec), output packet counter */
	uint32_t rpe_3_out_rx_pkt;
	/* Tx parser, input packet counter */
	uint32_t tpe_in_tx_pkt;
	/* Tx parser, output packet counter */
	uint32_t tpe_out_tx_pkt;
	/* Tx packet modification, input packet counter */
	uint32_t tpm_tx_pkt;
	/* Tx forwarding input packet counter */
	uint32_t tfw_in_tx_pkt;
	/* Tx forwarding input packet counter */
	uint32_t tfw_out_tx_pkt;
	/* Rx forwarding input packet counter */
	uint32_t rfw_in_rx_pkt;
	/* Rx Forwarding, packet with VLAN command drop indication */
	uint32_t rfw_in_vlan_drop;
	/* Rx Forwarding, packets with parse drop indication */
	uint32_t rfw_in_parse_drop;
	/* Rx Forwarding, multicast packets */
	uint32_t rfw_in_mc;
	/* Rx Forwarding, broadcast packets */
	uint32_t rfw_in_bc;
	/* Rx Forwarding, tagged packets */
	uint32_t rfw_in_vlan_exist;
	/* Rx Forwarding, untagged packets */
	uint32_t rfw_in_vlan_nexist;
	/* Rx Forwarding, packets with MAC address drop indication (from the MAC address table) */
	uint32_t rfw_in_mac_drop;
	/* Rx Forwarding, packets with undetected MAC address */
	uint32_t rfw_in_mac_ndet_drop;
	/* Rx Forwarding, packets with drop indication from the control table */
	uint32_t rfw_in_ctrl_drop;
	/* Rx Forwarding, packets with L3_protocol_index drop indication */
	uint32_t rfw_in_prot_i_drop;
	/* EEE, number of times the system went into EEE state */
	uint32_t eee_in;
};

/**
 * get ec statistics
 * @param adapter pointer to the private structure.
 * @param stats pointer to structure that will be filled with statistics.
 *
 * @return return 0 on success. otherwise on failure.
 */
int al_mod_eth_ec_stats_get(struct al_mod_hal_eth_adapter *adapter, struct al_mod_eth_ec_stats *stats);

struct al_mod_eth_ec_stat_udma{
	/* Rx forwarding output packet counter */
	uint32_t rfw_out_rx_pkt;
	/* Rx forwarding output drop packet counter */
	uint32_t rfw_out_drop;
	/* Multi-stream write, number of Rx packets */
	uint32_t msw_in_rx_pkt;
	/* Multi-stream write, number of dropped packets at SOP,  Q full indication */
	uint32_t msw_drop_q_full;
	/* Multi-stream write, number of dropped packets at SOP */
	uint32_t msw_drop_sop;
	/* Multi-stream write, number of dropped packets at EOP, */
	/*EOP was written with error indication (not all packet data was written) */
	uint32_t msw_drop_eop;
	/* Multi-stream write, number of packets written to the stream FIFO with EOP and without packet loss */
	uint32_t msw_wr_eop;
	/* Multi-stream write, number of packets read from the FIFO into the stream */
	uint32_t msw_out_rx_pkt;
	/* Number of transmitted packets without TSO enabled */
	uint32_t tso_no_tso_pkt;
	/* Number of transmitted packets with TSO enabled */
	uint32_t tso_tso_pkt;
	/* Number of TSO segments that were generated */
	uint32_t tso_seg_pkt;
	/* Number of TSO segments that required padding */
	uint32_t tso_pad_pkt;
	/* Tx Packet modification, MAC SA spoof error */
	uint32_t tpm_tx_spoof;
	/* Tx MAC interface, input packet counter */
	uint32_t tmi_in_tx_pkt;
	/* Tx MAC interface, number of packets forwarded to the MAC */
	uint32_t tmi_out_to_mac;
	/* Tx MAC interface, number of packets forwarded to the Rx data path */
	uint32_t tmi_out_to_rx;
	/* Tx MAC interface, number of transmitted bytes */
	uint32_t tx_q0_bytes;
	/* Tx MAC interface, number of transmitted bytes */
	uint32_t tx_q1_bytes;
	/* Tx MAC interface, number of transmitted bytes */
	uint32_t tx_q2_bytes;
	/* Tx MAC interface, number of transmitted bytes */
	uint32_t tx_q3_bytes;
	/*
	 * Tx MAC interface, number of transmitted bytes per queue
	 * valid for eth rev 4, in that case - other bytes counters in this struct
	 * are not relevant
	 */
	uint32_t tx_q_bytes[AL_ETH_UDMA_HW_QUEUES_MAX];
	/* Tx MAC interface, number of transmitted packets */
	uint32_t tx_q0_pkts;
	/* Tx MAC interface, number of transmitted packets */
	uint32_t tx_q1_pkts;
	/* Tx MAC interface, number of transmitted packets */
	uint32_t tx_q2_pkts;
	/* Tx MAC interface, number of transmitted packets */
	uint32_t tx_q3_pkts;
	/*
	 * Tx MAC interface, number of transmitted packets per queue
	 * valid for eth rev 4, in that case - other bytes counters in this struct
	 * are not relevant
	 */
	uint32_t tx_q_pkts[AL_ETH_UDMA_HW_QUEUES_MAX];
};

/**
 * get per_udma statistics
 * @param adapter pointer to the private structure.
 * @param idx udma_id value
 * @param stats pointer to structure that will be filled with statistics.
 *
 * @return return 0 on success. otherwise on failure.
 */
int al_mod_eth_ec_stat_udma_get(struct al_mod_hal_eth_adapter *adapter, uint8_t idx, struct al_mod_eth_ec_stat_udma *stats);

/* trafic control */

/**
 * perform Function Level Reset RMN
 *
 * Addressing RMN: 714
 *
 * @param pci_read_config_u32 pointer to function that reads register from pci header
 * @param pci_write_config_u32 pointer to function that writes register from pci header
 * @param handle pointer passes to the above functions as first parameter
 * @param mac_base base address of the MAC registers
 *
 * @return 0.
 */
int al_mod_eth_flr_rmn(int (* pci_read_config_u32)(void *handle, int where, uint32_t *val),
		   int (* pci_write_config_u32)(void *handle, int where, uint32_t val),
		   void *handle,
		   void __iomem	*mac_base);

/**
 * perform Function Level Reset RMN but restore registers that contain board specific data
 *
 * the data that save and restored is the board params and mac addresses
 *
 * @param pci_read_config_u32 pointer to function that reads register from pci header
 * @param pci_write_config_u32 pointer to function that writes register from pci header
 * @param handle pointer passes to the above functions as first parameter
 * @param mac_base base address of the MAC registers
 * @param ec_base base address of the Ethernet Controller registers
 * @param mac_addresses_num number of mac addresses to restore
 *
 * @return 0.
 */
int al_mod_eth_flr_rmn_restore_params(int (* pci_read_config_u32)(void *handle, int where, uint32_t *val),
		int (* pci_write_config_u32)(void *handle, int where, uint32_t val),
		void *handle,
		void __iomem	*mac_base,
		void __iomem	*ec_base,
		int	mac_addresses_num);

/** FLR type */
enum al_mod_eth_flr_type {
	/** Full FLR, including all UDMAs, EC, MAC, shared resources */
	AL_ETH_FLR_TYPE_FULL,
	/** Port FLR, including all port UDMAs, EC, MAC */
	AL_ETH_FLR_TYPE_PORT,
	/** Specific UDMA FLR */
	AL_ETH_FLR_TYPE_UDMA,
	/** Specific UDMA Queues */
	AL_ETH_FLR_TYPE_UDMA_QUEUES,
	/** FLR all UDMAs at once (can be done from any port) */
	AL_ETH_FLR_TYPE_ALL_UDMAS,
	/** Partial FLR, including all port UDMAs and EC (no MAC) */
	AL_ETH_FLR_TYPE_UDMA_EC,
};

/** FLR parameters */
#define AL_ETH_HAS_FLR_PARAMS
struct al_mod_eth_flr_params {
	/** pointer to function that reads register from pci header */
	int (*pci_read_config_u32)(void *handle, int where, uint32_t *val);
	/** pointer to function that writes register from pci header */
	int (*pci_write_config_u32)(void *handle, int where, uint32_t val);
	/** pointer passes to the above functions as first parameter */
	void				*handle;
	/** FLR type */
	enum al_mod_eth_flr_type		type;
	/** UDMA number - relevant if type is AL_ETH_FLR_TYPE_UDMA or AL_ETH_FLR_TYPE_UDMA_QUEUES*/
	unsigned int			udma_num;
	/** ETH port idx - relevant for type AL_ETH_FLR_TYPE_ALL_UDMAS to know
	 *  from which adapter the FLR is being triggered.
	 */
	unsigned int			port_idx;
};

/**
 * Ethernet unit FLR
 *
 * @param	adapter
 *		Ethernet unit object
 * @param	params
 *		FLR params
 */
void al_mod_eth_flr(
	struct al_mod_hal_eth_adapter	*adapter,
	struct al_mod_eth_flr_params	*params);

/* board specific information (media type, phy address, etc.. */

#define AL_ETH_BOARD_MEDIA_TYPE_HAS_100G
enum al_mod_eth_board_media_type {
	AL_ETH_BOARD_MEDIA_TYPE_AUTO_DETECT		= 0,
	AL_ETH_BOARD_MEDIA_TYPE_RGMII			= 1,
	AL_ETH_BOARD_MEDIA_TYPE_10GBASE_SR		= 2,
	AL_ETH_BOARD_MEDIA_TYPE_SGMII			= 3,
	AL_ETH_BOARD_MEDIA_TYPE_1000BASE_X		= 4,
	AL_ETH_BOARD_MEDIA_TYPE_AUTO_DETECT_AUTO_SPEED	= 5,
	AL_ETH_BOARD_MEDIA_TYPE_SGMII_2_5G		= 6,
	AL_ETH_BOARD_MEDIA_TYPE_NBASE_T			= 7,
	AL_ETH_BOARD_MEDIA_TYPE_25G			= 8,
	AL_ETH_BOARD_MEDIA_TYPE_25G_10G_AUTO		= 9,
	AL_ETH_BOARD_MEDIA_TYPE_40G			= 10,
	AL_ETH_BOARD_MEDIA_TYPE_100G			= 11,
};

enum al_mod_eth_board_mdio_freq {
	AL_ETH_BOARD_MDIO_FREQ_2_5_MHZ	= 0,
	AL_ETH_BOARD_MDIO_FREQ_1_MHZ	= 1,
};

enum al_mod_eth_board_ext_phy_if {
	AL_ETH_BOARD_PHY_IF_MDIO	= 0,
	AL_ETH_BOARD_PHY_IF_XMDIO	= 1,
	AL_ETH_BOARD_PHY_IF_I2C		= 2,

};

enum al_mod_eth_board_auto_neg_mode {
	AL_ETH_BOARD_AUTONEG_OUT_OF_BAND	= 0,
	AL_ETH_BOARD_AUTONEG_IN_BAND		= 1,

};

/* declare the 1G mac active speed when auto negotiation disabled */
enum al_mod_eth_board_1g_speed {
	AL_ETH_BOARD_1G_SPEED_1000M		= 0,
	AL_ETH_BOARD_1G_SPEED_100M		= 1,
	AL_ETH_BOARD_1G_SPEED_10M		= 2,
};

enum al_mod_eth_retimer_channel {
	AL_ETH_RETIMER_CHANNEL_A		= 0,
	AL_ETH_RETIMER_CHANNEL_B		= 1,
	AL_ETH_RETIMER_CHANNEL_C		= 2,
	AL_ETH_RETIMER_CHANNEL_D		= 3,
	AL_ETH_RETIMER_CHANNEL_E		= 4,
	AL_ETH_RETIMER_CHANNEL_F		= 5,
	AL_ETH_RETIMER_CHANNEL_G		= 6,
	AL_ETH_RETIMER_CHANNEL_H		= 7,
	AL_ETH_RETIMER_CHANNEL_MAX		= 8
};

/* list of supported retimers */
enum al_mod_eth_retimer_type {
	AL_ETH_RETIMER_BR_210			= 0,
	AL_ETH_RETIMER_BR_410			= 1,
	AL_ETH_RETIMER_DS_25			= 2,

	AL_ETH_RETIMER_TYPE_MAX			= 4,
};

/** structure represents the board information. this info set by boot loader
 * and read by OS driver.
 */
struct al_mod_eth_board_params {
	enum al_mod_eth_board_media_type	media_type;
	al_mod_bool		phy_exist; /**< external phy exist */
	uint8_t		phy_mdio_addr; /**< mdio address of external phy */
	al_mod_bool		sfp_plus_module_exist; /**< SFP+ module connected */
	al_mod_bool		autoneg_enable; /**< enable Auto-Negotiation */
	al_mod_bool		kr_lt_enable; /**< enable KR Link-Training */
	al_mod_bool		kr_fec_enable; /**< enable KR FEC */
	enum al_mod_eth_board_mdio_freq	mdio_freq; /**< MDIO frequency */
	uint8_t		i2c_adapter_id; /**< identifier for the i2c adapter to use to access SFP+ module */
	enum al_mod_eth_board_ext_phy_if	phy_if; /**< phy interface */
	enum al_mod_eth_board_auto_neg_mode	an_mode; /**< auto-negotiation mode (in-band / out-of-band) */
	uint8_t		serdes_grp; /**< serdes's group id */
	uint8_t		serdes_lane; /**< serdes's lane id */
	enum al_mod_eth_ref_clk_freq	ref_clk_freq; /**< reference clock frequency */
	al_mod_bool		dont_override_serdes; /**< prevent override serdes parameters */
	al_mod_bool		force_1000_base_x; /**< set mac to 1000 base-x mode (instead sgmii) */
	al_mod_bool		an_disable; /**< disable auto negotiation */
	enum al_mod_eth_board_1g_speed	speed; /**< port speed if AN disabled */
	al_mod_bool		half_duplex; /**< force half duplex if AN disabled */
	al_mod_bool		fc_disable; /**< disable flow control */
	al_mod_bool		retimer_exist; /**< retimer is exist on the board */
	uint8_t		retimer_bus_id; /**< in what i2c bus the retimer is on */
	uint8_t		retimer_i2c_addr; /**< i2c address of the retimer */
	enum al_mod_eth_retimer_channel retimer_channel; /**< what channel connected to this port (Rx) */
	al_mod_bool		dac; /**< assume direct attached cable is connected if auto detect is off or failed */
	uint8_t		dac_len; /**< assume this cable length if auto detect is off or failed  */
	enum al_mod_eth_retimer_type retimer_type; /**< the type of the specific retimer */
	enum al_mod_eth_retimer_channel retimer_tx_channel; /**< what channel connected to this port (Tx) */
	uint8_t		gpio_sfp_present; /**< gpio number of sfp present for this port. 0 if not exist */
	al_mod_bool		auto_fec_enable; /**< enable Auto FEC mode */
	uint8_t		gpio_spd_1g; /**< gpio num for 1g speed indication. 0 - N/A */
	uint8_t		gpio_spd_10g; /**< gpio num for 10g speed indication. 0 - N/A */
	uint8_t		gpio_spd_25g; /**< gpio num for 25g speed indication. 0 - N/A */
	enum al_mod_eth_common_mode common_mode;
};

/**
 * set board parameter of the eth (rev 1-3 only) port
 * this function used to set the board parameters into scratchpad
 * registers. those paramters can be read later by OS driver.
 *
 * @param mac_base the virtual address of the mac registers (PCI BAR 2)
 * @param params pointer to structure the includes the paramters
 *
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_board_params_set(void * __iomem mac_base, struct al_mod_eth_board_params *params);

/**
 * get board parameter of the eth (rev 1-3 only) port
 * this function used to get the board parameters from scratchpad
 * registers.
 *
 * @param mac_base the virtual address of the mac registers (PCI BAR 2)
 * @param params pointer to structure where the parameters will be stored.
 *
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_board_params_get(void * __iomem mac_base, struct al_mod_eth_board_params *params);

#define AL_ETH_HAS_BOARD_PARAMS_EX
/**
 * set board parameter of the eth port
 * this function used to set the board parameters into scratchpad
 * registers. those paramters can be read later by OS driver.
 * Must call this after the ethernet handle has been initialized
 * @param adapter pointer to the adapter private structure
 * @param params pointer to structure the includes the paramters
 *
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_board_params_set_ex(struct al_mod_hal_eth_adapter *adapter,
	struct al_mod_eth_board_params *params);

/**
 * get board parameter of the eth port
 * this function used to get the board parameters from scratchpad
 * registers.
 * Must call this after the ethernet handle has been initialized
 * @param adapter pointer to the adapter private structure
 * @param params pointer to structure the includes the paramters
 *
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_board_params_get_ex(struct al_mod_hal_eth_adapter *adapter,
	struct al_mod_eth_board_params *params);

/*
 * Wake-On-Lan (WoL)
 *
 * The following few functions configure the Wake-On-Lan packet detection
 * inside the Integrated Ethernet MAC.
 *
 * There are other alternative ways to set WoL, such using the
 * external 1000Base-T transceiver to set WoL mode.
 *
 * These APIs do not set the system-wide power-state, nor responsible on the
 * transition from Sleep to Normal power state.
 *
 * For system level considerations, please refer to Annapurna Labs Alpine Wiki.
 */
/* Interrupt enable WoL MAC DA Unicast detected  packet */
#define AL_ETH_WOL_INT_UNICAST		AL_BIT(0)
/* Interrupt enable WoL L2 Multicast detected  packet */
#define AL_ETH_WOL_INT_MULTICAST	AL_BIT(1)
/* Interrupt enable WoL L2 Broadcast detected  packet */
#define AL_ETH_WOL_INT_BROADCAST	AL_BIT(2)
/* Interrupt enable WoL IPv4 detected  packet */
#define AL_ETH_WOL_INT_IPV4		AL_BIT(3)
/* Interrupt enable WoL IPv6 detected  packet */
#define AL_ETH_WOL_INT_IPV6		AL_BIT(4)
/* Interrupt enable WoL EtherType+MAC DA detected  packet */
#define AL_ETH_WOL_INT_ETHERTYPE_DA	AL_BIT(5)
/* Interrupt enable WoL EtherType+L2 Broadcast detected  packet */
#define AL_ETH_WOL_INT_ETHERTYPE_BC	AL_BIT(6)
/* Interrupt enable WoL parser detected  packet */
#define AL_ETH_WOL_INT_PARSER		AL_BIT(7)
/* Interrupt enable WoL magic detected  packet */
#define AL_ETH_WOL_INT_MAGIC		AL_BIT(8)
/* Interrupt enable WoL magic+password detected  packet */
#define AL_ETH_WOL_INT_MAGIC_PSWD	AL_BIT(9)

/* Forward enable WoL MAC DA Unicast detected  packet */
#define AL_ETH_WOL_FWRD_UNICAST		AL_BIT(0)
/* Forward enable WoL L2 Multicast detected  packet */
#define AL_ETH_WOL_FWRD_MULTICAST	AL_BIT(1)
/* Forward enable WoL L2 Broadcast detected  packet */
#define AL_ETH_WOL_FWRD_BROADCAST	AL_BIT(2)
/* Forward enable WoL IPv4 detected  packet */
#define AL_ETH_WOL_FWRD_IPV4		AL_BIT(3)
/* Forward enable WoL IPv6 detected  packet */
#define AL_ETH_WOL_FWRD_IPV6		AL_BIT(4)
/* Forward enable WoL EtherType+MAC DA detected  packet */
#define AL_ETH_WOL_FWRD_ETHERTYPE_DA	AL_BIT(5)
/* Forward enable WoL EtherType+L2 Broadcast detected  packet */
#define AL_ETH_WOL_FWRD_ETHERTYPE_BC	AL_BIT(6)
/* Forward enable WoL parser detected  packet */
#define AL_ETH_WOL_FWRD_PARSER		AL_BIT(7)

struct al_mod_eth_wol_params {
	uint8_t *dest_addr; /**< 6 bytes array of destanation address for
				 magic packet detection */
	uint8_t *pswd; /**< 6 bytes array of the password to use */
	uint8_t *ipv4; /**< 4 bytes array of the ipv4 to use.
			    example: for ip = 192.168.1.2
			       ipv4[0]=2, ipv4[1]=1, ipv4[2]=168, ipv4[3]=192 */
	uint8_t *ipv6; /** 16 bytes array of the ipv6 to use.
			   example: ip = 2607:f0d0:1002:0051:0000:0000:5231:1234
			       ipv6[0]=34, ipv6[1]=12, ipv6[2]=31 .. */
	uint16_t ethr_type1; /**< first ethertype to use */
	uint16_t ethr_type2; /**< secound ethertype to use */
	uint16_t forward_mask; /**< bitmask of AL_ETH_WOL_FWRD_* of the packet
				    types needed to be forward. */
	uint16_t int_mask; /**< bitmask of AL_ETH_WOL_INT_* of the packet types
				that will send interrupt to wake the system. */
};

/**
 * enable the wol mechanism
 * set what type of packets will wake up the system and what type of packets
 * neet to forward after the system is up
 *
 * beside this function wol filter also need to be set by
 * calling al_mod_eth_filter_config with AL_ETH_RFW_FILTER_WOL
 *
 * @param adapter pointer to the private structure
 * @param wol the parameters needed to configure the wol
 *
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_wol_enable(
		struct al_mod_hal_eth_adapter *adapter,
		struct al_mod_eth_wol_params *wol);

/**
 * Disable the WoL mechnism.
 *
 * @param adapter pointer to the private structure
 *
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_wol_disable(
		struct al_mod_hal_eth_adapter *adapter);

/**
 * Configure tx fwd vlan table entry
 *
 * @param adapter pointer to the private structure
 * @param idx the entry index within the vlan table. The HW uses the vlan id
 * field of the packet when accessing this table.
 * @param udma_mask vlan table value that indicates that the packet should be forward back to
 * the udmas, through the Rx path (udma_mask is one-hot representation)
 * @param fwd_to_mac vlan table value that indicates that the packet should be forward to mac
 *
 * @return 0 on success. otherwise on failure.
 */
int al_mod_eth_tx_fwd_vid_table_set(struct al_mod_hal_eth_adapter *adapter, uint32_t idx, uint8_t udma_mask, al_mod_bool fwd_to_mac);

#define AL_ETH_CRC_ENGINE_V3_MAX	1
#define AL_ETH_CRC_ENGINE_V4_MAX	4
#define AL_ETH_CRC_ENGINE_MAX		AL_ETH_CRC_ENGINE_V4_MAX

#define AL_ETH_TX_GPD_TABLE_SIZE	32
/** Tx Generic protocol detect Cam compare table entry  */
struct al_mod_eth_tx_gpd_cam_entry {
	enum AL_ETH_PROTO_ID l3_proto_idx;
	enum AL_ETH_PROTO_ID l4_proto_idx;
	enum AL_ETH_TX_TUNNEL_MODE tunnel_control;
	uint8_t source_vlan_count:2;
	uint8_t tx_gpd_cam_ctrl:1;
	uint8_t l3_proto_idx_mask:5;
	uint8_t l4_proto_idx_mask:5;
	uint8_t tunnel_control_mask:3;
	uint8_t source_vlan_count_mask:2;
};

#define AL_ETH_RX_GPD_TABLE_SIZE	32
/** Rx Generic protocol detect Cam compare table entry  */
struct al_mod_eth_rx_gpd_cam_entry {
	enum AL_ETH_PROTO_ID outer_l3_proto_idx;
	enum AL_ETH_PROTO_ID outer_l4_proto_idx;
	enum AL_ETH_PROTO_ID inner_l3_proto_idx;
	enum AL_ETH_PROTO_ID inner_l4_proto_idx;
	uint8_t parse_ctrl;
	uint8_t outer_l3_len;
	uint8_t l3_priority;
	uint8_t l4_dst_port_lsb;
	uint8_t rx_gpd_cam_ctrl:1;
	uint8_t outer_l3_proto_idx_mask:5;
	uint8_t outer_l4_proto_idx_mask:5;
	uint8_t inner_l3_proto_idx_mask:5;
	uint8_t inner_l4_proto_idx_mask:5;
	uint8_t parse_ctrl_mask;
	uint8_t outer_l3_len_mask;
	uint8_t l3_priority_mask;
	uint8_t l4_dst_port_lsb_mask;
};

enum AL_ETH_TX_GCP_ALU_OPSEL {
	AL_ETH_TX_GCP_ALU_L3_OFFSET			= 0,
	AL_ETH_TX_GCP_ALU_OUTER_L3_OFFSET		= 1,
	AL_ETH_TX_GCP_ALU_L3_LEN			= 2,
	AL_ETH_TX_GCP_ALU_OUTER_L3_LEN			= 3,
	AL_ETH_TX_GCP_ALU_L4_OFFSET			= 4,
	AL_ETH_TX_GCP_ALU_L4_LEN			= 5,
	AL_ETH_TX_GCP_ALU_TABLE_VAL			= 10
};

enum AL_ETH_RX_GCP_ALU_OPSEL {
	AL_ETH_RX_GCP_ALU_OUTER_L3_OFFSET		= 0,
	AL_ETH_RX_GCP_ALU_INNER_L3_OFFSET		= 1,
	AL_ETH_RX_GCP_ALU_OUTER_L4_OFFSET		= 2,
	AL_ETH_RX_GCP_ALU_INNER_L4_OFFSET		= 3,
	AL_ETH_RX_GCP_ALU_OUTER_L3_HDR_LEN_LAT		= 4,
	AL_ETH_RX_GCP_ALU_INNER_L3_HDR_LEN_LAT		= 5,
	AL_ETH_RX_GCP_ALU_OUTER_L3_HDR_LEN_SEL		= 6,
	AL_ETH_RX_GCP_ALU_INNER_L3_HDR_LEN_SEL		= 7,
	AL_ETH_RX_GCP_ALU_PARSE_RESULT_VECTOR_OFFSET_1	= 8,
	AL_ETH_RX_GCP_ALU_PARSE_RESULT_VECTOR_OFFSET_2	= 9,
	AL_ETH_RX_GCP_ALU_TABLE_VAL			= 10,
	/** ETHv4 extension */
	AL_ETH_RX_GCP_ALU_V4_CONST_VAL_0		= 10,
	AL_ETH_RX_GCP_ALU_V4_CONST_VAL_1		= 11,
	AL_ETH_RX_GCP_ALU_V4_CONST_VAL_2		= 12,
	AL_ETH_RX_GCP_ALU_V4_CONST_VAL_3		= 13,
	AL_ETH_RX_GCP_ALU_V4_ZEROS			= 14,
	AL_ETH_RX_GCP_ALU_V4_TABLE_VAL			= 15
};

#define AL_ETH_TX_GCP_TABLE_SIZE	32
/** Tx Generic crc prameters table entry  */

struct al_mod_eth_tx_gcp_table_entry {
	uint8_t poly_sel:1;
	uint8_t crc32_bit_comp:1;
	uint8_t crc32_bit_swap:1;
	uint8_t crc32_byte_swap:1;
	uint8_t data_bit_swap:1;
	uint8_t data_byte_swap:1;
	uint8_t trail_size:8;
	uint8_t head_size:8;
	uint8_t head_calc:1;
	uint8_t mask_polarity:1;
	enum AL_ETH_ALU_OPCODE tx_alu_opcode_1;
	enum AL_ETH_ALU_OPCODE tx_alu_opcode_2;
	enum AL_ETH_ALU_OPCODE tx_alu_opcode_3;
	enum AL_ETH_TX_GCP_ALU_OPSEL tx_alu_opsel_1;
	enum AL_ETH_TX_GCP_ALU_OPSEL tx_alu_opsel_2;
	enum AL_ETH_TX_GCP_ALU_OPSEL tx_alu_opsel_3;
	enum AL_ETH_TX_GCP_ALU_OPSEL tx_alu_opsel_4;
	uint32_t gcp_mask[6];
	uint32_t crc_init;
	uint8_t gcp_table_res:7;
	uint16_t alu_val:9;

	/** ETHv4 extension */
	uint32_t ext[6];
};

#define AL_ETH_RX_GCP_TABLE_SIZE	32
/** Rx Generic crc prameters table entry  */

struct al_mod_eth_rx_gcp_table_entry {
	uint8_t poly_sel:1;
	uint8_t crc32_bit_comp:1;
	uint8_t crc32_bit_swap:1;
	uint8_t crc32_byte_swap:1;
	uint8_t data_bit_swap:1;
	uint8_t data_byte_swap:1;
	uint8_t trail_size:8;
	uint8_t head_size:8;
	uint8_t head_calc:1;
	uint8_t mask_polarity:1;
	enum AL_ETH_ALU_OPCODE rx_alu_opcode_1;
	enum AL_ETH_ALU_OPCODE rx_alu_opcode_2;
	enum AL_ETH_ALU_OPCODE rx_alu_opcode_3;
	enum AL_ETH_RX_GCP_ALU_OPSEL rx_alu_opsel_1;
	enum AL_ETH_RX_GCP_ALU_OPSEL rx_alu_opsel_2;
	enum AL_ETH_RX_GCP_ALU_OPSEL rx_alu_opsel_3;
	enum AL_ETH_RX_GCP_ALU_OPSEL rx_alu_opsel_4;
	uint32_t gcp_mask[6];
	uint32_t crc_init;
	uint32_t gcp_table_res:27;
	uint16_t alu_val:9;

	/** ETHv4 extension */
	uint8_t poly_sel_ext:2;
	uint8_t crc_cks_sel:1;
	uint8_t trail_calc:1;
	enum AL_ETH_RX_GCP_ALU_OPSEL rx_trail_alu_opsel_1;
	enum AL_ETH_RX_GCP_ALU_OPSEL rx_trail_alu_opsel_2;
	enum AL_ETH_RX_GCP_ALU_OPSEL rx_trail_alu_opsel_3;
	enum AL_ETH_RX_GCP_ALU_OPSEL rx_trail_alu_opsel_4;
	uint8_t head_size_ext:8;
	uint8_t crc_field_size:6;
	uint8_t crc_field_offset_calc:1;
	uint16_t crc_field_offset:16;
	uint32_t crc_check_value:32;
	uint32_t crc_replace_value:32;
	uint32_t crc_detect_value:32;
	enum AL_ETH_ALU_OPCODE rx_trail_alu_opcode_1;
	enum AL_ETH_ALU_OPCODE rx_trail_alu_opcode_2;
	enum AL_ETH_ALU_OPCODE rx_trail_alu_opcode_3;
	uint8_t crc_replace_sel:1;
	uint8_t crc_detect_sel:1;
};

/* The actual HW table is 128 entries, but the SW struct updates 4 HW entries at once
 * so this macro is defined to be 32 */
#define AL_ETH_TX_CRC_CSUM_REPLACE_SW_TABLE_SIZE	32
/** Tx per_protocol_number crc & l3_checksum & l4_checksum command table entry  */

struct al_mod_eth_tx_crc_chksum_replace_cmd_for_protocol_num_entry {
        al_mod_bool crc_en_00; /*from Tx_buffer_descriptor: enable_l4_checksum is 0 ,enable_l3_checksum is 0 */
        al_mod_bool crc_en_01; /*from Tx_buffer_descriptor: enable_l4_checksum is 0 ,enable_l3_checksum is 1 */
        al_mod_bool crc_en_10; /*from Tx_buffer_descriptor: enable_l4_checksum is 1 ,enable_l3_checksum is 0 */
        al_mod_bool crc_en_11; /*from Tx_buffer_descriptor: enable_l4_checksum is 1 ,enable_l3_checksum is 1 */
        al_mod_bool l4_csum_en_00; /*from Tx_buffer_descriptor: enable_l4_checksum is 0 ,enable_l3_checksum is 0 */
        al_mod_bool l4_csum_en_01; /*from Tx_buffer_descriptor: enable_l4_checksum is 0 ,enable_l3_checksum is 1 */
        al_mod_bool l4_csum_en_10; /*from Tx_buffer_descriptor: enable_l4_checksum is 1 ,enable_l3_checksum is 0 */
        al_mod_bool l4_csum_en_11; /*from Tx_buffer_descriptor: enable_l4_checksum is 1 ,enable_l3_checksum is 1 */
        al_mod_bool l3_csum_en_00; /*from Tx_buffer_descriptor: enable_l4_checksum is 0 ,enable_l3_checksum is 0 */
        al_mod_bool l3_csum_en_01; /*from Tx_buffer_descriptor: enable_l4_checksum is 0 ,enable_l3_checksum is 1 */
        al_mod_bool l3_csum_en_10; /*from Tx_buffer_descriptor: enable_l4_checksum is 1 ,enable_l3_checksum is 0 */
        al_mod_bool l3_csum_en_11; /*from Tx_buffer_descriptor: enable_l4_checksum is 1 ,enable_l3_checksum is 1 */
};

/**
 * The following macros represent the number of existing entries in the CRC tables'
 * initialization arrays (excluding the default entry which is at the end of each table):
 * - TX GPD, GCP and CRC_CSUM_REPLACE
 * - RX GPD and GCP
 * NOTICE: For each direction, all tables have the same number of used entries
 */
#define AL_ETH_TX_GENERIC_CRC_ENTRIES_NUM 0
#define AL_ETH_RX_PROTOCOL_DETECT_ENTRIES_NUM 12

/**
 * Configure tx_gpd_entry
 *
 * @param adapter pointer to the private structure
 * @param idx the entry index
 * @param tx_gpd_entry entry data for the Tx protocol detect Cam compare table
 *
 * @return 0 on success. otherwise on failure.
 *
 * @note if the table was initialized with al_mod_eth_tx_protocol_detect_table_init(), then new entries
 *       should be added starting from AL_ETH_TX_GENERIC_CRC_ENTRIES_NUM
 *
 */
int al_mod_eth_tx_protocol_detect_table_entry_set(struct al_mod_hal_eth_adapter *adapter, uint32_t idx,
		struct al_mod_eth_tx_gpd_cam_entry *tx_gpd_entry);

/**
 * Read tx_gpd_entry
 *
 * @param adapter pointer to the private structure
 * @param idx the entry index
 * @param tx_gpd_entry pointer to store entry contents from Tx protocol detect Cam compare table
 *
 */
void al_mod_eth_tx_protocol_detect_table_entry_get(struct al_mod_hal_eth_adapter *adapter, uint32_t idx,
					struct al_mod_eth_tx_gpd_cam_entry *tx_gpd_entry);

/**
 * Configure tx_gcp_entry
 *
 * @param adapter pointer to the private structure
 * @param engine_idx CRC engine index (ETHv4)
 * @param idx the entry index
 * @param tx_gcp_entry entry data for the Tx Generic crc prameters table
 *
 * @return 0 on success. otherwise on failure.
 *
 * @note if the table was initialized with al_mod_eth_tx_generic_crc_table_init(), then new entries
 *       should be added starting from AL_ETH_TX_GENERIC_CRC_ENTRIES_NUM
 *
 */
int al_mod_eth_tx_generic_crc_table_entry_set(struct al_mod_hal_eth_adapter *adapter,
		unsigned int engine_idx, uint32_t idx,
		struct al_mod_eth_tx_gcp_table_entry *tx_gcp_entry);

/**
 * Read tx_gcp_entry
 *
 * @param adapter pointer to the private structure
 * @param engine_idx CRC engine index (ETHv4)
 * @param idx the entry index
 * @param tx_gcp_entry pointer to store entry contents from the Tx Generic crc prameters table
 *
 * @return 0 on success. otherwise on failure.
 *
 */
void al_mod_eth_tx_generic_crc_table_entry_get(struct al_mod_hal_eth_adapter *adapter,
		unsigned int engine_idx, uint32_t idx,
		struct al_mod_eth_tx_gcp_table_entry *tx_gcp_entry);

/**
 * Configure tx_crc_chksum_replace_cmd_entry
 *
 * @param adapter pointer to the private structure
 * @param idx the entry index
 * @param tx_replace_entry entry data for the Tx crc_&_l3_checksum_&_l4_checksum replace command table
 *
 * @return 0 on success. otherwise on failure.
 *
 * @note if the table was initialized with al_mod_eth_tx_crc_chksum_replace_cmd_init(), then new entries
 *       should be added starting from AL_ETH_TX_GENERIC_CRC_ENTRIES_NUM
 */
int al_mod_eth_tx_crc_chksum_replace_cmd_entry_set(struct al_mod_hal_eth_adapter *adapter, uint32_t idx,
		struct al_mod_eth_tx_crc_chksum_replace_cmd_for_protocol_num_entry *tx_replace_entry);

/**
 * Read tx_crc_chksum_replace_cmd_entry
 *
 * @param adapter pointer to the private structure
 * @param idx the entry index
 * @param tx_replace_entry pointer to store entry contents from the
 *        Tx crc_&_l3_checksum_&_l4_checksum replace command table
 *
 */
void al_mod_eth_tx_crc_chksum_replace_cmd_entry_get(struct al_mod_hal_eth_adapter *adapter, uint32_t idx,
		struct al_mod_eth_tx_crc_chksum_replace_cmd_for_protocol_num_entry *tx_replace_entry);

/**
 * Configure rx_gpd_entry
 *
 * @param adapter pointer to the private structure
 * @param idx the entry index
 * @param rx_gpd_entry entry data for the Tx protocol detect Cam compare table
 *
 * @return 0 on success. otherwise on failure.
 *
 * @note if the table was initialized with al_mod_eth_rx_protocol_detect_table_init(), then new entries
 *       should be added starting from AL_ETH_RX_PROTOCOL_DETECT_ENTRIES_NUM
 *
 */
int al_mod_eth_rx_protocol_detect_table_entry_set(struct al_mod_hal_eth_adapter *adapter, uint32_t idx,
		struct al_mod_eth_rx_gpd_cam_entry *rx_gpd_entry);

/**
 * Read rx_gpd_entry
 * (Available only for Eth v3)
 *
 * @param adapter pointer to the private structure
 * @param idx the entry index
 * @param rx_gpd_entry entry to store data read from the Rx protocol detect Cam compare table
 *
 */
void al_mod_eth_rx_protocol_detect_table_entry_get(struct al_mod_hal_eth_adapter *adapter, uint32_t idx,
		struct al_mod_eth_rx_gpd_cam_entry *rx_gpd_entry);

/**
 * Configure rx_gcp_entry
 *
 * @param adapter pointer to the private structure
 * @param engine_idx CRC engine index (ETHv4)
 * @param idx the entry index
 * @param rx_gcp_entry entry data for the Tx Generic crc prameters table
 *
 * @return 0 on success. otherwise on failure.
 *
 * @note if the table was initialized with al_mod_eth_rx_generic_crc_table_init(), then new entries
 *       should be added starting from AL_ETH_RX_PROTOCOL_DETECT_ENTRIES_NUM
 *
 */
int al_mod_eth_rx_generic_crc_table_entry_set(struct al_mod_hal_eth_adapter *adapter,
		unsigned int engine_idx, uint32_t idx,
		struct al_mod_eth_rx_gcp_table_entry *rx_gcp_entry);

/**
 * Read rx_gcp_entry
 * (Available only for Eth v3)
 *
 * @param adapter pointer to the private structure
 * @param idx the entry index
 * @param rx_gcp_entry entry to store data read from the Rx Generic crc parameters table
 *
  */
void al_mod_eth_rx_generic_crc_table_entry_get(struct al_mod_hal_eth_adapter *adapter, uint32_t idx,
		struct al_mod_eth_rx_gcp_table_entry *rx_gcp_entry);

/**
 * Configure default tx_gpd_table and regs
 *
 * @param adapter pointer to the private structure
 *
 */
int al_mod_eth_tx_protocol_detect_table_init(struct al_mod_hal_eth_adapter *adapter);

/**
 * Configure user tx_gpd_table and regs
 *
 * @param adapter pointer to the private structure
 * @param entries pointer to the tx_gpd table
 * @param num_entries number of the table entries
 *
 */
int al_mod_eth_tx_protocol_detect_table_init_ex(struct al_mod_hal_eth_adapter *adapter,
					struct al_mod_eth_tx_gpd_cam_entry *entries,
					unsigned int num_entries);

/**
 * Configure user rx_gpd_table and regs
 *
 * @param adapter pointer to the private structure
 * @param entries pointer to the rx_gpd_table
 * @param num_entries number of the table entries
 *
 */
int al_mod_eth_rx_protocol_detect_table_init_ex(struct al_mod_hal_eth_adapter *adapter,
					struct al_mod_eth_rx_gpd_cam_entry *entries,
					unsigned int num_entries);

/**
 * Configure crc_chksum_replace_cmd_table
 *
 * @param adapter pointer to the private structure
 *
 */
int al_mod_eth_tx_crc_chksum_replace_cmd_init(struct al_mod_hal_eth_adapter *adapter);

/**
 * Configure crc_chksum_replace_cmd_table
 *
 * @param adapter pointer to the private structure
 * @param entries pointer to the private replace cmd table
 * @param num_entries number of the table entries
 *
 */
int al_mod_eth_tx_crc_chksum_replace_cmd_init_ex(struct al_mod_hal_eth_adapter *adapter,
			struct al_mod_eth_tx_crc_chksum_replace_cmd_for_protocol_num_entry *entries,
			unsigned int num_entries);

/**
 * Configure default tx_gcp_table and regs
 *
 * @param adapter pointer to the private structure
 * @param engine_idx CRC engine index (ETHv4)
 *
 */
int al_mod_eth_tx_generic_crc_table_init(struct al_mod_hal_eth_adapter *adapter, unsigned int engine_idx);

/**
 * Configure user tx_gcp_table and regs
 *
 * @param adapter pointer to the private structure
 * @param entries pointer to the tx gcp table
 * @param num_entries number of the table entries
 *
 */
int al_mod_eth_tx_generic_crc_table_init_ex(struct al_mod_hal_eth_adapter *adapter,
					struct al_mod_eth_tx_gcp_table_entry *entries,
					unsigned int num_entries);

/**
 * Configure rx_gpd_table and regs
 *
 * @param adapter pointer to the private structure
 *
 */
int al_mod_eth_rx_protocol_detect_table_init(struct al_mod_hal_eth_adapter *adapter);

/**
 * Configure default rx_gcp_table and regs
 *
 * @param adapter pointer to the private structure
 * @param engine_idx CRC engine index (ETHv4)
 *
 */
int al_mod_eth_rx_generic_crc_table_init(struct al_mod_hal_eth_adapter *adapter, unsigned int engine_idx);

/**
 * Configure user rx_gcp_table and regs
 *
 * @param adapter pointer to the private structure
 * @param entries pointer to the rx_gcp_table
 * @param num_entries number of the table entries
 *
 */
int al_mod_eth_rx_generic_crc_table_init_ex(struct al_mod_hal_eth_adapter *adapter,
					struct al_mod_eth_rx_gcp_table_entry *entries,
					unsigned int num_entries);

/**
 * Configure rx_gcp_shared_table and regs
 *
 * @param adapter pointer to the private structure
 *
 */
int al_mod_eth_rx_generic_crc_shared_table_init(struct al_mod_hal_eth_adapter *adapter);

/**
 * Configure tx_gcp_shared_table and regs
 *
 * @param adapter pointer to the private structure
 *
 */
int al_mod_eth_tx_generic_crc_shared_table_init(struct al_mod_hal_eth_adapter *adapter);

/**
 * Enable/Disable HW calculated CRC and Checksum insertion into TX packets
 *
 * @param adapter pointer to the private structure
 * @param crc_ins_en enable crc insertion into packet
 * @param cks_ins_en enable checksum insertion into packets
 *
 */
void al_mod_eth_tx_crce_pub_crc_cks_ins_set(struct al_mod_hal_eth_adapter *adapter,
					   al_mod_bool crc_ins_en,
					   al_mod_bool cks_ins_en);

/* Ethernet Unit info of register base address */
struct al_mod_eth_unit_regs_info {
	/* UDMA register base address */
	void __iomem *udma_regs_base;
	/* MAC register base address */
	void __iomem *mac_regs_base;
	/* EC register base address */
	void __iomem *ec_regs_base;
};

void al_mod_eth_unit_regs_info_get(void *bars[6],
			       unsigned int dev_id,
			       unsigned int rev_id,
			       struct al_mod_eth_unit_regs_info *unit_info);

/**
 * Ethernet EC iofic pointer
 *
 * @param adapter pointer to the private structure
 *
 * @return pointer to iofic regs
 */
void __iomem *al_mod_eth_ec_iofic_regs_get(
	struct al_mod_hal_eth_adapter *adapter);

/* Get only bits which are valid for the current runtime configuration (i.e.
 * mode-dependant features) */
#define AL_ETH_IOFIC_ATTRS_RUNTIME_CONFIG	(1 << 0)
/* Exclude bits which might become valid at a later stage */
#define AL_ETH_IOFIC_ATTRS_FILTER_TRANSIENT	(1 << 1)
/* Get only bits which should be unmasked by default (fatal error bits) */
#define AL_ETH_IOFIC_ATTRS_FATAL		(1 << 2)

/**
 * Get EC iofic attributes
 * Function will return iofic masks according to given level and flags
 *
 * @param adapter ethernet controller private structure
 * @param level level of iofic (primary / secondary)
 * @param flags bit field of AL_ETH_IOFIC_ATTRS_ values
 * @param ec_a_mask pointer to EC group A mask
 * @param ec_b_mask pointer to EC group B mask
 * @param ec_c_mask pointer to EC group C mask
 * @param ec_d_mask pointer to EC group D mask
 *
 */
int al_mod_eth_ec_iofic_attrs_get(struct al_mod_hal_eth_adapter *adapter,
			      enum al_mod_eth_iofic_level level, int flags,
			      uint32_t *ec_a_mask, uint32_t *ec_b_mask,
			      uint32_t *ec_c_mask, uint32_t *ec_d_mask);

/*
 * Unmask EC/MAC error interrupts.
 * Function will succeed only if minimum amount of packets
 * were transmitted/received before calling it.
 * should be called only on v1/v2/v3
 *
 * @param adapter pointer to the private structure
 *
 * @return 0 on success, -EAGAIN if minimum number of packets didnt
 * passed, otherwise on failure.
 *
 */
int al_mod_eth_error_ints_unmask(struct al_mod_hal_eth_adapter *adapter);

/**
 * Check if EC/MAC errors can be safely collected by polling (by calling helper
 * function like al_mod_err_events_module_collect or by reading IOFICs directly)
 *
 * Function will return AL_TRUE if minimum amount of packets
 * were transmitted/received before calling it, and therefore collecting errors
 * by polling is guaranteed to return valid results
 * should be called only on v1/v2/v3
 *
 * @param adapter pointer to the private structure
 *
 * @return AL_TRUE on success, AL_FALSE if minimum number of packets didn't
 * pass
 *
 */
al_mod_bool al_mod_eth_err_polling_is_avail(struct al_mod_hal_eth_adapter *adapter);

/*
 * Enable/Disable rx_gcp_table
 *
 * @param adapter pointer to the private structure
 * @param enable true to enable the table. false to disable the table.
 *
 */
void al_mod_eth_rx_generic_crc_table_enable(struct al_mod_hal_eth_adapter *adapter, al_mod_bool enable);

/**
 * Dump TSO
 *
 * Dump a line of the TSO metacache and optionally save to an array
 * @param adapter pointer to the private structure
 * @param idx the index of requested line
 * @param arr array of 4 32bit-words
 *
 */
void al_mod_eth_tso_metacahe_line_dump(struct al_mod_hal_eth_adapter *adapter,
	unsigned int idx, uint32_t *arr);

/* Mailbox */
#define AL_ETH_LINK_STATUS_SOURCE_UDMA		0
#define AL_ETH_LINK_STATUS_MESSAGE_VALID_SHIFT	0
#define AL_ETH_LINK_STATUS_MESSAGE_VALID_BIT	(1 << AL_ETH_LINK_STATUS_MESSAGE_VALID_SHIFT)
#define AL_ETH_LINK_STATUS_MESSAGE_DATA_SHIFT	1
#define AL_ETH_LINK_STATUS_MESSAGE_DATA_BIT	(1 << AL_ETH_LINK_STATUS_MESSAGE_DATA_SHIFT)

/**
 * Get link status from UDMA mailbox
 *
 * @param	adapter eth adapter data structure
 */
int al_mod_eth_mailbox_link_status_get(struct al_mod_hal_eth_adapter *adapter);

/**
 * Set link status to UDMA mailbox
 *
 * @param	adapter eth adapter data structure
 * @param	dst_udma_id UDMA destination number to write to
 * @param	status Link status, 1 - Link up, 0 - Link down
 */
void al_mod_eth_mailbox_link_status_set(struct al_mod_hal_eth_adapter *adapter,
				    uint8_t dst_udma_id, al_mod_bool status);

#ifdef __cplusplus
}
#endif
/* *INDENT-ON* */
#endif		/* __AL_HAL_ETH_H__ */
/** @} end of Ethernet group */
