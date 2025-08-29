#include "shader.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 700

int use_shader(struct Shader *shader) {
  if (shader == NULL) {
    return 1;
  }

  glUseProgram(shader->id);
  return 0;
}

int delete_shader(struct Shader *shader) {
  glDeleteProgram(shader->id);
  return 1;
}

int set_uniform_4f(const char *attribute, struct Shader *shader, float x,
                   float y, float z, float w) {
  int attribute_location = glGetUniformLocation(shader->id, attribute);
  glUniform4f(attribute_location, x, y, z, w);
  return 0;
}

int set_uniform_1i(const char *attribute, struct Shader *shader, int value) {
  int attribute_location = glGetUniformLocation(shader->id, attribute);
  glUniform1i(attribute_location, value);
  return 0;
}

void read_shader_source(const char *source_path, char **shader_source) {
  FILE *file = fopen(source_path, "r");
  if (file == NULL) {
    perror("failed to read from source\n");
    shader_source = NULL;
    return;
  }

  fseek(file, 0, SEEK_END);
  long len = ftell(file);
  rewind(file);

  *shader_source = (char *)malloc(len + 1);
  if (*shader_source == NULL) {
    fclose(file);
    return;
  }

  fread(*shader_source, 1, len, file);
  (*shader_source)[len] = '\0';

  fclose(file);
}

int init_shader(const char *vertex_path, const char *fragment_path,
                struct Shader *shader) {
  char *vertex_code, *fragment_code;
  read_shader_source(vertex_path, &vertex_code);
  read_shader_source(fragment_path, &fragment_code);

  if (vertex_code == NULL || fragment_code == NULL) {
    printf("failed to read source file\n");
    return -1;
  }

  int success;
  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_code, NULL);
  glCompileShader(vertex_shader);
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

  if (!success) {
    printf("compilation of vertex shader failed");
    return -1;
  }

  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_code, NULL);
  glCompileShader(fragment_shader);
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

  if (!success) {
    printf("compilation of fragment shader failed");
    return 1;
  }

  GLuint shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);
  glGetProgramiv(shader_program, GL_LINK_STATUS, &success);

  if (!success) {
    printf("linking shader failed");
    return 1;
  }

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  free(vertex_code);
  free(fragment_code);

  // fclose(vertex_file);
  // fclose(fragment_file);

  shader->id = shader_program;
  return 0;
}
