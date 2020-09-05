//
// Created by kira on 05.09.2020.
//

#include "example_interfaces/action/fibonacci.hpp"

template<class T, size_t (T::*)() const = &T::size>
size_t get_size(T const& t)
{
    return t.size();
}

template<class T, size_t (T::*) = &T::size>
size_t get_size(T const& t)
{
    return t.size;
}

class LOL {
 public:
    size_t size() const {
        return 2;
    }
};

class POP {
 public:
    size_t size = 10;
};

#include <iostream>

int main(int argc, char ** argv) {
    std::cout << get_size(LOL{}) << std::endl;
    std::cout << get_size(POP{}) << std::endl;

    return 0;
}
