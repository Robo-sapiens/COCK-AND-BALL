//
// Created by kira on 05.09.2020.
//

#include "state_machine.hpp"

#include <iostream>

using namespace cock_and_ball;

class IWaterState {
 public:
    const std::string &name() const {
        return _name;
    }
    IWaterState(const std::string &name, std::shared_ptr<StateMachine<IWaterState>> state_machine)
        : _name(name), _machine(state_machine) {}
    virtual void heat_up() = 0;
    virtual void cool_down() = 0;

 private:
    std::string _name;
    std::shared_ptr<StateMachine<IWaterState>> _machine;
};

class Water : public IWaterState {
 public:
    Water(std::shared_ptr<StateMachine<IWaterState>> state_machine)
        : IWaterState("Water", state_machine) {}
    void heat_up() override;
    void cool_down() override;
};

class Ice : public IWaterState {
 public:
    Ice(std::shared_ptr<StateMachine<IWaterState>> state_machine)
        : IWaterState("Ice", state_machine) {}
    void heat_up() override;
    void cool_down() override;
};

class Steam : public IWaterState {
 public:
    Steam(std::shared_ptr<StateMachine<IWaterState>> state_machine)
        : IWaterState("Steam", state_machine) {}
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
