#include "SuperTable.h"

CustomTable::CustomTable(IGUIEnvironment* env, IGUIElement* parent, s32 id, const core::rect<s32>& rectangle)
    : IGUIElement(EGUIET_ELEMENT, env, parent, id, rectangle),
    imageSize(0.1f * env->getVideoDriver()->getScreenSize().Height),
    scrollbar(nullptr), scrollPosition(0) {
    spriteBank = env->addEmptySpriteBank("customTableSpriteBank");
    if (!parent) {
        env->getRootGUIElement()->addChild(this);
    }

    // Scrollbar hinzufügen
    scrollbar = Environment->addScrollBar(true, rect<s32>(rectangle.getWidth() - 20, 0, rectangle.getWidth(), rectangle.getHeight()), this);
    scrollbar->setMax(0); // Anfangs keine Scrollbar notwendig
}

CustomTable::~CustomTable() {
    if (spriteBank) { 
        spriteBank->drop();
    }
}

void CustomTable::addRow(const wchar_t* text, const io::path& imageFile) {
    // ... (Bild und Text hinzufügen, wie zuvor)

    // Update Scrollbar
    if (entries.size() * imageSize > AbsoluteRect.getHeight()) {
        scrollbar->setMax(entries.size() * imageSize - AbsoluteRect.getHeight());
        scrollbar->setVisible(true);
    }
}

void CustomTable::draw() {
    if (!IsVisible)
        return;

    // ... (Bilder und Text zeichnen unter Berücksichtigung der Scroll-Position)

    IGUIElement::draw();
}

GUILine::GUILine(IGUIEnvironment* env, IGUIElement* parent, s32 id)
    : IGUIElement(EGUIET_ELEMENT, env, parent, id, core::rect<s32>(0, 0, 0, 0)),
    LineColor(255,255,255,255), LineThickness(1.0f), LineStart(0, 0), LineEnd(0, 0)
{
    // Setzen der Größe auf die Größe des übergeordneten Elements, wenn vorhanden
    if (parent) {
        this->setRelativePosition(parent->getAbsolutePosition());
    }

    // Das Element zum GUI-Umfeld hinzufügen
    if (env) {
        env->getRootGUIElement()->addChild(this);
    }
}

void GUILine::draw()
{
    if (!IsVisible)
        return;

    video::IVideoDriver* driver = Environment->getVideoDriver();
    driver->setTransform(video::ETS_WORLD, core::matrix4());
    driver->draw2DLine(LineStart, LineEnd, LineColor);

    IGUIElement::draw();
}

void GUILine::setLineColor(video::SColor color)
{
    LineColor = color;
}

void GUILine::setLineThickness(f32 thickness)
{
    LineThickness = thickness;
}

void GUILine::setLineStartEnd(const core::position2di& start, const core::position2di& end)
{
    LineStart = start;
    LineEnd = end;
}
