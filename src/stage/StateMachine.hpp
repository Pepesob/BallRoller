
#pragma once
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
    virtual ~StateMachine() {
        delete this->prev_state;
        delete this->current_state;
        delete this->next_state;
    }
    StateMachine() = default;
    explicit StateMachine(State* initial_state): current_state(initial_state) {}

    virtual void update() {
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
                delete this->prev_state;
                this->prev_state = this->current_state;
                this->current_state = this->next_state;
                this->next_state = nullptr;
                this->procedure = INIT;
                break;
            }
        }
    }

    virtual void switchState(State* new_state) {
        if (!new_state) {
            throw std::runtime_error("New state cannot be null!");
        }
        this->next_state = new_state;
        this->procedure = NEXT;
    }

    virtual void setInitialState(State* initial_state) {
        this->procedure = INIT;
        this->current_state = initial_state;
    }

    bool shutdown = false;

private:
    enum StateMachineProcedure {
        INIT, UPDATE, NEXT
    };

    State* prev_state = nullptr;
    State* current_state = nullptr;
    State* next_state = nullptr;
    StateMachineProcedure procedure = INIT;
};
