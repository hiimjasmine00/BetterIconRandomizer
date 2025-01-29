#include "BIRSelectPopup.hpp"
#include <hiimjustin000.icon_randomizer_api/include/IconRandomizer.hpp>

using namespace geode::prelude;

enum class ButtonColor {
    Random,
    Green,
    Pink,
    Blue,
    Cyan,
    Gray,
    DarkPurple,
    DarkAqua
};

ButtonColor BUTTON_COLOR = ButtonColor::Random;

ButtonColor fromString(std::string const& str) {
    if (str == "Random") return ButtonColor::Random;
    else if (str == "Green") return ButtonColor::Green;
    else if (str == "Pink") return ButtonColor::Pink;
    else if (str == "Blue") return ButtonColor::Blue;
    else if (str == "Cyan") return ButtonColor::Cyan;
    else if (str == "Gray") return ButtonColor::Gray;
    else if (str == "Dark Purple") return ButtonColor::DarkPurple;
    else if (str == "Dark Aqua") return ButtonColor::DarkAqua;
    return ButtonColor::Random;
}

std::string toString(ButtonColor color) {
    switch (color) {
        case ButtonColor::Random: return "Random";
        case ButtonColor::Green: return "Green";
        case ButtonColor::Pink: return "Pink";
        case ButtonColor::Blue: return "Blue";
        case ButtonColor::Cyan: return "Cyan";
        case ButtonColor::Gray: return "Gray";
        case ButtonColor::DarkPurple: return "Dark Purple";
        case ButtonColor::DarkAqua: return "Dark Aqua";
        default: return "Random";
    }
}

#include <Geode/modify/GJGarageLayer.hpp>
class $modify(BIRGarageLayer, GJGarageLayer) {
    bool init() override {
        if (!GJGarageLayer::init()) return false;

        auto oldRBC = Mod::get()->getSettingValue<int64_t>("randomize-button-color");
        if (oldRBC > 0) {
            Mod::get()->setSettingValue<std::string>("randomize-button-color-new", toString(static_cast<ButtonColor>(oldRBC)));
            Mod::get()->setSettingValue<int64_t>("randomize-button-color", 0);
        }
        auto color = fromString(Mod::get()->getSettingValue<std::string>("randomize-button-color-new"));
        BUTTON_COLOR = color == ButtonColor::Random ? static_cast<ButtonColor>(IconRandomizer::random(1, 7)) : color;

        auto randomizeBtn = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName(fmt::format("BIR_randomBtn_{:02d}_001.png"_spr, static_cast<int>(BUTTON_COLOR)).c_str()),
            this, menu_selector(BIRGarageLayer::onSelectRandomize)
        );
        randomizeBtn->setID("select-randomize-button"_spr);
        auto shardsMenu = getChildByID("shards-menu");
        shardsMenu->addChild(randomizeBtn);
        shardsMenu->updateLayout();

        return true;
    }

    void onSelectRandomize(CCObject*) {
        BIRSelectPopup::create(this)->show();
    }
};
