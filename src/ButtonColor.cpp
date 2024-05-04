#include "ButtonColor.hpp"

bool ButtonColorSettingValue::load(matjson::Value const& json) {
    if (!json.is_number()) return false;
    auto value = json.as_int();
    m_value = value >= 0 && value <= 5 ? static_cast<ButtonColor>(value) : ButtonColor::Random;
    return true;
}

bool ButtonColorSettingValue::save(matjson::Value& json) const {
    json = static_cast<int>(m_value);
    return true;
}

SettingNode* ButtonColorSettingValue::createNode(float width) {
    return ButtonColorSettingNode::create(this, width);
}

ButtonColor ButtonColorSettingValue::getValue() const {
    return m_value;
}

void ButtonColorSettingValue::setValue(ButtonColor value) {
    m_value = value;
}

const char* buttonColorToString(ButtonColor color) {
    switch (color) {
        case ButtonColor::Random: return "Random";
        case ButtonColor::Green: return "Green";
        case ButtonColor::Pink: return "Pink";
        case ButtonColor::Blue: return "Blue";
        case ButtonColor::Cyan: return "Cyan";
        case ButtonColor::Gray: return "Gray";
        default: return "Unknown";
    }
}

void colorLabel(CCLabelBMFont* label, ButtonColor color) {
    if (color != ButtonColor::Random) {
        for (auto fontSprite : CCArrayExt<CCSprite*>(label->getChildren())) {
            fontSprite->setColor({ 255, 255, 255 });
        }
    }
    switch (color) {
        case ButtonColor::Random: {
            label->setColor({ 255, 255, 255 });
            auto fontSprites = CCArrayExt<CCSprite*>(label->getChildren());
            fontSprites[0]->setColor({ 255, 0, 0 });
            fontSprites[1]->setColor({ 255, 165, 0 });
            fontSprites[2]->setColor({ 255, 255, 0 });
            fontSprites[3]->setColor({ 0, 255, 0 });
            fontSprites[4]->setColor({ 0, 0, 255 });
            fontSprites[5]->setColor({ 128, 0, 128 });
            break;
        }
        case ButtonColor::Green: label->setColor({ 0, 255, 0 }); break;
        case ButtonColor::Pink: label->setColor({ 255, 0, 255 }); break;
        case ButtonColor::Blue: label->setColor({ 0, 0, 255 }); break;
        case ButtonColor::Cyan: label->setColor({ 0, 255, 255 }); break;
        case ButtonColor::Gray: label->setColor({ 128, 128, 128 }); break;
        default: label->setColor({ 255, 255, 255 }); break;
    }
}

