#include "PauseScene.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "Utils.h"

USING_NS_CC;

Scene* PauseScene::createScene(std::string const& label, bool resumeAllowed)
{
	return Utils::CreateScene<PauseScene>(
		[label, resumeAllowed](){ return PauseScene::create(label, resumeAllowed); });
}

PauseScene* PauseScene::create(std::string const& label, bool resumeAllowed)
{
	return Utils::CreateCocosObject<PauseScene>(
		[](){ return new (std::nothrow) PauseScene(); },
		[label, resumeAllowed](PauseScene *s){ return s->init(label, resumeAllowed); });
}

bool PauseScene::init(std::string const& label, bool resumeAllowed)
{
	if (!ButtonScene::init())
		return false;


	auto labelNode = Sprite::create(label);
	labelNode->setPosition(Vec2(Utils::GetVisibleSize().width / 2, resumeAllowed ? 400 : 350));
	addChild(labelNode);


	if (resumeAllowed)
		AddButton("Resume", 300, [](){
			Director::getInstance()->popScene();
		});

	AddButton("Restart", 200, [](){
		Director::getInstance()->popScene();
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});

	AddButton("Main menu", 100, [](){
		Director::getInstance()->popScene();
		auto scene = MenuScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});


	return true;
}
