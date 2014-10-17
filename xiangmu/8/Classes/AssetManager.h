#pragma once

#include "AppMacro.h"

/* 音频管理器 */
class AudioManager : public Ref {
	friend class AssetManager;
public:
	~AudioManager();
private:
	AudioManager();
};

/* 动画管理器 */
class AnimationManager : public Ref {
	friend class AssetManager;
public:
	Animation* getHeroAnimation(const char *name);
	void loadHeroAnimation(const char *plist);
	~AnimationManager();
private:
	AnimationManager();
private:
	AnimationCache *m_manager;
};

/* 纹理管理器 */
class TextureManager : public Ref {
	friend class AssetManager;
protected:
		~TextureManager();
public:
	Texture2D **getHeroNormalTextures();
	Texture2D *getEnemyTexture(const char *name);
	Texture2D *getTexureByName(const char *name);
	void loadTexture(const char *plist);

private:
	TextureManager();
private:
	TextureCache* m_manager;
};

/* 资源管理器 */
class AssetManager : public Ref {
public:
	~AssetManager(void);
	static AssetManager *getInstance();
	inline AudioManager *getAudioManager() {return m_audioManager;}
	inline AnimationManager *getAnimationManager() {return m_aniManager;}
	inline TextureManager *getTextureManager() {return m_textureManager;}
	void loadAsset();
private:
	AssetManager();
	AssetManager(AssetManager&);
private:
	AudioManager *m_audioManager;
	AnimationManager *m_aniManager;
	TextureManager *m_textureManager;
	static AssetManager *m_assetManager;
};

