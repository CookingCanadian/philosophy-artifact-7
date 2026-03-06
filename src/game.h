#pragma once
#include "types.h"
#include "data.h"

// the three possible endings — determined by which ruler the player picks
enum class Ending {
    GOLDEN_AGE,    // chose shu — balanced, warm, the good ending
    IRON_DYNASTY,  // chose wei — ordered but cold, bittersweet
    SHADOW_THRONE, // chose min — cunning and untrustworthy, bad ending
};

// titles and scroll text for each ending
static const char* ENDING_TITLES[] = {
    "The Mandate Fulfilled",
    "The Dynasty of Frost",
    "The Throne of Smoke"
};

static const char* ENDING_SCROLLS[] = {
    // shu — golden age
    "You knelt before Shu Wenlan and offered your seal of service.\n\n"
    "He governed for thirty-one years. The river provinces tripled "
    "their harvests. Former bandits became village headmen. "
    "Three famines were averted by granary systems he built in peacetime.\n\n"
    "He died in his sixty-eighth year, in the room where he was born.\n"
    "The people mourned for forty days.\n\n"
    "The Mandate of Heaven was fulfilled.",

    // wei — iron dynasty
    "You knelt before Wei Zhongda and offered your seal of service.\n\n"
    "He governed for nineteen years. The roads were straight, "
    "the laws exact, the granaries always full.\n\n"
    "No one stole. No one dared.\n\n"
    "His son inherited a realm of perfect order and no warmth. "
    "Within a decade, the provinces that had been governed "
    "found governors of their own.\n\n"
    "The dynasty was efficient. The people feared the dawn.",

    // min — betrayal ending
    "You knelt before Min Baoshi and offered your seal of service.\n\n"
    "He was a brilliant administrator. For six years, you watched "
    "him build alliances by making promises he kept precisely "
    "long enough to no longer need the people he had made them to.\n\n"
    "In the seventh year, he broke an agreement with his oldest "
    "general. The general had three legions.\n\n"
    "You were not surprised. You had read the signs.\n"
    "You had simply chosen not to act on what you knew.\n\n"
    "The realm descended into chaos. That, too, was a choice."
};

// the main game class — owns state and handles all transitions
class Game {
public:
    GameState state;

    void reset() {
        state = GameState{};
    }

    // player picked one of the three questions (0-2)
    void selectQuestion(int questionIndex) {
        if (state.dilemmaAnswered) return;
        state.questionChosen  = questionIndex;
        state.dilemmaAnswered = true;

        // record which virtue this reply revealed for this ruler
        const Ruler*   ruler   = ALL_RULERS[state.rulerIndex];
        const Dilemma& dilemma = ruler->dilemmas[state.dilemmaIndex];
        Virtue         v       = dilemma.revealed[questionIndex];
        state.impressions[state.rulerIndex][v]++;
    }

    // move to next dilemma, or mark ruler as done and go to verdict
    void advanceDilemma() {
        state.dilemmaIndex++;
        state.questionChosen  = -1;
        state.dilemmaAnswered = false;

        if (state.dilemmaIndex >= 3) {
            state.interviewed[state.rulerIndex] = true;
            state.dilemmaIndex = 0;
            // find next uninterviewed ruler
            int next = -1;
            for (int i = 0; i < 3; i++) {
                if (!state.interviewed[i]) { next = i; break; }
            }
            if (next >= 0) {
                // auto-advance to next ruler
                state.rulerIndex      = next;
                state.questionChosen  = -1;
                state.dilemmaAnswered = false;
                state.scene           = Scene::INTERVIEW;
            } else {
                // all interviewed — go to verdict
                state.verdictSelection = -1;
                state.scene = Scene::VERDICT;
            }
        }
    }

    // player made their final choice — only works if all 3 interviewed
    void chooseRuler(int rulerIndex) {
        if (!allInterviewed()) return;
        state.chosenRuler = rulerIndex;
        state.scene       = Scene::ENDING;
    }

    // start interviewing a specific ruler
    void beginInterview(int rulerIndex) {
        state.rulerIndex      = rulerIndex;
        state.dilemmaIndex    = 0;
        state.questionChosen  = -1;
        state.dilemmaAnswered = false;
        state.scene           = Scene::INTERVIEW;
    }

    // go to instructions screen
    void goInstructions() {
        state.scene = Scene::INSTRUCTIONS;
    }

    // have all three been interviewed?
    bool allInterviewed() const {
        return state.interviewed[0] && state.interviewed[1] && state.interviewed[2];
    }

    // figure out which ending we get based on who was chosen
    Ending getEnding() const {
        switch (state.chosenRuler) {
            case 0: return Ending::IRON_DYNASTY;
            case 1: return Ending::GOLDEN_AGE;
            case 2: return Ending::SHADOW_THRONE;
            default: return Ending::GOLDEN_AGE;
        }
    }

    // handy accessors so you don't have to dig through state everywhere
    const Ruler*   currentRuler()   const { return ALL_RULERS[state.rulerIndex]; }
    const Dilemma* currentDilemma() const { return &ALL_RULERS[state.rulerIndex]->dilemmas[state.dilemmaIndex]; }
    const char*    currentReply()   const {
        if (state.questionChosen < 0) return nullptr;
        return currentDilemma()->replies[state.questionChosen];
    }
};