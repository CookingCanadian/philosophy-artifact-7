#include "raylib.h"
#include "raymath.h"
#include "assets.h"
#include "game.h"
#include <cstring>
#include <cstdio>

// native render size
static const int CANVAS_W = 640;
static const int CANVAS_H = 360;

// font sizes
static const int FS_HEADING    = 20;
static const int FS_SUBHEADING = 16;
static const int FS_CONTENT    = 12;
static const int FS_SELECTION  = 10;
static const int FS_HINT       =  8;

// line spacing per font size tier
static const int FS_HEADING_LH    = FS_HEADING    + 6;
static const int FS_CONTENT_LH    = FS_CONTENT    + 6;
static const int FS_SELECTION_LH  = FS_SELECTION  + 5;

static Texture2D texWei;
static Texture2D texShu;
static Texture2D texMin;

static inline void DT(const char* text, int x, int y, int size, Color col) {
    DrawText(text, x, y, size, col);
}

static inline int MT(const char* text, int size) {
    return MeasureText(text, size);
}

Game game;

void DrawSceneMenu();
void DrawSceneInstructions();
void DrawSceneInterview();
void DrawSceneVerdict();
void DrawSceneEnding();

int DrawTextWrapped(const char* text, int x, int y, int maxWidth, int fontSize, Color col) {
    int lineH = fontSize + 6;
    int len   = (int)strlen(text);

    char line[512];
    char word[128];
    int  li = 0, wi = 0;
    int  curY = y;

    auto flushLine = [&]() {
        if (li > 0) {
            line[li] = '\0';
            DT(line, x, curY, fontSize, col);
            curY += lineH;
            li = 0;
        }
    };

    for (int i = 0; i <= len; i++) {
        char c     = text[i];
        bool flush = (c == ' ' || c == '\n' || c == '\0');

        if (flush && wi > 0) {
            word[wi] = '\0';
            char test[512];
            if (li > 0) snprintf(test, sizeof(test), "%s %s", line, word);
            else        snprintf(test, sizeof(test), "%s", word);

            if (MT(test, fontSize) > maxWidth && li > 0) {
                flushLine();
                snprintf(line, sizeof(line), "%s", word);
                li = (int)strlen(line);
            } else {
                snprintf(line, sizeof(line), "%s", test);
                li = (int)strlen(line);
            }
            wi = 0;
        }
        if (c == '\n') {
            flushLine();
        } else if (!flush) {
            if (wi < 127) word[wi++] = c;
        }
    }
    flushLine();
    return curY;
}

static Texture2D LoadEmbeddedPNG(const unsigned char* data, int len) {
    Image     img = LoadImageFromMemory(".png", data, len); // from .h
    Texture2D tex = LoadTextureFromImage(img);
    UnloadImage(img);
    return tex;
}

void DrawPortrait(Texture2D tex, int cx, int cy, int maxW, int maxH, float breathPhase) {
    float scaleX = (float)maxW / tex.width;
    float scaleY = (float)maxH / tex.height;
    float fit    = (scaleX < scaleY) ? scaleX : scaleY;
    float breathe = 1.0f + sinf((float)GetTime() * 1.2f + breathPhase) * 0.02f;
    float w = tex.width  * fit * breathe;
    float h = tex.height * fit * breathe;
    Rectangle src = { 0, 0, (float)tex.width, (float)tex.height };
    Rectangle dst = { cx - w/2.0f, cy - h/2.0f, w, h };
    DrawTexturePro(tex, src, dst, { 0, 0 }, 0.0f, WHITE);
}

Texture2D GetRulerTex(int idx) {
    switch (idx) {
        case 0: return texWei;
        case 1: return texShu;
        case 2: return texMin;
        default: return texWei;
    }
}

// ── menu ──────────────────────────────────────────────────────────────────────
void DrawSceneMenu() {
    const char* label  = "THE GOLDEN RULE";
    const char* sub    = "Three rulers. Five virtues. One question.";
    const char* prompt = "press enter to begin";

    DT(label,  CANVAS_W/2 - MT(label,  FS_HEADING)/2,  CANVAS_H/2 - 40, FS_HEADING,  { 220, 190, 120, 255 });
    DT(sub,    CANVAS_W/2 - MT(sub,    FS_CONTENT)/2,   CANVAS_H/2 - 10, FS_CONTENT,  { 180, 165, 120, 220 });

    float alpha = (sinf((float)GetTime() * 2.0f) * 0.5f + 0.5f) * 180 + 75;
    DT(prompt, CANVAS_W/2 - MT(prompt, FS_HINT)/2,      CANVAS_H/2 + 40, FS_HINT,     { 200, 180, 120, (unsigned char)alpha });

    if (IsKeyPressed(KEY_ENTER)) game.goInstructions();
}

