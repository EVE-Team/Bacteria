#include "EndScene.h"
#include "MenuScene.h"
#include "Utils.h"

USING_NS_CC;

Scene* EndScene::createScene()
{
	return Utils::CreateScene<EndScene>();
}

EndScene* EndScene::create()
{
	return Utils::CreateCocosObject<EndScene>(
		[](){ return new (std::nothrow) EndScene(); },
		[](EndScene *s){ return s->init(); });
}

bool EndScene::init()
{
	if (!ButtonScene::init())
		return false;


	auto labelNode = Sprite::create("victory.png");
	labelNode->setPosition(Vec2(Utils::GetVisibleSize().width / 2, 310));
	addChild(labelNode);


	AddButton("Main menu", 110, [](){
		auto scene = MenuScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});


	return true;
}
