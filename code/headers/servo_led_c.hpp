#pragma once

#include <servo_decorator_c.hpp>

namespace r2d2::servo_interface {
    class servo_led_c : public servo_decorator_c {
    private:
        /*
         * the pin to which the led is connected
         * @internal
         */
        hwlib::pin_out &led;

    public:
        /*
         * constructor for initialising the component and led
         *
         * @param servo - servo for decorating
         * @param led_pin - pin where led is connected to
         */
        servo_led_c(servo_c &servo, hwlib::pin_out &led_pin)
            : servo_decorator_c(servo), led(led_pin){};

        /**
         * decorates function from servo_decorator_c class
         *
         * blinks a led before moving the servo
         *
         * @param new_angle - the new angle of the servo in degrees from
         * -360 to +360
         */
        void set_angle(const int16_t &new_angle) override;
    };
} // namespace r2d2::servo_interface