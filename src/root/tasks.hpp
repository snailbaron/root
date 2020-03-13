#pragma once

#include <functional>
#include <utility>
#include <vector>

enum class TaskState {
    Running,
    Finished,
};

class TaskPool {
public:
    void push(std::function<TaskState(float)>&& task)
    {
        _tasks.push_back(std::move(task));
    }

    void update(float delta)
    {
        for (size_t i = 0; i < _tasks.size();) {
            auto state = _tasks.at(i)(delta);
            if (state == TaskState::Finished) {
                if (i + 1 < _tasks.size()) {
                    std::swap(_tasks.at(i), _tasks.back());
                }
                _tasks.resize(_tasks.size() - 1);
            } else {
                i++;
            }
        }
    }

private:
    std::vector<std::function<TaskState(float)>> _tasks;
};
