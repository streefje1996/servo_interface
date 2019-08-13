#pragma once

#include <i2c_bus.hpp>
#include <servo_c.hpp>

namespace r2d2::servo_interface {
    class pca9685_c {
    private:
        /**
         * the i2c bus used to communicate with the pca9685
         * @internal
         */
        r2d2::i2c::i2c_bus_c &i2c_bus;

        /**
         * the i2c address of the pca9685
         * @internal
         */
        uint8_t slave_address;

        /**
         * a collection of all the servos
         * the maximum of servos that can be connected to the pca9685 is 16
         * @internal
         */
        servo_c *servos[16];

        /**
         * keeps track of the number of servos that exists
         * @internal
         */
        uint8_t servo_index;

        /**
         * holds the command for setting the leds
         * which is build up like this
         * 0. LEDn_OFF_L register
         * 1. LEDn_OFF_L value
         * 2. LEDn_OFF_H value
         * @internal
         */
        uint8_t led_cmd[3];

        /**
         * location of the mode 1 register
         * @internal
         */
        const uint8_t reg_mode_1 = 0;

        /**
         * location of the first LED_OFF_L register
         * @internal
         */
        const uint8_t reg_led0_off_l = 8;

        /**
         * location of the pre scale register
         * @internal
         */
        const uint8_t reg_pre_scale = 254;

        /**
         * default command for the startup that is used
         * bin(0010 0000)
         * MSB - RESTART, EXTCLK, AI, SLEEP, SUB1, SUB2, SUB3, ALLCALL - LSB
         * @internal
         */
        const uint8_t default_startup_cmd = 32;

        /**
         * the amount of counts in one cycle on the pca9685
         * @internal
         */
        const uint16_t counts = 4096;

        /**
         * sends the internal led_cmd over the bus
         *
         * @param id - the id of the servo that needs to be sent
         * @internal
         */
        void send_to_bus(const uint8_t &id);

        /**
         * an overloaded function used to unpack the parameter pack
         *
         * @param servo - the first servo in the parameter list
         * @param attributes - the remaining parameters
         * @internal
         */
        template <typename T, typename... A>
        void unpack_add_servo(T &servo, A &... attributes) {
            unpack_add_servo(servo);
            unpack_add_servo(attributes...);
        };

        /**
         * an overloaded function used to add the unpacked parameter (servo)
         * to the internal collection of servos
         * sets the pre scaler and starts the pca9685
         *
         * @param servo - a servo that is derived from servo_c
         * @internal
         */
        template <typename T>
        void unpack_add_servo(T &servo) {
            if (servo_index < 16) {
                servos[servo_index++] = &servo;

                uint8_t pre_scale_cmd[2] = {
                    reg_pre_scale,
                    static_cast<uint8_t>(
                        25'000'000.f / (servo.get_pwm().frequency * counts) -
                        1)};
                i2c_bus.write(slave_address, pre_scale_cmd, 2);
                hwlib::wait_ms(10);

                uint8_t startup_cmd[2] = {reg_mode_1, 32};
                i2c_bus.write(slave_address, startup_cmd, 2);
                hwlib::wait_ms(10);
            } else {
                hwlib::cout << "servo list full \n";
            }
        };

    public:
        /**
         * constructor for the pca9685_c class
         *
         * @param bus - an i2c bus
         * @param address - the i2c address of the pca9685
         */
        pca9685_c(r2d2::i2c::i2c_bus_c &bus, const uint8_t &address)
            : i2c_bus(bus), slave_address(address), servo_index(0) {
        }

        /**
         * sets the angle to the selected servo if in range
         * and updates the pca9685 accordingly
         *
         * @param id - the id of the servo that needs to be selected
         * @param new_angle - the angle you want the selected servo to turn to
         */
        void set_angle(const uint8_t &id, const int16_t &new_angle);

        /**
         * returns the angle of the selected servo
         *
         * @param id - the id of the servo that needs to be selected
         * @return the angle the selected servo is at
         */
        int16_t get_angle(const uint8_t &id);

        /**
         * adds to the selected servo's angle if possible
         *
         * @param id - the id of the servo that needs to be selected
         * @param added_angle - the angle you want to add to the selected servo
         */
        void add_angle(const uint8_t &id, const int16_t &added_angle);

        /**
         * adds the servo to the servo collection
         * this function is parameter packed wich allows you to add as many as
         * servos you want in one function call
         * example: pca9685.add_servo(servo1,servo2,servo3)
         *
         * @param attributes - parameter pack of servos
         */
        template <typename... A>
        void add_servo(A &... attributes) {
            unpack_add_servo(attributes...);
        }
    };
} // namespace r2d2::servo_interface