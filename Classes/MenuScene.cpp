#include "MenuScene.h"
#include "GameScene.h"
#include "ScoreScene.h"
#include "Utils.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
	return Utils::CreateScene<MenuScene>();
}

MenuScene* MenuScene::create()
{
	return Utils::CreateCocosObject<MenuScene>(
		[](){ return new (std::nothrow) MenuScene(); },
		[](MenuScene *s){ return s->init(); });
}

bool MenuScene::init()
{
	if (!ButtonScene::init())
		return false;


	{
		auto label = Sprite::create("title.png");
		label->setPosition(Vec2(Utils::GetVisibleSize().width / 2, 400));
		addChild(label);
	}


	AddButton("New game", 300, [](){
		auto scene = GameScene::createScene(GameProgress());
		Director::getInstance()->replaceScene(scene);
	});

	AddButton("Scores", 200, [](){
		auto scene = ScoreScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});

	AddButton("Exit", 100, [](){
		Director::getInstance()->end();
	});


	return true;
}
