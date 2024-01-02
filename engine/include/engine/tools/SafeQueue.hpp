/*
** EPITECH PROJECT, 2023
** RType
** File description:
** No file there , just an epitech header example
*/

#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

namespace RType {

    template<typename T>
    class SafeQueue {
    private:
        std::queue<T> _queue;
        std::mutex _mutex;
        std::condition_variable _condition;

    public:
        explicit SafeQueue() = default;

        /**
         * Push a value a the end of the _queue
         *a
         * @param value the value to push
         */
        void push(T value) {
            std::lock_guard lock(_mutex);

            _queue.push(value);
            _condition.notify_one();
        }

        /**
         * Pop a value if exists
         *
         * @param value the value if exists
         * @return if value exists
         */
        bool safePop(T &value) {
            std::lock_guard lock(_mutex);

            if (_queue.empty()) return false;
            value = _queue.front();
            _queue.pop();
            return true;
        }

        /**
         * Pop a value or wait
         *
         * @return the value
         */
        T pop() {
            std::unique_lock lock(_mutex);

            _condition.wait(lock, [this] { return !_queue.empty(); });
            T value = _queue.front();

            _queue.pop();
            return value;
        }

        /**
         * Check _queue emptiness
         *
         * @return if the _queue is empty
         */
        [[nodiscard]] bool isEmpty() {
            std::lock_guard lock(_mutex);

            return _queue.empty();
        }
    };

}
