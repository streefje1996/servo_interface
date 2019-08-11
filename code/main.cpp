#include <hwlib.hpp>
#include <sg90_c.hpp>
#include <pca9685_c.hpp>
#include <pwm.hpp>
#include <sg90_rtos_c.hpp>

int main(void) {
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);

    auto pin = hwlib::target::pin_out(hwlib::target::pins::d7);

    char one[] = "one";

	auto my_sg90 = r2d2::servo_interface::sg90_rtos_c(pin, one);
    (void)my_sg90;

	r2d2::servo_interface::servo_c *my_servo = &my_sg90;

	my_servo->set_angle(90);

	rtos::run();
}