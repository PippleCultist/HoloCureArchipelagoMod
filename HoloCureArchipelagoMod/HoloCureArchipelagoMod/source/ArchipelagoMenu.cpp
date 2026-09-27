#pragma comment(lib, "d3d11.lib")

#include "ArchipelagoMenu.h"
#include "APCpp/Archipelago.h"
#include "imgui/imgui.h"
#include "imgui/imgui_stdlib.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "ScriptFunctions.h"
#include "CodeEvents.h"
#include "Constants.h"
#include "nlohmann/json.hpp"
#include <unordered_set>
#include <deque>
#include <fstream>

// Data
static ID3D11Device* g_pd3dDevice = nullptr;
static ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
static IDXGISwapChain* g_pSwapChain = nullptr;
static bool                     g_SwapChainOccluded = false;
static UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;
static ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;

ImGuiIO io;

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

std::vector<std::string> apLogList;

std::unordered_map<itemIndexEnum, int> curObtainedItems;

std::deque<itemIndexEnum> itemIndexReceiveQueue;

std::string apIP;
std::string apGame = "HoloCure";
std::string apPlayerName;
std::string apPassword;

bool isConnected = false;
bool isConnecting = false;
bool newConnectSendChecks = false;

bool isGrindyChecksEnabled = false;
bool isStageEnabled = false;
bool isHoloHouseRandomizationEnabled = false;
bool isUniqueEnemyCheckEnabled = false;
int hololiveMemberGoal = 1;
int achievementGoal = 1;
int endGoal = -1;

std::unordered_set<locationIndexEnum> serverObtainedLocationSet;
std::unordered_set<std::string> hololiveMemberWhiteList;

extern CallbackManagerInterface* callbackManagerInterfacePtr;
extern std::map<locationIndexEnum, std::string> locationToNameMap;
extern std::unordered_set<locationIndexEnum> obtainedLocationSet;
extern std::unordered_map<locationIndexEnum, AP_NetworkItem> locationItemHintMap;
extern std::unordered_set<locationIndexEnum> holoHouseRandomizationLocations;
extern std::unordered_set<locationIndexEnum> enemyCheckLocations;
extern std::unordered_map<goalIndexEnum, std::unordered_set<locationIndexEnum>> goalIndexToLocationListMap;
extern std::map<locationIndexEnum, std::vector<std::string>> locationToCharacterNameMap;


// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
	// Setup swap chain
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	UINT createDeviceFlags = 0;
	//createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	D3D_FEATURE_LEVEL featureLevel;
	const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
	HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
	if (res == DXGI_ERROR_UNSUPPORTED) // Try high-performance WARP software driver if hardware is not available.
		res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
	if (res != S_OK)
		return false;

	CreateRenderTarget();
	return true;
}

void CleanupDeviceD3D()
{
	CleanupRenderTarget();
	if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = nullptr; }
	if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = nullptr; }
	if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
}

void CreateRenderTarget()
{
	ID3D11Texture2D* pBackBuffer;
	g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
	g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
	pBackBuffer->Release();
}

void CleanupRenderTarget()
{
	if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; }
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		if (wParam == SIZE_MINIMIZED)
			return 0;
		g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
		g_ResizeHeight = (UINT)HIWORD(lParam);
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	}
	return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}

void locationInfoCallback(std::vector<AP_NetworkItem> locationInfoReceive)
{
	locationItemHintMap.clear();
	for (auto curNetworkItem : locationInfoReceive)
	{
		locationItemHintMap[static_cast<locationIndexEnum>(curNetworkItem.location)] = curNetworkItem;
	}
}

void handleLogMenu()
{
	const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x, main_viewport->WorkPos.y), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(400, 720), ImGuiCond_FirstUseEver);
	ImGui::Begin("Log");

	ImGuiListClipper clipper;
	clipper.Begin(static_cast<int>(apLogList.size()));

	while (clipper.Step())
	{
		for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; row++)
		{
			ImGui::Text(apLogList[row].c_str());
		}
	}

	ImGui::End();
}

