add_library(rtt STATIC
    ${RTT_DIR}/RTT/SEGGER_RTT.c
)

target_include_directories(rtt SYSTEM PUBLIC
    ${RTT_DIR}/RTT
    ${RTT_DIR}/Config
)
