#include "hwlib.hpp"
#include "sg90_c.hpp"
#include <pwm.hpp>

int main(void) {
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);

    auto sg90_servo = r2d2::servo_interface::sg90_c();

    r2d2::servo_interface::servo_c *servo = &sg90_servo;

    auto pwm_0 = r2d2::pwm_lib::pwm_c(0);

    pwm_0.set_global_pwm_clock(servo->get_pwm().frequency,
                               r2d2::pwm_lib::clocks::CLOCKA);

    pwm_0.select_frequency(r2d2::pwm_lib::frequencies::CLOCKA);

    servo->set_angle(90);

    for (;;) {

        servo->set_angle(90);
        hwlib::cout << servo->get_pwm().time_on_us << "    "
                    << servo->get_angle() << "\n";
        pwm_0.set_duty_cycle(servo->get_pwm().duty_cycle);
        hwlib::wait_ms(1000);


		servo->set_angle(-90);
        hwlib::cout << servo->get_pwm().time_on_us << "    "
                    << servo->get_angle() << "\n";
        pwm_0.set_duty_cycle(servo->get_pwm().duty_cycle);
        hwlib::wait_ms(1000);

		servo->set_angle(0);
        hwlib::cout << servo->get_pwm().time_on_us << "    "
                    << servo->get_angle() << "\n";
        pwm_0.set_duty_cycle(servo->get_pwm().duty_cycle);
        hwlib::wait_ms(1000);
    }
}