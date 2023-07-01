// #define LOG_KEY_EVENTS
// #define LOG_MOUSE_EVENTS

#if defined(LOG_KEY_EVENTS) || defined(LOG_MOUSE_EVENTS)
#include <iostream>
#endif

#include <glm/vec2.hpp>
#include <string>
#include "core/InputManager.hpp"

inline std::string InputManager::SDL_GetKeyNameFromScancode(
    SDL_Scancode scancode)
{
    return SDL_GetKeyName(SDL_GetKeyFromScancode(scancode));
}

InputState* InputManager::State = nullptr;

InputManager::InputManager() { State = this; }
InputManager::~InputManager() { State = nullptr; }

void InputManager::HandleEvent(SDL_Event evt)
{
    switch (evt.type)
    {
        case SDL_KEYDOWN:
        {
            std::string key =
                SDL_GetKeyNameFromScancode(evt.key.keysym.scancode);
#ifdef LOG_KEY_EVENTS
            std::cout << "Pressed key: " << key << std::endl;
#endif
            PressKey(key);
            break;
        }

        case SDL_KEYUP:
        {
            std::string key =
                SDL_GetKeyNameFromScancode(evt.key.keysym.scancode);
#ifdef LOG_KEY_EVENTS
            std::cout << "Released key: " << key << std::endl;
#endif
            ReleaseKey(key);
            break;
        }

        case SDL_MOUSEBUTTONDOWN:
        {
            int mouseButtonIndex =
                SDL_MouseButtonToMouseButtonIndex(evt.button.button);
#ifdef LOG_MOUSE_EVENTS
            std::cout << "Pressed mouse button: " << (mouseButtonIndex + 1)
                      << std::endl;
#endif
            PressMouseButton(mouseButtonIndex);
            break;
        }

        case SDL_MOUSEBUTTONUP:
        {
            int mouseButtonIndex =
                SDL_MouseButtonToMouseButtonIndex(evt.button.button);
#ifdef LOG_MOUSE_EVENTS
            std::cout << "Released mouse button: " << (mouseButtonIndex + 1)
                      << std::endl;
#endif
            ReleaseMouseButton(mouseButtonIndex);
            break;
        }

        case SDL_MOUSEMOTION:
        {
            if (evt.motion.windowID != mMainWindowId) break;

            mMousePosition.x = evt.motion.x;
            mMousePosition.y = evt.motion.y;

            if (!IsMouseButtonPressed(1)) break;

            MouseDrag(glm::vec2(evt.motion.xrel, evt.motion.yrel));
            break;
        }

            // TODO: add support for mouse events
    }
}

bool InputManager::IsKeyPressed(const std::string& keyName)
{
    auto input = mKeyboardState.find(keyName);

    if (input != mKeyboardState.end())
    {
        return input->second;
    }

    mKeyboardState[keyName] = false;
    return false;
}

int InputManager::GetAxis(const std::string& positive,
                          const std::string& negative)
{
    int axis = 0;
    if (IsKeyPressed(positive)) axis += 1;
    if (IsKeyPressed(negative)) axis -= 1;
    return axis;
}

void InputManager::AddKeyEventListener(IKeyEventListener* listener)
{
    if (mKeyEventListeners.count(listener)) return;

    mKeyEventListeners.insert(listener);
}
void InputManager::RemoveKeyEventListener(IKeyEventListener* listener)
{
    if (!mKeyEventListeners.count(listener)) return;

    mKeyEventListeners.erase(listener);
}

void InputManager::AddMouseClickEventListener(
    IMouseClickEventListener* listener)
{
    if (mMouseClickEventListeners.count(listener)) return;

    mMouseClickEventListeners.insert(listener);
}
void InputManager::RemoveMouseClickEventListener(
    IMouseClickEventListener* listener)
{
    if (!mMouseClickEventListeners.count(listener)) return;

    mMouseClickEventListeners.erase(listener);
}

void InputManager::AddMouseDragEventListener(IMouseDragEventListener* listener)
{
    if (mMouseDragEventListeners.count(listener)) return;

    mMouseDragEventListeners.insert(listener);
}
void InputManager::RemoveMouseDragEventListener(
    IMouseDragEventListener* listener)
{
    if (!mMouseDragEventListeners.count(listener)) return;

    mMouseDragEventListeners.erase(listener);
}

bool InputManager::IsMouseButtonPressed(int mouseButtonNumber)
{
    if (mouseButtonNumber < 1 || mouseButtonNumber > 5) return false;

    return mMouseButtonsState[mouseButtonNumber - 1];
}

inline void InputManager::PressKey(std::string& keyName)
{
    mKeyboardState[keyName] = true;

    for (IKeyEventListener* listener : mKeyEventListeners)
    {
        // Trigger key down event
        listener->HandleKeyEvent(keyName, true);
    }
}

inline void InputManager::ReleaseKey(std::string& keyName)
{
    mKeyboardState[keyName] = false;

    for (IKeyEventListener* listener : mKeyEventListeners)
    {
        // Trigger key up event
        listener->HandleKeyEvent(keyName, false);
    }
}

inline void InputManager::PressMouseButton(int index)
{
    mMouseButtonsState[index] = true;
    if (index == 0)
    {
        mIsDragging = false;
    }
}

inline void InputManager::ReleaseMouseButton(int index)
{
    mMouseButtonsState[index] = false;
    if (index == 0)
    {
        if (mIsDragging)
            MouseDrag(glm::vec2(0, 0));
        else
            MouseClick();
    }
}

inline void InputManager::MouseClick()
{
#ifdef LOG_MOUSE_EVENTS
    std::cout << "Clicked: " << std::endl;
    PrettyPrint(std::cout, mMousePosition);
#endif
    for (IMouseClickEventListener* listener : mMouseClickEventListeners)
    {
        listener->HandleMouseClickEvent(mMousePosition);
    }
}

inline void InputManager::MouseDrag(glm::vec2 deltaPos)
{
    mIsDragging = true;
    glm::vec2 lastPos = mMousePosition - deltaPos;

#ifdef LOG_MOUSE_EVENTS
    std::cout << "Dragged from: " << std::endl;
    PrettyPrint(std::cout, lastPos);
    std::cout << "Dragged to: " << std::endl;
    PrettyPrint(std::cout, mMousePosition);
#endif

    for (IMouseDragEventListener* listener : mMouseDragEventListeners)
    {
        listener->HandleMouseDragEvent(mMousePosition, lastPos);
    }
}

void InputManager::SetMainWindow(Uint32 windowId) { mMainWindowId = windowId; }

inline int InputManager::SDL_MouseButtonToMouseButtonIndex(Uint8 sdlMouseButton)
{
    switch (sdlMouseButton)
    {
        case SDL_BUTTON_LEFT:
            // Mouse button 1
            return 0;
        case SDL_BUTTON_RIGHT:
            // Mouse button 2
            return 1;
        case SDL_BUTTON_MIDDLE:
            // Mouse button 3
            return 2;
        case SDL_BUTTON_X1:
            // Mouse button 4
            return 3;
        case SDL_BUTTON_X2:
            // Mouse button 5
            return 4;
    }
    return -1;
}
