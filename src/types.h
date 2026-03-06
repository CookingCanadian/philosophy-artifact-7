#pragma once

// the five confucian virtues — these are used everywhere
enum Virtue {
    REN  = 0,  // benevolence / compassion
    YI   = 1,  // righteousness / duty
    LI   = 2,  // propriety / order
    ZHI  = 3,  // wisdom / discernment
    XIN  = 4,  // trustworthiness / integrity
    VIRTUE_COUNT = 5
};

// full display names for the glossary tooltip etc
static const char* VIRTUE_NAMES[VIRTUE_COUNT] = {
    "\xe4\xbb\x81 Ren  - Benevolence",
    "\xe7\xbe\xa9 Yi   - Righteousness",
    "\xe7\xa6\xae Li   - Propriety",
    "\xe6\x99\xba Zhi  - Wisdom",
    "\xe4\xbf\xa1 Xin  - Trustworthiness"
};

// short labels for the ui
static const char* VIRTUE_SHORT[VIRTUE_COUNT] = {
    "Ren", "Yi", "Li", "Zhi", "Xin"
};

// a single question the scholar can ask — probes one virtue
struct Question {
    const char* text;   // what the player sees
    Virtue      tests;  // which virtue we're poking at
};

// one dilemma — the ruler tells a story, player picks a question, ruler replies
struct Dilemma {
    const char* setup;         // the ruler's story
    Question    questions[3];  // player picks one of these
    const char* replies[3];    // ruler's reply, indexed to whichever question was picked
    Virtue      revealed[3];   // what virtue each reply actually shows (might not match what was tested)
};

// a ruler — has a name, hidden scores, and three dilemmas to go through
struct Ruler {
    const char* name;
    const char* title;
    const char* epithet;              // one-liner that hints at their character
    int         scores[VIRTUE_COUNT]; // hidden 0-10, player never sees these directly
    Dilemma     dilemmas[3];
};

// all the scenes in the game
enum class Scene {
    MENU,
    INSTRUCTIONS,
    INTERVIEW,
    VERDICT,
    ENDING
};

// everything we need to know about what's happening right now
struct GameState {
    Scene   scene           = Scene::MENU;
    int     rulerIndex      = 0;    // which ruler we're talking to (0=wei, 1=shu, 2=min)
    int     dilemmaIndex    = 0;    // which of the 3 dilemmas we're on
    int     questionChosen  = -1;   // which question the player picked (-1 = hasn't yet)
    bool    dilemmaAnswered = false;

    // tracks which rulers the player has finished interviewing
    bool    interviewed[3]  = { false, false, false };

    // who the player chose to serve at the end (-1 = not decided yet)
    int     chosenRuler     = -1;

    // which ruler is currently highlighted on the verdict screen (-1 = none)
    int     verdictSelection = -1;

    // running tally of what virtues each ruler's replies have revealed
    // indexed [ruler][virtue], goes up by 1 each time a reply shows that virtue
    int     impressions[3][VIRTUE_COUNT] = {};
};