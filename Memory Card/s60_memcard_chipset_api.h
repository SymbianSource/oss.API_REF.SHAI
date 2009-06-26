/*
  s60_memcard_chipset_api.h

  Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies). 
  All rights reserved.

  This program and the accompanying materials are made available 
  under the terms of the Eclipse Public License v1.0 which accompanies 
  this distribution, and is available at 
  http://www.eclipse.org/legal/epl-v10.html

  Initial Contributors:
  Nokia Corporation - initial contribution.

  Contributors:
*/

/** @file
@brief Memcard Chipset API H

    Abstract and functional description

        3rd party Chipset API Specification for low level memory card driver

    Specification/design references

        Memory Card Chipset API Specification.doc
*/

/**
 * defgroup csapi Chipset API
 * Chipset API Documentation
 */

#ifndef MEMCARD_CHIPSET_API_H
#define MEMCARD_CHIPSET_API_H

/* Informative list of headers which are directly used by the present header
 * and hence assumed to be included by the .c module before the present header
 *     global.h
 *     type_def.h
 */

/* ---------------------------------------------------------------------------
 *
 * CONSTANTS
 *
 */

/**
 * @brief
 * Memory card ID.
 *
 * @details
 * Logical ID for memory card.
 *
 * @see link
 */
typedef enum hal_memcard_card
    {
    HAL_MEMCARD_CARD0, /**< Memory card 0 */
    HAL_MEMCARD_CARD1, /**< Memory card 1 */
    HAL_MEMCARD_CARD2, /**< Memory card 2 */
    HAL_MEMCARD_CARD3, /**< Memory card 3 */
    HAL_MEMCARD_NONE   /**< Memory card 4 */
    } HAL_MEMCARD_CARD;

/**
 * @brief
 * Memory card chipset API return values.
 *
 * @details
 * Memory card chipset API return values.
 *
 * @see link
 */
typedef enum hal_memcard_return
    {
    HAL_MEMCARD_FAIL              = 0, /**< Operation failed */
    HAL_MEMCARD_OK                = 1, /**< Operation succeeded */
    HAL_MEMCARD_DMA_ALLOC_FAIL    = 2, /**< DMA channel allocation failed */
    HAL_MEMCARD_DMA_TRANSFER_FAIL = 3, /**< DMA transfer failed */
    HAL_MEMCARD_CARD_STATUS_ERROR = 4, /**< A non-masked error bit was set in the card status */
    HAL_MEMCARD_CMD_TIMEOUT       = 5, /**< Command timeout occured */
    HAL_MEMCARD_DATA_TIMEOUT      = 6, /**< Data timeout occured */
    HAL_MEMCARD_CMD_CRC_ERROR     = 7, /**< Command CRC error occured */
    HAL_MEMCARD_DATA_CRC_ERROR    = 8  /**< Data CRC error occured */
    } HAL_MEMCARD_RETURN;

/**
 * @brief
 * Memory access operation.
 *
 * @details
 * Memory access operation types (read/write)
 *
 * @see link
 */
typedef enum hal_memcard_operation
    {
    HAL_MEMCARD_READ    = 0, /**< Read operation */
    HAL_MEMCARD_WRITE   = 1  /**< Write operation */
    } HAL_MEMCARD_OPERATION;

/**
 * @brief
 * Media change types.
 *
 * @details
 * Memory card media change types.
 *
 * @see link
 */
typedef enum hal_memcard_media_change_event
    {
    HAL_MEMCARD_INSERTED = 0, /**< Memory card inserted */
    HAL_MEMCARD_REMOVED  = 1  /**< Memory card removed */
    } HAL_MEMCARD_MEDIA_CHANGE_EVENT;

/**
 * @brief
 * Media change callback definition
 *
 * @details
 * -
 *
 * @see link
 */
typedef void (*hal_memcard_media_change_callback) (HAL_MEMCARD_MEDIA_CHANGE_EVENT mce, HAL_MEMCARD_CARD card);

