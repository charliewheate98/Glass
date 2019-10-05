#include "EditorApplication.h"

#pragma warning(disable:4251)

int main(int argc, char** argv)
{
	// Allocate the editor app on the STACK 
	// [faster then allocating on HELP]
	EditorApplication editor_app("Glass Editor");

	// Begin the main loop for the editor app
	editor_app.MainLoop();

	// Return success
	return EXIT_SUCCESS;
}
