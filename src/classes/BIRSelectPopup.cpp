#include "BIRSelectPopup.hpp"
#include <Geode/binding/ButtonSprite.hpp>
#include <Geode/binding/GameManager.hpp>
#include <Geode/binding/GJGarageLayer.hpp>
#include <Geode/binding/SimplePlayer.hpp>
#include <Geode/utils/ranges.hpp>
#include <hiimjustin000.icon_randomizer_api/include/IconRandomizer.hpp>
#include <hiimjustin000.more_icons/include/MoreIcons.hpp>

using namespace geode::prelude;

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
    setTitle("Select Icons to Randomize");
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
    iconMenu->setContentSize({ 340.0f, 20.0f });
    iconMenu->setPosition({ 175.0f, 110.0f });
    iconMenu->setID("icon-menu");
    m_mainLayer->addChild(iconMenu);

    m_iconToggles = CCArray::create();
    m_iconToggles->retain();
    createIconToggle(iconMenu, "gj_iconBtn_off_001.png", "gj_iconBtn_on_001.png", "cube-toggle");
    createIconToggle(iconMenu, "gj_shipBtn_off_001.png", "gj_shipBtn_on_001.png", "ship-toggle");
    createIconToggle(iconMenu, "gj_ballBtn_off_001.png", "gj_ballBtn_on_001.png", "ball-toggle");
    createIconToggle(iconMenu, "gj_birdBtn_off_001.png", "gj_birdBtn_on_001.png", "ufo-toggle");
    createIconToggle(iconMenu, "gj_dartBtn_off_001.png", "gj_dartBtn_on_001.png", "wave-toggle");
    createIconToggle(iconMenu, "gj_robotBtn_off_001.png", "gj_robotBtn_on_001.png", "robot-toggle");
    createIconToggle(iconMenu, "gj_spiderBtn_off_001.png", "gj_spiderBtn_on_001.png", "spider-toggle");
    createIconToggle(iconMenu, "gj_swingBtn_off_001.png", "gj_swingBtn_on_001.png", "swing-toggle");
    createIconToggle(iconMenu, "gj_jetpackBtn_off_001.png", "gj_jetpackBtn_on_001.png", "jetpack-toggle");

    iconMenu->updateLayout();

    auto specialMenu = CCMenu::create();
    specialMenu->setLayout(RowLayout::create()->setGap(15.0f));
    specialMenu->setContentSize({ 340.0f, 25.0f });
    specialMenu->setPosition({ 175.0f, 86.5f });
    specialMenu->setID("special-menu");
    m_mainLayer->addChild(specialMenu);

    m_specialToggles = CCArray::create();
    m_specialToggles->retain();
    createSpecialToggle(specialMenu, fmt::format("player_special_{:02}_001.png",
            IconRandomizer::active(ICON_RANDOMIZER_API_TRAIL, m_dual)), "trail-toggle");
    createSpecialToggle(specialMenu, fmt::format("shipfireIcon_{:02}_001.png",
        IconRandomizer::active(ICON_RANDOMIZER_API_SHIP_FIRE, m_dual)), "ship-fire-toggle");
    createSpecialToggle(specialMenu, "gjItem_18_001.png", "animation-toggle");
    createSpecialToggle(specialMenu, fmt::format("explosionIcon_{:02}_001.png",
        IconRandomizer::active(ICON_RANDOMIZER_API_DEATH_EFFECT, m_dual)), "death-toggle");

    specialMenu->updateLayout();

    auto colorMenu = CCMenu::create();
    colorMenu->setLayout(RowLayout::create()->setGap(20.0f));
    colorMenu->setContentSize({ 150.0f, 40.0f });
    colorMenu->setPosition({ 175.0f, 60.0f });
    colorMenu->setID("color-menu");
    m_mainLayer->addChild(colorMenu);

    auto gameManager = GameManager::get();
    m_colorToggles = CCArray::create();
    m_colorToggles->retain();
    createColorToggle(colorMenu, "1", gameManager->colorForIdx(IconRandomizer::active(ICON_RANDOMIZER_API_COLOR_1, m_dual)), "color-1-toggle");
    createColorToggle(colorMenu, "2", gameManager->colorForIdx(IconRandomizer::active(ICON_RANDOMIZER_API_COLOR_2, m_dual)), "color-2-toggle");
    createColorToggle(colorMenu, "G", gameManager->colorForIdx(IconRandomizer::active(ICON_RANDOMIZER_API_GLOW_COLOR, m_dual)), "color-glow-toggle");

    colorMenu->updateLayout();

    auto allMenu = CCMenu::create();
    allMenu->setLayout(ColumnLayout::create()->setGap(6.0f)->setAxisReverse(true));
    allMenu->setContentSize({ 30.0f, 80.0f });
    allMenu->setPosition({ 332.5f, 45.0f });
    allMenu->setID("all-menu");
    m_mainLayer->addChild(allMenu);

    m_allIconsToggler = CCMenuItemExt::createTogglerWithStandardSprites(0.6f, [this](CCMenuItemToggler* sender) {
        auto toggled = sender->m_toggled;
        for (auto toggle : CCArrayExt<CCMenuItemSpriteExtra*>(m_iconToggles)) {
            if (toggled == static_cast<CCBool*>(toggle->getUserObject("toggled"_spr))->getValue())
                (toggle->m_pListener->*toggle->m_pfnSelector)(toggle);
        }
        sender->m_toggled = toggled;
    });
    m_allIconsToggler->setID("all-icons-toggle");
    allMenu->addChild(m_allIconsToggler);

    m_allSpecialsToggler = CCMenuItemExt::createTogglerWithStandardSprites(0.6f, [this](CCMenuItemToggler* sender) {
        auto toggled = sender->m_toggled;
        for (auto toggle : CCArrayExt<CCMenuItemSpriteExtra*>(m_specialToggles)) {
            if (toggled == static_cast<CCBool*>(toggle->getUserObject("toggled"_spr))->getValue())
                (toggle->m_pListener->*toggle->m_pfnSelector)(toggle);
        }
        sender->m_toggled = toggled;
    });
    m_allSpecialsToggler->setID("all-specials-toggle");
    allMenu->addChild(m_allSpecialsToggler);

    m_allColorsToggler = CCMenuItemExt::createTogglerWithStandardSprites(0.6f, [this](CCMenuItemToggler* sender) {
        auto toggled = sender->m_toggled;
        for (auto toggle : CCArrayExt<CCMenuItemSpriteExtra*>(m_colorToggles)) {
            if (toggled == static_cast<CCBool*>(toggle->getUserObject("toggled"_spr))->getValue())
                (toggle->m_pListener->*toggle->m_pfnSelector)(toggle);
        }
        sender->m_toggled = toggled;
    });
    m_allColorsToggler->setID("all-colors-toggle");
    allMenu->addChild(m_allColorsToggler);

    allMenu->updateLayout();

    auto allLabels = CCNode::create();
    allLabels->setLayout(ColumnLayout::create()->setGap(8.35f)->setCrossAxisLineAlignment(AxisAlignment::End)->setAxisReverse(true)->setAutoScale(false));
    allLabels->setContentSize({ 70.0f, 70.0f });
    allLabels->setAnchorPoint({ 1.0f, 0.5f });
    allLabels->setPosition({ 320.0f, 45.0f });
    allLabels->setID("all-labels");
    m_mainLayer->addChild(allLabels);

    auto iconsLabel = CCLabelBMFont::create("Icons", "bigFont.fnt");
    iconsLabel->setScale(0.5f);
    iconsLabel->setID("all-icons-label");
    allLabels->addChild(iconsLabel);

    auto specialsLabel = CCLabelBMFont::create("Special", "bigFont.fnt");
    specialsLabel->setScale(0.5f);
    specialsLabel->setID("all-specials-label");
    allLabels->addChild(specialsLabel);

    auto colorsLabel = CCLabelBMFont::create("Colors", "bigFont.fnt");
    colorsLabel->setScale(0.5f);
    colorsLabel->setID("all-colors-label");
    allLabels->addChild(colorsLabel);

    allLabels->updateLayout();

    auto randomizeButton = CCMenuItemExt::createSpriteExtra(ButtonSprite::create("Randomize", "goldFont.fnt", "GJ_button_01.png", 0.8f), [this](auto) {
        randomize();
    });
    randomizeButton->setPosition({ 175.0f, 25.0f });
    randomizeButton->setID("randomize-button");
    m_buttonMenu->addChild(randomizeButton);

    IconRandomizer::init();

    return true;
}

