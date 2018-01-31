// ImGui - standalone example application for Glfw + OpenGL 3, using programmable pipeline
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"

//#define GLFW_INCLUDE_GLCOREARB
//#define GLFW_INCLUDE_GLU
#include "GL/gl3w.h"
#include "GLFW/glfw3.h"
#include "GL/OSX_GL.h"

#include <iostream>
#include <sstream>
#include <vector>

#include "Model.h"

#ifdef __APPLE__
extern const char* utilGetBundleResourcePath(const char* name,const char*type);
#endif

unsigned int width, height;
std::vector<std::string> users;
int user = -1;
int u=0;

std::vector<std::string> routines;
int routine = -1;
int new_routine = -1;
int r=0;

std::vector<std::string> movements;

int movement = -1;
int m=0;

int w=-1;
int wm=-1;

int selected[50];
int s=0;

int status[8];
int s1=-1;
int s2=-1;
int s3=-1;
int s4=-1;
int s5=-1;
int s6=-1;

int eOne=0;
int eTwo=0;

int nOne=0;
int nTwo=0;

char eOneLine[1024];
char eTwoLine[1024];

int Acoluna1[8];
int Acoluna2[8];
int Acoluna3[8];

int Bcoluna1[8];
int Bcoluna2[8];
int Bcoluna3[8];

int getWeekDay(){
  struct tm *ts;
  time_t timestamp = time(NULL);
  ts   = localtime(&timestamp);
  return ts->tm_wday;
}
const char*getEName(int i){
  switch(i){
  case 1: return "Pushups";
  case 2: return "Squats";
  case 3: return "Pullups";
  case 4: return "LegRaises";
  case 5: return "Bridges";
  case 6: return "HandstandPushups";
  default: return "";
  }
}

