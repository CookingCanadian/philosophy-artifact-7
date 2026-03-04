#include "raylib.h"

int main(void) {
    SetTraceLogLevel(LOG_INFO);

    InitWindow(0, 0, "Artifact 7");

    int w = GetMonitorWidth(GetCurrentMonitor());
    int h = GetMonitorHeight(GetCurrentMonitor());
    
    const char* exText = "testing; press esc to close the window";

    SetWindowSize(w, h);
    SetWindowPosition(0, 0);
    SetWindowState(FLAG_WINDOW_UNDECORATED);

    //SetTargetFPS(60);

    while (!WindowShouldClose()) {
        int fps = GetFPS();

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText(exText, w/2 - MeasureText(exText, 60)/2, h/2, 60, LIGHTGRAY);
            DrawText(TextFormat("running program at %d FPS", fps), 20, 30, 40, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}