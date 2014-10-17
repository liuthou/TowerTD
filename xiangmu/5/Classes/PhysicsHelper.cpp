#include "PhysicsHelper.h"

PhysicsHelper * PhysicsHelper::instance = nullptr;

PhysicsHelper::PhysicsHelper() {
	vertexesFlies[0] = "barricade.plist";
	vertexesFlies[1] = "blade_low.plist";
	vertexesFlies[2] = "beartrap.plist";
	vertexesFlies[3] = "campfire.plist";
	vertexesFlies[4] = "chainhook.plist";
	vertexesFlies[5] = "e_fence.plist";
	vertexesFlies[6] = "fence.plist";
	vertexesFlies[7] = "ground_blade_low.plist";
	vertexesFlies[8] = "knife.plist";
	vertexesFlies[9] = "ropehook.plist";
}

PhysicsHelper::~PhysicsHelper() {
	
};

std::vector<std::vector<Vec2>> PhysicsHelper::getPhysicsShapeVertexesFromFile(const std::string plistFile) {
	std::vector<std::vector<Vec2>> vertexes;
	ValueVector v = FileUtils::getInstance()->getValueVectorFromFile(plistFile);
	for (int i=0; i<v.size(); i++) {
		ValueVector ver = v.at(i).asValueVector();
		std::vector<Vec2> stdVer;
		for (int j = 0; j < ver.size(); j++){
			Vec2 xy = PointFromString(ver.at(j).asString());
			stdVer.push_back(xy);
		}
		vertexes.push_back(stdVer);
	}
	return vertexes;
}

std::vector<std::vector<Vec2>> PhysicsHelper::getPhysicsShapeByName(const char * name) {
	return vertexesMap.at(name);
}

PhysicsHelper* PhysicsHelper::getInstance() {
	if (instance == nullptr) {
		instance = new PhysicsHelper();
		instance->loadShapes();
	}
	return instance;
}

void PhysicsHelper::loadShapes() {
	for (int i = 0; i < NUM_OF_BLOCK; i++) {
		vertexesMap[vertexesFlies[i]] = getPhysicsShapeVertexesFromFile(vertexesFlies[i]);
	}
}