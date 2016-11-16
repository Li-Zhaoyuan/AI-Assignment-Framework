#pragma once

#include "../Gathering of Components/MyMeshComponent.h"
#include "..\\Classes\\Vertex.h"
#include <GL\glew.h>
#include <vector>
#include "MyMath.h"
#include "LoadOBJ.h"
#include "LoadHmap.h"
#include "../Gathering of Components/SpriteComponent.h"

class MyMeshBuilder
{
public:
    static MyMeshComponent* GenerateAxes(const std::string &MyMeshComponentName, float lengthX = 0.0f, float lengthY = 0.0f, float lengthZ = 0.0f);
    static MyMeshComponent* GenerateCrossHair(const std::string &MyMeshComponentName, float colour_r = 0.8f, float colour_g = 0.8f, float colour_b = 0.8f, float length = 0.5f);
    static MyMeshComponent* GenerateQuad(const std::string &MyMeshComponentName, Color color, float length = 1.f);
    static MyMeshComponent* GenerateCube(const std::string &MyMeshComponentName, Color color, float length = 1.f);
    static MyMeshComponent* GenerateRing(const std::string &MyMeshComponentName, Color color, unsigned numSlice, float outerR = 1.f, float innerR = 0.f);
    static MyMeshComponent* GenerateSphere(const std::string &MyMeshComponentName, Color color, unsigned numStack, unsigned numSlice, float radius = 1.f);
    static MyMeshComponent* GenerateCone(const std::string &MyMeshComponentName, Color color, unsigned numSlice, float radius, float height);
    static MyMeshComponent* GenerateOBJ(const std::string &MyMeshComponentName, const std::string &file_path);
    static MyMeshComponent* GenerateText(const std::string &MyMeshComponentName, unsigned row, unsigned col);
    static MyMeshComponent* GenerateMinimap(const std::string &MyMeshComponentName, Color color, float length = 1.f);
    static MyMeshComponent* GenerateMinimapBorder(const std::string &MyMeshComponentName, Color color, float length = 1.f);
    static MyMeshComponent* GenerateMinimapAvatar(const std::string &MyMeshComponentName, Color color, float length = 1.f);
    //TSL
    static MyMeshComponent* GenerateSkyPlane(const std::string &MyMeshComponentName, Color color, int slices, float PlanetRadius, float AtmosphereRadius, float hTile, float vTile);
    static MyMeshComponent* GenerateTerrain(const std::string &MyMeshComponentName, const std::string &file_path, std::vector<unsigned char>&heightMap);
    static SpriteComponent* GenerateSpriteAnimation(const std::string &MyMeshComponentName, unsigned numRow, unsigned numCol);

    //Extras
    static MyMeshComponent* GenerateCircle(const std::string &MyMeshComponentName, Color color, unsigned numSlices = 36); //numSizes refers to resolution
private:
    static float CircleX(float theta);
    static float CircleZ(float theta);
    static float sphereX(float phi, float theta);
    static float sphereY(float phi, float theta);
    static float sphereZ(float phi, float theta);
};
