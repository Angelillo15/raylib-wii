#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "gccore.h"
#include "stdio.h"
#include <ogc/system.h>
// #include <wiiuse/wpad.h>
#include <gl.h>
#include <rlgl.h>

static void *xfb = NULL;
static GXRModeObj *rmode = NULL;
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
	// Initialise the video system
	VIDEO_Init();

	// This function initialises the attached controllers
	// WPAD_Init();

	// Obtain the preferred video mode from the system
	// This will correspond to the settings in the Wii menu
	rmode = VIDEO_GetPreferredMode(NULL);

	// Allocate memory for the display in the uncached region
	xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));

	// Initialise the console, required for printf
	console_init(xfb, 20, 20, rmode->fbWidth, rmode->xfbHeight, rmode->fbWidth * VI_DISPLAY_PIX_SZ);

	// Set up the video registers with the chosen mode
	VIDEO_Configure(rmode);

	// Tell the video hardware where our display memory is
	VIDEO_SetNextFramebuffer(xfb);

	// Make the display visible
	VIDEO_SetBlack(false);

	// Flush the video register changes to the hardware
	VIDEO_Flush();

	// Wait for Video setup to complete
	VIDEO_WaitVSync();
	if (rmode->viTVMode & VI_NON_INTERLACE)
		VIDEO_WaitVSync();

	// The console understands VT terminal escape codes
	// This positions the cursor on row 2, column 0
	// we can use variables for this with format codes too
	// e.g. printf ("\x1b[%d;%dH", row, column );
	printf("\x1b[2;0H");

	printf("Hello, Wii! Debugging with DevkitPro and Dolphin.\n");

	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60); // Set our game to run at 60 frames-per-second
	// //--------------------------------------------------------------------------------------

	// Main game loop
	while (1) // Detect window close button or ESC key
	{

		// Call WPAD_ScanPads each loop, this reads the latest controller states
		// WPAD_ScanPads();

		// WPAD_ButtonsDown tells us which buttons were pressed in this loop
		// this is a "one shot" state which will not fire again until the button has been released
		// u32 pressed = WPAD_ButtonsDown(0);

		// We return to the launcher application via exit
		// if (pressed & WPAD_BUTTON_HOME)
		//	exit(0);

		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();
		ClearBackground(RAYWHITE);
		// glClearColor(255, 255, 255, 255);
		// rlClearColor(245, 245, 245, 255);   // Set clear color
    // // rlClearScreenBuffers();            
		// glClear(GL_COLOR_BUFFER_BIT); 

		DrawText("Redactado zampa pollas", 190, 200, 20, LIGHTGRAY);

		EndDrawing();

		// Wait for the next frame
		VIDEO_WaitVSync();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow(); // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}