#include "BIRSelectPopup.hpp"
#include <Geode/binding/ButtonSprite.hpp>
#include <Geode/binding/GameManager.hpp>
#include <Geode/binding/GJGarageLayer.hpp>
#include <Geode/binding/SimplePlayer.hpp>
#ifndef GEODE_IS_IOS
#include <geode.custom-keybinds/include/Keybinds.hpp>
#endif
#include <hiimjustin000.icon_randomizer_api/include/IconRandomizer.hpp>
#include <hiimjustin000.more_icons/include/MoreIcons.hpp>

using namespace geode::prelude;
#ifndef GEODE_IS_IOS
using namespace keybinds;
#endif

std::map<RandomizeType, bool> TOGGLE_STATES = {
    { ICON_RANDOMIZER_API_COLOR_1, false },
    { ICON_RANDOMIZER_API_COLOR_2, false },
    { ICON_RANDOMIZER_API_GLOW_COLOR, false },
    { ICON_RANDOMIZER_API_CUBE, false },
    { ICON_RANDOMIZER_API_SHIP, false },
    { ICON_RANDOMIZER_API_BALL, false },
    { ICON_RANDOMIZER_API_UFO, false },
    { ICON_RANDOMIZER_API_WAVE, false },
    { ICON_RANDOMIZER_API_ROBOT, false },
    { ICON_RANDOMIZER_API_SPIDER, false },
    { ICON_RANDOMIZER_API_SWING, false },
    { ICON_RANDOMIZER_API_JETPACK, false },
    { ICON_RANDOMIZER_API_DEATH_EFFECT, false },
    { ICON_RANDOMIZER_API_TRAIL, false },
    { ICON_RANDOMIZER_API_SHIP_FIRE, false },
    { ICON_RANDOMIZER_API_ANIMATION, false }
};

