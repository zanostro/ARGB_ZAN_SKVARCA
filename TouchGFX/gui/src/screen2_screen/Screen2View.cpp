#include <gui/screen2_screen/Screen2View.hpp>

Screen2View::Screen2View()
{

}

void Screen2View::setupScreen()
{
    Screen2ViewBase::setupScreen();
}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();
}

void Screen2View::UploadPrebuild1(){
	presenter->uploadAnimation1();
}

void Screen2View::UploadPrebuild2(){
	presenter->uploadAnimation2();
}

void Screen2View::UploadPrebuild3(){
	presenter->uploadAnimation3();
}

void Screen2View::UploadAnimationFun(){
	presenter->uploadUserAnimation();
}

void Screen2View::EraseAll(){
	presenter->eraseAllLeds();
}

void Screen2View::showLedsErasedMessage(){
	LedsClearedMsg.setVisible(true);
	LedsClearedMsg.invalidate();
}

void Screen2View::showLedsUpdatedMessage(){
	LedsUpdatedMsg.setVisible(true);
	LedsUpdatedMsg.invalidate();
}

void Screen2View::hideAllMessages(){
	LedsClearedMsg.setVisible(false);
	LedsUpdatedMsg.setVisible(false);
	LedsClearedMsg.invalidate();
	LedsUpdatedMsg.invalidate();
}
