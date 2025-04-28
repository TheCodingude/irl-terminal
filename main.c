#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define STB_EASY_FONT_IMPLEMENTATION
#include "stb_easy_font.h"

typedef struct{
    float red;
    float green;
    float blue;
} Vec3;


void drawText(float x, float y, float scale, const char* text, Vec3 color) {
    char buffer[99999]; // A buffer for vertices
    int num_quads;

    glPushMatrix();
    glTranslatef(x, y, 0); 
    glScalef(scale, scale, 1);    
    glColor3f(color.red, color.green, color.blue); // TODO: Add color to arguements 

    num_quads = stb_easy_font_print(0, 0, (char*)text, NULL, buffer, sizeof(buffer));

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 16, buffer);
    glDrawArrays(GL_QUADS, 0, num_quads * 4);
    glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();
}

void Clock(float x, float y, float scale, bool twelvehour, Vec3 color){
    time_t now;
    struct tm *timeinfo;

    time(&now);
    timeinfo = localtime(&now);

    if(twelvehour){
        timeinfo->tm_hour = timeinfo->tm_hour % 12;
    }
    
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);
    drawText(x,y,scale,buffer, color);
}



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
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, mode->width, mode->height, 0.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();
        glLineWidth(5.0f);

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, 1);
        }
        // Set the background color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        Vec3 color = {0.35f, 1.0f, 0.52f};

        Clock(100.0f, 100.0f, 10.0f, false, color);

        // glOrtho()

        // Swap buffers and poll events
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
