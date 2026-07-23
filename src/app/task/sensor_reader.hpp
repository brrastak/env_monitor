// Task to blink the LED to indicate that the system is alive.
#pragma once

#include "bsp/sensor.hpp"
#include "rtos/rtos.hpp"
#include "rtos/task.hpp"
#include "etl/chrono.h"
#include "log/log.hpp"

using namespace etl::chrono_literals;

namespace task {

class SensorReader : public rtos::Task {
public:
    SensorReader(bsp::Sensor& sensor, rtos::TaskPriority priority, size_t stackSize = rtos::MIN_STACK_SIZE)
        : Task{priority, stackSize}, m_sensor{sensor} {}

protected:
    void runner() override {
        while (true) {

            auto error = m_sensor.trigger_measurement();

            if (error != bsp::Sensor::Error::NoError) {

                logging::error("Trigger measurement error: {}", bsp::Sensor::error_name(error));
                rtos::delay(1_s);
                continue;
            }

            rtos::delay(bsp::MEASUREMENT_DURATION);
            
            auto result = m_sensor.read();
            if (! result.has_value()) {

                logging::error("Sensor data read error: {}", bsp::Sensor::error_name(result.error()));
                rtos::delay(1_s);
                continue;
            }

            auto value = result.value();
            logging::info("CO2: {} Temperature: {} Humiduty: {}", 
                value.co2, 
                value.temperature, 
                value.humidity
            );

            rtos::delay(15_s);
        }
    }

    rtos::TaskName name() const override {
        return "SENSOR_READER";
    }

private:
    bsp::Sensor& m_sensor;
};

}
