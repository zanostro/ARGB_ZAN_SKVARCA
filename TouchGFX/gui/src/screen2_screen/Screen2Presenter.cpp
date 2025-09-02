#include <gui/screen2_screen/Screen2View.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>

Screen2Presenter::Screen2Presenter(Screen2View& v)
    : view(v)
{

}

void Screen2Presenter::activate()
{
    // Bind this presenter to the model when Screen2 becomes active
    if (model)
    {
        model->bind(this);
    }
}

void Screen2Presenter::deactivate()
{

}

void Screen2Presenter::uploadAnimation1(){
	model->uploadAnimation1();
}

void Screen2Presenter::uploadAnimation2(){
	model->uploadAnimation2();
}

void Screen2Presenter::uploadAnimation3(){
	model->uploadAnimation3();
}

void Screen2Presenter::uploadUserAnimation(){
	model->uploadUserAnimation();
}

void Screen2Presenter::eraseAllLeds(){
	model->eraseAllLeds();
}

void Screen2Presenter::showLedsErasedMessage(){
	view.showLedsErasedMessage();
}

void Screen2Presenter::showLedsUpdatedMessage(){
	view.showLedsUpdatedMessage();
}

void Screen2Presenter::hideAllMessages(){
	view.hideAllMessages();
}
