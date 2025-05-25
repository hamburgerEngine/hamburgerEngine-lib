#ifdef __MINGW32__ || defined(__SWITCH__)
#include "State.h"
#include "SubState.h"
#include "Engine.h"
#include "../graphics/Sprite.h"
#include <iostream>
#else
#include <core/State.h>
#include <core/SubState.h>
#include <core/Engine.h>
#include <graphics/Sprite.h>
#include <iostream>
#endif

void State::openSubState(SubState* subState) {
    Log::getInstance().info("State::openSubState called");
    subState->setParentState(this);
    _subStates.push_back(subState);
    subState->create();
}

void State::closeSubState() {
    if (!_subStates.empty()) {
        SubState* subState = _subStates.back();
        if (subState) {
            subState->destroy();
            delete subState;
            _subStates.pop_back();
        }
    }
}

void State::updateSubState(float deltaTime) {
    if (!_subStates.empty()) {
        _subStates.back()->update(deltaTime);
    }
}

void State::renderSubState() {
    if (!_subStates.empty()) {
        _subStates.back()->render();
    }
}

void State::update(float deltaTime) {
    if (!_subStates.empty()) {
        _subStates.back()->update(deltaTime);
        return;
    }

    Engine* engine = Engine::getInstance();
    for (Sprite* sprite : engine->getSprites()) {
        if (sprite) sprite->update(deltaTime);
    }
    for (AnimatedSprite* sprite : engine->getAnimatedSprites()) {
        if (sprite) sprite->update(deltaTime);
    }
}
