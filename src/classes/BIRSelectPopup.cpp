#include "BIRSelectPopup.hpp"
#include <Geode/binding/ButtonSprite.hpp>
#include <Geode/binding/GameManager.hpp>
#include <Geode/binding/GJGarageLayer.hpp>
#include <Geode/binding/SimplePlayer.hpp>
#include <geode.custom-keybinds/include/OptionalAPI.hpp>
#include <hiimjustin000.icon_randomizer_api/include/IconRandomizer.hpp>
#include <hiimjustin000.more_icons/include/MoreIcons.hpp>
#include <jasmine/random.hpp>

using namespace geode::prelude;
using namespace keybinds;

std::array<bool, 18> toggleStates = {
    false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false
};

void registerBindable(const std::string& id, const std::string& name, const std::string& desc, std::initializer_list<enumKeyCodes> defaults) {
    if (auto cat = CategoryV2::create("Better Icon Randomizer")) {
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
    }
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
        if (customKeybinds->isEnabled()) {
            registerBindables();
        }
        else {
            new EventListener(+[](ModStateEvent*) {
                registerBindables();
            }, ModStateFilter(customKeybinds, ModEventType::Loaded));
        }
    }
}

BIRSelectPopup* BIRSelectPopup::create(GJGarageLayer* garageLayer) {
    auto ret = new BIRSelectPopup();
    if (ret->initAnchored(350.0f, 150.0f, garageLayer)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool BIRSelectPopup::setup(GJGarageLayer* garageLayer) {
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

    m_iconToggles = CCArray::create();
    createIconToggle(iconMenu, "icon", "cube", ICON_RANDOMIZER_API_CUBE);
    createIconToggle(iconMenu, "ship", "ship", ICON_RANDOMIZER_API_SHIP);
    createIconToggle(iconMenu, "ball", "ball", ICON_RANDOMIZER_API_BALL);
    createIconToggle(iconMenu, "bird", "ufo", ICON_RANDOMIZER_API_UFO);
    createIconToggle(iconMenu, "dart", "wave", ICON_RANDOMIZER_API_WAVE);
    createIconToggle(iconMenu, "robot", "robot", ICON_RANDOMIZER_API_ROBOT);
    createIconToggle(iconMenu, "spider", "spider", ICON_RANDOMIZER_API_SPIDER);
    createIconToggle(iconMenu, "swing", "swing", ICON_RANDOMIZER_API_SWING);
    createIconToggle(iconMenu, "jetpack", "jetpack", ICON_RANDOMIZER_API_JETPACK);

    iconMenu->updateLayout();

    auto specialMenu = CCMenu::create();
    specialMenu->setLayout(RowLayout::create()->setGap(15.0f));
    specialMenu->setContentSize({ 180.0f, 25.0f });
    specialMenu->setPosition({ 175.0f, 91.5f });
    specialMenu->setID("special-menu");
    m_mainLayer->addChild(specialMenu);

    m_specialToggles = CCArray::create();
    createSpecialToggle(specialMenu, "player_special", "trail", ICON_RANDOMIZER_API_TRAIL);
    createSpecialToggle(specialMenu, "shipfireIcon", "ship-fire", ICON_RANDOMIZER_API_SHIP_FIRE);
    createSpecialToggle(specialMenu, "gjItem", "animation", ICON_RANDOMIZER_API_ANIMATION);
    createSpecialToggle(specialMenu, "explosionIcon", "death", ICON_RANDOMIZER_API_DEATH_EFFECT);
    createSpecialToggle(specialMenu, "", "explode", ICON_RANDOMIZER_API_EXPLODE);

    specialMenu->updateLayout();

    auto colorMenu = CCMenu::create();
    colorMenu->setLayout(RowLayout::create()->setGap(15.0f));
    colorMenu->setContentSize({ 170.0f, 40.0f });
    colorMenu->setPosition({ 175.0f, 65.0f });
    colorMenu->setID("color-menu");
    m_mainLayer->addChild(colorMenu);

    m_colorToggles = CCArray::create();
    createColorToggle(colorMenu, "1", "color-1", ICON_RANDOMIZER_API_COLOR_1);
    createColorToggle(colorMenu, "2", "color-2", ICON_RANDOMIZER_API_COLOR_2);
    createColorToggle(colorMenu, "G", "color-glow", ICON_RANDOMIZER_API_GLOW_COLOR);
    createColorToggle(colorMenu, "", "glow", ICON_RANDOMIZER_API_GLOW);

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

    createAllToggle(allMenu, allLabels, "Icons", "icons", ICON_RANDOMIZER_API_ALL_ICONS);
    createAllToggle(allMenu, allLabels, "Specials", "specials", ICON_RANDOMIZER_API_ALL_SPECIAL);
    createAllToggle(allMenu, allLabels, "Colors", "colors", ICON_RANDOMIZER_API_ALL_COLORS);

    allMenu->updateLayout();
    allLabels->updateLayout();

    auto shardsMenu = garageLayer->getChildByID("shards-menu");
    auto selectRandomizeButton = shardsMenu ? static_cast<CCMenuItemSprite*>(shardsMenu->getChildByID("select-randomize-button"_spr)) : nullptr;
    auto randomizeFrame = selectRandomizeButton
        ? static_cast<CCSprite*>(selectRandomizeButton->getNormalImage())->displayFrame()
        : CCSpriteFrameCache::get()->spriteFrameByName("BIR_randomBtn_01_001.png"_spr);
    auto randomizeTogglesSprite = CCSprite::createWithSpriteFrame(randomizeFrame);
    randomizeTogglesSprite->setScale(0.8f);
    auto randomizeTogglesButton = CCMenuItemExt::createSpriteExtra(randomizeTogglesSprite, [this](auto) {
        randomizeToggles();
    });
    randomizeTogglesButton->setPosition({ 25.0f, 25.0f });
    randomizeTogglesButton->setID("randomize-toggles-button");
    m_buttonMenu->addChild(randomizeTogglesButton);

    listen(randomizeTogglesButton, "randomize-toggles"_spr);

    auto randomizeButton = CCMenuItemExt::createSpriteExtra(ButtonSprite::create("Randomize", 0.8f), [this](auto) {
        randomize();
    });
    randomizeButton->setPosition({ 175.0f, 25.0f });
    randomizeButton->setID("randomize-button");
    m_buttonMenu->addChild(randomizeButton);

    listen(randomizeButton, "randomize"_spr);

    IconRandomizer::init();

    return true;
}

void BIRSelectPopup::listen(cocos2d::CCMenuItem* item, const std::string& id) {
    addEventListener<InvokeBindFilterV2>([item](InvokeBindEventV2* event) {
        if (event->isDown()) item->activate();
        return ListenerResult::Propagate;
    }, id);
}

void BIRSelectPopup::updateToggles(bool icons, bool specials, bool colors) {
    if (icons) {
        m_allIconsToggler->toggle(std::all_of(toggleStates.begin() + 4, toggleStates.begin() + 13, std::identity()));
    }
    if (specials) {
        m_allSpecialsToggler->toggle(std::all_of(toggleStates.begin() + 13, toggleStates.begin() + 18, std::identity()));
    }
    if (colors) {
        m_allColorsToggler->toggle(std::all_of(toggleStates.begin(), toggleStates.begin() + 4, std::identity()));
    }
}

CCMenuItemToggler* BIRSelectPopup::createToggle(CCMenu* menu, CCArray* array, CCNode* offNode, CCNode* onNode, std::string_view id, int type) {
    auto toggler = CCMenuItemExt::createToggler(onNode, offNode, [this](CCMenuItemToggler* sender) {
        auto type = sender->getTag();
        if (type < 0 || type > 17) return;
        toggleStates[(RandomizeType)type] = !sender->m_toggled;
        updateToggles(type > 3 && type < 13, type > 12, type < 4);
    });
    toggler->toggle(toggleStates[(RandomizeType)type]);
    toggler->setTag(type);
    toggler->setID(fmt::format("{}-toggle", id));
    menu->addChild(toggler);
    array->addObject(toggler);

    listen(toggler, fmt::format("select-{}"_spr, id));

    return toggler;
}

void BIRSelectPopup::createIconToggle(CCMenu* menu, std::string_view prefix, std::string_view id, int type) {
    auto offSprite = CCSprite::createWithSpriteFrameName(fmt::format("gj_{}Btn_off_001.png", prefix).c_str());
    offSprite->setScale(0.6f);

    auto onSprite = CCSprite::createWithSpriteFrameName(fmt::format("gj_{}Btn_on_001.png", prefix).c_str());
    onSprite->setScale(0.6f);

    createToggle(menu, m_iconToggles, offSprite, onSprite, id, type);
}

void BIRSelectPopup::createSpecialToggle(CCMenu* menu, std::string_view prefix, std::string_view id, int type) {
    CCSprite* offSprite = nullptr;
    CCSprite* onSprite = nullptr;
    const char* sizeFrame = nullptr;

    if (type == ICON_RANDOMIZER_API_EXPLODE) {
        offSprite = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
        offSprite->setScale(0.6f);

        onSprite = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
        onSprite->setScale(0.6f);

        sizeFrame = "GJ_checkOff_001.png";
    }
    else {
        auto frame = fmt::format("{}_{:02}_001.png", prefix,
            type != ICON_RANDOMIZER_API_ANIMATION ? IconRandomizer::active((RandomizeType)type, m_dual) : 18);

        offSprite = CCSprite::createWithSpriteFrameName(frame.c_str());
        offSprite->setScale(0.65f);
        offSprite->setColor({ 153, 153, 153 });

        onSprite = CCSprite::createWithSpriteFrameName(frame.c_str());
        onSprite->setScale(0.65f);

        sizeFrame = "playerSquare_001.png";
    }

    auto toggler = createToggle(menu, m_specialToggles, offSprite, onSprite, id, type);
    toggler->setContentSize(CCSpriteFrameCache::get()->spriteFrameByName(sizeFrame)->getOriginalSize() * 0.65f);
    toggler->updateSprite();
}

void BIRSelectPopup::createColorToggle(CCMenu* menu, const char* label, std::string_view id, int type) {
    CCSprite* offSprite = nullptr;
    CCSprite* onSprite = nullptr;
    const char* sizeFrame = nullptr;

    if (type == ICON_RANDOMIZER_API_GLOW) {
        offSprite = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
        offSprite->setScale(0.8f);

        onSprite = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
        onSprite->setScale(0.8f);

        sizeFrame = "GJ_checkOff_001.png";
    }
    else {
        auto color = GameManager::get()->colorForIdx(IconRandomizer::active((RandomizeType)type, m_dual));
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

    auto toggler = createToggle(menu, m_colorToggles, offSprite, onSprite, id, type);
    toggler->setContentSize(CCSpriteFrameCache::get()->spriteFrameByName(sizeFrame)->getOriginalSize() * 0.9f);
    toggler->updateSprite();
}

void BIRSelectPopup::createAllToggle(CCMenu* menu, CCNode* node, const char* text, std::string_view id, int type) {
    auto toggler = CCMenuItemExt::createTogglerWithStandardSprites(0.6f, [this](CCMenuItemToggler* sender) {
        auto toggled = !sender->m_toggled;
        for (auto toggle : CCArrayExt<CCMenuItemToggler*>(static_cast<CCArray*>(sender->getUserObject("toggles"_spr)))) {
            toggle->toggle(toggled);
            toggleStates[(RandomizeType)toggle->getTag()] = toggled;
        }
    });
    switch (type) {
        case ICON_RANDOMIZER_API_ALL_ICONS:
            m_allIconsToggler = toggler;
            updateToggles(true, false, false);
            toggler->setUserObject("toggles"_spr, m_iconToggles);
            break;
        case ICON_RANDOMIZER_API_ALL_SPECIAL:
            m_allSpecialsToggler = toggler;
            updateToggles(false, true, false);
            toggler->setUserObject("toggles"_spr, m_specialToggles);
            break;
        case ICON_RANDOMIZER_API_ALL_COLORS:
            m_allColorsToggler = toggler;
            updateToggles(false, false, true);
            toggler->setUserObject("toggles"_spr, m_colorToggles);
            break;
    }
    toggler->setID(fmt::format("all-{}-toggle", id));
    menu->addChild(toggler);

    listen(toggler, fmt::format("select-all-{}"_spr, id));

    auto label = CCLabelBMFont::create(text, "bigFont.fnt");
    label->setScale(0.5f);
    label->setID(fmt::format("all-{}-label", id));
    node->addChild(label);
}

void BIRSelectPopup::randomizeToggles() {
    for (auto toggle : CCArrayExt<CCMenuItemToggler*>(m_iconToggles)) {
        auto toggled = jasmine::random::getBool();
        toggleStates[(RandomizeType)toggle->getTag()] = toggled;
        toggle->toggle(toggled);
    }

    for (auto toggle : CCArrayExt<CCMenuItemToggler*>(m_specialToggles)) {
        auto toggled = jasmine::random::getBool();
        toggleStates[(RandomizeType)toggle->getTag()] = toggled;
        toggle->toggle(toggled);
    }

    for (auto toggle : CCArrayExt<CCMenuItemToggler*>(m_colorToggles)) {
        auto toggled = jasmine::random::getBool();
        toggleStates[(RandomizeType)toggle->getTag()] = toggled;
        toggle->toggle(toggled);
    }

    updateToggles(true, true, true);
}

void BIRSelectPopup::randomize() {
    auto gameManager = GameManager::get();
    std::vector<IconType> enabledTypes;
    for (auto toggle : CCArrayExt<CCMenuItemToggler*>(m_iconToggles)) {
        if (toggle->m_toggled) {
            auto type = (RandomizeType)toggle->getTag();
            auto iconType = IconRandomizer::toIconType(type);
            enabledTypes.push_back(iconType);
            auto num = IconRandomizer::randomize(type, m_dual);
            if (num > 0) {
                m_garageLayer->m_iconPages[iconType] = (num - 1) / 36;
            }
            else {
                auto customIcons = MoreIcons::getIcons(iconType);
                if (auto it = std::ranges::find(customIcons, MoreIcons::getIcon(iconType, m_dual)); it != customIcons.end()) {
                    m_garageLayer->m_iconPages[iconType] = (gameManager->countForType(iconType) + 35) / 36 + (it - customIcons.begin()) / 36;
                }
            }
        }
    }

    auto specialEnabled = false;
    auto deathEnabled = false;

    for (auto toggle : CCArrayExt<CCMenuItemToggler*>(m_specialToggles)) {
        if (toggle->m_toggled) {
            auto type = (RandomizeType)toggle->getTag();
            if (type == ICON_RANDOMIZER_API_DEATH_EFFECT || type == ICON_RANDOMIZER_API_EXPLODE) deathEnabled = true;
            else specialEnabled = true;
            auto num = IconRandomizer::randomize(type, m_dual);
            if (type != ICON_RANDOMIZER_API_ANIMATION && type != ICON_RANDOMIZER_API_EXPLODE) {
                auto iconType = IconRandomizer::toIconType(type);
                if (num > 0) {
                    m_garageLayer->m_iconPages[iconType] = (num - 1) / 36;
                }
                else {
                    auto customIcons = MoreIcons::getIcons(iconType);
                    if (auto it = std::ranges::find(customIcons, MoreIcons::getIcon(iconType, m_dual)); it != customIcons.end()) {
                        m_garageLayer->m_iconPages[iconType] = (gameManager->countForType(iconType) + 35) / 36 + (it - customIcons.begin()) / 36;
                    }
                }
            }
        }
    }

    for (auto toggle : CCArrayExt<CCMenuItemToggler*>(m_colorToggles)) {
        if (toggle->m_toggled) {
            IconRandomizer::randomize((RandomizeType)toggle->getTag(), m_dual);
        }
    }

    auto randomType = m_dual ? (IconType)m_separateDualIcons->getSavedValue("lastmode", 0) : gameManager->m_playerIconType;
    auto selectedType = m_garageLayer->m_iconType;
    if (enabledTypes.empty()) {
        if (specialEnabled || deathEnabled) {
            if (specialEnabled && deathEnabled) {
                selectedType = (IconType)jasmine::random::getInt(98, 99);
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
        randomType = enabledTypes[jasmine::random::getInt(0, enabledTypes.size() - 1)];
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
    MoreIcons::updateSimplePlayer(simplePlayer, randomType, m_dual);
    simplePlayer->setColor(gameManager->colorForIdx(IconRandomizer::active(ICON_RANDOMIZER_API_COLOR_1, m_dual)));
    simplePlayer->setSecondColor(gameManager->colorForIdx(IconRandomizer::active(ICON_RANDOMIZER_API_COLOR_2, m_dual)));
    simplePlayer->enableCustomGlowColor(gameManager->colorForIdx(IconRandomizer::active(ICON_RANDOMIZER_API_GLOW_COLOR, m_dual)));
    simplePlayer->m_hasGlowOutline = IconRandomizer::active(ICON_RANDOMIZER_API_GLOW, m_dual) != 0;
    simplePlayer->updateColors();

    m_garageLayer->selectTab(selectedType);

    onClose(nullptr);
}
