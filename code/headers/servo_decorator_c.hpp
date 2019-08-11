#pragma once

#include <servo_c.hpp>

namespace r2d2::servo_interface {
    class servo_decorator_c : public servo_c {
    private:
        /*
         * servo component for decorating
         * @internal
         */
        servo_c &component;

    public:
        /*
         * constructor for initialising the component
         *
         * @param servo - servo for decorating
         */
        servo_decorator_c(servo_c &servo) : component(servo) {
        }

        /**
         * implements function from servo_c class
         *
         * sets the angle and the pwm accordingly to the servo
         *
         * @param new_angle - the new angle of the servo
         */
        virtual void set_angle(const int16_t &new_angle) override;

        /**
         * implements function from servo_c class
         *
         * add to the current angle of the servo
         * and update the pwm accordingly
         *
         * @param adding_angle - the desired angle to be added
         */
        virtual void add_angle(const int16_t &adding_angle) override;
    };
} // namespace r2d2::servo_interface