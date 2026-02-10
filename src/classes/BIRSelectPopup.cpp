#include "BIRSelectPopup.hpp"
#include <Geode/binding/ButtonSprite.hpp>
#include <Geode/binding/GameManager.hpp>
#include <Geode/binding/GJGarageLayer.hpp>
#include <Geode/binding/SimplePlayer.hpp>
//#include <geode.custom-keybinds/include/OptionalAPI.hpp>
#include <Geode/loader/Mod.hpp>
#include <Geode/utils/random.hpp>
#include <hiimjustin000.icon_randomizer_api/include/IconRandomizer.hpp>
#define MORE_ICONS_EVENTS
#include <hiimjustin000.more_icons/include/MoreIcons.hpp>

using namespace geode::prelude;
//using namespace keybinds;

std::array<bool, 18> toggleStates = {
    false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false
};

void registerBindable(const std::string& id, const std::string& name, const std::string& desc, std::initializer_list<enumKeyCodes> defaults) {
    /*if (auto cat = CategoryV2::create("Better Icon Randomizer")) {
        std::vector<Ref<Bind>> defs;
        for (auto key : defaults) {
            if (auto keybind = KeybindV2::create(key)) {
                defs.push_back(keybind.unwrap());
            }
            else return;
        }

        if (auto action = BindableActionV2::create(id, name, desc, defs, std::move(cat).unwrap())) {
            (void)BindManagerV2::registerBindable(std::move(action).unwrap());
        }
    }*/
}

void registerBindables() {
    // Icon Toggles
    registerBindable("select-cube"_spr, "Select Cube Toggle", "Selects the cube toggle.", { KEY_Q });
    registerBindable("select-ship"_spr, "Select Ship Toggle", "Selects the ship toggle.", { KEY_W });
    registerBindable("select-ball"_spr, "Select Ball Toggle", "Selects the ball toggle.", { KEY_E });
    registerBindable("select-ufo"_spr, "Select UFO Toggle", "Selects the UFO toggle.", { KEY_R });
    registerBindable("select-wave"_spr, "Select Wave Toggle", "Selects the wave toggle.", { KEY_T });
    registerBindable("select-robot"_spr, "Select Robot Toggle", "Selects the robot toggle.", { KEY_Y });
    registerBindable("select-spider"_spr, "Select Spider Toggle", "Selects the spider toggle.", { KEY_U });
    registerBindable("select-swing"_spr, "Select Swing Toggle", "Selects the swing toggle.", { KEY_I });
    registerBindable("select-jetpack"_spr, "Select Jetpack Toggle", "Selects the jetpack toggle.", { KEY_O });

    // Special Toggles
    registerBindable("select-trail"_spr, "Select Trail Toggle", "Selects the trail toggle.", { KEY_D });
    registerBindable("select-ship-fire"_spr, "Select Ship Fire Toggle", "Selects the ship fire toggle.", { KEY_F });
    registerBindable("select-animation"_spr, "Select Animation Toggle", "Selects the animation toggle.", { KEY_G });
    registerBindable("select-death"_spr, "Select Death Effect Toggle", "Selects the death effect toggle.", { KEY_H });
    registerBindable("select-explode"_spr, "Select Explode Toggle", "Selects the explode toggle.", { KEY_J });

    // Color Toggles
    registerBindable("select-color-1"_spr, "Select Primary Color Toggle", "Selects the primary color toggle.", { KEY_C });
    registerBindable("select-color-2"_spr, "Select Secondary Color Toggle", "Selects the secondary color toggle.", { KEY_V });
    registerBindable("select-color-glow"_spr, "Select Glow Color Toggle", "Selects the glow color toggle.", { KEY_B });
    registerBindable("select-glow"_spr, "Select Glow Toggle", "Selects the glow toggle.", { KEY_N });

    // "Select All" Toggles
    registerBindable("select-all-icons"_spr, "Select All Icon Toggles", "Selects all icon toggles.", { KEY_P });
    registerBindable("select-all-specials"_spr, "Select All Special Toggles", "Selects all special toggles.", { KEY_K });
    registerBindable("select-all-colors"_spr, "Select All Color Toggles", "Selects all color toggles.", { KEY_M });

    // Randomize Buttons
    registerBindable("randomize-toggles"_spr, "Randomize Toggles", "Randomizes the selected toggles.", { KEY_Z });
    registerBindable("randomize"_spr, "Randomize Icons", "Randomizes the selected icons.", { KEY_Enter, KEY_Space });
}

