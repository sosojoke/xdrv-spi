/*
 * This file is part of x_spi
 *
 * Copyright (C) 2011, 2012 - Nenad Radulovic
 *
 * x_spi is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * x_spi is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * x_spi; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * web site:    http://blueskynet.dyndns-server.com
 * e-mail  :    blueskyniss@gmail.com
 *//***********************************************************************//**
 * @file
 * @author  	Nenad Radulovic
 * @brief       Control and configuration interface of XSPI driver
 * @addtogroup  ioctl_intf
 *********************************************************************//** @{ */

#if !defined(X_SPI_IOCTL_H_)
#define X_SPI_IOCTL_H_

/*=========================================================  INCLUDE FILES  ==*/
/*===============================================================  MACRO's  ==*/

/*------------------------------------------------------------------------*//**
 * @name        Global settings
 * @{ *//*--------------------------------------------------------------------*/

#define XSPI_IOC_MAGIC                  1

/* --------------------------------------------------------------------------
 * Current channel selection
 * -------------------------------------------------------------------------- */

enum xspiChn {
    XSPI_CHN_0                  = 0,
    XSPI_CHN_1                  = 1,
    XSPI_CHN_2                  = 2,
    XSPI_CHN_3                  = 3
};

/**@brief       Set the current channel being configured
 * @details     0 - 3 channel
 */
#define XSPI_IOC_SET_CURRENT_CHN        _IOW(XSPI_IOC_MAGIC, 1, int)

/**@brief       Get the current channel being configured
 */
#define XSPI_IOC_GET_CURRENT_CHN        _IOR(XSPI_IOC_MAGIC, 101, int)

/* --------------------------------------------------------------------------
 * FIFO channel selection
 * -------------------------------------------------------------------------- */

enum xspiFifoChn {
    XSPI_FIFO_CHN_DISABLED      = -1,
    XSPI_FIFO_CHN_0             = 0,
    XSPI_FIFO_CHN_1             = 1,
    XSPI_FIFO_CHN_2             = 2,
    XSPI_FIFO_CHN_3             = 3
};

/**@brief       Enable/disable FIFO mode on one channel
 * @details     -1 - disable FIFO
 *              0 - 3 channel with FIFO enabled
 */
#define XSPI_IOC_SET_FIFO_CHN           _IOW(XSPI_IOC_MAGIC, 2, int)

/**@brief       Get which channel has FIFO enabled
 */
#define XSPI_IOC_GET_FIFO_CHN           _IOR(XSPI_IOC_MAGIC, 102, int)

/* --------------------------------------------------------------------------
 * CS pin mode
 * -------------------------------------------------------------------------- */

enum xspiCsMode {
    XSPI_CS_MODE_ENABLED        = 0,
    XSPI_CS_MODE_DISABLED       = 1
};

/**@brief       Set SPIEN (Chip-Select) global mode
 * @details     0 - SPIEN is used as a chip select
 *              1 - SPIEN is not used
 */
#define XSPI_IOC_SET_CS_MODE            _IOW(XSPI_IOC_MAGIC, 3, int)

/**@brief       Get SPIEN (Chip-Select) mode
 */
#define XSPI_IOC_GET_CS_MODE            _IOR(XSPI_IOC_MAGIC, 103, int)

/* --------------------------------------------------------------------------
 * SPI master/slave mode
 * -------------------------------------------------------------------------- */

enum xspiMode {
    XSPI_MODE_MASTER            = 0,
    XSPI_MODE_SLAVE             = 1
};

/**@brief       Set module master/slave mode
 * @details     0 - Master - The module generates the SPICLK and SPIEN[3:0]
 *              1 - Slave - The module receives the SPICLK and SPIEN[3:0]
 */
#define XSPI_IOC_SET_MODE               _IOW(XSPI_IOC_MAGIC, 4, int)

/**@brief       Get module mode
 */
#define XSPI_IOC_GET_MODE               _IOR(XSPI_IOC_MAGIC, 104, int)

/* --------------------------------------------------------------------------
 * Single/multi channel mode
 * -------------------------------------------------------------------------- */

enum xspiChannelMode {
    XSPI_CHANNEL_MODE_MULTI     = 0,
    XSPI_CHANNEL_MODE_SINGLE    = 1
};

/**@brief       Set module channel mode
 * @details     0 - More than one channel will be used in master mode
 *              1 - Only one channel will be usedd in master mode
 * @note        This setting is valid only if the device is in master mode (
 *              XSPI_IOC_SET_MODE(XSPI_MODE_MASTER))
 */