bool showPassword = false;
bool hasInvalidField = false;
bool is2xStageTimer = false;
int connectTimer = 0;

void handleGameplayMenu()
{
	const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 800, main_viewport->WorkPos.y), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_FirstUseEver);
	ImGui::Begin("Gameplay");

	ImGui::BeginTabBar("Game");
	
	if (ImGui::BeginTabItem("Connect"))
	{
		connectTimer++;
		if (connectTimer >= 60)
		{
			RValue saveDir;
			g_ModuleInterface->GetBuiltin("game_save_id", nullptr, NULL_INDEX, saveDir);
			if (std::filesystem::exists(saveDir.ToString() + "/ArchipelagoConnect.txt"))
			{
				std::ifstream inFile;
				inFile.open(saveDir.ToString() + "/ArchipelagoConnect.txt");

				std::getline(inFile, apPlayerName);
				
				// TODO: Look into if there's a way to determine empty password
				std::string tempPassword;
				std::getline(inFile, tempPassword);

				std::getline(inFile, apIP);

				inFile.close();

				std::filesystem::remove(saveDir.ToString() + "/ArchipelagoConnect.txt");
			}
			connectTimer = 0;
		}
		ImGui::InputTextWithHint("IP", "localhost:38281", &apIP);
		ImGui::InputText("Player Name", &apPlayerName);
		ImGui::InputText("Password", &apPassword, showPassword ? ImGuiInputTextFlags_None : ImGuiInputTextFlags_Password);
		ImGui::Checkbox("Show Password", &showPassword);

		if (hasInvalidField)
		{
			ImGui::TextColored(ImVec4(1, 0, 0, 1), "Please input a non empty IP/Player Name");
		}

		if (ImGui::Button("Connect"))
		{
			if (apIP.empty() || apPlayerName.empty())
			{
				hasInvalidField = true;
			}
			else
			{
				hasInvalidField = false;
				initArchipelago();
			}
		}
		ImGui::EndTabItem();
	}

	if (ImGui::BeginTabItem("Game Options"))
	{
		ImGui::Checkbox("Enable 2x Stage Timer", &is2xStageTimer);
		ImGui::EndTabItem();
	}

	ImGui::EndTabBar();

	ImGui::End();
}

void sendAPCheck(CInstance* Self, locationIndexEnum sendLocationIndex)
{
	obtainedLocationSet.insert(sendLocationIndex);
	RValue playerSave = g_ModuleInterface->CallBuiltin("variable_global_get", { "PlayerSave" });
	RValue archipelagoChecks = g_ModuleInterface->CallBuiltin("ds_map_find_value", { playerSave, "archipelagoChecks" });
	if (archipelagoChecks.m_Kind == VALUE_UNDEFINED)
	{
		RValue apCheckStruct;
		g_RunnerInterface.StructCreate(&apCheckStruct);
		g_ModuleInterface->CallBuiltin("ds_map_set", { playerSave, "archipelagoChecks", apCheckStruct });
		archipelagoChecks = apCheckStruct;
	}

	std::string checkStr = std::format("ap_{}", static_cast<int>(sendLocationIndex));

	if (!g_ModuleInterface->CallBuiltin("struct_exists", { archipelagoChecks, checkStr.c_str() }).ToBoolean())
	{
		g_ModuleInterface->CallBuiltin("struct_set", { archipelagoChecks, checkStr.c_str(), 1 });
		RValue result;
		origSavePlayerSaveScript(Self, nullptr, result, 0, nullptr);
	}
	if (serverObtainedLocationSet.contains(sendLocationIndex))
	{
		return;
	}
	AP_SendItem(sendLocationIndex);
}

