#pragma once

#include <string>

namespace nmlh{
    // NEEDS TO BE MOVED ELSEWHERE
    class Event;
    class TimeStep;

    class RenderingLayer{
        // This must be able to be accessed by inherited classes
        protected:
            std::string m_LayerName;

        public:
            RenderingLayer(const std::string& LayerName = "Default Layer Name") : m_LayerName(LayerName) {}
            virtual ~RenderingLayer() = default;

            virtual void OnAttach(){}
            virtual void OnDetach(){}
            virtual void OnEvent(Event& EventToHandle){}
            virtual void OnUpdate(TimeStep& /*<- remove reference later*/ ts){} // A TimeStep is the time difference between the current and last frame

            const std::string& GetName() const{return m_LayerName;}
    };
}