#define XSPI_IOC_SET_CHANNEL_MODE       _IOW(XSPI_IOC_MAGIC, 5, int)

/**@brief       Get module channel mode
 */
#define XSPI_IOC_GET_CHANNEL_MODE       _IOR(XSPI_IOC_MAGIC, 105, int)

/* --------------------------------------------------------------------------
 * Data initial delay
 * -------------------------------------------------------------------------- */

enum xspiInitialDelay {
    XSPI_INITIAL_DELAY_0        = 0,
    XSPI_INITIAL_DELAY_4        = 1,
    XSPI_INITIAL_DELAY_8        = 2,
    XSPI_INITIAL_DELAY_16       = 3,
    XSPI_INITIAL_DELAY_32       = 4
};

/**@brief       First SPI word delayed
 * @details     0 - 32 clock cycles
 */
#define XSPI_IOC_SET_INITIAL_DELAY      _IOW(XSPI_IOC_MAGIC, 6, int)

/**@brief       Get first SPI word delay
 */
#define XSPI_IOC_GET_INITIAL_DELAY      _IOR(XSPI_IOC_MAGIC, 106, int)

/**@} *//*----------------------------------------------------------------*//**
 * @name        Per channel settings
 * @{ *//*--------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * Transfer mode
 * -------------------------------------------------------------------------- */

enum xspiTransferMode {
    XSPI_TRANSFER_MODE_TX_AND_RX = 0,
    XSPI_TRANSFER_MODE_RX_ONLY   = 1,
    XSPI_TRANSFER_MODE_TX_ONLY   = 2
};

/**@brief       Transmit/receive modes
 * @details     0 - Transmit and receive mode
 *              1 - Receive mode only
 *              2 - Transmit mode only
 */
#define XSPI_IOC_SET_TRANSFER_MODE      _IOW(XSPI_IOC_MAGIC, 7, int)

/**@brief       Get transmit/receive mode
 */
#define XSPI_IOC_GET_TRANSFER_MODE      _IOR(XSPI_IOC_MAGIC, 107, int)

/* --------------------------------------------------------------------------
 * Tx/Rx pin layout
 * -------------------------------------------------------------------------- */

enum xspiPinLayout {
    XSPI_PIN_LAYOUT_TX_RX       = 0,
    XSPI_PIN_LAYOUT_RX_TX       = 1
};

/**@brief       Reverse the directions of transmit/receive pins
 * @details     0 - pins are in transmit/receive layout
 *              1 - pins are in receive/transmit layout
 */
#define XSPI_IOC_SET_PIN_LAYOUT         _IOW(XSPI_IOC_MAGIC, 8, int)

/**@brief       Gt the current pin layout
 */
#define XSPI_IOC_GET_PIN_LAYOUT         _IOR(XSPI_IOC_MAGIC, 108, int)

/* --------------------------------------------------------------------------
 * Data word length
 * -------------------------------------------------------------------------- */

/**@brief       Set data word length
 * @details     Data length can be in range from 4 bits to 32 bits
 */
#define XSPI_IOC_SET_WORD_LENGTH        _IOW(XSPI_IOC_MAGIC, 9, int)

/**@brief       Get data word length
 */
#define XSPI_IOC_GET_WORD_LENGTH        _IOR(XSPI_IOC_MAGIC, 109, int)

/* --------------------------------------------------------------------------
 * CS delay
 * -------------------------------------------------------------------------- */

enum xspiCsDelay {
    XSPI_CS_DELAY_0_5           = 0,
    XSPI_CS_DELAY_1_5           = 1,
    XSPI_CS_DELAY_2_5           = 2,
    XSPI_CS_DELAY_3_5           = 3
};

/**@brief       Chip-Select Timing Control (per channel setting)
 * @details     0 - 3 cycle delay
 * @note        This setting is valid only when XSPI_IOC_SET_CS_MODE = 0.
 */
#define XSPI_IOC_SET_CS_DELAY           _IOW(XSPI_IOC_MAGIC, 10, int)

/**@brief       Get Chip-select timing
 */
#define XSPI_IOC_GET_CS_DELAY           _IOR(XSPI_IOC_MAGIC, 110, int)

/* --------------------------------------------------------------------------
 * CS polarity
 * -------------------------------------------------------------------------- */