bool isForceCheck = false;
bool isLocationHint = false;
bool isProgressionItem = false;
bool isUsefulItem = false;
bool isTrapItem = false;
bool isOnlyShowGoal = false;

void handleArchipelagoMenu(CInstance* Self)
{
	const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 400, main_viewport->WorkPos.y), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(400, 720), ImGuiCond_FirstUseEver);
	ImGui::Begin("Archipelago Window");

	ImGui::BeginTabBar("Archipelago");
	if (ImGui::BeginTabItem("Checks"))
	{
		//	ImGuiListClipper clipper;
		//	clipper.Begin(locationToNameMap.size());

//		ImGui::Checkbox("Toggle Force Check", &isForceCheck);
		ImGui::Checkbox("Toggle Location Hints", &isLocationHint);
		ImGui::Checkbox("Filter Progression Item", &isProgressionItem);
		ImGui::Checkbox("Filter Useful Item", &isUsefulItem);
		ImGui::Checkbox("Filter Trap Item", &isTrapItem);
		ImGui::Checkbox("Only Show Goal Locations", &isOnlyShowGoal);
		int itemBitFlag = (isProgressionItem ? 0b1 : 0) | (isUsefulItem ? 0b10 : 0) | (isTrapItem ? 0b100 : 0);
		// TODO: Try to figure out a way to not need an extra loop for this. Maybe precalculate it somewhere?
		int obtainedCount = 0;
		int count = 0;
		for (auto& locationPair : locationToNameMap)
		{
			if (!isGrindyChecksEnabled && grindyLocations.contains(locationPair.first))
			{
				continue;
			}
			if (!isStageEnabled && (endGoal != goalIndexEnum_BeatAllNormalStages && endGoal != goalIndexEnum_BeatAllHardStages) && (stageLocations.contains(locationPair.first) || enemyCheckLocations.contains(locationPair.first)))
			{
				continue;
			}
			if (!isHoloHouseRandomizationEnabled && holoHouseRandomizationLocations.contains(locationPair.first))
			{
				continue;
			}
			if (!isUniqueEnemyCheckEnabled && enemyCheckLocations.contains(locationPair.first))
			{
				continue;
			}
			if (!hololiveMemberWhiteList.empty() && hololiveMemberWhiteList.size() != 47 && locationToCharacterNameMap.contains(locationPair.first))
			{
				bool isInWhiteList = false;
				for (auto& curCharName : locationToCharacterNameMap[locationPair.first])
				{
					if (hololiveMemberWhiteList.contains(curCharName))
					{
						isInWhiteList = true;
						break;
					}
				}

				if (!isInWhiteList)
				{
					continue;
				}
			}
			if (!locationItemHintMap.empty() && (locationItemHintMap[locationPair.first].flags & itemBitFlag) != itemBitFlag)
			{
				continue;
			}
			if (endGoal != -1 && isOnlyShowGoal && !goalIndexToLocationListMap[static_cast<goalIndexEnum>(endGoal)].contains(locationPair.first))
			{
				continue;
			}
			if (obtainedLocationSet.contains(locationPair.first))
			{
				obtainedCount++;
			}
			count++;
		}
		ImGui::Text("%d / %d", obtainedCount, count);

		if (ImGui::BeginTable("ChecksTable", isLocationHint ? 2 : 1, ImGuiTableFlags_ScrollY | ImGuiTableFlags_ScrollX))
		{
			// TODO: Fix this UI
			int curRow = 0;
			for (auto& locationPair : locationToNameMap)
			{
				if (!isGrindyChecksEnabled && grindyLocations.contains(locationPair.first))
				{
					continue;
				}
				if (!isStageEnabled && (endGoal != goalIndexEnum_BeatAllNormalStages && endGoal != goalIndexEnum_BeatAllHardStages) && (stageLocations.contains(locationPair.first) || enemyCheckLocations.contains(locationPair.first)))
				{
					continue;
				}
				if (!isHoloHouseRandomizationEnabled && holoHouseRandomizationLocations.contains(locationPair.first))
				{
					continue;
				}
				if (!isUniqueEnemyCheckEnabled && enemyCheckLocations.contains(locationPair.first))
				{
					continue;
				}
				if (!hololiveMemberWhiteList.empty() && hololiveMemberWhiteList.size() != 47 && locationToCharacterNameMap.contains(locationPair.first))
				{
					bool isInWhiteList = false;
					for (auto& curCharName : locationToCharacterNameMap[locationPair.first])
					{
						if (hololiveMemberWhiteList.contains(curCharName))
						{
							isInWhiteList = true;
							break;
						}
					}

					if (!isInWhiteList)
					{
						continue;
					}
				}
				if (!locationItemHintMap.empty() && (locationItemHintMap[locationPair.first].flags & itemBitFlag) != itemBitFlag)
				{
					continue;
				}
				if (endGoal != -1 && isOnlyShowGoal && !goalIndexToLocationListMap[static_cast<goalIndexEnum>(endGoal)].contains(locationPair.first))
				{
					continue;
				}
				ImGui::TableNextRow();
				//ImGui::TableNextColumn();
				ImGui::TableSetColumnIndex(0);
				if (isForceCheck)
				{
					if (ImGui::Button(std::format("Send##{}", curRow).c_str()))
					{
						sendAPCheck(Self, locationPair.first);
					}
					ImGui::SameLine();
				}
				ImVec4 textColor;
				if (obtainedLocationSet.contains(locationPair.first))
				{
					textColor = ImVec4(0, 1, 0, 1);
				}
				else if (serverObtainedLocationSet.contains(locationPair.first))
				{
					textColor = ImVec4(1, .65, 0, 1);
				}
				else
				{
					textColor = ImVec4(1, 0, 0, 1);
				}
				ImGui::TextColored(textColor, "%s", locationPair.second.c_str());

				if (isLocationHint && !locationItemHintMap.empty())
				{
					ImGui::Text("(%s) %s", locationItemHintMap[locationPair.first].playerName.c_str(), locationItemHintMap[locationPair.first].itemName.c_str());
				}

				curRow++;
			}
			ImGui::EndTable();
		}
		ImGui::EndTabItem();
	}

	if (ImGui::BeginTabItem("Items"))
	{
		for (auto& curItem : curObtainedItems)
		{
			ImGui::Text("%s %d", itemToNameMap[curItem.first].c_str(), curItem.second);
		}
		ImGui::EndTabItem();
	}

	ImGui::EndTabBar();

	ImGui::End();
}

