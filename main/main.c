#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include "wi_fi_access_point.h"
#include <stdio.h>

void app_main(void)
{
  wi_fi_access_point_init();
}
