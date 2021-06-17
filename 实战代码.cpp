//  Created by Qin, Jianbo on 2021/6/16.
//  Copyright © 2021 Qin, Jianbo. All rights reserved.

/*********************************************************************************
 1. Add glfw and glad to include path [Search Paths]:
    ① search path for <>
    ② user path for ""
 
 2. Add .a to project [Build Phases -> Link Binary With Libraries]:
   // I don't know how to use the .dylib at present.
 
    Add the following framwork (MacOS)
        ① CoreVideo.framework
        ② IOKit.framework
        ③ Cocoa.framework
        ④ OpenGL.framework
        ⑤ GLUT.framework
 
    Add the glfw lib
        ①libglfw3.a
 
 3. Add glad.c to your project
 
 *********************************************************************************/

#include <cmath>
#include <iostream>

#include <GLAD/glad/include/glad/glad.h>
#include <GLFW/glfw-3.3.4.bin.MACOS/include/GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <STB/stb_image.h>

#include <GLM/glm/glm/glm.hpp>
#include <GLM/glm/glm/gtc/matrix_transform.hpp>
#include <GLM/glm/glm/gtc/type_ptr.hpp>

const unsigned int WIDTH  = 800;
const unsigned int HEIGHT = 600;

// data
float vertices[] = {
    // pos                // texture   // color
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f
};
glm::vec3 cubePositions[] = {
  glm::vec3( 0.0f,  0.0f,  0.0f),
  glm::vec3( 2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3( 2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3( 1.3f, -2.0f, -2.5f),
  glm::vec3( 1.5f,  2.0f, -2.5f),
  glm::vec3( 1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f),
  glm::vec3(-2.3f,  1.0f, -1.5f)
};
unsigned int indices[] =
{
    0, 1, 3,
    1, 2, 3
};

// Vertex shader
const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec2 aTexCoord;\n"
"layout (location = 2) in vec3 aColor;\n"
"uniform mat4 uniformPosTran;\n"
"out vec3 tmpColor;\n"
"out vec2 TexCoord;\n"

"void main()\n"
"{\n"
"   gl_Position = uniformPosTran * vec4(aPos, 1.0);\n"
"   tmpColor = aColor;\n"
"   TexCoord = aTexCoord;\n"
"}\0";

// Fragment shader
const char* fragmentShaderSource =
"#version 330 core\n"
"in vec3 tmpColor;\n"
"in vec2 TexCoord;\n"
"uniform vec4 uniformColor;\n"
"uniform sampler2D uniformTexture;\n"
"out vec4 FragColor;\n"

"void main()\n"
"{\n"
"   FragColor = texture(uniformTexture, TexCoord) * (uniformColor + vec4(tmpColor, 1.0f));\n"
"}\0";

// camera
glm::vec3 cameraPos   = glm::vec3(0, 0, 5);
glm::vec3 cameraFront = glm::vec3(0, 0, -1);
glm::vec3 cameraUp    = glm::vec3(0, 1, 0);

bool firstMouse  = true;
bool isPress     = false;
double yaw       = -90;
double pitch     = 0;
double lastX     = WIDTH / 2;
double lastY     = HEIGHT / 2;
float zoomLevel  = 27.0f;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    
    if(!isPress)
    {
        return;
    }
    
    float sensitivity = 0.1;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    
    yaw += xoffset;
    pitch += yoffset;
    
    pitch = pitch >  89.0 ? 89.0 : pitch;
    pitch = pitch < -89.0 ? -89.0 : pitch;
    
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(action == GLFW_PRESS)
    {
        switch (button)
        {
            case GLFW_MOUSE_BUTTON_LEFT:
                isPress = true;
                break;
                
            default:
                break;
        }
    }
    
    if(action == GLFW_RELEASE)
    {
        isPress = false;
    }
}

void zoom_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    zoomLevel = (zoomLevel >= 1.0f && zoomLevel <= 45.0f) ? zoomLevel - yoffset : zoomLevel;
    zoomLevel = zoomLevel <= 1.0f ? 1.0f : zoomLevel;
    zoomLevel = zoomLevel >= 45.0f ? 45.0f : zoomLevel;
}

