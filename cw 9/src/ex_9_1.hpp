#include "glew.h"
#include <GLFW/glfw3.h>
#include "glm.hpp"
#include "ext.hpp"
#include <iostream>
#include <cmath>
#include "Shader_Loader.h"
#include "Render_Utils.h"
#include "Texture.h"
#include "Box.cpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include "SOIL/SOIL.h"



const unsigned int SHADOW_WIDTH = 6024, SHADOW_HEIGHT = 6024;
int WIDTH = 900, HEIGHT = 900;
bool isTransitioningSpace = false;
bool isTransitioningMars = false;
int transitionCount = 0;
int transitionFrames = 20;
int timeframesCount = 0;
int timeframes = 50;
int riseFrames = 100;
bool earthquake = false;

namespace models {
	Core::RenderContext shipContext;
	Core::RenderContext sphereContext;
	Core::RenderContext skyboxContext;
	Core::RenderContext doorContext;
	Core::RenderContext closeDoorContext;
	Core::RenderContext planeContext;
	Core::RenderContext roomContext;
	Core::RenderContext windowContext;
	Core::RenderContext testContext;
	Core::RenderContext floorContext;
	Core::RenderContext wallContext;
	Core::RenderContext lampContext;
	Core::RenderContext ground;
	Core::RenderContext armchair;
	Core::RenderContext plantPot;
	Core::RenderContext plantLeaves;
	Core::RenderContext cabinet;
	Core::RenderContext table;
	Core::RenderContext sideTable;
	Core::RenderContext ufo;
	Core::RenderContext r2d2;
	Core::RenderContext fern;
	Core::RenderContext waterTower;
	Core::RenderContext astronaut;
	Core::RenderContext helmet;
	Core::RenderContext star;
	Core::RenderContext soldier;
	Core::RenderContext sword;
	Core::RenderContext alien;
	Core::RenderContext asteroid;
	Core::RenderContext egg;
	Core::RenderContext mountain;
	Core::RenderContext roof;
	Core::RenderContext dish;
}

namespace texture {
	GLuint cubemapTexture;
	GLuint cubemapTextureFirstMission;

	GLuint defaultTexture;
	GLuint defaultTextureNormal;
	GLuint defaultTextureArm;

	GLuint spaceshipTexture;
	GLuint spaceshipTextureNormal;
	GLuint spaceshipTextureArm;

	GLuint floorTexture;
	GLuint floorTextureNormal;
	GLuint floorTextureArm;

	GLuint wallTexture;
	GLuint wallTextureNormal;
	GLuint wallTextureArm;

	GLuint windowTexture;
	GLuint windowTextureNormal;
	GLuint windowTextureArm;

	GLuint doorTexture;
	GLuint doorTextureNormal;
	GLuint doorTextureArm;

	GLuint lampTexture;
	GLuint lampTextureNormal;
	GLuint lampTextureArm;
	//armchair
	GLuint armchairTexture;
	GLuint armchairTextureNormal;
	// plant
	GLuint plantPotTexture;
	GLuint plantPotNormal;
	GLuint plantLeavesTexture;
	//cabinet
	GLuint cabinetTexture;
	GLuint cabinetTextureNormal;
	GLuint cabinetTextureArm;
	// table
	GLuint tableTexture;
	GLuint tableTextureNormal;
	GLuint tableTextureArm;
	// sideTable
	GLuint sideTableTexture;
	GLuint sideTableextureNormal;
	GLuint sideTableTextureArm;
	// ufo
	GLuint ufoTexture;
	GLuint ufoTextureNormal;
	//fern
	GLuint fernTexture;
	// corridor
	GLuint r2d2Texture;
	// alien
	GLuint alienTexture;
	GLuint alienTextureNormal;
	// waterTower
	GLuint waterTowerTexture;
	GLuint waterTowerTextureNormal;
	// asteroid
	GLuint asteroidTexture;
	GLuint asteroidTextureNormal;
	GLuint asteroidTexture3;
	// egg
	GLuint eggTexture;
	// roof
	GLuint roofTexture;
	//mounatin
	GLuint mountainTexture;
	GLuint mountainTextureNormal;

	// planets
	GLuint groundTexture;
	GLuint sunTexture;
	GLuint marsTexture;
	GLuint mercuryTexture;
	GLuint moonTexture;
	GLuint neptuneTexture;
	GLuint earthTexture;
	GLuint earthTextureNormal;
	GLuint earthClouds;
	// dish
	GLuint dishTexture;

	GLuint astronautTexture;
	GLuint astronautTextureNormal;

	GLuint helmetTexture;
	GLuint helmetTextureNormal;

	GLuint starTexture;

	GLuint soldierTexture;

	GLuint swordTexture;
	GLuint swordTextureNormal;
	GLuint swordTextureRough;

	GLuint alien;
}

GLuint depthMapFBO;
GLuint depthMap;
GLuint depthMapShipFBO;
GLuint depthMapShip;

GLuint bloomTextureFBO;
unsigned int colorBuffers[2];
unsigned int blurFBO[2];
unsigned int blurBuffer[2];

GLuint program;
GLuint programRoomLamp;
GLuint programSun;
GLuint programTest;
GLuint programDepth;
GLuint programSkybox;
GLuint programBlur;
GLuint programBloom;
GLuint programlightPlace;

GLuint triangleVAO;

Core::Shader_Loader shaderLoader;

glm::vec3 sunPos = glm::vec3(-4.740971f, 2.149999f, 0.369280f);
glm::vec3 sunDir = glm::vec3(-0.93633f, 0.351106, 0.003226f);
glm::vec3 sunColor = glm::vec3(0.9f, 0.9f, 0.7f) * 8;

glm::vec3 cameraPos = glm::vec3(0.479490f, 1.250000f, -2.124680f);
glm::vec3 cameraDir = glm::vec3(-0.354510f, 0.000000f, 0.935054f);

glm::vec3 spaceshipPos = glm::vec3(-995.0f, 0.0f, -5.0f);
glm::vec3 spaceshipDir = glm::vec3(-1.f, 0.000000f, -0.02f);

glm::vec3 starPos = glm::vec3(-0.281308f, 1.791063f, -1.625526f);
glm::vec3 starDir = glm::vec3(0.028363f, 0.000000f, 0.999599f);

float aspectRatio = 1.f;
float exposition = 1.f;

glm::vec3 pointlightPos = glm::vec3(0, 1.89622, 0.0008);
glm::vec3 pointlightColor = glm::vec3(0.9f, 0.9f, 0.7f) * 4;

glm::vec3 spotlightPos = glm::vec3(0, 0, 0);
glm::vec3 spotlightConeDir = glm::vec3(0, 0, 0);
glm::vec3 spotlightColor = glm::vec3(0.4, 0.4, 0.9) * 7;

glm::vec3 lightPlacePos = glm::vec3(-1000.f, 0.f, -5.f);

float lastTime = -1.f;
float deltaTime = 0.f;

glm::mat4 lightVP = glm::ortho(-20.f, 20.f, -20.f, 20.f, 1.0f, 30.0f) * glm::lookAt(sunPos, sunPos - sunDir, glm::vec3(0, 1, 0) * 50);
glm::mat4 lightShipVP;

void applyEarthquakeEffect(glm::vec3& cameraPos, GLfloat earthquakeIntensity) {
	GLfloat randomOffset = ((GLfloat)rand() / RAND_MAX) * 2.0f - 1.0f;
	cameraPos.x += randomOffset * earthquakeIntensity;
	randomOffset = ((GLfloat)rand() / RAND_MAX) * 2.0f - 1.0f;
	cameraPos.y += randomOffset * earthquakeIntensity;
	randomOffset = ((GLfloat)rand() / RAND_MAX) * 2.0f - 1.0f;
	cameraPos.z += randomOffset * earthquakeIntensity;
}

