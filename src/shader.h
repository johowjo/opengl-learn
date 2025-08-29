#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

struct Shader {
  GLuint id;
};

// struct vec4f {
//   float x, y, z, w;
// };

int use_shader(struct Shader *shader);
int init_shader(const char *vertex_path, const char *fragment_path,
                struct Shader *shader);
int set_uniform_4f(const char *attribute, struct Shader *shader, float x,
                   float y, float z, float w);
int set_uniform_1i(const char *attribute, struct Shader *shader, int value);
int delete_shader(struct Shader *shader);

#endif /* ifndef SHADER_H */
