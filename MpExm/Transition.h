#ifndef TRANSITION_H
#define TRANSITION_H

#include "Constants.h"

class Transition{

 private:

    // Moves mitten to OPEN postion if necesary
    void openMitten();
	// Moves mitten to CLOSE postion if necesary
    void closeMitten();

	// Moves forefinger to OPEN postion if necesary
    void openForefinger();
	// Moves forefinger to CLOSE postion if necesary
    void closeForefinger();
	// Moves forefinger to TONGS postion if necesary
    void tongsForefinger();

	// Moves thumb to OPEN postion if necesary
    void openThumb();
	// Moves thumb to CLOSE postion if necesary
    void closeThumb();
	// Moves thumb to TONGS postion if necesary
    void tongsThumb();
	
  public:

	// Constructor
    Transition();
    
	// Resets state
    void reset();

	// Gets the state selected by user from input elements feedback
    int getTransitionToPerform();

	// Goes to innactive state depending on the current one
    void transitionToInactive();
	// Goes to idle state depending on the current one
    void transitionToIdle();
	// Goes to tongs state depending on the current one
    void transitionToTongs();
	// Goes to finger state depending on the current one
    void transitionToFinger();
	// Goes to close state depending on the current one
    void transitionToClose();
	// Goes to fist state depending on the current one
    void transitionToFist();

  };

#endif