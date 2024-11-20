#version 400 core

in vec3 position;
in vec3 normal;
in vec2 texCoord;

uniform vec3 Kd;
uniform vec3 Ks;

uniform vec3 Ia;
uniform vec3 Id;
uniform vec3 Is;
uniform float shininess;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;

layout (location = 0) out vec4 fragColor;

vec3 ads()
{
    vec3 n = normalize( normal );
    vec3 l = normalize( lightPosition - position );
    vec3 v = normalize( cameraPosition - position );
    vec3 r = reflect( -l, n );

    float diff = max (dot(n, l), 0.0f);
    vec3 diffuse = diff * Id;

    float spec = pow(max(dot(v, r), 0.0), shininess);
    vec3 specular = Ks * spec * Is;

    vec3 result = ((Ia + diffuse) * Kd) + specular;

    return result;
}

void main() {
    fragColor = vec4(ads(), 1.0f);
}
