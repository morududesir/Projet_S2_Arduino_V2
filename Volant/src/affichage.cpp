#include "affichage.h"
U8G2_SSD1309_128X64_NONAME0_F_4W_HW_SPI u8g2(
  U8G2_R0,
  47,   // CS
  48,   // DC
  49    // RESET
);
int pinRpm = 10;

// ── Layout ─────────────────────────────
// Gauche  : x=0..30   (31px) → Gear
// Sep.    : x=31
// Centre  : x=32..95  (64px) → Vitesse
// Sep.    : x=96
// Droite  : x=97..127 (31px) → Gas/Tire vertical
// ───────────────────────────────────────

void setupOLED() {
    u8g2.begin();
    u8g2.clearBuffer();
    pinMode(pinRpm, OUTPUT);
}

void afficherData(float rpm, float maxRpm, int gear, float fuel, float tireWear, float speed, bool inPit) {

    int pwm = map(rpm, 0, maxRpm, 0, 70);
    pwm = constrain(pwm, 0, 70);
    analogWrite(pinRpm, pwm);

    char buf[8];
    u8g2.clearBuffer();

    // ════════════════════════════════
    // GAUCHE : Gear (x=0..30)
    // ════════════════════════════════
    u8g2.setFont(u8g2_font_4x6_tr);
    u8g2.drawStr(7, 10, "GEAR");

    itoa(gear, buf, 10);
    u8g2.setFont(u8g2_font_inb33_mn);
    int wGear = u8g2.getStrWidth(buf);
    u8g2.drawStr((31 - wGear) / 2, 52, buf);

    // ── Séparateur gauche ──
    u8g2.drawVLine(32, 0, 64);

    // ════════════════════════════════
    // CENTRE : Vitesse (x=33..95)
    // ════════════════════════════════
    itoa((int)speed, buf, 10);
    u8g2.setFont(u8g2_font_logisoso32_tn);
    int w1 = u8g2.getStrWidth(buf);
    u8g2.drawStr(33 + (63 - w1) / 2, 50, buf);

    u8g2.setFont(u8g2_font_6x12_tr);
    int w2 = u8g2.getStrWidth("KM/H");
    u8g2.drawStr(33 + (63 - w2) / 2, 63, "KM/H");

    // ── Séparateur droit ──
    u8g2.drawVLine(96, 0, 64);

    // ════════════════════════════════
    // DROITE : Gas + Tire verticaux
    // ════════════════════════════════
    const int barH = 44;
    const int barW = 12;
    const int barY = 8;
    const int gasX  = 99;
    const int tireX = 115;

    // Barre GAS
    u8g2.drawFrame(gasX, barY, barW, barH);
    int gasH = map((int)fuel, 0, 100, 0, barH - 2);
    if (gasH > 0)
        u8g2.drawBox(gasX + 1, barY + 1 + (barH - 2 - gasH), barW - 2, gasH);

    // Barre TIRE
    u8g2.drawFrame(tireX, barY, barW, barH);
    int tireH = map((int)tireWear, 0, 100, 0, barH - 2);
    if (tireH > 0)
        u8g2.drawBox(tireX + 1, barY + 1 + (barH - 2 - tireH), barW - 2, tireH);

    // Labels sous les barres
    u8g2.setFont(u8g2_font_4x6_tr);
    u8g2.drawStr(gasX,      58, "GAS");
    u8g2.drawStr(tireX - 2, 58, "TIRE");

    u8g2.sendBuffer();
}