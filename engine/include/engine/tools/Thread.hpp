/*
** EPITECH PROJECT, 2023
** plazza
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <thread>
#include <memory>

#include "../exception/ThreadException.hpp"

namespace RType {

    enum class ThreadStatus {
        Started,
        Running,
        Dead
    };

    class Thread {
    private:
        ThreadStatus _status = ThreadStatus::Dead;
        std::thread _thread;

    public:
        /**
         * Create a new thread
         */
        explicit Thread() = default;

        Thread(Thread&& other) noexcept : _status(other._status) {
            _thread = std::move(other._thread);

            other._status = ThreadStatus::Dead;
        }

        Thread(const Thread &other) = delete;

        /**
         * Execute a function in thread
         *
         * @tparam T_function function type
         * @tparam T_args arguments types
         * @param function function to execute
         * @param args arguments of the function
         */
        template<typename T_function, typename... T_args>
        void run(T_function &&function, T_args &&... args) {
            if (_status != ThreadStatus::Dead)
                throw ThreadException("Thread already running");

            _status = ThreadStatus::Started;
            _thread = std::thread(std::forward<T_function>(function), std::forward<T_args>(args)...);
            _status = ThreadStatus::Running;
        }

        /**
         * Wait for thread to exit
         */
        void wait() {
            if (_status == ThreadStatus::Dead)
                return;

            if (_thread.joinable()) {
                _thread.join();
                _status = ThreadStatus::Dead;
            }
        }

        ~Thread() = default;
    };

}
