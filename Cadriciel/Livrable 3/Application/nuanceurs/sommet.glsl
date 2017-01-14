#version 420

uniform mat4 modelViewProjection;
uniform mat4 matrModel;
uniform mat4 matrVue;
uniform mat4 matrProjection;
uniform mat3 matrNormal;

layout (location = 0) in vec3 position;
layout(location = 1) in vec3 normale;
layout(location = 2) in vec2 texCoordIn;
layout(location=3) in vec4 Color;

// Définition des paramètres des sources de lumière
layout(std140) uniform LightSourceParameters
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 position[2];
	vec3 spotDirection[2];
	float spotExponent;
	float spotCutoff;            // ([0.0,90.0] ou 180.0)
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
} LightSource;

// Définition des paramètres des matériaux
layout(std140) uniform MaterialParameters
{
	vec4 emission;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
} FrontMaterial;

// Définition des paramètres globaux du modèle de lumière
layout(std140) uniform LightModelParameters
{
	vec4 ambient;       // couleur ambiante
} LightModel;

layout(std140) uniform varsUnif
{
	int ambianteActive;
	int directionelleActive;
	int spotActive;
};

out vec4 couleur;
out vec3 normal;
out vec3 lumiDir[2];
out vec3 obsVec;
varying vec2 texCoord;

void main()
{
	gl_Position = modelViewProjection * vec4(position, 1.0);
	texCoord = texCoordIn;
	couleur = Color;
	//calcul de la normale
	normal = normalize(vec3(matrNormal*normale));
	//Calcul de la position du sommet dans l'espace de la camera
	vec3 pos = vec3(matrVue*matrModel*vec4(position, 1.0));
	for (int i = 0; i < 2; ++i) {
		if (directionelleActive == 1)//lumiere directionnelle
		{
			//LightSource[0].position.w = 0;
			lumiDir[i] = normalize(vec3(matrVue*LightSource.position[i]));
		}
		else //lumiere positionnelle (le spot)
			lumiDir[i] = normalize(vec3((matrVue*LightSource.position[i]).xyz - pos));
	}
	//Vecteur de la direction vers l'oservateur
	obsVec = normalize(-pos);
}