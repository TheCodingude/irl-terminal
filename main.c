#include <GLFW/glfw3.h>
#include <stdio.h>

int main(void) {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "OpenGL Window", monitor, NULL);


    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable V-Sync

    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();
        glLineWidth(5.0f);

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, 1);
        }
        // Set the background color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_LINE_LOOP); 

        glColor3f(1.0f, 1.0f, 1.0f); 

        glVertex2f(-0.5f, -0.5f); 
        glVertex2f( 0.5f, -0.5f); 
        glVertex2f( 0.5f,  0.5f); 
        glVertex2f(-0.5f,  0.5f); 
        glEnd();



        // Swap buffers and poll events
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
