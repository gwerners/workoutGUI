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
#include "database.hpp"
#include "raylib.h"
#include "raymath.h"

#include "imgui.h"
#include "rlImGui.h"

#include <fmt/color.h>
#include <fmt/format.h>

#include <vector>

const unsigned int wait4seconds = 60;

unsigned int width = 1280;
unsigned int height = 720;
std::vector<std::string> users;

int u = 0;

std::vector<std::string> routines;
int routine = -1;
int new_routine = -1;
int r = 0;

std::vector<std::string> movements;

int movement = -1;
int m = 0;

int w = -1;
int wm = -1;

int selected[50];
int s = 0;

int status[8];
int s1 = -1;
int s2 = -1;
int s3 = -1;
int s4 = -1;
int s5 = -1;
int s6 = -1;

int eOne = 0;
int eTwo = 0;

int nOne = 0;
int nTwo = 0;

char eOneLine[1024];
char eTwoLine[1024];

int Acoluna1[8];
int Acoluna2[8];
int Acoluna3[8];

int Bcoluna1[8];
int Bcoluna2[8];
int Bcoluna3[8];

void SetupStyleFromHue();

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

void init() {
  const char* databaseName = getenv("WORKOUT_DATABASE");
  char databaseNameBuffer[256];
  if (databaseName == nullptr) {
    fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
               "WORKOUT_DATABASE is empty! Using Workout.db as default.\n");

    strcpy((char*)databaseNameBuffer, "Workout.db");
    databaseName = (char*)databaseNameBuffer;
  }
  startDatabase(databaseName);
}
static void initializeData() {
  fmt::print(fmt::emphasis::bold | fg(fmt::color::red), "initializing data\n");
  database::instance().getString("SELECT * FROM User;", users, 1, 50, &u);
  database::instance().getString("SELECT * FROM Routine;", routines, 1, 50, &r);
  routine = -1;
  database::instance().getString("SELECT * FROM Movement;", movements, 1, 50,
                                 &m);
  movement = 0;
  w = getWeekDay();
  wm = w;
  database::instance().getColumn(
      fmt::format("SELECT * FROM Status WHERE Id = 1;"), (int*)&status, 1, 7);
  new_routine = status[0] - 1;
  s1 = status[1];
  s2 = status[2];
  s3 = status[3];
  s4 = status[4];
  s5 = status[5];
  s6 = status[6];
  database::instance().getInt(
      fmt::format("SELECT * FROM Progress WHERE Routine={} and Day={};",
                  new_routine + 1, w),
      (int*)&selected, 2, 50, &s);
  eOne = database::instance().queryGetInt(
             fmt::format("SELECT {} FROM ProgressionIndex WHERE Id = 1;",
                         getEName(selected[0]))) -
         1;
  nOne = eOne;
  eTwo = database::instance().queryGetInt(
             fmt::format("SELECT {} FROM ProgressionIndex WHERE Id = 1;",
                         getEName(selected[1]))) -
         1;
  nTwo = eTwo;
  SetupStyleFromHue();
}
static void updateData() {
  int i, j, id, one = 1;

  if ((w != wm) || (s1 != status[1]) || (s2 != status[2]) ||
      (s3 != status[3]) || (s4 != status[4]) || (s5 != status[5]) ||
      (s6 != status[6]) || (routine != new_routine)) {
    wm = w;

    database::instance().sqlCmd(
        fmt::format("BEGIN TRANSACTION;Update Status SET Routine = "
                    "{},Pushups = {},Squats = {},Pullups = "
                    "{},LegRaises = {},Bridges = {},HandstandPushups = {} "
                    "WHERE Id = 1;COMMIT;",
                    new_routine + 1, s1, s2, s3, s4, s5, s6));

    status[1] = s1;
    status[2] = s2;
    status[3] = s3;
    status[4] = s4;
    status[5] = s5;
    status[6] = s6;
    memset(Acoluna1, 0, sizeof(int) * 8);
    memset(Acoluna2, 0, sizeof(int) * 8);
    memset(Acoluna3, 0, sizeof(int) * 8);
    memset(Bcoluna1, 0, sizeof(int) * 8);
    memset(Bcoluna2, 0, sizeof(int) * 8);
    memset(Bcoluna3, 0, sizeof(int) * 8);
    printf("%d new_routine!=routine\n", __LINE__);
    routine = new_routine;
    memset(selected, 0, sizeof(int) * 50);
    database::instance().getInt(
        fmt::format(
            "SELECT Routine, Day, Movement FROM Progress WHERE Routine={} and "
            "Day={};",
            new_routine + 1, w),
        (int*)&selected, 2, 50, &s);

    if (selected[0]) {
      switch (selected[0]) {
        case 1:  // Pushups
          id = s1;
          database::instance().getLine("Select * from Pushups;",
                                       (char*)eOneLine);
          break;
        case 2:  // Squats
          id = s2;
          database::instance().getLine("Select * from Squats;",
                                       (char*)eOneLine);
          break;
        case 3:  // Pullups
          id = s3;
          database::instance().getLine("Select * from Pullups;",
                                       (char*)eOneLine);
          break;
        case 4:  // LegRaises
          id = s4;
          database::instance().getLine("Select * from LegRaises;",
                                       (char*)eOneLine);
          break;
        case 5:  // Bridges
          id = s5;
          database::instance().getLine("Select * from Bridges;",
                                       (char*)eOneLine);
          break;
        case 6:  // HandstandPushups
          id = s6;
          database::instance().getLine("Select * from HandstandPushups;",
                                       (char*)eOneLine);
          break;
      }

      database::instance().getColumn(
          fmt::format("SELECT * FROM Set1 WHERE Id = {};", id), (int*)Acoluna1,
          2, 9);
      database::instance().getColumn(
          fmt::format("SELECT * FROM Set2 WHERE Id = {};", id), (int*)Acoluna2,
          2, 9);
      database::instance().getColumn(
          fmt::format("SELECT * FROM Set3 WHERE Id = {};", id), (int*)Acoluna3,
          2, 9);
      eOne = database::instance().queryGetInt(
                 fmt::format("SELECT {} FROM ProgressionIndex WHERE Id = 1;",
                             getEName(selected[0]))) -
             1;
      nOne = eOne;
    }
    if (selected[1]) {
      switch (selected[1]) {
        case 1:  // Pushups
          id = s1;
          database::instance().getLine("Select * from Pushups;",
                                       (char*)eTwoLine);
          break;
        case 2:  // Squats
          id = s2;
          database::instance().getLine("Select * from Squats;",
                                       (char*)eTwoLine);
          break;
        case 3:  // Pullups
          id = s3;
          database::instance().getLine("Select * from Pullups;",
                                       (char*)eTwoLine);
          break;
        case 4:  // LegRaises
          id = s4;
          database::instance().getLine("Select * from LegRaises;",
                                       (char*)eTwoLine);
          break;
        case 5:  // Bridges
          id = s5;
          database::instance().getLine("Select * from Bridges;",
                                       (char*)eTwoLine);
          break;
        case 6:  // HandstandPushups
          id = s6;
          database::instance().getLine("Select * from HandstandPushups;",
                                       (char*)eTwoLine);
          break;
      }
      database::instance().getColumn(
          fmt::format("SELECT * FROM Set1 WHERE Id = {};", id), (int*)Bcoluna1,
          2, 9);
      database::instance().getColumn(
          fmt::format("SELECT * FROM Set2 WHERE Id = {};", id), (int*)Bcoluna2,
          2, 9);
      database::instance().getColumn(
          fmt::format("SELECT * FROM Set3 WHERE Id = {};", id), (int*)Bcoluna3,
          2, 9);
      eTwo = database::instance().queryGetInt(
                 fmt::format("SELECT {} FROM ProgressionIndex WHERE Id = 1;",
                             getEName(selected[1]))) -
             1;
      nTwo = eTwo;
    }
  }  // if(new_routine!=routine)
  if (eOne != nOne) {
    fmt::print(fmt::emphasis::bold | fg(fmt::color::green), "[{} {}] {}\n",
               eOne, nOne, "nOne changed");
    database::instance().sqlCmd(
        fmt::format("Update ProgressionIndex SET {} = {} WHERE Id = 1;",
                    getEName(selected[0]), nOne + 1));
    eOne = nOne;
  }
  if (eTwo != nTwo) {
    fmt::print(fmt::emphasis::bold | fg(fmt::color::green), "[{} {}] {}\n",
               eTwo, nTwo, "nTwo changed");
    database::instance().sqlCmd(
        fmt::format("Update ProgressionIndex SET {} = {} WHERE Id = 1;",
                    getEName(selected[1]), nTwo + 1));
    eTwo = nTwo;
  }
}

