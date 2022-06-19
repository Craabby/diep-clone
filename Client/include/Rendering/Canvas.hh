#pragma once

#include <cmath>
#include <functional>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace client
{
    class Canvas
    {
        GLFWwindow *window;

    public:
        Canvas(std::function<void(Canvas *)> render);

        template <bool filled = true>
        void DrawCircle(float centerX, float centerY, float r)
        {
            // https://stackoverflow.com/a/24843626

            glBegin(filled ? GL_TRIANGLE_FAN : GL_LINE_LOOP);
            for (int i = 0; i < 100; i++)
            {
                float theta = 2.0f * 3.1415926f * float(i) / 100.f; // get the current angle
                float x = r * cosf(theta);                          // calculate the x component
                float y = r * sinf(theta);                          // calculate the y component
                glVertex2f(x + centerX, y + centerY);               // output vertex
            }
            glEnd();
        };
        void SetColor(float r, float g, float b);
    };
}
