#include "Aplikacia.h"

int main(void)
{
	Aplikacia* app = new Aplikacia();

	app->spusti();

	delete app;

	return 0;
}