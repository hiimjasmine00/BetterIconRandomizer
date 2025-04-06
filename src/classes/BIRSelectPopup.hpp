#include <Geode/ui/Popup.hpp>

class BIRSelectPopup : public geode::Popup<GJGarageLayer*> {
protected:
    #ifndef GEODE_IS_IOS
    inline static constexpr std::array keybindIDs = {
        GEODE_MOD_ID "/select-color-1",
        GEODE_MOD_ID "/select-color-2",
        GEODE_MOD_ID "/select-color-glow",
        GEODE_MOD_ID "/select-glow",
        GEODE_MOD_ID "/select-cube",
        GEODE_MOD_ID "/select-ship",
        GEODE_MOD_ID "/select-ball",
        GEODE_MOD_ID "/select-ufo",
        GEODE_MOD_ID "/select-wave",
        GEODE_MOD_ID "/select-robot",
        GEODE_MOD_ID "/select-spider",
        GEODE_MOD_ID "/select-swing",
        GEODE_MOD_ID "/select-jetpack",
        GEODE_MOD_ID "/select-death",
        GEODE_MOD_ID "/select-trail",
        GEODE_MOD_ID "/select-ship-fire",
        GEODE_MOD_ID "/select-animation",
        GEODE_MOD_ID "/select-explode"
    };
    #endif

    GJGarageLayer* m_garageLayer;
    cocos2d::CCArray* m_iconToggles;
    cocos2d::CCArray* m_specialToggles;
    cocos2d::CCArray* m_colorToggles;
    CCMenuItemToggler* m_allIconsToggler;
    CCMenuItemToggler* m_allSpecialsToggler;
    CCMenuItemToggler* m_allColorsToggler;
    geode::Mod* m_separateDualIcons;
    bool m_dual;

    bool setup(GJGarageLayer*) override;
    CCMenuItemSpriteExtra* createIconToggle(cocos2d::CCMenu*, std::string_view, std::string_view, int);
    CCMenuItemSpriteExtra* createSpecialToggle(cocos2d::CCMenu*, std::string_view, int);
    CCMenuItemSpriteExtra* createColorToggle(cocos2d::CCMenu*, std::string_view, const cocos2d::ccColor3B&, int);
public:
    static BIRSelectPopup* create(GJGarageLayer*);

    void randomize();
    void randomizeToggles();

    ~BIRSelectPopup() override;
};
