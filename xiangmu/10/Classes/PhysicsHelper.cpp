#include "PhysicsHelper.h"

PhysicsHelper * PhysicsHelper::instance = nullptr;

PhysicsHelper::PhysicsHelper() {
	vertexesFlies[0] = "cn.plist";
	vertexesFlies[1] = "usa.plist";
	vertexesFlies[2] = "rsa.plist";
	vertexesFlies[3] = "koran.plist";
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
			Vec2 xy = PointFromString(ver.at(j).asString());//把字符串直接转化成点类型
			stdVer.push_back(xy);
		}
		vertexes.push_back(stdVer);
	}
	return vertexes;
}

std::vector<std::vector<Vec2>> PhysicsHelper::getPhysicsShapeByName(const char *name) {
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
	for (int i = 0; i < NUM_OF_ENEMY; i++) {
		vertexesMap[vertexesFlies[i]] = getPhysicsShapeVertexesFromFile(vertexesFlies[i]);
	}

	vertexesMap["propBanShou.plist"] = getPhysicsShapeVertexesFromFile("propBanShou.plist");
}