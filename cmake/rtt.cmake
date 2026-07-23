set(RTT_DIR ${PROJECT_SOURCE_DIR}/external/rtt)

add_library(rtt STATIC
    ${RTT_DIR}/RTT/SEGGER_RTT.c
    ${RTT_DIR}/RTT/SEGGER_RTT_printf.c
)

target_include_directories(rtt
    SYSTEM PUBLIC
        ${RTT_DIR}/RTT
        # ${RTT_DIR}/Config
)


target_include_directories(rtt
    PUBLIC
        ${PROJECT_SOURCE_DIR}/config
)
