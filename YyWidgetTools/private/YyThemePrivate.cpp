#include "YyThemePrivate.h"

YyThemePrivate::YyThemePrivate(QObject* parent)
    : QObject{parent}
{
}

YyThemePrivate::~YyThemePrivate()
{
}

void YyThemePrivate::_initThemeColor()
{
    //YyScrollBar
    _lightThemeColorList[YyThemeType::ScrollBarHandle] = QColor(0xA0, 0xA0, 0xA0);
    _darkThemeColorList[YyThemeType::ScrollBarHandle] = QColor(0x9F, 0x9F, 0x9F);

    //YyToggleSwitch
    _lightThemeColorList[YyThemeType::ToggleSwitchNoToggledCenter] = QColor(0x5A, 0x5A, 0x5A);
    _darkThemeColorList[YyThemeType::ToggleSwitchNoToggledCenter] = QColor(0xD0, 0xD0, 0xD0);

    // 主题颜色
    _lightThemeColorList[YyThemeType::PrimaryNormal] = QColor(0x00, 0x67, 0xC0);
    _darkThemeColorList[YyThemeType::PrimaryNormal] = QColor(0x4C, 0xC2, 0xFF);
    _lightThemeColorList[YyThemeType::PrimaryHover] = QColor(0x19, 0x75, 0xC5);
    _darkThemeColorList[YyThemeType::PrimaryHover] = QColor(0x47, 0xB1, 0xE8);
    _lightThemeColorList[YyThemeType::PrimaryPress] = QColor(0x31, 0x83, 0xCA);
    _darkThemeColorList[YyThemeType::PrimaryPress] = QColor(0x42, 0xA1, 0xD2);

    // 通用颜色
    // 普通窗体
    _lightThemeColorList[YyThemeType::WindowBase] = QColor(0xF3, 0xF3, 0xF3);
    _darkThemeColorList[YyThemeType::WindowBase] = QColor(0x20, 0x20, 0x20);
    _lightThemeColorList[YyThemeType::WindowCentralStackBase] = QColor(0xFF, 0xFF, 0xFF, 80);
    _darkThemeColorList[YyThemeType::WindowCentralStackBase] = QColor(0x3E, 0x3E, 0x3E, 60);

    // 浮动窗体
    _lightThemeColorList[YyThemeType::PopupBorder] = QColor(0xD6, 0xD6, 0xD6);
    _darkThemeColorList[YyThemeType::PopupBorder] = QColor(0x47, 0x47, 0x47);
    _lightThemeColorList[YyThemeType::PopupBorderHover] = QColor(0xCC, 0xCC, 0xCC);
    _darkThemeColorList[YyThemeType::PopupBorderHover] = QColor(0x54, 0x54, 0x54);
    _lightThemeColorList[YyThemeType::PopupBase] = QColor(0xFA, 0xFA, 0xFA);
    _darkThemeColorList[YyThemeType::PopupBase] = QColor(0x2C, 0x2C, 0x2C);
    _lightThemeColorList[YyThemeType::PopupHover] = QColor(0xF0, 0xF0, 0xF0);
    _darkThemeColorList[YyThemeType::PopupHover] = QColor(0x38, 0x38, 0x38);

    // Dialog窗体
    _lightThemeColorList[YyThemeType::DialogBase] = Qt::white;
    _darkThemeColorList[YyThemeType::DialogBase] = QColor(0x1F, 0x1F, 0x1F);
    _lightThemeColorList[YyThemeType::DialogLayoutArea] = QColor(0xF3, 0xF3, 0xF3);
    _darkThemeColorList[YyThemeType::DialogLayoutArea] = QColor(0x20, 0x20, 0x20);

    // 基础颜色
    _lightThemeColorList[YyThemeType::BasicText] = Qt::black;
    _darkThemeColorList[YyThemeType::BasicText] = Qt::white;
    _lightThemeColorList[YyThemeType::BasicTextInvert] = Qt::white;
    _darkThemeColorList[YyThemeType::BasicTextInvert] = Qt::black;
    _lightThemeColorList[YyThemeType::BasicDetailsText] = QColor(0x87, 0x87, 0x87);
    _darkThemeColorList[YyThemeType::BasicDetailsText] = QColor(0xAD, 0xAD, 0xB0);
    _lightThemeColorList[YyThemeType::BasicTextNoFocus] = QColor(0x86, 0x86, 0x8A);
    _darkThemeColorList[YyThemeType::BasicTextNoFocus] = QColor(0x86, 0x86, 0x8A);
    _lightThemeColorList[YyThemeType::BasicTextDisable] = QColor(0xB6, 0xB6, 0xB6);
    _darkThemeColorList[YyThemeType::BasicTextDisable] = QColor(0xA7, 0xA7, 0xA7);
    _lightThemeColorList[YyThemeType::BasicTextPress] = QColor(0x5A, 0x5A, 0x5D);
    _darkThemeColorList[YyThemeType::BasicTextPress] = QColor(0xBB, 0xBB, 0xBF);
    _lightThemeColorList[YyThemeType::BasicTextCategory] = QColor(0x5C, 0x5C, 0x5F);
    _darkThemeColorList[YyThemeType::BasicTextCategory] = QColor(0xCC, 0xCC, 0xCE);
    _lightThemeColorList[YyThemeType::BasicBorder] = QColor(0xE5, 0xE5, 0xE5);
    _darkThemeColorList[YyThemeType::BasicBorder] = QColor(0x4B, 0x4B, 0x4B);
    _lightThemeColorList[YyThemeType::BasicBorderDeep] = QColor(0xA8, 0xA8, 0xA8);
    _darkThemeColorList[YyThemeType::BasicBorderDeep] = QColor(0x5C, 0x5C, 0x5C);
    _lightThemeColorList[YyThemeType::BasicBorderHover] = QColor(0xDA, 0xDA, 0xDA);
    _darkThemeColorList[YyThemeType::BasicBorderHover] = QColor(0x57, 0x57, 0x57);
    _lightThemeColorList[YyThemeType::BasicBase] = QColor(0xFD, 0xFD, 0xFD);
    _darkThemeColorList[YyThemeType::BasicBase] = QColor(0x34, 0x34, 0x34);
    _lightThemeColorList[YyThemeType::BasicBaseDeep] = QColor(0xE6, 0xE6, 0xE6);
    _darkThemeColorList[YyThemeType::BasicBaseDeep] = QColor(0x61, 0x61, 0x61);
    _lightThemeColorList[YyThemeType::BasicDisable] = QColor(0xF5, 0xF5, 0xF5);
    _darkThemeColorList[YyThemeType::BasicDisable] = QColor(0x2A, 0x2A, 0x2A);
    _lightThemeColorList[YyThemeType::BasicHover] = QColor(0xF3, 0xF3, 0xF3);
    _darkThemeColorList[YyThemeType::BasicHover] = QColor(0x40, 0x40, 0x40);
    _lightThemeColorList[YyThemeType::BasicPress] = QColor(0xF7, 0xF7, 0xF7);
    _darkThemeColorList[YyThemeType::BasicPress] = QColor(0x3A, 0x3A, 0x3A);
    _lightThemeColorList[YyThemeType::BasicSelectedHover] = QColor(0xEB, 0xEB, 0xEB);
    _darkThemeColorList[YyThemeType::BasicSelectedHover] = QColor(0x38, 0x38, 0x38);
    _lightThemeColorList[YyThemeType::BasicBaseLine] = QColor(0xD1, 0xD1, 0xD1);
    _darkThemeColorList[YyThemeType::BasicBaseLine] = QColor(0x45, 0x45, 0x45);
    _lightThemeColorList[YyThemeType::BasicHemline] = QColor(0x86, 0x86, 0x86);
    _darkThemeColorList[YyThemeType::BasicHemline] = QColor(0x9A, 0x9A, 0x9A);
    _lightThemeColorList[YyThemeType::BasicIndicator] = QColor(0x75, 0x7C, 0x87);
    _darkThemeColorList[YyThemeType::BasicIndicator] = QColor(0x75, 0x7C, 0x87);
    _lightThemeColorList[YyThemeType::BasicChute] = QColor(0xB3, 0xB3, 0xB3);
    _darkThemeColorList[YyThemeType::BasicChute] = QColor(0x63, 0x63, 0x63);

    // 基础透明
    _lightThemeColorList[YyThemeType::BasicAlternating] = QColor(0xEF, 0xEF, 0xEF, 160);
    _darkThemeColorList[YyThemeType::BasicAlternating] = QColor(0x45, 0x45, 0x45, 125);
    _lightThemeColorList[YyThemeType::BasicBaseAlpha] = QColor(0xFF, 0xFF, 0xFF, 160);
    _darkThemeColorList[YyThemeType::BasicBaseAlpha] = QColor(0x2D, 0x2D, 0x2D, 95);
    _lightThemeColorList[YyThemeType::BasicBaseDeepAlpha] = QColor(0xCC, 0xCC, 0xCC, 160);
    _darkThemeColorList[YyThemeType::BasicBaseDeepAlpha] = QColor(0x72, 0x72, 0x72, 95);
    _lightThemeColorList[YyThemeType::BasicHoverAlpha] = QColor(0xCC, 0xCC, 0xCC, 70);
    _darkThemeColorList[YyThemeType::BasicHoverAlpha] = QColor(0x4B, 0x4B, 0x4B, 75);
    _lightThemeColorList[YyThemeType::BasicPressAlpha] = QColor(0xCC, 0xCC, 0xCC, 40);
    _darkThemeColorList[YyThemeType::BasicPressAlpha] = QColor(0x4B, 0x4B, 0x4B, 55);
    _lightThemeColorList[YyThemeType::BasicSelectedAlpha] = QColor(0xCC, 0xCC, 0xCC, 70);
    _darkThemeColorList[YyThemeType::BasicSelectedAlpha] = QColor(0x4B, 0x4B, 0x4B, 75);
    _lightThemeColorList[YyThemeType::BasicSelectedHoverAlpha] = QColor(0xCC, 0xCC, 0xCC, 40);
    _darkThemeColorList[YyThemeType::BasicSelectedHoverAlpha] = QColor(0x4B, 0x4B, 0x4B, 55);

    // 状态颜色
    _lightThemeColorList[YyThemeType::StatusDanger] = QColor(0xE8, 0x11, 0x23);
    _darkThemeColorList[YyThemeType::StatusDanger] = QColor(0xE8, 0x11, 0x23);

    // Win10顶部边框颜色
    _lightThemeColorList[YyThemeType::Win10BorderActive] = QColor(0x6E, 0x6E, 0x6E);
    _darkThemeColorList[YyThemeType::Win10BorderActive] = QColor(0x33, 0x33, 0x33);
    _lightThemeColorList[YyThemeType::Win10BorderInactive] = QColor(0xA7, 0xA7, 0xA7);
    _darkThemeColorList[YyThemeType::Win10BorderInactive] = QColor(0x3D, 0x3D, 0x3D);
}
