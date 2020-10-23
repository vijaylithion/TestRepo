/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdio.h"
#include "string.h"



/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum reset_cause_e
{
    RESET_CAUSE_UNKNOWN = 0,
    RESET_CAUSE_LOW_POWER_RESET,
    RESET_CAUSE_WINDOW_WATCHDOG_RESET,
    RESET_CAUSE_INDEPENDENT_WATCHDOG_RESET,
    RESET_CAUSE_SOFTWARE_RESET,
    RESET_CAUSE_POWER_ON_POWER_DOWN_RESET,
    RESET_CAUSE_EXTERNAL_RESET_PIN_RESET,
    RESET_CAUSE_BROWNOUT_RESET,
} resetCause_t;
/* USER CODE END PTD */



/* USER CODE BEGIN PFP */
resetCause_t resetCause(void);
const char * resetCauseName(resetCause_t reset_cause);
/* USER CODE END PFP */




  /* USER CODE BEGIN SysInit */
  resetCause_t reset_cause = resetCause();
  /* USER CODE END SysInit */
  
  
  
  /* USER CODE BEGIN 2 */
  char buf[50] = {0};
  sprintf(buf, "SYSTEM RESET CAUSE -->  %s \n",(char*) resetCauseName(reset_cause));
  HAL_UART_Transmit(&huart1,(uint8_t*)buf,50,1000);
  HAL_Delay(500);
  /* USER CODE END 2 */
  
  
  
  /* USER CODE BEGIN 4 */

resetCause_t resetCause(void)
{
    resetCause_t reset_cause;

    if (__HAL_RCC_GET_FLAG(RCC_FLAG_LPWRRST))
    {
        reset_cause = RESET_CAUSE_LOW_POWER_RESET;
    }
    else if (__HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST))
    {
        reset_cause = RESET_CAUSE_WINDOW_WATCHDOG_RESET;
    }
    else if (__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST))
    {
        reset_cause = RESET_CAUSE_INDEPENDENT_WATCHDOG_RESET;
    }
    else if (__HAL_RCC_GET_FLAG(RCC_FLAG_SFTRST))
    {
        reset_cause = RESET_CAUSE_SOFTWARE_RESET; // This reset is induced by calling the ARM CMSIS `NVIC_SystemReset()` function!
    }
    else if (__HAL_RCC_GET_FLAG(RCC_FLAG_PORRST))
    {
        reset_cause = RESET_CAUSE_POWER_ON_POWER_DOWN_RESET;
    }
    else if (__HAL_RCC_GET_FLAG(RCC_FLAG_PINRST))
    {
        reset_cause = RESET_CAUSE_EXTERNAL_RESET_PIN_RESET;
    }
    else if (__HAL_RCC_GET_FLAG(RCC_FLAG_BORRST))
    {
        reset_cause = RESET_CAUSE_BROWNOUT_RESET;
    }
    else
    {
        reset_cause = RESET_CAUSE_UNKNOWN;
    }

    // Clear all the reset flags or else they will remain set during future resets until system power is fully removed.
    __HAL_RCC_CLEAR_RESET_FLAGS();

    return reset_cause;
}





const char * resetCauseName(resetCause_t reset_cause)
{
    const char * cause_name = "TBD";

    switch (reset_cause)
    {
        case RESET_CAUSE_UNKNOWN:
            cause_name = "UNKNOWN";
            break;
        case RESET_CAUSE_LOW_POWER_RESET:
            cause_name = "LOW_POWER_RESET";
            break;
        case RESET_CAUSE_WINDOW_WATCHDOG_RESET:
            cause_name = "WINDOW_WATCHDOG_RESET";
            break;
        case RESET_CAUSE_INDEPENDENT_WATCHDOG_RESET:
            cause_name = "INDEPENDENT_WATCHDOG_RESET";
            break;
        case RESET_CAUSE_SOFTWARE_RESET:
            cause_name = "SOFTWARE_RESET";
            break;
        case RESET_CAUSE_POWER_ON_POWER_DOWN_RESET:
            cause_name = "POWER-ON_RESET (POR) / POWER-DOWN_RESET (PDR)";
            break;
        case RESET_CAUSE_EXTERNAL_RESET_PIN_RESET:
            cause_name = "EXTERNAL_RESET_PIN_RESET";
            break;
        case RESET_CAUSE_BROWNOUT_RESET:
            cause_name = "BROWNOUT_RESET (BOR)";
            break;
    }

    return cause_name;
}
/* USER CODE END 4 */