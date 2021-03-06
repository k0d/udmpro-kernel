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
 * @defgroup group_crc_memcpy_api API
 * CRC/memcpy Acceleration Engine HAL driver API
 * @ingroup group_crc_memcpy
 * @{
 * @file   al_hal_ssm_crc_memcpy.h
 */

#ifndef __AL_HAL_SSM_CRC_MEMCPY_H__
#define __AL_HAL_SSM_CRC_MEMCPY_H__

#include "al_hal_common.h"
#include "al_hal_ssm.h"

#define AL_CRC_APP_IOFIC_OFFSET			0x100

/* interrupt controller group A */
#define AL_CRC_APP_INT_A_S2M_TIMEOUT		AL_BIT(0)
#define AL_CRC_APP_INT_A_M2S_TIMEOUT		AL_BIT(1)
#define AL_CRC_APP_INT_A_CMD_DECODE_ERROR	AL_BIT(2)
#define AL_CRC_APP_INT_A_INPUT_LENGTH_ERROR	AL_BIT(3)
#define AL_CRC_APP_INT_A_MEM_SW_ERROR		AL_BIT(4)
#define AL_CRC_APP_INT_A_LENGTH_TOO_BIG		AL_BIT(5)
#define AL_CRC_APP_INT_A_M2S_ERROR		AL_BIT(8)
#define AL_CRC_APP_INT_A_FIFO_ACK_ERROR_0	AL_BIT(9)
#define AL_CRC_APP_INT_A_FIFO_ACK_ERROR_1	AL_BIT(10)
#define AL_CRC_APP_INT_A_FIFO_ACK_ERROR_2	AL_BIT(11)
#define AL_CRC_APP_INT_A_FIFO_ACK_ERROR_3	AL_BIT(12)
#define AL_CRC_APP_INT_A_FIFO_ACK_ERROR_4	AL_BIT(13)
#define AL_CRC_APP_INT_A_FIFO_Q_OVERRUN		AL_BIT(14)
#define AL_CRC_APP_INT_A_SOP_AFTER_SOP		AL_BIT(15)
#define AL_CRC_APP_INT_A_NO_SOP			AL_BIT(16)
#define AL_CRC_APP_INT_A_SOP_WITH_EOP		AL_BIT(17)
#define AL_CRC_APP_INT_A_EOP_AFTER_EOP		AL_BIT(18)

/*
 * Rx (S2M) Descriptors
 */
#define RX_DESC_META			(1<<30)	/* Meta data */
/* Tx (M2S) word1 common Descriptors */
#define TX_DESC_META_OP_MASK		(0x3<<23)
#define TX_DESC_META_OP_SHIFT		(23)

/* Word 1 */
#define TX_DESC_META_CRC_OP_TYPE_EXTENDED_MASK	(0x1<<26) /* CRC/Checksum op type MSB */
#define TX_DESC_META_CRC_OP_TYPE_EXTENDED_SHIFT	(26)

#define TX_DESC_META_CRC_OP_TYPE_MASK	(0x7<<20)/* CRC/Checksum op type mask */
#define TX_DESC_META_CRC_OP_TYPE_SHIFT	(20)
#define TX_DESC_META_CRC_SEND_ORIG	(1<<19) /* send the original data */
#define TX_DESC_META_CRC_ST_CRC_IV	(1<<18) /* store buf crc IV to cache*/
#define TX_DESC_META_CRC_SAVE_IV	(1<<17) /* store crc res in cache */
#define TX_DESC_META_CRC_SEND_CRC	(1<<16) /* send crc resualt */
#define TX_DESC_META_CRC_USE_ST_IV	(1<<15) /* use IV from cache */
#define TX_DESC_META_CRC_VALID		(1<<14) /* Validate crc */

#define TX_DESC_META_CRC_SWAP_MASK	(0xff<<6) /* Swapping */
#define TX_DESC_META_CRC_SWAP_SHIFT	(6)

#define TX_DESC_META_CRC_IDX_MASK	(0x7<<3) /* Cached CRC IV index mask */
#define TX_DESC_META_CRC_IDX_SHIFT	(3)

#define TX_DESC_META_CRC_EXTENDED_IDX_MASK	(0x1<<2) /* Cached CRC IV MSB index */
#define TX_DESC_META_CRC_EXTENDED_IDX_SHIFT	(2)

#define RX_DESC_META_CRC_FIRST_BUF	(1<<1)   /* First buffer in the block */
#define RX_DESC_META_CRC_LAST_BUF	(1<<0)   /* First buffer in the block */
#define TX_DESC_META_CRC_FIRST_BUF	(1<<1)   /* First buffer in the block */
#define TX_DESC_META_CRC_LAST_BUF	(1<<0)   /* First buffer in the block */

/* Tx (M2S) word2 Descriptors -> in XOR  */

/* Tx (M2S) word3 Descriptors -> Out XOR */

#define AL_CRC_CHECKSUM			2

#define RX_COMP_STATUS_MASK		0

/** CRC/checksum operation type according, values according
 * to HW descriptor setting
 */
enum al_crc_checksum_type {
	AL_CRC_CHECKSUM_NULL = 0,
	AL_CRC_CHECKSUM_CRC32 = 1,
	AL_CRC_CHECKSUM_CRC32C = 2,
	AL_CRC_CHECKSUM_CKSM16 = 3,
	AL_CRC_CHECKSUM_CKSM32 = 4,
	AL_CRC_CHECKSUM_CRC16 = 5,
	AL_CRC_CHECKSUM_CKSM32A = 6,
	AL_CRC_CHECKSUM_CRC8 = 7,
	AL_CRC_CHECKSUM_CRC8N = 8,
	AL_CRC_CHECKSUM_CKSM8 = 9,
};

/**
 * CRC/Checksum Operation bit/byte swap
 *
 * bit_swap : bit reversal within every byte.
 * byte_swap: byte reversal within the entire field.
 * bit_swap & byte_swap: can be used for endianity adjustments of SOURCE_DATA,
 * IV and RESULT. Any combination of bit_swap/byte_swap is supported, there are
 * no hardware relevant restrictions.
 *
 * Example:
 *          IV = 0x01234567
 *          IV(bit_swap=0, byte_swap=1) = 0x67452301
 *          IV(bit_swap=1, byte_swap=0) = 0x80C4A2E6
 *          IV(bit_swap=1, byte_swap=1) = 0xE6A2C480
 */
enum al_crcsum_swap_flags {
	IV_BIT_SWAP = AL_BIT(7),
	IV_BYTE_SWAP = AL_BIT(6),
	SRC_BIT_SWAP = AL_BIT(5),
	SRC_BYTE_SWAP = AL_BIT(4),
	RES_BIT_SWAP = AL_BIT(1),
	RES_BYTE_SWAP = AL_BIT(0)
};

/** Memcpy transaction
 */
struct al_memcpy_transaction {
	enum al_ssm_op_flags flags;
	struct al_block src;	/**< In data - scatter gather*/
	struct al_block dst;	/**< Out data - scatter gather*/
	uint32_t tx_descs_count;/* number of tx descriptors created for this */
				/* transaction, this field set by the hal */
};

/** CRC/Checksum transaction
 * In case dst, iv_in, crc_out are not valid, set the al_buf->len to 0
 * When the dst is not empty the src will be copied to the dst and CRC/checksum
 * will be calculated on the fly.
 */
struct al_crc_transaction {
	enum al_crc_checksum_type crcsum_type; /*< CRC type/ Cheksum */
	enum al_ssm_op_flags flags;
	struct al_block src;	/**< In data - scatter gather*/
	struct al_block dst;	/**< Out data - scatter gather*/
	uint32_t tx_descs_count;/* number of tx descriptors created for this */
				/* transaction, this field set by the hal */

	struct al_buf crc_iv_in; /**< CRC IV, if not set will use from cache */
	uint32_t cached_crc_indx;/**< cached CRC index in crypto engine */
	al_bool st_crc_iv;     /**< Store current IV in the IV cache */
	al_bool st_crc_out;      /**< Store CRC result in the IV cached */
	struct al_buf crc_expected; /**< Expected CRC to validate */
	/**
	 * This is provided as a separate al_buf to allow storing the output CRC
	 * in any address space, depending on application. For example, in a
	 * file-system like BTRFS, the CRC is stored in a metadata array
	 */
	struct al_buf crc_out;   /**< Calculated CRC/Checksum buffer */

	/* Enhanced */
	enum al_crcsum_swap_flags swap_flags; /**< Swap fields */
	/**
	 * When xor_valid is TRUE, an additional metadata descriptor is provided
	 * to the engine, with two values: in_xor and res_xor.
	 * These values will be XOR-ed with the IV and Result, respectively.
	 */
	al_bool xor_valid;       /**< valid in and out XOR */
	/**
	 * XORing IV with a constant value (usually 0xFF..F) is used to detect
	 * errors that append zeros to the beginning of the message
	 */
	uint32_t in_xor;         /**< CRC Input XOR */
	/**
	 * XORing Result with a constant value (usually 0xFF..F) is used to
	 * detect errors that append zeros to the end of the message
	 */
	uint32_t res_xor;        /**< CRC Result XOR */
};

/**
 * Send Memcpy transaction to the HW
 *
 * Perform the following steps:
 *  - Calculate the number of needed RX descriptors and check if the RX UDMA
 *    have available space.
 *  - Do the same for TX descriptors.
 *  - Prepare the RX descriptors.
 *  - Update the tail pointer of the submission ring of the RX UDMA about the
 *    new prepared descriptors.
 *  - Prepare the TX descriptors.
 *
 * Note: A given UDMA queue can be used either for crypto/authentication
 * transactions or for crc/csum/memcpy transactions, but not for both types.
 *
 * @param dma crypto DMA handle
 * @param qid queue index
 * @param xaction transaction context
 *
 * @return 0 if no error found.
 *	   <0 otherwise.
 */
int al_memcpy_prepare(struct al_ssm_dma *dma, uint32_t qid,
			     struct al_memcpy_transaction *xaction);

/**
 * Send CRC/Checksum transaction to the HW
 *
 * Perform the following steps:
 *  - Calculate the number of needed RX descriptors and check if the RX UDMA
 *   have available space.
 *   The number of descriptors depends on which buffers are passed in
 *   the transaction (crc_out) and the number of dest buffers.
 *  - Do the same for TX descriptors. The number of descriptors depends on
 *   which buffers are passed in the transaction (crc_iv_in, crc_expected) and
 *   the number of source buffers.
 *  - Prepare the RX descriptors.
 *  - Update the tail pointer of the submission ring of the RX UDMA
 *   about the new prepared descriptors.
 *  - Prepare the TX descriptors.
 *
 * Note: A given UDMA queue can be used either for crypto/authentication
 * transactions or for crc/csum/memcpy transactions, but not for both types.
 *
 * @param dma crypto DMA handle
 * @param qid queue index
 * @param xaction transaction context
 *
 * @return 0 if no error found.
 *	   -ENOSPC if no space available.
 */
int al_crc_csum_prepare(struct al_ssm_dma *dma, uint32_t qid,
			       struct al_crc_transaction *xaction);

/**
 * Start asynchronous execution of crypto/auth or CRC/Checksum transaction
 *
 * Update the tail pointer of the submission ring of the TX UDMA about
 * previously prepared descriptors.
 * This function could return before the hardware start the work as its an
 * asynchronous non-blocking call to the hardware.
 *
 * @param dma crypto DMA handle
 * @param qid queue index
 * @param tx_descs number of tx descriptors to be processed by the engine
 *
 * @return 0 if no error found.
 *	   -EINVAL if quid is out of range
 */
int al_crc_memcpy_dma_action(struct al_ssm_dma *dma, uint32_t qid,
			 int tx_descs);

/**
 * Check and cleanup completed transaction
 *
 *  when the upper layer decides to check for completed transaction
 *  (e.g. due to interrupt) it calls al_crypto_dma_completion()
 *  API function provided by this driver. this function will call helper
 *  function provided by the m2m_udma module to check for completed requests.
 *  The al_crypto_dma_completion() is responsible for the cleanup of the
 *  completed request from the completion ring, so upper layer don't need to
 *  worry about the queues management.
 *  This driver doesn't provide the upper layer which transaction was
 *  completed, the upper layer should find this information by itself relying
 *  on the fact that for a given queue, the transaction completed in the same
 *  order it was sent to the same queue, no ordering is guaranteed between
 *  transaction that sent to different queues.

 * @param dma crypto DMA handle
 * @param qid queue index
 * @param comp_status status reported by rx completion descriptor
 *
 * @return the number of completed transactions.
 */
int al_crc_memcpy_dma_completion(struct al_ssm_dma *dma,
			     uint32_t qid,
			     uint32_t *comp_status);

/**
 * Get SSM CRC error interrupts masks
 *
 * @param rev_id - PCI revision ID
 * @param crc_a_mask - pointer to iofic group A mask
 * @param crc_b_mask - pointer to iofic group B mask
 * @param crc_c_mask - pointer to iofic group C mask
 * @param crc_d_mask - pointer to iofic group D mask
 */
void al_crc_error_ints_mask_get(unsigned int rev_id,
				uint32_t *crc_a_mask,
				uint32_t *crc_b_mask,
				uint32_t *crc_c_mask,
				uint32_t *crc_d_mask);

/**
 * Unmask CRC error interrupts
 *
 * @param	rev_id
 *		PCI adapter revision ID
 * @param	num_of_crc
 *		number of CRC instances
 * @param	crc_regs_base
 *		CRC's register base addresses
 * @param	udma_regs_base
 *		UDMA register base address
 */
void al_crc_memcpy_error_ints_unmask(uint8_t rev_id,
				     unsigned int num_of_crc,
				     void __iomem *crc_regs_base[AL_SSM_MAX_CRC],
				     void __iomem *udma_regs_base);
 /* *INDENT-OFF* */
#ifdef __cplusplus
}
#endif
/* *INDENT-ON* */
/** @} end of crc_memcpy group */
#endif		/* __AL_HAL_SSM_CRC_MEMCPY_H__ */
