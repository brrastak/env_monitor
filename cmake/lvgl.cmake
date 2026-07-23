set(LV_BUILD_CONF_PATH "${PROJECT_SOURCE_DIR}/config/lv_conf.h")

add_subdirectory(external/lvgl)

target_compile_definitions(lvgl PUBLIC
    LV_CONF_INCLUDE_SIMPLE
)

target_include_directories(lvgl
    PRIVATE
        ${PROJECT_SOURCE_DIR}/config
)
