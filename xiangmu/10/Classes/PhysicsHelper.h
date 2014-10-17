#pragma once

#include "AppMacro.h"

#define NUM_OF_ENEMY 4

/*
	physics helper which contain's some utilities for physics
*/
class PhysicsHelper : public Ref {
private:
	static PhysicsHelper *instance;
	std::map<std::string, std::vector<std::vector<Vec2>>> vertexesMap;
	char *vertexesFlies[NUM_OF_ENEMY];
private:
	void loadShapes();
	PhysicsHelper();
public:
	static PhysicsHelper *getInstance();
	std::vector<std::vector<Vec2>> getPhysicsShapeByName(const char *name);
	~PhysicsHelper();

	/*
		get shape vertexes from a plist file
	*/
	std::vector<std::vector<Vec2>> getPhysicsShapeVertexesFromFile(const std::string plistFile);
};