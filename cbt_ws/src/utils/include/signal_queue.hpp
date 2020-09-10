//
// Created by kira on 07.09.2020.
//

#ifndef COCK_AND_BALL_CBT_WS_SRC_UTILS_INCLUDE_SIGNAL_QUEUE_HPP_
#define COCK_AND_BALL_CBT_WS_SRC_UTILS_INCLUDE_SIGNAL_QUEUE_HPP_

#include <memory>
#include <deque>
#include <mutex>


namespace cock_and_ball {
namespace signal {
template<class SignalT>
class SignalQueue {
 public:
    using SharedPtr = std::shared_ptr<SignalQueue>;
    SignalQueue() = default;

    void emit(SignalT &&signal) {
        std::lock_guard q_lock{_mutex};
        _q.push_back(std::move(signal));
    }
    SignalT dispatch_signal() {
        std::lock_guard q_lock{_mutex};
        auto signal = _q.front();
        _q.pop_front();
        return signal;
    }
    bool ready() const {
        std::lock_guard q_lock{_mutex};
        return not _q.empty();
    }
 private:
    std::deque<SignalT> _q;
    std::mutex _mutex;
};
}  // namespace signal
}  // namespace cock_and_ball

#endif //COCK_AND_BALL_CBT_WS_SRC_UTILS_INCLUDE_SIGNAL_QUEUE_HPP_
