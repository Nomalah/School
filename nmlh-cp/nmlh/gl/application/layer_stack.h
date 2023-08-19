#pragma once

#include <vector>

#include "layer.h"

namespace nmlh{
    // Literally just a stack of layers
    class LayerStack{
        private:
            // This is the index that is used when inserting a base layer into the stack
            size_t m_LayerInsertIndex;
            // Use layer* to save space
            std::vector<RenderingLayer*> m_Stack;
        public:
            LayerStack() : m_LayerInsertIndex(0){};
            ~LayerStack();

            // There are 2 kinds of layers, base, and overlay.
            // Overlay layers will always be inserted after the base layers
            // Base layers will be inserted just before Overlay layers
            void PushLayer(RenderingLayer* Layer);
            void PushOverlay(RenderingLayer* Overlay);
            void PopLayer(RenderingLayer* Layer);
            void PopOverlay(RenderingLayer* Overlay);

            // Iterators
            std::vector<RenderingLayer*>::iterator begin(){return m_Stack.begin();}
            std::vector<RenderingLayer*>::iterator end(){return m_Stack.end();}
            std::vector<RenderingLayer*>::reverse_iterator rbegin(){return m_Stack.rbegin();}
            std::vector<RenderingLayer*>::reverse_iterator rend(){return m_Stack.rend();}

            std::vector<RenderingLayer*>::const_iterator begin() const{return m_Stack.begin();}
            std::vector<RenderingLayer*>::const_iterator end() const{return m_Stack.end();}
            std::vector<RenderingLayer*>::const_reverse_iterator rbegin() const{return m_Stack.rbegin();}
            std::vector<RenderingLayer*>::const_reverse_iterator rend() const{return m_Stack.rend();}
    };
}