// ── instructions ──────────────────────────────────────────────────────────────
void DrawSceneInstructions() {
    const char* title = "HOW TO PLAY";
    DT(title, CANVAS_W/2 - MT(title, FS_HEADING)/2, 12, FS_HEADING, { 220, 190, 120, 255 });
    DrawLine(16, 40, CANVAS_W - 16, 40, { 100, 80, 40, 120 });

    int tx = 32, tw = CANVAS_W - 64, y = 52;

    const char* lines[] = {
        "You are a Confucian scholar tasked with choosing a ruler that you believe in.",
        "You will interview each of the three dukes individually.",
        "Each duke will describe a past dilemma they faced.",
        "Choose a question to probe their true character.",
        "After all three interviews, you will choose one duke to serve.",
        "Judge each duke according to the Golden Rule.",
        nullptr
    };

    for (int i = 0; lines[i] != nullptr; i++) {
        DT("-", tx, y, FS_CONTENT, { 160, 140, 80, 200 });
        y = DrawTextWrapped(lines[i], tx + 16, y, tw - 16, FS_CONTENT, { 210, 195, 160, 255 });
        y += 4;
    }

    DrawLine(16, CANVAS_H - 36, CANVAS_W - 16, CANVAS_H - 36, { 100, 80, 40, 80 });
    float alpha = (sinf((float)GetTime() * 2.0f) * 0.5f + 0.5f) * 180 + 75;
    const char* prompt = "press enter to meet the first duke";
    DT(prompt, CANVAS_W/2 - MT(prompt, FS_HINT)/2, CANVAS_H - 32, FS_HINT, { 200, 180, 120, (unsigned char)alpha });

    if (IsKeyPressed(KEY_ENTER)) game.beginInterview(0);
}

// ── interview ─────────────────────────────────────────────────────────────────
void DrawSceneInterview() {
    const Ruler*   ruler   = game.currentRuler();
    const Dilemma* dilemma = game.currentDilemma();

    // portrait left column
    DrawPortrait(GetRulerTex(game.state.rulerIndex), 78, CANVAS_H/2, 120, 192, 0.0f);
    DrawLine(156, 2, 156, CANVAS_H - 2, { 80, 65, 35, 100 });

    int tx = 168, tw = CANVAS_W - tx - 8;

    DT(ruler->name, tx, 8, FS_SUBHEADING, { 220, 190, 120, 255 });

    const char* dukeLabel = TextFormat("Duke %d of 3", game.state.rulerIndex + 1);
    const char* counter   = TextFormat("Dilemma %d of 3", game.state.dilemmaIndex + 1);
    DT(dukeLabel, CANVAS_W - MT(dukeLabel, FS_HINT) - 8, 8,  FS_HINT, { 140, 120, 70, 200 });
    DT(counter,   CANVAS_W - MT(counter,   FS_HINT) - 8, 18, FS_HINT, { 140, 120, 70, 180 });
    DrawLine(tx, 32, CANVAS_W - 8, 32, { 100, 80, 40, 100 });

    if (!game.state.dilemmaAnswered) {
        int afterSetup = DrawTextWrapped(dilemma->setup, tx, 40, tw, FS_CONTENT, { 210, 195, 160, 255 });

        int qY = afterSetup + 8;
        for (int i = 0; i < 3; i++) {
            bool selected = (game.state.questionChosen == i);
            Color qcol   = selected ? Color{240,220,140,255} : Color{190,175,130,255};
            Color lblcol = selected ? Color{220,200,100,255} : Color{160,140,80,220};
            char lbl[5] = {'[', (char)('1'+i), ']', ' ', '\0'};
            DT(lbl, tx, qY, FS_SELECTION, lblcol);
            int nextY = DrawTextWrapped(dilemma->questions[i].text, tx + 28, qY, tw - 28, FS_SELECTION, qcol);
            qY = nextY + 4;
        }

        float alpha = (sinf((float)GetTime() * 2.0f) * 0.5f + 0.5f) * 150 + 105;
        const char* hint = game.state.questionChosen >= 0 ? "press enter to ask" : "press 1, 2 or 3 to select";
        DT(hint, tx, CANVAS_H - 32, FS_HINT, { 200, 180, 120, (unsigned char)alpha });

        if (IsKeyPressed(KEY_ONE))   game.state.questionChosen = 0;
        if (IsKeyPressed(KEY_TWO))   game.state.questionChosen = 1;
        if (IsKeyPressed(KEY_THREE)) game.state.questionChosen = 2;
        if (IsKeyPressed(KEY_ENTER) && game.state.questionChosen >= 0)
            game.selectQuestion(game.state.questionChosen);

    } else {
        DT("They answer:", tx, 40, FS_CONTENT, { 180, 160, 100, 255 });
        DrawTextWrapped(game.currentReply(), tx, 58, tw, FS_CONTENT, { 210, 195, 160, 255 });

        float alpha = (sinf((float)GetTime() * 2.0f) * 0.5f + 0.5f) * 180 + 75;
        bool lastDilemma = (game.state.dilemmaIndex == 2);
        bool lastDuke    = (game.state.rulerIndex == 2);
        const char* cont = (lastDilemma && lastDuke) ? "press enter to make your choice"
                         : lastDilemma               ? "press enter to meet the next duke"
                                                     : "press enter to continue";
        DT(cont, CANVAS_W/2 - MT(cont, FS_HINT)/2, CANVAS_H - 32, FS_HINT, { 200, 180, 120, (unsigned char)alpha });

        if (IsKeyPressed(KEY_ENTER)) game.advanceDilemma();
    }
}

