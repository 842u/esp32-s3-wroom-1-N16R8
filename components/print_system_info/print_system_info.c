#include "print_system_info.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_heap_caps.h"
#include "esp_psram.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <inttypes.h>
#include <stdio.h>

void print_system_info(void *arg)
{
  while (1)
  {
    // Chip information
    printf("\n=== Chip Information ===\n");

    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);

    printf("Chip: %s\n", CONFIG_IDF_TARGET);
    printf("Cores: %d\n", chip_info.cores);

    unsigned major_rev = chip_info.revision / 100;
    unsigned minor_rev = chip_info.revision % 100;
    printf("Silicon revision: v%d.%d\n", major_rev, minor_rev);

    printf("Features: %s%s%s%s%s\n",
           (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "WiFi/" : "",
           (chip_info.features & CHIP_FEATURE_BT) ? "BT" : "",
           (chip_info.features & CHIP_FEATURE_BLE) ? "BLE" : "",
           (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "",
           (chip_info.features & CHIP_FEATURE_EMB_PSRAM) ? ", embedded PSRAM" : "");

    // Memory information
    printf("\n=== Memory Information ===\n");

    // Flash
    uint32_t flash_size;
    if (esp_flash_get_size(NULL, &flash_size) != ESP_OK)
    {
      printf("Get flash size failed");
      return;
    }
    printf("Flash size: %" PRIu32 " bytes (%.2f MB)\n",
           flash_size, flash_size / (1024.0 * 1024.0));
    printf("Flash type: %s\n",
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    // Heap
    size_t heap_total_size = heap_caps_get_total_size(MALLOC_CAP_DEFAULT);
    printf("Total heap size: %d bytes (%.2f MB)\n",
           heap_total_size, heap_total_size / (1024.0 * 1024.0));

    size_t heap_free_size = heap_caps_get_free_size(MALLOC_CAP_DEFAULT);
    printf("Free heap size: %d bytes (%.2f MB)\n",
           heap_free_size, heap_free_size / (1024.0 * 1024.0));

    size_t heap_minimum_free_size = esp_get_minimum_free_heap_size();
    printf("Free minimum heap size: %d bytes (%.2f MB)\n",
           heap_minimum_free_size, heap_minimum_free_size / (1024.0 * 1024.0));

    // Internal RAM
    size_t ram_size = heap_caps_get_total_size(MALLOC_CAP_INTERNAL);
    printf("Internal RAM size: %d bytes free (%.2f MB)\n",
           ram_size,
           ram_size / (1024.0 * 1024.0));

    size_t ram_free_size = heap_caps_get_free_size(MALLOC_CAP_INTERNAL);
    printf("Free internal RAM: %d bytes free (%.2f MB)\n",
           ram_free_size,
           ram_free_size / (1024.0 * 1024.0));

    // PSRAM
    size_t psram_size = esp_psram_get_size();
    printf("PSRAM size: %d bytes (%.2f MB)\n",
           psram_size, psram_size / (1024.0 * 1024.0));

    size_t total_psram = heap_caps_get_total_size(MALLOC_CAP_SPIRAM);
    printf("Total PSRAM available to heap: %d bytes (%.2f MB)\n",
           total_psram, total_psram / (1024.0 * 1024.0));

    size_t free_psram = heap_caps_get_free_size(MALLOC_CAP_SPIRAM);
    printf("Free PSRAM: %d bytes (%.2f MB)\n",
           free_psram, free_psram / (1024.0 * 1024.0));

    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}