/**
 * @brief
 * Data (bus) width types
 *
 * @details
 * Memory card bus widths (1/4/8-bits).
 *
 * @see link
 */
typedef enum hal_memcard_data_width
    {
    HAL_MEMCARD_DATA_WIDTH_1_BIT    = 0, /**< 1-bit bus width */
    HAL_MEMCARD_DATA_WIDTH_4_BIT    = 1, /**< 4-bit bus width */
    HAL_MEMCARD_DATA_WIDTH_8_BIT    = 2  /**< 8-bit bus width */
    } HAL_MEMCARD_DATA_WIDTH;

/**
 * @brief
 * Presence of the memory card
 *
 * @details
 * Presence of the memory card.
 *
 * @see link
 */
typedef enum hal_memcard_presence_status
    {
    HAL_MEMCARD_CARD_IS_IN  = 0, /**< Memory card is in */
    HAL_MEMCARD_CARD_IS_OUT = 1  /**< Memory card is out */
    } HAL_MEMCARD_PRESENCE_STATUS;


/**
 * @brief
 * Mode of data transfer
 *
 * @details
 * Data transfer mode, DMA or not DMA (for example interrupt transfer).
 *
 * @see link
 */
typedef enum hal_memcard_data_transfer_mode
    {
    HAL_MEMCARD_DMA         = 0, /**< Use DMA transfer */
    HAL_MEMCARD_NOT_DMA     = 1  /**< Do not use DMA transfer */
    } HAL_MEMCARD_DATA_TRANSFER_MODE;

/**
 * @brief
 * Memory card response type
 *
 * @details
 * -
 *
 * @see link
 */
typedef enum hal_memcard_response_type
{
    HAL_MEMCARD_RESPONSE_NONE      = 0x00000, /**< None */
    HAL_MEMCARD_RESPONSE_R1        = 0x00100, /**< R1 response */
    HAL_MEMCARD_RESPONSE_R1b       = 0x00200, /**< R1b response */
    HAL_MEMCARD_RESPONSE_R2        = 0x00300, /**< R2 response */
    HAL_MEMCARD_RESPONSE_R3        = 0x00400, /**< R3 response */
    HAL_MEMCARD_RESPONSE_R4        = 0x00500, /**< R4 response */
    HAL_MEMCARD_RESPONSE_R5        = 0x00600, /**< R5 response */
    HAL_MEMCARD_RESPONSE_R6        = 0x00700, /**< R6 response */
    HAL_MEMCARD_RESPONSE_R7        = 0x00800, /**< R7 response */
    HAL_MEMCARD_RESPONSE_TYPE_MASK = 0x00f00  /**< Response type mask */
} HAL_MEMCARD_RESPONSE_TYPE;

/**
 * @brief
 * Memory card command type
 *
 * @details
 * -
 *
 * @see link
 */
typedef enum hal_memcard_command_type
{
    HAL_MEMCARD_COMMAND_TYPE_BC         = 0x00000, /**< BC */
    HAL_MEMCARD_COMMAND_TYPE_BCR        = 0x01000, /**< BCR */
    HAL_MEMCARD_COMMAND_TYPE_AC         = 0x02000, /**< AC */
    HAL_MEMCARD_COMMAND_TYPE_ADTC_WRITE = 0x03000, /**< ADTC write */
    HAL_MEMCARD_COMMAND_TYPE_ADTC_READ  = 0x04000, /**< ADTC read */
    HAL_MEMCARD_COMMAND_TYPE_MASK       = 0x07000  /**< Command type mask */
} HAL_MEMCARD_COMMAND_TYPE;

/**
 * @brief
 * Memory card type
 *
 * @details
 * -
 *
 * @see link
 */
typedef enum hal_memcard_command_card_type
{
    HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON = 0x00000, /**< Common */
    HAL_MEMCARD_COMMAND_CARD_TYPE_MMC    = 0x08000, /**< MMC card */
    HAL_MEMCARD_COMMAND_CARD_TYPE_SD     = 0x10000, /**< SD card */
    HAL_MEMCARD_COMMAND_CARD_TYPE_MASK   = 0x18000  /**< Card type mask */
} HAL_MEMCARD_COMMAND_CARD_TYPE;

