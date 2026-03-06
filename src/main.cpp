#include "raylib.h"
#include "raymath.h"
#include "assets.h" 

static const int CANVAS_W = 320;
static const int CANVAS_H = 180;

int main(void) {
    SetTraceLogLevel(LOG_INFO);
    InitWindow(0, 0, "The Golden Rule");

    int monitorW = GetMonitorWidth(GetCurrentMonitor());
    int monitorH = GetMonitorHeight(GetCurrentMonitor());

    SetWindowSize(monitorW, monitorH);
    SetWindowPosition(0, 0);
    SetWindowState(FLAG_WINDOW_UNDECORATED);
    SetTargetFPS(60);

    RenderTexture2D canvas = LoadRenderTexture(CANVAS_W, CANVAS_H);
    SetTextureFilter(canvas.texture, TEXTURE_FILTER_POINT); 

    Shader crt = LoadShaderFromMemory(nullptr, (const char*)crt_frag); // crt shader to make assets look better
    int resLoc  = GetShaderLocation(crt, "resolution");
    int timeLoc = GetShaderLocation(crt, "time");

    float res[2] = { (float)monitorW, (float)monitorH };
    SetShaderValue(crt, resLoc, res, SHADER_UNIFORM_VEC2);

    float scaleX = (float)monitorW / CANVAS_W;
    float scaleY = (float)monitorH / CANVAS_H;
    float scale  = (scaleX < scaleY) ? scaleX : scaleY; // uniform fit
    int destW = (int)(CANVAS_W * scale);
    int destH = (int)(CANVAS_H * scale);
    int destX = (monitorW - destW) / 2;
    int destY = (monitorH - destH) / 2;

    Rectangle srcRect  = { 0, 0, (float)CANVAS_W, -(float)CANVAS_H }; // flip Y
    Rectangle destRect = { (float)destX, (float)destY, (float)destW, (float)destH };

    while (!WindowShouldClose()) {
        float t = (float)GetTime();
        SetShaderValue(crt, timeLoc, &t, SHADER_UNIFORM_FLOAT);

        BeginTextureMode(canvas);
            ClearBackground({ 10, 8, 20, 255 }); 

            const char* label = "THE GOLDEN RULE";
            DrawText(label,
                CANVAS_W/2 - MeasureText(label, 10)/2,
                CANVAS_H/2 - 5,
                10, { 220, 190, 120, 255 });

            const char* sub = "Three rulers. Five virtues. One question.";
            DrawText(sub,
                CANVAS_W/2 - MeasureText(sub, 5)/2,
                CANVAS_H/2 + 10,
                5, { 140, 120, 80, 180 });

        EndTextureMode();

        BeginDrawing();
            ClearBackground(BLACK);
            BeginShaderMode(crt);
                DrawTexturePro(canvas.texture, srcRect, destRect, { 0, 0 }, 0.0f, WHITE);
            EndShaderMode();
        EndDrawing();
    }

    UnloadRenderTexture(canvas);
    UnloadShader(crt);
    CloseWindow();
    return 0;
}