static void error_callback(int error, const char* description)
{
  std::cerr << "Error " << error << ": " << description << std::endl;
}
void SetupImGuiStyle( bool bStyleDark_, float alpha_  ){
  ImGuiStyle& style = ImGui::GetStyle();

  // light style from Pacôme Danhiez (user itamago) https://github.com/ocornut/imgui/pull/511#issuecomment-175719267
  style.Alpha = 1.0f;
  style.FrameRounding = 3.0f;
  style.Colors[ImGuiCol_Text]                  = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  style.Colors[ImGuiCol_TextDisabled]          = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
  style.Colors[ImGuiCol_WindowBg]              = ImVec4(0.94f, 0.94f, 0.94f, 0.94f);
  style.Colors[ImGuiCol_ChildWindowBg]         = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  style.Colors[ImGuiCol_PopupBg]               = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
  style.Colors[ImGuiCol_Border]                = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
  style.Colors[ImGuiCol_BorderShadow]          = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
  style.Colors[ImGuiCol_FrameBg]               = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
  style.Colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
  style.Colors[ImGuiCol_FrameBgActive]         = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
  style.Colors[ImGuiCol_TitleBg]               = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
  style.Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
  style.Colors[ImGuiCol_TitleBgActive]         = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
  style.Colors[ImGuiCol_MenuBarBg]             = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
  style.Colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
  style.Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
  style.Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
  style.Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
  style.Colors[ImGuiCol_ComboBg]               = ImVec4(0.86f, 0.86f, 0.86f, 0.99f);
  style.Colors[ImGuiCol_CheckMark]             = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  style.Colors[ImGuiCol_SliderGrab]            = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
  style.Colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  style.Colors[ImGuiCol_Button]                = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
  style.Colors[ImGuiCol_ButtonHovered]         = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  style.Colors[ImGuiCol_ButtonActive]          = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
  style.Colors[ImGuiCol_Header]                = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
  style.Colors[ImGuiCol_HeaderHovered]         = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
  style.Colors[ImGuiCol_HeaderActive]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  style.Colors[ImGuiCol_Column]                = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
  style.Colors[ImGuiCol_ColumnHovered]         = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
  style.Colors[ImGuiCol_ColumnActive]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  style.Colors[ImGuiCol_ResizeGrip]            = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
  style.Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
  style.Colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
  style.Colors[ImGuiCol_CloseButton]           = ImVec4(0.59f, 0.59f, 0.59f, 0.50f);
  style.Colors[ImGuiCol_CloseButtonHovered]    = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
  style.Colors[ImGuiCol_CloseButtonActive]     = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
  style.Colors[ImGuiCol_PlotLines]             = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
  style.Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
  style.Colors[ImGuiCol_PlotHistogram]         = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
  style.Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
  style.Colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
  style.Colors[ImGuiCol_ModalWindowDarkening]  = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

  if( bStyleDark_ )
  {
      for (int i = 0; i <= ImGuiCol_COUNT; i++)
      {
          ImVec4& col = style.Colors[i];
          float H, S, V;
          ImGui::ColorConvertRGBtoHSV( col.x, col.y, col.z, H, S, V );

          if( S < 0.1f )
          {
             V = 1.0f - V;
          }
          ImGui::ColorConvertHSVtoRGB( H, S, V, col.x, col.y, col.z );
          if( col.w < 1.00f )
          {
              col.w *= alpha_;
          }
      }
  }
  else
  {
      for (int i = 0; i <= ImGuiCol_COUNT; i++)
      {
          ImVec4& col = style.Colors[i];
          if( col.w < 1.00f )
          {
              col.x *= alpha_;
              col.y *= alpha_;
              col.z *= alpha_;
              col.w *= alpha_;
          }
      }
  }
}
void SetupStyleFromHue()
{
#if 1
    // FIXME: those should become parameters to the function
    static int hue = 140;
    static float col_main_sat = 180.f/255.f;
    static float col_main_val = 161.f/255.f;
    static float col_area_sat = 124.f/255.f;
    static float col_area_val = 100.f/255.f;
    static float col_back_sat = 59.f/255.f;
    static float col_back_val = 40.f/255.f;

    ImGui::Begin("Hue Style");
    ImGui::SliderInt("master hue", &hue, 0, 255);

    float dummy;
    ImVec4 rgb;
    ImGui::ColorEditMode(ImGuiColorEditMode_HSV);

    ImGui::ColorConvertHSVtoRGB(hue/255.f, col_main_sat, col_main_val, rgb.x, rgb.y, rgb.z);
    ImGui::ColorEdit3("main", &rgb.x);
    ImGui::ColorConvertRGBtoHSV(rgb.x, rgb.y, rgb.z, dummy, col_main_sat, col_main_val);

    ImGui::ColorConvertHSVtoRGB(hue/255.f, col_area_sat, col_area_val, rgb.x, rgb.y, rgb.z);
    ImGui::ColorEdit3("area", &rgb.x);
    ImGui::ColorConvertRGBtoHSV(rgb.x, rgb.y, rgb.z, dummy, col_area_sat, col_area_val);

    ImGui::ColorConvertHSVtoRGB(hue/255.f, col_back_sat, col_back_val, rgb.x, rgb.y, rgb.z);
    ImGui::ColorEdit3("back", &rgb.x);
    ImGui::ColorConvertRGBtoHSV(rgb.x, rgb.y, rgb.z, dummy, col_back_sat, col_back_val);

    ImGui::End();
#endif

    ImGuiStyle& style = ImGui::GetStyle();

    ImVec4 col_text = ImColor::HSV(hue/255.f,  20.f/255.f, 235.f/255.f);
    ImVec4 col_main = ImColor::HSV(hue/255.f, col_main_sat, col_main_val);
    ImVec4 col_back = ImColor::HSV(hue/255.f, col_back_sat, col_back_val);
    ImVec4 col_area = ImColor::HSV(hue/255.f, col_area_sat, col_area_val);

    style.Colors[ImGuiCol_Text]                  = ImVec4(col_text.x, col_text.y, col_text.z, 1.00f);
    style.Colors[ImGuiCol_TextDisabled]          = ImVec4(col_text.x, col_text.y, col_text.z, 0.58f);
    style.Colors[ImGuiCol_WindowBg]              = ImVec4(col_back.x, col_back.y, col_back.z, 1.00f);
    style.Colors[ImGuiCol_ChildWindowBg]         = ImVec4(col_area.x, col_area.y, col_area.z, 0.00f);
    style.Colors[ImGuiCol_Border]                = ImVec4(col_text.x, col_text.y, col_text.z, 0.30f);
    style.Colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_FrameBg]               = ImVec4(col_area.x, col_area.y, col_area.z, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered]        = ImVec4(col_main.x, col_main.y, col_main.z, 0.68f);
    style.Colors[ImGuiCol_FrameBgActive]         = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
    style.Colors[ImGuiCol_TitleBg]               = ImVec4(col_main.x, col_main.y, col_main.z, 0.45f);
    style.Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(col_main.x, col_main.y, col_main.z, 0.35f);
    style.Colors[ImGuiCol_TitleBgActive]         = ImVec4(col_main.x, col_main.y, col_main.z, 0.78f);
    style.Colors[ImGuiCol_MenuBarBg]             = ImVec4(col_area.x, col_area.y, col_area.z, 0.57f);
    style.Colors[ImGuiCol_ScrollbarBg]           = ImVec4(col_area.x, col_area.y, col_area.z, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(col_main.x, col_main.y, col_main.z, 0.31f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(col_main.x, col_main.y, col_main.z, 0.78f);
    style.Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
    style.Colors[ImGuiCol_ComboBg]               = ImVec4(col_area.x, col_area.y, col_area.z, 1.00f);
    style.Colors[ImGuiCol_CheckMark]             = ImVec4(col_main.x, col_main.y, col_main.z, 0.80f);
    style.Colors[ImGuiCol_SliderGrab]            = ImVec4(col_main.x, col_main.y, col_main.z, 0.24f);
    style.Colors[ImGuiCol_SliderGrabActive]      = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
    style.Colors[ImGuiCol_Button]                = ImVec4(col_main.x, col_main.y, col_main.z, 0.44f);
    style.Colors[ImGuiCol_ButtonHovered]         = ImVec4(col_main.x, col_main.y, col_main.z, 0.86f);
    style.Colors[ImGuiCol_ButtonActive]          = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
    style.Colors[ImGuiCol_Header]                = ImVec4(col_main.x, col_main.y, col_main.z, 0.76f);
    style.Colors[ImGuiCol_HeaderHovered]         = ImVec4(col_main.x, col_main.y, col_main.z, 0.86f);
    style.Colors[ImGuiCol_HeaderActive]          = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
    style.Colors[ImGuiCol_Column]                = ImVec4(col_text.x, col_text.y, col_text.z, 0.32f);
    style.Colors[ImGuiCol_ColumnHovered]         = ImVec4(col_text.x, col_text.y, col_text.z, 0.78f);
    style.Colors[ImGuiCol_ColumnActive]          = ImVec4(col_text.x, col_text.y, col_text.z, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip]            = ImVec4(col_main.x, col_main.y, col_main.z, 0.20f);
    style.Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(col_main.x, col_main.y, col_main.z, 0.78f);
    style.Colors[ImGuiCol_ResizeGripActive]      = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
    style.Colors[ImGuiCol_CloseButton]           = ImVec4(col_text.x, col_text.y, col_text.z, 0.16f);
    style.Colors[ImGuiCol_CloseButtonHovered]    = ImVec4(col_text.x, col_text.y, col_text.z, 0.39f);
    style.Colors[ImGuiCol_CloseButtonActive]     = ImVec4(col_text.x, col_text.y, col_text.z, 1.00f);
    style.Colors[ImGuiCol_PlotLines]             = ImVec4(col_text.x, col_text.y, col_text.z, 0.63f);
    style.Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram]         = ImVec4(col_text.x, col_text.y, col_text.z, 0.63f);
    style.Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg]        = ImVec4(col_main.x, col_main.y, col_main.z, 0.43f);
    //style.Colors[ImGuiCol_TooltipBg]             = ImVec4(col_main.x, col_main.y, col_main.z, 0.92f);
    style.Colors[ImGuiCol_ModalWindowDarkening]  = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}
