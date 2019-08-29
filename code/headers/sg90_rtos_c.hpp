#pragma once

#include <rtos.hpp>
#include <sg90_c.hpp>

namespace r2d2::servo_interface {
    class sg90_rtos_c : public sg90_c, public rtos::task<> {
    private:
        /**
         * the periodic clock that ticks on the PWM period
         * @internal
         */
        rtos::clock pwm_period;

        /**
         * timer on how long the signal should be active
         * @internal
         */
        rtos::timer on_timer;

        /**
         * pool that holds the angle that needs to be set
         * @internal
         */
        rtos::pool<int16_t> angle_pool;

        /**
         * mutex for protecting the angle_pool
         * @internal
         */
        rtos::mutex angle_mutex;

        /**
         * data pin which the servo is connected to
         * @internal
         */
        hwlib::pin_out &data_pin;

        /**
         * states for the state machine
         * low - pin is logic 0
         * high - pin is logic 1
         * @internal
         */
        enum class states { low, high };

        /**
         * keeps track of the current state
         * @internal
         */
        states state;

    public:
        /**
         * default constructor
         * initializes rtos components and state machine
         *
         * @param data_out - pin wich the servo is connected to
         * @param name - name of this rtos task
         */
        sg90_rtos_c(hwlib::pin_out &data_out, char *name)
            : task(1, name),
              pwm_period(this, (1.f / pwm.frequency * 1'000'000), "pwm_period"),
              on_timer(this, "on_timer"),
              angle_pool("angle pool"),
              angle_mutex("angle mutex"),
              data_pin(data_out),
              state(states::low) {
        }

        /**
         * implements function from sg90_c class
         *
         * sets the angle_pool
         *
         * @param new_angle - the new angle of the servo in degrees from
         * -360 to +360
         */
        void set_angle(const int16_t &new_angle) override;

        /**
         * implements function from sg90_c class
         *
         * sets the angle_pool with current angle added
         *
         * @param new_angle - the desired angle to be added in degrees from
         * -360 to +360
         */
        void add_angle(const int16_t &adding_angle) override;

        /**
         * implements function from rtos
         */
        void main() override;
    };
} // namespace r2d2::servo_interface