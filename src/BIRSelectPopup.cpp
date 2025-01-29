#include "BIRSelectPopup.hpp"
#include <Geode/binding/ButtonSprite.hpp>
#include <Geode/binding/GameManager.hpp>
#include <Geode/binding/GJGarageLayer.hpp>
#include <Geode/binding/SimplePlayer.hpp>
#include <Geode/loader/Mod.hpp>
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
    setTitle("Select Icons to Randomize");

    m_garageLayer = garageLayer;
    m_separateDualIcons = Loader::get()->getLoadedMod("weebify.separate_dual_icons");
    m_dual = m_separateDualIcons ? m_separateDualIcons->getSavedValue("2pselected", false) : false;

    m_iconMenu = CCMenu::create();
    m_iconMenu->setLayout(RowLayout::create()->setGap(6.0f));
    m_iconMenu->setContentSize({ 340.0f, 30.0f });
    m_iconMenu->setPosition({ 175.0f, 100.0f });
    m_mainLayer->addChild(m_iconMenu);

    m_iconToggles = CCArray::create();
    m_iconToggles->retain();
    createIconToggle("gj_iconBtn_off_001.png", "gj_iconBtn_on_001.png");
    createIconToggle("gj_shipBtn_off_001.png", "gj_shipBtn_on_001.png");
    createIconToggle("gj_ballBtn_off_001.png", "gj_ballBtn_on_001.png");
    createIconToggle("gj_birdBtn_off_001.png", "gj_birdBtn_on_001.png");
    createIconToggle("gj_dartBtn_off_001.png", "gj_dartBtn_on_001.png");
    createIconToggle("gj_robotBtn_off_001.png", "gj_robotBtn_on_001.png");
    createIconToggle("gj_spiderBtn_off_001.png", "gj_spiderBtn_on_001.png");
    createIconToggle("gj_swingBtn_off_001.png", "gj_swingBtn_on_001.png");
    createIconToggle("gj_jetpackBtn_off_001.png", "gj_jetpackBtn_on_001.png");

    m_specialToggles = CCArray::create();
    m_specialToggles->retain();
    createSpecialToggle("gj_streakBtn_off_001.png", "gj_streakBtn_on_001.png");
    createSpecialToggle("gj_explosionBtn_off_001.png", "gj_explosionBtn_on_001.png");

    m_iconMenu->updateLayout();

    m_colorMenu = CCMenu::create();
    m_colorMenu->setLayout(RowLayout::create()->setGap(20.0f));
    m_colorMenu->setContentSize({ 150.0f, 40.0f });
    m_colorMenu->setPosition({ 175.0f, 65.0f });
    m_mainLayer->addChild(m_colorMenu);

    auto gameManager = GameManager::sharedState();
    m_colorToggles = CCArray::create();
    m_colorToggles->retain();
    createColorToggle("1", gameManager->colorForIdx(IconRandomizer::active(ICON_RANDOMIZER_API_COLOR_1, m_dual)));
    createColorToggle("2", gameManager->colorForIdx(IconRandomizer::active(ICON_RANDOMIZER_API_COLOR_2, m_dual)));
    createColorToggle("G", gameManager->colorForIdx(IconRandomizer::active(ICON_RANDOMIZER_API_GLOW_COLOR, m_dual)));

    m_colorMenu->updateLayout();

    auto allMenu = CCMenu::create();
    allMenu->setLayout(ColumnLayout::create()->setGap(6.0f)->setAxisReverse(true));
    allMenu->setContentSize({ 30.0f, 80.0f });
    allMenu->setPosition({ 332.5f, 45.0f });
    m_mainLayer->addChild(allMenu);

    m_allIconsToggler = CCMenuItemExt::createTogglerWithStandardSprites(0.6f, [this](auto sender) { onAllToggle(m_iconToggles, sender); });
    allMenu->addChild(m_allIconsToggler);
    m_allSpecialsToggler = CCMenuItemExt::createTogglerWithStandardSprites(0.6f, [this](auto sender) { onAllToggle(m_specialToggles, sender); });
    allMenu->addChild(m_allSpecialsToggler);
    m_allColorsToggler = CCMenuItemExt::createTogglerWithStandardSprites(0.6f, [this](auto sender) { onAllToggle(m_colorToggles, sender); });
    allMenu->addChild(m_allColorsToggler);

    allMenu->updateLayout();

    auto allLabels = CCNode::create();
    allLabels->setLayout(ColumnLayout::create()->setGap(8.35f)->setCrossAxisLineAlignment(AxisAlignment::End)->setAxisReverse(true)->setAutoScale(false));
    allLabels->setContentSize({ 70.0f, 70.0f });
    allLabels->setAnchorPoint({ 1.0f, 0.5f });
    allLabels->setPosition({ 320.0f, 45.0f });
    m_mainLayer->addChild(allLabels);

    auto iconsLabel = CCLabelBMFont::create("Icons", "bigFont.fnt");
    iconsLabel->setScale(0.5f);
    allLabels->addChild(iconsLabel);
    auto specialsLabel = CCLabelBMFont::create("Special", "bigFont.fnt");
    specialsLabel->setScale(0.5f);
    allLabels->addChild(specialsLabel);
    auto colorsLabel = CCLabelBMFont::create("Colors", "bigFont.fnt");
    colorsLabel->setScale(0.5f);
    allLabels->addChild(colorsLabel);

    allLabels->updateLayout();

    auto randomizeButton = CCMenuItemExt::createSpriteExtra(ButtonSprite::create("Randomize", "goldFont.fnt", "GJ_button_01.png", 0.8f), [this](auto) { randomize(); });
    randomizeButton->setPosition({ 175.0f, 25.0f });
    m_buttonMenu->addChild(randomizeButton);

    IconRandomizer::init();

    return true;
}

