#pragma once

#include "cocos2d.h"
USING_NS_CC;
#define NUM_OF_BLOCK 10

/*
	physics helper which contain's some utilities for physics
*/
class PhysicsHelper : public Ref {
private:
	static PhysicsHelper * instance;
	std::map<std::string, std::vector<std::vector<Vec2>>> vertexesMap;
	char* vertexesFlies[NUM_OF_BLOCK];
private:
	void loadShapes();
	PhysicsHelper();
public:
	static PhysicsHelper* getInstance();
	std::vector<std::vector<Vec2>> getPhysicsShapeByName(const char * name);
	~PhysicsHelper();

	/*
		get shape vertexes from a plist file
		
		the plist file format is :
			<plist version="1.0">
				<array>
					<dict>
						<key>x</key>
						<integer>0</integer>
						<key>y</key>
						<integer>1</integer>
					</dict>
					<dict>
						<key>x</key>
						<integer>1</integer>
						<key>y</key>
						<integer>1</integer>
					</dict>
					<dict>
						<key>x</key>
						<integer>2</integer>
						<key>y</key>
						<integer>1</integer>
					</dict>
				</array>
			</plist>
	*/
	std::vector<std::vector<Vec2>> getPhysicsShapeVertexesFromFile(const std::string plistFile);
};