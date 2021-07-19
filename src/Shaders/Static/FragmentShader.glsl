#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};


uniform Material material;

struct Light {
    vec3 color;
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
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

mat3 calculateLighting(vec3 unitNormal, vec3 unitVectorToCamera, vec3 toLightVector[4], Light lights[4], Material material);

void main() {

    vec4 textureColor = texture(textureSampler, pass_textureCoords);
    if (textureColor.a < 0.5) {
        discard;
    }

    vec3 unitNormal = normalize(surfaceNormal);
    vec3 unitVectorToCamera = normalize(viewPosition - vec3(worldPosition));

    mat3 lv = calculateLighting(unitNormal, unitVectorToCamera, toLightVector, light, material);


    out_color = vec4(lv[0], 1.0) * textureColor + vec4(lv[2], 1.0) + vec4(lv[1], 1.0);
    out_color = mix(vec4(skyColor, 1.0), out_color, visibility);
}



mat3 calculateLighting(vec3 unitNormal, vec3 unitVectorToCamera, vec3 toLightVector[4], Light lights[4], Material material) {
    vec3 totalDiffuse;
    vec3 totalSpecular;
    vec3 totalAmbient;

    for (int i = 0; i < 4; i++) {
        totalAmbient = totalAmbient + light[i].ambient * material.ambient;
        vec3 unitLightVector = normalize(toLightVector[i]);

        float nDot1 = dot(unitNormal, unitLightVector);
        float brightness = max(nDot1, 0.2);

        vec3 lightDirection = -unitLightVector;
        vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);

        float specularFactor = dot(unitVectorToCamera, reflectedLightDirection);
        specularFactor = max(specularFactor, 0.0);
        float dampedFactor = pow(specularFactor, material.shininess);

        totalDiffuse = totalDiffuse + (brightness * light[i].color * material.diffuse) * light[i].diffuse;
        totalSpecular =  totalSpecular + (dampedFactor * material.specular) * light[i].specular;
    }

    return mat3(totalDiffuse, totalSpecular, totalAmbient);
}