void handleImGUI(CInstance* Self)
{
	handleLogMenu();
	handleGameplayMenu();
	handleArchipelagoMenu(Self);
}

void loggingCallback(std::string logMessage)
{
	apLogList.push_back(logMessage);
	callbackManagerInterfacePtr->LogToFile(MODNAME, "%s", logMessage.c_str());
}

void itemClearCallback()
{
	loggingCallback("Item Clear");
	curObtainedItems.clear();
}

void itemReceiveCallback(int64_t itemID, bool isNotify)
{
	bool hasObtainedValidItem = true;

	itemIndexEnum itemIndexID = static_cast<itemIndexEnum>(itemID);

	if (itemID >= itemIndexEnum_HoloHouse && itemID <= itemIndexEnum_TimeStage1)
	{
		// Stages + HoloCoin
		itemIndexReceiveQueue.push_back(itemIndexID);
	}
	else if (itemID >= itemIndexEnum_AmeliaWatson && itemID <= itemIndexEnum_HimemoriLuna)
	{
		// Characters
		itemIndexReceiveQueue.push_back(itemIndexID);
	}
	else if (itemID >= itemIndexEnum_WamyWater && itemID <= itemIndexEnum_OwlDagger)
	{
		// Weapons
		itemIndexReceiveQueue.push_back(itemIndexID);
	}
	else if (itemID >= itemIndexEnum_EnergyDrink && itemID <= itemIndexEnum_PromiseTiara)
	{
		// Items
		itemIndexReceiveQueue.push_back(itemIndexID);
	}
	else if (itemID >= itemIndexEnum_SpecialAttackShopUpgrade && itemID <= itemIndexEnum_MarketingProgressiveShopUpgrade)
	{
		// Shop
		itemIndexReceiveQueue.push_back(itemIndexID);
	}
	else if (itemID >= itemIndexEnum_StandardSoil && itemID <= itemIndexEnum_GarlicSeed)
	{
		// HoloHouse Farm
		itemIndexReceiveQueue.push_back(itemIndexID);
	}
	else if (itemID >= itemIndexEnum_ProgressiveRod && itemID <= itemIndexEnum_ProgressivePickaxe)
	{
		// HoloHouse Forge
		itemIndexReceiveQueue.push_back(itemIndexID);
	}
	else
	{
		hasObtainedValidItem = false;
	}

	if (!hasObtainedValidItem)
	{
		loggingCallback(std::format("Unrecognized item id {} received", itemID));
	}
	else
	{
		loggingCallback(std::format("{} received", itemToNameMap[itemIndexID]));
	}
}