// colision part
bool astronautVisible = true;
bool helmetVisible = true;
bool astronautStarVisible = true;

bool afterAsteroids = false;
bool isEggGiven = false;
bool eggVisible = true;
bool alienStarVisible = true;
bool alienStarPicked = false;
bool spaceStarVisible = true;
bool spaceStarPicked = false;
bool astronautStarPicked = false;

bool fallAsteroid = false;
float fallSpeed = 2.0f;
glm::vec3 asteroidPosition = glm::vec3(-20.0f, 20.0f, 7.0f);
glm::vec3 asteroidPosition2 = glm::vec3(-22.0f, 20.0f, 5.0f);
glm::vec3 asteroidPosition3 = glm::vec3(-18.0f, 18.0f, 9.0f);
glm::vec3 asteroidPosition4 = glm::vec3(-22.0f, 20.0f, 10.0f);
glm::vec3 asteroidPosition5 = glm::vec3(-26.8f, 20.0f, 8.0f);
glm::vec3 asteroidPosition6 = glm::vec3(-24.0f, 20.0f, 6.0f);

float rotationAngle = 0.2f;

float generateRandomFloat(float minValue, float maxValue) {
	return minValue + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (maxValue - minValue));
}

float helmetX = generateRandomFloat(-2.3f, -5.8f);
float helmetZ = generateRandomFloat(-24.0f, 4.8f);
bool gameStart = true;

bool checkCollision(const glm::vec3& spaceshipPos, const glm::vec3& otherObjectPos) {
	float distance = glm::length(spaceshipPos - otherObjectPos);
	float collisionThreshold = 1.0f;

	if (distance < collisionThreshold)
		return true; // Collision
	else
		return false; // No collision
}
void updateDeltaTime(float time) {
	if (lastTime < 0) {
		lastTime = time;
		return;
	}

	deltaTime = time - lastTime;
	if (deltaTime > 0.1) deltaTime = 0.1;
	lastTime = time;
}
glm::mat4 createCameraMatrix()
{
	glm::vec3 cameraSide = glm::normalize(glm::cross(cameraDir, glm::vec3(0.f, 1.f, 0.f)));
	glm::vec3 cameraUp = glm::normalize(glm::cross(cameraSide, cameraDir));
	glm::mat4 cameraRotrationMatrix = glm::mat4({
		cameraSide.x,cameraSide.y,cameraSide.z,0,
		cameraUp.x,cameraUp.y,cameraUp.z ,0,
		-cameraDir.x,-cameraDir.y,-cameraDir.z,0,
		0.,0.,0.,1.,
		});
	cameraRotrationMatrix = glm::transpose(cameraRotrationMatrix);
	glm::mat4 cameraMatrix = cameraRotrationMatrix * glm::translate(-cameraPos);

	return cameraMatrix;
}
glm::mat4 createPerspectiveMatrix(float scale = 1.0){
	glm::mat4 perspectiveMatrix;
	float n = 0.05;
	float f = 20.;
	float aspectRatioLocal = aspectRatio;

	if (scale != 1.0) 
		aspectRatioLocal = 1.0;

	perspectiveMatrix = glm::mat4({
		1 * scale,0,0.,0.,
		0.,aspectRatioLocal * scale,0.,0.,
		0.,0.,(f + n) / (n - f),2 * f * n / (n - f),
		0.,0.,-1.,0.,
		});

	perspectiveMatrix = glm::transpose(perspectiveMatrix);

	return perspectiveMatrix;
}

void drawObjectPBR(Core::RenderContext& context, glm::mat4 modelMatrix, GLuint texture = texture::defaultTexture, GLuint textureNormal = texture::defaultTextureNormal, GLuint textureArm = texture::defaultTextureArm) {
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(program, "depthMap"), 0);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glUniformMatrix4fv(glGetUniformLocation(program, "lightVP"), 1, GL_FALSE, (float*)&lightVP);

	glActiveTexture(GL_TEXTURE1);
	glUniform1i(glGetUniformLocation(program, "depthMapShip"), 1);
	glBindTexture(GL_TEXTURE_2D, depthMapShip);
	glUniformMatrix4fv(glGetUniformLocation(program, "lightShipVP"), 1, GL_FALSE, (float*)&lightShipVP);

	glm::mat4 viewProjectionMatrix = createPerspectiveMatrix() * createCameraMatrix();
	glm::mat4 transformation = viewProjectionMatrix * modelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(program, "transformation"), 1, GL_FALSE, (float*)&transformation);
	glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, GL_FALSE, (float*)&modelMatrix);

	glUniform1f(glGetUniformLocation(program, "exposition"), exposition);

	glUniform3f(glGetUniformLocation(program, "cameraPos"), cameraPos.x, cameraPos.y, cameraPos.z);

	glUniform3f(glGetUniformLocation(program, "sunPos"), sunPos.x, sunPos.y, sunPos.z);
	glUniform3f(glGetUniformLocation(program, "sunColor"), sunColor.x, sunColor.y, sunColor.z);

	glUniform3f(glGetUniformLocation(program, "lightPos"), pointlightPos.x, pointlightPos.y, pointlightPos.z);
	glUniform3f(glGetUniformLocation(program, "lightColor"), pointlightColor.x, pointlightColor.y, pointlightColor.z);

	glUniform3f(glGetUniformLocation(program, "spotlightConeDir"), spotlightConeDir.x, spotlightConeDir.y, spotlightConeDir.z);
	glUniform3f(glGetUniformLocation(program, "spotlightPos"), spotlightPos.x, spotlightPos.y, spotlightPos.z);
	glUniform3f(glGetUniformLocation(program, "spotlightColor"), spotlightColor.x, spotlightColor.y, spotlightColor.z);

	glUniform3f(glGetUniformLocation(program, "lightPlacePos"), lightPlacePos.x, lightPlacePos.y, lightPlacePos.z);

	Core::SetActiveTexture(texture, "colorTexture", program, 2);
	Core::SetActiveTexture(textureNormal, "normalSampler", program, 3);
	Core::SetActiveTexture(textureArm, "armSampler", program, 4);
	Core::DrawContext(context);
}

void drawObjectDepth(Core::RenderContext& context, glm::mat4 viewProjection, glm::mat4 model) {
	glUniformMatrix4fv(glGetUniformLocation(programDepth, "viewProjectionMatrix"), 1, GL_FALSE, (float*)&viewProjection);
	glUniformMatrix4fv(glGetUniformLocation(programDepth, "modelMatrix"), 1, GL_FALSE, (float*)&model);
	Core::DrawContext(context);
}