/**
 * @brief
 * Memory card command type
 *
 * @details
 * -
 *
 * @see link
 */
typedef enum hal_memcard_command_app_norm
{
    HAL_MEMCARD_COMMAND_NORMAL        = 0x00000, /**< Normal */
    HAL_MEMCARD_COMMAND_APP           = 0x20000, /**< Application command */
    HAL_MEMCARD_COMMAND_APP_NORM_MASK = 0x20000  /**< Mask */
} HAL_MEMCARD_COMMAND_APP_NORM;

/**
 * @brief
 * Memory card command index mask
 *
 * @details
 * -
 *
 * @see link
 */
#define HAL_MEMCARD_COMMAND_INDEX_MASK 0x0003f

/**
 * @brief
 * Memorycard commands
 *
 * @details
 * Memory card command codes
 *
 * @see link
 */
typedef enum hal_memcard_command
{
    /* class 0 and class 1 */
    CMD0_GO_IDLE_STATE            =  0 | HAL_MEMCARD_RESPONSE_NONE | HAL_MEMCARD_COMMAND_TYPE_BC         | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD0  */
    CMD1_SEND_OP_COND             =  1 | HAL_MEMCARD_RESPONSE_R3   | HAL_MEMCARD_COMMAND_TYPE_BCR        | HAL_MEMCARD_COMMAND_CARD_TYPE_MMC    | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD1  */
    CMD2_ALL_SEND_CID_MMC         =  2 | HAL_MEMCARD_RESPONSE_R2   | HAL_MEMCARD_COMMAND_TYPE_BCR        | HAL_MEMCARD_COMMAND_CARD_TYPE_MMC    | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD2  */
    CMD2_ALL_SEND_CID_SD          =  2 | HAL_MEMCARD_RESPONSE_R2   | HAL_MEMCARD_COMMAND_TYPE_BCR        | HAL_MEMCARD_COMMAND_CARD_TYPE_SD     | HAL_MEMCARD_COMMAND_NORMAL,
    CMD3_SET_RELATIVE_ADDR        =  3 | HAL_MEMCARD_RESPONSE_R1   | HAL_MEMCARD_COMMAND_TYPE_AC         | HAL_MEMCARD_COMMAND_CARD_TYPE_MMC    | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD3  */
    CMD3_SEND_RELATIVE_ADDR       =  3 | HAL_MEMCARD_RESPONSE_R6   | HAL_MEMCARD_COMMAND_TYPE_AC         | HAL_MEMCARD_COMMAND_CARD_TYPE_SD     | HAL_MEMCARD_COMMAND_NORMAL,
    CMD4_SET_DSR                  =  4 | HAL_MEMCARD_RESPONSE_NONE | HAL_MEMCARD_COMMAND_TYPE_BC         | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD4  */
    CMD5_SLEEP_AWAKE              =  5 | HAL_MEMCARD_RESPONSE_R1b  | HAL_MEMCARD_COMMAND_TYPE_AC         | HAL_MEMCARD_COMMAND_CARD_TYPE_MMC    | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD5  */
    CMD6_SWITCH                   =  6 | HAL_MEMCARD_RESPONSE_R1b  | HAL_MEMCARD_COMMAND_TYPE_AC         | HAL_MEMCARD_COMMAND_CARD_TYPE_MMC    | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD6  */
    CMD6_SWITCH_FUNC              =  6 | HAL_MEMCARD_RESPONSE_R1   | HAL_MEMCARD_COMMAND_TYPE_ADTC_READ  | HAL_MEMCARD_COMMAND_CARD_TYPE_SD     | HAL_MEMCARD_COMMAND_NORMAL,
    ACMD6_SET_BUS_WIDTH           =  6 | HAL_MEMCARD_RESPONSE_R1   | HAL_MEMCARD_COMMAND_TYPE_AC         | HAL_MEMCARD_COMMAND_CARD_TYPE_SD     | HAL_MEMCARD_COMMAND_APP,
    CMD7_SELECT_CARD              =  7 | HAL_MEMCARD_RESPONSE_R1b  | HAL_MEMCARD_COMMAND_TYPE_AC         | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD7  */
    CMD7_DESELECT_CARD            =  7 | HAL_MEMCARD_RESPONSE_NONE | HAL_MEMCARD_COMMAND_TYPE_AC         | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL,
    CMD8_SEND_EXT_CSD             =  8 | HAL_MEMCARD_RESPONSE_R1   | HAL_MEMCARD_COMMAND_TYPE_ADTC_READ  | HAL_MEMCARD_COMMAND_CARD_TYPE_MMC    | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD8  */
    CMD8_SEND_IF_COND             =  8 | HAL_MEMCARD_RESPONSE_R7   | HAL_MEMCARD_COMMAND_TYPE_BCR        | HAL_MEMCARD_COMMAND_CARD_TYPE_SD     | HAL_MEMCARD_COMMAND_NORMAL,
    CMD9_SEND_CSD                 =  9 | HAL_MEMCARD_RESPONSE_R2   | HAL_MEMCARD_COMMAND_TYPE_AC         | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD9  */
    CMD10_SEND_CID                = 10 | HAL_MEMCARD_RESPONSE_R2   | HAL_MEMCARD_COMMAND_TYPE_AC         | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD10 */
    CMD11_READ_DAT_UNTIL_STOP     = 11 | HAL_MEMCARD_RESPONSE_R1   | HAL_MEMCARD_COMMAND_TYPE_ADTC_READ  | HAL_MEMCARD_COMMAND_CARD_TYPE_SD     | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD11 */
    CMD12_STOP_TRANSMISSION       = 12 | HAL_MEMCARD_RESPONSE_R1b  | HAL_MEMCARD_COMMAND_TYPE_AC         | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD12 */
    CMD13_SEND_STATUS             = 13 | HAL_MEMCARD_RESPONSE_R1   | HAL_MEMCARD_COMMAND_TYPE_AC         | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD13 */
    ACMD13_SD_STATUS              = 13 | HAL_MEMCARD_RESPONSE_R1   | HAL_MEMCARD_COMMAND_TYPE_ADTC_READ  | HAL_MEMCARD_COMMAND_CARD_TYPE_SD     | HAL_MEMCARD_COMMAND_APP,
    CMD14_BUSTEST_R               = 14 | HAL_MEMCARD_RESPONSE_R1   | HAL_MEMCARD_COMMAND_TYPE_ADTC_READ  | HAL_MEMCARD_COMMAND_CARD_TYPE_MMC    | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD14 */
    CMD15_GO_INACTIVE_STATE       = 15 | HAL_MEMCARD_RESPONSE_NONE | HAL_MEMCARD_COMMAND_TYPE_AC         | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD15 */
    /* class 2 */
    CMD16_SET_BLOCKLEN            = 16 | HAL_MEMCARD_RESPONSE_R1   | HAL_MEMCARD_COMMAND_TYPE_AC         | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD16 */
    CMD17_READ_SINGLE_BLOCK       = 17 | HAL_MEMCARD_RESPONSE_R1   | HAL_MEMCARD_COMMAND_TYPE_ADTC_READ  | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD17 */
    CMD18_READ_MULTIPLE_BLOCK     = 18 | HAL_MEMCARD_RESPONSE_R1   | HAL_MEMCARD_COMMAND_TYPE_ADTC_READ  | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD18 */
    CMD19_BUS_TEST_W              = 19 | HAL_MEMCARD_RESPONSE_R1   | HAL_MEMCARD_COMMAND_TYPE_ADTC_WRITE | HAL_MEMCARD_COMMAND_CARD_TYPE_MMC    | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD19 */
    /* class 3 */
    CMD20_WRITE_DAT_UNTIL_STOP    = 20 | HAL_MEMCARD_RESPONSE_R1   | HAL_MEMCARD_COMMAND_TYPE_ADTC_WRITE | HAL_MEMCARD_COMMAND_CARD_TYPE_MMC    | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD20 */
    CMD21                         = 21,                                                                                                                                       /**< CMD21 */
    CMD22                         = 22,                                                                                                                                       /**< CMD22 */
    ACMD22_SEND_NUM_WR_BLOCKS     = 22 | HAL_MEMCARD_RESPONSE_R1   | HAL_MEMCARD_COMMAND_TYPE_AC         | HAL_MEMCARD_COMMAND_CARD_TYPE_SD     | HAL_MEMCARD_COMMAND_APP,
    /* class 4 */
    CMD23_SET_BLOCK_COUNT         = 23 | HAL_MEMCARD_RESPONSE_R1   | HAL_MEMCARD_COMMAND_TYPE_AC         | HAL_MEMCARD_COMMAND_CARD_TYPE_MMC    | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD23 */
    ACMD23_SET_WR_BLK_ERASE_COUNT = 23 | HAL_MEMCARD_RESPONSE_R1   | HAL_MEMCARD_COMMAND_TYPE_AC         | HAL_MEMCARD_COMMAND_CARD_TYPE_SD     | HAL_MEMCARD_COMMAND_APP,
    CMD24_WRITE_BLOCK             = 24 | HAL_MEMCARD_RESPONSE_R1   | HAL_MEMCARD_COMMAND_TYPE_ADTC_WRITE | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD24 */
    CMD25_WRITE_MULTIPLE_BLOCK    = 25 | HAL_MEMCARD_RESPONSE_R1   | HAL_MEMCARD_COMMAND_TYPE_ADTC_WRITE | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD25 */
    CMD26_PROGRAM_CID             = 26 | HAL_MEMCARD_RESPONSE_R1   | HAL_MEMCARD_COMMAND_TYPE_ADTC_WRITE | HAL_MEMCARD_COMMAND_CARD_TYPE_MMC    | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD26 */
    CMD27_PROGRAM_CSD             = 27 | HAL_MEMCARD_RESPONSE_R1   | HAL_MEMCARD_COMMAND_TYPE_ADTC_WRITE | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD27 */
    /* class 6 */
    CMD28_SET_WRITE_PROT          = 28 | HAL_MEMCARD_RESPONSE_R1b  | HAL_MEMCARD_COMMAND_TYPE_AC         | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD28 */
    CMD29_CLR_WRITE_PROT          = 29 | HAL_MEMCARD_RESPONSE_R1b  | HAL_MEMCARD_COMMAND_TYPE_AC         | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD29 */
    CMD30_SEND_WRITE_PROT         = 30 | HAL_MEMCARD_RESPONSE_R1   | HAL_MEMCARD_COMMAND_TYPE_ADTC_READ  | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD30 */
    CMD31                         = 31,                                                                                                                       /**< CMD31 */
    /* class 5 */
    CMD32_ERASE_WR_BLK_START      = 32 | HAL_MEMCARD_RESPONSE_R1   | HAL_MEMCARD_COMMAND_TYPE_AC         | HAL_MEMCARD_COMMAND_CARD_TYPE_SD     | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD32 */
    CMD33_ERASE_WR_BLK_END        = 33 | HAL_MEMCARD_RESPONSE_R1   | HAL_MEMCARD_COMMAND_TYPE_AC         | HAL_MEMCARD_COMMAND_CARD_TYPE_SD     | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD33 */
    CMD34                         = 34,                                                                                                                                       /**< CMD34 */
    CMD35_ERASE_GROUP_START       = 35 | HAL_MEMCARD_RESPONSE_R1   | HAL_MEMCARD_COMMAND_TYPE_AC         | HAL_MEMCARD_COMMAND_CARD_TYPE_MMC    | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD35 */
    CMD36_ERASE_GROUP_END         = 36 | HAL_MEMCARD_RESPONSE_R1   | HAL_MEMCARD_COMMAND_TYPE_AC         | HAL_MEMCARD_COMMAND_CARD_TYPE_MMC    | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD36 */
    CMD37                         = 37,                                                                                                                                       /**< CMD37 */
    CMD38_ERASE                   = 38 | HAL_MEMCARD_RESPONSE_R1b  | HAL_MEMCARD_COMMAND_TYPE_AC         | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD38 */
    /* class 9 */
    CMD39_FASTIO                  = 39 | HAL_MEMCARD_RESPONSE_R4   | HAL_MEMCARD_COMMAND_TYPE_AC         | HAL_MEMCARD_COMMAND_CARD_TYPE_MMC    | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD39 */
    CMD40_GO_IRQSTATE             = 40 | HAL_MEMCARD_RESPONSE_R5   | HAL_MEMCARD_COMMAND_TYPE_BCR        | HAL_MEMCARD_COMMAND_CARD_TYPE_MMC    | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD40 */
    CMD41                         = 41,                                                                                                                                       /**< CMD41 */
    ACMD41_SD_SEND_OP_COND        = 41 | HAL_MEMCARD_RESPONSE_R3   | HAL_MEMCARD_COMMAND_TYPE_BCR        | HAL_MEMCARD_COMMAND_CARD_TYPE_SD     | HAL_MEMCARD_COMMAND_APP,
    /* class 7 */
    CMD42_LOCK_UNLOCK             = 42 | HAL_MEMCARD_RESPONSE_R1   | HAL_MEMCARD_COMMAND_TYPE_ADTC_WRITE | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD42 */
    ACMD42_SET_CLR_CARD_DETECT    = 42 | HAL_MEMCARD_RESPONSE_R1   | HAL_MEMCARD_COMMAND_TYPE_AC         | HAL_MEMCARD_COMMAND_CARD_TYPE_SD     | HAL_MEMCARD_COMMAND_APP,
    CMD43                         = 43,                                                                                                                                       /**< CMD43 */
    CMD44                         = 44,                                                                                                                                       /**< CMD44 */
    CMD45                         = 45,                                                                                                                                       /**< CMD45 */
    CMD46                         = 46,                                                                                                                                       /**< CMD46 */
    CMD47                         = 47,                                                                                                                                       /**< CMD47 */
    CMD48                         = 48,                                                                                                                                       /**< CMD48 */
    CMD49                         = 49,                                                                                                                                       /**< CMD49 */
    CMD50                         = 50,                                                                                                                                       /**< CMD50 */
    CMD51                         = 51,                                                                                                                                       /**< CMD51 */
    ACMD51_SEND_SCR               = 51 | HAL_MEMCARD_RESPONSE_R1   | HAL_MEMCARD_COMMAND_TYPE_ADTC_READ  | HAL_MEMCARD_COMMAND_CARD_TYPE_SD     | HAL_MEMCARD_COMMAND_APP,
    CMD52                         = 52,                                                                                                                                       /**< CMD52 */
    CMD53                         = 53,                                                                                                                                       /**< CMD53 */
    CMD54                         = 54,                                                                                                                                       /**< CMD54 */
    /* class 8 */
    CMD55_APP_CMD                 = 55 | HAL_MEMCARD_RESPONSE_R1   | HAL_MEMCARD_COMMAND_TYPE_AC         | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD55 */
    CMD56_GEN_CMD                 = 56 | HAL_MEMCARD_RESPONSE_R1   | HAL_MEMCARD_COMMAND_TYPE_ADTC_WRITE | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL, /**< CMD56 */
    CMD57                         = 57,                                                                                                                                       /**< CMD57 */
    CMD58                         = 58,                                                                                                                                       /**< CMD58 */
    CMD59                         = 59,                                                                                                                                       /**< CMD59 */
    CMD60                         = 60,                                                                                                                                       /**< CMD60 */
    CMD61                         = 61,                                                                                                                                       /**< CMD61 */
    CMD62                         = 62,                                                                                                                                       /**< CMD62 */
    CMD63                         = 63                                                                                                                                        /**< CMD63 */
} HAL_MEMCARD_COMMAND;


