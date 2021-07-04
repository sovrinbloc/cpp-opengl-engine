#version 330 core

in vec2 pass_textureCoords;
in vec3 surfaceNormal;
in vec3 toLightVector;

in vec4 worldPosition;

out vec4 out_color;

uniform sampler2D textureSampler;

uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 viewPosition;

uniform float reflectivity;
uniform float shineDamper;
uniform float ambientStrength;

void main()
{

    vec3 ambient = ambientStrength * lightColor;

    vec3 unitNormal = normalize(surfaceNormal);
    vec3 unitLightVector = normalize(toLightVector);

    float nDot1 = dot(unitNormal, unitLightVector);
    float brightness = max(nDot1, 0.2);
    vec3 diffuse = brightness *  lightColor;

    vec3 unitVectorToCamera = normalize(viewPosition - vec3(worldPosition));
    vec3 lightDirection = -unitLightVector;
    vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);

    float specularFactor = dot(unitVectorToCamera, reflectedLightDirection);
    specularFactor = max(specularFactor, 0.0);
    float dampedFactor = pow(specularFactor, shineDamper);
    vec3 specular = dampedFactor * reflectivity * lightColor;


    out_color = vec4(diffuse, 1.0) * texture(textureSampler, pass_textureCoords) + vec4(ambient, 1.0) + vec4(specular, 1.0);

}
