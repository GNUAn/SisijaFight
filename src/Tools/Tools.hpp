#pragma once
#include <random>
#include <imgui.h>
#include <irrlicht.h>

inline float map(float val, float min, float max, float newmin, float newmax) {
    // Prüfe zuerst, ob der ursprüngliche Bereich 0 ist, um Division durch Null zu vermeiden
    if (min == max) {
        return newmin;
    }
    // Berechne, wie weit (in Prozent) der val-Wert in seinem ursprünglichen Bereich liegt
    float scale = (val - min) / (max - min);
    // Wende diesen Prozentsatz auf den neuen Bereich an und gebe das Ergebnis zurück
    return newmin + scale * (newmax - newmin);
}

inline long modulateFloatAt16Bit(float num){
    long scaledFloatPart = static_cast<long>(num * 1000);
    scaledFloatPart &= 0xFFFF;
    return scaledFloatPart;
}

inline float demodulateFloatAt16Bit(long cv){
    long extractedScaledFloatPart = cv & 0xFFFF;
    return extractedScaledFloatPart / 1000.0f;
}

inline float random(float from, float to) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution(from, to);
    return distribution(gen);
}

inline int random(int from, int to) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(from, to);
    return distribution(gen);
}

inline ImVec4 sc2imv4(irr::video::SColor c) {
	return ImVec4(c.getRed(), c.getGreen(), c.getBlue(), c.getAlpha());
}

// Basic stuff
inline ImVec2 ivec22imvec2(irr::core::recti size) {
	return ImVec2(size.LowerRightCorner.X - size.UpperLeftCorner.X, size.LowerRightCorner.Y - size.UpperLeftCorner.Y);
}
inline ImVec2 ivec22imvec2(irr::core::dimension2du size) {
	return ImVec2(size.Width, size.Height);
}
inline ImVec2 ivec2Pos2imvec2(irr::core::recti size) {
	return ImVec2(size.UpperLeftCorner.X, size.UpperLeftCorner.Y);
}

#define i2imp(args) ivec2Pos2imvec2(args)
#define i2im(args) ivec22imvec2(args)