/*
  bt_chipset_api.h

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

/*
    Abstract and functional description

        3rd party Chipset API Specification for Bluetooth

    Specification/design references

        BT Chipset API Specification.doc


*/

#ifndef BT_CHIPSET_API_H
#define BT_CHIPSET_API_H


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

/* ----------------------------------------------------------- */
/* macros for interface function: hal_bt_uart_control()        */
/* ----------------------------------------------------------- */
/* possible actions */
#define HAL_BT_UART_CTRL_ENABLE_INT            0
#define HAL_BT_UART_CTRL_DISABLE_INT           1
#define HAL_BT_UART_CTRL_INIT_UART             2
#define HAL_BT_UART_CTRL_BAUDRATE_SET          3
#define HAL_BT_UART_CTRL_SLEEP                 4
#define HAL_BT_UART_CTRL_FLUSH                 5

/* possible interrupts for enable/disable interrupts */
#define HAL_BT_UART_HOST_WAKEUP_INT            (1<<0)
#define HAL_BT_UART_RX_INT                     (1<<1)
#define HAL_BT_UART_TX_INT                     (1<<2)
#define HAL_BT_UART_CTS_INT                    (1<<3)
#define HAL_BT_UART_ALL_INT                    ( HAL_BT_UART_HOST_WAKEUP_INT| \
                                                 HAL_BT_UART_RX_INT|          \
                                                 HAL_BT_UART_TX_INT|          \
                                                 HAL_BT_UART_CTS_INT )
/* possible actions for enable/disable interrupts */
#define HAL_BT_UART_DISABLE_INT                0
#define HAL_BT_UART_ENABLE_INT                 1  /* Note: any value != 0 will enable the int */

/* possible activities for sleep control */
#define HAL_BT_UART_SLEEP_DISABLE              0
#define HAL_BT_UART_SLEEP_ENABLE               1
#define HAL_BT_UART_SLEEP_ENABLE_TX            2
#define HAL_BT_UART_SLEEP_ENABLE_RX            3
#define HAL_BT_UART_SLEEP_DISABLE_TX           4
#define HAL_BT_UART_SLEEP_DISABLE_RX           5

/* possible buffers rx/tx flush */
#define HAL_BT_UART_RX_BUFFER                  (1<<0)
#define HAL_BT_UART_TX_BUFFER                  (1<<1)

/* constants for UART init: */
/* parity setting */
#define HAL_BT_UART_PARITY_NONE                0
#define HAL_BT_UART_PARITY_ODD                 1
#define HAL_BT_UART_PARITY_EVEN                2
/* flow control */
#define HAL_BT_UART_FLOW_MODE_FREE             1    /* no flow control used */
#define HAL_BT_UART_FLOW_MODE_SOFT             2    /* SW controled flow control */
#define HAL_BT_UART_FLOW_MODE_HARD             3    /* HW controled flow control */
/* need to write number of bits-1 to register */
#define HAL_BT_UART_DATA_BIT_8                 7
#define HAL_BT_UART_STOP_BIT_1                 0



/* ----------------------------------------------------------- */
/* macros for interface function: hal_bt_uart_port_access()    */
/* ----------------------------------------------------------- */
/* possible ports */
#define HAL_BT_UART_RTS                        0
#define HAL_BT_UART_BT_WAKEUP                  1
#define HAL_BT_UART_BT_RESETX                  2
#define HAL_BT_UART_HOST_WAKEUP                3
#define HAL_BT_UART_CTS                        4
/* access types */
#define HAL_BT_UART_READ                       0
#define HAL_BT_UART_WRITE                      1
/* possible port states */
#define HAL_BT_UART_OFF                        0
#define HAL_BT_UART_ON                         1


/* ----------------------------------------------------------- */
/* macros for interface function: hal_bt_uart_register_event() */
/* ----------------------------------------------------------- */
/* possible events */
/* used when registrating handler for certain events */
#define HAL_BT_UART_TX_FINISHED_EVENT          0
#define HAL_BT_UART_RX_FINISHED_EVENT          1
#define HAL_BT_UART_RX_HEADER_EVENT            2
#define HAL_BT_UART_HOST_WAKEUP_EVENT          3
#define HAL_BT_UART_CTS_EVENT                  4


/* ----------------------------------------------------------- */
/* HAL BT UART interface function error codes/return values    */
/* ----------------------------------------------------------- */
#define HAL_BT_UART_ERR_UNSUPPORTED_PORT       2
#define HAL_BT_UART_ERR_UNSUPPORTED_OPERATION  3
#define HAL_BT_UART_ERR_UNSUPPORTED_PARAMETER  5

/* ---------------------------------------------------------------------------
 *
 * TYPES
 *
 */

typedef void (*HAL_BT_UART_EVENT_HANDLER)(void);
typedef uint8   HAL_BT_UART_INTR_CTRL_STR;
typedef uint32 HAL_BT_UART_BAUDRATE;

typedef struct
    {
    uint8  data_bit;
    uint8  stop_bit;
    uint8  parity;
    uint8  flow_control;
    } HAL_BT_UART_INIT_CTRL_STR;

/** a pointer to a union of this type is used to pass parameters to the
 * different control features of bt_hal_control function
 */
typedef union
    {
    HAL_BT_UART_INTR_CTRL_STR   intr_control;
    HAL_BT_UART_INIT_CTRL_STR   init_control;
    HAL_BT_UART_BAUDRATE        baudrate_control;
    uint8                       sleep_control;
    uint8                       flush_control;
    } HAL_BT_UART_CONTROL_STR;

/* ---------------------------------------------------------------------------
 *
 * FUNCTIONAL PROTOTYPES AND MACROS
 *
 */

/** This function serves as control and configuration function */
uint8   hal_bt_uart_control(uint8 action, HAL_BT_UART_CONTROL_STR* control_str);

/** Register an event handler for one of the possible interrupts */
void    hal_bt_uart_register_event(uint8 event_type, HAL_BT_UART_EVENT_HANDLER event_cb_hdl, uint16 trigger_level);

/** access input/output pins */
uint8   hal_bt_uart_port_access(uint8 port, uint8 action, uint8 pin_set, uint8* port_status);

/** Starts data transmission */
void    hal_bt_uart_send(uint8* tx_data, uint16 num_bytes);

/** Prepare reception of one message */
uint8   hal_bt_uart_rx_buffer_set(uint8* rx_buf, uint16 length);

/** Given a theoretical baudrate to be used return a real baudrate that will be used on UART */
uint32  hal_bt_uart_phy_baudrate_get(uint32 baudrate);

#endif /* BT_CHIPSET_API_H */
/* End of Include File */
