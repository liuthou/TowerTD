#include "Angle.h"
//È¥ËÀ°É
bool Angle::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->setGLProgram(GLProgramCache::getInstance()->getGLProgram((GLProgram::SHADER_NAME_POSITION_LENGTH_TEXTURE_COLOR)));

	return true;
}

void Angle::visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
	Layer::visit(renderer, parentTransform, parentFlags);
	_command.init(0.1f);
	_command.func = CC_CALLBACK_0(Angle::onDraw, this);
	Director::getInstance()->getRenderer()->addCommand(&_command);
}

void Angle::onDraw()
{
	//get current shader of Angle
	auto glProgram = getGLProgram();
	
	//use the shader
	glProgram->use();

	//set some uniform 
	glProgram->setUniformsForBuiltins();

	auto size = Director::getInstance()->getWinSize();

	float vertercies[] = { 0, 0,
		size.width, 0,
		size.width / 2, size.height };

	float color[] = { 0, 1, 0, 1,
		1, 0, 0, 1,
		0, 0, 1, 1 };

	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);

	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertercies);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 3);

	CHECK_GL_ERROR_DEBUG();
}