// ── verdict ───────────────────────────────────────────────────────────────────
void DrawSceneVerdict() {
    const char* title = "WHO WILL YOU SERVE?";
    DT(title, CANVAS_W/2 - MT(title, FS_HEADING)/2, 8, FS_HEADING, { 220, 190, 120, 255 });
    DrawLine(16, 34, CANVAS_W - 16, 34, { 100, 80, 40, 100 });
    const char* sub = "You have heard all three. Now choose.";
    DT(sub, CANVAS_W/2 - MT(sub, FS_HINT)/2, 38, FS_HINT, { 170, 155, 110, 200 });

    int cardW = 188, gap = 18;
    int startX = (CANVAS_W - (cardW * 3 + gap * 2)) / 2;

    for (int i = 0; i < 3; i++) {
        const Ruler* r     = ALL_RULERS[i];
        bool         sel   = (game.state.verdictSelection == i);
        int          cx    = startX + i * (cardW + gap) + cardW / 2;
        int          cardX = startX + i * (cardW + gap);

        if (sel) {
            DrawRectangle(cardX - 2, 52, cardW + 4, CANVAS_H - 90, { 80, 65, 30, 60 });
            DrawRectangleLines(cardX - 2, 52, cardW + 4, CANVAS_H - 90, { 180, 155, 80, 160 });
        }

        Texture2D tex = GetRulerTex(i);
        float scx = 100.0f / tex.width, scy = 160.0f / tex.height;
        float fit = (scx < scy) ? scx : scy;
        float breathe = 1.0f + sinf((float)GetTime() * 1.2f + i * 1.1f) * 0.02f;
        float pw = tex.width * fit * breathe, ph = tex.height * fit * breathe;
        Rectangle src = { 0, 0, (float)tex.width, (float)tex.height };
        Rectangle dst = { cx - pw/2, 56 + (160 - ph)/2.0f, pw, ph };
        DrawTexturePro(tex, src, dst, { 0, 0 }, 0.0f, WHITE);

        Color namecol    = sel ? Color{240,215,130,255} : Color{200,180,120,220};
        Color epithetcol = sel ? Color{200,185,130,230} : Color{160,145,100,190};
        DT(TextFormat("[%d] %s", i+1, r->name), cardX, 224, FS_CONTENT, namecol);
        DrawTextWrapped(r->epithet, cardX, 242, cardW, FS_SELECTION, epithetcol);
    }

    DrawLine(8, CANVAS_H - 28, CANVAS_W - 8, CANVAS_H - 28, { 100, 80, 40, 80 });
    float alpha = (sinf((float)GetTime() * 2.0f) * 0.5f + 0.5f) * 150 + 105;
    const char* hint = game.state.verdictSelection >= 0
        ? "press enter to kneel and offer your service"
        : "press 1, 2 or 3 to select a duke";
    DT(hint, CANVAS_W/2 - MT(hint, FS_HINT)/2, CANVAS_H - 32, FS_HINT, { 200, 180, 120, (unsigned char)alpha });

    if (IsKeyPressed(KEY_ONE))   game.state.verdictSelection = 0;
    if (IsKeyPressed(KEY_TWO))   game.state.verdictSelection = 1;
    if (IsKeyPressed(KEY_THREE)) game.state.verdictSelection = 2;
    if (IsKeyPressed(KEY_ENTER) && game.state.verdictSelection >= 0)
        game.chooseRuler(game.state.verdictSelection);
}

