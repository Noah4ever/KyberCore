#include "led_control.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#define LED_PIN 0 // Typically the onboard LED pin on the Raspberry Pi Pico

// Function to initialize the LED (set the LED pin to output mode)
bool init_led()
{
  // Initialize the CYW43 Wi - Fi chip(needed to use the LED on Pico W)
  if (cyw43_arch_init())
  {
    return false; // Initialization failed
  }
  return true;
}

// Function to turn the LED on
void turn_led_on()
{
  cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
}

// Function to turn the LED off
void turn_led_off()
{
  cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
}

// Function to toggle the LED state (on/off)
void toggle_led()
{
  static bool led_state = false; // Start with the LED off

  led_state = !led_state; // Toggle the state

  cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_state); // Set the LED pin based on the new state
}
