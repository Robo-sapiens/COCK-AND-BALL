//
// Created by kira on 05.09.2020.
//

#include "state_machine.h"

#include <iostream>
#include <utility>

using namespace cock_and_ball::state_machine;

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

class Void : public IState {
 public:
    [[nodiscard]] std::string name() const override {
        return "Void";
    }
};

int main(int argc, char **argv) {
    (void) argc;
    (void) argv;
    auto water = std::make_shared<Water>();
    auto ice = std::make_shared<Ice>();
    auto steam = std::make_shared<Steam>();
    auto voidness = std::make_shared<Void>();

    auto transitions = std::make_unique<StateTransitions>(
        StateTransitions::MultiMap{
            {"heat_up", {ice, water}},
            {"heat_up", {water, steam}},
            {"heat_up", {steam, steam}},
            {"cool_down", {steam, water}},
            {"cool_down", {water, ice}},
            {"cool_down", {ice, ice}}
        },
        StateCollection{
            water, ice, steam, voidness
        });
    transitions->extend_with("flush", std::regex{"\\w*"}, voidness);

    StateMachine bowl_of_water{
        water,
        std::move(transitions)
    };

    std::cout << "available commands: heat_up, cool_down, flush" << std::endl;
    std::cout << "current state: " << bowl_of_water.current()->name() << std::endl;

    std::string cmd{};
    while (std::cin >> cmd) {
        bowl_of_water.change_state(cmd);
        std::cout << "current state: " << bowl_of_water.current()->name() << std::endl;
    }
    return 0;
}
