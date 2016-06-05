#include "ShadowLabel.h"
#include "Utils.h"

USING_NS_CC;

ShadowLabel* ShadowLabel::createWithTTF(const std::string& text, const std::string& fontFilePath, float fontSize, Vec2 const& shadowShift,
	Color3B const& textColor, Color3B const& shadowColor,
	const Size& dimensions, TextHAlignment hAlignment, TextVAlignment vAlignment)
{
	return Utils::CreateCocosObject<ShadowLabel>(
		[](){ return new (std::nothrow) ShadowLabel(); },
		[&text, &fontFilePath, fontSize, &shadowShift, &textColor, &shadowColor, &dimensions, hAlignment, vAlignment](ShadowLabel *l){ return l->initWithTTF(text, fontFilePath, fontSize, shadowShift, textColor, shadowColor, dimensions, hAlignment, vAlignment); });
}

bool ShadowLabel::initWithTTF(const std::string& text, const std::string& fontFilePath, float fontSize, Vec2 const& shadowShift,
	Color3B const& textColor, Color3B const& shadowColor,
	const Size& dimensions, TextHAlignment hAlignment, TextVAlignment vAlignment)
{
	if (!Node::init())
		return false;


	this->shadowShift = shadowShift;

	shadow = Label::createWithTTF(text, fontFilePath, fontSize, dimensions, hAlignment, vAlignment);
	shadow->setColor(shadowColor);
	addChild(shadow);

	this->text = Label::createWithTTF(text, fontFilePath, fontSize, dimensions, hAlignment, vAlignment);
	this->text->setColor(textColor);
	addChild(this->text);


	return true;
}

void ShadowLabel::setPosition(Vec2 const& pos)
{
	text->setPosition(pos);
	shadow->setPosition(pos + shadowShift);
}

void ShadowLabel::setAnchorPoint(cocos2d::Vec2 const& point)
{
	text->setAnchorPoint(point);
	shadow->setAnchorPoint(point);
}

void ShadowLabel::setString(const std::string& text)
{
	this->text->setString(text);
	shadow->setString(text);
}