enum xspiCsPolarity {
    XSPI_CS_POLARITY_ACTIVE_HIGH = 0,
    XSPI_CS_POLAROTY_ACTIVE_LOW  = 1
};

/**@brief       Set Chip-Select polarity
 * @details     0 - CS is held high during the active state
 *              1 - CS is held low during the active state
 */
#define XSPI_IOC_SET_CS_POLARITY        _IOW(XSPI_IOC_MAGIC, 11, int)

/**@brief       Get Chip-Select polarity
 */
#define XSPI_IOC_GET_CS_POLARITY        _IOR(XSPI_IOC_MAGIC, 111, int)

/* --------------------------------------------------------------------------
 * CS state
 * -------------------------------------------------------------------------- */

enum xspiCsState {
    XSPI_CS_STATE_INACTIVE      = 0,
    XSPI_CS_STATE_ACTIVE        = 1
};

/**@brief       Set-force Chip-Select pin state between SPI words
 * @details     0 - Set CS state to inactive
 *              1 - Set CS state to active
 * @note        This setting is valid only when XSPI_IOC_SET_CS_MODE is set to 0.
 */
#define XSPI_IOC_SET_CS_STATE           _IOW(XSPI_IOC_MAGIC, 12, int)

/**@brief       Get Chip-Select pin state
 */
#define XSPI_IOC_GET_CS_STATE           _IOR(XSPI_IOC_MAGIC, 112, int)

/* --------------------------------------------------------------------------
 * Clock frrequency
 * -------------------------------------------------------------------------- */

/**@brief       Define SPICLK clock frequency
 */
#define XSPI_IOC_SET_CLOCK_FREQ         _IOW(XSPI_IOC_MAGIC, 13, int)

/**@brief       Get SPICLK clock frequency
 */
#define XSPI_IOC_GET_CLOCK_FREQ         _IOR(XSPI_IOC_MAGIC, 113, int)

/* --------------------------------------------------------------------------
 * Clock phase
 * -------------------------------------------------------------------------- */

enum xspiClockPhase {
    XSPI_CLOCK_PHASE_ODD_EDGES  = 0,
    XSPI_CLOCK_PHASE_EVEN_EDGES = 1
};

/**@brief       Define SPICLK clock phase
 * @details     0 - Data is latched on odd numbered edges of SPICLK
 *              1 - Data is latched on even numbered edges of SPICLK
 */
#define XSPI_IOC_SET_CLOCK_PHASE        _IOW(XSPI_IOC_MAGIC, 14, int)

/**@brief       Get SPICLK clock phase
 */
#define XSPI_IOC_GET_CLOCK_PHASE        _IOR(XSPI_IOC_MAGIC, 114, int)

/* --------------------------------------------------------------------------
 * Clock polarity
 * -------------------------------------------------------------------------- */

enum xspiClockPolarity {
    XSPI_CLOCK_POLARITY_ACTIVE_HIGH = 0,
    XSPI_CLOCK_POLARITY_ACTIVE_LOW  = 1
};

/**@brief       Define SPICLK clock polarity
 * @details     0 - SPICLK is held high during the active state
 *              1 - SPICLK is held low during the active state
 */
#define XSPI_IOC_SET_CLOCK_POLARITY     _IOW(XSPI_IOC_MAGIC, 15, int)

/**@brief       Get SPICLK clock polarity
 */
#define XSPI_IOC_GET_CLOCK_POLARITY     _IOR(XSPI_IOC_MAGIC, 115, int)


/**@} *//*----------------------------------------------------------------*//**
 * @name        SPI Status
 * @brief       All IOC data/control is per channel
 * @{ *//*--------------------------------------------------------------------*/

/**@brief       Get the device status
 */
#define XSPI_IOC_GET_STATUS             _IOR(XSPI_IOC_MAGIC, 200, int)

/**@brief       Get the channel status
 */
#define XSPI_IOC_GET_CHN_STATUS         _IOR(XSPI_IOC_MAGIC, 201, int)

/**@} *//*--------------------------------------------------------------------*/

/*============================================================  DATA TYPES  ==*/
/*======================================================  GLOBAL VARIABLES  ==*/
/*===================================================  FUNCTION PROTOTYPES  ==*/
/*================================*//** @cond *//*==  CONFIGURATION ERRORS  ==*/
/** @endcond *//** @} *//******************************************************
 * END of x_spi_ioctl.h
 ******************************************************************************/
#endif /* X_SPI_IOCTL_H_ */