void BIRSelectPopup::createIconToggle(CCMenu* iconMenu, std::string_view offFrame, std::string_view onFrame, std::string_view nodeID) {
    auto toggler = CCMenuItemExt::createSpriteExtraWithFrameName(offFrame, 0.6f, [this, offFrame, onFrame](CCMenuItemSpriteExtra* sender) {
        auto toggled = static_cast<CCBool*>(sender->getUserObject("toggled"_spr));
        toggled->setValue(!toggled->getValue());

        static_cast<CCSprite*>(sender->getNormalImage())->setDisplayFrame(
            CCSpriteFrameCache::get()->spriteFrameByName(toggled->getValue() ? onFrame.data() : offFrame.data()));

        auto iconToggles = reinterpret_cast<CCMenuItemSpriteExtra**>(m_iconToggles->data->arr);
        auto toggleCount = m_iconToggles->count();
        m_allIconsToggler->toggle(std::count_if(iconToggles, iconToggles + toggleCount, [](CCMenuItemSpriteExtra* toggle) {
            return static_cast<CCBool*>(toggle->getUserObject("toggled"_spr))->getValue();
        }) == toggleCount);
    });

    toggler->setUserObject("toggled"_spr, CCBool::create(false));
    toggler->setID(nodeID.data());
    iconMenu->addChild(toggler);
    m_iconToggles->addObject(toggler);
}

