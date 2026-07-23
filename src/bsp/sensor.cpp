#include "sensor.hpp"
// #include "stm32f4xx_hal.h"
#include "scd4x_i2c.h"
#include "sensirion_i2c.h"
#include "sensirion_common.h"

namespace {

// Dosn't include r/w bit
constexpr uint8_t SCD41_I2C_ADDRESS = 0x62 << 1;
bsp::Sensor::Error encode_error(uint16_t error_code);

}

namespace bsp {

Sensor::Sensor() {
    
    scd4x_init(SCD41_I2C_ADDRESS);
}

Sensor::Error Sensor::trigger_measurement(){

    return encode_error(scd4x_measure_single_shot());
}

std::expected<Sensor::Data, Sensor::Error> Sensor::read(){

    uint16_t co2;
    int32_t temp;
    int32_t hum;

    auto error = encode_error(scd4x_read_measurement(&co2, &temp, &hum));
    if (error == Error::NoError) {
        return Data{.co2 = co2, .temperature = temp / 1000.0, .humidity = hum / 1000.0};
    }
    else {
        return std::unexpected(error);
    }
}

etl::string<20> Sensor::error_name(Error error) {
    switch (error)
    {
    case Error::NoError:
        return "OK";
    case Error::CrcError:
        return "CRC error";
    case Error::I2cBusError:
        return "I2C bus error";
    case Error::I2cNackError:
        return "I2C NACK error";
    case Error::ByteNumError:
        return "Byte number error";
    case Error::UnknownError:
        return "Unknown error";
    }
}

}

namespace {

bsp::Sensor::Error encode_error(uint16_t error_code) {

    switch (error_code)
    {
    case NO_ERROR:
        return bsp::Sensor::Error::NoError;
    case CRC_ERROR:
        return bsp::Sensor::Error::CrcError;
    case I2C_BUS_ERROR:
        return bsp::Sensor::Error::I2cBusError;
    case I2C_NACK_ERROR:
        return bsp::Sensor::Error::I2cNackError;
    case BYTE_NUM_ERROR:
        return bsp::Sensor::Error::ByteNumError;
    default:
        return bsp::Sensor::Error::UnknownError;
    }
}

}
