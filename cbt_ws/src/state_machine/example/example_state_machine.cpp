//
// Created by kira on 05.09.2020.
//

#include "state_machine.h"

#include <iostream>
#include <utility>

using namespace cock_and_ball::state_machine;

class IH2O : public IState {
 public:
    IH2O(std::shared_ptr<SignalQueue> shared_ptr) : IState(shared_ptr) {}
    void execute() override {
        _signal_q->emit(name());
    }
};

class Water : public IH2O {
 public:
    Water(std::shared_ptr<SignalQueue> shared_ptr) : IH2O(shared_ptr) {}
    [[nodiscard]] std::string name() const override {
        return "Water";
    }
};

class Ice : public IH2O {
 public:
    Ice(std::shared_ptr<SignalQueue> shared_ptr) : IH2O(shared_ptr) {}
    [[nodiscard]] std::string name() const override {
        return "Ice";
    }
};

class Steam : public IH2O {
 public:
    Steam(std::shared_ptr<SignalQueue> shared_ptr) : IH2O(shared_ptr) {}
    [[nodiscard]] std::string name() const override {
        return "Steam";
    }
};

class Void : public IH2O {
 public:
    Void(std::shared_ptr<SignalQueue> shared_ptr) : IH2O(shared_ptr) {}
    [[nodiscard]] std::string name() const override {
        return "Void";
    }
};

int main(int argc, char **argv) {
    (void) argc;
    (void) argv;
    auto signal_q = std::make_shared<SignalQueue>();

    auto water = std::make_shared<Water>(signal_q);
    auto ice = std::make_shared<Ice>(signal_q);
    auto steam = std::make_shared<Steam>(signal_q);
    auto voidness = std::make_shared<Void>(signal_q);

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
        std::move(transitions),
        signal_q
    };

    std::cout << "available commands: heat_up, cool_down, flush" << std::endl;
    std::cout << "current state: " << bowl_of_water.current()->name() << std::endl;

    std::string cmd{};
    while (std::cin >> cmd) {
        bowl_of_water.change_state(cmd);
        std::cout << "current state: " << bowl_of_water.current()->name() << std::endl;
        bowl_of_water.current()->execute();
        while (signal_q->ready()) {
            std::cout << "signal: " << signal_q->dispatch_signal() << std::endl;
        }
    }
    return 0;
}
