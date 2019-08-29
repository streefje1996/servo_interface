#pragma once

#include <servo_decorator_c.hpp>

namespace r2d2::servo_interface {
    class servo_logger_c : public servo_decorator_c {
    public:
        /*
         * constructor for initialising the component
         *
         * @param servo - servo for decorating
         */
        servo_logger_c(servo_c &servo) : servo_decorator_c(servo){};

        /**
         * decorates function from servo_decorator_c class
         *
         * sets the angle and the pwm accordingly to the servo
         * and logs it to the console
         *
         * @param new_angle - the new angle of the servo in degrees from
         * -360 to +360
         */
        void set_angle(const int16_t &new_angle) override;

        /**
         * decorates function from servo_decorator_c class
         *
         * add to the current angle of the servo, update the pwm accordingly
         * and logs it to the console
         *
         * @param adding_angle - the desired angle to be added in degrees from
         * -360 to +360
         */
        void add_angle(const int16_t &adding_angle) override;
    };

} // namespace r2d2::servo_interface