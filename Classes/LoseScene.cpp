#include "LoseScene.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "Utils.h"

USING_NS_CC;

Scene* LoseScene::createScene(GameProgress const& gameProgress)
{
	return Utils::CreateScene<LoseScene>(
		[&gameProgress](){ return LoseScene::create(gameProgress); });
}

LoseScene* LoseScene::create(GameProgress const& gameProgress)
{
	return Utils::CreateCocosObject<LoseScene>(
		[](){ return new (std::nothrow) LoseScene(); },
		[&gameProgress](LoseScene *s){ return s->init(gameProgress); });
}

bool LoseScene::init(GameProgress const& gameProgress)
{
	if (!ButtonScene::init())
		return false;


	auto labelNode = Sprite::create("lose.png");
	labelNode->setPosition(Vec2(Utils::GetVisibleSize().width / 2, 375));
	addChild(labelNode);


	AddButton("Restart", 210, [gameProgress](){
		auto newGameProgress(gameProgress);
		newGameProgress.score /= 2;

		auto scene = GameScene::createScene(newGameProgress);
		Director::getInstance()->replaceScene(scene);
	});

	AddButton("Main menu", 85, [](){
		auto scene = MenuScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});


	return true;
}