void renderShadowMap(GLuint depthFBO, glm::mat4 light) {
	float time = glfwGetTime();
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	//bindowanie FBO
	glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
	//czyszczenie mapy głębokości 
	glClear(GL_DEPTH_BUFFER_BIT);
	//ustawianie programu
	glUseProgram(programDepth);

	drawObjectDepth(models::doorContext, light, glm::mat4());
	drawObjectDepth(models::planeContext, light, glm::mat4());
	drawObjectDepth(models::roomContext, light, glm::mat4());
	drawObjectDepth(models::windowContext, light, glm::mat4());
	drawObjectDepth(models::lampContext, light, glm::mat4());
	drawObjectDepth(models::sphereContext, light, glm::translate(pointlightPos) * glm::scale(glm::vec3(.115f)));

	// astronaut
	drawObjectDepth(models::astronaut, light, glm::mat4() * glm::translate(glm::vec3(1.3f, 0.f, -2.95f)) *
		glm::rotate(glm::mat4(), glm::radians(-180.f), glm::vec3(0, 1, 1)) * glm::scale(glm::vec3(.75f)));
	//alien
	drawObjectDepth(models::alien, light, glm::mat4() * glm::translate(glm::vec3(6.f, 0.f, 6.f))
		* glm::rotate(glm::mat4(), glm::radians(90.f), glm::vec3(1, 0, 0))
		* glm::rotate(glm::mat4(), glm::radians(-180.f), glm::vec3(0, 1, 0))
		* glm::rotate(glm::mat4(), glm::radians(90.f), glm::vec3(0, 0, 1))
		* glm::scale(glm::vec3(0.6f)));
	// chair
	drawObjectDepth(models::armchair, light, glm::mat4() * glm::translate(glm::vec3(-1.f, 0.6f, 1.5f)) *
		glm::rotate(glm::mat4(), glm::radians(-180.f), glm::vec3(0, 1, 1)) * glm::scale(glm::vec3(.03f)));
	// pot
	drawObjectDepth(models::plantPot, light, glm::mat4() * glm::translate(glm::vec3(1.2f, 0.0f, -1.5f)) *
		glm::scale(glm::vec3(.02f)));
	// cabinet
	drawObjectDepth(models::cabinet, light, glm::mat4() * glm::translate(glm::vec3(1.4f, 0.0f, 0.f)) * glm::rotate(glm::mat4(), glm::radians(-90.f), glm::vec3(1, 0, 0)) *
		glm::rotate(glm::mat4(), glm::radians(-90.f), glm::vec3(0, 0, 1)) * glm::scale(glm::vec3(.8f)));
	// table
	drawObjectDepth(models::table, light, glm::mat4() * glm::translate(glm::vec3(-1.f, 0.0f, 0.f)) *
		glm::rotate(glm::mat4(), glm::radians(-90.f), glm::vec3(1, 0, 0)) * glm::scale(glm::vec3(0.8f)));
	// sideTable
	drawObjectDepth(models::sideTable, light, glm::mat4() * glm::translate(glm::vec3(1.2f, 0.0f, 1.6f)) *
		glm::rotate(glm::mat4(), glm::radians(-90.f), glm::vec3(1, 0, 0)) * glm::scale(glm::vec3(1.f)));
	// fern
	drawObjectDepth(models::fern, light, glm::mat4() * glm::translate(glm::vec3(1.2f, 0.5f, -1.5f)) * glm::scale(glm::vec3(0.005f)));
	// r2d2
	drawObjectDepth(models::r2d2, light, glm::mat4() * glm::translate(glm::vec3(1.2f, 0.1f, 0.f))
		* glm::rotate(glm::mat4(), glm::radians(-90.f), glm::vec3(0, 1, 0))
		* glm::scale(glm::vec3(.07f)));
	// waterTower
	drawObjectDepth(models::waterTower, light, glm::mat4() * glm::translate(glm::vec3(5.f, 2.7f, -7.f)) * glm::rotate(glm::mat4(), glm::radians(-90.f), glm::vec3(0, 1, 0)) * glm::scale(glm::vec3(0.2f)));

	// dish 
	drawObjectDepth(models::dish, light, glm::mat4() * glm::translate(glm::vec3(-9.f, 0.1f, -12.f)));

	glm::vec3 spaceshipSide = glm::normalize(glm::cross(spaceshipDir, glm::vec3(0.f, 1.f, 0.f)));
	glm::vec3 spaceshipUp = glm::normalize(glm::cross(spaceshipSide, spaceshipDir));
	glm::mat4 specshipCameraRotrationMatrix = glm::mat4({
		spaceshipSide.x,spaceshipSide.y,spaceshipSide.z,0,
		spaceshipUp.x,spaceshipUp.y,spaceshipUp.z ,0,
		-spaceshipDir.x,-spaceshipDir.y,-spaceshipDir.z,0,
		0.,0.,0.,1.,
		});

	drawObjectDepth(models::shipContext, light,
		glm::translate(spaceshipPos) * specshipCameraRotrationMatrix * glm::eulerAngleY(glm::pi<float>()) * glm::scale(glm::vec3(0.03f))
	);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, WIDTH, HEIGHT);
}