#ifndef GEODE_IS_IOS
$execute {
    auto bindManager = BindManager::get();

    bindManager->registerBindable({
        "select-cube"_spr,
        "Select Cube Toggle",
        "Selects the cube icon toggle in the randomizer popup.",
        { Keybind::create(KEY_Q) },
        "Better Icon Randomizer"
    });
    bindManager->registerBindable({
        "select-ship"_spr,
        "Select Ship Toggle",
        "Selects the ship icon toggle in the randomizer popup.",
        { Keybind::create(KEY_W) },
        "Better Icon Randomizer"
    });
    bindManager->registerBindable({
        "select-ball"_spr,
        "Select Ball Toggle",
        "Selects the ball icon toggle in the randomizer popup.",
        { Keybind::create(KEY_E) },
        "Better Icon Randomizer"
    });
    bindManager->registerBindable({
        "select-ufo"_spr,
        "Select UFO Toggle",
        "Selects the UFO icon toggle in the randomizer popup.",
        { Keybind::create(KEY_R) },
        "Better Icon Randomizer"
    });
    bindManager->registerBindable({
        "select-wave"_spr,
        "Select Wave Toggle",
        "Selects the wave icon toggle in the randomizer popup.",
        { Keybind::create(KEY_T) },
        "Better Icon Randomizer"
    });
    bindManager->registerBindable({
        "select-robot"_spr,
        "Select Robot Toggle",
        "Selects the robot icon toggle in the randomizer popup.",
        { Keybind::create(KEY_Y) },
        "Better Icon Randomizer"
    });
    bindManager->registerBindable({
        "select-spider"_spr,
        "Select Spider Toggle",
        "Selects the spider icon toggle in the randomizer popup.",
        { Keybind::create(KEY_U) },
        "Better Icon Randomizer"
    });
    bindManager->registerBindable({
        "select-swing"_spr,
        "Select Swing Toggle",
        "Selects the swing icon toggle in the randomizer popup.",
        { Keybind::create(KEY_I) },
        "Better Icon Randomizer"
    });
    bindManager->registerBindable({
        "select-jetpack"_spr,
        "Select Jetpack Toggle",
        "Selects the jetpack icon toggle in the randomizer popup.",
        { Keybind::create(KEY_O) },
        "Better Icon Randomizer"
    });

    bindManager->registerBindable({
        "select-trail"_spr,
        "Select Trail Toggle",
        "Selects the trail icon toggle in the randomizer popup.",
        { Keybind::create(KEY_F) },
        "Better Icon Randomizer"
    });
    bindManager->registerBindable({
        "select-ship-fire"_spr,
        "Select Ship Fire Toggle",
        "Selects the ship fire icon toggle in the randomizer popup.",
        { Keybind::create(KEY_G) },
        "Better Icon Randomizer"
    });
    bindManager->registerBindable({
        "select-animation"_spr,
        "Select Animation Toggle",
        "Selects the animation icon toggle in the randomizer popup.",
        { Keybind::create(KEY_H) },
        "Better Icon Randomizer"
    });
    bindManager->registerBindable({
        "select-death"_spr,
        "Select Death Effect Toggle",
        "Selects the death effect icon toggle in the randomizer popup.",
        { Keybind::create(KEY_J) },
        "Better Icon Randomizer"
    });

    bindManager->registerBindable({
        "select-color-1"_spr,
        "Select Color 1 Toggle",
        "Selects the first color icon toggle in the randomizer popup.",
        { Keybind::create(KEY_V) },
        "Better Icon Randomizer"
    });
    bindManager->registerBindable({
        "select-color-2"_spr,
        "Select Color 2 Toggle",
        "Selects the second color icon toggle in the randomizer popup.",
        { Keybind::create(KEY_B) },
        "Better Icon Randomizer"
    });
    bindManager->registerBindable({
        "select-color-glow"_spr,
        "Select Glow Color Toggle",
        "Selects the glow color icon toggle in the randomizer popup.",
        { Keybind::create(KEY_N) },
        "Better Icon Randomizer"
    });

    bindManager->registerBindable({
        "select-all-icons"_spr,
        "Select All Icons Toggle",
        "Selects all icon toggles in the randomizer popup.",
        { Keybind::create(KEY_P) },
        "Better Icon Randomizer"
    });
    bindManager->registerBindable({
        "select-all-specials"_spr,
        "Select All Specials Toggle",
        "Selects all special icon toggles in the randomizer popup.",
        { Keybind::create(KEY_K) },
        "Better Icon Randomizer"
    });
    bindManager->registerBindable({
        "select-all-colors"_spr,
        "Select All Colors Toggle",
        "Selects all color icon toggles in the randomizer popup.",
        { Keybind::create(KEY_M) },
        "Better Icon Randomizer"
    });

    bindManager->registerBindable({
        "randomize-toggles"_spr,
        "Randomize Toggles",
        "Randomizes the selected toggles in the randomizer popup.",
        { Keybind::create(KEY_Z) },
        "Better Icon Randomizer"
    });
    bindManager->registerBindable({
        "randomize"_spr,
        "Randomize Icons",
        "Randomizes the selected icons in the randomizer popup.",
        { Keybind::create(KEY_Enter), Keybind::create(KEY_Space) },
        "Better Icon Randomizer"
    });
}
#endif

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
    createIconToggle(iconMenu, "gj_iconBtn_off_001.png", "gj_iconBtn_on_001.png", ICON_RANDOMIZER_API_CUBE)->setID("cube-toggle");
    createIconToggle(iconMenu, "gj_shipBtn_off_001.png", "gj_shipBtn_on_001.png", ICON_RANDOMIZER_API_SHIP)->setID("ship-toggle");
    createIconToggle(iconMenu, "gj_ballBtn_off_001.png", "gj_ballBtn_on_001.png", ICON_RANDOMIZER_API_BALL)->setID("ball-toggle");
    createIconToggle(iconMenu, "gj_birdBtn_off_001.png", "gj_birdBtn_on_001.png", ICON_RANDOMIZER_API_UFO)->setID("ufo-toggle");
    createIconToggle(iconMenu, "gj_dartBtn_off_001.png", "gj_dartBtn_on_001.png", ICON_RANDOMIZER_API_WAVE)->setID("wave-toggle");
    createIconToggle(iconMenu, "gj_robotBtn_off_001.png", "gj_robotBtn_on_001.png", ICON_RANDOMIZER_API_ROBOT)->setID("robot-toggle");
    createIconToggle(iconMenu, "gj_spiderBtn_off_001.png", "gj_spiderBtn_on_001.png", ICON_RANDOMIZER_API_SPIDER)->setID("spider-toggle");
    createIconToggle(iconMenu, "gj_swingBtn_off_001.png", "gj_swingBtn_on_001.png", ICON_RANDOMIZER_API_SWING)->setID("swing-toggle");
    createIconToggle(iconMenu, "gj_jetpackBtn_off_001.png", "gj_jetpackBtn_on_001.png", ICON_RANDOMIZER_API_JETPACK)->setID("jetpack-toggle");

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
        IconRandomizer::active(ICON_RANDOMIZER_API_TRAIL, m_dual)), ICON_RANDOMIZER_API_TRAIL)->setID("trail-toggle");
    createSpecialToggle(specialMenu, fmt::format("shipfireIcon_{:02}_001.png",
        IconRandomizer::active(ICON_RANDOMIZER_API_SHIP_FIRE, m_dual)), ICON_RANDOMIZER_API_SHIP_FIRE)->setID("ship-fire-toggle");
    createSpecialToggle(specialMenu, "gjItem_18_001.png", ICON_RANDOMIZER_API_ANIMATION)->setID("animation-toggle");
    createSpecialToggle(specialMenu, fmt::format("explosionIcon_{:02}_001.png",
        IconRandomizer::active(ICON_RANDOMIZER_API_DEATH_EFFECT, m_dual)), ICON_RANDOMIZER_API_DEATH_EFFECT)->setID("death-toggle");

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
    createColorToggle(colorMenu, "1", gameManager->colorForIdx(IconRandomizer::active(
        ICON_RANDOMIZER_API_COLOR_1, m_dual)), ICON_RANDOMIZER_API_COLOR_1)->setID("color-1-toggle");
    createColorToggle(colorMenu, "2", gameManager->colorForIdx(IconRandomizer::active(
        ICON_RANDOMIZER_API_COLOR_2, m_dual)), ICON_RANDOMIZER_API_COLOR_2)->setID("color-2-toggle");
    createColorToggle(colorMenu, "G", gameManager->colorForIdx(IconRandomizer::active(
        ICON_RANDOMIZER_API_GLOW_COLOR, m_dual)), ICON_RANDOMIZER_API_GLOW_COLOR)->setID("color-glow-toggle");

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
    m_allIconsToggler->toggle(TOGGLE_STATES[ICON_RANDOMIZER_API_CUBE] && TOGGLE_STATES[ICON_RANDOMIZER_API_SHIP] &&
        TOGGLE_STATES[ICON_RANDOMIZER_API_BALL] && TOGGLE_STATES[ICON_RANDOMIZER_API_UFO] && TOGGLE_STATES[ICON_RANDOMIZER_API_WAVE] &&
        TOGGLE_STATES[ICON_RANDOMIZER_API_ROBOT] && TOGGLE_STATES[ICON_RANDOMIZER_API_SPIDER] && TOGGLE_STATES[ICON_RANDOMIZER_API_SWING] &&
        TOGGLE_STATES[ICON_RANDOMIZER_API_JETPACK]);
    allMenu->addChild(m_allIconsToggler);

    #ifndef GEODE_IS_IOS
    addEventListener<InvokeBindFilter>([this](InvokeBindEvent* event) {
        if (event->isDown()) {
            (m_allIconsToggler->m_pListener->*m_allIconsToggler->m_pfnSelector)(m_allIconsToggler);
            m_allIconsToggler->toggle(!m_allIconsToggler->m_toggled);
        }
        return ListenerResult::Propagate;
    }, "select-all-icons"_spr);
    #endif

    m_allSpecialsToggler = CCMenuItemExt::createTogglerWithStandardSprites(0.6f, [this](CCMenuItemToggler* sender) {
        auto toggled = sender->m_toggled;
        for (auto toggle : CCArrayExt<CCMenuItemSpriteExtra*>(m_specialToggles)) {
            if (toggled == static_cast<CCBool*>(toggle->getUserObject("toggled"_spr))->getValue())
                (toggle->m_pListener->*toggle->m_pfnSelector)(toggle);
        }
        sender->m_toggled = toggled;
    });
    m_allSpecialsToggler->setID("all-specials-toggle");
    m_allSpecialsToggler->toggle(TOGGLE_STATES[ICON_RANDOMIZER_API_TRAIL] && TOGGLE_STATES[ICON_RANDOMIZER_API_SHIP_FIRE] &&
        TOGGLE_STATES[ICON_RANDOMIZER_API_ANIMATION] && TOGGLE_STATES[ICON_RANDOMIZER_API_DEATH_EFFECT]);
    allMenu->addChild(m_allSpecialsToggler);

    #ifndef GEODE_IS_IOS
    addEventListener<InvokeBindFilter>([this](InvokeBindEvent* event) {
        if (event->isDown()) {
            (m_allSpecialsToggler->m_pListener->*m_allSpecialsToggler->m_pfnSelector)(m_allSpecialsToggler);
            m_allSpecialsToggler->toggle(!m_allSpecialsToggler->m_toggled);
        }
        return ListenerResult::Propagate;
    }, "select-all-specials"_spr);
    #endif

    m_allColorsToggler = CCMenuItemExt::createTogglerWithStandardSprites(0.6f, [this](CCMenuItemToggler* sender) {
        auto toggled = sender->m_toggled;
        for (auto toggle : CCArrayExt<CCMenuItemSpriteExtra*>(m_colorToggles)) {
            if (toggled == static_cast<CCBool*>(toggle->getUserObject("toggled"_spr))->getValue())
                (toggle->m_pListener->*toggle->m_pfnSelector)(toggle);
        }
        sender->m_toggled = toggled;
    });
    m_allColorsToggler->setID("all-colors-toggle");
    m_allColorsToggler->toggle(TOGGLE_STATES[ICON_RANDOMIZER_API_COLOR_1] && TOGGLE_STATES[ICON_RANDOMIZER_API_COLOR_2] &&
        TOGGLE_STATES[ICON_RANDOMIZER_API_GLOW_COLOR]);
    allMenu->addChild(m_allColorsToggler);

    #ifndef GEODE_IS_IOS
    addEventListener<InvokeBindFilter>([this](InvokeBindEvent* event) {
        if (event->isDown()) {
            (m_allColorsToggler->m_pListener->*m_allColorsToggler->m_pfnSelector)(m_allColorsToggler);
            m_allColorsToggler->toggle(!m_allColorsToggler->m_toggled);
        }
        return ListenerResult::Propagate;
    }, "select-all-colors"_spr);
    #endif

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

    auto shardsMenu = m_garageLayer->getChildByID("shards-menu");
    auto selectRandomizeButton = shardsMenu ? static_cast<CCMenuItemSprite*>(shardsMenu->getChildByID("select-randomize-button"_spr)) : nullptr;
    auto randomizeTogglesSprite = selectRandomizeButton ? CCSprite::createWithSpriteFrame(static_cast<CCSprite*>(
        selectRandomizeButton->getNormalImage())->displayFrame()) : CCSprite::createWithSpriteFrameName("BIR_randomBtn_01_001.png"_spr);
    randomizeTogglesSprite->setScale(0.8f);
    auto randomizeTogglesButton = CCMenuItemExt::createSpriteExtra(randomizeTogglesSprite, [this](auto) { randomizeToggles(); });
    randomizeTogglesButton->setPosition({ 25.0f, 25.0f });
    randomizeTogglesButton->setID("randomize-toggles-button");
    m_buttonMenu->addChild(randomizeTogglesButton);

    #ifndef GEODE_IS_IOS
    addEventListener<InvokeBindFilter>([this](InvokeBindEvent* event) {
        if (event->isDown()) randomizeToggles();
        return ListenerResult::Propagate;
    }, "randomize-toggles"_spr);
    #endif

    auto randomizeButton = CCMenuItemExt::createSpriteExtra(ButtonSprite::create("Randomize", "goldFont.fnt", "GJ_button_01.png", 0.8f), [this](auto) {
        randomize();
    });
    randomizeButton->setPosition({ 175.0f, 25.0f });
    randomizeButton->setID("randomize-button");
    m_buttonMenu->addChild(randomizeButton);

    #ifndef GEODE_IS_IOS
    addEventListener<InvokeBindFilter>([this](InvokeBindEvent* event) {
        if (event->isDown()) randomize();
        return ListenerResult::Propagate;
    }, "randomize"_spr);
    #endif

    IconRandomizer::init();

    return true;
}

