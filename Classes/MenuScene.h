#pragma once

#include "cocos2d.h"

class MenuScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	static MenuScene* create();
	bool init() override;

private:
	struct ClickableButton
	{
		cocos2d::Label *label;
		cocos2d::Sprite *bgSprite;
		std::function<void()> onClick;

		ClickableButton(cocos2d::Label *label, cocos2d::Sprite *bgSprite, std::function<void()> const& onClick)
			: label(label)
			, bgSprite(bgSprite)
			, onClick(onClick)
		{}
	};

	std::vector<ClickableButton> buttons;
	void AddButton(std::string const& text, float posY, std::function<void()> const& onClick);
};
