/**
 * @file evalkit.ino
 * @brief Evaluation Kit example for Arduino
 * This example demonstrates how to use the EvalKit v5 with various animations and displays.
 * @version 0.1
 * @date 2025-08-08
 * @copyright Copyright (c) 2025
 */

#include <Arduino.h>

#include "app_config.h"
#include "app_config_defs.h"
#include "driverv5_board.h"
#include "evalkit_anims.h"
#include "evalkit_displays.h"

constexpr ynv::app::AppConfig_t appConfig = {.displayIndex     = DISPLAY_ATTACHED,
                                             .supplyVoltage    = SUPPLY_VOLTAGE,
                                             .activeDriving    = ACTIVE_DRIVING,
                                             .analogResolution = ANALOG_RESOLUTION,
                                             .wireAddress      = WIRE_ADDRESS};

auto& board    = ynv::driverv5::Board::getInstance();
auto& displays = ynv::ecd::EvalkitDisplays::getInstance();
auto& anims    = ynv::anim::EvalkitAnims::getInstance();

void setup()
{
    displays.init(&appConfig);  // Initialize the ECD displays
    board.init(&appConfig);     // Initialize the board
    anims.init(&appConfig);     // Initialize the animations for the attached display

    board.getButtons().registerCallback(onButtonPressed);
    anims.registerStateChangeCallback(onAnimStateChanged);
}

void loop()
{
    board.handleEvents();             // Handle button events
    anims.getCurrentAnim().update();  // Update the current animation
    delay(10);
}

/******* callbacks **********/
void onButtonPressed(ynv::driverv5::Buttons::ButtonPress_t buttonEvent)
{
    switch (buttonEvent)
    {
        case ynv::driverv5::Buttons::BTN_START_PRESSED:
        {
            Serial.println("BTN_START_PRESSED");
            anims.getCurrentAnim().changeState();
        }
        break;

        case ynv::driverv5::Buttons::BTN_START_LONG_PRESSED:
        {
            Serial.println("BTN_START_LONG_PRESSED");
            anims.getCurrentAnim().abort();
        }
        break;

        case ynv::driverv5::Buttons::BTN_UP_PRESSED:
        {
            Serial.println("BTN_UP_PRESSED");
            ynv::anim::EvalkitAnims::Anim_t nextAnim = anims.next();
            Serial.println(anims.getAnimName(nextAnim).c_str());
            board.getLEDArray().show(((unsigned int)nextAnim) + 1);
        }
        break;
        case ynv::driverv5::Buttons::BTN_DOWN_PRESSED:

        {
            Serial.println("BTN_DOWN_PRESSED");
            ynv::anim::EvalkitAnims::Anim_t previousAnim = anims.previous();
            Serial.println(anims.getAnimName(previousAnim).c_str());
            board.getLEDArray().show(((unsigned int)previousAnim) + 1);
            // board.getLEDArray().show((unsigned int)anims.previous());
        }
        break;

        default:
            break;
    }
}

void onAnimStateChanged(ynv::anim::AnimBase::State_t state)
{
    switch (state)
    {
        case ynv::anim::AnimBase::State_t::IDLE:
            Serial.println("State_t::IDLE");
            board.getRGBLED().blue();  // Set RGB LED to blue when idle
            break;

        case ynv::anim::AnimBase::State_t::RUNNING:
            Serial.println("State_t::RUNNING");
            board.getRGBLED().green();  // Set RGB LED to green when running
            break;

        case ynv::anim::AnimBase::State_t::PAUSED:
            Serial.println("State_t::PAUSED");
            board.getRGBLED().red();  // Set RGB LED to red when paused
            break;

        case ynv::anim::AnimBase::State_t::COMPLETED:
            Serial.println("State_t::COMPLETED");
            break;

        case ynv::anim::AnimBase::State_t::ABORTED:
            Serial.println("State_t::ABORTED");
            break;

        case ynv::anim::AnimBase::State_t::READY:
            Serial.println("State_t::READY");
            break;

        default:
            break;
    }
}