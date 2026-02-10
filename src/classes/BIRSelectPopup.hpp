#include <Geode/loader/Types.hpp>
#include <Geode/ui/Popup.hpp>
#include <hiimjustin000.icon_randomizer_api/include/Enums.hpp>

class BIRSelectPopup : public geode::Popup {
protected:
    GJGarageLayer* m_garageLayer;
    std::array<std::vector<CCMenuItemToggler*>, 3> m_toggles;
    std::array<CCMenuItemToggler*, 3> m_allTogglers;
    geode::Mod* m_separateDualIcons;
    bool m_dual;

    bool init(GJGarageLayer*, cocos2d::CCSpriteFrame*);
    void listen(cocos2d::CCMenuItem*, const std::string&);
    void updateToggles(bool, bool, bool);
    CCMenuItemToggler* createToggle(
        cocos2d::CCMenu*, std::vector<CCMenuItemToggler*>&, cocos2d::CCNode*, cocos2d::CCNode*, std::string_view, RandomizeType
    );
    void onToggle(cocos2d::CCObject*);
    void createIconToggle(cocos2d::CCMenu*, std::string_view, std::string_view, RandomizeType);
    void createSpecialToggle(cocos2d::CCMenu*, std::string_view, std::string_view, RandomizeType);
    void createColorToggle(cocos2d::CCMenu*, const char*, std::string_view, RandomizeType);
    void createAllToggle(cocos2d::CCMenu*, cocos2d::CCNode*, const char*, std::string_view, RandomizeAllType);
    void onAllToggle(cocos2d::CCObject*);
    void onRandomize(cocos2d::CCObject*);
    void onRandomizeToggles(cocos2d::CCObject*);
public:
    static BIRSelectPopup* create(GJGarageLayer*, cocos2d::CCSpriteFrame*);
};
