#pragma once
#include <string>
#include <irrlicht.h>
#include "../../Tools/GUITools.hpp"
#include "../../Gamemodes/Gamemodes.hpp"
#include "Elements/SuperTable.hpp"

using namespace irr;

class GUIPage {
public:
	 virtual void draw(GUIEnvironment* dev)=0;
	 inline virtual bool isFinished() {
		 return finished;
	 };
	 inline virtual void onFinish(std::function<void()> f) {
		 end = f;
	 }
protected:
	std::function<void()> end;
	bool finished = false;
	inline virtual void finish() {
		finished = true;
		end();
	}
};
class GUIClass {
public:
	 virtual void draw(GUIEnvironment* env)=0;
};

/// @brief A complex Widget similar to GUIPage but needn't delete the background. (A window)
class GUIWidget {
public:
	virtual void draw(GUIEnvironment* env)=0;
};
