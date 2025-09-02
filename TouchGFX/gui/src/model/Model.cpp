#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

extern "C" {
	#include "addressable_rgb_controller.h"
	#include "animation.h"
	#include "leds.h"
}

#define RED   0u
#define GREEN 1u
#define BLUE  2u

typedef struct {
	Led frames[MAX_ANIMATION_FRAMES][NUM_LEDS];
} AnimationData;

Led indicator = {.r = 255, .g = 0, .b=0};
int selected_led_ix = 0;
int time_select_counter = 0;

AnimationData current_animation;

// Slider animation variables
static bool isAnimatingSliders = false;
static int sliderAnimationCounter = 0;
static int animationSteps = 5;
static int currentRedValue = 255, currentGreenValue = 0, currentBlueValue = 0;  
static int displayedRedValue = 255, displayedGreenValue = 0, displayedBlueValue = 0;  
static int targetRedValue = 0, targetGreenValue = 0, targetBlueValue = 0;
static float redStep = 0.0f, greenStep = 0.0f, blueStep = 0.0f;

// Message timer variables
static bool messageDisplayed = false;
static int messageTimer = 0;
static const int MESSAGE_DISPLAY_TIME = 60; // 60 ticks = ~1 second at 60fps

// LED initialization tracking
static bool ledInitialized = false;

// Init text fading animation
static int fadeTimer = 0;
static bool fadingOut = true;
static const int FADE_SPEED = 3;
static const int MIN_ALPHA = 50;
static const int MAX_ALPHA = 255;


Model::Model() : modelListener(0)
{
	for(int frame = 0; frame < MAX_ANIMATION_FRAMES; frame++) {
		for(int led = 0; led < NUM_LEDS; led++) {
			current_animation.frames[frame][led].r = 255;
			current_animation.frames[frame][led].g = 0;
			current_animation.frames[frame][led].b = 0;
		}
	}
}

void Model::tick()
{
	// Check for LED initialization completion
	if(!ledInitialized) {
		uint8_t complete;
		osStatus status = osMessageQueueGet(LedInitHandle, &complete, NULL, 0U);
		if(status == osOK && complete == 1) {
			ledInitialized = true;
			if(modelListener) {
				modelListener->transitionToScreen1();
			}
		}
		
		// Animate init text while waiting for LED initialization
		fadeTimer += FADE_SPEED;
		
		uint8_t alpha;
		if(fadingOut) {
			alpha = MAX_ALPHA - (fadeTimer * (MAX_ALPHA - MIN_ALPHA) / 100);
			if(alpha <= MIN_ALPHA) {
				alpha = MIN_ALPHA;
				fadingOut = false;
				fadeTimer = 0;
			}
		} else {
			alpha = MIN_ALPHA + (fadeTimer * (MAX_ALPHA - MIN_ALPHA) / 100);
			if(alpha >= MAX_ALPHA) {
				alpha = MAX_ALPHA;
				fadingOut = true;
				fadeTimer = 0;
			}
		}
		
		if(modelListener) {
			modelListener->updateInitTextAlpha(alpha);
		}
	}
	
	updateSliderAnimation();
	
	// Auto-hide status messages after 1 second
	if(messageDisplayed) {
		messageTimer++;
		if(messageTimer >= MESSAGE_DISPLAY_TIME) {
			messageDisplayed = false;
			messageTimer = 0;
			if(modelListener) {
				modelListener->hideAllMessages();
			}
		}
	}
}


void Model::update_led(){
	Animation* animation = TestAnimation1();
	osMessageQueuePut(animationQueueHandle, &animation, 0U, 0U);
}

void Model::updated_slider(int color, int val){
	switch(color){
		case RED: indicator.r = val; break;
		case GREEN: indicator.g = val; break;
		case BLUE: indicator.b = val; break;
		default: break;
	}
	
	if(time_select_counter >= 0 && time_select_counter < MAX_ANIMATION_FRAMES &&
	   selected_led_ix >= 0 && selected_led_ix < NUM_LEDS) {
		current_animation.frames[time_select_counter][selected_led_ix] = indicator;
	}
	
	modelListener->update_indicator_color(selected_led_ix, indicator.r, indicator.g, indicator.b);
}


void Model::UserLedSelected(int index){
	int prev_selected = selected_led_ix;
	selected_led_ix = index;

	modelListener->confirm_selected_led(index, prev_selected);
	
	if(selected_led_ix >= 0 && selected_led_ix < NUM_LEDS) {
		Led led_color = current_animation.frames[time_select_counter][selected_led_ix];
		indicator = led_color;
		startSliderAnimation(led_color.r, led_color.g, led_color.b);
	}
}

void Model::adjustTimeSelect(int delta){
	int prev_selected = selected_led_ix;
	time_select_counter += delta;
	
	if(time_select_counter < 0){
		time_select_counter = 0;
	}
	else if(time_select_counter >= MAX_ANIMATION_FRAMES){
		time_select_counter = MAX_ANIMATION_FRAMES - 1;
	}
	
	selected_led_ix = 0;
	
	for(int led = 0; led < NUM_LEDS; led++) {
		Led* frameColor = &current_animation.frames[time_select_counter][led];
		modelListener->update_indicator_color(led, frameColor->r, frameColor->g, frameColor->b);
	}
	
	if(time_select_counter >= 0 && time_select_counter < MAX_ANIMATION_FRAMES &&
	   selected_led_ix >= 0 && selected_led_ix < NUM_LEDS) {
		indicator = current_animation.frames[time_select_counter][selected_led_ix];
		
		modelListener->confirm_selected_led(selected_led_ix, prev_selected);
		
		Led led_color = current_animation.frames[time_select_counter][selected_led_ix];
		startSliderAnimation(led_color.r, led_color.g, led_color.b);
	}
	
	modelListener->updateTimeIndex(time_select_counter);
}

