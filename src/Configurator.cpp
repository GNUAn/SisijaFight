#include "Configurator.hpp"
#include "Game/GUI/Widgets.hpp"
#include "globals.hpp"

SFConfig globalConfig;

/// @brief Checks the Processor speed and opens a warning screen if too slow
void checkProcessor() {
	IOSOperator* o = device->getOSOperator();
	u32 ps;
	o->getProcessorSpeedMHz(&ps);
	if (ps < 6000) {
		SErrorWidget* w = new SErrorWidget();
		w->show(device->getGUIEnvironment(), translator::translate("Your Processor is very slow! So the game could run slow!"), SErrorWidget::WARN_LEVEL::SF_SEW_WARN);

	}
}