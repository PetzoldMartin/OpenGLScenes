#include "render_engine.h"

#include <iostream>

using namespace std;

RenderEngine::RenderEngine()
{
}

void RenderEngine::Render()
{
    for(int i = drawables.size() -1; i >= 0; --i) {
        drawables[i]->Draw();
    }
}
