# <b>Ux_Device_HID_Bidir STM32 application</b>

STM32 project that can send and receive 3 bytes via joystick HID using NUCLEO-F767ZI  board, AZURE USBX, STM32CubeIDE and a PC.

STM32 Ux_Device_Hid project that was a Mouse Hid using B1 (button1 on dev board) was transformed into Ux_Device_Hid_Bidir, still using B1 to send test data, but now set as a joystick to work with USB2550HidTest c# PC app. The app shows received data, and sends data via its Button1, which is reflected back to the app. If press send button too quickly can crash board, just reset (there is no send complete event yet) The main app file is ux_device_mouse.c

some Help to transform the app came from
https://en-support.renesas.com/knowledgeBase/18553243
https://helmpcb.com/electronics/modifying-the-joystick-hid-descriptor 
which also added an interrupt OUT endpoint.

#### <b>To see the app in action</b>

Buy NUCLEO-F767ZI and must also get 2 of USB A to USB Micro B cables and 1 of Male Micro USB AB to Female MICRO B Cable, (see RS 236-9085) Connecting the board will take 3 cables and 2 USB slots on the PC.

Have VS2022 and download/build/run the app from https://www.codeproject.com/tips/530836/csharp-usb-hid-interface only download USB2550HidTest.zip 35 KB.

Have STM32CubeIDE and import Ux_Device_Hid_Bidir.zip via File menu, open projects from file system, Import source from Archive, then tick only eclipse project. Build with Hammer Icon and run with play icon to the right of the green bug icon. Project running and saved to Board after seen Download verified successfully Shutting down...Exit. in the console. 

The Ux_Device_Hid_Bidir project was created by cleaning, copying and renaming the original Ux_Device_Hid project folder, renaming some file names and the contents of some files. see original project below.

Bookbuddi July 2022


## <b>Ux_Device_HID application description</b>

This application provides an example of Azure RTOS USBX stack usage on STM32F767ZI board,
it shows how to develop USB Device Human Interface "HID" mouse based application.

The application is designed to emulate an USB HID mouse device, the code provides all required device descriptors framework
and associated Class descriptor report to build a compliant USB HID mouse device.

At the beginning ThreadX call the entry function tx_application_define(), at this stage, all USBx resources
are initialized, the HID Class driver is registered and the application creates 2 threads with the same priorities :

  - usbx_app_thread_entry (Prio : 20; PreemptionPrio : 20) used to initialize USB OTG HAL PCD driver and start the device.
  - usbx_hid_thread_entry (Prio : 20; PreemptionPrio : 20) used to send HID reports to move automatically the PC host machine cursor.

To customize the HID application by sending the mouse position step by step every 10ms.
For each 10ms, the application calls the GetPointerData() API to update the mouse position (x, y) and send
the report buffer through the ux_device_class_hid_event_set() API.

#### <b>Expected success behavior</b>

When plugged to PC host, the STM32F767ZI must be properly enumerated as an USB HID mouse device.
During the enumeration phase, device provides host with the requested descriptors (Device, configuration, string).
Those descriptors are used by host driver to identify the device capabilities.
Once the STM32F767ZI USB device successfully completed the enumeration phase, the device sends a HID report after a user button press.
Each report sent should move the mouse cursor by one step on host side.

#### <b>Error behaviors</b>

Host PC shows that USB device does not operate as designed (Mouse enumeration failed, the mouse pointer doesn't move).

#### <b>Assumptions if any</b>

User is familiar with USB 2.0 "Universal Serial BUS" Specification and HID class Specification.

#### <b>Known limitations</b>

The remote wakeup feature is not yet implemented (used to bring the USB suspended bus back to the active condition).

When creating an USBX based application with MDK-ARM AC6 compiler make sure to disable the optimization for stm32F7xx_ll_usb.c file, otherwise application might not work correctly.
This limitation will be fixed in future release.

### <b>Notes</b>

 1.  If the user code size exceeds the DTCM-RAM size or starts from internal cacheable memories (SRAM1 and SRAM2), that is shared between several processors,
      then it is highly recommended to enable the CPU cache and maintain its coherence at application level.
      The address and the size of cacheable buffers (shared between CPU and other masters) must be properly updated to be aligned to cache line size (32 bytes).

#### <b>ThreadX usage hints</b>

 - ThreadX uses the Systick as time base, thus it is mandatory that the HAL uses a separate time base through the TIM IPs.
 - ThreadX is configured with 100 ticks/sec by default, this should be taken into account when using delays or timeouts at application. It is always possible to reconfigure it in the "tx_user.h", the "TX_TIMER_TICKS_PER_SECOND" define,but this should be reflected in "tx_initialize_low_level.s" file too.
 - ThreadX is disabling all interrupts during kernel start-up to avoid any unexpected behavior, therefore all system related calls (HAL, BSP) should be done either at the beginning of the application or inside the thread entry functions.
 - ThreadX offers the "tx_application_define()" function, that is automatically called by the tx_kernel_enter() API.
   It is highly recommended to use it to create all applications ThreadX related resources (threads, semaphores, memory pools...)  but it should not in any way contain a system API call (HAL or BSP).
 - Using dynamic memory allocation requires to apply some changes to the linker file.
   ThreadX needs to pass a pointer to the first free memory location in RAM to the tx_application_define() function,
   using the "first_unused_memory" argument.
   This require changes in the linker files to expose this memory location.
    + For EWARM add the following section into the .icf file:
     ```
	 place in RAM_region    { last section FREE_MEM };
	 ```
    + For MDK-ARM:
	```
    either define the RW_IRAM1 region in the ".sct" file
    or modify the line below in "tx_low_level_initilize.s to match the memory region being used
        LDR r1, =|Image$$RW_IRAM1$$ZI$$Limit|
	```
    + For STM32CubeIDE add the following section into the .ld file:
	```
    ._threadx_heap :
      {
         . = ALIGN(8);
         __RAM_segment_used_end__ = .;
         . = . + 64K;
         . = ALIGN(8);
       } >RAM_D1 AT> RAM_D1
	```

       The simplest way to provide memory for ThreadX is to define a new section, see ._threadx_heap above.
       In the example above the ThreadX heap size is set to 64KBytes.
       The ._threadx_heap must be located between the .bss and the ._user_heap_stack sections in the linker script.
       Caution: Make sure that ThreadX does not need more than the provided heap memory (64KBytes in this example).
       Read more in STM32CubeIDE User Guide, chapter: "Linker script".

    + The "tx_initialize_low_level.s" should be also modified to enable the "USE_DYNAMIC_MEMORY_ALLOCATION" flag.

#### <b>USBX usage hints</b>

- The DTCM non cacheable memory (0x20000000-0x2001FFFF) is accessible by the USB-DMA.
- When using a cacheable memory (SRAM1 or SRAM2), make sure to configure the USB memory pool region attribute "Non-Cacheable" to ensure coherency between the CPU and the USB DMA.

### <b>Keywords</b>

RTOS, ThreadX, USBX, USB_OTG, Full Speed, HID, Mouse,

### <b>Hardware and Software environment</b>

  - This application runs on STM32F767ZIxx devices.
  - This application has been tested with STMicroelectronics STM32F767ZI-NUCLEO board MB1137 Revision B-01
    and can be easily tailored to any other supported device and development board.

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the application
