#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <touchgfx/Unicode.hpp>

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void UpdateRed(int value);
    virtual void UpdateGreen(int value);
    virtual void UpdateBlue(int value);

    virtual void ButtonLed0();
    virtual void ButtonLed1();
    virtual void ButtonLed2();
    virtual void ButtonLed3();
    virtual void ButtonLed4();
    virtual void ButtonLed5();
    virtual void ButtonLed6();
    virtual void ButtonLed7();
    virtual void confirm_selected_led(int idx, int prev);
    virtual void ButtonUpClick();
    virtual void ButtonDownClick();
    virtual void update_indicator_color(int led_index, int r, int g, int b);
    virtual void updateTimeIndex(int counter);
    virtual void updateSliders(int r, int g, int b);
protected:
    touchgfx::Unicode::UnicodeChar redTextBuffer[4];
    touchgfx::Unicode::UnicodeChar greenTextBuffer[4];
    touchgfx::Unicode::UnicodeChar blueTextBuffer[4];
};

#endif // SCREEN1VIEW_HPP
