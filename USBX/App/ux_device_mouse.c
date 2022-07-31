/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    ux_device_mouse.c
  * @author  MCD Application Team
  * @brief   USBX Device applicative file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  * Modified by BookBuddi July 2022
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "ux_device_mouse.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "main.h"
#include "tx_api.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define CURSOR_STEP     10

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
volatile uint8_t User_Button_State = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
static void GetPointerData(UX_SLAVE_CLASS_HID_EVENT *hid_event);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
UINT app_usbx_device_thread_hid_callback(UX_SLAVE_CLASS_HID *hid,
                                         UX_SLAVE_CLASS_HID_EVENT *hid_event)
{
  return 0U;
}


VOID    demo_hid_instance_activate(VOID *hid_instance)
{

}

VOID    demo_hid_instance_deactivate(VOID *hid_instance)
{

UINT status;

    /* Abort all transfer requests on the interrupt OUT endpoint. */
    status = ux_device_stack_transfer_abort(&interrupt_out_endpoint -> ux_slave_endpoint_transfer_request, 0);
    if (status)
        Error_Handler();
}





/**
  * @brief  Function implementing usbx_hid_thread_entry.
  * @param arg: Not used
  * @retval None
  */
void usbx_hid_thread_entry(ULONG arg)
{
  UX_SLAVE_DEVICE    *device;
  UX_SLAVE_INTERFACE *interface;
  UX_SLAVE_CLASS_HID *hid;
  UX_SLAVE_CLASS_HID_EVENT hid_event;

  device = &_ux_system_slave->ux_system_slave_device;
  ux_utility_memory_set(&hid_event, 0, sizeof(UX_SLAVE_CLASS_HID_EVENT));

  while (1)
  {
    /* Check if the device state already configured */
    if (device->ux_slave_device_state == UX_DEVICE_CONFIGURED)
    {
      /* Get the interface */
      interface = device->ux_slave_device_first_interface;
      /* Get the instance */
      hid = interface->ux_slave_interface_class_instance;

      /* sleep for 10ms */
      tx_thread_sleep(MS_TO_TICK(10));

      /* Check if user button is pressed */
      if (User_Button_State)
      {
        /* Get the new position */
        GetPointerData(&hid_event);

        /* Send an event to the hid */
        ux_device_class_hid_event_set(hid, &hid_event);

        /* Reset User Button state */
        User_Button_State =0;
      }
    }
    else
    {
      /* sleep for 10ms */
      tx_thread_sleep(MS_TO_TICK(10));
    }
  }
}





