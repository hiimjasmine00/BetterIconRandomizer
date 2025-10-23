#include "../classes/BIRSelectPopup.hpp"
#include <Geode/modify/GJGarageLayer.hpp>
#include <hiimjustin000.icon_randomizer_api/include/IconRandomizer.hpp>

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
std::unordered_map<std::string, int> numbers = {
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

        auto mod = Mod::get();
        int oldRBC = mod->getSettingValue<int64_t>("randomize-button-color");
        if (oldRBC > 0) {
            mod->setSettingValue<std::string>("randomize-button-color-new", oldRBC < names.size() ? names[oldRBC] : "Random");
            mod->setSettingValue<int64_t>("randomize-button-color", 0);
        }

        auto it = numbers.find(mod->getSettingValue<std::string>("randomize-button-color-new"));
        auto randomizeBtn = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName(
                fmt::format("BIR_randomBtn_{:02}_001.png"_spr, it != numbers.end() ? it->second : IconRandomizer::random(1, 7)).c_str()
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
