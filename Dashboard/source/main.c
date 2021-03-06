/* XDash is a graphical dashboard interface, based on the text-based
\  dashboard system of the previous XDash. The aim is to create an
\  "alternative dashboard" which is completely free and open source.
\  Code execution, file browsing, and developer features are the core
\  goals for this project.
\
\  Updated on 10-25-2012
\  Please view the readme for details on the revitalization of this
\  project.
\
\  XDash is still in early development but should be reletively bug free, if
\  there is a bug in the code however, feel free to notify me at:
\  tylerjkuck@gmail.com
\
\  Please enjoy XDash, and feel free to edit this source code as you see fit!
\  Just remember to give proper credit where credit is due.
\
\  Written by UNIX:
\  LibXenon.org
*/

// Include the respective include file
#include "main.h"

/* I previously thought threading was an efficient way
* of starting VL with the dashboard(). This seems to terribly
* break everything, however, since dashboard() requires 
* verificationLoader() to have been executed. May be why
* I gave up on XDash earlier. Overcomplication is my worst
* enemy.
*
* // Make available 100MB for thread stacks
* int stack_size = 0x6400000;
*
* // Void pointers for our thread stacks
* void *stack_1;
* void *stack_2;
* void *stack_3;
*
* // Thread integers
* int thread_1 = 1;
* int thread_2 = 2;
* int thread_3 = 3;
*
*/

int main(){
	// Execute the verificationLoader() function to load in
	// all necessary system functionality, such as xenos, 
	// console, input, etc.
	verificationLoader();

	// Run the dashboard on the condition that verificationLoader()
	// has returned status 1.
	if(verificationLoader == 1){
		dashboard();
	}

	return 0;
}

