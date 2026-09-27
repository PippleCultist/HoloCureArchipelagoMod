#pragma once
#include "ModuleMain.h"
#include <Aurie/shared.hpp>
#include <YYToolkit/YYTK_Shared.hpp>

enum locationIndexEnum;

void sendAPCheck(CInstance* Self, locationIndexEnum sendLocationIndex);
void loggingCallback(std::string logMessage);

bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
void renderImguiWindow(CInstance* Self);

void initArchipelago();
void loadModImguiMenu();