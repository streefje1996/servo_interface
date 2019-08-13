#include <hwlib.hpp>
#include <pca9685_c.hpp>
#include <pwm.hpp>
#include <servo_led_c.hpp>
#include <servo_logger_c.hpp>
#include <servo_mirror_c.hpp>
#include <sg90_c.hpp>

int main(void) {
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);

    auto sg90 = r2d2::servo_interface::sg90_c();

    auto servo0 = r2d2::servo_interface::servo_mirror_c(sg90);

    auto servo1 = r2d2::servo_interface::sg90_c();

    auto logger0 = r2d2::servo_interface::servo_logger_c(servo0);
    auto logger1 = r2d2::servo_interface::servo_logger_c(servo1);

    auto pin0 = hwlib::target::pin_out(hwlib::target::pins::d2);
    auto pin1 = hwlib::target::pin_out(hwlib::target::pins::d3);

    auto slow0 = r2d2::servo_interface::servo_led_c(logger0, pin0);
    auto slow1 = r2d2::servo_interface::servo_led_c(logger1, pin1);

    auto bus = r2d2::i2c::i2c_bus_c(
        r2d2::i2c::i2c_bus_c::interface::interface_0, 100000);

    r2d2::servo_interface::pca9685_c servos(bus, 0x40);

    servos.add_servo(slow0, slow1);

    for (unsigned int i = 0; i < 2; i++) {
        servos.set_angle(i, -90);
    }

    for (;;) {

        for (unsigned int i = 0; i < 2; i++) {
            servos.set_angle(i, 90);
            hwlib::wait_ms(700);
        }
    }
}