#pragma once

#include "pwm_s.hpp"

namespace r2d2::servo_interface {
    class servo_c {
    protected:
        /**
         * the current angle the servo is at
		 * this value can be anywhere between -360 to +360
         */
        int16_t angle;

		/**
         * the pwm needed to put the servo at the desired angle
         */
        pwm_s pwm;

    public:
        /**
         * sets the angle and the pwm accordingly to the servo
         *
		 * @param new_angle - the new angle of the servo
         */
        virtual void set_angle(const int16_t &new_angle) = 0;

		/**
         * returns the current angle the servo is set to
         */
        int16_t get_angle() {
            return angle;
        }

		/**
         * add to the current angle of the servo
		 * and update the pwm accordingly
         *
         * @param adding_angle - the desired angle to be added
         */
        virtual void add_angle(const int16_t &adding_angle) = 0;

		/**
         * returns the desired pwm to set the given angle
         */
		pwm_s get_pwm() {
            return pwm;
        }

    };
} // namespace r2d2_servo_interface