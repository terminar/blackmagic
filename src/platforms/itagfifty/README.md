# BMP firmware for iSYSTEM iTAG.FIFTY (STM32F405)

This platform is based on platforms/hydrabus.

## General pins

- C6              : LED-GREEN
- PA9, PA11, PA12 : USB

## J2-Hdr

- J2-0: VDD
- J2-1: BOOT0

## Top-left header
```
  .-----------,
  | C3  | C2  |
  | --  | C0  |
  | B6  | --  |
  | B7  | B9  |
  | GND | GND |
  `-----------´
```

## Backside header (added manually)

- 0: GND
- 1: RESET
- 2: SWDCLK
- 3: SWDIO

## Jtag header
```
  ----------------------------
  | VCC/VTREF    | VCC (opt) |
  | TRST         | GND       | OC5
  | NC/TDI       | GND       | B10
  | SWDIO/TMS    | GND       | B1
  - SWDCLK/TCLK  | GND       | B0
  - RTCK         | GND       | B12
  | SWO/TDO      | GND       | C7
  | RESET        | GND       | C4
  | NC           | GND       |
  | NC           | GND       |
----------------------------
```

## How to Build

Patch the libopencm3 or USB will not work. Instructions/patch below.

```
cd blackmagic
make clean
make PROBE_HOST=itagfifty
```

## libopencm3 patch

The VBUS sensing isn't properly working on the iTAG.FIFTY with libopencm3.

There are some issues regarding VBUS sensing:
- https://github.com/libopencm3/libopencm3-examples/issues/178
- https://github.com/libopencm3/libopencm3/issues/1119
- https://github.com/libopencm3/libopencm3/pull/1256


A fix is maybe to add 
```
OTG_FS_GCCFG |= OTG_GCCFG_NOVBUSSENS | OTG_GCCFG_PWRDWN;
OTG_FS_GCCFG &= ~(OTG_GCCFG_VBUSBSEN | OTG_GCCFG_VBUSASEN);
```
somewhere in the platform.c init code but that's untested.
Currently a quickfix is to patch libopencm3.

```
diff --git a/lib/usb/usb_f107.c b/lib/usb/usb_f107.c
index 52df7172..d36744a9 100644
--- a/lib/usb/usb_f107.c
+++ b/lib/usb/usb_f107.c
@@ -67,7 +67,9 @@ static usbd_device *stm32f107_usbd_init(void)
                OTG_FS_GCCFG |= OTG_GCCFG_VBDEN | OTG_GCCFG_PWRDWN;
        } else {
                /* Enable VBUS sensing in device mode and power up the PHY. */
-               OTG_FS_GCCFG |= OTG_GCCFG_VBUSBSEN | OTG_GCCFG_PWRDWN;
+               // OTG_FS_GCCFG |= OTG_GCCFG_VBUSBSEN | OTG_GCCFG_PWRDWN;
+               // TODO: fixed for ITAG.FIFTY (STM32F405RG)
+               OTG_FS_GCCFG |= OTG_GCCFG_NOVBUSSENS | OTG_GCCFG_PWRDWN;
        }
        /* Explicitly enable DP pullup (not all cores do this by default) */
        OTG_FS_DCTL &= ~OTG_DCTL_SDIS;
```
