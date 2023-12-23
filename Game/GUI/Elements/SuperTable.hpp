#ifndef CUSTOMTABLE_H
#define CUSTOMTABLE_H

#include <irrlicht.h>
#include <vector>

using namespace irr;
using namespace gui;
using namespace core;
using namespace video;

class CustomTable : public IGUIElement {
public:
    CustomTable(IGUIEnvironment* env, IGUIElement* parent, s32 id, const core::rect<s32>& rectangle);
    virtual ~CustomTable();

    void addRow(const wchar_t* text, const io::path& imageFile);
    virtual void draw() override;

private:
    struct TableEntry {
        u32 imageIndex;
        core::stringw text;
    };

    IGUISpriteBank* spriteBank;
    std::vector<TableEntry> entries;
    f32 imageSize;
    IGUIScrollBar* scrollbar;  // Scrollbar für die Tabelle
    int scrollPosition;     // Aktuelle Scroll-Position
};

class GUILine : public IGUIElement
{
public:
    // Konstruktor ohne rect, fügt sich selbst zum GUI-Umfeld hinzu
    GUILine(IGUIEnvironment* env, IGUIElement* parent, s32 id);

    virtual void draw() override;

    void setLineColor(video::SColor color);
    void setLineThickness(f32 thickness);
    void setLineStartEnd(const core::position2di& start, const core::position2di& end);

private:
    video::SColor LineColor;
    f32 LineThickness;
    core::position2di LineStart;
    core::position2di LineEnd;
};

#endif // CUSTOMTABLE_H
