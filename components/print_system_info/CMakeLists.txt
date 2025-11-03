idf_component_register(
  SRCS "print_system_info.c"
  PRIV_REQUIRES spi_flash
  INCLUDE_DIRS include
  REQUIRES esp_psram esp_system)