ButtonColorSettingNode* ButtonColorSettingNode::create(ButtonColorSettingValue* value, float width) {
    auto ret = new ButtonColorSettingNode();
    if (ret && ret->init(value, width)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool ButtonColorSettingNode::init(ButtonColorSettingValue* value, float width) {
    if (!SettingNode::init(value)) return false;
    m_value = value;

    setContentSize({ width, 40.0f });

    m_uncommittedValue = static_cast<int>(value->getValue());

    m_nameLabel = CCLabelBMFont::create("Randomize Button Color", "bigFont.fnt");
    m_nameLabel->setAnchorPoint({ 0.0f, 0.5f });
    m_nameLabel->limitLabelWidth(width / 2 - 50.0f, 0.5f, 0.1f);
    m_nameLabel->setPosition(20.0f, 20.0f);
    addChild(m_nameLabel);

    auto menu = CCMenu::create();
    menu->setPosition(width - 20.0f, 20.0f);
    addChild(menu);

    auto infoSpr = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
    infoSpr->setScale(0.6f);
    auto infoBtn = CCMenuItemSpriteExtra::create(infoSpr, this, menu_selector(ButtonColorSettingNode::onDescription));
    infoBtn->setPositionX(-width + 40.0f + m_nameLabel->getScaledContentSize().width + 15.0f);
    menu->addChild(infoBtn);

    auto resetBtnSpr = CCSprite::createWithSpriteFrameName("geode.loader/reset-gold.png");
    resetBtnSpr->setScale(0.5f);
    m_resetBtn = CCMenuItemSpriteExtra::create(resetBtnSpr, this, menu_selector(ButtonColorSettingNode::onReset));
    m_resetBtn->setPositionX(-width + 40.0f + m_nameLabel->getScaledContentSize().width + 35.0f);
    menu->addChild(m_resetBtn);

    menu->setTouchEnabled(true);

    auto bgSprite = CCScale9Sprite::create("square02b_001.png", { 0.0f, 0.0f, 80.0f, 80.0f });
    bgSprite->setScale(0.325f);
    bgSprite->setColor({ 0, 0, 0 });
    bgSprite->setOpacity(75);
    bgSprite->setContentSize({ (width / 2 - 70.0f) * 2, 60.0f });
    bgSprite->setPositionX(-width / 4 + 35.0f);
    menu->addChild(bgSprite);

    m_label = CCLabelBMFont::create("", "chatFont.fnt");
    m_label->setScale(0.5525f);
    m_label->setPositionX(-width / 4 + 35.0f);
    menu->addChild(m_label);

    auto decArrowSpr = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");
    decArrowSpr->setFlipX(true);
    decArrowSpr->setScale(0.3f);
    auto decArrow = CCMenuItemSpriteExtra::create(decArrowSpr, this, menu_selector(ButtonColorSettingNode::onLeftArrow));
    decArrow->setPositionX(-width / 2 + 80.f);
    menu->addChild(decArrow);

    auto incArrowSpr = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");
    incArrowSpr->setScale(0.3f);
    auto incArrow = CCMenuItemSpriteExtra::create(incArrowSpr, this, menu_selector(ButtonColorSettingNode::onRightArrow));
    incArrow->setPositionX(-10.f);
    menu->addChild(incArrow);

    valueChanged();
    return true;
}

void ButtonColorSettingNode::onDescription(CCObject*) {
    FLAlertLayer::create("Randomize Button Color", "The color of the randomize button.", "OK")->show();
}

void ButtonColorSettingNode::onReset(CCObject*) {
    createQuickPopup("Reset", "Are you sure you want to <cr>reset</c> <cl>Randomize Button Color</c> to <cy>default</c>?", "Cancel", "Reset",
        [this](auto, bool btn2) { if (btn2) resetToDefault(); });
}

void ButtonColorSettingNode::onLeftArrow(CCObject*) {
    m_uncommittedValue -= 1;
    if (m_uncommittedValue < 0) m_uncommittedValue = 5;
    valueChanged();
}

void ButtonColorSettingNode::onRightArrow(CCObject*) {
    m_uncommittedValue += 1;
    if (m_uncommittedValue > 5) m_uncommittedValue = 0;
    valueChanged();
}

void ButtonColorSettingNode::valueChanged() {
    if (hasUncommittedChanges()) m_nameLabel->setColor({ 17, 221, 0 });
    else m_nameLabel->setColor({ 255, 255, 255 });
    m_resetBtn->setVisible(hasNonDefaultValue());
    dispatchChanged();
    auto buttonColor = static_cast<ButtonColor>(m_uncommittedValue);
    m_label->setString(buttonColorToString(buttonColor));
    colorLabel(m_label, buttonColor);
}

void ButtonColorSettingNode::commit() {
    auto settingValue = static_cast<ButtonColorSettingValue*>(m_value);
    settingValue->setValue(static_cast<ButtonColor>(m_uncommittedValue));
    ButtonColorSettingValue::randomColor = settingValue->getValue();
    m_uncommittedValue = static_cast<int>(ButtonColorSettingValue::randomColor);
    valueChanged();
    dispatchCommitted();
}

bool ButtonColorSettingNode::hasUncommittedChanges() {
    return static_cast<ButtonColor>(m_uncommittedValue) != static_cast<ButtonColorSettingValue*>(m_value)->getValue();
}

bool ButtonColorSettingNode::hasNonDefaultValue() {
    return static_cast<ButtonColor>(m_uncommittedValue) != ButtonColor::Random;
}

void ButtonColorSettingNode::resetToDefault() {
    m_uncommittedValue = 0;
    valueChanged();
}

ButtonColor SettingValueSetter<ButtonColor>::get(SettingValue* setting) {
    return static_cast<ButtonColorSettingValue*>(setting)->getValue();
}

void SettingValueSetter<ButtonColor>::set(SettingValue* setting, ButtonColor const& value) {
    static_cast<ButtonColorSettingValue*>(setting)->setValue(value);
}
