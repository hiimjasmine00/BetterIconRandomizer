#include <Geode/ui/Popup.hpp>

class BIRSelectPopup : public geode::Popup<GJGarageLayer*> {
protected:
    GJGarageLayer* m_garageLayer;
    cocos2d::CCArray* m_iconToggles;
    cocos2d::CCArray* m_specialToggles;
    cocos2d::CCArray* m_colorToggles;
    CCMenuItemToggler* m_allIconsToggler;
    CCMenuItemToggler* m_allSpecialsToggler;
    CCMenuItemToggler* m_allColorsToggler;
    cocos2d::CCMenu* m_iconMenu;
    cocos2d::CCMenu* m_colorMenu;
    geode::Mod* m_separateDualIcons;
    bool m_dual;

    bool setup(GJGarageLayer*) override;
    void createIconToggle(std::string_view, std::string_view, std::string_view);
    void createSpecialToggle(std::string_view, std::string_view, std::string_view);
    void createColorToggle(std::string_view, const cocos2d::ccColor3B&, std::string_view);
    void onToggle(cocos2d::CCArray*, CCMenuItemToggler*, CCMenuItemToggler*);
    void onAllToggle(cocos2d::CCArray*, CCMenuItemToggler*);
public:
    static BIRSelectPopup* create(GJGarageLayer*);

    void randomize();

    ~BIRSelectPopup() override;
};