// ── ending ────────────────────────────────────────────────────────────────────
void DrawSceneEnding() {
    Ending ending = game.getEnding();
    int    idx    = (int)ending;

    DT(ENDING_TITLES[idx], CANVAS_W/2 - MT(ENDING_TITLES[idx], FS_HEADING)/2, 12, FS_HEADING, { 220, 190, 120, 255 });
    DrawLine(16, 40, CANVAS_W - 16, 40, { 100, 80, 40, 100 });
    DrawTextWrapped(ENDING_SCROLLS[idx], 24, 52, CANVAS_W - 48, FS_CONTENT, { 210, 195, 160, 255 });

    float alpha = (sinf((float)GetTime() * 2.0f) * 0.5f + 0.5f) * 180 + 75;
    const char* restart = "press enter to return to menu";
    DT(restart, CANVAS_W/2 - MT(restart, FS_HINT)/2, CANVAS_H - 32, FS_HINT, { 200, 180, 120, (unsigned char)alpha });

    if (IsKeyPressed(KEY_ENTER)) game.reset();
}

// ── main ──────────────────────────────────────────────────────────────────────
int main(void) {
    game.reset();
    SetTraceLogLevel(LOG_INFO);
    InitWindow(0, 0, "The Golden Rule");

    int monitorW = GetMonitorWidth(GetCurrentMonitor());
    int monitorH = GetMonitorHeight(GetCurrentMonitor());

    SetWindowSize(monitorW, monitorH);
    SetWindowPosition(0, 0);
    SetWindowState(FLAG_WINDOW_UNDECORATED);
    SetTargetFPS(60);

    texWei = LoadEmbeddedPNG(wei_png, wei_png_len);
    texShu = LoadEmbeddedPNG(shu_png, shu_png_len);
    texMin = LoadEmbeddedPNG(min_png, min_png_len);

    RenderTexture2D canvas = LoadRenderTexture(CANVAS_W, CANVAS_H);
    SetTextureFilter(canvas.texture, TEXTURE_FILTER_POINT);

    Shader crt   = LoadShaderFromMemory(nullptr, (const char*)crt_frag);
    int resLoc   = GetShaderLocation(crt, "resolution");
    int timeLoc  = GetShaderLocation(crt, "time");

    float res[2] = { (float)CANVAS_W, (float)CANVAS_H };
    SetShaderValue(crt, resLoc, res, SHADER_UNIFORM_VEC2);

    float scaleX = (float)monitorW / CANVAS_W;
    float scaleY = (float)monitorH / CANVAS_H;
    float scale  = (scaleX < scaleY) ? scaleX : scaleY;
    int destW    = (int)(CANVAS_W * scale);
    int destH    = (int)(CANVAS_H * scale);
    int destX    = (monitorW - destW) / 2;
    int destY    = (monitorH - destH) / 2;

    Rectangle srcRect  = { 0, 0, (float)CANVAS_W, -(float)CANVAS_H };
    Rectangle destRect = { (float)destX, (float)destY, (float)destW, (float)destH };

    while (!WindowShouldClose()) {
        float t = (float)GetTime();
        SetShaderValue(crt, timeLoc, &t, SHADER_UNIFORM_FLOAT);

        BeginTextureMode(canvas);
            ClearBackground({ 10, 8, 20, 255 });
            switch (game.state.scene) {
                case Scene::MENU:         DrawSceneMenu();         break;
                case Scene::INSTRUCTIONS: DrawSceneInstructions(); break;
                case Scene::INTERVIEW:    DrawSceneInterview();    break;
                case Scene::VERDICT:      DrawSceneVerdict();      break;
                case Scene::ENDING:       DrawSceneEnding();       break;
            }
        EndTextureMode();

        BeginDrawing();
            ClearBackground(BLACK);
            BeginShaderMode(crt);
                DrawTexturePro(canvas.texture, srcRect, destRect, { 0, 0 }, 0.0f, WHITE);
            EndShaderMode();
        EndDrawing();
    }

    UnloadTexture(texWei);
    UnloadTexture(texShu);
    UnloadTexture(texMin);
    UnloadRenderTexture(canvas);
    UnloadShader(crt);
    CloseWindow();
    return 0;
}