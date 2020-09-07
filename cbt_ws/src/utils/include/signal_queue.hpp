//
// Created by kira on 07.09.2020.
//

#ifndef COCK_AND_BALL_CBT_WS_SRC_UTILS_INCLUDE_SIGNAL_QUEUE_HPP_
#define COCK_AND_BALL_CBT_WS_SRC_UTILS_INCLUDE_SIGNAL_QUEUE_HPP_

#include <memory>
#include <deque>


namespace cock_and_ball {
namespace signal {
template<class SignalT>
class SignalQueue {
 public:
    using SharedPtr = std::shared_ptr<SignalQueue>;
    SignalQueue() = default;

    void emit(SignalT &&signal) {
        _q.push_back(std::move(signal));
    }
    SignalT dispatch_signal() {
        auto signal = _q.front();
        _q.pop_front();
        return signal;
    }
    bool ready() const {
        return not _q.empty();
    }
 private:
    std::deque<SignalT> _q;
};
}  // namespace signal
}  // namespace cock_and_ball

#endif //COCK_AND_BALL_CBT_WS_SRC_UTILS_INCLUDE_SIGNAL_QUEUE_HPP_