void BIRSelectPopup::createIconToggle(const char* offFrame, const char* onFrame) {
    auto toggler = CCMenuItemExt::createTogglerWithFrameName(onFrame, offFrame, 0.75f, [this](auto sender) { onToggle(m_iconToggles, sender, m_allIconsToggler); });
    m_iconMenu->addChild(toggler);
    m_iconToggles->addObject(toggler);
}

void BIRSelectPopup::createSpecialToggle(const char* offFrame, const char* onFrame) {
    auto toggler = CCMenuItemExt::createTogglerWithFrameName(onFrame, offFrame, 0.75f, [this](auto sender) { onToggle(m_specialToggles, sender, m_allSpecialsToggler); });
    m_iconMenu->addChild(toggler);
    m_specialToggles->addObject(toggler);
}

void BIRSelectPopup::createColorToggle(const char* label, ccColor3B color) {
    ccColor3B darkColor = {
        (unsigned char)floorf(color.r * 0.6f),
        (unsigned char)floorf(color.g * 0.6f),
        (unsigned char)floorf(color.b * 0.6f)
    };

    auto colorLabelOff = CCLabelBMFont::create(label, "bigFont.fnt");
    colorLabelOff->setScale(0.5f);
    colorLabelOff->setColor(darkColor);
    auto colorSpriteOff = CCSprite::createWithSpriteFrameName("player_special_01_001.png");
    colorSpriteOff->setColor(darkColor);
    colorSpriteOff->addChild(colorLabelOff);
    auto colorLabelOn = CCLabelBMFont::create(label, "bigFont.fnt");
    colorLabelOn->setScale(0.5f);
    colorLabelOn->setColor(color);
    auto colorSpriteOn = CCSprite::createWithSpriteFrameName("player_special_01_001.png");
    colorSpriteOn->setColor(color);
    colorSpriteOn->addChild(colorLabelOn);
    auto toggler = CCMenuItemExt::createToggler(colorSpriteOn, colorSpriteOff, [this](auto sender) { onToggle(m_colorToggles, sender, m_allColorsToggler); });
    colorLabelOff->setPosition(colorSpriteOff->getPosition());
    colorLabelOn->setPosition(colorSpriteOn->getPosition());
    m_colorMenu->addChild(toggler);
    m_colorToggles->addObject(toggler);
}

void BIRSelectPopup::onToggle(CCArray* toggles, CCMenuItemToggler* toggler, CCMenuItemToggler* allToggler) {
    toggler->m_toggled = !toggler->m_toggled;
    auto toggled = true;
    for (auto toggle : CCArrayExt<CCMenuItemToggler*>(toggles)) {
        if (!toggle->m_toggled) {
            toggled = false;
            break;
        }
    }
    allToggler->toggle(toggled);
    toggler->m_toggled = !toggler->m_toggled;
}

void BIRSelectPopup::onAllToggle(CCArray* toggles, CCMenuItemToggler* allToggler) {
    for (auto toggle : CCArrayExt<CCMenuItemToggler*>(toggles)) {
        toggle->toggle(!allToggler->m_toggled);
    }
}

