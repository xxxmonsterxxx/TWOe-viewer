#include "widgets/ViewWidget.h"

bool ViewWidget::show()
{
	if (!_engine)
		return false;

	visible = true;
	return true;
}

void ViewWidget::hide()
{
	visible = false;
}