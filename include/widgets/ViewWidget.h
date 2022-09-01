#include <SGE/SGE.h>

class ViewWidget {

public:
	void init(SGE* engine) { _engine = engine; }
	virtual void update() = 0;
	bool show();
	void hide();

protected:
	std::string name = "Widget";
	bool visible = false;
	SGE* _engine = nullptr;

};