/**
 * @name Memorycard error/status types
 * @{
 */
#define HAL_MEMCARD_OUT_OF_RANGE        0x80000000 /**< The command’s address argument was out of the allowed range for this card */
#define HAL_MEMCARD_ADDRESS_ERROR       0x40000000 /**< misaligned address which did not match the block length was used in the command. */
#define HAL_MEMCARD_BLOCK_LEN_ERROR     0x20000000 /**< The transferred block length is not allowed for this card, or the number of transferred bytes does not match the block length. */
#define HAL_MEMCARD_ERASE_SEQ_ERROR     0x10000000 /**< An error in the sequence of erase commands occurred. */
#define HAL_MEMCARD_ERASE_PARAM         0x08000000 /**< An invalid selection of write-blocks for erase occurred. */
#define HAL_MEMCARD_WP_VIOLATION        0x04000000 /**< Set when the host attempts to write to a protected block or to the temporary or permanent write protected card. */
#define HAL_MEMCARD_CARD_IS_LOCKED      0x02000000 /**< When set, signals that the card is locked by the host */
#define HAL_MEMCARD_LOCK_UNLOCK_FAILED  0x01000000 /**< Set when a sequence or password error has been detected in lock/unlock card command. */
#define HAL_MEMCARD_COM_CRC_ERROR       0x00800000 /**< The CRC check of the previous command failed. */
#define HAL_MEMCARD_ILLEGAL_COMMAND     0x00400000 /**< Command not legal for the card state */
#define HAL_MEMCARD_CARD_ECC_FAILED     0x00200000 /**< Card internal ECC was applied but failed to correct the data. */
#define HAL_MEMCARD_CC_ERROR            0x00100000 /**< Internal card controller error */
#define HAL_MEMCARD_ERROR               0x00080000 /**< A general or an unknown error occurred during the operation. */
#define HAL_MEMCARD_UNDERRUN            0x00040000 /**< The card could not sustain data transfer in stream read mode */
#define HAL_MEMCARD_OVERRUN             0x00020000 /**< The card could not sustain data programming in stream write mode */
#define HAL_MEMCARD_CIDCSD_OVERWRITE    0x00010000 /**< CID or CSD cannot be overwritten */
#define HAL_MEMCARD_WP_ERASE_SKIP       0x00008000 /**< Only partial address space was erased due to existing write protected blocks. */
#define HAL_MEMCARD_CARD_ECC_DISABLED   0x00004000 /**< The command has been executed without using the internal ECC. */
#define HAL_MEMCARD_ERASE_RESET         0x00002000 /**< An erase sequence was cleared before executing because an out of erase sequence command was received */
#define HAL_MEMCARD_CARD_STATE          0x00001E00 /**< The state of the card when receiving the command. */
#define HAL_MEMCARD_CARD_READY_FOR_DATA 0x00000100 /**< Corresponds to buffer empty signaling on the bus */
#define HAL_MEMCARD_APP_CMD             0x00000020 /**< The card will expect ACMD, or an indication that the command has been interpreted as ACMD */
#define HAL_MEMCARD_SWITCH_ERROR        0x00000080 /**< If set, the card did not switch to the expected mode as requested by the SWITCH command */
#define HAL_MEMCARD_AKE_SEQ_ERROR       0x00000008 /**< Error in the sequence of the authentication process */
#define HAL_MEMCARD_NO_ERRORS           0          /**< No errors */
/*@}*/