void BIRSelectPopup::createSpecialToggle(CCMenu* specialMenu, std::string_view frame, std::string_view nodeID) {
    auto togglerSprite = CCSprite::createWithSpriteFrameName(frame.data());
    togglerSprite->setScale(0.65f);
    togglerSprite->setColor({ 153, 153, 153 });

    auto toggler = CCMenuItemExt::createSpriteExtra(togglerSprite, [this](CCMenuItemSpriteExtra* sender) {
        auto toggled = static_cast<CCBool*>(sender->getUserObject("toggled"_spr));
        toggled->setValue(!toggled->getValue());

        static_cast<CCSprite*>(sender->getNormalImage())->setColor(toggled->getValue() ? ccColor3B { 255, 255, 255 } : ccColor3B { 153, 153, 153 });

        auto specialToggles = reinterpret_cast<CCMenuItemSpriteExtra**>(m_specialToggles->data->arr);
        auto toggleCount = m_specialToggles->count();
        m_allSpecialsToggler->toggle(std::count_if(specialToggles, specialToggles + toggleCount, [](CCMenuItemSpriteExtra* toggle) {
            return static_cast<CCBool*>(toggle->getUserObject("toggled"_spr))->getValue();
        }) == toggleCount);
    });
    
    toggler->setContentSize(CCSpriteFrameCache::get()->spriteFrameByName("playerSquare_001.png")->getOriginalSize() * 0.65f);
    togglerSprite->setPosition(toggler->getScaledContentSize() / 2.0f);
    toggler->setUserObject("toggled"_spr, CCBool::create(false));
    toggler->setID(nodeID.data());
    specialMenu->addChild(toggler);
    m_specialToggles->addObject(toggler);
}

