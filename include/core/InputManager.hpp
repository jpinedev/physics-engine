#ifndef __INPUTMANAGER_HPP__
#define __INPUTMANAGER_HPP__

#include <set>
#include <string>
#include <unordered_map>

#include <glm/vec2.hpp>

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else  // This works for Mac
#include <SDL.h>
#endif

/**
 * An event listener interface for keyboard events (press and release).
 */
class IKeyEventListener
{
public:
    /**
     * Handle key events whenever they are triggered (by the InputManager).
     * @param keyName Name of the key
     * @param isKeyPressed Is the key being pressed?
     */
    virtual void HandleKeyEvent(const std::string& keyName,
                                bool isKeyPressed) = 0;
};

/**
 * An event listener interface for mouse click events.
 */
class IMouseClickEventListener
{
public:
    /**
     * Handle mouse click events whenever they are triggered (by the
     * InputManager).
     * @param mousePos The current mouse position on the screen
     */
    virtual void HandleMouseClickEvent(glm::vec2 mousePos) = 0;
};

/**
 * An event listener interface for mouse drag events.
 */
class IMouseDragEventListener
{
public:
    /**
     * Handle mouse drag events whenever they are triggered (by the
     * InputManager).
     * @param currentPos The current position of the mouse
     * @param lastPos The last position of the mouse
     */
    virtual void HandleMouseDragEvent(glm::vec2 currentPos,
                                      glm::vec2 lastPos) = 0;
};

/**
 * An event listener interface for all sdl events.
 */
class IGeneralEventListener
{
public:
    /**
     * Handles events
     * @param evt The event we want to handle
     */
    virtual void HandleGeneralEvent(SDL_Event* evt) = 0;
};

/**
 * Represents the current state of user input devices like mouse and keyboard.
 *
 * TODO: define an Axis struct for handling multiple keys for the same action.
 * TODO: add support for scroll wheel input
 */
class InputState
{
public:
    /**
     * Check if a key is pressed by key name.
     * @param keyName The name of the key we are checking
     * @return Was that key pressed?
     */
    virtual bool IsKeyPressed(const std::string& keyName) = 0;

    /**
     * Get axis direction from currently pressed keys.
     *
     * If both the positive and negative keys are pressed, the net effect is 0.
     *
     * TODO: add support for multiple keys for the same action.
     * @param positive The name of the key that is the "positive" for the axis
     * @param negative The name of the key that is the "negative" for the axis
     * @return The value of the input on the axis
     */
    virtual int GetAxis(const std::string& positive,
                        const std::string& negative) = 0;

    /**
     * Check if a mouse button is pressed by mouse button number.
     * @param mouseButtonNumber The mouse button we check
     * @return Is the mouse button being pressed?
     */
    virtual bool IsMouseButtonPressed(int mouseButtonNumber) = 0;
};

/**
 * Manager to handle all input events for keyboard and mouse.
 */
class InputManager : public InputState
{
public:
    /**
     * Constructor
     */
    InputManager();

    /**
     * Destructor
     */
    ~InputManager();

    /**
     * Read all input events and update the input state accordingly.
     *
     * TODO: add support for mouse events (mouse move, mouse button, mouse drag,
     * etc.)
     * @param evt The event we want to handle
     */
    void HandleEvent(SDL_Event evt);

    /**
     * Singleton for accessing input state globally.
     */
    static InputState* State;

    /**
     * Check if a key is pressed by key name.
     * @param keyName The name of the key we are checking
     * @return Was that key pressed?
     */
    virtual bool IsKeyPressed(const std::string& keyName) override;

    /**
     * Get axis direction from currently pressed keys.
     *
     * If both the positive and negative keys are pressed, the net effect is 0.
     *
     * TODO: add support for multiple keys for the same action.
     * @param positive The name of the key that is the "positive" for the axis
     * @param negative The name of the key that is the "negative" for the axis
     * @return The value of the input on the axis
     */
    virtual int GetAxis(const std::string& positive,
                        const std::string& negative) override;

    /**
     * Check if a mouse button is pressed by mouse button number.
     * @param mouseButtonNumber The mouse button we check
     * @return Is the mouse button being pressed?
     */
    virtual bool IsMouseButtonPressed(int mouseButtonNumber) override;

    /**
     * Sets the main window
     * @param windowId The window id
     */
    void SetMainWindow(Uint32 windowId);

    /**
     * Adds a key event listener
     * @param keyListener The event listener we are adding
     */
    void AddKeyEventListener(IKeyEventListener* keyListener);

    /**
     * Removes a key event listener
     * @param keyListener The event listener we are removing
     */
    void RemoveKeyEventListener(IKeyEventListener* keyListener);

    /**
     * Adds a mouse click event listener
     * @param mcListener The event listener we are adding
     */
    void AddMouseClickEventListener(IMouseClickEventListener* mcListener);

    /**
     * Removes a mouse click event listener
     * @param mcListener The event listener we are removing
     */
    void RemoveMouseClickEventListener(IMouseClickEventListener* mcListener);

    /**
     * Adds a mouse drag event listener
     * @param mdListener The event listener we are adding
     */
    void AddMouseDragEventListener(IMouseDragEventListener* mdListener);

    /**
     * Removes a mouse drag event listener
     * @param mdListener The event listener we are removing
     */
    void RemoveMouseDragEventListener(IMouseDragEventListener* mdListener);

protected:
    /**
     * Update keyboard state for a key and alert key event listeners.
     * @param keyName The name of the key pressed
     */
    inline void PressKey(std::string& keyName);

    /**
     * Update keyboard state for a key and alert key event listeners.
     * @param keyName The name of the key removed
     */
    inline void ReleaseKey(std::string& keyName);

    /**
     * Update mouse button state for a button.
     * @param index The index of the mouse button
     */
    inline void PressMouseButton(int index);

    /**
     * Update mouse button state for a button and alert mouse click listeners
     * (when applicable).
     * @param index The index of the mouse button released
     */
    inline void ReleaseMouseButton(int index);

    /**
     * Mouse was clicked
     */
    inline void MouseClick();

    /**
     * Mouse was dragged
     * @param mouseDelta The delta change of the mouse
     */
    inline void MouseDrag(glm::vec2 mouseDelta);

    /**
     * Converts the mouse button number to the mouse button index
     * @param mbNumber Mouse button number
     * @return Mouse button index
     */
    static inline int MouseButtonNumberToMouseButtonIndex(int mbNumber);

    /**
     * Converts the mouse button to the mouse button index
     * @param sdlMouseButton Mouse button
     * @return Mouse button index
     */
    static inline int SDL_MouseButtonToMouseButtonIndex(Uint8 sdlMouseButton);

    /**
     * Translate from scancode to human-readable name of a key.
     * @param scancode The scancode we are using
     * @return The name of the key
     */
    static inline std::string SDL_GetKeyNameFromScancode(SDL_Scancode scancode);

private:
    // Stores state for each key, indexed by key name
    std::unordered_map<std::string, bool> mKeyboardState;
    // Stores state for each mouse button, indexed by MouseButtonNumber - 1
    bool mMouseButtonsState[5]{0, 0, 0, 0, 0};
    bool mIsDragging = false;
    glm::vec2 mMousePosition{0, 0};

    std::set<IKeyEventListener*> mKeyEventListeners;
    std::set<IMouseClickEventListener*> mMouseClickEventListeners;
    std::set<IMouseDragEventListener*> mMouseDragEventListeners;

    Uint32 mMainWindowId = 0;
};

#endif
