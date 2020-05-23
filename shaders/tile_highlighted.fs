#version 330 core

in vec2 texcoord_fs;
in vec3 pos_in;
in vec3 normal_in;

in mat4 world_fs;

// Ouput data
out vec4 color;

uniform sampler2D sampler;

struct DirectionalLight {
  vec3 color;
  vec3 direction;
  float intensity;
};

struct PointLight {
  vec3 color;
  vec3 pos;
  float intensity;
};

DirectionalLight light;
PointLight point_light;

void main() {
  light.color = vec3(1.0, 1.0, 1.0);
  light.intensity = 0.4;
  light.direction = vec3(1.0, -5.0, 1.0);

  point_light.color = vec3(0.0, 0.0, 0.0);
  point_light.intensity = 0.8;
  point_light.pos = vec3(world_fs * vec4(1, 1, 1, 1)).xyz;
  
  vec4 ambient_light = vec4(0.7, 0.7, 0.7, 1.0);
  
  float diffuse_factor = dot(normalize(normal_in), -light.direction);
  
  vec4 diffuse_color;
  
  if (diffuse_factor > 0) {
    diffuse_color = vec4(light.color * light.intensity * diffuse_factor, 1.0);
  } else {
    diffuse_color = vec4(0, 0, 0, 0);
  }
  
  float d = length(point_light.pos - pos_in);
  vec4 point_color = vec4(point_light.color * point_light.intensity / (d*d), 1.0);
  
  vec4 selection_color = vec4(-0.5, 0.9, -0.5, 1.0);
  
  color = texture2D(sampler, texcoord_fs.st) * (diffuse_color + ambient_light + point_color + selection_color);
}


