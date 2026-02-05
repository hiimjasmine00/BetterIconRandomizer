#include "../classes/BIRSelectPopup.hpp"
#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/utils/random.hpp>
#include <jasmine/setting.hpp>

using namespace geode::prelude;

constexpr std::array names = {
    "Random",
    "Green",
    "Pink",
    "Blue",
    "Cyan",
    "Gray",
    "Dark Purple",
    "Dark Aqua"
};
StringMap<int> numbers = {
    { "Green", 1 },
    { "Pink", 2 },
    { "Blue", 3 },
    { "Cyan", 4 },
    { "Gray", 5 },
    { "Dark Purple", 6 },
    { "Dark Aqua", 7 }
};

class $modify(BIRGarageLayer, GJGarageLayer) {
    bool init() override {
        if (!GJGarageLayer::init()) return false;

        auto oldSetting = jasmine::setting::get<int>("randomize-button-color");
        auto newSetting = jasmine::setting::get<std::string>("randomize-button-color-new");
        if (oldSetting && newSetting) {
            int oldRBC = oldSetting->getValue();
            if (oldRBC > 0) {
                newSetting->setValue(oldRBC < names.size() ? names[oldRBC] : "Random");
                oldSetting->setValue(0);
            }
        }

        auto it = newSetting ? numbers.find(newSetting->getValue()) : numbers.end();
        auto randomizeBtn = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName(
                fmt::format("BIR_randomBtn_{:02}_001.png"_spr, it != numbers.end() ? it->second : random::generate(1, 7)).c_str()
            ),
            this, menu_selector(BIRGarageLayer::onSelectRandomize)
        );
        randomizeBtn->setID("select-randomize-button"_spr);
        if (auto shardsMenu = getChildByID("shards-menu")) {
            shardsMenu->addChild(randomizeBtn);
            shardsMenu->updateLayout();
        }

        return true;
    }

    void onSelectRandomize(CCObject*) {
        BIRSelectPopup::create(this)->show();
    }
};
