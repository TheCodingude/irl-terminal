#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <GLFW/glfw3.h>
#include <GL/glut.h>

#define STB_EASY_FONT_IMPLEMENTATION
#include "stb_easy_font.h"

typedef struct{
    float red;
    float green;
    float blue;
} Vec3;

Vec3 hex_to_rgb(const char *hex) {
    Vec3 color = {0};

    // Skip leading '#' if present
    if (hex[0] == '#') {
        hex++;
    }

    if (strlen(hex) != 6) {
        fprintf(stderr, "Invalid hex color format: %s\n", hex);
        return color;
    }

    char r_str[3] = { hex[0], hex[1], '\0' };
    char g_str[3] = { hex[2], hex[3], '\0' };
    char b_str[3] = { hex[4], hex[5], '\0' };

    int r = (int)strtol(r_str, NULL, 16);
    int g = (int)strtol(g_str, NULL, 16);
    int b = (int)strtol(b_str, NULL, 16);

    color.red = r / 255.0f;
    color.green = g / 255.0f;  // normalize the shits
    color.blue = b / 255.0f;

    return color;
}


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

void Date(float x, float y, float scale, Vec3 color){
    time_t now;
    struct tm *timeinfo;

    time(&now);
    timeinfo = localtime(&now);

    char buffer[100];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);

    drawText(x, y, scale, buffer, color);

}

void Clock(float x, float y, float scale, bool twelvehour, Vec3 color){
    time_t now;
    struct tm *timeinfo;

    time(&now);
    timeinfo = localtime(&now);

    if(twelvehour){
        timeinfo->tm_hour = timeinfo->tm_hour % 12;
    }
    
    char buffer[100];
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


        // Vec3 color = {0.35f, 1.0f, 0.52f}; // Random color
        // Vec3 color = {1.0f, 1.0f, 1.0f}; // white
        Vec3 color = hex_to_rgb("#1058c4");


        Clock(100.0f, 100.0f, 10.0f, false, color);
        Date(1000.0f, 100.0f, 10.0f, color);

        // glOrtho()

        // Swap buffers and poll events
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
