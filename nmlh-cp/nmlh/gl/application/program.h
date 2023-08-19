#pragma once

#include "layer_stack.h"

namespace nmlh{
    // An application has layers
    class Application{
        private:
            LayerStack ProgramLayers;
            bool m_Running;
            bool m_Minimized;

        public:
    };
}