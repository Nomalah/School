#pragma once

namespace nmlh{
    enum class EventType{
        None = 0,
        WindowClose, WindowResized, WindowMoved, WindowLoseFocus, WindowGainFocus,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum EventCategory{
        None = 0,
        EventCategoryWindow = 1,
        EventCategoryInput = 2,
        EventCategoryKeyboard = 4,
        EventCategoryMouse = 8,
        EventCategoryMouseButton = 16,
        EventCategoryApplication = 32
    };

    // May change to a struct later, but likely not.
    class Event{
        public:
            bool IsHandled;

            Event() : IsHandled(false){}

            virtual EventType GetEventType() const = 0;
            virtual int GetCategoryFlags() const = 0;

            inline bool IsInCategory(EventCategory CheckCategory){
                return GetCategoryFlags() & CheckCategory;
            }
    };

    class EventHandler{
        private:
            Event& m_ToHandle;

        public:
            EventHandler(Event& ToHandle) : m_ToHandle(ToHandle){}

            
    };
}