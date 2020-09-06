//
// Created by kira on 05.09.2020.
//

#include "state_machine.h"

#include <iostream>
#include <utility>

using namespace cock_and_ball;

class Water : public IState {
 public:
    [[nodiscard]] std::string name() const override {
        return "Water";
    }
};

class Ice : public IState {
 public:
    [[nodiscard]] std::string name() const override {
        return "Ice";
    }
};

class Steam : public IState {
 public:
    [[nodiscard]] std::string name() const override {
        return "Steam";
    }
};

int main(int argc, char **argv) {
    auto water = std::make_shared<Water>();
    auto ice = std::make_shared<Ice>();
    auto steam = std::make_shared<Steam>();

    StateMachine bowl_of_water{water,
        std::make_unique<StateTransitions>(
            StateTransitions::MultiMap{
                {
                    {"heat_up", {ice, water}},
                    {"heat_up", {water, steam}},
                    {"heat_up", {steam, steam}},
                    {"cool_down", {steam, water}},
                    {"cool_down", {water, ice}},
                    {"cool_down", {ice, ice}}
                }
            })
    };

    std::cout << "available commands: heat_up, cool_down" << std::endl;
    std::cout << "current state: " << bowl_of_water.current()->name() << std::endl;

    std::string cmd{};
    while (std::cin >> cmd) {
        bowl_of_water.change_state(cmd);
        std::cout << "current state: " << bowl_of_water.current()->name() << std::endl;
    }
    return 0;
}
