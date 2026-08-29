#pragma comment(lib, "d3d11.lib")

#include "ArchipelagoMenu.h"
#include "APCpp/Archipelago.h"
#include "imgui/imgui.h"
#include "imgui/imgui_stdlib.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "ScriptFunctions.h"
#include <unordered_set>
#include <deque>

std::unordered_map<itemIndexEnum, std::string> itemToNameMap
{
	{ itemIndexEnum_HoloHouse, "HoloHouse" },
	{ itemIndexEnum_HoloCoin, "HoloCoin" },
	{ itemIndexEnum_ProgressiveStage, "Progressive Stage" },
	{ itemIndexEnum_TimeStage1, "Time Stage 1" },
	{ itemIndexEnum_AmeliaWatson, "Amelia Watson" },
	{ itemIndexEnum_GawrGura, "Gawr Gura" },
	{ itemIndexEnum_NinomaeInanis, "Ninomae Inanis" },
	{ itemIndexEnum_TakanashiKiara, "Takanashi Kiara" },
	{ itemIndexEnum_MoriCalliope, "Mori Calliope" },
	{ itemIndexEnum_HakosBaelz, "Hakos Baelz" },
	{ itemIndexEnum_OuroKronii, "Ouro Kronii" },
	{ itemIndexEnum_CeresFauna, "Ceres Fauna" },
	{ itemIndexEnum_NanashiMumei, "Nanashi Mumei" },
	{ itemIndexEnum_TsukumoSana, "Tsukumo Sana" },
	{ itemIndexEnum_IRyS, "IRyS" },
	{ itemIndexEnum_ShirakamiFubuki, "Shirakami Fubuki" },
	{ itemIndexEnum_OokamiMio, "Ookami Mio" },
	{ itemIndexEnum_NekomataOkayu, "Nekomata Okayu" },
	{ itemIndexEnum_InugamiKorone, "Inugami Korone" },
	{ itemIndexEnum_TokinoSora, "Tokino Sora" },
	{ itemIndexEnum_AZki, "AZki" },
	{ itemIndexEnum_RobocoSan, "Roboco-san" },
	{ itemIndexEnum_HoshimachiSuisei, "Hoshimachi Suisei" },
	{ itemIndexEnum_SakuraMiko, "Sakura Miko" },
	{ itemIndexEnum_AkaiHaato, "Akai Haato" },
	{ itemIndexEnum_YozoraMel, "Yozora Mel" },
	{ itemIndexEnum_NatsuiroMatsuri, "Natsuiro Matsuri" },
	{ itemIndexEnum_AkiRosenthal, "Aki Rosenthal" },
	{ itemIndexEnum_YuzukiChoco, "Yuzuki Choco" },
	{ itemIndexEnum_OozoraSubaru, "Oozora Subaru" },
	{ itemIndexEnum_MurasakiShion, "Murasaki Shion" },
	{ itemIndexEnum_NakiriAyame, "Nakiri Ayame" },
	{ itemIndexEnum_MinatoAqua, "Minato Aqua" },
	{ itemIndexEnum_MoonaHoshinova, "Moona Hoshinova" },
	{ itemIndexEnum_AiraniIofifteen, "Airani Iofifteen" },
	{ itemIndexEnum_AyundaRisu, "Ayunda Risu" },
	{ itemIndexEnum_KureijiOllie, "Kureiji Ollie" },
	{ itemIndexEnum_PavoliaReine, "Pavolia Reine" },
	{ itemIndexEnum_AnyaMelfissa, "Anya Melfissa" },
	{ itemIndexEnum_KoboKanaeru, "Kobo Kanaeru" },
	{ itemIndexEnum_KaelaKovalskia, "Kaela Kovalskia" },
	{ itemIndexEnum_VestiaZeta, "Vestia Zeta" },
	{ itemIndexEnum_UsadaPekora, "Usada Pekora" },
	{ itemIndexEnum_ShiroganeNoel, "Shirogane Noel" },
	{ itemIndexEnum_ShiranuiFlare, "Shiranui Flare" },
	{ itemIndexEnum_HoushouMarine, "Houshou Marine" },
	{ itemIndexEnum_KiryuCoco, "Kiryu Coco" },
	{ itemIndexEnum_AmaneKanata, "Amane Kanata" },
	{ itemIndexEnum_TsunomakiWatame, "Tsunomaki Watame" },
	{ itemIndexEnum_TokoyamiTowa, "Tokoyami Towa" },
	{ itemIndexEnum_HimemoriLuna, "Himemori Luna" },
	{ itemIndexEnum_WamyWater, "Wamy Water" },
	{ itemIndexEnum_PsychoAxe, "Psycho Axe" },
	{ itemIndexEnum_XPotato, "X-Potato" },
	{ itemIndexEnum_BounceBall, "Bounce Ball" },
	{ itemIndexEnum_Sausage, "Sausage" },
	{ itemIndexEnum_Glowstick, "Glowstick" },
	{ itemIndexEnum_SpiderCooking, "Spider Cooking" },
	{ itemIndexEnum_PlugTypeAsacoco, "Plug Type Asacoco" },
	{ itemIndexEnum_BLBook, "BL Book" },
	{ itemIndexEnum_EliteLava, "Elite Lava Bucket" },
	{ itemIndexEnum_HoloBomb, "Holo Bomb" },
	{ itemIndexEnum_CuttingBoard, "Cutting Board" },
	{ itemIndexEnum_FanBeam, "Fan Beam" },
	{ itemIndexEnum_IdolSong, "Idol Song" },
	{ itemIndexEnum_CEOTears, "CEO's Tears" },
	{ itemIndexEnum_ENCurse, "EN's Curse" },
	{ itemIndexEnum_OwlDagger, "Owl Dagger" },
	{ itemIndexEnum_EnergyDrink, "Energy Drink" },
	{ itemIndexEnum_Plushie, "Plushie" },
	{ itemIndexEnum_Limiter, "Limiter" },
	{ itemIndexEnum_Beetle, "Beetle" },
	{ itemIndexEnum_Shackles, "Kusogaki Shackles" },
	{ itemIndexEnum_NinjaHeadband, "Ninja Headband" },
	{ itemIndexEnum_ChickenFeather, "Chicken's Feather" },
	{ itemIndexEnum_RavenFeather, "Raven Feather" },
	{ itemIndexEnum_BodyPillow, "Body Pillow" },
	{ itemIndexEnum_FullMeal, "Full Meal" },
	{ itemIndexEnum_PikiPikiPiman, "Piki Piki Piman" },
	{ itemIndexEnum_NurseHorn, "Nurse's Horn" },
	{ itemIndexEnum_Headphones, "Headphones" },
	{ itemIndexEnum_UberSheep, "Uber Sheep" },
	{ itemIndexEnum_KnightlyMilk, "Knightly Milk" },
	{ itemIndexEnum_Sake, "Sake" },
	{ itemIndexEnum_FaceMask, "Face Mask" },
	{ itemIndexEnum_CreditCard, "Credit Card" },
	{ itemIndexEnum_GorillaPaw, "Gorilla's Paw" },
	{ itemIndexEnum_SuperChattoTime, "Super Chatto Time!" },
	{ itemIndexEnum_Halu, "Halu" },
	{ itemIndexEnum_InjectionTypeAsacoco, "Injection Type Asacoco" },
	{ itemIndexEnum_IdolCostume, "Idol Costume" },
	{ itemIndexEnum_GWSPill, "GWS Pill" },
	{ itemIndexEnum_JustBandage, "Just Bandage" },
	{ itemIndexEnum_Breastplate, "Breastplate" },
	{ itemIndexEnum_StudyGlasses, "Study Glasses" },
	{ itemIndexEnum_BlacksmithGear, "Blacksmith's Gear" },
	{ itemIndexEnum_HopeSoda, "Hope Soda" },
	{ itemIndexEnum_StolenPiggyBank, "Stolen Piggy Bank" },
	{ itemIndexEnum_CandyKingdomSweets, "Candy Kingdom Sweets" },
	{ itemIndexEnum_ResearcherCoat, "Researcher's Coat" },
	{ itemIndexEnum_Membership, "Membership" },
	{ itemIndexEnum_DevilHat, "Devil Hat" },
	{ itemIndexEnum_FocusShades, "Focus Shades" },
	{ itemIndexEnum_CorporationPin, "Corporation Pin" },
	{ itemIndexEnum_PromiseTiara, "Promise Tiara" },
	{ itemIndexEnum_SpecialAttackShopUpgrade, "Special Attack Shop Upgrade" },
	{ itemIndexEnum_GrowthProgressiveShopUpgrade, "Growth Progressive Shop Upgrade" },
	{ itemIndexEnum_RerollProgressiveShopUpgrade, "Reroll Progressive Shop Upgrade" },
	{ itemIndexEnum_EliminateProgressiveShopUpgrade, "Eliminate Progressive Shop Upgrade" },
	{ itemIndexEnum_HoldProgressiveShopUpgrade, "Hold Progressive Shop Upgrade" },
	{ itemIndexEnum_CustomizeShopUpgrade, "Customize Shop Upgrade" },
	{ itemIndexEnum_SupportsShopUpgrade, "Supports Shop Upgrade" },
	{ itemIndexEnum_MaterialShopUpgrade, "Material Find Shop Upgrade" },
	{ itemIndexEnum_StampsShopUpgrade, "Stamps Shop Upgrade" },
	{ itemIndexEnum_EnchantmentsShopUpgrade, "Enchantments Shop Upgrade" },
	{ itemIndexEnum_FandomShopUpgrade, "Fandom Shop Upgrade" },
	{ itemIndexEnum_FanLettersShopUpgrade, "Fan Letters Shop Upgrade" },
	{ itemIndexEnum_MaxHPProgressiveShopUpgrade, "Max HP Progressive Shop Upgrade" },
	{ itemIndexEnum_ATKProgressiveShopUpgrade, "ATK Progressive Shop Upgrade" },
	{ itemIndexEnum_SPDProgressiveShopUpgrade, "SPD Progressive Shop Upgrade" },
	{ itemIndexEnum_CritProgressiveShopUpgrade, "Crit Progressive Shop Upgrade" },
	{ itemIndexEnum_PickUpProgressiveShopUpgrade, "Pick Up Range Progressive Shop Upgrade" },
	{ itemIndexEnum_HasteProgressiveShopUpgrade, "Haste Up Progressive Shop Upgrade" },
	{ itemIndexEnum_RegenProgressiveShopUpgrade, "Regen Progressive Shop Upgrade" },
	{ itemIndexEnum_DefenseProgressiveShopUpgrade, "Defense Progressive Shop Upgrade" },
	{ itemIndexEnum_SpecialCooldownProgressiveShopUpgrade, "Special Cooldown Reduction Progressive Shop Upgrade" },
	{ itemIndexEnum_SkillUpProgressiveShopUpgrade, "Skill Up Progressive Shop Upgrade" },
	{ itemIndexEnum_EXPGainProgressiveShopUpgrade, "EXP Gain Up Progressive Shop Upgrade" },
	{ itemIndexEnum_FoodDropProgressiveShopUpgrade, "Food Drops Up Progressive Shop Upgrade" },
	{ itemIndexEnum_MoneyGainProgressiveShopUpgrade, "Money Gain Up Progressive Shop Upgrade" },
	{ itemIndexEnum_EnhancementProgressiveShopUpgrade, "Enhancement Rate Up Progressive Shop Upgrade" },
	{ itemIndexEnum_MarketingProgressiveShopUpgrade, "Marketing Up Progressive Shop Upgrade" },
};

