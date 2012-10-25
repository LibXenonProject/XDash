/* This is the main menu source file. The main menu will be
   rendered and displayed here. In addition, input will also
   be handled here. This source file doesn't contain any
   of the functions to interact with low level components
   (such as SFCX). Instead, it will call these functions
   from different source files upon user demand.

   This way, everything will be nice and separated.
   We can have many small modules of code instead of
   throwing everything into main.c This should increase
   code efficiency, as well as editability and update 
   ability in the future.
*/

/* TODO: Decide whether to use Xenos directly or use libPNG
   For now this is unclear to me, so I will leave libPNG
   included.

  Using Xenos directly seems to be the better way.
*/

#include "dashboard.h"

// Globals
int pngExists = false;	// Used in dashboard() and checkPNGExists()
// TODO: Add PNG image file specifications. Height, width, depth, etc, etc.

// Check if PNG exists
void checkPNGExists(char *file_name){
	FILE *fp;

	// If file is not found, return error 
	if((fp = fopen(file_name, "rb")) == NULL){
		printf("!! ERROR: Opening file\n");
		exit(-1);
	}
	else{
		pngExists = true;
	}
}

// Display the PNG image from USB
void displayPNG(){
	/* Here we will interact with the already initialized 
	   GPU, courtesy of VL. Since VL has already done the
	   hard work for us, we can just directly interface
	   Xenos using xe.h, we get to skip all of the init()
	   stuff. All we have to do it tell Xenos what to do.
	*/
	printf("That's enough coding for tonight. :)\n");
	exit(-1);
}

void getInput(){
	// Create a controller handler.
	struct controller_data_s controller;

	// Loop conditions for button actions.
	while(1){

		// Create a button handler.
		struct controller_data_s button;

 		if (get_controller_data(&button, 0))
 		{
			// Execute functions based on controller input.
			if((button.start)&&(!controller.start))
			{
				clearScreen();
				reDash();
			}
			if((button.x)&&(!controller.x))
			{
				printTemperatures();
			}
			if((button.y)&&(!controller.y))
			{
				clearScreen();
			}
			if((button.b)&&(!controller.b))
			{
				clearScreen();
				shutdownConsole();
			}											  
			controller=button;
		}
 		usb_do_poll();
 	}
}

void dashboard(){
	// File name and FILE type for the main dashboard pngFile
	char *fileName = "uda:/dashboard.png";

	// Read the PNG file
	checkPNGExists(fileName);

	// If the PNG file exists, execute the input loop.
	if(pngExists == true){
		// Display dashboard image.
		displayPNG();
		
		// Run the getInput(); loop.
		getInput();

	}

	// If PNG does not exist, print errors.
	else if(pngExists == false){
		// Print errors to the console.
		PRINT_ERR("!! Unable to find PNG file on USB.\n");
		PRINT_ERR("?? Check if file exists, and reboot.\n");

		// Exit condition.
		exit(-2);
	}
}

