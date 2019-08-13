#pragma once

#include <servo_decorator_c.hpp>

namespace r2d2::servo_interface {
    class servo_mirror_c : public servo_decorator_c {
    public:
        /*
         * constructor for initialising the component
         *
         * @param servo - servo for decorating
         */
        servo_mirror_c(servo_c &servo) : servo_decorator_c(servo) {
        }

        /**
         * implements function from servo_decorator_c class
         *
         * sets the angle mirrored and the pwm accordingly to the servo
         *
         * @param new_angle - the new mirrored angle of the servo
         */
        void set_angle(const int16_t &new_angle) override;

        /**
         * implements function from servo_decorator_c class
         *
         * add to the current mirrored angle of the servo
         * and update the pwm accordingly
         *
         * @param adding_angle - the desired mirrored angle to be added
         */
        void add_angle(const int16_t &adding_angle) override;
    };
} // namespace r2d2::servo_interface