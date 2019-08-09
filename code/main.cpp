#include "hwlib.hpp"
#include "sg90_c.hpp"
#include <pca9685_c.hpp>
#include <pwm.hpp>

int main(void) {
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);

    auto sg90_servo = r2d2::servo_interface::sg90_c();
    auto sg90_servo2 = r2d2::servo_interface::sg90_c();
    auto sg90_servo3 = r2d2::servo_interface::sg90_c();
    auto sg90_servo4 = r2d2::servo_interface::sg90_c();
    auto sg90_servo5 = r2d2::servo_interface::sg90_c();

    auto bus = r2d2::i2c::i2c_bus_c(
        r2d2::i2c::i2c_bus_c::interface::interface_0, 100000);

    r2d2::servo_interface::pca9685_c servos(bus, 0x40);

    servos.add_servo(sg90_servo, sg90_servo2, sg90_servo3, sg90_servo4,
                     sg90_servo5);

    for (unsigned int i = 0; i < 5; i++) {
        servos.set_angle(i, -90);
    }

	

    for (;;) {
        hwlib::cout << servos.get_angle(1) << "\n";
        for (unsigned int i = 0; i < 5; i++) {
            servos.add_angle(i, 1);
            hwlib::wait_ms(20);
        }

    }
}