std::unordered_set<locationIndexEnum> grindyLocations
{
	locationIndexEnum_AmeliaWastonGachikoi,
	locationIndexEnum_GawrGuraGachikoi,
	locationIndexEnum_NinomaeInanisGachikoi,
	locationIndexEnum_TakanshiKiaraGachikoi,
	locationIndexEnum_MoriCalliopeGachikoi,
	locationIndexEnum_HakosBaelzGachikoi,
	locationIndexEnum_OuroKroniiGachikoi,
	locationIndexEnum_CeresFaunaGachikoi,
	locationIndexEnum_NanashiMumeiGachikoi,
	locationIndexEnum_TsukumoSanaGachikoi,
	locationIndexEnum_IRySGachikoi,
	locationIndexEnum_ShirakamiFubukiGachikoi,
	locationIndexEnum_OokamiMioGachikoi,
	locationIndexEnum_NekomataOkayuGachikoi,
	locationIndexEnum_InugamiKoroneGachikoi,
	locationIndexEnum_TokinoSoraGachikoi,
	locationIndexEnum_AZkiGachikoi,
	locationIndexEnum_RobocoGachikoi,
	locationIndexEnum_HoshimachiSuiseiGachikoi,
	locationIndexEnum_SakuraMikoGachikoi,
	locationIndexEnum_AkaiHaatoGachikoi,
	locationIndexEnum_YozoraMelGachikoi,
	locationIndexEnum_NatsuiroMatsuriGachikoi,
	locationIndexEnum_AkiRosenthalGachikoi,
	locationIndexEnum_YuzukiChocoGachikoi,
	locationIndexEnum_OozoraSubaruGachikoi,
	locationIndexEnum_MurasakiShionGachikoi,
	locationIndexEnum_NakiriAyameGachikoi,
	locationIndexEnum_MinatoAquaGachikoi,
	locationIndexEnum_MoonaHoshinovaGachikoi,
	locationIndexEnum_AiraniIofifteenGachikoi,
	locationIndexEnum_AyundaRisuGachikoi,
	locationIndexEnum_KureijiOllieGachikoi,
	locationIndexEnum_PavoliaReineGachikoi,
	locationIndexEnum_AnyaMelfissaGachikoi,
	locationIndexEnum_KoboKanaeruGachikoi,
	locationIndexEnum_KaelaKovalskiaGachikoi,
	locationIndexEnum_VestiaZetaGachikoi,
	locationIndexEnum_UsadaPekoraGachikoi,
	locationIndexEnum_ShiroganeNoelGachikoi,
	locationIndexEnum_ShiranuiFlareGachikoi,
	locationIndexEnum_HoushouMarineGachikoi,
	locationIndexEnum_KiryuCocoGachikoi,
	locationIndexEnum_AmaneKanataGachikoi,
	locationIndexEnum_TsunomakiWatameGachikoi,
	locationIndexEnum_TokoyamiTowaGachikoi,
	locationIndexEnum_HimemoriLunaGachikoi,
	locationIndexEnum_ClearTowerOfSuffering,
	locationIndexEnum_GetSomeHelp,
};

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
std::string apGame;
std::string apPlayerName;
std::string apPassword;

