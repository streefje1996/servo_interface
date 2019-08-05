#pragma once

namespace r2d2::servo_interface {
    struct pwm_s {
        /**
         * the lenght of one PWM cycle in us
         */
        uint32_t period_us;

		/**
         * duty cycle in percentage
		 * time the PWM signal is active
		 * over given period
         */
        uint8_t duty_cycle;
	};
}