int main()
{
//================== PART 01 ==================//
    
    // init
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL.Version.0.1", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, zoom_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    
    // load gl func
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

//================== PART 02 ==================//
    
    // manage data --> VAO
    unsigned int VAO;
    glad_glGenVertexArrays(1, &VAO);
    glad_glBindVertexArray(VAO);
    
    unsigned int VBO;
    glad_glGenBuffers(1, &VBO);
    glad_glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glad_glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    unsigned int EBO;
    glad_glGenBuffers(1, &EBO);
    glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // data attributes
    glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glad_glEnableVertexAttribArray(0);
    
    glad_glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    glad_glEnableVertexAttribArray(1);
    
    glad_glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5*sizeof(float)));
    glad_glEnableVertexAttribArray(2);
    
    glad_glBindVertexArray(0);
    glad_glBindBuffer(GL_ARRAY_BUFFER, 0);
    glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
//================== PART 03 ==================//
    
    // shader --> shaderProgram
    unsigned int vertexShader;
    vertexShader = glad_glCreateShader(GL_VERTEX_SHADER);
    glad_glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glad_glCompileShader(vertexShader);
    
    // debug
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    unsigned int fragmentShader;
    fragmentShader = glad_glCreateShader(GL_FRAGMENT_SHADER);
    glad_glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glad_glCompileShader(fragmentShader);
    
    // debug
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    unsigned int shaderProgram;
    shaderProgram = glad_glCreateProgram();
    glad_glAttachShader(shaderProgram, vertexShader);
    glad_glAttachShader(shaderProgram, fragmentShader);
    glad_glLinkProgram(shaderProgram);
    
    // debug
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    glad_glDeleteShader(vertexShader);
    glad_glDeleteShader(fragmentShader);
    
//================== PART 04 ==================//
    
    // image
    const char* path = "/Users/jbqin/JavenData/CodeXcode/myOpenGL/myOpenGL/myOpenGL/JV.jpeg";
    
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* img = stbi_load(path, &width, &height, &channels, 0);
    
    // texture
    unsigned int texture;
    glad_glGenTextures(1, &texture);
    glad_glBindTexture(GL_TEXTURE_2D, texture);
    
    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glad_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
    glad_glGenerateMipmap(GL_TEXTURE_2D);
    
    stbi_image_free(img);
    glad_glBindTexture(GL_TEXTURE_2D, 0);
    
    
//================== PART 05 ==================//
    
    // some configuration
    glad_glPolygonMode(GL_FRONT_AND_BACK, /*GL_LINE*/GL_FILL);
    glad_glEnable(GL_DEPTH_TEST);
    
    // uniform need not update per frame
    glad_glUseProgram(shaderProgram);
    glad_glUniform1i(glad_glGetUniformLocation(shaderProgram, "uniformTexture"), 0);
    glad_glUniform4f(glad_glGetUniformLocation(shaderProgram, "uniformColor"), /*sin(glfwGetTime())*/ 0.5, 0.5f, 0.5, 0.5f);
    
//================== PART 06 ==================//
    
    // render loop
    while(!glfwWindowShouldClose(window))
    {
        glad_glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // bind something
        glad_glActiveTexture(GL_TEXTURE0);
        glad_glBindTexture(GL_TEXTURE_2D, texture);
        
        glad_glBindVertexArray(VAO);
        
        // set uniform update per frame
        //glad_glUniform4f(glad_glGetUniformLocation(shaderProgram, "uniformColor"), sin(glfwGetTime()), 0.5f, 0.5, 0.5f);

        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glm::mat4 proj = glm::perspective(glm::radians(zoomLevel), (float)WIDTH/(float)HEIGHT, 0.1f, 100.0f);
        for(int i = 0; i < 10; ++i)
        {
            // matrix for model view projection
            glm::mat4 model = glm::mat4(1);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, /*(float)glfwGetTime()*/ glm::radians(float(20.0 * (i+1))), glm::vec3(1, 0.3, 0.5));
            
            glm::mat4 trans = proj * view * model;
            glad_glUniformMatrix4fv(glad_glGetUniformLocation(shaderProgram, "uniformPosTran"), 1, GL_FALSE, glm::value_ptr(trans));
            
            // draw
            //glad_glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glad_glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // exit
    glfwTerminate();
    return 0;
}
