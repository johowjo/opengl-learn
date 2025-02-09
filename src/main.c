#include <glad/glad.h>  // Include GLAD before GLFW
#include <GLFW/glfw3.h>
#include <stdio.h>

// Callback for window resizing
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

int main() {
  // Initialize GLFW
  if (!glfwInit()) {
    printf("Failed to initialize GLFW\n");
    return -1;
  }

  // Configure GLFW
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create window
  GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL with GLAD", NULL, NULL);
  if (!window) {
    // std::cerr << "Failed to create GLFW window\n";
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Initialize GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    // std::cerr << "Failed to initialize GLAD\n";
    return -1;
  }

  // Set viewport
  glViewport(0, 0, 800, 600);

  // Render loop

  float f1 = 0.1f;
  float f2 = 0.1f;
  float f3 = 0.1f;
  float f4 = 0.1f;

  while (!glfwWindowShouldClose(window)) {
    // Clear screen
    glClearColor(f1, f2, f3, f4);
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap buffers and poll events
    glfwSwapBuffers(window);
    glfwPollEvents();
    f1 += 0.01f;
    f2 += 0.01f;
    f3 += 0.01f;
    f4 += 0.01f;
  }

  // Cleanup
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}


