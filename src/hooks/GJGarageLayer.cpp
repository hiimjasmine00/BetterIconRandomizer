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

$on_mod(Loaded) {
    auto mod = Mod::get();
    auto& data = mod->getSavedSettingsData();
    if (!mod->setSavedValue("migrated-color", true)) {
        if (auto indexRes = data["randomize-button-color"].asInt()) {
            auto index = indexRes.unwrap();
            if (index > 0) {
                if (auto setting = jasmine::setting::get<std::string>("randomize-button-color-new")) {
                    setting->setValue(index < names.size() ? names[index] : "Random");
                }
            }
        }
    }
}

class $modify(BIRGarageLayer, GJGarageLayer) {
    bool init() override {
        if (!GJGarageLayer::init()) return false;

        auto it = numbers.find(jasmine::setting::getValue<std::string>("randomize-button-color-new"));
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

    void onSelectRandomize(CCObject* sender) {
        BIRSelectPopup::create(this, static_cast<CCSprite*>(static_cast<CCMenuItemSprite*>(sender)->getNormalImage())->displayFrame())->show();
    }
};