CCMenuItemSpriteExtra* BIRSelectPopup::createIconToggle(CCMenu* iconMenu, std::string_view offFrame, std::string_view onFrame, int type) {
    auto toggler = CCMenuItemExt::createSpriteExtraWithFrameName(TOGGLE_STATES[(RandomizeType)type] ? onFrame : offFrame, 0.6f,
        [this, offFrame, onFrame](CCMenuItemSpriteExtra* sender) {
            auto toggled = static_cast<CCBool*>(sender->getUserObject("toggled"_spr));
            toggled->setValue(!toggled->getValue());

            TOGGLE_STATES[(RandomizeType)sender->getTag()] = toggled->getValue();

            static_cast<CCSprite*>(sender->getNormalImage())->setDisplayFrame(
                CCSpriteFrameCache::get()->spriteFrameByName(toggled->getValue() ? onFrame.data() : offFrame.data()));

            auto iconToggles = reinterpret_cast<CCNode**>(m_iconToggles->data->arr);
            auto toggleCount = m_iconToggles->count();
            m_allIconsToggler->toggle(std::count_if(iconToggles, iconToggles + toggleCount, [](CCNode* toggle) {
                return static_cast<CCBool*>(toggle->getUserObject("toggled"_spr))->getValue();
            }) == toggleCount);
        });

    toggler->setUserObject("toggled"_spr, CCBool::create(TOGGLE_STATES[(RandomizeType)type]));
    toggler->setTag(type);
    iconMenu->addChild(toggler);
    m_iconToggles->addObject(toggler);

    #ifndef GEODE_IS_IOS
    addEventListener<InvokeBindFilter>([toggler](InvokeBindEvent* event) {
        if (event->isDown()) (toggler->m_pListener->*toggler->m_pfnSelector)(toggler);
        return ListenerResult::Propagate;
    }, keybindIDs[type]);
    #endif

    return toggler;
}

