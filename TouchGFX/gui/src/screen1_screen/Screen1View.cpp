#include <gui/screen1_screen/Screen1View.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>

extern "C" {
	#include "addressable_rgb_controller.h"
}

#define RED   0u
#define GREEN 1u
#define BLUE  2u



Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}


void Screen1View::UpdateRed(int value){
	presenter->updated_slider(RED, value);
	
	touchgfx::Unicode::snprintf(redTextBuffer, 4, "%d", value);
	RedValueText.setWildcard1(redTextBuffer);
	
	touchgfx::colortype redColor = touchgfx::Color::getColorFromRGB(value, 0, 0);
	RedValueText.setColor(redColor);
	
	RedValueText.invalidate();
}

void Screen1View::UpdateGreen(int value){
	presenter->updated_slider(GREEN, value);
	
	touchgfx::Unicode::snprintf(greenTextBuffer, 4, "%d", value);
	GreenValueText.setWildcard1(greenTextBuffer);
	
	touchgfx::colortype greenColor = touchgfx::Color::getColorFromRGB(0, value, 0);
	GreenValueText.setColor(greenColor);
	
	GreenValueText.invalidate();
}

void Screen1View::UpdateBlue(int value){
	presenter->updated_slider(BLUE, value);
	
	touchgfx::Unicode::snprintf(blueTextBuffer, 4, "%d", value);
	BlueValueText.setWildcard1(blueTextBuffer);
	
	touchgfx::colortype blueColor = touchgfx::Color::getColorFromRGB(0, 0, value);
	BlueValueText.setColor(blueColor);
	
	BlueValueText.invalidate();
}

void Screen1View::update_indicator_color(int led_index, int r, int g, int b){
	touchgfx::colortype color = touchgfx::Color::getColorFromRGB(r, g, b);
	
	switch(led_index){
		case 0:
			LedIndicator_0Painter.setColor(color);
			LedIndicator_0.setPainter(LedIndicator_0Painter);
			LedIndicator_0.invalidate();
			break;
		case 1:
			LedIndicator_1Painter.setColor(color);
			LedIndicator_1.setPainter(LedIndicator_1Painter);
			LedIndicator_1.invalidate();
			break;
		case 2:
			LedIndicator_2Painter.setColor(color);
			LedIndicator_2.setPainter(LedIndicator_2Painter);
			LedIndicator_2.invalidate();
			break;
		case 3:
			LedIndicator_3Painter.setColor(color);
			LedIndicator_3.setPainter(LedIndicator_3Painter);
			LedIndicator_3.invalidate();
			break;
		case 4:
			LedIndicator_4Painter.setColor(color);
			LedIndicator_4.setPainter(LedIndicator_4Painter);
			LedIndicator_4.invalidate();
			break;
		case 5:
			LedIndicator_5Painter.setColor(color);
			LedIndicator_5.setPainter(LedIndicator_5Painter);
			LedIndicator_5.invalidate();
			break;
		case 6:
			LedIndicator_6Painter.setColor(color);
			LedIndicator_6.setPainter(LedIndicator_6Painter);
			LedIndicator_6.invalidate();
			break;
		case 7:
			LedIndicator_7Painter.setColor(color);
			LedIndicator_7.setPainter(LedIndicator_7Painter);
			LedIndicator_7.invalidate();
			break;
		default:
			break;
	}
}


void Screen1View::ButtonLed0(){
	presenter->UserLedSelected(0);
}
void Screen1View::ButtonLed1(){
	presenter->UserLedSelected(1);
}
void Screen1View::ButtonLed2(){
	presenter->UserLedSelected(2);
}
void Screen1View::ButtonLed3(){
	presenter->UserLedSelected(3);
}
void Screen1View::ButtonLed4(){
	presenter->UserLedSelected(4);
}
void Screen1View::ButtonLed5(){
	presenter->UserLedSelected(5);
}
void Screen1View::ButtonLed6(){
	presenter->UserLedSelected(6);
}
void Screen1View::ButtonLed7(){
	presenter->UserLedSelected(7);
}

void Screen1View::confirm_selected_led(int idx, int prev){
	// Make previous selected LED invisible
	switch(prev){
		case 0: selectedLed_0.setVisible(false); selectedLed_0.invalidate(); break;
		case 1: selectedLed_1.setVisible(false); selectedLed_1.invalidate(); break;
		case 2: selectedLed_2.setVisible(false); selectedLed_2.invalidate(); break;
		case 3: selectedLed_3.setVisible(false); selectedLed_3.invalidate(); break;
		case 4: selectedLed_4.setVisible(false); selectedLed_4.invalidate(); break;
		case 5: selectedLed_5.setVisible(false); selectedLed_5.invalidate(); break;
		case 6: selectedLed_6.setVisible(false); selectedLed_6.invalidate(); break;
		case 7: selectedLed_7.setVisible(false); selectedLed_7.invalidate(); break;
		default: break;
	}
	
	// Make current selected LED visible
	switch(idx){
		case 0: selectedLed_0.setVisible(true); selectedLed_0.invalidate(); break;
		case 1: selectedLed_1.setVisible(true); selectedLed_1.invalidate(); break;
		case 2: selectedLed_2.setVisible(true); selectedLed_2.invalidate(); break;
		case 3: selectedLed_3.setVisible(true); selectedLed_3.invalidate(); break;
		case 4: selectedLed_4.setVisible(true); selectedLed_4.invalidate(); break;
		case 5: selectedLed_5.setVisible(true); selectedLed_5.invalidate(); break;
		case 6: selectedLed_6.setVisible(true); selectedLed_6.invalidate(); break;
		case 7: selectedLed_7.setVisible(true); selectedLed_7.invalidate(); break;
		default: break;
	}
}

void Screen1View::ButtonUpClick(){
	presenter->adjustTimeSelect(1);
}

void Screen1View::ButtonDownClick(){
	presenter->adjustTimeSelect(-1);
}

void Screen1View::updateTimeIndex(int counter){
	Unicode::snprintf(TimeCounterLabelBuffer, TIMECOUNTERLABEL_SIZE, "%u", counter);
	TimeCounterLabel.invalidate();
	
	int progressValue = counter;
	TimeProgressBar.setValue(progressValue);
	TimeProgressBar.invalidate();
}

void Screen1View::updateSliders(int r, int g, int b){
	SliderRed.setValue(r);
	SliderGreen.setValue(g);
	SliderBlue.setValue(b);
	
	SliderRed.invalidate();
	SliderGreen.invalidate();
	SliderBlue.invalidate();
	
	touchgfx::Unicode::snprintf(redTextBuffer, 4, "%d", r);
	touchgfx::Unicode::snprintf(greenTextBuffer, 4, "%d", g);
	touchgfx::Unicode::snprintf(blueTextBuffer, 4, "%d", b);
	
	RedValueText.setWildcard1(redTextBuffer);
	RedValueText.setColor(touchgfx::Color::getColorFromRGB(r, 0, 0));
	RedValueText.invalidate();
	GreenValueText.setWildcard1(greenTextBuffer);
	GreenValueText.setColor(touchgfx::Color::getColorFromRGB(0, g, 0));
	GreenValueText.invalidate();
	BlueValueText.setWildcard1(blueTextBuffer);
	BlueValueText.setColor(touchgfx::Color::getColorFromRGB(0, 0, b));
	BlueValueText.invalidate();
	
	invalidate();
}

