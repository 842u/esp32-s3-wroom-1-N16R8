#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "print_system_info.h"
#include "sdkconfig.h"
#include <stdio.h>

void app_main(void)
{
  xTaskCreate(print_system_info, "print_system_info", 2048, NULL, 5, NULL);
}
