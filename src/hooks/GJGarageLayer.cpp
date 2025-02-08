#include "../classes/BIRSelectPopup.hpp"
#include <Geode/modify/GJGarageLayer.hpp>
#include <hiimjustin000.icon_randomizer_api/include/IconRandomizer.hpp>

using namespace geode::prelude;

class $modify(BIRGarageLayer, GJGarageLayer) {
    bool init() override {
        if (!GJGarageLayer::init()) return false;

        auto oldRBC = Mod::get()->getSettingValue<int64_t>("randomize-button-color");
        if (oldRBC > 0) {
            std::string colorStr;
            switch (oldRBC) {
                case 1: colorStr = "Green"; break;
                case 2: colorStr = "Pink"; break;
                case 3: colorStr = "Blue"; break;
                case 4: colorStr = "Cyan"; break;
                case 5: colorStr = "Gray"; break;
                case 6: colorStr = "Dark Purple"; break;
                case 7: colorStr = "Dark Aqua"; break;
                default: colorStr = "Random"; break;
            }
            Mod::get()->setSettingValue<std::string>("randomize-button-color-new", colorStr);
            Mod::get()->setSettingValue<int64_t>("randomize-button-color", 0);
        }
        auto colorStr = Mod::get()->getSettingValue<std::string>("randomize-button-color-new");
        auto color = 0;
        if (colorStr == "Green") color = 1;
        else if (colorStr == "Pink") color = 2;
        else if (colorStr == "Blue") color = 3;
        else if (colorStr == "Cyan") color = 4;
        else if (colorStr == "Gray") color = 5;
        else if (colorStr == "Dark Purple") color = 6;
        else if (colorStr == "Dark Aqua") color = 7;
        else color = IconRandomizer::random(1, 7);

        auto randomizeBtn = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName(fmt::format("BIR_randomBtn_{:02d}_001.png"_spr, color).c_str()),
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
