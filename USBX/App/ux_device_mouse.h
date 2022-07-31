/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    ux_device_mouse.h
  * @author  MCD Application Team
  * @brief   USBX Device Mouse header file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UX_DEVICE_MOUSE_H__
#define __UX_DEVICE_MOUSE_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ux_api.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ux_device_class_hid.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/

/* USER CODE BEGIN EFP */

UINT app_usbx_device_thread_hid_callback(UX_SLAVE_CLASS_HID *hid,
                                         UX_SLAVE_CLASS_HID_EVENT *hid_event);

void  usbx_hid_thread_entry(ULONG arg);


VOID    demo_hid_instance_activate(VOID *hid_instance); //pbw
VOID    demo_hid_instance_deactivate(VOID *hid_instance);



extern UX_SLAVE_ENDPOINT            *interrupt_out_endpoint;
extern UCHAR                        interrupt_out_endpoint_data_buffer[8];
void                                interrupt_out_thread_entry(ULONG); //pbw

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

#ifdef __cplusplus
}
#endif
#endif  /* __UX_DEVICE_MOUSE_H__ */
