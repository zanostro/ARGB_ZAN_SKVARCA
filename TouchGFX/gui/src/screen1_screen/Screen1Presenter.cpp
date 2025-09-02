#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

#define RED   0u
#define GREEN 1u
#define BLUE  2u


Screen1Presenter::Screen1Presenter(Screen1View& v)
    : view(v)
{

}

void Screen1Presenter::activate()
{
	// Refresh the screen with current model state when becoming active
	refreshScreen1();
}

void Screen1Presenter::deactivate()
{

}


void Screen1Presenter::gui_led_updated(){

	model->update_led();

}


void Screen1Presenter::updated_slider(int color, int val){
	model->updated_slider(color, val);
}

void Screen1Presenter::update_indicator_color(int led_index, int r, int g, int b){

	view.update_indicator_color(led_index, r, g, b);
}

void Screen1Presenter::UserLedSelected(int index){
	model->UserLedSelected(index);
}

void Screen1Presenter::confirm_selected_led(int idx, int prev){
	view.confirm_selected_led(idx, prev);
}

void Screen1Presenter::adjustTimeSelect(int delta){
	model->adjustTimeSelect(delta);
}

void Screen1Presenter::updateTimeIndex(int timeIndex){
	
	view.updateTimeIndex(timeIndex + 1);
}

void Screen1Presenter::updateSliders(int r, int g, int b){
	view.updateSliders(r, g, b);
}

void Screen1Presenter::uploadAnimation1(){
	model->uploadAnimation1();
}

void Screen1Presenter::uploadAnimation2(){
	model->uploadAnimation2();
}

void Screen1Presenter::uploadAnimation3(){
	model->uploadAnimation3();
}

void Screen1Presenter::uploadUserAnimation(){
	model->uploadUserAnimation();
}

void Screen1Presenter::refreshScreen1(){
	model->refreshScreen1();
}



