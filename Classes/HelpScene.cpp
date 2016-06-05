#include "HelpScene.h"
#include "MenuScene.h"
#include "Utils.h"
#include "ShadowLabel.h"

USING_NS_CC;

Scene* HelpScene::createScene()
{
	return Utils::CreateScene<HelpScene>();
}

HelpScene* HelpScene::create()
{
	return Utils::CreateCocosObject<HelpScene>(
		[](){ return new (std::nothrow) HelpScene(); },
		[](HelpScene *s){ return s->init(); });
}

bool HelpScene::init()
{
	if (!ButtonScene::init())
		return false;


	std::string helpStr = R"*(Rules:
You are playing as a green cell. The aim is to eliminate all red cells on the level. While player cell is touching an enemy cell, the bigger one takes the mass off the smaller one. While player or enemy cell is touching a plankton, the cell takes the mass off the plankton. Mass exchange keeps going until the contact stops or one of the cells disappears completely.

Score points:
Plankton consumption: received mass * 0.25
Dash mass loss: lost mass * -0.3
Enemy consumption: received mass
Enemy mass loss: lost mass * -1.25)*";

	Size textW;
	textW.width = Utils::GetVisibleSize().width - 50;

	auto text = ShadowLabel::createWithTTF(helpStr, "fonts/arial.ttf", 24, Vec2(2, -2), Color3B(255, 255, 255), Color3B(0, 0, 0), textW);
	text->setPosition(Vec2(Utils::GetVisibleSize().width / 2, Utils::GetVisibleSize().height / 2 + 45));
	addChild(text);

	AddButton("Back to menu", 50, [](){
		auto scene = MenuScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});


	return true;
}
