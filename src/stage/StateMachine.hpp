
#pragma once
#include <memory>
#include <stdexcept>

class StateMachine;

class State {
public:
    virtual ~State() = default;

    virtual void onInit() = 0;
    virtual void onUpdate() = 0;
    virtual void onNext() = 0;
};


class StateMachine {
public:
    explicit StateMachine(std::unique_ptr<State> initial_state): current_state(std::move(initial_state)) {}

    void update() {
        switch (this->procedure) {
            case INIT: {
                this->current_state->onInit();
                this->procedure = UPDATE;
                break;
            }
            case UPDATE: {
                this->current_state->onUpdate();
                break;
            }
            case NEXT: {
                this->current_state->onNext();
                this->prev_state = std::move(this->current_state);
                this->current_state = std::move(this->next_state);
                this->next_state = nullptr;
                this->procedure = INIT;
                break;
            }
        }
    }

    void switchState(std::unique_ptr<State> new_state) {
        if (!new_state) {
            throw std::runtime_error("New state cannot be null!");
        }
        this->next_state = std::move(new_state);
        this->procedure = NEXT;
    }

    void setInitialState(std::unique_ptr<State> initial_state) {
        this->procedure = INIT;
        this->current_state = std::move(initial_state);
    }

    bool shutdown = false;

private:
    enum StateMachineProcedure {
        INIT, UPDATE, NEXT
    };

    std::unique_ptr<State> prev_state = nullptr;
    std::unique_ptr<State> current_state = nullptr;
    std::unique_ptr<State> next_state = nullptr;
    StateMachineProcedure procedure = INIT;
};