void  interrupt_out_thread_entry(ULONG input)
{

UX_SLAVE_DEVICE                 *device;
UX_SLAVE_INTERFACE              *interface;
UX_SLAVE_ENDPOINT               *endpoint;
UX_SLAVE_TRANSFER               *transfer_request;
UINT                            status;
//UINT                            i;


UX_SLAVE_CLASS_HID *hid; //pbw
UX_SLAVE_CLASS_HID_EVENT hid_event;

    /* Get the pointer to the device.  */
    device =  &_ux_system_slave -> ux_system_slave_device;

    /* Do this forever. */
    while (1)
    {

        /* Wait for the device to become configured. */
        while (device -> ux_slave_device_state != UX_DEVICE_CONFIGURED)
            tx_thread_sleep(100);

//pbw was here

        /* Get the interface. We use the first interface, this is a simple device.  */
        interface =  device -> ux_slave_device_first_interface;

        /* Get the interrupt OUT endpoint. We don't bother checking the endpoint type,
           since we know this device only has interrupt endpoints. */
        endpoint = interface -> ux_slave_interface_first_endpoint;

        while ((endpoint -> ux_slave_endpoint_descriptor.bEndpointAddress & UX_ENDPOINT_DIRECTION) != UX_ENDPOINT_OUT)
        {
            endpoint = endpoint -> ux_slave_endpoint_next_endpoint;
            tx_thread_sleep(100); //pbw wait for interrupt
        }

        //pbw was here

        /* Save the interrupt endpoint in a global. */
        interrupt_out_endpoint = endpoint; //used for error pbw

        /* Get the transfer request from the endpoint. */
        transfer_request = &endpoint -> ux_slave_endpoint_transfer_request; //pbw from the buff to the hid, I dont need but must be done

        /* While the device stays configured, read from the interrupt OUT endpoint.  */
        while (device -> ux_slave_device_state == UX_DEVICE_CONFIGURED)
        {

            /* Setup the transfer request. */
            transfer_request -> ux_slave_transfer_request_data_pointer = interrupt_out_endpoint_data_buffer;
            transfer_request -> ux_slave_transfer_request_requested_length = sizeof(interrupt_out_endpoint_data_buffer);

            /* Do the transfer request. Note this function is blocking. When the device is disconnected,
               the instance deactivate callback will abort the request, thus resuming this function.*/
            status = ux_device_stack_transfer_request(transfer_request,
                                                      /* These two parameters should just be the requested length. */
                                                      sizeof(interrupt_out_endpoint_data_buffer), sizeof(interrupt_out_endpoint_data_buffer));

            //blocking function till next int, clear int buff put into local buff


            /* Was the transfer aborted? */
            if (status == UX_TRANSFER_BUS_RESET) break;

            /* Error? */
            if (status != UX_SUCCESS) Error_Handler();

            /* Process data from host. pbw */
            //for (i = 0; i < transfer_request->ux_slave_transfer_request_actual_length; i++)
                //printf("%c", transfer_request->ux_slave_transfer_request_data_pointer[i]);

            //pbw was here, instead of printf received data, reflect it back to pc app
            //tx_thread_sleep(MS_TO_TICK(1000));


            interface = device->ux_slave_device_first_interface;
            hid = interface->ux_slave_interface_class_instance;

            hid_event.ux_device_class_hid_event_length = 3;
            hid_event.ux_device_class_hid_event_buffer[0] = interrupt_out_endpoint_data_buffer[0];
            hid_event.ux_device_class_hid_event_buffer[1] = interrupt_out_endpoint_data_buffer[1];
            hid_event.ux_device_class_hid_event_buffer[2] = interrupt_out_endpoint_data_buffer[2];
            ux_device_class_hid_event_set(hid, &hid_event);

            //hid_event.ux_device_class_hid_event_buffer[0] = transfer_request->ux_slave_transfer_request_data_pointer[0];
            //hid_event.ux_device_class_hid_event_buffer[1] = transfer_request->ux_slave_transfer_request_data_pointer[1];
            //hid_event.ux_device_class_hid_event_buffer[2] = transfer_request->ux_slave_transfer_request_data_pointer[2];
            //ux_device_class_hid_event_set(hid, &hid_event);


        } //while
    } //while 1
}



/**
  * @brief  Gets Pointer Data.
  * @param  pbuf: Pointer to report
  * @retval None
  */
static void GetPointerData(UX_SLAVE_CLASS_HID_EVENT *hid_event)
{
  static int8_t cnt = 0;
  static int8_t x = 0, y = 0;

  /* Reset counter */
  if (cnt == 16)
  {
    cnt = 0;
  }
  /* Update pointer position x and y */
  if ((cnt >= 0) && (cnt < 4))
  {
    y=0;
    x = CURSOR_STEP;
  }
  else if ((cnt >= 4) && (cnt < 8))
  {
    x =0;
    y = CURSOR_STEP;
  }
  else if ((cnt >= 8) && (cnt < 12))
  {
    y=0;
    x = -CURSOR_STEP;
  }
  else
  {
    x=0;
    y = -CURSOR_STEP;
  }
  /* Increment counter */
  cnt++;

  /* Mouse event. Length is fixed to . */
  hid_event->ux_device_class_hid_event_length = 3;

  /* Set X position. */
  hid_event->ux_device_class_hid_event_buffer[0] = x;

  /* Set Y position. */
  hid_event->ux_device_class_hid_event_buffer[1] = y;

  hid_event->ux_device_class_hid_event_buffer[2] = 0;
}

/**
  * @brief  EXTI line detection callback.
  * @param  GPIO_Pin: Specifies the port pin connected to corresponding EXTI line.
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  /* Read User Button state */
  User_Button_State = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);

}

/* USER CODE END 0 */

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