void locationCheckedCallback(int64_t locationID)
{
	locationIndexEnum locationIndexID = static_cast<locationIndexEnum>(locationID);
	serverObtainedLocationSet.insert(locationIndexID);
	loggingCallback(std::format("{} server checked", locationToNameMap[locationIndexID].c_str()));
}

void loadModImguiMenu()
{
	if (g_pd3dDevice == nullptr)
	{
		// Create application window
		//ImGui_ImplWin32_EnableDpiAwareness();
		WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"HoloCure Archipelago Mod", nullptr };
		::RegisterClassExW(&wc);
		HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"HoloCure Archipelago Mod", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 720, nullptr, nullptr, wc.hInstance, nullptr);
		// Initialize Direct3D
		if (!CreateDeviceD3D(hwnd))
		{
			CleanupDeviceD3D();
			::UnregisterClassW(wc.lpszClassName, wc.hInstance);
			return;
		}

		// Show the window
		::ShowWindow(hwnd, SW_SHOWDEFAULT);
		::UpdateWindow(hwnd);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		ImGui::StyleColorsDark();
		// Setup Platform/Renderer backends
		ImGui_ImplWin32_Init(hwnd);
		ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
	}
}

void renderImguiWindow(CInstance* Self)
{
	AP_ConnectionStatus connectStatus = AP_GetConnectionStatus();
	isConnected = (connectStatus == AP_ConnectionStatus::Authenticated);

//	if (connectStatus == AP_ConnectionStatus::Disconnected || connectStatus == AP_ConnectionStatus::ConnectionRefused)
	{
//		isConnecting = false;
	}

	if (isConnected && AP_IsMessagePending())
	{
		do
		{
			AP_Message* message = AP_GetLatestMessage();
			loggingCallback(message->text);
			AP_ClearLatestMessage();
		} while (AP_IsMessagePending());
	}

	if (g_pd3dDevice == nullptr)
	{
		return;
	}

	{
		// Poll and handle messages (inputs, window resize, etc.)
		// See the WndProc() function below for our to dispatch events to the Win32 backend.
		MSG msg;
		while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
			{

			}
		}

		// Handle window being minimized or screen locked
		if (g_SwapChainOccluded && g_pSwapChain->Present(0, DXGI_PRESENT_TEST) == DXGI_STATUS_OCCLUDED)
		{
			::Sleep(10);
			return;
		}
		g_SwapChainOccluded = false;

		// Handle window resize (we don't resize directly in the WM_SIZE handler)
		if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
		{
			CleanupRenderTarget();
			g_pSwapChain->ResizeBuffers(0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
			g_ResizeWidth = g_ResizeHeight = 0;
			CreateRenderTarget();
		}

		// Start the Dear ImGui frame
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		handleImGUI(Self);

		// Rendering
		ImGui::Render();
		const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
		g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
		g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		// Present
		HRESULT hr = g_pSwapChain->Present(1, 0);   // Present with vsync
		//HRESULT hr = g_pSwapChain->Present(0, 0); // Present without vsync
		g_SwapChainOccluded = (hr == DXGI_STATUS_OCCLUDED);
	}
}

