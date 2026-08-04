#include "log/log.hpp"
#include <cstdint>
#include "stm32f4xx_hal.h"


extern "C" void MemManage_Handler(void) __attribute__((naked));
extern "C" void HardFault_Handler(void) __attribute__((naked));
extern "C" void Default_Handler(void) __attribute__((naked));

/// Fix stack pointer and call actual handler
#define CALL_HANDLER(handler) \
    __asm volatile ( \
        "ldr r0, =_estack\n" \
        "msr msp, r0\n" \
        "b " #handler "\n" \
    );

extern "C" void MemManage_Handler(void) {
    CALL_HANDLER(mem_manage_handler);
}

extern "C" void HardFault_Handler(void) {
    CALL_HANDLER(hard_fault_handler);
}

// extern "C" void Default_Handler(void) {
//     CALL_HANDLER(default_handler);
// }

extern "C" void mem_manage_handler() {

    logging::error("Stack overflow detected!");

    while (true) {}
}

extern "C" void hard_fault_handler() {

    logging::error("Hard fault!");

    while (true) {}
}

extern "C" void default_handler() {

    uint32_t ipsr = __get_IPSR();
    logging::error("Default handler: IPSR = {}", ipsr);

    while (true) {}
}
