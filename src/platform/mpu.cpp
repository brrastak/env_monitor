#include "stm32f4xx_hal.h"
#include "log/log.hpp"

// Value from linker script: stack end address
extern "C" {
    extern volatile uintptr_t _sstack;
}

namespace {

// constexpr uintptr_t GUARD_SIZE = 32;

// Base address of MPU region - should be aligned to 32 bytes
// Stack grows downwards, so we add GUARD_SIZE to the stack start address
// to use the last 32 bytes of the stack as a guard region
uintptr_t base = reinterpret_cast<uintptr_t>(&_sstack) & 0xFFFF'FFE0;
// uintptr_t base = 0x2000f000;
//     (reinterpret_cast<uintptr_t>(&_sstack) + GUARD_SIZE) & 0xFFFF'FFE0;
}

/// Init MPU to detect stack overflow
void init_mpu() {
    
    MPU_Region_InitTypeDef MPU_InitStruct = {};

    HAL_MPU_Disable();

    logging::debug("MPU base address: {:#x}", base);

    MPU_InitStruct.Enable           = MPU_REGION_ENABLE;
    MPU_InitStruct.Number           = MPU_REGION_NUMBER0;
    MPU_InitStruct.BaseAddress      = base;
    MPU_InitStruct.Size             = MPU_REGION_SIZE_128B;
    MPU_InitStruct.SubRegionDisable = 0x00;
    MPU_InitStruct.TypeExtField     = MPU_TEX_LEVEL0;
    MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
    MPU_InitStruct.DisableExec      = MPU_INSTRUCTION_ACCESS_DISABLE;
    MPU_InitStruct.IsShareable      = MPU_ACCESS_NOT_SHAREABLE;
    MPU_InitStruct.IsCacheable      = MPU_ACCESS_NOT_CACHEABLE;
    MPU_InitStruct.IsBufferable     = MPU_ACCESS_NOT_BUFFERABLE;

    HAL_MPU_ConfigRegion(&MPU_InitStruct);

    HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

    // Enable MemManage fault
    SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA_Msk;
}