void BIRSelectPopup::createColorToggle(CCMenu* colorMenu, std::string_view label, const ccColor3B& color, std::string_view nodeID) {
    ccColor3B darkColor = { (uint8_t)(color.r * 0.6f), (uint8_t)(color.g * 0.6f), (uint8_t)(color.b * 0.6f) };

    auto colorSprite = CCSprite::createWithSpriteFrameName("player_special_01_001.png");
    colorSprite->setScale(0.9f);
    colorSprite->setColor(darkColor);

    auto colorLabel = CCLabelBMFont::create(label.data(), "bigFont.fnt");
    colorLabel->setPosition(colorSprite->getContentSize() / 2.0f);
    colorLabel->setScale(0.5f);
    colorLabel->setColor(darkColor);
    colorSprite->addChild(colorLabel);

    auto toggler = CCMenuItemExt::createSpriteExtra(colorSprite, [this, color, darkColor](CCMenuItemSpriteExtra* sender) {
        auto toggled = static_cast<CCBool*>(sender->getUserObject("toggled"_spr));
        toggled->setValue(!toggled->getValue());

        static_cast<CCSprite*>(sender->getNormalImage())->setColor(toggled->getValue() ? color : darkColor);
        static_cast<CCLabelBMFont*>(static_cast<CCSprite*>(
            sender->getNormalImage())->getChildren()->objectAtIndex(0))->setColor(toggled->getValue() ? color : darkColor);

        auto colorToggles = reinterpret_cast<CCMenuItemSpriteExtra**>(m_colorToggles->data->arr);
        auto toggleCount = m_colorToggles->count();
        m_allColorsToggler->toggle(std::count_if(colorToggles, colorToggles + toggleCount, [](CCMenuItemSpriteExtra* toggle) {
            return static_cast<CCBool*>(toggle->getUserObject("toggled"_spr))->getValue();
        }) == toggleCount);
    });

    toggler->setUserObject("toggled"_spr, CCBool::create(false));
    toggler->setID(nodeID.data());
    colorMenu->addChild(toggler);
    m_colorToggles->addObject(toggler);
}

