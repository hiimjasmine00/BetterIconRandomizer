#include <Geode/loader/Types.hpp>
#include <Geode/ui/Popup.hpp>
#include <hiimjustin000.icon_randomizer_api/include/Enums.hpp>

class BIRSelectPopup : public geode::Popup {
protected:
    GJGarageLayer* m_garageLayer;
    geode::Ref<cocos2d::CCArray> m_iconToggles;
    geode::Ref<cocos2d::CCArray> m_specialToggles;
    geode::Ref<cocos2d::CCArray> m_colorToggles;
    CCMenuItemToggler* m_allIconsToggler;
    CCMenuItemToggler* m_allSpecialsToggler;
    CCMenuItemToggler* m_allColorsToggler;
    geode::Mod* m_separateDualIcons;
    bool m_dual;

    bool init(GJGarageLayer*);
    void listen(cocos2d::CCMenuItem*, const std::string&);
    void updateToggles(bool, bool, bool);
    CCMenuItemToggler* createToggle(cocos2d::CCMenu*, cocos2d::CCArray*, cocos2d::CCNode*, cocos2d::CCNode*, std::string_view, RandomizeType);
    void createIconToggle(cocos2d::CCMenu*, std::string_view, std::string_view, RandomizeType);
    void createSpecialToggle(cocos2d::CCMenu*, std::string_view, std::string_view, RandomizeType);
    void createColorToggle(cocos2d::CCMenu*, const char*, std::string_view, RandomizeType);
    void createAllToggle(cocos2d::CCMenu*, cocos2d::CCNode*, const char*, std::string_view, RandomizeAllType);
public:
    static BIRSelectPopup* create(GJGarageLayer*);

    void randomize();
    void randomizeToggles();
};
