#ifndef MODEL_HPP
#define MODEL_HPP

extern "C" {
	#include "addressable_rgb_controller.h"
	#include "animation.h"
	#include "leds.h"
}

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();
    void update_led();
    void updated_slider(int color, int val);
    void UserLedSelected(int index);
    void adjustTimeSelect(int delta);
    void uploadAnimation1();
    void uploadAnimation2();  
    void uploadAnimation3();
    void uploadUserAnimation();
    void eraseAllLeds();
    void updateSliderAnimation();
    void startSliderAnimation(int r, int g, int b);
    void refreshScreen1();
    void showEraseMessage();
    void showUpdateMessage();
protected:
    ModelListener* modelListener;
};

#endif // MODEL_HPP
