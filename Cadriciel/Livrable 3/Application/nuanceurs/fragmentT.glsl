#version 420

layout(binding=0) uniform sampler2D diffuseTex;

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

varying vec2 texCoord;
in vec4 couleur;
in vec3 normal;
in vec3 lumiDir[2];
in vec3 obsVec;
out vec4 color;


float calculerSpot(in vec3 spotDir, in vec3 L)
{
	float facteur;

	float cosG = dot(L, spotDir);
	float cosD = cos(radians(LightSource.spotCutoff));
	float c = LightSource.spotExponent;

	if (cosG > cosD)
	{
		facteur = pow(cosG, c);
	}
	else
	{
		facteur = 0.0f;
	}

	return facteur;
}

vec4 calculerReflexion(in vec3 L, in vec3 N, in vec3 O)
{
	//Calcule de la composante ambiente
	vec4 coul;
	if (ambianteActive == 1)
		return  FrontMaterial.emission + FrontMaterial.ambient * LightModel.ambient;
	else
		coul = FrontMaterial.emission + FrontMaterial.ambient * LightModel.ambient + LightSource.ambient * FrontMaterial.ambient;
	float NdotL = max(dot(N, L), 0.0);

	if (NdotL > 0.0)
	{
		//Calcule de la composante diffuse
		coul += FrontMaterial.diffuse * LightSource.diffuse * NdotL;

		//Calcul de la composante speculaire
		vec3 R = reflect(-L, N); //reflexion de L par rapport a N

		//Speculaire Phong
		float NdotHV = max(0.0, dot(R, O));
		coul += FrontMaterial.specular * LightSource.specular * pow(NdotHV, FrontMaterial.shininess);
	}
	return coul;
}

void main()
{
    color = vec4(0.5, 0.5, 0.5, 1.0);
   //color = texture2D(diffuseTex, texCoord.st);
    //color = couleur;

   float dist, attenuation, effetSpot;
   for (int i = 0; i < 2; ++i) {
	   dist = length(lumiDir[i]);
	  // effetSpot = calculerSpot(normalize(LightSource.spotDirection[i]), -lumiDir[i]);
	   float cosG = dot(-lumiDir[i], normalize(LightSource.spotDirection[i]));
	   float cosD = cos(radians(LightSource.spotCutoff));
	   float c = LightSource.spotExponent;
	   attenuation = 1.0;
	   //if (directionelleActive == 1)
	   //attenuation = 1.0; //On attenue pas la lumiere directionnelle
	   if (spotActive == 1) {

		  if (cosG > cosD)
		   {
			   effetSpot = pow(cosG, c);
			   attenuation = effetSpot / (LightSource.constantAttenuation +
				   LightSource.linearAttenuation * dist +
				   LightSource.quadraticAttenuation * dist * dist);
			   color += attenuation*calculerReflexion(lumiDir[i], normal, obsVec);
		   }
		   else
			   color += FrontMaterial.emission + FrontMaterial.ambient * LightModel.ambient;
		   color += attenuation*calculerReflexion(lumiDir[i], normal, obsVec);
	   }
	   else {
		   color += attenuation*calculerReflexion(lumiDir[i], normal, obsVec);
	   }
	   
   }

   color = color*texture2D(diffuseTex, texCoord.st);
  // color = clamp(coul, 0.0, 1.0);
}