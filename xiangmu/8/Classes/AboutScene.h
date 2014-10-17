#pragma once

#include "AppMacro.h"

class AboutScene : public Layer {
protected:
    virtual bool init();
public:
    static Scene *createScene();
    CREATE_FUNC(AboutScene);
};