bool isConnected = false;
bool isConnecting = false;
bool newConnectSendChecks = false;

bool isGrindyChecksEnabled = false;

extern CallbackManagerInterface* callbackManagerInterfacePtr;
extern std::map<locationIndexEnum, std::string> locationToNameMap;
extern std::unordered_set<locationIndexEnum> obtainedLocationSet;

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

void handleLogMenu()
{
	ImGui::Begin("Log");

//	if (ImGui::BeginTable("LogTable", 1))
	{
		ImGuiListClipper clipper;
		clipper.Begin(apLogList.size());

		while (clipper.Step())
		{
			for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; row++)
			{
//				ImGui::TableNextRow();
				ImGui::Text(apLogList[row].c_str());
			}
		}

//		ImGui::EndTable();
	}

	ImGui::End();
}

void handleConnectMenu()
{
	ImGui::Begin("Connect");

	ImGui::InputText("IP", &apIP);
	ImGui::InputText("Game", &apGame);
	ImGui::InputText("Player Name", &apPlayerName);
	ImGui::InputText("Password", &apPassword);
	if (isConnected || isConnecting)
	{
		ImGui::BeginDisabled();
	}

	if (ImGui::Button("Connect"))
	{
		initArchipelago();
	}

	if (isConnected || isConnecting)
	{
		ImGui::EndDisabled();
	}

	ImGui::End();
}

