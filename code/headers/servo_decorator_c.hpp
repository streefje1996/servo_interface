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
         * sets the angle and the pwm of the component accordingly
         *
         * @param new_angle - the new angle of the component's servo
         */
        virtual void set_angle(const int16_t &new_angle) override;

        /**
         * returns the current angle the component's servo is set to
         *
         * @return the current angle of the component's servo
         */
        virtual int16_t get_angle() override;

        /**
         * implements function from servo_c class
         *
         * add to the current angle of the component's servo
         * and update the pwm accordingly
         *
         * @param adding_angle - the desired angle to be added
         */
        virtual void add_angle(const int16_t &adding_angle) override;

        /**
         * returns the PWM to set the component's servo to the set angle
         *
         * @return the current pwm of the component's servo
         */
        virtual pwm_s get_pwm() override;
    };
} // namespace r2d2::servo_interface