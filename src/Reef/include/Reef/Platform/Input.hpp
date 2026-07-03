#ifndef REEF_PLATFORM_INPUT_HPP
#define REEF_PLATFORM_INPUT_HPP

#include <Reef/Export.hpp>

#include <glm/vec2.hpp>

namespace Reef
{

enum class KeyboardLayout
{
    GERMAN,
    ENGLISH,
};

enum class Key: uint8_t
{
    SPACE,           // Spacebar key
    MINUS,           // - key
    PERIOD,          // . key
    COMMA,           // , key
    
    ZERO,            // 0 key
    ONE,             // 1 key
    TWO,             // 2 key
    THREE,           // 3 key
    FOUR,            // 4 key
    FIVE,            // 5 key
    SIX,             // 6 key
    SEVEN,           // 7 key
    EIGHT,           // 8 key
    NINE,            // 9 key

    A,               // A key
    B,               // B key
    C,               // C key
    D,               // D key
    E,               // E key
    F,               // F key
    G,               // G key
    H,               // H key
    I,               // I key
    J,               // J key
    K,               // K key
    L,               // L key
    M,               // M key
    N,               // N key
    O,               // O key
    P,               // P key
    Q,               // Q key
    R,               // R key
    S,               // S key
    T,               // T key
    U,               // U key
    V,               // V key
    W,               // W key
    X,               // X key
    Y,               // Y key
    Z,               // Z key
   
    ESCAPE,          // Esc key
    RETURN,          // Enter key
    TAB,             // Tab key
    BACKSPACE,       // Backspace key
    INSERT,          // Insert key
    DELETE,          // Delete key
    RIGHT,           // Right arrow key
    LEFT,            // Left arrow key
    DOWN,            // Down arrow key
    UP,              // Up arrow key
    PAGE_UP,         // Page up key
    PAGE_DOWN,       // Page down key
    HOME,            // Home key
    END,             // End key
    CAPS_LOCK,       // Caps lock key
    SCROLL_LOCK,     // Scroll lock key
    NUM_LOCK,        // Num lock key
    PRINT_SCREEN,    // Print screen key
    PAUSE,           // Pause key

    F1,              // F1 key
    F2,              // F2 key
    F3,              // F3 key
    F4,              // F4 key
    F5,              // F5 key
    F6,              // F6 key
    F7,              // F7 key
    F8,              // F8 key
    F9,              // F9 key
    F10,             // F10 key
    F11,             // F11 key
    F12,             // F12 key
    F13,             // F13 key
    F14,             // F14 key
    F15,             // F15 key
    F16,             // F16 key
    F17,             // F17 key
    F18,             // F18 key
    F19,             // F19 key
    F20,             // F20 key
    F21,             // F21 key
    F22,             // F22 key
    F23,             // F23 key
    F24,             // F24 key

    NUMPAD_ZERO,     // Numeric keypad 0 key
    NUMPAD_ONE,      // Numeric keypad 1 key
    NUMPAD_TWO,      // Numeric keypad 2 key
    NUMPAD_THREE,    // Numeric keypad 3 key
    NUMPAD_FOUR,     // Numeric keypad 4 key
    NUMPAD_FIVE,     // Numeric keypad 5 key
    NUMPAD_SIX,      // Numeric keypad 6 key
    NUMPAD_SEVEN,    // Numeric keypad 7 key
    NUMPAD_EIGHT,    // Numeric keypad 8 key
    NUMPAD_NINE,     // Numeric keypad 9 key

    NUMPAD_DECIMAL,  // Numeric keypad , key
    NUMPAD_DIVIDE,   // Numeric keypad / key
    NUMPAD_MULTIPLY, // Numeric keypad * key
    NUMPAD_SUBTRACT, // Numeric keypad - key
    NUMPAD_ADD,      // Numeric keypad + key

    LEFT_SHIFT,      // Left shift key
    LEFT_CONTROL,    // Left control key
    LEFT_ALT,        // Left alt key
    LEFT_SUPER,      // Left super key
    RIGHT_SHIFT,     // Right shift key
    RIGHT_CONTROL,   // Right control key
    RIGHT_ALT,       // Right alt key
    RIGHT_SUPER,     // Right super key

    // Keys available for german keyboard layouts
    CARET,        // ^ key (German layout)
    ESZETT,       // ß key (German layout)
    ACUTE_ACCENT, // ´ key (German layout)
    UE,           // Ü key (German layout)
    PLUS,         // + key (German layout)
    OE,           // Ö key (German layout)
    AE,           // Ä key (German layout)
    HASH,         // # key (German layout)
    LESS_THAN,    // < key (German layout)

    // Keys available for english keyboard layouts
    LEFT_BRACKET,    // [ key (English layout)
    RIGHT_BRACKET,   // ] key (English layout)
    GRAVE_ACCENT,    // ` key (English layout)
    BACKSLASH,       // \ key (English layout)
    SLASH,           // / key (English layout)
    SEMICOLON,       // ; key (English layout)
    EQUAL,           // = key (English layout)
    APOSTROPHE,      // ' key (English layout)
};


enum class MouseButton
{
    /// Left mouse button
    LEFT,
    /// Right mouse button
    RIGHT,
    /// Middle mouse button
    MIDDLE,
    /// X1 mouse button
    X1,
    /// X2 mouse button
    X2,
};


enum class KeyState
{
    /// The key is not pressed
    UP,
    /// The key is pressed
    PRESSED,
    /// The key was pressed but is no longer pressed
    RELEASED
};


class REEF_API Input
{
public:

    virtual KeyState getKeyState(Key key) const = 0;

    virtual KeyState getMouseButtonState(MouseButton button) const = 0;

    virtual void setCursorPosition(const glm::uvec2& pixelPosition) = 0;

    virtual glm::ivec2 getCursorPosition() const = 0;

    //virtual Event<Key, KeyState>& onKeyEvent() = 0;

    //virtual Event<MouseButton, KeyState>& onMouseButtonEvent() = 0;

    //virtual Event<glm::ivec2>& onCursorMoved() = 0;

}; // class Input

} // namespace Reef

#endif // !REEF_PLATFORM_INPUT_HPP
