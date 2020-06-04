#include <algorithm>

#include "layer_stack.h"

namespace nmlh{
    LayerStack::~LayerStack(){
        for(RenderingLayer* Layer: m_Stack){
            Layer->OnDetach();
            delete Layer;
        }
    }

    // There are 2 kinds of layers, base, and overlay.
    // Overlay layers will always be inserted after the base layers
    // Base layers will be inserted just before Overlay layers
    void LayerStack::PushLayer(RenderingLayer* Layer){
        m_Stack.emplace(m_Stack.begin() + m_LayerInsertIndex, Layer);
        m_LayerInsertIndex++;
    }

    void LayerStack::PushOverlay(RenderingLayer* Overlay){
        m_Stack.emplace_back(Overlay);
    }

    void LayerStack::PopLayer(RenderingLayer* Layer){
        // Look at locations from the start to the end of the insertion area
        auto FindLocation = std::find(m_Stack.begin(), m_Stack.begin() + m_LayerInsertIndex, Layer);

        // If the iterator is not at the end of the search area, it means the layer has been found
        if(FindLocation != m_Stack.begin() + m_LayerInsertIndex){
            Layer->OnDetach();
            m_Stack.erase(FindLocation);
            m_LayerInsertIndex--;
        }
    }

    void LayerStack::PopOverlay(RenderingLayer* Overlay){
        // Look at locations from the insertion area to the end
        auto FindLocation = std::find(m_Stack.begin() + m_LayerInsertIndex, m_Stack.end(), Overlay);

        // If the iterator is not at the end of the search area, it means the layer has been found
        if(FindLocation != m_Stack.begin() + m_LayerInsertIndex){
            Overlay->OnDetach();
            m_Stack.erase(FindLocation);
            m_LayerInsertIndex--;
        }
    }
}