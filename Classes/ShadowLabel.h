#pragma once

#include "cocos2d.h"

class ShadowLabel : public cocos2d::Node
{
public:
	static ShadowLabel* createWithTTF(const std::string& text, const std::string& fontFilePath, float fontSize, cocos2d::Vec2 const& shadowShift,
		cocos2d::Color3B const& textColor, cocos2d::Color3B const& shadowColor,
		const cocos2d::Size& dimensions = cocos2d::Size::ZERO, cocos2d::TextHAlignment hAlignment = cocos2d::TextHAlignment::LEFT,
		cocos2d::TextVAlignment vAlignment = cocos2d::TextVAlignment::TOP);

	bool initWithTTF(const std::string& text, const std::string& fontFilePath, float fontSize, cocos2d::Vec2 const& shadowShift,
		cocos2d::Color3B const& textColor, cocos2d::Color3B const& shadowColor,
		const cocos2d::Size& dimensions, cocos2d::TextHAlignment hAlignment,
		cocos2d::TextVAlignment vAlignment);

	void setPosition(cocos2d::Vec2 const& pos) override;
	void setAnchorPoint(cocos2d::Vec2 const& point) override;
	void setString(const std::string& text);

private:
	cocos2d::Vec2 shadowShift;
	cocos2d::Label *text;
	cocos2d::Label *shadow;
};