void BIRSelectPopup::randomize() {
    std::vector<IconType> enabledTypes;
    std::map<IconType, bool> moreIconsTypes;

    if (static_cast<CCMenuItemToggler*>(m_iconToggles->objectAtIndex(0))->m_toggled) {
        enabledTypes.push_back(IconType::Cube);
        auto num = IconRandomizer::randomize(ICON_RANDOMIZER_API_CUBE, m_dual);
        if (num > 0) m_garageLayer->m_iconPages[IconType::Cube] = (num - 1) / 36;
        else moreIconsTypes[IconType::Cube] = true;
    }
    if (static_cast<CCMenuItemToggler*>(m_iconToggles->objectAtIndex(1))->m_toggled) {
        enabledTypes.push_back(IconType::Ship);
        auto num = IconRandomizer::randomize(ICON_RANDOMIZER_API_SHIP, m_dual);
        if (num > 0) m_garageLayer->m_iconPages[IconType::Ship] = (num - 1) / 36;
        else moreIconsTypes[IconType::Ship] = true;
    }
    if (static_cast<CCMenuItemToggler*>(m_iconToggles->objectAtIndex(2))->m_toggled) {
        enabledTypes.push_back(IconType::Ball);
        auto num = IconRandomizer::randomize(ICON_RANDOMIZER_API_BALL, m_dual);
        if (num > 0) m_garageLayer->m_iconPages[IconType::Ball] = (num - 1) / 36;
        else moreIconsTypes[IconType::Ball] = true;
    }
    if (static_cast<CCMenuItemToggler*>(m_iconToggles->objectAtIndex(3))->m_toggled) {
        enabledTypes.push_back(IconType::Ufo);
        auto num = IconRandomizer::randomize(ICON_RANDOMIZER_API_UFO, m_dual);
        if (num > 0) m_garageLayer->m_iconPages[IconType::Ufo] = (num - 1) / 36;
        else moreIconsTypes[IconType::Ufo] = true;
    }
    if (static_cast<CCMenuItemToggler*>(m_iconToggles->objectAtIndex(4))->m_toggled) {
        enabledTypes.push_back(IconType::Wave);
        auto num = IconRandomizer::randomize(ICON_RANDOMIZER_API_WAVE, m_dual);
        if (num > 0) m_garageLayer->m_iconPages[IconType::Wave] = (num - 1) / 36;
        else moreIconsTypes[IconType::Wave] = true;
    }
    if (static_cast<CCMenuItemToggler*>(m_iconToggles->objectAtIndex(5))->m_toggled) {
        enabledTypes.push_back(IconType::Robot);
        auto num = IconRandomizer::randomize(ICON_RANDOMIZER_API_ROBOT, m_dual);
        if (num > 0) m_garageLayer->m_iconPages[IconType::Robot] = (num - 1) / 36;
        else moreIconsTypes[IconType::Robot] = true;
    }
    if (static_cast<CCMenuItemToggler*>(m_iconToggles->objectAtIndex(6))->m_toggled) {
        enabledTypes.push_back(IconType::Spider);
        auto num = IconRandomizer::randomize(ICON_RANDOMIZER_API_SPIDER, m_dual);
        if (num > 0) m_garageLayer->m_iconPages[IconType::Spider] = (num - 1) / 36;
        else moreIconsTypes[IconType::Spider] = true;
    }
    if (static_cast<CCMenuItemToggler*>(m_iconToggles->objectAtIndex(7))->m_toggled) {
        enabledTypes.push_back(IconType::Swing);
        auto num = IconRandomizer::randomize(ICON_RANDOMIZER_API_SWING, m_dual);
        if (num > 0) m_garageLayer->m_iconPages[IconType::Swing] = (num - 1) / 36;
        else moreIconsTypes[IconType::Swing] = true;
    }
    if (static_cast<CCMenuItemToggler*>(m_iconToggles->objectAtIndex(8))->m_toggled) {
        enabledTypes.push_back(IconType::Jetpack);
        auto num = IconRandomizer::randomize(ICON_RANDOMIZER_API_JETPACK, m_dual);
        if (num > 0) m_garageLayer->m_iconPages[IconType::Jetpack] = (num - 1) / 36;
        else moreIconsTypes[IconType::Jetpack] = true;
    }

    if (static_cast<CCMenuItemToggler*>(m_specialToggles->objectAtIndex(0))->m_toggled) {
        auto num = IconRandomizer::randomize(ICON_RANDOMIZER_API_TRAIL, m_dual);
        if (num > 0) m_garageLayer->m_iconPages[IconType::Special] = (num - 1) / 36;
        else moreIconsTypes[IconType::Special] = true;
        m_garageLayer->m_iconPages[IconType::ShipFire] = (IconRandomizer::randomize(ICON_RANDOMIZER_API_SHIP_FIRE, m_dual) - 1) / 36;
        IconRandomizer::randomize(ICON_RANDOMIZER_API_ANIMATION, m_dual);
    }
    if (static_cast<CCMenuItemToggler*>(m_specialToggles->objectAtIndex(1))->m_toggled) {
        auto num = IconRandomizer::randomize(ICON_RANDOMIZER_API_DEATH_EFFECT, m_dual);
        if (num > 0) m_garageLayer->m_iconPages[IconType::DeathEffect] = (num - 1) / 36;
        else moreIconsTypes[IconType::DeathEffect] = true;
    }

    if (static_cast<CCMenuItemToggler*>(m_colorToggles->objectAtIndex(0))->m_toggled) IconRandomizer::randomize(ICON_RANDOMIZER_API_COLOR_1, m_dual);
    if (static_cast<CCMenuItemToggler*>(m_colorToggles->objectAtIndex(1))->m_toggled) IconRandomizer::randomize(ICON_RANDOMIZER_API_COLOR_2, m_dual);
    if (static_cast<CCMenuItemToggler*>(m_colorToggles->objectAtIndex(2))->m_toggled) {
        IconRandomizer::randomize(ICON_RANDOMIZER_API_GLOW_COLOR, m_dual);
        IconRandomizer::randomize(ICON_RANDOMIZER_API_GLOW, m_dual);
    }

    auto gameManager = GameManager::sharedState();
    auto randomType = enabledTypes.empty() ? m_dual ? (IconType)m_separateDualIcons->getSavedValue("lasttype", 0) : gameManager->m_playerIconType :
        enabledTypes[(size_t)IconRandomizer::random(0, enabledTypes.size() - 1)];
    if (m_dual) {
        m_separateDualIcons->setSavedValue("lastmode", (int)randomType);
        m_separateDualIcons->setSavedValue("lasttype", (int)randomType);
    }
    else gameManager->m_playerIconType = randomType;
    auto playerFrame = IconRandomizer::active(IconRandomizer::fromIconType(randomType), m_dual);
    auto simplePlayer = m_dual ? static_cast<SimplePlayer*>(m_garageLayer->getChildByID("player2-icon")) : m_garageLayer->m_playerObject;
    simplePlayer->setScale(randomType == IconType::Jetpack ? 1.5f : 1.6f);
    simplePlayer->setColor(gameManager->colorForIdx(IconRandomizer::active(ICON_RANDOMIZER_API_COLOR_1, m_dual)));
    simplePlayer->setSecondColor(gameManager->colorForIdx(IconRandomizer::active(ICON_RANDOMIZER_API_COLOR_2, m_dual)));
    simplePlayer->setGlowOutline(gameManager->colorForIdx(IconRandomizer::active(ICON_RANDOMIZER_API_GLOW_COLOR, m_dual)));
    if (IconRandomizer::active(ICON_RANDOMIZER_API_GLOW, m_dual) == 0) simplePlayer->disableGlowOutline();
    simplePlayer->updatePlayerFrame(playerFrame, randomType);
    m_garageLayer->m_selectedIconType = randomType;
    m_garageLayer->m_iconID = playerFrame;
    m_garageLayer->onSelectTab(m_garageLayer->getChildByID("category-menu")->getChildByTag((int)randomType));
    if (auto moreIconsNav = m_garageLayer->getChildByID("hiimjustin000.more_icons/navdot-menu")) {
        if (moreIconsTypes[randomType]) {
            auto customIcon = MoreIcons::activeForType(randomType, m_dual);
            if (auto foundIcon = ranges::indexOf(MoreIcons::vectorForType(randomType), customIcon)) {
                MoreIcons::updateSimplePlayer(simplePlayer, customIcon, randomType);
                auto navDot = static_cast<CCMenuItemSpriteExtra*>(moreIconsNav->getChildren()->objectAtIndex(foundIcon.value() / 36));
                (navDot->m_pListener->*navDot->m_pfnSelector)(navDot);
            }
        }
    }

    if (!moreIconsTypes[randomType] && !enabledTypes.empty()) {
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
