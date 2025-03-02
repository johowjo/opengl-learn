#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include "shader.h"

const char* fragment_shader_source_path = "/Users/howardliao/opengl-learn/src/shaders/fragment_shader.txt";
const char* vertex_shader_source_path = "/Users/howardliao/opengl-learn/src/shaders/vertex_shader.txt";

void framebuffer_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void process_key(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, 1);
  }
}

int main() {
  glfwInit();

  // using OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow *window = glfwCreateWindow(600, 800, "learn OpenGL", NULL, NULL);

  if (window == NULL) {
    printf("failed to create window\n");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // initialize glad
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("failed to initialize glad\n");
    return -1;
  }

  // set viewport
  glViewport(0, 0, 600, 800);
  glfwSetFramebufferSizeCallback(window, framebuffer_callback);

  struct Shader shader;
  int success = init_shader(vertex_shader_source_path, fragment_shader_source_path, &shader);
  // printf("%d\n", success);
  
  //
  float vertices[] = {
      // positions         // colors
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
      0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f  // top
  };

  unsigned int indices[] = {
      // note that we start from 0!
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };

  GLuint VAO, VBO;
  // GLuint EBO;
  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // glGenBuffers(1, &EBO);
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);
  glBindVertexArray(0);

  // run render loop
  while (!glfwWindowShouldClose(window)) {
    process_key(window);

    // set color
    glClearColor(0.2f, 0.3f, 0.1f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT);
    use_shader(&shader);

    //
    float time = glfwGetTime();
    float value = (sin(time) / 2.0f) + 0.5f;

    set_uniform_4f("color", &shader, 0.0f, value, 0.0f, 1.0f);
    // int vertexColorLocation = glGetUniformLocation(shaderProgram, "color");
    // glUniform4f(vertexColorLocation, 0.0f, value, 0.0f, 1.0f);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  delete_shader(&shader);

  glfwTerminate();
  return 0;
}
