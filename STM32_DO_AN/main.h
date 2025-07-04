#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

    /* Private includes ----------------------------------------------------------*/
    /* USER CODE BEGIN Includes */

    /* USER CODE END Includes */

    /* USER CODE BEGIN 4 */
    /* USER CODE END 4 */
    /**
     * @brief  This function is executed in case of error occurrence.
     * @retval None
     */
    void Error_Handler(void)
    {
        /* USER CODE BEGIN Error_Handler_Debug */
        /* User can add his own implementation to report the HAL error return state */
        /* USER CODE END Error_Handler_Debug */
    }
#ifdef USE_FULL_ASSERT
    /**
    * @brief  Reports the name of the source file and the source line number
    *
          where the assert_param error has occurred.
    * @param  file: pointer to the source file name
    * @param  line: assert_param error line source number
    * @retval None
    */
    void assert_failed(uint8_t *file, uint32_t line)
    {
        /* USER CODE BEGIN 6 */
        /* User can add his own implementation to report the file name and line number,
        tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
        /* USER CODE END 6 */
    }
#endif /* USE_FULL_ASSERT */
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
