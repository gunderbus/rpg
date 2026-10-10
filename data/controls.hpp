#include <SFML/Window.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#pragma once

#ifndef CONTROLS_HPP
#define CONTROLS_HPP

// Your control-related code goes here
namespace ctrl {
    float getAxisPosition(unsigned int axis) {
        return sf::Joystick::getAxisPosition(0, static_cast<sf::Joystick::Axis>(axis));
    }

    float getAxisPosition(unsigned int axis, unsigned int joystickId) {
        return sf::Joystick::getAxisPosition(joystickId, static_cast<sf::Joystick::Axis>(axis));
    }

    bool isButtonPressed(unsigned int button) {
        return sf::Joystick::isButtonPressed(0, button);
    }

    bool isButtonPressed(unsigned int button, unsigned int joystickId) {
        return sf::Joystick::isButtonPressed(joystickId, button);
    }

    float getMouseX() {
        return static_cast<float>(sf::Mouse::getPosition().x);
    }

    float getMouseY() {
        return static_cast<float>(sf::Mouse::getPosition().y);
    }
}

#endif // CONTROLS_HPP