idf_component_register(
  SRCS "wi_fi_access_point.c"
  PRIV_REQUIRES esp_netif esp_wifi nvs_flash
  INCLUDE_DIRS "include")