$execute {
    if (auto customKeybinds = Loader::get()->getInstalledMod("geode.custom-keybinds")) {
        if (customKeybinds->isLoaded()) {
            registerBindables();
        }
        else if (customKeybinds->shouldLoad()) {
            ModStateEvent(ModEventType::Loaded, customKeybinds).listen([] {
                registerBindables();
            }).leak();
        }
    }
}

BIRSelectPopup* BIRSelectPopup::create(GJGarageLayer* garageLayer, CCSpriteFrame* spriteFrame) {
    auto ret = new BIRSelectPopup();
    if (ret->init(garageLayer, spriteFrame)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool BIRSelectPopup::init(GJGarageLayer* garageLayer, CCSpriteFrame* spriteFrame) {
    if (!Popup::init(350.0f, 150.0f)) return false;

    setID("BIRSelectPopup");
    setTitle("Select Icons to Randomize", "goldFont.fnt", 0.7f, 15.0f);
    m_title->setID("select-randomize-title");
    m_mainLayer->setID("main-layer");
    m_buttonMenu->setID("button-menu");
    m_bgSprite->setID("background");
    m_closeBtn->setID("close-button");

    m_garageLayer = garageLayer;
    m_separateDualIcons = Loader::get()->getLoadedMod("weebify.separate_dual_icons");
    m_dual = m_separateDualIcons && m_separateDualIcons->getSavedValue("2pselected", false);

    auto iconMenu = CCMenu::create();
    iconMenu->setLayout(RowLayout::create()->setGap(10.0f));
    iconMenu->setContentSize({ 270.0f, 20.0f });
    iconMenu->setPosition({ 175.0f, 115.0f });
    iconMenu->setID("icon-menu");
    m_mainLayer->addChild(iconMenu);

    m_toggles[0].reserve(9);
    createIconToggle(iconMenu, "icon", "cube", RandomizeType::Cube);
    createIconToggle(iconMenu, "ship", "ship", RandomizeType::Ship);
    createIconToggle(iconMenu, "ball", "ball", RandomizeType::Ball);
    createIconToggle(iconMenu, "bird", "ufo", RandomizeType::Ufo);
    createIconToggle(iconMenu, "dart", "wave", RandomizeType::Wave);
    createIconToggle(iconMenu, "robot", "robot", RandomizeType::Robot);
    createIconToggle(iconMenu, "spider", "spider", RandomizeType::Spider);
    createIconToggle(iconMenu, "swing", "swing", RandomizeType::Swing);
    createIconToggle(iconMenu, "jetpack", "jetpack", RandomizeType::Jetpack);

    iconMenu->updateLayout();

    auto specialMenu = CCMenu::create();
    specialMenu->setLayout(RowLayout::create()->setGap(15.0f));
    specialMenu->setContentSize({ 180.0f, 25.0f });
    specialMenu->setPosition({ 175.0f, 91.5f });
    specialMenu->setID("special-menu");
    m_mainLayer->addChild(specialMenu);

    m_toggles[1].reserve(5);
    createSpecialToggle(specialMenu, "player_special", "trail", RandomizeType::Trail);
    createSpecialToggle(specialMenu, "shipfireIcon", "ship-fire", RandomizeType::ShipFire);
    createSpecialToggle(specialMenu, "gjItem", "animation", RandomizeType::Animation);
    createSpecialToggle(specialMenu, "explosionIcon", "death", RandomizeType::DeathEffect);
    createSpecialToggle(specialMenu, "", "explode", RandomizeType::Explode);
    specialMenu->updateLayout();

    auto colorMenu = CCMenu::create();
    colorMenu->setLayout(RowLayout::create()->setGap(15.0f));
    colorMenu->setContentSize({ 170.0f, 40.0f });
    colorMenu->setPosition({ 175.0f, 65.0f });
    colorMenu->setID("color-menu");
    m_mainLayer->addChild(colorMenu);

    m_toggles[2].reserve(4);
    createColorToggle(colorMenu, "1", "color-1", RandomizeType::Color1);
    createColorToggle(colorMenu, "2", "color-2", RandomizeType::Color2);
    createColorToggle(colorMenu, "G", "color-glow", RandomizeType::GlowColor);
    createColorToggle(colorMenu, "", "glow", RandomizeType::Glow);

    colorMenu->updateLayout();

    auto allMenu = CCMenu::create();
    allMenu->setLayout(ColumnLayout::create()->setGap(6.0f)->setAxisReverse(true));
    allMenu->setContentSize({ 30.0f, 80.0f });
    allMenu->setPosition({ 332.5f, 45.0f });
    allMenu->setID("all-menu");
    m_mainLayer->addChild(allMenu);

    auto allLabels = CCNode::create();
    allLabels->setLayout(ColumnLayout::create()
        ->setGap(8.35f)
        ->setCrossAxisLineAlignment(AxisAlignment::End)
        ->setAxisReverse(true)
        ->setAutoScale(false));
    allLabels->setContentSize({ 70.0f, 70.0f });
    allLabels->setAnchorPoint({ 1.0f, 0.5f });
    allLabels->setPosition({ 320.0f, 45.0f });
    allLabels->setID("all-labels");
    m_mainLayer->addChild(allLabels);

    createAllToggle(allMenu, allLabels, "Icons", "icons", RandomizeAllType::Icons);
    createAllToggle(allMenu, allLabels, "Specials", "specials", RandomizeAllType::Special);
    createAllToggle(allMenu, allLabels, "Colors", "colors", RandomizeAllType::Colors);

    allMenu->updateLayout();
    allLabels->updateLayout();

    auto randomizeTogglesSprite = CCSprite::createWithSpriteFrame(spriteFrame);
    randomizeTogglesSprite->setScale(0.8f);
    auto randomizeTogglesButton = CCMenuItemSpriteExtra::create(randomizeTogglesSprite, this, menu_selector(BIRSelectPopup::onRandomizeToggles));
    randomizeTogglesButton->setPosition({ 25.0f, 25.0f });
    randomizeTogglesButton->setID("randomize-toggles-button");
    m_buttonMenu->addChild(randomizeTogglesButton);

    listen(randomizeTogglesButton, "randomize-toggles"_spr);

    auto randomizeButton = CCMenuItemSpriteExtra::create(ButtonSprite::create("Randomize", 0.8f), this, menu_selector(BIRSelectPopup::onRandomize));
    randomizeButton->setPosition({ 175.0f, 25.0f });
    randomizeButton->setID("randomize-button");
    m_buttonMenu->addChild(randomizeButton);

    listen(randomizeButton, "randomize"_spr);

    IconRandomizer::init();

    return true;
}

void BIRSelectPopup::listen(CCMenuItem* item, const std::string& id) {
    /*addEventListener<InvokeBindFilterV2>([item](InvokeBindEventV2* event) {
        if (event->isDown()) item->activate();
        return ListenerResult::Propagate;
    }, id);*/
}

void BIRSelectPopup::updateToggles(bool icons, bool specials, bool colors) {
    if (icons) {
        m_allTogglers[0]->toggle(std::all_of(toggleStates.begin() + 4, toggleStates.begin() + 13, std::identity()));
    }
    if (specials) {
        m_allTogglers[1]->toggle(std::all_of(toggleStates.begin() + 13, toggleStates.begin() + 18, std::identity()));
    }
    if (colors) {
        m_allTogglers[2]->toggle(std::all_of(toggleStates.begin(), toggleStates.begin() + 4, std::identity()));
    }
}

CCMenuItemToggler* BIRSelectPopup::createToggle(
    CCMenu* menu, std::vector<CCMenuItemToggler*>& array, CCNode* offNode, CCNode* onNode, std::string_view id, RandomizeType type
) {
    auto toggler = CCMenuItemToggler::create(offNode, onNode, this, menu_selector(BIRSelectPopup::onToggle));
    toggler->toggle(toggleStates[(int)type]);
    toggler->setTag((int)type);
    toggler->setID(fmt::format("{}-toggle", id));
    menu->addChild(toggler);
    array.push_back(toggler);

    listen(toggler, fmt::format("select-{}"_spr, id));

    return toggler;
}

void BIRSelectPopup::onToggle(CCObject* sender) {
    auto type = sender->getTag();
    if (type < 0 || type > 17) return;
    toggleStates[type] = !static_cast<CCMenuItemToggler*>(sender)->m_toggled;
    updateToggles(type > 3 && type < 13, type > 12, type < 4);
}

void BIRSelectPopup::createIconToggle(CCMenu* menu, std::string_view prefix, std::string_view id, RandomizeType type) {
    auto offSprite = CCSprite::createWithSpriteFrameName(fmt::format("gj_{}Btn_off_001.png", prefix).c_str());
    offSprite->setScale(0.6f);

    auto onSprite = CCSprite::createWithSpriteFrameName(fmt::format("gj_{}Btn_on_001.png", prefix).c_str());
    onSprite->setScale(0.6f);

    createToggle(menu, m_toggles[0], offSprite, onSprite, id, type);
}

void BIRSelectPopup::createSpecialToggle(CCMenu* menu, std::string_view prefix, std::string_view id, RandomizeType type) {
    CCSprite* offSprite = nullptr;
    CCSprite* onSprite = nullptr;
    const char* sizeFrame = nullptr;

    if (type == RandomizeType::Explode) {
        offSprite = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
        offSprite->setScale(0.6f);

        onSprite = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
        onSprite->setScale(0.6f);

        sizeFrame = "GJ_checkOff_001.png";
    }
    else {
        auto frame = fmt::format("{}_{:02}_001.png", prefix,
            type != RandomizeType::Animation ? IconRandomizer::active(type, m_dual) : 18);

        offSprite = CCSprite::createWithSpriteFrameName(frame.c_str());
        offSprite->setScale(0.65f);
        offSprite->setColor({ 153, 153, 153 });

        onSprite = CCSprite::createWithSpriteFrameName(frame.c_str());
        onSprite->setScale(0.65f);

        sizeFrame = "playerSquare_001.png";
    }

    auto toggler = createToggle(menu, m_toggles[1], offSprite, onSprite, id, type);
    toggler->setContentSize(CCSpriteFrameCache::get()->spriteFrameByName(sizeFrame)->getOriginalSize() * 0.65f);
    toggler->updateSprite();
}

void BIRSelectPopup::createColorToggle(CCMenu* menu, const char* label, std::string_view id, RandomizeType type) {
    CCSprite* offSprite = nullptr;
    CCSprite* onSprite = nullptr;
    const char* sizeFrame = nullptr;

    if (type == RandomizeType::Glow) {
        offSprite = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
        offSprite->setScale(0.8f);

        onSprite = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
        onSprite->setScale(0.8f);

        sizeFrame = "GJ_checkOff_001.png";
    }
    else {
        auto color = GameManager::get()->colorForIdx(IconRandomizer::active(type, m_dual));
        ccColor3B darkColor(color.r * 0.6, color.g * 0.6, color.b * 0.6);

        offSprite = CCSprite::createWithSpriteFrameName("player_special_01_001.png");
        offSprite->setScale(0.85f);
        offSprite->setColor(darkColor);
        auto offLabel = CCLabelBMFont::create(label, "bigFont.fnt");
        offLabel->setPosition(offSprite->getContentSize() / 2.0f);
        offLabel->setScale(0.45f);
        offLabel->setColor(darkColor);
        offSprite->addChild(offLabel);

        onSprite = CCSprite::createWithSpriteFrameName("player_special_01_001.png");
        onSprite->setScale(0.85f);
        onSprite->setColor(color);
        auto onLabel = CCLabelBMFont::create(label, "bigFont.fnt");
        onLabel->setPosition(onSprite->getContentSize() / 2.0f);
        onLabel->setScale(0.45f);
        onLabel->setColor(color);
        onSprite->addChild(onLabel);

        sizeFrame = "player_special_01_001.png";
    }

    auto toggler = createToggle(menu, m_toggles[2], offSprite, onSprite, id, type);
    toggler->setContentSize(CCSpriteFrameCache::get()->spriteFrameByName(sizeFrame)->getOriginalSize() * 0.9f);
    toggler->updateSprite();
}

void BIRSelectPopup::createAllToggle(CCMenu* menu, CCNode* node, const char* text, std::string_view id, RandomizeAllType type) {
    auto offSprite = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
    offSprite->setScale(0.6f);
    auto onSprite = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
    onSprite->setScale(0.6f);
    auto toggler = CCMenuItemToggler::create(offSprite, onSprite, this, menu_selector(BIRSelectPopup::onAllToggle));
    m_allTogglers[(int)type] = toggler;
    updateToggles(type == RandomizeAllType::Icons, type == RandomizeAllType::Special, type == RandomizeAllType::Colors);
    toggler->setTag((int)type);
    toggler->setID(fmt::format("all-{}-toggle", id));
    menu->addChild(toggler);

    listen(toggler, fmt::format("select-all-{}"_spr, id));

    auto label = CCLabelBMFont::create(text, "bigFont.fnt");
    label->setScale(0.5f);
    label->setID(fmt::format("all-{}-label", id));
    node->addChild(label);
}

void BIRSelectPopup::onAllToggle(CCObject* sender) {
    auto type = sender->getTag();
    if (type < 0 || type > 2) return;
    auto toggled = !static_cast<CCMenuItemToggler*>(sender)->m_toggled;
    for (auto toggle : m_toggles[type]) {
        toggle->toggle(toggled);
        toggleStates[toggle->getTag()] = toggled;
    }
}

void BIRSelectPopup::onRandomizeToggles(CCObject* sender) {
    for (auto toggle : m_toggles[0]) {
        auto toggled = random::generate<bool>();
        toggleStates[toggle->getTag()] = toggled;
        toggle->toggle(toggled);
    }

    for (auto toggle : m_toggles[1]) {
        auto toggled = random::generate<bool>();
        toggleStates[toggle->getTag()] = toggled;
        toggle->toggle(toggled);
    }

    for (auto toggle : m_toggles[2]) {
        auto toggled = random::generate<bool>();
        toggleStates[toggle->getTag()] = toggled;
        toggle->toggle(toggled);
    }

    updateToggles(true, true, true);
}

void BIRSelectPopup::onRandomize(CCObject* sender) {
    auto gameManager = GameManager::get();
    std::vector<IconType> enabledTypes;
    for (auto toggle : m_toggles[0]) {
        if (toggle->m_toggled) {
            auto type = (RandomizeType)toggle->getTag();
            auto iconType = IconRandomizer::toIconType(type);
            enabledTypes.push_back(iconType);
            auto num = IconRandomizer::randomize(type, m_dual);
            if (num > 0) {
                m_garageLayer->m_iconPages[iconType] = (num - 1) / 36;
            }
            else if (auto icons = more_icons::getIcons(iconType)) {
                if (auto icon = more_icons::activeIcon(iconType, m_dual)) {
                    m_garageLayer->m_iconPages[iconType] = (gameManager->countForType(iconType) + 35) / 36 + (icon - icons->data()) / 36;
                }
            }
        }
    }

    auto specialEnabled = false;
    auto deathEnabled = false;

    for (auto toggle : m_toggles[1]) {
        if (toggle->m_toggled) {
            auto type = (RandomizeType)toggle->getTag();
            if (type == RandomizeType::DeathEffect || type == RandomizeType::Explode) deathEnabled = true;
            else specialEnabled = true;
            auto num = IconRandomizer::randomize(type, m_dual);
            if (type != RandomizeType::Animation && type != RandomizeType::Explode) {
                auto iconType = IconRandomizer::toIconType(type);
                if (num > 0) {
                    m_garageLayer->m_iconPages[iconType] = (num - 1) / 36;
                }
                else if (auto icons = more_icons::getIcons(iconType)) {
                    if (auto icon = more_icons::activeIcon(iconType, m_dual)) {
                        m_garageLayer->m_iconPages[iconType] = (gameManager->countForType(iconType) + 35) / 36 + (icon - icons->data()) / 36;
                    }
                }
            }
        }
    }

    for (auto toggle : m_toggles[2]) {
        if (toggle->m_toggled) {
            IconRandomizer::randomize((RandomizeType)toggle->getTag(), m_dual);
        }
    }

    auto randomType = m_dual ? (IconType)m_separateDualIcons->getSavedValue("lastmode", 0) : gameManager->m_playerIconType;
    auto selectedType = m_garageLayer->m_iconType;
    if (enabledTypes.empty()) {
        if (specialEnabled || deathEnabled) {
            if (specialEnabled && deathEnabled) {
                selectedType = (IconType)random::generate(98, 99);
            }
            else if (specialEnabled) {
                selectedType = IconType::Special;
            }
            else if (deathEnabled) {
                selectedType = IconType::DeathEffect;
            }
        }
    }
    else {
        randomType = enabledTypes[random::generate(0uz, enabledTypes.size() - 1)];
        selectedType = randomType;
    }
    auto activeIcon = IconRandomizer::active(IconRandomizer::fromIconType(selectedType), m_dual);

    if (!enabledTypes.empty() || specialEnabled || deathEnabled) {
        if (m_dual) {
            m_separateDualIcons->setSavedValue("lastmode", (int)randomType);
            m_separateDualIcons->setSavedValue("lasttype", (int)selectedType);
        }
        else {
            gameManager->m_playerIconType = randomType;
            m_garageLayer->m_selectedIconType = selectedType;
            m_garageLayer->m_iconID = activeIcon;
        }
    }

    auto simplePlayer = m_dual ? static_cast<SimplePlayer*>(m_garageLayer->getChildByID("player2-icon")) : m_garageLayer->m_playerObject;
    simplePlayer->setScale(randomType == IconType::Jetpack ? 1.5f : 1.6f);
    simplePlayer->updatePlayerFrame(IconRandomizer::active(IconRandomizer::fromIconType(randomType), m_dual), randomType);
    more_icons::updateSimplePlayer(simplePlayer, randomType, m_dual);
    simplePlayer->setColor(gameManager->colorForIdx(IconRandomizer::active(RandomizeType::Color1, m_dual)));
    simplePlayer->setSecondColor(gameManager->colorForIdx(IconRandomizer::active(RandomizeType::Color2, m_dual)));
    simplePlayer->enableCustomGlowColor(gameManager->colorForIdx(IconRandomizer::active(RandomizeType::GlowColor, m_dual)));
    simplePlayer->m_hasGlowOutline = IconRandomizer::active(RandomizeType::Glow, m_dual) != 0;
    simplePlayer->updateColors();

    m_garageLayer->selectTab(selectedType);

    onClose(nullptr);
}
