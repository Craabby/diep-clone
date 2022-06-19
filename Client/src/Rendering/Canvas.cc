#include <Rendering/Canvas.hh>

#include <cmath>
#include <functional>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace client
{
    Canvas::Canvas(std::function<void(Canvas *)> render)
    {
        /* Initialize the library */
        if (!glfwInit())
            return;

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(720, 720, "diep-clone", nullptr, nullptr);
        if (!window)
        {
            glfwTerminate();
            return;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        if (glewInit() != GLEW_OK)
            std::cout << "uh oh";

        std::cout << "using opengl version: " << glGetString(GL_VERSION) << std::endl;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            render(this);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        glfwTerminate();
    }

}
