/* This is the verification loader for XDash. It's a relatively new concept.
   The idea is that this loader will verify that everything initializes 
   correctly. If not, then an error code will be displayed on screen and on
   ROL. The main purpose, however, is to separate the initialization of low
   level components from the graphical dashboard which will interact with
   these from a high level.
*/

#include "VL.h"

/* GPU initialization struct. Static type, so dashboard.c 
   can use it to do rendering later on.
*/
static struct XenosDevice *xe;

void verificationLoader(){
	// Wake up all CPU cores
	xenon_make_it_faster(XENON_SPEED_FULL);

	// Start the text console
	console_init();

	// Start Xenos
	xenos_init(VIDEO_MODE_AUTO);

	// Start the network
	network_init();
	network_print_config();

	// Start USB
	usb_init();
	usb_do_poll();

	// Start SFCX and XConfig
	sfcx_init();
	if(SFCX_INITIALIZED != true){
		PRINT_ERR("!! SFCX initialization failed.\n");		
		xenon_smc_set_led(4, 2);
		BP;
	}

	xenon_config_init();

	// Initialize the GPU and EDRAM
	edram_init(xe);	
	Xe_Init(xe);

	// Initialize the background remote execution loop.
	// startREAgent();
}

