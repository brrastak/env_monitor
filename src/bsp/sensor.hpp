#pragma once

#include "etl/chrono.h"
#include "etl/string.h"
#include <expected>

using namespace etl::chrono_literals;

namespace bsp
{

constexpr auto MEASUREMENT_DURATION = 5_s;

class Sensor
{
public:
    Sensor();

    struct Data {
        double co2;
        double temperature;
        double humidity;
    };

    enum class Error {
        NoError,
        CrcError,
        I2cBusError,
        I2cNackError,
        ByteNumError,
        UnknownError,
    };

    /// Should be paused for MEASUREMENT_DURATION time to let sensor perform data measurement
    Error trigger_measurement();
    std::expected<Data, Error> read();

    static etl::string<20> error_name(Error);
};

}
