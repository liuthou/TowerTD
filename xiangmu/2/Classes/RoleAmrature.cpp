#include "RoleAmrature.h"
#include "tinyxml2/tinyxml2.h"

 RoleAmrature* RoleAmrature::roleAmrature = nullptr;
 RoleAmrature * RoleAmrature::getInstance()
 {
	 if (roleAmrature==nullptr)
	 {
		 roleAmrature = new RoleAmrature();
		 auto fileName = FileUtils::getInstance()->getStringFromFile("MainRole.xml");
		 tinyxml2::XMLDocument  doc;
		 doc.Parse(fileName.c_str());
		 roleAmrature->roleLevel = doc.RootElement()->FirstChildElement()->IntAttribute("LEVEL");
		 roleAmrature->setRoleExp(doc.RootElement()->FirstChildElement()->IntAttribute("EXP"));
		 auto i = doc.RootElement()->FirstChildElement()->IntAttribute("MONEY");
		 roleAmrature->setRoleMoney(doc.RootElement()->FirstChildElement()->IntAttribute("MONEY"));
	 }
	 	 return roleAmrature;
 }

 RoleAmrature::~RoleAmrature()
 {
	 
 }
