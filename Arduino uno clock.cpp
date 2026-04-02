#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>

MCUFRIEND_kbv tft;

// Time + date
int hours = 14, minutes = 11, seconds = 50;
int day = 2, month = 4, year = 2026;

unsigned long previousMillis = 0;

// Screen size (landscape)
#define SCREEN_W 320
#define SCREEN_H 240

void setup() {
    uint16_t ID = tft.readID();
    tft.begin(ID);
    tft.setRotation(1);

    tft.fillScreen(0x0000);

    drawTime();
}

void loop() {
    updateClock();
}

// ================= CLOCK =================
void updateClock() {
    if (millis() - previousMillis >= 1000) {
        previousMillis = millis();
        seconds++;

        if (seconds >= 60) {
            seconds = 0;
            minutes++;
        }

        if (minutes >= 60) {
            minutes = 0;
            hours++;
        }

        if (hours >= 24) {
            hours = 0;
            incrementDate();
        }

        drawTime();
    }
}

// ================= DATE =================
void incrementDate() {
    day++;

    int daysInMonth;

    if (month == 2)
        daysInMonth = 28;
    else if (month == 4 || month == 6 || month == 9 || month == 11)
        daysInMonth = 30;
    else
        daysInMonth = 31;

    if (day > daysInMonth) {
        day = 1;
        month++;
    }

    if (month > 12) {
        month = 1;
        year++;
    }
}

// ================= DRAW =================
void drawTime() {
    tft.fillScreen(0x0000);

    char timeStr[10];
    sprintf(timeStr, "%02d:%02d:%02d", hours, minutes, seconds);

    char dateStr[15];
    sprintf(dateStr, "%02d/%02d/%04d", day, month, year);

    // ---------- TIME (BIG) ----------
    tft.setTextSize(4);
    tft.setTextColor(0xFFFF);

    int16_t x1, y1;
    uint16_t w, h;

    tft.getTextBounds(timeStr, 0, 0, &x1, &y1, &w, &h);

    int timeX = (SCREEN_W - w) / 2;
    int timeY = (SCREEN_H / 2) - h;

    tft.setCursor(timeX, timeY);
    tft.print(timeStr);

    // ---------- DATE (SMALLER) ----------
    tft.setTextSize(2);

    tft.getTextBounds(dateStr, 0, 0, &x1, &y1, &w, &h);

    int dateX = (SCREEN_W - w) / 2;
    int dateY = (SCREEN_H / 2) + 20;

    tft.setCursor(dateX, dateY);
    tft.print(dateStr);

    // ---------- TIMEZONE ----------
    tft.setTextSize(2);
    char tz[] = "IST";

    tft.getTextBounds(tz, 0, 0, &x1, &y1, &w, &h);

    int tzX = (SCREEN_W - w) / 2;
    int tzY = dateY + 25;

    tft.setCursor(tzX, tzY);
    tft.print(tz);
}


    








