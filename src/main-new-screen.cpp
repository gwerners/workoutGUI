/*******************************************************************************************
 *
 *   raylib-extras [ImGui] example - Simple Integration
 *
 *	This is a simple ImGui Integration
 *	It is done using C++ but with C style code
 *	It can be done in C as well if you use the C ImGui wrapper
 *	https://github.com/cimgui/cimgui
 *
 *   Copyright (c) 2021 Jeffery Myers
 *
 ********************************************************************************************/
#include "raylib.h"
#include "raymath.h"

#include "imgui.h"
#include "rlImGui.h"

#include <fmt/color.h>
#include <fmt/format.h>
int weekDay[] = {-1, -1, -1, -1, -1, -1, -1};
int s1 = -1;
int s2 = -1;
int s3 = -1;
int s4 = -1;
int s5 = -1;
int s6 = -1;

static bool show_app_window_convict = true;
int getWeekDay() {
  struct tm* ts;
  time_t timestamp = time(NULL);
  ts = localtime(&timestamp);
  return ts->tm_wday;
}
const char* getEName(int i) {
  switch (i) {
    case 1:
      return "Pushups";
    case 2:
      return "Squats";
    case 3:
      return "Pullups";
    case 4:
      return "LegRaises";
    case 5:
      return "Bridges";
    case 6:
      return "HandstandPushups";
    default:
      return "";
  }
}
static void ShowAppWindowConvict(bool*) {
  const ImGuiViewport* viewport = ImGui::GetMainViewport();
  const ImVec2 base_pos = viewport->Pos;
  ImGui::SetNextWindowPos(ImVec2(base_pos.x, base_pos.y),
                          ImGuiCond_FirstUseEver);
  ImGui::Begin("Training");

  static ImGuiTableFlags flags = ImGuiTableFlags_Borders |
                                 ImGuiTableFlags_RowBg |
                                 ImGuiTableFlags_SizingFixedFit;

  ImGui::Combo("Dia da Semana", &weekDay[6],
               "Domingo\0Segunda\0Terça\0Quarta\0Quinta\0Sexta\0Sabado\0\0");
  static bool selected[10] = {};
  const char* routine[] = {"Pushups",   "Squats",  "Pullups",
                           "LegRaises", "Bridges", "HandstandPushups"};
  const char* hiddenName01[] = {
      "##0", "##1", "##2", "##3", "##4", "##5",
  };
  ImGui::Columns(3);
  ImGui::SetColumnWidth(0, 100.);
  ImGui::InputInt(hiddenName01[0], &s1);
  ImGui::InputInt(hiddenName01[0], &s2);
  ImGui::InputInt(hiddenName01[0], &s3);
  ImGui::InputInt(hiddenName01[0], &s4);
  ImGui::InputInt(hiddenName01[0], &s5);
  ImGui::InputInt(hiddenName01[0], &s6);
  ImGui::NextColumn();
  ImGui::Combo(routine[0], &weekDay[0],
               "Domingo\0Segunda\0Terça\0Quarta\0Quinta\0Sexta\0Sabado\0\0");
  ImGui::Combo(routine[1], &weekDay[1],
               "Domingo\0Segunda\0Terça\0Quarta\0Quinta\0Sexta\0Sabado\0\0");
  ImGui::Combo(routine[2], &weekDay[2],
               "Domingo\0Segunda\0Terça\0Quarta\0Quinta\0Sexta\0Sabado\0\0");
  ImGui::Combo(routine[3], &weekDay[3],
               "Domingo\0Segunda\0Terça\0Quarta\0Quinta\0Sexta\0Sabado\0\0");
  ImGui::Combo(routine[4], &weekDay[4],
               "Domingo\0Segunda\0Terça\0Quarta\0Quinta\0Sexta\0Sabado\0\0");
  ImGui::Combo(routine[4], &weekDay[4],
               "Domingo\0Segunda\0Terça\0Quarta\0Quinta\0Sexta\0Sabado\0\0");
  /*
   */

  ImGui::NextColumn();
  if (ImGui::BeginTable("table1", 5, flags)) {
    ImGui::TableSetupColumn("Routine", ImGuiTableColumnFlags_WidthStretch);
    ImGui::TableSetupColumn("Serie", ImGuiTableColumnFlags_WidthStretch);
    ImGui::TableSetupColumn("<5", ImGuiTableColumnFlags_WidthStretch);
    ImGui::TableSetupColumn("6-10", ImGuiTableColumnFlags_WidthStretch);
    ImGui::TableSetupColumn("11-20", ImGuiTableColumnFlags_WidthStretch);
    ImGui::TableHeadersRow();
    for (int row = 0; row < 5; row++) {
      ImGui::TableNextRow();
      for (int column = 0; column < 5; column++) {
        ImGui::TableSetColumnIndex(column);

        char buf[32];
        switch (column) {
          case 0:
            sprintf(buf, "%s", routine[row]);
            break;
          case 1:
            sprintf(buf, "%d", 1);
            break;
          case 2:
            sprintf(buf, "%d,%d", column, row);
            break;
          case 3:
            sprintf(buf, "%d,%d", column, row);
            break;
          case 4:
            sprintf(buf, "%d,%d", column, row);
            break;
        }

        // ImGui::TextUnformatted(buf);
        if (column != 1) {
          ImGui::TextUnformatted(buf);
          // ImGui::Selectable(buf,&selected[row],ImGuiSelectableFlags_SpanAllColumns);
        }
      }
    }

    ImGui::EndTable();
  }
  ImGui::End();
}
int main(int argc, char* argv[]) {
  // Initialization
  //--------------------------------------------------------------------------------------
  int screenWidth = 1280;
  int screenHeight = 800;

  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
  InitWindow(screenWidth, screenHeight,
             "raylib-Extras [ImGui] example - simple ImGui Demo");
  SetTargetFPS(144);
  rlImGuiSetup(true);

  InitAudioDevice();  // Initialize audio device

  Sound fxWav = LoadSound(
      "./raylib/examples/audio/resources/sound.wav");  // Load WAV audio file
  Sound fxOgg = LoadSound(
      "./raylib/examples/audio/resources/target.ogg");  // Load OGG audio file

  weekDay[5] = getWeekDay();
  // Main game loop
  while (!WindowShouldClose())  // Detect window close button or ESC key
  {
    BeginDrawing();
    ClearBackground(DARKGRAY);

    if (IsKeyPressed(KEY_SPACE)) {
      fmt::print(fmt::emphasis::bold | fg(fmt::color::green), "play wav \n");
      // PlaySound(fxWav);  // Play WAV sound
    }
    if (IsKeyPressed(KEY_ENTER)) {
      fmt::print(fmt::emphasis::bold | fg(fmt::color::green), "play ogg \n");
      // PlaySound(fxOgg);  // Play OGG sound
    }

    // DrawText("Press SPACE to PLAY the WAV sound!", 200, 180, 20, LIGHTGRAY);
    // DrawText("Press ENTER to PLAY the OGG sound!", 200, 220, 20, LIGHTGRAY);

    // start ImGui Conent
    rlImGuiBegin();

    // show ImGui Content
    bool open = true;
    ImGui::ShowDemoWindow(&open);
    if (show_app_window_convict)
      ShowAppWindowConvict(&show_app_window_convict);
    // end ImGui Content
    rlImGuiEnd();

    EndDrawing();
    //----------------------------------------------------------------------------------
  }
  rlImGuiShutdown();

  UnloadSound(fxWav);  // Unload sound data
  UnloadSound(fxOgg);  // Unload sound data

  CloseAudioDevice();  // Close audio device
  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow();  // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
