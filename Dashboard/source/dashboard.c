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

// Display the PNG image from USB
void displayPNG(){
	/* Here we will interact with the already initialized 
	   GPU, courtesy of VL. Since VL has already done the
	   hard work for us, we can just directly interface
	   Xenos using xe.h, we get to skip all of the init()
	   stuff. All we have to do it tell Xenos what to do.
	*/
	printf("Coming soon!\n");
	exit(-6);
}

// Create the data structures for the Dashboard PNG file.
// Taken from piko3d.com, adapted for standard C
int setupPNG(char *filename){
	// Validate the PNG file we are using is true.
	if (!validate(filename)) {
    		printf("!! Structure does not contain valid PNG data!");
		exit(-3);
	}

	// Create a data structure for the PNG to be read into.
	png_structp pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!pngPtr) {
   		printf("!! Could not initialize PNG data structure!");
    		exit(-4);
	}

	// Create a data structure for the PNG info to be read into.
	// If this fails, clean up all PNG data and exit.
	png_infop infoPtr = png_create_info_struct(pngPtr);
	if (!infoPtr) {
		printf("!! Could not initialize PNG data structure! Cleaning up...");
    		png_destroy_read_struct(&pngPtr, (png_infopp)0, (png_infopp)0);
    		exit(-5);
	}

	return 1;
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
	char fileName = "uda:/dashboard.png";

	// Validate and setup the PNG image in uda:/
	setupPNG(fileName);

	// If the PNG file exists, execute the input loop.
	if(setupPNG == 1){
		// Display dashboard image.
		displayPNG();
		
		// Run the getInput(); loop.
		getInput();
	}

	// If PNG does not exist, print errors.
	else if(setupPNG == NULL){
		// Print errors to the console.
		PRINT_ERR("!! Unable to find PNG file on USB.\n");
		PRINT_ERR("?? Check if file exists, and reboot.\n");

		// Exit condition.
		exit(-2);
	}
}

