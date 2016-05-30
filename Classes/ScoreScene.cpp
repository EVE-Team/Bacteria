#include "ScoreScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* ScoreScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = ScoreScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool ScoreScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto background = Sprite::create("brushwalker137.png");
	Texture2D::TexParams tp;
	tp.minFilter = GL_LINEAR;
	tp.magFilter = GL_LINEAR;
	tp.wrapS = GL_REPEAT;
	tp.wrapT = GL_REPEAT;
	background->getTexture()->setTexParameters(tp);
	background->setTextureRect(Rect(Vec2(), visibleSize));
	background->setAnchorPoint(Vec2());
	addChild(background);

	menu = Label::createWithTTF("Back to menu", "fonts/Marker Felt.ttf", 36);
	menu->setColor(Color3B(0, 0, 0));
	menu->setPosition(Vec2(visibleSize.width / 2, 100));
	addChild(menu);


	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = [this](Touch* touch, Event* event)
	{
		auto location = touch->getLocation();

		if (menu->boundingBox().containsPoint(location))
		{
			auto scene = HelloWorld::createScene();
			Director::getInstance()->replaceScene(scene);
			return true;
		}

		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


	return true;
}