static void initializeData(const char*path){
  std::stringstream os;
  if(user==-1)
  {
    Database model(path);
      //"/Users/gabrielwernersbachfarinas/gui/convict_3.0/genapp/Convict.app/Contents/Resources/convict.db");
    std::cout << "inicializando tela" << std::endl;

    //get users
    model.getString("SELECT * FROM User;",users,1,50,&u);
    user=0;
    //////////////////////////////////////////////////////////////////////////
    //get routines
    model.getString("SELECT * FROM Routine;",routines,1,50,&r);
    routine=-1;
    //////////////////////////////////////////////////////////////////////////
    //get movements
    model.getString("SELECT * FROM Movement;",movements,1,50,&m);
    movement=0;

    w=getWeekDay();
    wm=w;
    //////////////////////////////////////////////////////////////////////////
    os.str("");os.clear();
    os << "SELECT * FROM Status WHERE Id = " << user+1 << ";";
    model.getColumn(os.str(),(int*)&status,1,7);
    new_routine=status[0]-1;
    s1=status[1];
    s2=status[2];
    s3=status[3];
    s4=status[4];
    s5=status[5];
    s6=status[6];
    os.str("");os.clear();
    os << "SELECT * FROM Progress WHERE Routine=" << new_routine+1 << " and Day=" << w << ";";
    model.getInt(os.str(),(int*)&selected,2,50,&s);

    os.str("");os.clear();
    os << "SELECT " << getEName(selected[0]) << " FROM ProgressionIndex WHERE Id = " << user+1 << ";";
    eOne=model.QueryGetInt(os.str())-1;
    nOne=eOne;

    os.str("");os.clear();
    os << "SELECT " << getEName(selected[1]) << " FROM ProgressionIndex WHERE Id = " << user+1 << ";";
    eTwo=model.QueryGetInt(os.str())-1;
    nTwo=eTwo;

    SetupStyleFromHue();
  }
}
static void updateData(const char *path){
  int i,j,id,one=1;

  Database model(path);
  std::stringstream os;

  //"/Users/gabrielwernersbachfarinas/gui/convict_3.0/genapp/Convict.app/Contents/Resources/convict.db");
  if(
    (w!=wm)||
    (s1!=status[1])||
    (s2!=status[2])||
    (s3!=status[3])||
    (s4!=status[4])||
    (s5!=status[5])||
    (s6!=status[6])||
    (routine !=new_routine)
  )
  {
    wm=w;
    std::cout << __LINE__ << " segunda mudanca" << std::endl;

    os << "Update \"Status\" SET Routine = " << new_routine+1
    << ",Pushups = " << s1
    << ",Squats = "  << s2
    << ",Pullups = " << s3
    << ",LegRaises = "<< s4
    << ",Bridges = " << s5
    << ",HandstandPushups = " << s6
    << " WHERE Id = " << user+1
    << ";";
    model.sql(os.str());
    status[1]=s1;
    status[2]=s2;
    status[3]=s3;
    status[4]=s4;
    status[5]=s5;
    status[6]=s6;
    memset(Acoluna1,0,sizeof(int)*8);
    memset(Acoluna2,0,sizeof(int)*8);
    memset(Acoluna3,0,sizeof(int)*8);
    memset(Bcoluna1,0,sizeof(int)*8);
    memset(Bcoluna2,0,sizeof(int)*8);
    memset(Bcoluna3,0,sizeof(int)*8);
    printf("%d new_routine!=routine\n",__LINE__);
    routine=new_routine;
    os.str("");os.clear();
    os << "SELECT * FROM Progress WHERE Routine=" << new_routine+1 << " and Day=" << w << ";";
    memset(selected,0,sizeof(int)*50);
    model.getInt(os.str(),(int*)&selected,2,50,&s);

    if(selected[0]){
      switch(selected[0]){
        case 1://Pushups
          id=s1;
          model.getLine("Select * from Pushups;",(char*)eOneLine);
          break;
        case 2://Squats
          id=s2;
          model.getLine("Select * from Squats;",(char*)eOneLine);
          break;
        case 3://Pullups
          id=s3;
          model.getLine("Select * from Pullups;",(char*)eOneLine);
          break;
        case 4://LegRaises
          id=s4;
          model.getLine("Select * from LegRaises;",(char*)eOneLine);
          break;
        case 5://Bridges
          id=s5;
          model.getLine("Select * from Bridges;",(char*)eOneLine);
          break;
        case 6://HandstandPushups
          id=s6;
          model.getLine("Select * from HandstandPushups;",(char*)eOneLine);
          break;
      }
      os.str("");os.clear();
      os << "SELECT * FROM Set1 WHERE Id = " << id << ";";
      model.getColumn(os.str(),(int*)Acoluna1,2,9);
      os.str("");os.clear();
      os << "SELECT * FROM Set2 WHERE Id = " << id << ";";
      model.getColumn(os.str(),(int*)Acoluna2,2,9);
      os.str("");os.clear();
      os << "SELECT * FROM Set3 WHERE Id = " << id << ";";
      model.getColumn(os.str(),(int*)Acoluna3,2,9);
      os.str("");os.clear();
      os << "SELECT " << getEName(selected[0]) << " FROM ProgressionIndex WHERE Id = " << user+1;
      eOne=model.QueryGetInt(os.str())-1;
      nOne=eOne;
    }
    if(selected[1]){
      switch(selected[1]){
        case 1://Pushups
          id=s1;
          model.getLine("Select * from Pushups;",(char*)eTwoLine);
          break;
        case 2://Squats
          id=s2;
          model.getLine("Select * from Squats;",(char*)eTwoLine);
          break;
        case 3://Pullups
          id=s3;
          model.getLine("Select * from Pullups;",(char*)eTwoLine);
          break;
        case 4://LegRaises
          id=s4;
          model.getLine("Select * from LegRaises;",(char*)eTwoLine);
          break;
        case 5://Bridges
          id=s5;
          model.getLine("Select * from Bridges;",(char*)eTwoLine);
          break;
        case 6://HandstandPushups
          id=s6;
          model.getLine("Select * from HandstandPushups;",(char*)eTwoLine);
          break;
      }
      os.str("");os.clear();
      os << "SELECT * FROM Set1 WHERE Id = " << id << ";";
      model.getColumn(os.str(),(int*)Bcoluna1,2,9);
      os.str("");os.clear();
      os << "SELECT * FROM Set2 WHERE Id = " << id << ";";
      model.getColumn(os.str(),(int*)Bcoluna2,2,9);
      os.str("");os.clear();
      os << "SELECT * FROM Set3 WHERE Id = " << id << ";";
      model.getColumn(os.str(),(int*)Bcoluna3,2,9);
      os.str("");os.clear();
      os << "SELECT " << getEName(selected[1]) << " FROM ProgressionIndex WHERE Id = " << user+1;
      eTwo=model.QueryGetInt(os.str())-1;
      nTwo=eTwo;
    }
  }//if(new_routine!=routine)
  if(eOne!=nOne){
    printf("[%d %d]%s\n",eOne,nOne,"nOne changed");
    os.str("");os.clear();
    os << "Update \"ProgressionIndex\" SET "
      << getEName(selected[0]) << " = " << nOne+1
      << " WHERE Id = " << user+1 << ";";
    model.sql(os.str());
    //printf("%s[%s]\n","eOne update",os.str());
    eOne=nOne;
  }
  if(eTwo!=nTwo){
    printf("[%d %d]%s\n",eTwo,nTwo,"nTwo changed");
    os.str("");os.clear();
    os << "Update \"ProgressionIndex\" SET "
      << getEName(selected[1]) <<" = " << nTwo+1 << " WHERE Id = " << user+1 << ";";
    model.sql(os.str());
    //printf("%s[%s]\n","eTwo update",os.str());
    eTwo=nTwo;
  }
}
void ShowAnotherWindow(){
  static int marked1 = -1;
  static int marked2 = -1;
  int i;
  static int a=0;
  char name[256];

  if (!a){
    if (ImGui::Button("Start Routine##425")){
      marked1=0;
      marked2=0;
      a ^= 1;
    }
  }
  if (a){
    static time_t dingdong=0;
    static char counter[10];
    //ImGui::SameLine();
    if(dingdong && dingdong < time(NULL)){
      dingdong=0;
#ifdef __APPLE__
      system("say finished");
#endif
    }
    if(dingdong){
      sprintf((char*)&counter,"%.2d",(int)(dingdong-time(NULL)));
      ImGui::Text(counter);
      ImGui::SameLine();
    }
    if (ImGui::Button("Next Routine##429")){
      ++marked2;
      ++marked1;
      dingdong=time(NULL)+5;
    }
    if (marked1>=8){
      marked1=0;
      marked2=0;
    }
  }

  //////////////////////////////////////////////////////////////////////////////
  ImGui::Text("Séries:");
  ImGui::Columns(4,"Exercise1"); // 4-ways, with border
  ImGui::Separator();
  sprintf(name,"%s",getEName(selected[0]));
  ImGui::Text(name); ImGui::NextColumn();
  ImGui::Text("<5"); ImGui::NextColumn();
  ImGui::Text("6-10"); ImGui::NextColumn();
  ImGui::Text("11-20"); ImGui::NextColumn();
  ImGui::Separator();
  const char* names1[8] = {
    "SET 1##SETA1", "SET 2##SETA2", "SET 3##SETA3", "SET 4##SETA4",
    "SET 5##SETA5", "SET 6##SETA6", "SET 7##SETA7", "SET 8##SETA8" };
  const char* names2[8] = {
    "SET 1##SETB1", "SET 2##SETB2", "SET 3##SETB3", "SET 4##SETB4",
    "SET 5##SETB5", "SET 6##SETB6", "SET 7##SETB7", "SET 8##SETB8" };

  char item1[20];
  char item2[20];
  char item3[20];

  for (i = 0; i < 8; i++)
  {
      if (ImGui::Selectable((char*)names1[i], marked1 == i, ImGuiSelectableFlags_SpanAllColumns))
          marked1 = i;
      ImGui::NextColumn();
      sprintf((char*)&item1,"%d",i*1);
      sprintf((char*)&item2,"%d",i*2);
      sprintf((char*)&item3,"%d",i*3);
      ImGui::Text((char*)&item1); ImGui::NextColumn();
      ImGui::Text((char*)&item2); ImGui::NextColumn();
      ImGui::Text((char*)&item3); ImGui::NextColumn();
  }
  ImGui::Columns(1);
  ImGui::Separator();
  ImGui::Columns(4,"Exercise2");
  sprintf(name,"%s",getEName(selected[1]));
  ImGui::Text((char*)name); ImGui::NextColumn();
  ImGui::Text("<5"); ImGui::NextColumn();
  ImGui::Text("6-10"); ImGui::NextColumn();
  ImGui::Text("11-20"); ImGui::NextColumn();
  ImGui::Separator();
  for (i = 0; i < 8; i++)
  {
      if (ImGui::Selectable((char*)names2[i], marked2 == i, ImGuiSelectableFlags_SpanAllColumns))
          marked2 = i;
      ImGui::NextColumn();
      sprintf((char*)&item1,"%d",i*1);
      sprintf((char*)&item2,"%d",i*2);
      sprintf((char*)&item3,"%d",i*3);
      ImGui::Text((char*)&item1); ImGui::NextColumn();
      ImGui::Text((char*)&item2); ImGui::NextColumn();
      ImGui::Text((char*)&item3); ImGui::NextColumn();
  }
  ImGui::Columns(1);
  ImGui::Separator();
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
static void Training(const char*path)
{
  static bool a=false;
  static int marked1 = -1;
  static int marked2 = -1;
  static int OnlyOnce=1;
  int i,j;
  char name[256];
  //ImGui::Text((char*)&gpath);


  if(OnlyOnce){
    initializeData(path);
    OnlyOnce=0;
  }
  updateData(path);

  ImGui::PushItemWidth(150);
  ImGui::Combo("Dia da Semana", &w, "Domingo\0Segunda\0Terça\0Quarta\0Quinta\0Sexta\0Sabado\0\0");
  ImGui::SameLine(0, 20);
  //ImGui::PushItemWidth(150);
  //ImGui::Combo("Usuário", &user, (char*)users.data(), u);
  ImGui::Combo("Usuário", &user,
      [](void* vec, int idx, const char** out_text){
          std::vector<std::string>* vector = reinterpret_cast<std::vector<std::string>*>(vec);
          if(idx < 0 || idx >= vector->size())return false;
          *out_text = vector->at(idx).c_str();
          return true;
      }, reinterpret_cast<void*>(&users), users.size());

  ImGui::PushItemWidth(250);
  if(selected[0]){
    ImGui::SameLine(0, 20);
    ImGui::Combo(getEName(selected[0]), &nOne, eOneLine);
  }
  if(selected[1]){
    ImGui::SameLine(0, 20);
    ImGui::Combo(getEName(selected[1]), &nTwo, eTwoLine);
  }
  if (!a){
    //ImGui::SameLine(0, 20);
    if (ImGui::Button("Start Routine##425")){
      marked1=0;
      marked2=0;
      a ^= 1;
    }
  }
  if (a){
    static time_t dingdong=0;
    static char counter[10];
    if(dingdong && dingdong < time(NULL)){
      dingdong=0;
#ifdef __APPLE__
      system("say finished");
#else
      system("mpg123 -q alarm.mp3");
#endif
  }
    if(dingdong){
      sprintf((char*)&counter,"Aguarde %.2d...",(int)(dingdong-time(NULL)));
      ImGui::Text(counter);
      ImGui::SameLine(0, 20);

    }

    //ImGui::SameLine(0, 20);
    if(ImGui::Button("Next Routine##429")){
      ++marked2;
      ++marked1;
      dingdong=time(NULL)+60;
    }

    if (marked1>=8){
      marked1=0;
      marked2=0;
    }
  }
  //////////////////////////////////////////////////////////////////////////////
  for(i=0;i<r;i++){
    ImGui::RadioButton(routines[i].c_str(), &new_routine, i); ImGui::SameLine();
  }
  //////////////////////////////////////////////////////////////////////////////
  static int n=0;

  ImGui::Columns(2);
  ImGui::Separator();
  bool isSelected;
  for(i=0;i<m;i++){
    isSelected=false;
    for(j=0;j<s;j++){
      if(selected[j]-1==i){
        isSelected=true;
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
  if(s1<=0)s1=1;
  if(s2<=0)s2=1;
  if(s3<=0)s3=1;
  if(s4<=0)s4=1;
  if(s5<=0)s5=1;
  if(s6<=0)s6=1;

  if(s1>18)s1=18;
  if(s2>18)s2=18;
  if(s3>18)s3=18;
  if(s4>18)s4=18;
  if(s5>18)s5=18;
  if(s6>18)s6=18;
  ImGui::Columns(1);

  //////////////////////////////////////////////////////////////////////////////

  const char* names1[8] = {
    "SET 1##SETA1", "SET 2##SETA2", "SET 3##SETA3", "SET 4##SETA4",
    "SET 5##SETA5", "SET 6##SETA6", "SET 7##SETA7", "SET 8##SETA8" };
  const char* names2[8] = {
    "SET 1##SETB1", "SET 2##SETB2", "SET 3##SETB3", "SET 4##SETB4",
    "SET 5##SETB5", "SET 6##SETB6", "SET 7##SETB7", "SET 8##SETB8" };

  char item1[20];
  char item2[20];
  char item3[20];

  ImGui::Separator();
  ImGui::Text("Séries:");
  ImGui::Columns(4,"Exercise1"); // 4-ways, with border
  ImGui::Separator();
  sprintf(name,"%s",getEName(selected[0]));
  ImGui::Text(name); ImGui::NextColumn();
  ImGui::Text("<5"); ImGui::NextColumn();
  ImGui::Text("6-10"); ImGui::NextColumn();
  ImGui::Text("11-20"); ImGui::NextColumn();
  ImGui::Separator();

  for (i = 0; i < 8; i++)
  {
      if (ImGui::Selectable((char*)names1[i], marked1 == i, ImGuiSelectableFlags_SpanAllColumns))
          marked1 = i;
      ImGui::NextColumn();
      sprintf((char*)&item1,"%d",Acoluna1[i]);
      sprintf((char*)&item2,"%d",Acoluna2[i]);
      sprintf((char*)&item3,"%d",Acoluna3[i]);
      ImGui::Text((char*)&item1); ImGui::NextColumn();
      ImGui::Text((char*)&item2); ImGui::NextColumn();
      ImGui::Text((char*)&item3); ImGui::NextColumn();
  }
  ImGui::Columns(1);
  ImGui::Separator();
  ImGui::Columns(4,"Exercise2");
  sprintf(name,"%s",getEName(selected[1]));
  ImGui::Text((char*)name); ImGui::NextColumn();
  ImGui::Text("<5"); ImGui::NextColumn();
  ImGui::Text("6-10"); ImGui::NextColumn();
  ImGui::Text("11-20"); ImGui::NextColumn();
  ImGui::Separator();
  for (i = 0; i < 8; i++)
  {
      if (ImGui::Selectable((char*)names2[i], marked2 == i, ImGuiSelectableFlags_SpanAllColumns))
          marked2 = i;
      ImGui::NextColumn();
      sprintf((char*)&item1,"%d",Bcoluna1[i]);
      sprintf((char*)&item2,"%d",Bcoluna2[i]);
      sprintf((char*)&item3,"%d",Bcoluna3[i]);
      ImGui::Text((char*)&item1); ImGui::NextColumn();
      ImGui::Text((char*)&item2); ImGui::NextColumn();
      ImGui::Text((char*)&item3); ImGui::NextColumn();
  }
  ImGui::Columns(1);
  ImGui::Separator();
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

  //////////////////////////////////////////////////////////////////////////////
}
int main(int, char**)
{

    // Setup window
    glfwSetErrorCallback(error_callback);
    width=1280;
    height=720;
    if (!glfwInit())
        return 1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow* window = glfwCreateWindow(width, height, "ImGui OpenGL3 example", NULL, NULL);
    glfwMakeContextCurrent(window);
    gl3wInit();

    // Setup ImGui binding
    ImGui_ImplGlfwGL3_Init(window, true);
    /* Initialize our window. */
    // Load Fonts
    // (there is a default font, this is only if you want to change it. see extra_fonts/README.txt for more details)
    //ImGuiIO& io = ImGui::GetIO();
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("./extra_fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("./extra_fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("./extra_fonts/ProggyClean.ttf", 13.0f);
    //io.Fonts->AddFontFromFileTTF("./extra_fonts/ProggyTiny.ttf", 10.0f);
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());

    bool show_test_window = false;
    bool show_another_window = false;
    bool show_training_window=true;
    char path[1024];
    ImVec4 clear_color = ImColor(114, 144, 154);
#ifdef __APPLE__
    sprintf((char*)path,"%s",utilGetBundleResourcePath("convict","db"));
#else
    getcwd((char*)path,1023);
    strcat((char*)path,"/convict.db");
#endif

    printf("database path[%s]\n",path);
    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        ImGui_ImplGlfwGL3_NewFrame();



        // 1. Show a simple window
        // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
        {
            static float f = 0.0f;
            ImGui::Text("Hello, world!");
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
            ImGui::ColorEdit3("clear color", (float*)&clear_color);
            if (ImGui::Button("Test Window")) show_test_window ^= 1;
            if (ImGui::Button("Another Window")) show_another_window ^= 1;
            if (ImGui::Button("Convict Window")) show_training_window ^= 1;
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }

        if(show_training_window){
          ImGui::SetNextWindowSize(ImVec2(200,100), ImGuiSetCond_FirstUseEver);
          ImGui::Begin("Training", &show_training_window);
          Training(path);
          ImGui::End();
          ImGui::ShowMetricsWindow(&show_training_window);
        }
        // 2. Show another simple window, this time using an explicit Begin/End pair
        if (show_another_window)
        {
            ImGui::SetNextWindowSize(ImVec2(200,100), ImGuiSetCond_FirstUseEver);
            ImGui::Begin("Another Window", &show_another_window);
            ShowAnotherWindow();
            ImGui::End();

        }

        // 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
        if (show_test_window)
        {
            ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
            ImGui::ShowTestWindow(&show_test_window);
        }

        /*{
          ImGui::ShowStyleEditor
        }*/
        // Rendering
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);



        ImGui::Render();
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplGlfwGL3_Shutdown();
    glfwTerminate();
    return 0;
}