/* ---------------------------------------------------------------------------
 *
 * DATA TYPES
 *
 */

/* Configuration structure to 3rd party API */
/**
 * @brief
 * Configuration structure to HAL layer.
 *
 * @details
 * Main structure is HAL_MEMCARD_INIT_CONF which is passed to the low level
 * memory card driver. This structure contains some HW related configuration data.
 *
 * @see link
 */
typedef struct hal_memcard_init_conf
    {
    /** How many times to try after fail, for instance sending commands */
    uint32 retries_after_fail;
    } HAL_MEMCARD_INIT_CONF;

/* Configuration structure from 3rd party API */
/**
 * @brief
 * Configuration structure from HAL layer.
 *
 * @details
 * Configuration structure from HAL layer.
 *
 * @see link
 */
typedef struct hal_memcard_hw_conf
    {
     /**
      * Version of the chipset API implementation<br>
      * bits [31:24] API specification major version number.<br>
      * bits [23:16] API specification minor version number.<br>
      * bits [15:8]  API implemention year. (2000 = 0, 2001 = 1, ...)<br>
      * bits [7:0]   API implemention week.<br>
      * Example: API specification version 4.0, implementation w46 2008 => 0x0400082E
      */
    uint32 api_version;

    /** Maximum block count which can be transferred at once */
    uint32 max_block_count;

    /** Maximum clock frequence in Hz supported by HW */
    uint32 max_clock_freq;

    /** Maximum data bus width supported by HW */
    uint16 max_data_width;

    /** Is high-speed mode supported by HW (supported=1, not supported=0) */
    uint8 hs_mode_supported;

    /** Is memory card removable (removable=1, not removable=0) */
    uint8 card_removable;
    } HAL_MEMCARD_HW_CONF;