void slotDataEndGoalCallback(int slotData)
{
	loggingCallback("end goal: " + std::to_string(slotData));
	endGoal = slotData;
}

void slotDataGrindyChecksCallback(int slotData)
{
	loggingCallback("grindy checks: " + std::to_string(slotData));
	isGrindyChecksEnabled = slotData;
}

void slotDataStageEnabledCallback(int slotData)
{
	loggingCallback("stage enabled: " + std::to_string(slotData));
	isStageEnabled = slotData;
}

void slotDataEnableHoloHouseRandomizationCallback(int slotData)
{
	loggingCallback("Holo House randomization: " + std::to_string(slotData));
	isHoloHouseRandomizationEnabled = slotData;
}

void slotDataEnableUniqueEnemyChecksCallback(int slotData)
{
	loggingCallback("Unique Enemy Check: " + std::to_string(slotData));
	isUniqueEnemyCheckEnabled = slotData;
}

void slotDataHololiveMemberWhitelistCallback(std::string slotData)
{
	loggingCallback("Hololive Member Whitelist: " + slotData);
	hololiveMemberWhiteList.clear();
	nlohmann::json whiteList = nlohmann::json::parse(slotData);
	int arrLen = whiteList.size();
	for (int i = 0; i < arrLen; i++)
	{
		hololiveMemberWhiteList.insert(whiteList[i].get<std::string>());
	}
}

void slotDataHololiveMemberGoalCallback(int slotData)
{
	loggingCallback("Hololive Member Goal: " + std::to_string(slotData));
	hololiveMemberGoal = slotData;
}

void slotDataAchievementGoalCallback(int slotData)
{
	loggingCallback("Achievement Goal: " + std::to_string(slotData));
	achievementGoal = slotData;
}

void initArchipelago()
{
	AP_Shutdown();
	callbackManagerInterfacePtr->LogToFile(MODNAME, "Init AP");
	AP_Init(apIP.c_str(), apGame.c_str(), apPlayerName.c_str(), apPassword.c_str());

	AP_SetItemClearCallback(itemClearCallback);
	AP_SetItemRecvCallback(itemReceiveCallback);
	AP_SetLocationCheckedCallback(locationCheckedCallback);
	AP_SetLocationInfoCallback(locationInfoCallback);

	AP_RegisterSlotDataIntCallback("end_goal", slotDataEndGoalCallback);
	AP_RegisterSlotDataIntCallback("grindy_checks", slotDataGrindyChecksCallback);
	AP_RegisterSlotDataIntCallback("enable_stage", slotDataStageEnabledCallback);
	AP_RegisterSlotDataIntCallback("enable_holo_house_randomization", slotDataEnableHoloHouseRandomizationCallback);
	AP_RegisterSlotDataIntCallback("enable_unique_enemy_checks", slotDataEnableUniqueEnemyChecksCallback);
	AP_RegisterSlotDataRawCallback("hololive_member_whitelist", slotDataHololiveMemberWhitelistCallback);
	AP_RegisterSlotDataIntCallback("hololive_member_goal", slotDataHololiveMemberGoalCallback);
	AP_RegisterSlotDataIntCallback("achievement_goal", slotDataAchievementGoalCallback);

	AP_SetLoggingCallback(loggingCallback);

//	isConnecting = true;
	AP_Start();

	newConnectSendChecks = true;
}