#include "Input.h"
#include <SFML/Window/Keyboard.hpp>
#include <unordered_map>
#include <vector>

namespace
{
    std::unordered_map<Action, std::vector<sf::Keyboard::Key>> keyMap =
    {
        {Action::Throttle,   {sf::Keyboard::W, sf::Keyboard::Up}},
        {Action::Brake,     {sf::Keyboard::S, sf::Keyboard::Down}},
        {Action::SteerLeft, {sf::Keyboard::A, sf::Keyboard::Left}},
        {Action::SteerRight,{sf::Keyboard::D, sf::Keyboard::Right}},
        {Action::HandBrake, {sf::Keyboard::E}},
        {Action::Pause,     {sf::Keyboard::Escape}},
        {Action::GearAuto,  {sf::Keyboard::E}},
        {Action::GearUp,    {sf::Keyboard::LShift}},
        {Action::GearDown,  {sf::Keyboard::LControl}}
    };

    std::unordered_map<Action, bool> curr;
    std::unordered_map<Action, bool> prev;
}

void Input::update()
{
    prev = curr;

    for (auto& [action, keys] : keyMap)
    {
        bool pressed = false;
        for (auto key : keys)
        {
            if (sf::Keyboard::isKeyPressed(key))
            {
                pressed = true;
                break;
            }
        }
        curr[action] = pressed;
    }
}

bool Input::isDown(Action action)
{
    return curr[action];
}

bool Input::isPressed(Action action)
{
    return curr[action] && !prev[action];
}

/*
plans :
    add ability to addBinding
    add clearing Bindings
    For game menu

*/