/*
 * This file is part of the Black Magic Debug project.
 *
 * Copyright (C) 2012  Black Sphere Technologies Ltd.
 * Written by Gareth McMullin <gareth@blacksphere.co.nz>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/cm3/cortex.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/scs.h>
#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/cdc.h>

#include "general.h"
#include "usbuart.h"
#include "usb.h"
#include "aux_serial.h"

#ifdef DMA_STREAM0
#define DMA_CGIF DMA_ISR_FLAGS
#else
#define DMA_CGIF DMA_IFCR_CGIF_BIT
#endif

#ifdef ENABLE_DEBUG
/* Debug Fifo buffer with space for copy fn overrun */
char usb_dbg_buf[AUX_UART_BUFFER_SIZE];
/* Debug Fifo in pointer */
uint8_t usb_dbg_in;
/* Debug Fifo out pointer */
uint8_t usb_dbg_out;
#endif
