#ifndef SCREEN1PRESENTER_HPP
#define SCREEN1PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

extern "C" {
	#include "addressable_rgb_controller.h"
	#include "animation.h"
	#include "leds.h"
}

using namespace touchgfx;

class Screen1View;

class Screen1Presenter : public touchgfx::Presenter, public ModelListener
{
public:
    Screen1Presenter(Screen1View& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~Screen1Presenter() {}

    virtual void gui_led_updated();
    virtual void updated_slider(int color, int val);

    virtual void update_indicator_color(int led_index, int r, int g, int b);

    virtual void UserLedSelected(int index);

    virtual void confirm_selected_led(int idx, int prev);

    virtual void adjustTimeSelect(int delta);
    
    virtual void updateTimeIndex(int timeIndex);
    
    virtual void updateSliders(int r, int g, int b);
    
    virtual void uploadAnimation1();
    virtual void uploadAnimation2();
    virtual void uploadAnimation3();
    virtual void uploadUserAnimation();
    virtual void refreshScreen1();

private:
    Screen1Presenter();

    Screen1View& view;
};

#endif // SCREEN1PRESENTER_HPP
