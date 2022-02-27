#include "TwoeViewer.h"

int main()
{
	TwoeViewer& app = TwoeViewer::get();

	if (!app.init())
		return 0;

	app.execute();

	app.deinit();

	return 1;
}