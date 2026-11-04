/*
** EPITECH PROJECT, 2026
** bonus
** File description:
** Config
*/

#pragma once

// ==================== WINDOW CONFIGURATION ====================
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_NAME "NanoBonus"
#define WINDOW_FPS 60

// ==================== CAMERA CONFIGURATION ====================
#define CAMERA_ZOOM_IN_FACTOR 0.9f
#define CAMERA_ZOOM_OUT_FACTOR 1.1f
#define CAMERA_KEYBOARD_SPEED 10.0f

// ==================== KEY BINDS ====================
#define CAMERA_KEY_UP sf::Keyboard::Key::Up
#define CAMERA_KEY_DOWN sf::Keyboard::Key::Down
#define CAMERA_KEY_LEFT sf::Keyboard::Key::Left
#define CAMERA_KEY_RIGHT sf::Keyboard::Key::Right
#define CAMERA_KEY_UP_ALT sf::Keyboard::Key::Z
#define CAMERA_KEY_DOWN_ALT sf::Keyboard::Key::S
#define CAMERA_KEY_LEFT_ALT sf::Keyboard::Key::Q
#define CAMERA_KEY_RIGHT_ALT sf::Keyboard::Key::D

#define KEY_DELETE_PRIMARY sf::Keyboard::Key::Delete
#define KEY_DELETE_SECONDARY sf::Keyboard::Key::Backspace
#define KEY_QUIT sf::Keyboard::Key::Escape

// ==================== GRID & RENDERING ====================
#define GRID_SIZE 20
#define GRID_COLOR sf::Color(0, 0, 0)
#define BACKGROUND_COLOR sf::Color(15, 15, 35)

// ==================== COMPONENTS SETTINGS ====================
#define MIN_COMPONENT_HEIGHT 40.0f
#define COMPONENT_HEIGHT_PER_PIN 20.0f
#define MIN_COMPONENT_WIDTH 70.0f
#define COMPONENT_FILL_COLOR sf::Color(50, 50, 50)
#define COMPONENT_OUTLINE_THICKNESS 2.0f
#define COMPONENT_OUTLINE_COLOR sf::Color(255, 255, 255)

#define OUTPUT_COLOR_ON sf::Color(50, 150, 50)
#define OUTPUT_COLOR_OFF sf::Color(150, 50, 50)

// ==================== PINS SETTINGS ====================
#define PINS_RADIUS 5.0f
#define PINS_OUTLINE_THICKNESS 1.0f
#define PINS_OUTLINE_COLOR sf::Color(255, 255, 255)
#define INPUT_COLOR_ON sf::Color(50, 150, 50)
#define INPUT_COLOR_OFF sf::Color(150, 50, 50)
#define OUTPUT_PIN_ON sf::Color(50, 150, 50)
#define OUTPUT_PIN_OFF sf::Color(50, 50, 50)
#define OUTPUT_PIN_UNDEFINED sf::Color(150, 50, 50)

#define PIN_USER_INPUT_MARGIN 15.0f

// ==================== LINKS SETTINGS ====================
#define LINK_ON_COLOR sf::Color(0, 255, 0)
#define LINK_OFF_COLOR sf::Color(50, 50, 50)

#define LINK_PENDING_COLOR sf::Color(100, 100, 100)

// ==================== INTERACTIONS SETTINGS ====================
#define LINK_DESTROY_DISTANCE 10.0f
#define CIRCUIT_DRAG_THRESHOLD 5.0f

// ==================== TOOLBAR SETTINGS ====================
#define TOOLBAR_COLOR sf::Color(30, 30, 30)
#define TOOLBAR_OUTLINE_THICKNESS 1.0f
#define TOOLBAR_OUTLINE_COLOR sf::Color(100, 100, 100)
#define TOOLBAR_ARROWS_COLOR sf::Color(45, 45, 45)
#define TOOLBAR_COMPONENT_SLOT_COLOR sf::Color(45, 45, 45)

#define TOOLBAR_SCREEN_SIZE 1.0f / 6.0f
#define TOOLBAR_COMPONENTS_PADDING_RATIO 1.0f / 10.0f
#define TOOLBAR_COMPONENT_INSLOT_SCALE 8.0f / 10.0f

// ==================== ASSET PATHS ====================
#define FONT "assets/Inter.ttf"

// ==================== BOOLEAN LOGIC ====================
#define UNDEFINED -1
#define TRUE 1
#define FALSE 0