void initDepthMap()
{
	glGenFramebuffers(1, &depthMapFBO);
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void initDepthMapShip()
{
	glGenFramebuffers(1, &depthMapShipFBO);
	glGenTextures(1, &depthMapShip);
	glBindTexture(GL_TEXTURE_2D, depthMapShip);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindFramebuffer(GL_FRAMEBUFFER, depthMapShipFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMapShip, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void initBloom() {
	// set up floating point framebuffer to render scene to
	glGenFramebuffers(1, &bloomTextureFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, bloomTextureFBO);

	glGenTextures(2, colorBuffers);
	for (unsigned int i = 0; i < 2; i++)
	{
		glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RGBA16F, WIDTH, HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL
		);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		// attach texture to framebuffer
		glFramebufferTexture2D(
			GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0
		);
		unsigned int rboDepth;

		glGenRenderbuffers(1, &rboDepth);
		glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, WIDTH, HEIGHT);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
	}

	unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, attachments);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;


	glGenFramebuffers(2, blurFBO);
	glGenTextures(2, blurBuffer);
	for (unsigned int i = 0; i < 2; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, blurFBO[i]);
		glBindTexture(GL_TEXTURE_2D, blurBuffer[i]);
		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RGBA16F, WIDTH, HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL
		);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(
			GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, blurBuffer[i], 0
		);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void bluring()
{
	bool horizontal = true, first_iteration = true;
	int amount = 20;
	glUseProgram(programBlur);

	for (unsigned int i = 0; i < amount; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, blurFBO[horizontal]);
		glUniform1i(glGetUniformLocation(programBlur, "horizontal"), horizontal);
		glBindTexture(
			GL_TEXTURE_2D, first_iteration ? colorBuffers[1] : blurBuffer[!horizontal]
		);
		Core::SetActiveTexture(first_iteration ? colorBuffers[1] : blurBuffer[!horizontal], "image", programBlur, 5);
		Core::DrawContext(models::testContext);
		horizontal = !horizontal;
		if (first_iteration)
			first_iteration = false;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void drawSkybox(glm::mat4 modelMatrix) {
	glDisable(GL_DEPTH_TEST);

	glUseProgram(programSkybox);

	glm::mat4 viewProjectionMatrix = createPerspectiveMatrix() * createCameraMatrix();
	glm::mat4 transformation = viewProjectionMatrix * modelMatrix;

	glUniformMatrix4fv(glGetUniformLocation(programSkybox, "transformation"), 1, GL_FALSE, (float*)&transformation);
	Core::SetActiveTexture(texture::cubemapTexture, "skybox", programSkybox, 0);

	glUniform1f(glGetUniformLocation(programSkybox, "exposition"), exposition);

	Core::DrawContext(models::skyboxContext);

	glEnable(GL_DEPTH_TEST);
}

void loadCubemap(char* cubemap[])
{
	glGenTextures(1, &texture::cubemapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture::cubemapTexture);

	int w, h;
	unsigned char* data;
	for (unsigned int i = 0; i < 6; i++)
	{
		data = SOIL_load_image(cubemap[i], &w, &h, 0, SOIL_LOAD_RGBA);
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data
		);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void renderScene(GLFWwindow* window)
{
	glClearColor(0.4f, 0.4f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	float time = glfwGetTime();
	updateDeltaTime(time);
	renderShadowMap(depthMapFBO, lightVP);
	spotlightPos = spaceshipPos + 0.2 * spaceshipDir;
	spotlightConeDir = spaceshipDir;
	lightShipVP = createPerspectiveMatrix(0.5) * glm::lookAt(spotlightPos, spotlightPos + spotlightConeDir, glm::vec3(0, 1, 0));
	renderShadowMap(depthMapShipFBO, lightShipVP);

	glBindFramebuffer(GL_FRAMEBUFFER, bloomTextureFBO);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, WIDTH, HEIGHT);
	
	drawSkybox(glm::translate(cameraPos));

	//room lamp
	glUseProgram(programRoomLamp);
	glm::mat4 viewProjectionMatrix = createPerspectiveMatrix() * createCameraMatrix();
	glm::mat4 transformation = viewProjectionMatrix * glm::translate(pointlightPos) * glm::scale(glm::vec3(0.115));
	glUniformMatrix4fv(glGetUniformLocation(programRoomLamp, "transformation"), 1, GL_FALSE, (float*)&transformation);
	glUniform3f(glGetUniformLocation(programRoomLamp, "color"), sunColor.x / 2, sunColor.y / 2, sunColor.z / 2);
	glUniform1f(glGetUniformLocation(programRoomLamp, "exposition"), exposition);
	Core::DrawContext(models::sphereContext);

	if (gameStart) {
		helmetX = generateRandomFloat(-2.3f, -5.8f);
		helmetZ = generateRandomFloat(-24.0f, 4.8f);
		//swordX = generateRandomFloat(-2.3f, -5.8f);
		//swordZ = generateRandomFloat(-24.0f, 4.8f);

		gameStart = false;
	}

	glUseProgram(program);
	// lamp
	drawObjectPBR(models::lampContext, glm::mat4(), texture::lampTexture, texture::lampTextureNormal, texture::lampTextureArm);
	// doors
	if (astronautVisible)
		drawObjectPBR(models::closeDoorContext, glm::mat4(), texture::doorTexture, texture::doorTextureNormal, texture::doorTextureArm);
	// floor
	drawObjectPBR(models::planeContext, glm::mat4(), texture::floorTexture, texture::floorTextureNormal, texture::floorTextureArm);
	// room
	drawObjectPBR(models::roomContext, glm::mat4(), texture::wallTexture, texture::wallTextureNormal, texture::wallTextureArm);
	// window
	drawObjectPBR(models::windowContext, glm::mat4(), texture::windowTexture, texture::windowTextureNormal, texture::windowTextureArm);
	//armchair
	drawObjectPBR(models::armchair, glm::mat4() * glm::translate(glm::vec3(-1.f, 0.6f, 1.5f)) *
		glm::rotate(glm::mat4(), glm::radians(-180.f), glm::vec3(0, 1, 1)) * glm::scale(glm::vec3(.03f)), texture::armchairTexture, texture::armchairTextureNormal);
	// pot
	drawObjectPBR(models::plantPot, glm::mat4() * glm::translate(glm::vec3(1.2f, 0.0f, -1.5f)) *
		glm::scale(glm::vec3(.02f)), texture::plantPotTexture);
	// cabinet
	drawObjectPBR(
		models::cabinet,
		glm::mat4() * glm::translate(glm::vec3(1.4f, 0.0f, 0.f)) *
		glm::rotate(glm::mat4(), glm::radians(-90.f), glm::vec3(1, 0, 0)) * // Rotate to stand vertically
		glm::rotate(glm::mat4(), glm::radians(-90.f), glm::vec3(0, 0, 1)) * // Rotate to the right (adjust 'angle' as needed)
		glm::scale(glm::vec3(.8f)),
		texture::cabinetTexture,
		texture::cabinetTextureNormal,
		texture::cabinetTextureArm
	);
	// table
	drawObjectPBR(models::table, glm::mat4() * glm::translate(glm::vec3(-1.f, 0.0f, 0.f)) *
		glm::rotate(glm::mat4(), glm::radians(-90.f), glm::vec3(1, 0, 0)) * glm::scale(glm::vec3(0.8f)), texture::tableTexture, texture::tableTextureNormal, texture::tableTextureArm);
	// sideTable
	drawObjectPBR(models::sideTable, glm::mat4() * glm::translate(glm::vec3(1.2f, 0.0f, 1.6f)) *
		glm::rotate(glm::mat4(), glm::radians(-90.f), glm::vec3(1, 0, 0)) * glm::scale(glm::vec3(1.f)), texture::sideTableTexture, texture::sideTableextureNormal, texture::sideTableTextureArm);
	//fern
	drawObjectPBR(models::fern, glm::mat4() * glm::translate(glm::vec3(1.2f, 0.5f, -1.5f)) * glm::scale(glm::vec3(0.005f)), texture::fernTexture);
	// r2d2
	drawObjectPBR(models::r2d2, glm::mat4() * glm::translate(glm::vec3(1.2f, 0.1f, 0.f))
		* glm::rotate(glm::mat4(), glm::radians(-90.f), glm::vec3(0, 1, 0))
		* glm::scale(glm::vec3(.07f)), texture::r2d2Texture);
	// waterTower
	drawObjectPBR(models::waterTower, glm::mat4() * glm::translate(glm::vec3(5.f, 2.7f, -7.f)) * glm::rotate(glm::mat4(), glm::radians(-90.f), glm::vec3(0, 1, 0)) * glm::scale(glm::vec3(0.2f)), 
		texture::waterTowerTexture, texture::waterTowerTextureNormal);
	// roof
	drawObjectPBR(models::roof, glm::mat4(), texture::roofTexture);
	// dish
	drawObjectPBR(models::dish, glm::mat4() * glm::translate(glm::vec3(-9.f, 0.0f, -12.f)), texture::mercuryTexture);
	// mountain
	drawObjectPBR(models::mountain, glm::mat4() * glm::translate(glm::vec3(0.f, 3.f, 17.f)) * glm::scale(glm::vec3(0.5f, 0.2f, 0.2f)) * glm::rotate(glm::mat4(), glm::radians(180.f), glm::vec3(0, 1, 0)), texture::mountainTexture);
	//drawObjectPBR(models::mountain, glm::mat4() * glm::translate(glm::vec3(0.f, 0.f, -15.f)) * glm::scale(glm::vec3(0.5f, 0.2f, 0.3f)) * glm::rotate(glm::mat4(), glm::radians(180.f), glm::vec3(0, 1, 0)), texture::mountainTexture);

	// asteroids
	if (fallAsteroid) {
		// asteroid1 + earthquake
		asteroidPosition.x += fallSpeed * 0.1f;
		asteroidPosition.y -= fallSpeed * 0.1f;
		if (asteroidPosition.y <= 0.0) {
			drawObjectPBR(models::asteroid, glm::mat4()
				* glm::translate(glm::vec3(0.0f, 0.0f, 7.f)) * glm::scale(glm::vec3(0.8f)), texture::asteroidTexture, texture::asteroidTextureNormal, texture::asteroidTexture3);
			if (timeframesCount <= timeframes) {
				earthquake = true;
				timeframesCount += 1;
			}
			else {
				earthquake = false;
				afterAsteroids = true;
			}
		}
		else 
			drawObjectPBR(models::asteroid,
				glm::mat4() * glm::translate(asteroidPosition) * glm::rotate(time * 5, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::vec3(1.f)),
				texture::asteroidTexture, texture::asteroidTextureNormal, texture::asteroidTexture3);
		// asteroid2
		asteroidPosition2.x += fallSpeed * 0.1f;
		asteroidPosition2.y -= fallSpeed * 0.09f;
		if (asteroidPosition2.y <= 0.0)
			drawObjectPBR(models::asteroid, glm::mat4() * glm::translate(glm::vec3(2.2f, 0.0f, 5.f)) * glm::rotate(glm::mat4(), glm::radians(-90.f), glm::vec3(0, 0, 1)) * glm::scale(glm::vec3(0.6f)), texture::asteroidTexture, texture::asteroidTextureNormal, texture::asteroidTexture3);
		else
			drawObjectPBR(models::asteroid, glm::mat4() * glm::translate(asteroidPosition2) * glm::rotate(time * 5, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::vec3(0.5f)), texture::asteroidTexture, texture::asteroidTextureNormal, texture::asteroidTexture3);
		// asteroid3
		asteroidPosition3.x += fallSpeed * 0.077f;
		asteroidPosition3.y -= fallSpeed * 0.08f;
		if (asteroidPosition3.y <= 0.0)
			drawObjectPBR(models::asteroid, glm::mat4() * glm::translate(glm::vec3(1.25f, 0.0f, 9.f)) * glm::rotate(glm::mat4(), glm::radians(-180.f), glm::vec3(0, 0, 1)) * glm::scale(glm::vec3(0.4f)), texture::asteroidTexture, texture::asteroidTextureNormal, texture::asteroidTexture3);
		else
			drawObjectPBR(models::asteroid, glm::mat4() * glm::translate(asteroidPosition3) * glm::rotate(time * 5, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::vec3(0.5f)), texture::asteroidTexture, texture::asteroidTextureNormal, texture::asteroidTexture3);
		// asteroid4
		asteroidPosition4.x += fallSpeed * 0.1f;
		asteroidPosition4.y -= fallSpeed * 0.09f;
		if (asteroidPosition4.y <= 0.0)
			drawObjectPBR(models::asteroid, glm::mat4() * glm::translate(glm::vec3(0.f, 0.0f, 10.f)) * glm::rotate(glm::mat4(), glm::radians(-90.f), glm::vec3(0, 0, 1)) * glm::scale(glm::vec3(0.4f)), texture::asteroidTexture, texture::asteroidTextureNormal, texture::asteroidTexture3);
		else
			drawObjectPBR(models::asteroid, glm::mat4() * glm::translate(asteroidPosition4) * glm::rotate(time * 5, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::vec3(0.5f)), texture::asteroidTexture, texture::asteroidTextureNormal, texture::asteroidTexture3);
		// asteroid5
		asteroidPosition5.x += fallSpeed * 0.1f;
		asteroidPosition5.y -= fallSpeed * 0.09f;
		if (asteroidPosition5.y <= 0.0)
			drawObjectPBR(models::asteroid, glm::mat4() * glm::translate(glm::vec3(-3.2f, 0.0f, 8.f)) * glm::rotate(glm::mat4(), glm::radians(-120.f), glm::vec3(0, 0, 1)) * glm::scale(glm::vec3(0.5f)), texture::asteroidTexture, texture::asteroidTextureNormal, texture::asteroidTexture3);
		else
			drawObjectPBR(models::asteroid, glm::mat4() * glm::translate(asteroidPosition5) * glm::rotate(time * 5, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::vec3(0.5f)), texture::asteroidTexture, texture::asteroidTextureNormal, texture::asteroidTexture3);
		// asteroid6
		asteroidPosition6.x += fallSpeed * 0.1f;
		asteroidPosition6.y -= fallSpeed * 0.12f;
		if (asteroidPosition6.y <= 0.0) 
			drawObjectPBR(models::asteroid, glm::mat4() * glm::translate(glm::vec3(-7.4f, 0.0f, 6.f)) * glm::rotate(glm::mat4(), glm::radians(-120.f), glm::vec3(1, 0, 1)) * glm::scale(glm::vec3(0.7f)), texture::asteroidTexture, texture::asteroidTextureNormal, texture::asteroidTexture3);
		else
			drawObjectPBR(models::asteroid, glm::mat4() * glm::translate(asteroidPosition6) * glm::rotate(time * 5, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::vec3(0.5f)), texture::asteroidTexture, texture::asteroidTextureNormal, texture::asteroidTexture3);
	}
	// ground
	drawObjectPBR(models::ground, glm::mat4() * glm::translate(glm::vec3(0.f, -0.01f, 0.f))
		* glm::scale(glm::vec3(12.f, 10.f, 10.f)), texture::groundTexture);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Planets
	glm::vec3 sunPosition = glm::vec3(-1000.f, 0.f, -5.f);
	drawObjectPBR(models::sphereContext, glm::mat4() * glm::translate(sunPosition) * glm::scale(glm::vec3(.8f)), texture::sunTexture);
	// mercury
	float mercuryRotationAngle = 0.0f;
	float mercuryrotationSpeed = 0.3f;
	mercuryRotationAngle += time * mercuryrotationSpeed;
	glm::mat4 mercuryModelMatrix = glm::mat4() * glm::translate(sunPosition) * glm::rotate(glm::mat4(), mercuryRotationAngle, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(glm::vec3(-2.f, 0.f, -2.f)) * glm::scale(glm::vec3(0.4f));
	drawObjectPBR(models::sphereContext, mercuryModelMatrix, texture::mercuryTexture);
	float ufoSpeed = time * 0.5;
	glm::mat4 ufoModelMatrix = mercuryModelMatrix * glm::eulerAngleY(ufoSpeed) * glm::translate(glm::vec3(4.f, 0, 0)) * glm::scale(glm::vec3(0.02f));
	drawObjectPBR(models::ufo, ufoModelMatrix, texture::ufoTexture, texture::ufoTextureNormal);
	// neptune
	float neptuneRotationAngle = 5.0f;
	float neptunerotationSpeed = 0.3f;
	neptuneRotationAngle += time * neptunerotationSpeed;
	glm::mat4 neptuneModelMatrix = glm::mat4() * glm::translate(sunPosition) * glm::rotate(glm::mat4(), neptuneRotationAngle, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(glm::vec3(-6.f, 0.f, -6.f)) * glm::scale(glm::vec3(0.4f));
	drawObjectPBR(models::sphereContext, neptuneModelMatrix, texture::neptuneTexture);
	glm::mat4 starModelMatrix = neptuneModelMatrix * glm::eulerAngleY(time * 0.9f) * glm::translate(glm::vec3(4.f, 0, 0)) * glm::rotate(glm::mat4(), glm::radians(-90.f), glm::vec3(0.8, 0, 0)) * glm::scale(glm::vec3(0.06f));
	glm::vec3 starPosition = glm::vec3(starModelMatrix[3]);
	
	// spaceStar
	bool spaceStarBool = checkCollision(spaceshipPos, starPosition);
	if (spaceStarBool) {
		spaceStarVisible = false;
		spaceStarPicked = true;
	}
	if (spaceStarVisible)
		drawObjectPBR(models::star, starModelMatrix, texture::starTexture);

	// mars
	float marsRotationAngle = 3.0f;
	float marsrotationSpeed = 0.5f;
	marsRotationAngle += time * marsrotationSpeed;
	glm::mat4 marsModelMatrix = glm::mat4() * glm::translate(sunPosition) * glm::rotate(glm::mat4(), marsRotationAngle, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(glm::vec3(-4.f, 0.f, -4.f)) * glm::scale(glm::vec3(0.4f));
	drawObjectPBR(models::sphereContext, marsModelMatrix, texture::marsTexture);
	glm::mat4 moonModelMatrix = marsModelMatrix * glm::eulerAngleY(time) * glm::translate(glm::vec3(4.f, 0, 0)) * glm::scale(glm::vec3(0.2f));
	drawObjectPBR(models::sphereContext, moonModelMatrix, texture::moonTexture);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// astronaut quest
	bool astronautBool = checkCollision(spaceshipPos, glm::vec3(1.3f, 0.5f, -2.95f));
	bool helmetBool = checkCollision(spaceshipPos, glm::vec3(helmetX, 0.3f, helmetZ));
	bool astronautStarBool = checkCollision(spaceshipPos, glm::vec3(-0.3f, 1.f, 1.f));
	//printf("Spaceship Position: (%f, %f, %f\n, %f, %f, %f)\n", spaceshipPos.x, spaceshipPos.y, spaceshipPos.z, cameraDir.x, cameraDir.y, cameraDir.z);

	// astronaut -> helmet -> star
	if (astronautBool && helmetVisible == false)
		astronautVisible = false;

	drawObjectPBR(models::astronaut, glm::mat4() * glm::translate(glm::vec3(1.3f, 0.f, -2.95f)) *
		glm::rotate(glm::mat4(), glm::radians(-180.f), glm::vec3(0, 1, 1)) * glm::scale(glm::vec3(.75f)), texture::astronautTexture);

	if (helmetBool)
		helmetVisible = false;
	else if (helmetVisible)
		drawObjectPBR(models::helmet, glm::mat4() * glm::translate(glm::vec3(helmetX, 0.15f, helmetZ)) *
			glm::rotate(glm::mat4(), glm::radians(-180.f), glm::vec3(0, 1, 1)) * glm::scale(glm::vec3(.01f)), texture::helmetTexture, texture::helmetTextureNormal);
	else if (astronautVisible == false) {
		drawObjectPBR(models::helmet, glm::mat4() * glm::translate(glm::vec3(1.3f, 1.45f, -2.95f)) *
			glm::rotate(glm::mat4(), glm::radians(-180.f), glm::vec3(0, 1, 1)) * glm::scale(glm::vec3(.0095f)), texture::helmetTexture, texture::helmetTextureNormal);
		drawObjectPBR(models::doorContext, glm::mat4(), texture::doorTexture, texture::doorTextureNormal, texture::doorTextureArm);
	}

	if (astronautStarBool && astronautVisible == false) {
		astronautStarVisible = false;
		astronautStarPicked = true;
	}
	else if (astronautStarVisible && helmetVisible == false && astronautVisible == false) {
		rotationAngle += 0.1f;

		drawObjectPBR(
			models::star,
			glm::mat4() * glm::translate(glm::vec3(-0.3f, 1.f, 1.f)) *
			glm::rotate(glm::mat4(), rotationAngle, glm::vec3(0, 1, 0)) *  // Rotate around the Y-axis
			glm::rotate(glm::mat4(), glm::radians(-90.f), glm::vec3(1, 0, 0)) *  // Upright rotation around the X-axis
			glm::scale(glm::vec3(.04f)), texture::starTexture
		);
	}


	// alien quest
	bool alienBool = checkCollision(spaceshipPos, glm::vec3(6.f, 1.f, 6.f));
	bool eggBool = checkCollision(spaceshipPos, glm::vec3(0.f, 0.2f, 8.f));
	bool alienStarBool = checkCollision(spaceshipPos, glm::vec3(5.1f, 5.f, -7.f));

	// alien -> egg -> star
	if (afterAsteroids) {
		// alien
		drawObjectPBR(models::alien, glm::mat4() * glm::translate(glm::vec3(6.f, 0.f, 6.f))
			* glm::rotate(glm::mat4(), glm::radians(90.f), glm::vec3(1, 0, 0))
			* glm::rotate(glm::mat4(), glm::radians(-180.f), glm::vec3(0, 1, 0))
			* glm::rotate(glm::mat4(), glm::radians(90.f), glm::vec3(0, 0, 1))
			* glm::scale(glm::vec3(0.7f)), texture::alienTexture, texture::alienTextureNormal);
		if (eggBool) 
			eggVisible = false;
		else if (eggVisible)
			drawObjectPBR(models::egg, glm::mat4() * glm::translate(glm::vec3(0.f, 0.2f, 8.f)) * glm::scale(glm::vec3(1.f)), texture::eggTexture);

		if (eggVisible == false && alienBool) 
			isEggGiven = true;

		if (isEggGiven) {
			if (alienStarBool) {
				alienStarVisible = false;
				alienStarPicked = true;
			}
			else if (alienStarVisible) {
				rotationAngle += 0.1f;

				drawObjectPBR(
					models::star,
					glm::mat4() * glm::translate(glm::vec3(5.1f, 5.f, -7.f)) *
					glm::rotate(glm::mat4(), rotationAngle, glm::vec3(0, 1, 0))*  // Rotate around the Y-axis
					glm::rotate(glm::mat4(), glm::radians(-90.f), glm::vec3(1, 0, 0))*  // Upright rotation around the X-axis
					glm::scale(glm::vec3(.04f)), texture::starTexture
				);
			}
			
		}
	}
	
	glm::vec3 spaceshipSide = glm::normalize(glm::cross(spaceshipDir, glm::vec3(0.f, 1.f, 0.f)));
	glm::vec3 spaceshipUp = glm::normalize(glm::cross(spaceshipSide, spaceshipDir));
	glm::mat4 specshipCameraRotrationMatrix = glm::mat4({
		spaceshipSide.x,spaceshipSide.y,spaceshipSide.z,0,
		spaceshipUp.x,spaceshipUp.y,spaceshipUp.z ,0,
		-spaceshipDir.x,-spaceshipDir.y,-spaceshipDir.z,0,
		0.,0.,0.,1.,
		});

	drawObjectPBR(models::shipContext,
		glm::translate(spaceshipPos) * specshipCameraRotrationMatrix * glm::eulerAngleY(glm::pi<float>()) * glm::scale(glm::vec3(0.01f)), texture::spaceshipTexture, texture::spaceshipTextureNormal
	);

	if (spaceStarVisible == false)
		drawObjectPBR(models::star, glm::translate(glm::vec3(spaceshipPos.x, spaceshipPos.y + 0.65, spaceshipPos.z)) * specshipCameraRotrationMatrix
			* glm::eulerAngleY(glm::pi<float>()) * glm::rotate(glm::mat4(), glm::radians(-90.f), glm::vec3(1, 0, 0)) * glm::scale(glm::vec3(0.004f)), texture::starTexture);
	if (astronautStarVisible == false)
		drawObjectPBR(models::star, glm::translate(glm::vec3(spaceshipPos.x, spaceshipPos.y + 0.6, spaceshipPos.z)) * specshipCameraRotrationMatrix 
			* glm::eulerAngleY(glm::pi<float>()) * glm::rotate(glm::mat4(), glm::radians(-90.f), glm::vec3(1, 0, 0)) * glm::scale(glm::vec3(0.004f)), texture::starTexture);
	if (alienStarVisible == false)
		drawObjectPBR(models::star, glm::translate(glm::vec3(spaceshipPos.x, spaceshipPos.y + 0.55, spaceshipPos.z)) * specshipCameraRotrationMatrix
			* glm::eulerAngleY(glm::pi<float>()) * glm::rotate(glm::mat4(), glm::radians(-90.f), glm::vec3(1, 0, 0)) * glm::scale(glm::vec3(0.004f)), texture::starTexture);



	bluring();

	glUseProgram(programBloom);
	Core::SetActiveTexture(colorBuffers[0], "scene", programBloom, 6);
	Core::SetActiveTexture(blurBuffer[!true], "bloomBlur", programBloom, 7);
	glUniform1f(glGetUniformLocation(programBloom, "exposition"), exposition);
	Core::DrawContext(models::testContext);

	glUseProgram(0);
	glfwSwapBuffers(window);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	aspectRatio = width / float(height);
	glViewport(0, 0, width, height);
	WIDTH = width;
	HEIGHT = height;
	initBloom();
}
void loadModelToContext(std::string path, Core::RenderContext& context)
{
	Assimp::Importer import;
	const aiScene * scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return;
	}
	context.initFromAssimpMesh(scene->mMeshes[0]);
}

void init(GLFWwindow* window)
{
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glEnable(GL_DEPTH_TEST);
	program = shaderLoader.CreateProgram("shaders/shader_main.vert", "shaders/shader_main.frag");
	programTest = shaderLoader.CreateProgram("shaders/test.vert", "shaders/test.frag");
	programRoomLamp = shaderLoader.CreateProgram("shaders/shader_room_lamp.vert", "shaders/shader_room_lamp.frag");
	programDepth = shaderLoader.CreateProgram("shaders/shader_depth.vert", "shaders/shader_depth.frag");
	programBlur = shaderLoader.CreateProgram("shaders/shader_blur.vert", "shaders/shader_blur.frag");
	programBloom = shaderLoader.CreateProgram("shaders/shader_bloom.vert", "shaders/shader_bloom.frag");
	programSkybox = shaderLoader.CreateProgram("shaders/shader_skybox.vert", "shaders/shader_skybox.frag");
	programlightPlace = shaderLoader.CreateProgram("shaders/shader_lightPlace.vert", "shaders/shader_lightPlace.frag");

	loadModelToContext("./models/sphere.obj", models::sphereContext);
	loadModelToContext("./models/spaceship/spaceship.obj", models::shipContext);
	loadModelToContext("./models/cube.obj", models::skyboxContext);
	loadModelToContext("./models/door.obj", models::doorContext);
	loadModelToContext("./models/door/door.obj", models::closeDoorContext);
	loadModelToContext("./models/ground.obj", models::planeContext);
	loadModelToContext("./models/room.obj", models::roomContext);
	loadModelToContext("./models/window/window.obj", models::windowContext);
	loadModelToContext("./models/test.obj", models::testContext);

	loadModelToContext("./models/lamp/lamp.obj", models::lampContext);
	loadModelToContext("./models/astronaut/astronaut.fbx", models::astronaut);
	loadModelToContext("./models/Helmet.fbx", models::helmet);
	loadModelToContext("./models/star.obj", models::star);
	loadModelToContext("./models/ComDish.obj", models::dish);
	loadModelToContext("./models/ground.obj", models::ground);
	loadModelToContext("./models/Sword.obj", models::sword);
	loadModelToContext("./models/armchair.fbx", models::armchair);
	loadModelToContext("./models/Sansevieria.obj", models::plantPot);
	loadModelToContext("./models/cabinet.fbx", models::cabinet);
	loadModelToContext("./models/table.fbx", models::table);
	loadModelToContext("./models/sideTable.fbx", models::sideTable);
	loadModelToContext("./models/UFO.obj", models::ufo);
	loadModelToContext("./models/fern.obj", models::fern);
	loadModelToContext("./models/r2d2.obj", models::r2d2);
	loadModelToContext("./models/alien.fbx", models::alien);
	loadModelToContext("./models/waterTower.obj", models::waterTower);
	loadModelToContext("./models/asteroid.obj", models::asteroid);
	loadModelToContext("./models/egg.fbx", models::egg);
	loadModelToContext("./models/mountain.obj", models::mountain);
	loadModelToContext("./models/roof.obj", models::roof);

	texture::defaultTexture = Core::LoadTexture("textures/default/default.png");
	texture::defaultTextureNormal = Core::LoadTexture("textures/default/default_normalmap.png");
	texture::defaultTextureArm = Core::LoadTexture("textures/default/default_arm.png");
	// spaceship
	texture::spaceshipTexture = Core::LoadTexture("textures/spaceship/spaceship.jpg");
	texture::spaceshipTextureNormal = Core::LoadTexture("textures/spaceship/spaceship_normalmap.png");
	texture::spaceshipTextureArm = Core::LoadTexture("textures/spaceship/spaceship_arm.png");
	// floor
	texture::floorTexture = Core::LoadTexture("textures/floor/floor.png");
	texture::floorTextureNormal = Core::LoadTexture("textures/floor/floor_normalmap.png");
	texture::floorTextureArm = Core::LoadTexture("textures/floor/floor_arm.png");
	// wall
	texture::wallTexture = Core::LoadTexture("textures/wall/wall.png");
	texture::wallTextureNormal = Core::LoadTexture("textures/wall/wall_normalmap.png");
	texture::wallTextureArm = Core::LoadTexture("textures/wall/wall_arm.png");
	// roof
	texture::roofTexture = Core::LoadTexture("textures/roof/roof.png");
	// window
	texture::windowTexture = Core::LoadTexture("textures/window/window.png");
	texture::windowTextureNormal = Core::LoadTexture("textures/window/window_normalmap.png");
	texture::windowTextureArm = Core::LoadTexture("textures/window/window_arm.png");
	// door
	texture::doorTexture = Core::LoadTexture("textures/door/door.png");
	texture::doorTextureNormal = Core::LoadTexture("textures/door/door_normalmap.png");
	texture::doorTextureArm = Core::LoadTexture("textures/door/door_arm.png");
	// lamp
	texture::lampTexture = Core::LoadTexture("textures/lamp/lamp.png");
	texture::lampTextureNormal = Core::LoadTexture("textures/lamp/lamp_normalmap.png");
	texture::lampTextureArm = Core::LoadTexture("textures/lamp/lamp_arm.png");
	// armchair
	texture::armchairTexture = Core::LoadTexture("textures/armchair/armchairBase.png");
	texture::armchairTextureNormal = Core::LoadTexture("textures/armchair/armchairNormal.png");
	// plant
	texture::plantPotTexture = Core::LoadTexture("textures/plant/plantPotBase.png");
	texture::plantPotNormal = Core::LoadTexture("textures/plant/plantPotNormal.png");
	texture::plantLeavesTexture = Core::LoadTexture("textures/plant/leaves.png");
	// cabinet
	texture::cabinetTexture = Core::LoadTexture("textures/cabinet/cabinetBase.jpg");
	texture::cabinetTextureNormal = Core::LoadTexture("textures/cabinet/cabinetNormal.jpg");
	texture::cabinetTextureArm = Core::LoadTexture("textures/cabinet/cabineArm.jpg");
	// table
	texture::tableTexture = Core::LoadTexture("textures/table/tableBase.jpg");
	texture::tableTextureNormal = Core::LoadTexture("textures/table/tableNormal.jpg");
	texture::tableTextureArm = Core::LoadTexture("textures/table/tableArm.jpg");
	// sideTable
	texture::sideTableTexture = Core::LoadTexture("textures/sideTable/sideTableBase.jpg");
	texture::sideTableextureNormal = Core::LoadTexture("textures/sideTable/sideTableNormal.jpg");
	texture::sideTableTextureArm = Core::LoadTexture("textures/sideTable/sideTableArm.jpg");
	// ufo
	texture::ufoTexture = Core::LoadTexture("textures/ufo/ufoBase.png");
	texture::ufoTextureNormal = Core::LoadTexture("textures/ufo/ufoNormal.png");
	// fern
	texture::fernTexture = Core::LoadTexture("textures/fern/fernBase.png");
	// r2d2
	texture::r2d2Texture = Core::LoadTexture("textures/r2d2/r2d2.png");
	// alien
	texture::alienTexture = Core::LoadTexture("textures/alien/alienBase.png");
	texture::alienTextureNormal = Core::LoadTexture("textures/alien/alienNormal.png");
	// waterTower
	texture::waterTowerTexture = Core::LoadTexture("textures/waterTower/base.png");
	texture::waterTowerTextureNormal = Core::LoadTexture("textures/waterTower/normal.png");
	// asteroid
	texture::asteroidTexture = Core::LoadTexture("textures/asteroid/asteroid.jpg");
	texture::asteroidTextureNormal = Core::LoadTexture("textures/asteroid/asteroidNormal.jpg");
	texture::asteroidTexture3 = Core::LoadTexture("textures/asteroid/asteroidEmission.jpg");
	// egg
	texture::eggTexture = Core::LoadTexture("textures/egg/egg.png");
	// astronaut
	texture::astronautTexture = Core::LoadTexture("textures/astronaut/suit.png");
	texture::astronautTextureNormal = Core::LoadTexture("textures/astronaut/helmet_albedo.png");
	//helmet
	texture::helmetTexture = Core::LoadTexture("textures/helmet/helmet_base.jpeg");
	texture::helmetTextureNormal = Core::LoadTexture("textures/astronaut/Helmet_normal.png");
	// star
	texture::starTexture = Core::LoadTexture("textures/star/star.png");
	// planets
	texture::marsTexture = Core::LoadTexture("textures/planets/mars.png");
	texture::sunTexture = Core::LoadTexture("textures/planets/sun.jpg");
	texture::mercuryTexture = Core::LoadTexture("textures/planets/mercury.jpg");
	texture::moonTexture = Core::LoadTexture("textures/planets/moon.jpg");
	texture::neptuneTexture = Core::LoadTexture("textures/planets/neptune.jpg");
	//earth
	texture::earthTexture = Core::LoadTexture("textures/planets/earth.jpg");
	texture::earthTextureNormal = Core::LoadTexture("textures/planets/earthNormal.tif");
	texture::earthClouds = Core::LoadTexture("textures/planets/clouds.jpg");
	// sword
	texture::swordTexture = Core::LoadTexture("textures/sword/swordBase_Color.jpg");
	texture::swordTextureNormal = Core::LoadTexture("textures/sword/swordNormal.jpg");
	texture::swordTextureRough = Core::LoadTexture("textures/sword/Sting_Roughness.jpg");
	// mounatain
	texture::mountainTexture = Core::LoadTexture("textures/mountain/lava.png");
	texture::mountainTextureNormal = Core::LoadTexture("textures/mountain/lavaNormal.png");
	// gorund
	texture::groundTexture = Core::LoadTexture("textures/grounf/mars.png");
	

	initDepthMap();
	initDepthMapShip();

	initBloom();

	char* cubemap[] = { "textures/skybox/hot_lf.png", "textures/skybox/hot_rt.png", "textures/skybox/hot_up.png", "textures/skybox/hot_dn.png", "textures/skybox/hot_ft.png", "textures/skybox/hot_bk.png" };
	//char* cubemap2[] = { "textures/skybox/sp_lf.png", "textures/skybox/sp_rt.png", "textures/skybox/sp_up.png", "textures/skybox/sp_dn.png", "textures/skybox/sp_ft.png", "textures/skybox/sp_bk.png" };
	//char* cubemap3[] = { "textures/skybox2/left.png", "textures/skybox2/right.png", "textures/skybox2/up.png", "textures/skybox2/bottom.png", "textures/skybox2/front.png", "textures/skybox2/back.png" };
	loadCubemap(cubemap);
}

void shutdown(GLFWwindow* window) {
	shaderLoader.DeleteProgram(program);
}

void processInput(GLFWwindow* window)
{
	glm::vec3 spaceshipSide = glm::normalize(glm::cross(spaceshipDir, glm::vec3(0.f, 1.f, 0.f)));
	glm::vec3 spaceshipUp = glm::vec3(0.f, 1.f, 0.f);
	float angleSpeed = 0.05f * deltaTime * 60;
	float moveSpeed = 0.05f * deltaTime * 60;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		spaceshipPos += spaceshipDir * moveSpeed;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		spaceshipPos -= spaceshipDir * moveSpeed;
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		spaceshipPos += spaceshipSide * moveSpeed;
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		spaceshipPos -= spaceshipSide * moveSpeed;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		spaceshipPos += spaceshipUp * moveSpeed;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		if (spaceshipPos.y >= 0.01)
			spaceshipPos -= spaceshipUp * moveSpeed;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		spaceshipDir = glm::vec3(glm::eulerAngleY(angleSpeed) * glm::vec4(spaceshipDir, 0));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		spaceshipDir = glm::vec3(glm::eulerAngleY(-angleSpeed) * glm::vec4(spaceshipDir, 0));
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		spaceshipDir = glm::vec3(glm::eulerAngleZ(angleSpeed) * glm::vec4(spaceshipDir, 0));
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		spaceshipDir = glm::vec3(glm::eulerAngleZ(-angleSpeed) * glm::vec4(spaceshipDir, 0));
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS && glm::dot(glm::vec3(-1.277735f, 0.622864f, -0.097097f), spaceshipDir) > 0.866 && glm::distance(glm::vec3(-1.277735f, 0.622864f, -0.097097f), spaceshipPos) < 0.7) {
		spaceshipPos = glm::vec3(-1.277735f, 0.622864f, -0.097097f);
		spaceshipDir = glm::vec3(1.0f, 0.0f, 0.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		exposition -= 0.05;
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		exposition += 0.05;
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		printf("spaceshipPos = glm::vec3(%ff, %ff, %ff);\n", spaceshipPos.x, spaceshipPos.y, spaceshipPos.z);
		printf("spaceshipDir = glm::vec3(%ff, %ff, %ff);\n", spaceshipDir.x, spaceshipDir.y, spaceshipDir.z);
	}

	glm::vec3 initialCameraOffset = glm::vec3(0, 1, 0) * 0.2f - 0.5f * spaceshipDir;
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		fallAsteroid = true;

	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
		if (!isTransitioningSpace) {
			isTransitioningSpace = true;
			transitionCount = 0;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		if (!isTransitioningMars) {
			isTransitioningMars = true;
			transitionCount = 0;
		}
	}

	if (isTransitioningSpace) {
		if (spaceStarPicked)
			spaceStarVisible = true;
		if (alienStarPicked)
			alienStarVisible = true;
		if (astronautStarPicked)
			astronautStarVisible = true;
		if (transitionCount < transitionFrames) {
			cameraPos += glm::normalize(cameraDir) * -0.1f; // Adjust the speed as needed
			transitionCount++;
		}
		else if (transitionCount < transitionFrames + riseFrames) {
			// After moving the camera, rise the spaceship
			spaceshipPos.y += 0.05f;
			transitionCount++;
		}
		else {
			spaceshipPos = glm::vec3(-995.0f, 0.0f, -5.0f);
			spaceshipDir = glm::vec3(-1.f, 0.000000f, -0.02f);
			isTransitioningSpace = false;
			if (spaceStarPicked)
				spaceStarVisible = false;
			if (alienStarPicked)
				alienStarVisible = false;
			if (astronautStarPicked)
				astronautStarVisible = false;
			transitionCount = 0;
		}
	}

	if (isTransitioningMars) {
		if (spaceStarPicked)
			spaceStarVisible = true;
		if (alienStarPicked)
			alienStarVisible = true;
		if (astronautStarPicked)
			astronautStarVisible = true;
		if (transitionCount < transitionFrames) {
			cameraPos += glm::normalize(cameraDir) * -0.1f; // Adjust the speed as needed
			transitionCount++;
		}
		else {
			// Teleport the spaceship to the new position
			spaceshipPos = glm::vec3(.0f, .0f, -5.0f);
			isTransitioningMars = false;
			if (spaceStarPicked)
				spaceStarVisible = false;
			if (alienStarPicked)
				alienStarVisible = false;
			if (astronautStarPicked)
				astronautStarVisible = false;
			transitionCount = 0;
		}
	}

	if (earthquake) {
		GLfloat earthquakeIntensity = 0.1f;

		applyEarthquakeEffect(cameraPos, earthquakeIntensity);
	}
	else if (isTransitioningSpace == false && earthquake == false && isTransitioningMars == false) {
		cameraPos = spaceshipPos + initialCameraOffset;
		cameraDir = spaceshipDir;
	}

}


void renderLoop(GLFWwindow* window) {
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		renderScene(window);
		glfwPollEvents();
	}
}