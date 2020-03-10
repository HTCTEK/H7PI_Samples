# H7PI_Samples

## Introduction
H7PI Samples

## How to use？

#### How does the bootloader run
bootloader at 0x08000000-->app at 0x90000000(qspi flash)

#### How does the app run
app at 0x90000000-->STM32 HAL Init-->freeRTOS Init-->User's Default Task-->User's Init(Functions,Drivers Init)-->User's Task

#### other samples
wikis，[H7PI WIKI](https://pinno.cc/2020/02/28/H7PI-%E7%AE%80%E4%BB%8B/)

