#include "PauseScene.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "Utils.h"

USING_NS_CC;

Scene* PauseScene::createScene()
{
	return Utils::CreateScene<PauseScene>();
}

PauseScene* PauseScene::create()
{
	return Utils::CreateCocosObject<PauseScene>(
		[](){ return new (std::nothrow) PauseScene(); },
		[](PauseScene *s){ return s->init(); });
}

bool PauseScene::init()
{
	if (!ButtonScene::init())
		return false;


	auto labelNode = Sprite::create("pause.png");
	labelNode->setPosition(Vec2(Utils::GetVisibleSize().width / 2, 380));
	addChild(labelNode);


	AddButton("Resume", 240, [](){
		Director::getInstance()->popScene();
	});

	AddButton("Main menu", 115, [](){
		Director::getInstance()->popScene();
		auto scene = MenuScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});


	return true;
}
