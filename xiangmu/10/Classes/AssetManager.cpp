#include "AssetManager.h"

AudioManager::AudioManager() {
	
}

AudioManager::~AudioManager() {

}

/************************************************************************/

AnimationManager::AnimationManager() {
	m_manager = AnimationCache::getInstance();
	m_manager->retain();
}

AnimationManager::~AnimationManager() {
	CC_SAFE_RELEASE(m_manager);
}

Animation* AnimationManager::getHeroAnimation(const char *name) {
	std::string prefix("hero-");
	return m_manager->getAnimation(prefix + name);
}

void AnimationManager::loadHeroAnimation(const char *plist) {
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile(plist);
	auto animation = Animation::create();
	for (int i = 1; i < 3; i++)
	{
		auto filename = StringUtils::format("mainplaneIdle%d.png", i);
		animation->addSpriteFrame(cache->getSpriteFrameByName(filename));
	}
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(-1);
	m_manager->addAnimation(animation, "hero-normal");
}
/************************************************************************/

TextureManager::TextureManager() {
	m_manager = Director::getInstance()->getTextureCache();
	m_manager->retain();
}

TextureManager::~TextureManager() {
	CC_SAFE_RELEASE(m_manager);
}

Texture2D *TextureManager::getEnemyTexture(const char *name) {
	auto path = StringUtils::format("enemy-%s.png", name);
	auto texture = m_manager->getTextureForKey(path);
	if (texture == nullptr) {
		texture = m_manager->addImage(path);
	}
	return texture;
}

Texture2D **TextureManager::getHeroNormalTextures() {
	Texture2D *m_texture[2] = {nullptr, nullptr};
	m_texture[0] = m_manager->getTextureForKey("mainplaneIdle1.png");
	m_texture[1] = m_manager->getTextureForKey("mainplaneIdle2.png");
	return m_texture;
}

Texture2D *TextureManager::getTexureByName(const char *name) {
	return m_manager->getTextureForKey(name);
}

void TextureManager::loadTexture(const char *plist) {
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);
}

/************************************************************************/

AssetManager* AssetManager::m_assetManager = nullptr;

AssetManager::AssetManager(void) {
	m_textureManager = new TextureManager();
	m_audioManager = new AudioManager();
	m_aniManager = new AnimationManager();
}

AssetManager::~AssetManager(void) {
	CC_SAFE_RELEASE_NULL(m_aniManager);
	CC_SAFE_RELEASE_NULL(m_audioManager);
	CC_SAFE_RELEASE_NULL(m_textureManager);
}

AssetManager* AssetManager::getInstance() {
	if (m_assetManager == nullptr) {
		m_assetManager = new AssetManager();
		m_assetManager->loadAsset();
	}
	return m_assetManager;
}

void AssetManager::loadAsset() {
	m_textureManager->loadTexture("asset.plist");
	m_aniManager->loadHeroAnimation("mainplane.plist");
}