/* ---------------------------------------------------------------------------
 *
 * FUNCTIONAL PROTOTYPES AND MACROS
 *
 */

HAL_MEMCARD_HW_CONF hal_memcard_get_hw_conf(HAL_MEMCARD_CARD card);

HAL_MEMCARD_RETURN hal_memcard_init_data_transfer(HAL_MEMCARD_CARD card,
                                                  uint32 blocks,
                                                  uint32 block_size,
                                                  uint8* data,
                                                  void (*fp)(HAL_MEMCARD_RETURN result),
                                                  HAL_MEMCARD_OPERATION op,
                                                  HAL_MEMCARD_DATA_TRANSFER_MODE transfer_mode);

HAL_MEMCARD_RETURN hal_memcard_power(HAL_MEMCARD_CARD card,
                                     uint8 mode,
                                     void (*fp)(HAL_MEMCARD_RETURN result));

HAL_MEMCARD_PRESENCE_STATUS hal_memcard_presence_status_get(HAL_MEMCARD_CARD card);

HAL_MEMCARD_RETURN hal_memcard_send_init_seq(HAL_MEMCARD_CARD card);

HAL_MEMCARD_RETURN hal_memcard_send_cmd(HAL_MEMCARD_CARD card,
                                        HAL_MEMCARD_COMMAND cmd,
                                        uint32 argument,
                                        uint32 error_mask,
                                        uint32* response);

