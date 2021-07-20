#version 330 core
struct Material {
    float shininess;
    float reflectivity;
};
uniform Material material;

struct Light {
    vec3 position;

    vec3 diffuse;
    vec3 ambient;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform Light light[4];

in vec2 pass_textureCoords;
in vec3 surfaceNormal;
in vec3 toLightVector[4];
in vec3 toCameraVector;
in vec4 worldPosition;
in float visibility;

out vec4 out_color;

uniform sampler2D backgroundTexture;
uniform sampler2D rTexture;
uniform sampler2D gTexture;
uniform sampler2D bTexture;
uniform sampler2D blendMap;

uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 viewPosition;

uniform float reflectivity;
uniform float  shineDamper;
uniform float ambientStrength;
uniform vec3 skyColor;

void main() {

    vec4 blendMapColour = texture(blendMap, pass_textureCoords);

    float backTextureAmount = 1 - (blendMapColour.r, blendMapColour.g, blendMapColour.b);
    vec2 tiledCoords = pass_textureCoords * 40.0;
    vec4 backgroundTextureColor = texture(backgroundTexture, tiledCoords) * backTextureAmount;
    vec4 rTextureColor = texture(rTexture, tiledCoords) * blendMapColour.r;
    vec4 gTextureColor = texture(gTexture, tiledCoords) * blendMapColour.g;
    vec4 bTextureColor = texture(bTexture, tiledCoords) * blendMapColour.b;

    vec4 totalColour = backgroundTextureColor + rTextureColor + gTextureColor + bTextureColor;


    vec3 unitNormal = normalize(surfaceNormal);
    vec3 unitVectorToCamera = normalize(viewPosition - vec3(worldPosition));

    if (dot(unitNormal, unitVectorToCamera) < 0.0)
        unitNormal = -unitNormal;
//    unitVectorToCamera = normalize(toCameraVector); // added now to replace former line if this works


    vec3 totalDiffuse = vec3(0.0f);
    vec3 totalSpecular = vec3(0.0f);
    vec3 totalAmbient = vec3(0.0f);
    vec3 runningResult = vec3(0.0f);

    for (int i = 0; i < 4; i++) {
        float distance = length(toLightVector[i]);

        vec3 unitLightVector = normalize(toLightVector[i]);

        float nDot1 = dot(unitNormal, unitLightVector);
        float brightness = max(nDot1, 0.0);

        vec3 lightDirection = -unitLightVector;
        vec3 reflectedLightDirection = reflect(lightDirection,unitNormal);
        float specularFactor = dot(reflectedLightDirection , unitVectorToCamera);

        specularFactor = max(specularFactor, 0.0);
//        float dampedFactor = pow(specularFactor, material.shininess);
        float dampedFactor = pow(specularFactor, 32.0f);

        // attenuation
        float attenuation = 1.0 / (light[i].constant + light[i].linear * distance + light[i].quadratic * (distance * distance));

        vec3 diffuse = (brightness * light[i].diffuse);
        vec3 specular = (dampedFactor * material.reflectivity * light[i].diffuse);
        vec3 ambient = (light[i].ambient * totalColour.rgb);

        ambient *= attenuation;
        diffuse  *= attenuation;
        specular *= attenuation;

        totalDiffuse = totalDiffuse + diffuse;
        totalSpecular = totalSpecular + specular;
        totalAmbient = totalAmbient + ambient;

        vec3 result = (ambient + diffuse + specular);
        runningResult += result;
    }
    totalDiffuse = max(totalDiffuse, 0.2f);

    vec4 combination1 = vec4(totalDiffuse, 1.0f) + vec4(totalSpecular, 1.0f) + vec4(totalAmbient, 1.0f);
    vec4 combination2 = vec4(totalDiffuse, 1.0f) * vec4(totalSpecular, 1.0f) * vec4(totalAmbient, 1.0f);
    vec4 combination3 = vec4(runningResult, 1.0f);

//    out_color = mix(vec4(skyColor, 1.0), vec4(runningResult, 1.0f), visibility);
    out_color = mix(vec4(skyColor, 1.0), combination3, visibility);

}
