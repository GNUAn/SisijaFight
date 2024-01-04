#include "GUI.hpp"
#include <map>
#include <string>
#include <functional>

class SErrorWidget {
public:
	enum WARN_LEVEL {
		SF_SEW_INFO, SF_SEW_WARN, SF_SEW_ERROR
	};
	enum SF_EVENT {
		SF_BUTTON_OK_PRESSED
	};
	void show(IGUIEnvironment* env, std::string text, WARN_LEVEL l);
	inline void onEvent(SF_EVENT e, std::function<void()> f) {
		pairs[e] = f;
	}
private:
	std::map < SF_EVENT, std::function<void()> > pairs;
};