CCMenuItemSpriteExtra* BIRSelectPopup::createSpecialToggle(CCMenu* specialMenu, std::string_view frame, int type) {
    auto togglerSprite = CCSprite::createWithSpriteFrameName(frame.data());
    togglerSprite->setScale(0.65f);
    togglerSprite->setColor(TOGGLE_STATES[(RandomizeType)type] ? ccColor3B { 255, 255, 255 } : ccColor3B { 153, 153, 153 });

    auto toggler = CCMenuItemExt::createSpriteExtra(togglerSprite, [this](CCMenuItemSpriteExtra* sender) {
        auto toggled = static_cast<CCBool*>(sender->getUserObject("toggled"_spr));
        toggled->setValue(!toggled->getValue());

        TOGGLE_STATES[(RandomizeType)sender->getTag()] = toggled->getValue();

        static_cast<CCSprite*>(sender->getNormalImage())->setColor(toggled->getValue() ? ccColor3B { 255, 255, 255 } : ccColor3B { 153, 153, 153 });

        auto specialToggles = reinterpret_cast<CCNode**>(m_specialToggles->data->arr);
        auto toggleCount = m_specialToggles->count();
        m_allSpecialsToggler->toggle(std::count_if(specialToggles, specialToggles + toggleCount, [](CCNode* toggle) {
            return static_cast<CCBool*>(toggle->getUserObject("toggled"_spr))->getValue();
        }) == toggleCount);
    });

    toggler->setContentSize(CCSpriteFrameCache::get()->spriteFrameByName("playerSquare_001.png")->getOriginalSize() * 0.65f);
    togglerSprite->setPosition(toggler->getScaledContentSize() / 2.0f);
    toggler->setUserObject("toggled"_spr, CCBool::create(TOGGLE_STATES[(RandomizeType)type]));
    toggler->setTag(type);
    specialMenu->addChild(toggler);
    m_specialToggles->addObject(toggler);

    #ifndef GEODE_IS_IOS
    addEventListener<InvokeBindFilter>([toggler](InvokeBindEvent* event) {
        if (event->isDown()) (toggler->m_pListener->*toggler->m_pfnSelector)(toggler);
        return ListenerResult::Propagate;
    }, keybindIDs[type]);
    #endif

    return toggler;
}

