#pragma once

#include "cocos2d.h"

class ShadowLabel;

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
		ShadowLabel *label;
		cocos2d::Sprite *bgSprite;
		std::function<void()> onClick;

		ClickableButton(ShadowLabel *label, cocos2d::Sprite *bgSprite, std::function<void()> const& onClick)
			: label(label)
			, bgSprite(bgSprite)
			, onClick(onClick)
		{}
	};

	std::vector<ClickableButton> buttons;
};
