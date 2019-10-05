#include "EditorApplication.h"

#pragma warning(disable:4251)

int main(int argc, char** argv)
{
	EditorApplication* editor_app = new EditorApplication("Glass Editor");

	editor_app->MainLoop();

	return EXIT_SUCCESS;
}
