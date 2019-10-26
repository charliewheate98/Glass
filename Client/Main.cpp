#include "EditorApplication.h"

#pragma warning(disable:4251)

int main(int argc, char** argv)
{
	Glass::Logger::Create();

	LOG_INFO("Glass Engine Initalised");

	// Allocate the editor app on the STACK 
	// [faster then allocating on HEAP]
	EditorApplication editor_app("Glass Engine");

	// Begin the main loop for the editor app
	editor_app.MainLoop();

	// Return success
	return EXIT_SUCCESS;
}