CCMenuItemSpriteExtra* BIRSelectPopup::createColorToggle(CCMenu* colorMenu, std::string_view label, const ccColor3B& color, int type) {
    ccColor3B darkColor = { (uint8_t)(color.r * 0.6f), (uint8_t)(color.g * 0.6f), (uint8_t)(color.b * 0.6f) };

    auto colorSprite = CCSprite::createWithSpriteFrameName("player_special_01_001.png");
    colorSprite->setScale(0.9f);
    colorSprite->setColor(TOGGLE_STATES[(RandomizeType)type] ? color : darkColor);

    auto colorLabel = CCLabelBMFont::create(label.data(), "bigFont.fnt");
    colorLabel->setPosition(colorSprite->getContentSize() / 2.0f);
    colorLabel->setScale(0.5f);
    colorLabel->setColor(TOGGLE_STATES[(RandomizeType)type] ? color : darkColor);
    colorSprite->addChild(colorLabel);

    auto toggler = CCMenuItemExt::createSpriteExtra(colorSprite, [this, color, darkColor](CCMenuItemSpriteExtra* sender) {
        auto toggled = static_cast<CCBool*>(sender->getUserObject("toggled"_spr));
        toggled->setValue(!toggled->getValue());

        TOGGLE_STATES[(RandomizeType)sender->getTag()] = toggled->getValue();

        static_cast<CCSprite*>(sender->getNormalImage())->setColor(toggled->getValue() ? color : darkColor);
        static_cast<CCLabelBMFont*>(static_cast<CCSprite*>(
            sender->getNormalImage())->getChildren()->objectAtIndex(0))->setColor(toggled->getValue() ? color : darkColor);

        auto colorToggles = reinterpret_cast<CCNode**>(m_colorToggles->data->arr);
        auto toggleCount = m_colorToggles->count();
        m_allColorsToggler->toggle(std::count_if(colorToggles, colorToggles + toggleCount, [](CCNode* toggle) {
            return static_cast<CCBool*>(toggle->getUserObject("toggled"_spr))->getValue();
        }) == toggleCount);
    });

    toggler->setUserObject("toggled"_spr, CCBool::create(TOGGLE_STATES[(RandomizeType)type]));
    toggler->setTag(type);
    colorMenu->addChild(toggler);
    m_colorToggles->addObject(toggler);

    #ifndef GEODE_IS_IOS
    addEventListener<InvokeBindFilter>([toggler](InvokeBindEvent* event) {
        if (event->isDown()) (toggler->m_pListener->*toggler->m_pfnSelector)(toggler);
        return ListenerResult::Propagate;
    }, keybindIDs[type]);
    #endif

    return toggler;
}