void Model::eraseAllLeds() {
	// Clear all animation frames
	for(int frame = 0; frame < MAX_ANIMATION_FRAMES; frame++) {
		for(int led = 0; led < NUM_LEDS; led++) {
			current_animation.frames[frame][led].r = 0;
			current_animation.frames[frame][led].g = 0;
			current_animation.frames[frame][led].b = 0;
		}
	}
	
	indicator.r = 0;
	indicator.g = 0;
	indicator.b = 0;
	
	for(int led = 0; led < NUM_LEDS; led++) {
		modelListener->update_indicator_color(led, 0, 0, 0);
	}
	
	startSliderAnimation(0, 0, 0);
	showEraseMessage();
}

// When you change screens
void Model::refreshScreen1() {
	for(int led = 0; led < NUM_LEDS; led++) {
		Led* frameColor = &current_animation.frames[time_select_counter][led];
		modelListener->update_indicator_color(led, frameColor->r, frameColor->g, frameColor->b);
	}
	
	modelListener->confirm_selected_led(selected_led_ix, -1);  
	modelListener->updateTimeIndex(time_select_counter);
	
	if(selected_led_ix >= 0 && selected_led_ix < NUM_LEDS && 
	   time_select_counter >= 0 && time_select_counter < MAX_ANIMATION_FRAMES) {
		Led led_color = current_animation.frames[time_select_counter][selected_led_ix];
		indicator = led_color;
		
		displayedRedValue = led_color.r;
		displayedGreenValue = led_color.g;
		displayedBlueValue = led_color.b;
		
		modelListener->updateSliders(led_color.r, led_color.g, led_color.b);
	}
}

void Model::showEraseMessage() {
	if(modelListener) {
		modelListener->hideAllMessages();
	}
	
	messageDisplayed = true;
	messageTimer = 0;
	if(modelListener) {
		modelListener->showLedsErasedMessage();
	}
}

void Model::showUpdateMessage() {
	if(modelListener) {
		modelListener->hideAllMessages();
	}
	
	messageDisplayed = true;
	messageTimer = 0;
	if(modelListener) {
		modelListener->showLedsUpdatedMessage();
	}
}

void Model::uploadAnimation1(){
	Animation* animation = TestAnimation1();
	osMessageQueuePut(animationQueueHandle, &animation, 0U, 0U);
}

void Model::uploadAnimation2(){
	Animation* animation = TestAnimation2();
	osMessageQueuePut(animationQueueHandle, &animation, 0U, 0U);
	
	showUpdateMessage();
}

void Model::uploadAnimation3(){
	Animation* animation = TestAnimation3();
	osMessageQueuePut(animationQueueHandle, &animation, 0U, 0U);
	
	showUpdateMessage();
}

void Model::uploadUserAnimation(){
	Led *frames_buffer = (Led*)pvPortMalloc(MAX_ANIMATION_FRAMES * NUM_LEDS * sizeof(Led));
	if(frames_buffer) {
		for(int frame = 0; frame < MAX_ANIMATION_FRAMES; frame++) {
			for(int led = 0; led < NUM_LEDS; led++) {
				frames_buffer[frame * NUM_LEDS + led] = current_animation.frames[frame][led];
			}
		}
		
		Animation* animation = Animation_Create(5, NUM_LEDS, MAX_ANIMATION_FRAMES, 1, frames_buffer, 1);
		if(animation) {
			osMessageQueuePut(animationQueueHandle, &animation, 0U, 0U);
			showUpdateMessage();
		} else {
			vPortFree(frames_buffer);
		}
	}
}

void Model::updateSliderAnimation() {
	if(isAnimatingSliders && modelListener) {
		sliderAnimationCounter++;
		
		// Calculate interpolated values
		currentRedValue += (int)redStep;
		currentGreenValue += (int)greenStep;
		currentBlueValue += (int)blueStep;
		
		if(currentRedValue < 0) currentRedValue = 0;
		if(currentRedValue > 255) currentRedValue = 255;
		if(currentGreenValue < 0) currentGreenValue = 0;
		if(currentGreenValue > 255) currentGreenValue = 255;
		if(currentBlueValue < 0) currentBlueValue = 0;
		if(currentBlueValue > 255) currentBlueValue = 255;
		
		displayedRedValue = currentRedValue;
		displayedGreenValue = currentGreenValue;
		displayedBlueValue = currentBlueValue;
		
		modelListener->updateSliders(currentRedValue, currentGreenValue, currentBlueValue);
		
		if(sliderAnimationCounter >= animationSteps) {
			displayedRedValue = targetRedValue;
			displayedGreenValue = targetGreenValue;
			displayedBlueValue = targetBlueValue;
			modelListener->updateSliders(targetRedValue, targetGreenValue, targetBlueValue);
			isAnimatingSliders = false;
		}
	}
}

void Model::startSliderAnimation(int r, int g, int b) {
	targetRedValue = r;
	targetGreenValue = g;
	targetBlueValue = b;
	
	if(!isAnimatingSliders) {
		currentRedValue = displayedRedValue;
		currentGreenValue = displayedGreenValue;
		currentBlueValue = displayedBlueValue;
	}
	
	sliderAnimationCounter = 0;
	isAnimatingSliders = true;
	
	// Calculate animation steps (5 frames for 80ms transition)
	animationSteps = 5;
	
	redStep = (float)(targetRedValue - currentRedValue) / animationSteps;
	greenStep = (float)(targetGreenValue - currentGreenValue) / animationSteps;
	blueStep = (float)(targetBlueValue - currentBlueValue) / animationSteps;
}