static void showWorkoutGui(const Sound& alarm) {
  static bool a = false;
  static int marked1 = -1;
  static int marked2 = -1;
  static int OnlyOnce = 1;
  int i, j;
  char name[256];
  static bool once = true;
  if (once) {
    initializeData();
    once = false;
  }
  updateData();
  ImGui::PushItemWidth(150);
  ImGui::Combo(
      "Day of Week", &w,
      "Sunday\0Monday\0Tursday\0Wednesday\0Thursday\0Friday\0Saturday\0\0");
  ImGui::SameLine(0, 20);

  ImGui::PushItemWidth(250);
  if (selected[0]) {
    ImGui::SameLine(0, 20);
    ImGui::Combo(getEName(selected[0]), &nOne, eOneLine);
  }
  if (selected[1]) {
    ImGui::SameLine(0, 20);
    ImGui::Combo(getEName(selected[1]), &nTwo, eTwoLine);
  }
  if (!a) {
    // ImGui::SameLine(0, 20);
    if (ImGui::Button("Start Routine##425")) {
      marked1 = 0;
      marked2 = 0;
      a ^= 1;
    }
  }
  if (a) {
    static time_t dingdong = 0;
    if (dingdong && dingdong < time(NULL)) {
      dingdong = 0;
      PlaySound(alarm);
    }
    if (dingdong) {
      ImGui::Text("Wait %.2d...", (int)(dingdong - time(NULL)));
      ImGui::SameLine(0, 20);
    }
    // ImGui::SameLine(0, 20);
    if (ImGui::Button("Next Routine##429")) {
      ++marked2;
      ++marked1;
      dingdong = time(NULL) + wait4seconds;
    }
    if (marked1 >= 8) {
      marked1 = 0;
      marked2 = 0;
    }
  }
  //////////////////////////////////////////////////////////////////////////////
  for (i = 0; i < r; i++) {
    ImGui::RadioButton(routines[i].c_str(), &new_routine, i);
    ImGui::SameLine();
  }
  //////////////////////////////////////////////////////////////////////////////
  static int n = 0;
  ImGui::Columns(2);
  ImGui::Separator();
  bool isSelected;
  for (i = 0; i < m; i++) {
    isSelected = false;
    for (j = 0; j < s; j++) {
      if (selected[j] - 1 == i) {
        isSelected = true;
        break;
      }
    }
    ImGui::Selectable(movements[i].c_str(), isSelected);
  }
  ImGui::NextColumn();

  ImGui::InputInt("Pushups##286", &s1);
  ImGui::InputInt("Squats##287", &s2);
  ImGui::InputInt("Pullups##288", &s3);
  ImGui::InputInt("LegRaises##289", &s4);
  ImGui::InputInt("Bridges##290", &s5);
  ImGui::InputInt("HandstandPushups##291", &s6);
  if (s1 <= 0)
    s1 = 1;
  if (s2 <= 0)
    s2 = 1;
  if (s3 <= 0)
    s3 = 1;
  if (s4 <= 0)
    s4 = 1;
  if (s5 <= 0)
    s5 = 1;
  if (s6 <= 0)
    s6 = 1;

  if (s1 > 18)
    s1 = 18;
  if (s2 > 18)
    s2 = 18;
  if (s3 > 18)
    s3 = 18;
  if (s4 > 18)
    s4 = 18;
  if (s5 > 18)
    s5 = 18;
  if (s6 > 18)
    s6 = 18;
  ImGui::Columns(1);
  //////////////////////////////////////////////////////////////////////////////
  const char* names1[8] = {"SET 1##SETA1", "SET 2##SETA2", "SET 3##SETA3",
                           "SET 4##SETA4", "SET 5##SETA5", "SET 6##SETA6",
                           "SET 7##SETA7", "SET 8##SETA8"};
  const char* names2[8] = {"SET 1##SETB1", "SET 2##SETB2", "SET 3##SETB3",
                           "SET 4##SETB4", "SET 5##SETB5", "SET 6##SETB6",
                           "SET 7##SETB7", "SET 8##SETB8"};
  char item1[20];
  char item2[20];
  char item3[20];
  // ImGui::Separator();
  // ImGui::Text("Séries:");
  ImGui::Columns(4, "Exercise1");  // 4-ways, with border
  ImGui::Separator();
  sprintf(name, "%s", getEName(selected[0]));
  ImGui::Text("%s", name);
  ImGui::NextColumn();
  ImGui::Text("<5");
  ImGui::NextColumn();
  ImGui::Text("6-10");
  ImGui::NextColumn();
  ImGui::Text("11-20");
  ImGui::NextColumn();
  ImGui::Separator();
  for (i = 0; i < 8; i++) {
    if (ImGui::Selectable((char*)names1[i], marked1 == i,
                          ImGuiSelectableFlags_SpanAllColumns))
      marked1 = i;
    ImGui::NextColumn();
    sprintf((char*)&item1, "%d", Acoluna1[i]);
    sprintf((char*)&item2, "%d", Acoluna2[i]);
    sprintf((char*)&item3, "%d", Acoluna3[i]);
    ImGui::Text("%s", (char*)&item1);
    ImGui::NextColumn();
    ImGui::Text("%s", (char*)&item2);
    ImGui::NextColumn();
    ImGui::Text("%s", (char*)&item3);
    ImGui::NextColumn();
  }
  ImGui::Columns(1);
  ImGui::Separator();
  ImGui::Columns(4, "Exercise2");
  sprintf(name, "%s", getEName(selected[1]));
  ImGui::Text("%s", (char*)name);
  ImGui::NextColumn();
  ImGui::Text("<5");
  ImGui::NextColumn();
  ImGui::Text("6-10");
  ImGui::NextColumn();
  ImGui::Text("11-20");
  ImGui::NextColumn();
  ImGui::Separator();
  for (i = 0; i < 8; i++) {
    if (ImGui::Selectable((char*)names2[i], marked2 == i,
                          ImGuiSelectableFlags_SpanAllColumns))
      marked2 = i;
    ImGui::NextColumn();
    sprintf((char*)&item1, "%d", Bcoluna1[i]);
    sprintf((char*)&item2, "%d", Bcoluna2[i]);
    sprintf((char*)&item3, "%d", Bcoluna3[i]);
    ImGui::Text("%s", (char*)&item1);
    ImGui::NextColumn();
    ImGui::Text("%s", (char*)&item2);
    ImGui::NextColumn();
    ImGui::Text("%s", (char*)&item3);
    ImGui::NextColumn();
  }
  ImGui::Columns(1);
  ImGui::Separator();
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
              1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

int main(int argc, char* argv[]) {
  init();
  int screenWidth = 1280;
  int screenHeight = 800;

  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
  InitWindow(screenWidth, screenHeight, "Workout Gui + ImGui Demo");
  SetTargetFPS(144);
  rlImGuiSetup(true);
  InitAudioDevice();  // Initialize audio device

  Sound alarm = LoadSound("./alarm.mp3");
  bool show_training_window = true;
  while (!WindowShouldClose())  // Detect window close button or ESC key
  {
    BeginDrawing();
    ClearBackground(DARKGRAY);
    rlImGuiBegin();
    //----------------------------------------------------------------------------------
    bool open = true;
    ImGui::ShowDemoWindow(&open);

    if (show_training_window) {
      ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiCond_FirstUseEver);
      ImGui::Begin("Training", &show_training_window);
      showWorkoutGui(alarm);
      ImGui::End();
      // ImGui::ShowMetricsWindow(&show_training_window);
    }
    //----------------------------------------------------------------------------------
    rlImGuiEnd();
    EndDrawing();
  }
  rlImGuiShutdown();
  UnloadSound(alarm);
  CloseAudioDevice();
  CloseWindow();
  return 0;
}

