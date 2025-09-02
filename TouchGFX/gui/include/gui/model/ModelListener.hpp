#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }
    
    virtual void update_indicator_color(int led_index, int r, int g, int b) {}
    virtual void confirm_selected_led(int idx, int prev) {}
    virtual void updateTimeIndex(int timeIndex) {}
    virtual void updateSliders(int r, int g, int b) {}
    virtual void showLedsErasedMessage() {}
    virtual void showLedsUpdatedMessage() {}
    virtual void hideAllMessages() {}
    virtual void transitionToScreen1() {}
    virtual void updateInitTextAlpha(uint8_t alpha) {}
    
protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