void BIRSelectPopup::randomizeToggles() {
    for (auto iconToggle : CCArrayExt<CCMenuItemSpriteExtra*>(m_iconToggles)) {
        if (static_cast<CCBool*>(iconToggle->getUserObject("toggled"_spr))->getValue() != IconRandomizer::random(0, 1))
            (iconToggle->m_pListener->*iconToggle->m_pfnSelector)(iconToggle);
    }

    for (auto specialToggle : CCArrayExt<CCMenuItemSpriteExtra*>(m_specialToggles)) {
        if (static_cast<CCBool*>(specialToggle->getUserObject("toggled"_spr))->getValue() != IconRandomizer::random(0, 1))
            (specialToggle->m_pListener->*specialToggle->m_pfnSelector)(specialToggle);
    }

    for (auto colorToggle : CCArrayExt<CCMenuItemSpriteExtra*>(m_colorToggles)) {
        if (static_cast<CCBool*>(colorToggle->getUserObject("toggled"_spr))->getValue() != IconRandomizer::random(0, 1))
            (colorToggle->m_pListener->*colorToggle->m_pfnSelector)(colorToggle);
    }
}

void BIRSelectPopup::randomize() {
    std::vector<IconType> enabledTypes;
    std::map<IconType, bool> moreIconsTypes;

    for (int i = 0; i < m_iconToggles->count(); i++) {
        auto toggle = static_cast<CCNode*>(m_iconToggles->objectAtIndex(i));
        auto iconType = (IconType)i;
        if (static_cast<CCBool*>(toggle->getUserObject("toggled"_spr))->getValue()) {
            enabledTypes.push_back(iconType);
            auto num = IconRandomizer::randomize(IconRandomizer::fromIconType(iconType), m_dual);
            if (num > 0) m_garageLayer->m_iconPages[iconType] = (num - 1) / 36;
            else moreIconsTypes[iconType] = true;
        }
    }

    auto specialToggles = reinterpret_cast<CCNode**>(m_specialToggles->data->arr);
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

    auto colorToggles = reinterpret_cast<CCNode**>(m_colorToggles->data->arr);

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

    m_garageLayer->selectTab(selectedType);
    if (auto moreIconsNav = m_garageLayer->getChildByID(MORE_ICONS_EXPAND("navdot-menu"))) {
        IconInfo* customIconInfo;

        if (moreIconsTypes[randomType]) {
            customIconInfo = MoreIcons::getIcon(MoreIcons::activeIcon(randomType, m_dual), randomType);
            if (customIconInfo) MoreIcons::updateSimplePlayer(simplePlayer, customIconInfo->name, randomType);
        }

        if (moreIconsTypes[selectedType]) {
            if (randomType != selectedType) customIconInfo = MoreIcons::getIcon(MoreIcons::activeIcon(selectedType, m_dual), selectedType);

            auto customIcons = MoreIcons::getIcons(selectedType);
            if (auto it = std::ranges::find(customIcons, customIconInfo); it != customIcons.end()) {
                if (auto navDot = static_cast<CCMenuItem*>(moreIconsNav->getChildren()->objectAtIndex((it - customIcons.begin()) / 36)))
                    (navDot->m_pListener->*navDot->m_pfnSelector)(navDot);
            }
        }
    }

    if (!moreIconsTypes[selectedType] && !enabledTypes.empty() && !specialEnabled && !deathEnabled) {
        if (auto pageButton = static_cast<CCMenuItem*>(m_garageLayer->m_pageButtons->objectAtIndex((m_garageLayer->m_iconID - 1) / 36)))
            (pageButton->m_pListener->*pageButton->m_pfnSelector)(pageButton);
    }

    onClose(nullptr);
}

BIRSelectPopup::~BIRSelectPopup() {
    CC_SAFE_RELEASE(m_iconToggles);
    CC_SAFE_RELEASE(m_specialToggles);
    CC_SAFE_RELEASE(m_colorToggles);
}