void SetupStyleFromHue() {
#if 1
  // FIXME: those should become parameters to the function
  static int hue = 140;
  static float col_main_sat = 180.f / 255.f;
  static float col_main_val = 161.f / 255.f;
  static float col_area_sat = 124.f / 255.f;
  static float col_area_val = 100.f / 255.f;
  static float col_back_sat = 59.f / 255.f;
  static float col_back_val = 40.f / 255.f;

  ImGui::Begin("Hue Style");
  ImGui::SliderInt("master hue", &hue, 0, 255);

  float dummy;
  ImVec4 rgb;
  ImGui::SetColorEditOptions(ImGuiColorEditFlags_InputHSV);

  ImGui::ColorConvertHSVtoRGB(hue / 255.f, col_main_sat, col_main_val, rgb.x,
                              rgb.y, rgb.z);
  ImGui::ColorEdit3("main", &rgb.x);
  ImGui::ColorConvertRGBtoHSV(rgb.x, rgb.y, rgb.z, dummy, col_main_sat,
                              col_main_val);

  ImGui::ColorConvertHSVtoRGB(hue / 255.f, col_area_sat, col_area_val, rgb.x,
                              rgb.y, rgb.z);
  ImGui::ColorEdit3("area", &rgb.x);
  ImGui::ColorConvertRGBtoHSV(rgb.x, rgb.y, rgb.z, dummy, col_area_sat,
                              col_area_val);

  ImGui::ColorConvertHSVtoRGB(hue / 255.f, col_back_sat, col_back_val, rgb.x,
                              rgb.y, rgb.z);
  ImGui::ColorEdit3("back", &rgb.x);
  ImGui::ColorConvertRGBtoHSV(rgb.x, rgb.y, rgb.z, dummy, col_back_sat,
                              col_back_val);

  ImGui::End();
#endif

  ImGuiStyle& style = ImGui::GetStyle();

  ImVec4 col_text = ImColor::HSV(hue / 255.f, 20.f / 255.f, 235.f / 255.f);
  ImVec4 col_main = ImColor::HSV(hue / 255.f, col_main_sat, col_main_val);
  ImVec4 col_back = ImColor::HSV(hue / 255.f, col_back_sat, col_back_val);
  ImVec4 col_area = ImColor::HSV(hue / 255.f, col_area_sat, col_area_val);

  style.Colors[ImGuiCol_Text] =
      ImVec4(col_text.x, col_text.y, col_text.z, 1.00f);
  style.Colors[ImGuiCol_TextDisabled] =
      ImVec4(col_text.x, col_text.y, col_text.z, 0.58f);
  style.Colors[ImGuiCol_WindowBg] =
      ImVec4(col_back.x, col_back.y, col_back.z, 1.00f);
  style.Colors[ImGuiCol_ChildBg] =
      ImVec4(col_area.x, col_area.y, col_area.z, 0.00f);
  style.Colors[ImGuiCol_Border] =
      ImVec4(col_text.x, col_text.y, col_text.z, 0.30f);
  style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  style.Colors[ImGuiCol_FrameBg] =
      ImVec4(col_area.x, col_area.y, col_area.z, 1.00f);
  style.Colors[ImGuiCol_FrameBgHovered] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.68f);
  style.Colors[ImGuiCol_FrameBgActive] =
      ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
  style.Colors[ImGuiCol_TitleBg] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.45f);
  style.Colors[ImGuiCol_TitleBgCollapsed] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.35f);
  style.Colors[ImGuiCol_TitleBgActive] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.78f);
  style.Colors[ImGuiCol_MenuBarBg] =
      ImVec4(col_area.x, col_area.y, col_area.z, 0.57f);
  style.Colors[ImGuiCol_ScrollbarBg] =
      ImVec4(col_area.x, col_area.y, col_area.z, 1.00f);
  style.Colors[ImGuiCol_ScrollbarGrab] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.31f);
  style.Colors[ImGuiCol_ScrollbarGrabHovered] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.78f);
  style.Colors[ImGuiCol_ScrollbarGrabActive] =
      ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
  style.Colors[ImGuiCol_PopupBg] =
      ImVec4(col_area.x, col_area.y, col_area.z, 1.00f);
  style.Colors[ImGuiCol_CheckMark] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.80f);
  style.Colors[ImGuiCol_SliderGrab] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.24f);
  style.Colors[ImGuiCol_SliderGrabActive] =
      ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
  style.Colors[ImGuiCol_Button] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.44f);
  style.Colors[ImGuiCol_ButtonHovered] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.86f);
  style.Colors[ImGuiCol_ButtonActive] =
      ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
  style.Colors[ImGuiCol_Header] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.76f);
  style.Colors[ImGuiCol_HeaderHovered] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.86f);
  style.Colors[ImGuiCol_HeaderActive] =
      ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
  style.Colors[ImGuiCol_Separator] =
      ImVec4(col_text.x, col_text.y, col_text.z, 0.32f);
  style.Colors[ImGuiCol_SeparatorHovered] =
      ImVec4(col_text.x, col_text.y, col_text.z, 0.78f);
  style.Colors[ImGuiCol_SeparatorActive] =
      ImVec4(col_text.x, col_text.y, col_text.z, 1.00f);
  style.Colors[ImGuiCol_ResizeGrip] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.20f);
  style.Colors[ImGuiCol_ResizeGripHovered] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.78f);
  style.Colors[ImGuiCol_ResizeGripActive] =
      ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
  style.Colors[ImGuiCol_PlotLines] =
      ImVec4(col_text.x, col_text.y, col_text.z, 0.63f);
  style.Colors[ImGuiCol_PlotLinesHovered] =
      ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
  style.Colors[ImGuiCol_PlotHistogram] =
      ImVec4(col_text.x, col_text.y, col_text.z, 0.63f);
  style.Colors[ImGuiCol_PlotHistogramHovered] =
      ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
  style.Colors[ImGuiCol_TextSelectedBg] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.43f);
  style.Colors[ImGuiCol_PopupBg] =
      ImVec4(col_main.x, col_main.y, col_main.z, 0.92f);
  style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}
