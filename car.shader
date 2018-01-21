#shader vertex
#version 330 core


// input varyings
layout(location = 0) in vec3 vertexPosition;
in vec3 norm;
in vec2 texCoord;
layout(location = 1) in vec3 colors;

// uniforms
uniform vec3 light;
uniform mat4 modelMatrix;
uniform mat4 inverseModelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

// normal, texture coordinates, light in model coordinates
out vec3 normalOut;
out vec2 texCoordOut;
out vec3 lightOut;
out vec3 colorOut;
// position in model coordinates
out vec3 positionOut;
out vec3 fragPos;

void main() {
	// transforms light from world coordinates to model coordinates
	lightOut = (inverseModelMatrix * vec4(light, 1.0)).xyz;

	// copies normals and passes them to FS
	normalOut = norm;
	// copies texture coordinates and passes them to FS
	texCoordOut = texCoord;
	// copies position and passes it to FS (in model coordinates)
	positionOut = vertexPosition;

	colorOut = colors;

	fragPos = vec3(modelMatrix * vec4(vertexPosition, 1.0));

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPosition, 1.0);
}

#shader fragment
#version 330 core

// normal, texture coordinates, light in model coordinates
in vec3 normalOut;
in vec2 texCoordOut;
in vec3 lightOut;
in vec3 colorOut;
in vec3 fragPos;//world coordinate
// position in model coordinates
in vec3 positionOut;

// uniforms
uniform vec3 ambient;
// uniform sampler2DRect mire;

// out color
out vec4 frag_colour;

void main() {
	float sum = 0.0f;
	for (int i = 0; i < 3; i++) {
		sum += abs(positionOut[i] - lightOut[i]);
	}
	float distance = sqrt(sum);


	vec3 lightDir = normalize(lightOut - positionOut);
	// diffuse lighting contribution to color
	float diffuse = max(dot(normalize(normalOut), lightDir), 0.0f);
	frag_colour.rgb = vec3((diffuse + ambient)*colorOut);
	//frag_colour.r = ambient[0]*distance;
}
