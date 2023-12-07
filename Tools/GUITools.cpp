#include "GUITools.h"

// Returns the percent-value of a float
float p(float v, float p) {
    return (v / 100) * p;
}

// Returns the percent-value of an integer
int p(int v, int p) {
    return (v * p) / 100;
}

irr::core::recti s_rect(int pX, int pY, int pW, int pH) {
    return irr::core::recti(p(screenSize.Width, pX), p(screenSize.Height, pY), p(screenSize.Width, pX) + p(screenSize.Width, pW), p(screenSize.Height, pY) + p(screenSize.Height, pH));
}

struct Color {
    double r; // Rot
    double g; // Grün
    double b; // Blau
    double a; // Alpha

    Color(double r, double g, double b, double a)
        : r(r), g(g), b(b), a(a) {}
};

// Funktion zur Umwandlung von HSV zu RGB
Color HSVtoRGB(double h, double s, double v, double a) {
    double r, g, b;

    int i = std::floor(h * 6);
    double f = h * 6 - i;
    double p = v * (1 - s);
    double q = v * (1 - f * s);
    double t = v * (1 - (1 - f) * s);

    switch (i % 6) {
    case 0: r = v, g = t, b = p; break;
    case 1: r = q, g = v, b = p; break;
    case 2: r = p, g = v, b = t; break;
    case 3: r = p, g = q, b = v; break;
    case 4: r = t, g = p, b = v; break;
    case 5: r = v, g = p, b = q; break;
    }

    return Color(r * 255, g * 255, b * 255, a);
}

std::wstring stringToWString(const std::string& str) {
    return std::wstring(str.begin(), str.end());
}

// Funktion, die bei jedem Aufruf eine neue Farbe zurückgibt
SColor getNewColor() {
    static double t = 0.0;

    // Erzeugen Sie eine Farbe im HSV-Farbraum und konvertieren Sie sie in RGB
    Color color = HSVtoRGB(t, 1.0, 1.0, 255.0);

    // Aktualisieren Sie t für den nächsten Aufruf
    t += 0.00003;
    if (t > 1.0) {
        t = 0.0;
    }

    return SColor(color.a, color.r, color.g, color.b);
}