HAL_MEMCARD_RETURN hal_memcard_set_clk(HAL_MEMCARD_CARD card,
                                       uint8 mode);

HAL_MEMCARD_RETURN hal_memcard_set_clk_freq(HAL_MEMCARD_CARD card,
                                            uint32 *freq);

HAL_MEMCARD_RETURN hal_memcard_set_data_width(HAL_MEMCARD_CARD card,
                                              HAL_MEMCARD_DATA_WIDTH width);

HAL_MEMCARD_RETURN hal_memcard_set_dto(HAL_MEMCARD_CARD card,
                                       uint32 time_out);

HAL_MEMCARD_RETURN hal_memcard_standby(HAL_MEMCARD_CARD card,
                                       uint8 mode);

void hal_memcard_stop_data_transfer(HAL_MEMCARD_CARD card);

HAL_MEMCARD_RETURN hal_memcard_register_conf(HAL_MEMCARD_CARD card,
                                             HAL_MEMCARD_INIT_CONF* init_conf);

HAL_MEMCARD_RETURN hal_memcard_register_mc_callback(hal_memcard_media_change_callback fp);

HAL_MEMCARD_RETURN hal_memcard_reset_controller(HAL_MEMCARD_CARD card,
                                                void (*fp)(HAL_MEMCARD_RETURN result));

#endif /* MEMCARD_CHIPSET_API_H */

/* End of Include File */
