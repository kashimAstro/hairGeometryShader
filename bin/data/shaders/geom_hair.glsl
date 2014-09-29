#version 150

#define N 50

layout(triangles) in;
layout(line_strip) out;
layout(max_vertices = N) out;

const float NSTEPS = N - 1.0;

uniform float hairLeng;
uniform float time;
uniform mat4 projection;
uniform mat4 modelview;

out vec3 fcolor;

void main() {
	  vec3 a = vec3(gl_in[1].gl_Position - gl_in[0].gl_Position);
	  vec3 b = vec3(gl_in[2].gl_Position - gl_in[0].gl_Position);

	  vec3 center = vec3(gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) / 3.0;
	  vec3 normal = normalize(cross(b, a));

	  fcolor = vec3(0.0);
	  gl_Position = projection * modelview * vec4(center, 1.0);
	  EmitVertex();

	  float delta = hairLeng / float(NSTEPS);
	  float t = delta;
	  for (int i = 0; i < NSTEPS; ++i) {
	      fcolor = vec3(t / hairLeng);
	      vec3 position = normal * t + center;
	      position.y += -0.1 * t * t;
	      gl_Position = projection * modelview * vec4(position, 1.0);
	      EmitVertex();
	      t += delta;
	  }
	  EndPrimitive();
}