void BIRSelectPopup::randomize() {
    std::vector<IconType> enabledTypes;
    std::map<IconType, bool> moreIconsTypes;

    for (int i = 0; i < m_iconToggles->count(); i++) {
        auto toggle = static_cast<CCMenuItemSpriteExtra*>(m_iconToggles->objectAtIndex(i));
        auto iconType = (IconType)i;
        if (static_cast<CCBool*>(toggle->getUserObject("toggled"_spr))->getValue()) {
            enabledTypes.push_back(iconType);
            auto num = IconRandomizer::randomize(IconRandomizer::fromIconType(iconType), m_dual);
            if (num > 0) m_garageLayer->m_iconPages[iconType] = (num - 1) / 36;
            else moreIconsTypes[iconType] = true;
        }
    }

    auto specialToggles = reinterpret_cast<CCMenuItemSpriteExtra**>(m_specialToggles->data->arr);
    auto specialEnabled = false;
    auto deathEnabled = false;

    if (static_cast<CCBool*>(specialToggles[0]->getUserObject("toggled"_spr))->getValue()) {
        specialEnabled = true;
        auto num = IconRandomizer::randomize(ICON_RANDOMIZER_API_TRAIL, m_dual);
        if (num > 0) m_garageLayer->m_iconPages[IconType::Special] = (num - 1) / 36;
        else moreIconsTypes[IconType::Special] = true;
    }

    if (static_cast<CCBool*>(specialToggles[1]->getUserObject("toggled"_spr))->getValue()) {
        specialEnabled = true;
        auto num = IconRandomizer::randomize(ICON_RANDOMIZER_API_SHIP_FIRE, m_dual);
        if (num > 0) m_garageLayer->m_iconPages[IconType::ShipFire] = (num - 1) / 36;
        else moreIconsTypes[IconType::ShipFire] = true;
    }

    if (static_cast<CCBool*>(specialToggles[2]->getUserObject("toggled"_spr))->getValue()) {
        specialEnabled = true;
        IconRandomizer::randomize(ICON_RANDOMIZER_API_ANIMATION, m_dual);
    }

    if (static_cast<CCBool*>(specialToggles[3]->getUserObject("toggled"_spr))->getValue()) {
        deathEnabled = true;
        auto num = IconRandomizer::randomize(ICON_RANDOMIZER_API_DEATH_EFFECT, m_dual);
        if (num > 0) m_garageLayer->m_iconPages[IconType::DeathEffect] = (num - 1) / 36;
        else moreIconsTypes[IconType::DeathEffect] = true;
        IconRandomizer::randomize(ICON_RANDOMIZER_API_EXPLODE, m_dual);
    }

    auto colorToggles = reinterpret_cast<CCMenuItemSpriteExtra**>(m_colorToggles->data->arr);

    if (static_cast<CCBool*>(colorToggles[0]->getUserObject("toggled"_spr))->getValue())
        IconRandomizer::randomize(ICON_RANDOMIZER_API_COLOR_1, m_dual);

    if (static_cast<CCBool*>(colorToggles[1]->getUserObject("toggled"_spr))->getValue())
        IconRandomizer::randomize(ICON_RANDOMIZER_API_COLOR_2, m_dual);

    if (static_cast<CCBool*>(colorToggles[2]->getUserObject("toggled"_spr))->getValue()) {
        IconRandomizer::randomize(ICON_RANDOMIZER_API_GLOW_COLOR, m_dual);
        IconRandomizer::randomize(ICON_RANDOMIZER_API_GLOW, m_dual);
    }

    auto gameManager = GameManager::get();
    auto randomType = enabledTypes.empty() ? m_dual ? (IconType)m_separateDualIcons->getSavedValue("lastmode", 0) : gameManager->m_playerIconType :
        enabledTypes[IconRandomizer::random(0, enabledTypes.size() - 1)];
    auto selectedType = enabledTypes.empty() ? specialEnabled && deathEnabled ? (IconType)(98 + IconRandomizer::random(0, 1)) :
        specialEnabled ? IconType::Special : deathEnabled ? IconType::DeathEffect : randomType : randomType;
    if (m_dual) {
        m_separateDualIcons->setSavedValue("lastmode", (int)randomType);
        m_separateDualIcons->setSavedValue("lasttype", (int)selectedType);
    }
    else {
        gameManager->m_playerIconType = randomType;
        m_garageLayer->m_selectedIconType = selectedType;
        m_garageLayer->m_iconID = IconRandomizer::active(IconRandomizer::fromIconType(selectedType), m_dual);
    }

    auto simplePlayer = m_dual ? static_cast<SimplePlayer*>(m_garageLayer->getChildByID("player2-icon")) : m_garageLayer->m_playerObject;
    simplePlayer->setScale(randomType == IconType::Jetpack ? 1.5f : 1.6f);
    simplePlayer->setColor(gameManager->colorForIdx(IconRandomizer::active(ICON_RANDOMIZER_API_COLOR_1, m_dual)));
    simplePlayer->setSecondColor(gameManager->colorForIdx(IconRandomizer::active(ICON_RANDOMIZER_API_COLOR_2, m_dual)));
    simplePlayer->setGlowOutline(gameManager->colorForIdx(IconRandomizer::active(ICON_RANDOMIZER_API_GLOW_COLOR, m_dual)));
    if (IconRandomizer::active(ICON_RANDOMIZER_API_GLOW, m_dual) == 0) simplePlayer->disableGlowOutline();
    simplePlayer->updatePlayerFrame(IconRandomizer::active(IconRandomizer::fromIconType(randomType), m_dual), randomType);

    m_garageLayer->onSelectTab(m_garageLayer->getChildByID("category-menu")->getChildByTag((int)selectedType));
    if (auto moreIconsNav = m_garageLayer->getChildByID(MORE_ICONS_EXPAND("navdot-menu"))) {
        if (moreIconsTypes[randomType]) {
            auto customIcon = MoreIcons::activeForType(randomType, m_dual);
            if (auto foundIcon = ranges::indexOf(MoreIcons::vectorForType(randomType), customIcon))
                MoreIcons::updateSimplePlayer(simplePlayer, customIcon, randomType);
        }

        if (moreIconsTypes[selectedType]) {
            auto customIcon = MoreIcons::activeForType(selectedType, m_dual);
            if (auto foundIcon = ranges::indexOf(MoreIcons::vectorForType(selectedType), customIcon)) {
                auto navDot = static_cast<CCMenuItemSpriteExtra*>(moreIconsNav->getChildren()->objectAtIndex(foundIcon.value() / 36));
                (navDot->m_pListener->*navDot->m_pfnSelector)(navDot);
            }
        }
    }

    if (!moreIconsTypes[selectedType] && !enabledTypes.empty() && !specialEnabled && !deathEnabled) {
        if (auto pageButton = m_garageLayer->m_pageButtons->objectAtIndex((m_garageLayer->m_iconID - 1) / 36)) {
            auto page = static_cast<CCMenuItemSpriteExtra*>(pageButton);
            (page->m_pListener->*page->m_pfnSelector)(page);
        }
    }

    onClose(nullptr);
}

BIRSelectPopup::~BIRSelectPopup() {
    CC_SAFE_RELEASE(m_iconToggles);
    CC_SAFE_RELEASE(m_specialToggles);
    CC_SAFE_RELEASE(m_colorToggles);
}
