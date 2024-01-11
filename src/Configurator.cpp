#include "Configurator.hpp"
#include "Game/GUI/Widgets.hpp"
#include "globals.hpp"

SFConfig globalConfig;

/// @brief Checks the Processor speed and opens a warning screen if too slow
void checkProcessor() {
	IOSOperator* o = device->getOSOperator();
	u32 ps;
	if(!o->getProcessorSpeedMHz(&ps)){
		exit(2);
	}
	if (ps < 2500) {
		SErrorWidget* w = new SErrorWidget();
		w->show(device->getGUIEnvironment(), translator::translate("Your Processor is very slow! So the game could run slow!") + "\n" + translator::translate("Your Processor Speed is: ") + std::to_string(ps) + translator::translate(" MHz"), SErrorWidget::WARN_LEVEL::SF_SEW_WARN);
	}
}