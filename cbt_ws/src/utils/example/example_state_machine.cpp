//
// Created by kira on 05.09.2020.
//

#include "state_machine.hpp"

#include <iostream>
#include <utility>

using namespace cock_and_ball;

class IWaterState {
 public:
    [[nodiscard]] virtual std::string name() const = 0;
    explicit IWaterState(std::shared_ptr<StateMachine<IWaterState>> state_machine)
        : _machine(std::move(state_machine)) {}
    virtual void heat_up() = 0;
    virtual void cool_down() = 0;

 protected:
    std::shared_ptr<StateMachine<IWaterState>> _machine;
};

class Water : public IWaterState {
 public:
    explicit Water(std::shared_ptr<StateMachine<IWaterState>> state_machine)
        : IWaterState(std::move(state_machine)) {}
    [[nodiscard]] std::string name() const override {
        return "Water";
    }
    void heat_up() override;
    void cool_down() override;
};

class Ice : public IWaterState {
 public:
    explicit Ice(std::shared_ptr<StateMachine<IWaterState>> state_machine)
        : IWaterState(std::move(state_machine)) {}
    [[nodiscard]] std::string name() const override {
        return "Ice";
    }
    void heat_up() override;
    void cool_down() override;
};

class Steam : public IWaterState {
 public:
    explicit Steam(std::shared_ptr<StateMachine<IWaterState>> state_machine)
        : IWaterState(std::move(state_machine)) {}
    [[nodiscard]] std::string name() const override {
        return "Steam";
    }
    void heat_up() override;
    void cool_down() override;
};

void Water::heat_up() {
    _machine->set_current_state(std::make_unique<Steam>(_machine));
}
void Water::cool_down() {
    _machine->set_current_state(std::make_unique<Ice>(_machine));
}

void Steam::heat_up() {}
void Steam::cool_down() {
    _machine->set_current_state(std::make_unique<Water>(_machine));
}

void Ice::heat_up() {
    _machine->set_current_state(std::make_unique<Water>(_machine));
}
void Ice::cool_down() {}

int main(int argc, char **argv) {
    std::shared_ptr<StateMachine<IWaterState>> bowl_of_water{new StateMachine<IWaterState>{}};
    bowl_of_water->set_current_state(std::make_unique<Water>(bowl_of_water));

    std::cout << "current state: " << bowl_of_water->current().name() << std::endl;

    std::string cmd{};
    while (std::cin >> cmd) {
        if (cmd == "heat") {
            bowl_of_water->current().heat_up();
        } else if (cmd == "cool") {
            bowl_of_water->current().cool_down();
        }
        std::cout << "current state: " << bowl_of_water->current().name() << std::endl;
    }
    return 0;
}