void sendAPCheck(CInstance* Self, locationIndexEnum sendLocationIndex)
{
	AP_SendItem(sendLocationIndex);
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
	
	g_ModuleInterface->CallBuiltin("struct_set", { archipelagoChecks, std::format("ap_{}", static_cast<int>(sendLocationIndex)).c_str(), 1});
	RValue result;
	origSavePlayerSaveScript(Self, nullptr, result, 0, nullptr);
}

bool isForceCheck = false;

void handleCheckMenu(CInstance* Self)
{
	ImGui::Begin("Checks");
//	ImGuiListClipper clipper;
//	clipper.Begin(locationToNameMap.size());

	ImGui::Checkbox("Toggle Force Check", &isForceCheck);
	ImGui::Text("%d / %d", obtainedLocationSet.size(), locationToNameMap.size());

	if (ImGui::BeginTable("ChecksTable", 1, ImGuiTableFlags_ScrollY))
	{
		int curRow = 0;
		for (auto& locationPair : locationToNameMap)
		{
			if (!isGrindyChecksEnabled && grindyLocations.contains(locationPair.first))
			{
				continue;
			}
			ImGui::TableNextRow();
			ImGui::TableNextColumn();
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
			else
			{
				textColor = ImVec4(1, 0, 0, 1);
			}
			ImGui::TextColored(textColor, "%s", locationPair.second.c_str());
			curRow++;
		}
		ImGui::EndTable();
	}

	ImGui::End();
}

void handleImGUI(CInstance* Self)
{
	handleLogMenu();
	handleConnectMenu();
	handleCheckMenu(Self);
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
	obtainedLocationSet.insert(locationIndexID);
	loggingCallback(std::format("{} checked", locationToNameMap[locationIndexID].c_str()));
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
	isConnected = (connectStatus == AP_ConnectionStatus::Connected);

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

void slotDataGrindyChecksCallback(int slotData)
{
	isGrindyChecksEnabled = slotData;
}

void initArchipelago()
{
	callbackManagerInterfacePtr->LogToFile(MODNAME, "Init AP");
	AP_Init(apIP.c_str(), apGame.c_str(), apPlayerName.c_str(), apPassword.c_str());

	AP_SetItemClearCallback(itemClearCallback);
	AP_SetItemRecvCallback(itemReceiveCallback);
	AP_SetLocationCheckedCallback(locationCheckedCallback);

	AP_RegisterSlotDataIntCallback("grindy_checks", slotDataGrindyChecksCallback);

	AP_SetLoggingCallback(loggingCallback);

//	isConnecting = true;
	AP_Start();

	newConnectSendChecks = true;
}