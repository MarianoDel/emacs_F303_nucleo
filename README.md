# Placa de desarrollo NUCLEO-F303RE STM32
micro STM32F303RE


Antes de empezar revisar seleccion del micro y configuracion
------------------------------------------------------------

* work area size y flash image
>stm32f3_flash.cfg

* work area size y flash image
>stm32f3_flash_lock.cfg

* work area size
>stm32f3_gdb.cfg

* work area size
>stm32f3_reset.cfg

* end of ram; stack size; memory lenght
>./startup_src/STM32F303RETx_FLASH.ld

* elegir clock (xtal o rc)
>./src/hard.h

* elegir procesador definiciones -> modificar en Makefile
>.Makefile

* Lo que no migre esta en las cabeceras como F103
* Lo migrado como F303
