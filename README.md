# STM32 HC165 usb hid keyboard

VERSION V0.2.0

## fix
* 修改hc165获取数据方式 
* 添加hc165_driver.h/c
* 添加keyboard.h/c
* 删除key.h/c
* 删除hc165.h/c

## platformIO ini 配置

```ini
[env:genericSTM32F103C8]
platform = ststm32
board = genericSTM32F103C8
; framework = stm32cube
build_flags = 
	-D STM32F103xx
	-ICore/Inc
	-IDrivers/CMSIS/Include
	-IDrivers/CMSIS/Device/ST/STM32F1xx/Include
	-IDrivers/STM32F1xx_HAL_Driver/Inc
	-IDrivers/STM32F1xx_HAL_Driver/Inc/Legacy
	-IUSB_DEVICE/App
	-IUSB_DEVICE/Target
	-IMIDDLEWARES/ST/STM32_USB_Device_Library/Class/HID/Inc
	-IMIDDLEWARES/ST/STM32_USB_Device_Library/Core/Inc

src_filter = +<Core/Src> +<startup_stm32f103xb.s> +<Drivers/> +<Middlewares/>+<Usb_device/>
board_build.ldscript = ./STM32F103C8Tx_FLASH.ld
upload_protocol = stlink 
debug_tool = stlink


[platformio]
src_dir = ./
include_dir = Core/Inc
```

PB15 -> LATCH PIN
PB14 -> DATA PIN
PB13 -> CLK PIN



