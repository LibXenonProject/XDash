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

#include "dashboard.h"

// Set an image as the default Xenos texture to render.
// I have no idea if this even makes sense.
void XeRenderImage(FILE *file){
	// Create a data structure for the surface.
	struct XenosSurface *Image;
	struct XenosDevice *xe;

	// Seek the size of the file.
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	fseek(file, 0, SEEK_SET);

	// Copy the image to memory.
	void *imageAddress = malloc(size);
	fread(imageAddress, 1, size, file);

	// Copy the memory contents to surface data structure.
	memcpy(Image, &imageAddress, size);

	// Set the texture to render.
	Xe_SetTexture(xe, XE_FMT_BGRA, Image);

	// Render and resolve.
	Xe_SetRenderTarget(xe, Image);
	Xe_Resolve(xe);
}

/*
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
*/

void dashboard(){	
	// Setup a file type for the default dashboard file.
	FILE *defaultImage;
	char defaultImageName = "uda:/dashboard.bgra";		

	defaultImage = fopen(defaultImageName, "rb");

	// Loop the display of the image and input handling.
	while(1){
		// Render the dashboard image.
		XeRenderImage(defaultImage);

		// Handle incoming controller input.
		// getInput();
	}
}

