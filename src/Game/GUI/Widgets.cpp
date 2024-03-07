#include "Widgets.hpp"
#include "SGE/GUIENvironment.hpp"
#include "Tools/GUITools.hpp"

/// @brief Shows a Error, Warning or Info Dialog
/// @param env The Irrlicht GUI-Environment
/// @param text The Error Message
/// @param l The Waning Level use like this '..., SErrorWidget::WARN_LEVEL::...' supported levels are SF_SEW_ERROR, SF_SEW_WARNING and SF_SEW_INFO
void SErrorWidget::show(IGUIEnvironment* env, std::string text, WARN_LEVEL l)
{
	/*
	static IGUIWindow* w = env->addWindow(s_rect(30, 30, 40, 40), false, l == SF_SEW_ERROR ? translate("ERROR").c_str() : (l == SF_SEW_WARN ? translate("WARNING").c_str() : translate("INFO").c_str()));
	recti ws = s_rect(30, 30, 40, 40);
	ITexture* img = env->getVideoDriver()->getTexture(l == SF_SEW_ERROR ? "data/images/GUI/Error.png" : (l == SF_SEW_WARN ? "data/images/GUI/Warn.png" : "data/images/GUI/Info.png"));
	dimension2du size = img->getOriginalSize();
	recti ipos = recti(p(3, ws.getWidth()), p(50, ws.getHeight()) - size.Height / 2, p(3, ws.getWidth()) + size.Width, p(50, ws.getHeight()) - size.Height / 2 + size.Height);
	static IGUIImage* i = env->addImage(ipos, w);
	i->setImage(img);
	i->setScaleImage(true);
	static IGUIStaticText* tex = env->addStaticText(stringToWString(text).c_str(), recti(p(23, ws.getWidth()), p(7, ws.getHeight()), p(98, ws.getWidth()), p(98, ws.getHeight())), false, true, w);
	tex->setOverrideColor(l==SF_SEW_ERROR ? STD_RED : (l==SF_SEW_WARN ? STD_YELLOW : STD_CYAN));
	static IGUIButton* close = env->addButton(recti(p(60, ws.getWidth()), p(85, ws.getHeight()), p(99, ws.getWidth()), p(99, ws.getHeight())), w, -1, translate("OK").c_str());
	GUIEngine->addObject(w, NULL);
	GUIEngine->addObject(i, NULL);
	GUIEngine->addObject(close, [&](SEvent::SGUIEvent e){
		if(e.EventType==EGET_BUTTON_CLICKED){
		w->remove();
		w->drop();
		}
	});
	*/
}
/// @brief Shows a music widget
/// @param env The GUI-environment
/// @param name The song name
/// @param interpret The interpret name
void MusicWidget::show(GUIEnvironment *env, std::string name, std::string interpret)
{
	
}
