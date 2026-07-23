set(CONFIG_LV_BUILD_DEMOS OFF CACHE BOOL "" FORCE)
set(CONFIG_LV_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(CONFIG_LV_USE_THORVG_INTERNAL OFF CACHE BOOL "" FORCE)

set(LV_BUILD_CONF_DIR
    "${PROJECT_SOURCE_DIR}/config"
    CACHE PATH "" FORCE
)

add_subdirectory(external/lvgl)

target_include_directories(lvgl
    PRIVATE
        ${PROJECT_SOURCE_DIR}/config
)
