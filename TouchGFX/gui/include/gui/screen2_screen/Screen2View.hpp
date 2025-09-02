#ifndef SCREEN2VIEW_HPP
#define SCREEN2VIEW_HPP

#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>

class Screen2View : public Screen2ViewBase
{
public:
    Screen2View();
    virtual ~Screen2View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void UploadAnimationFun();
    virtual void UploadPrebuild1();
    virtual void UploadPrebuild2();
    virtual void UploadPrebuild3();
    virtual void EraseAll();
    virtual void showLedsErasedMessage();
    virtual void showLedsUpdatedMessage();
    virtual void hideAllMessages();
protected:
};

#endif // SCREEN2VIEW_HPP
