#pragma once

#include "hwlib.hpp"

namespace r2d2::servo_interface {
    struct pwm_s {
        /**
         * the frequency of one PWM cycle in hz
         */
        uint32_t frequency;

		/**
         * duty cycle in numbers ranging from 0 - 255
		 * where 255 = 100% and 0 = 0%
		 * time the PWM signal is active
		 * over given period
         */
        uint8_t duty_cycle;

		/**
         * time in us how long the signal needs to be high
         */
        uint32_t time_on_us;
	};
}
