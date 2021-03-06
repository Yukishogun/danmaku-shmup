#include <SDL.h>
#pragma once

extern bool keysDown[];

enum KeyAction {
    ACTION_MOVE_UP = SDL_SCANCODE_UP,
    ACTION_MOVE_LEFT = SDL_SCANCODE_LEFT,
    ACTION_MOVE_RIGHT = SDL_SCANCODE_RIGHT,
    ACTION_MOVE_DOWN = SDL_SCANCODE_DOWN,
    WASD_ACTION_MOVE_UP = SDL_SCANCODE_W,
    WASD_ACTION_MOVE_LEFT = SDL_SCANCODE_A,
    WASD_ACTION_MOVE_RIGHT = SDL_SCANCODE_D,
    WASD_ACTION_MOVE_DOWN = SDL_SCANCODE_S
};