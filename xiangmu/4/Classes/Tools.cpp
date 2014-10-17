#include "Tools.h"

Tools *Tools::instance = nullptr;

Tools *Tools::getInstance() {
	if (instance == nullptr)
	{
		instance = new Tools();
	}
	return instance;
}

void Tools::addTools(Tool *tool) {
	toolVector.pushBack(tool);
}

void Tools::deleteTool() {
	for(auto it = toolVector.begin();it!=toolVector.end();) {
		if ((*it)->getDie())
		{
			it = toolVector.erase(it);
		} else {
			it++;
		}
	}
}

void Tools::reset() {
	toolVector.clear();
}