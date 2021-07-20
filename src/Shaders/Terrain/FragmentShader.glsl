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


vec3 CalcPointLight(Light light, vec3 lightVector, vec3 unitNormal, vec3 unitVectorToCamera, vec4 totalColour);
vec3 CalcDirLight(Light light, vec3 unitNormal, vec3 unitVectorToCamera, vec4 totalColour);

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
//    unitVectorToCamera = normalize(toCameraVector); // added now to replace former line if this works

    if (dot(unitNormal, unitVectorToCamera) < 0.0)
        unitNormal = -unitNormal;

    vec3 runningResult = vec3(0.0f);

    for (int i = 0; i < 4; i++) {
        if (light[i].constant != -1) {
            runningResult = runningResult + CalcPointLight(light[i], toLightVector[i], unitNormal, unitVectorToCamera, totalColour);
        } else {
            runningResult = runningResult + CalcDirLight(light[i], unitNormal, unitVectorToCamera, totalColour);
        }
    }

    vec4 results = vec4(runningResult, 1.0f);

    out_color = mix(vec4(skyColor, 1.0), results, visibility);

}

vec3 CalcPointLight(Light light, vec3 lightVector, vec3 unitNormal, vec3 unitVectorToCamera, vec4 totalColour) {
    vec3 unitLightVector = normalize(lightVector);

    float nDot1 = dot(unitNormal, unitLightVector);
    float brightness = max(nDot1, 0.0);

    vec3 lightDirection = -unitLightVector;
    vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);
    float specularFactor = dot(unitVectorToCamera, reflectedLightDirection);

    specularFactor = max(specularFactor, 0.0);
    float dampedFactor = pow(specularFactor, material.shininess);

    // attenuation (looks okay)
    float distance = length(lightVector); // checks out
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    //        dampedFactor = max(dampedFactor, .65);

    vec3 ambient = (light.ambient * totalColour.rgb);
    vec3 diffuse = (brightness * light.diffuse);
    vec3 specular = (dampedFactor * material.reflectivity * light.specular);

    ambient *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    
    return ambient + diffuse + specular;
}


vec3 CalcDirLight(Light light, vec3 unitNormal, vec3 unitVectorToCamera, vec4 totalColour)
{
    vec3 lightDirection = normalize(-light.position);
    // diffuse shading
    float diff = max(dot(unitNormal, lightDirection), 0.0);
    // specular shading
    vec3 reflectDirection = reflect(-lightDirection, unitNormal);
    float spec = pow(max(dot(unitVectorToCamera, reflectDirection), 0.0), material.shininess);
    // combine results
    vec3 diffuse  = light.diffuse  * diff * totalColour.rgb;
    vec3 specular = light.specular * spec * totalColour.rgb;
    vec3 ambient  = light.ambient  * totalColour.rgb;
    return (ambient + diffuse + specular);
}