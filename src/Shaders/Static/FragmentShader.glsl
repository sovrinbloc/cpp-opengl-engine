#version 330 core

struct Material {
    float shininess;
    float reflectivity;
};


uniform Material material;

struct Light {
    vec3 position;

    vec3 attenuation;
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
};

uniform Light light[4];


in vec2 pass_textureCoords;
in vec3 surfaceNormal;
in vec3 toLightVector[4];

in vec4 worldPosition;
in float visibility;

out vec4 out_color;

uniform sampler2D textureSampler;

uniform vec3 lightColor;
uniform vec3 viewPosition;

uniform float reflectivity;
uniform float shineDamper;
uniform float ambientStrength;
uniform vec3 skyColor;

void main() {
    vec3 totalDiffuse = vec3(0.0f);
    vec3 totalSpecular = vec3(0.0f);

    vec3 unitNormal = normalize(surfaceNormal);
    vec3 unitVectorToCamera = normalize(viewPosition - vec3(worldPosition));

    for (int i = 0; i < 4; i++) {
        float distance = length(toLightVector[i]);
        float attFactor = light[i].attenuation.x + (light[i].attenuation.y * distance) + (light[i].attenuation.z * distance * distance);

        vec3 unitLightVector = normalize(toLightVector[i]);

        float nDot1 = dot(unitNormal, unitLightVector);
        float brightness = max(nDot1, 0.2);

        vec3 lightDirection = -unitLightVector;
        vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);

        float specularFactor = dot(unitVectorToCamera, reflectedLightDirection);
        specularFactor = max(specularFactor, 0.0);

        float dampedFactor = pow(specularFactor, material.shininess);

        totalDiffuse = totalDiffuse + (brightness * light[i].diffuse) / attFactor;
        totalSpecular =  totalSpecular + (dampedFactor * material.reflectivity * light[i].specular) / attFactor;
    }
    totalDiffuse = max(totalDiffuse, 0.2f);

    vec4 textureColor = texture(textureSampler, pass_textureCoords);
    if (textureColor.a < 0.5) {
        discard;
    }

    out_color = vec4(totalDiffuse, 1.0) * textureColor + vec4(totalSpecular, 1.0);
    out_color = mix(vec4(skyColor, 1.0), out_color, visibility);
}
