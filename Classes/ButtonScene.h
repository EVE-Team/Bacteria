#pragma once

#include "cocos2d.h"

class ButtonScene : public cocos2d::Layer
{
public:
	virtual ~ButtonScene() = default;
	virtual bool init() override;

protected:
	void AddButton(std::string const& text, float posY, std::function<void()> const& onClick);

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
};