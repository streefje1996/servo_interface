#pragma once

#include "servo_c.hpp"

namespace r2d2::servo_interface {
    class sg90_c : public servo_c {
        /**
         * the PWM frequency this servo operates on in Hz
         * @internal
         */
        const uint32_t pwm_frequency_hz = 50;

        /**
         * the maximum rotation this servo can turn
         * @internal
         */
        const uint8_t max_rotation = 90;

        /**
         * the minumum rotation this servo can turn
         * @internal
         */
        const int8_t min_rotation = -90;

        /**
         * the time the signal should be high
         * to get to the max rotation
         * @internal
         */
        const uint32_t max_time_on_us = 2'500;

        /**
         * the time the signal should be high
         * to get to the min rotation
         * @internal
         */
        const uint32_t min_time_on_us = 700;

        /**
         * the ratio for converting rotation to time in us
         * @internal
         */
        const double rotation_time_ratio =
            (max_time_on_us - min_time_on_us) / (max_rotation - min_rotation);

    public:
        /**
         * basic contructor that sets default frequency for pwm from servo_c
         * class
         */
        sg90_c() {
            pwm.frequency = pwm_frequency_hz;
        }

        /**
         * implements function from servo_c class
         *
         * sets the angle and the pwm accordingly to the servo
         *
         * @param new_angle - the new angle of the servo
         */
        void set_angle(const int16_t &new_angle) override;

        /**
         * implements function from servo_c class
         *
         * add to the current angle of the servo
         * and update the pwm accordingly
         *
         * @param adding_angle - the desired angle to be added
         */
        void add_angle(const int16_t &adding_angle) override;
    };
} // namespace r2d2::servo_interface