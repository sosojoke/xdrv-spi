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
 * x_spi; if not, write to the Free Software Foundation, Inc., 51 Franklin St,
 * Fifth Floor, Boston, MA  02110-1301  USA
 *
 * web site:    http://blueskynet.dyndns-server.com
 * e-mail  :    blueskyniss@gmail.com
 *//***********************************************************************//**
 * @file
 * @author      Nenad Radulovic
 * @brief       Low Level Driver implementation
 *********************************************************************//** @{ */

/*=========================================================  INCLUDE FILES  ==*/

#include "linux/io.h"

#include "port/port.h"
#include "drv/x_spi_lld.h"
#include "drv/x_spi.h"
#include "log/log.h"
#include "dbg/dbg.h"

/*=========================================================  LOCAL MACRO's  ==*/

#define MCSPI_REVISION_X_MAJOR_Pos      (8u)
#define MCSPI_REVISION_X_MAJOR_Mask     (0x03u << MCSPI_REVISION_X_MAJOR_Pos)
#define MCSPI_REVISION_Y_MINOR_Pos      (0u)
#define MCSPI_REVISION_Y_MINOR_Mask     (0x1fu << MCSPI_REVISION_Y_MINOR_Pos)
#define MCSPI_SYSCONFIG_SOFTRESET_Pos   (1u)
#define MCSPI_SYSCONFIG_SOFTRESET_Mask  (0x01u << MCSPI_SYSCONFIG_SOFTRESET_Pos)
#define MCSPI_SYSSTATUS_RESETDONE_Pos   (0u)
#define MCSPI_SYSSTATUS_RESETDONE_Mask  (0x01u << MCSPI_SYSSTATUS_RESETDONE_Pos)

/*======================================================  LOCAL DATA TYPES  ==*/

enum mcspiRegs {
    MCSPI_REVISION      = 0x000u,
    MCSPI_SYSCONFIG     = 0x110u,
    MCSPI_SYSSTATUS     = 0x114u,
    MCSPI_IRQSTATUS     = 0x118u,
    MCSPI_IRQENABLE     = 0x11cu,
    MCSPI_SYST          = 0x124u,
    MCSPI_MODULCTRL     = 0x128u,
    MCSPI_CHANNEL_BASE  = 0x12cu,
    MCSPI_XFERLEVEL     = 0x17cu,
    MCSPI_DAFTX         = 0x180u,
    MCSPI_DAFRX         = 0x1a0u
};

enum mcspiChnRegs {
    MCSPI_CH_CONF       = 0x00u,
    MCSPI_CH_STAT       = 0x04u,
    MCSPI_CH_CTRL       = 0x08u,
    MCSPI_CH_TX         = 0x0cu,
    MCSPI_CH_RX         = 0x10u,
    MCSPI_CHANNEL_SIZE  = 0x14u
};

/*=============================================  LOCAL FUNCTION PROTOTYPES  ==*/

static inline void regWrite(
    volatile uint8_t *  io,
    enum mcspiRegs      reg,
    uint32_t            val);

static inline uint32_t regRead(
    volatile uint8_t *  io,
    enum mcspiRegs      reg);

static inline void regChnWrite(
    volatile uint8_t *  io,
    uint32_t            chn,
    enum mcspiChnRegs   reg,
    uint32_t            val);

static inline uint32_t regChnRead(
    volatile uint8_t *  io,
    uint32_t            chn,
    enum mcspiChnRegs   reg);

/*=======================================================  LOCAL VARIABLES  ==*/

DECL_MODULE_INFO("x_spi_lld", "Low-level device driver", DEF_DRV_AUTHOR);

/*======================================================  GLOBAL VARIABLES  ==*/
/*============================================  LOCAL FUNCTION DEFINITIONS  ==*/

static inline void regWrite(
    volatile uint8_t *  io,
    enum mcspiRegs      reg,
    uint32_t            val) {

    LOG_DBG("UART wr: %p, %x = %x", io, reg, val);

    iowrite32(val, &io[reg]);
}

static inline uint32_t regRead(
    volatile uint8_t *  io,
    enum mcspiRegs      reg) {

    uint32_t            ret;

    ret = ioread32(&io[reg]);

    LOG_DBG("UART rd: %p, %x : %x", io, reg, ret);

    return (ret);
}

static inline void regChnWrite(
    volatile uint8_t *  io,
    uint32_t            chn,
    enum mcspiChnRegs   reg,
    uint32_t            val) {

    regWrite(io, MCSPI_CHANNEL_BASE + (chn * MCSPI_CHANNEL_SIZE) + reg, val);
}

static inline uint32_t regChnRead(
    volatile uint8_t *  io,
    uint32_t            chn,
    enum mcspiChnRegs   reg) {

    uint32_t            ret;

    ret = regRead(io, MCSPI_CHANNEL_BASE + (chn * MCSPI_CHANNEL_SIZE) + reg);

    return (ret);
}

/*===================================  GLOBAL PRIVATE FUNCTION DEFINITIONS  ==*/
/*====================================  GLOBAL PUBLIC FUNCTION DEFINITIONS  ==*/

int32_t lldDevInit(
    struct rtdm_device * dev) {

    volatile uint8_t *  io;
    int32_t             retval;
    uint32_t            revision;

    io = portRemapGet(
        dev);
    revision = regRead(
        io,
        MCSPI_REVISION);                                                        /* Read revision info                                       */
    LOG_INFO("hardware version: %d.%d",
        (revision & MCSPI_REVISION_X_MAJOR_Mask) >> MCSPI_REVISION_X_MAJOR_Pos,
        (revision & MCSPI_REVISION_Y_MINOR_Mask) >> MCSPI_REVISION_Y_MINOR_Pos);
    lldDevReset(
        dev);
    retval = 0;

    return (retval);
}

void lldDevTerm(
    struct rtdm_device * dev) {

    lldDevReset(
        dev);
}

void lldDevReset(
    struct rtdm_device * dev) {

    volatile uint8_t *  io;
    uint32_t            sysconfig;

    io = portRemapGet(
        dev);

    sysconfig = regRead(
        io,
        MCSPI_SYSCONFIG);
    regWrite(
        io,
        MCSPI_SYSCONFIG,
        sysconfig | MCSPI_SYSCONFIG_SOFTRESET_Mask);                            /* Reset device module                                      */

    while (0u == (regRead(io, MCSPI_SYSSTATUS) & MCSPI_SYSSTATUS_RESETDONE_Mask));  /* Wait a few cycles for reset procedure                */
}

/*================================*//** @cond *//*==  CONFIGURATION ERRORS  ==*/
/** @endcond *//** @} *//******************************************************
 * END of x_spi_lld.c
 ******************************************************************************/
