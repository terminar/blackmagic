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

# How to Build

```
cd blackmagic
make clean
make PROBE_HOST=itagfifty
```
