#pragma once

class GUIEnvironment;
/// @brief A complex Widget similar to GUIPage but needn't delete the background. (A window)
class GUIWidget {
public:
    inline virtual void subscribe(int id_) { id=id_; }
    virtual void draw(GUIEnvironment* e)=0;
private:
    int id;
};