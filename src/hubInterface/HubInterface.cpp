#include "HubInterface.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui-node/imgui_node_editor.h"
#include "imgui-node/imgui_node_editor_internal.h"


namespace ed = ax::NodeEditor;
void RenderMainDockSpace()
{
    static bool dockspaceOpen = true;
    static bool opt_fullscreen = true;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    ImGui::Begin("MainDockSpace", &dockspaceOpen, window_flags);

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // DockSpace
    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

    ImGui::End();
}


HubInterface::HubInterface()
{    

    glfwInit();
    window = glfwCreateWindow(1280, 720, "PulseHub", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    gladLoadGL(); // ou glewInit() selon ton loader

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io; 

    ImFont* dmSansFont = io.Fonts->AddFontFromFileTTF("D:/PulseSoftware/PulseForgeProject/PulseEngine/PulseEngineEditor/fonts/EngineFont.ttf", 18.0f);
    io.FontDefault = dmSansFont;    
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.IniFilename = "HubGui.ini";
    
    ImGui_ImplGlfw_InitForOpenGL(window, true); 
    ImGui_ImplOpenGL3_Init("#version 460");

    ImGui::StyleColorsDark(); 
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 6.0f;
    style.FrameRounding = 5.0f;
    style.GrabRounding = 5.0f;
    style.ScrollbarRounding = 6.0f;
    style.ChildRounding = 6.0f;
    
    style.FrameBorderSize = 1.0f;
    style.WindowBorderSize = 1.0f;
    style.TabBorderSize = 1.0f;
    
    style.WindowPadding = ImVec2(12.0f, 12.0f);
    style.FramePadding = ImVec2(8.0f, 6.0f);
    style.ItemSpacing = ImVec2(10.0f, 8.0f);
    style.ItemInnerSpacing = ImVec2(8.0f, 6.0f);
    
    
ImVec4 orangeAccent      = ImVec4(1.00f, 0.55f, 0.20f, 1.00f); // Warm orange
ImVec4 orangeAccentHover = ImVec4(1.00f, 0.65f, 0.30f, 1.00f); // Slightly brighter on hover
ImVec4 orangeAccentActive= ImVec4(1.00f, 0.45f, 0.10f, 1.00f); // Slightly darker on press
    // Couleurs
// Textes
style.Colors[ImGuiCol_Text]                   = ImVec4(0.92f, 0.95f, 1.00f, 1.00f); // Blanc bleuté, doux
style.Colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.55f, 0.65f, 1.00f);

// Fond général
style.Colors[ImGuiCol_WindowBg]               = ImVec4(0.04f, 0.05f, 0.07f, 1.00f); // Très sombre
style.Colors[ImGuiCol_ChildBg]                = ImVec4(0.07f, 0.08f, 0.10f, 1.00f);
style.Colors[ImGuiCol_PopupBg]                = ImVec4(0.05f, 0.06f, 0.07f, 0.98f);

// Bordures
style.Colors[ImGuiCol_Border]                 = ImVec4(0.18f, 0.20f, 0.24f, 0.50f);
style.Colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

// Cadres
style.Colors[ImGuiCol_FrameBg]                = ImVec4(0.12f, 0.13f, 0.16f, 1.00f);
style.Colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.16f, 0.18f, 0.22f, 1.00f);
style.Colors[ImGuiCol_FrameBgActive]          = ImVec4(0.18f, 0.20f, 0.25f, 1.00f);

// Titres et barres
style.Colors[ImGuiCol_TitleBg]                = ImVec4(0.06f, 0.07f, 0.08f, 1.00f);
style.Colors[ImGuiCol_TitleBgActive]          = ImVec4(0.10f, 0.12f, 0.14f, 1.00f);
style.Colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.03f, 0.03f, 0.04f, 1.00f);

style.Colors[ImGuiCol_MenuBarBg]              = ImVec4(0.07f, 0.08f, 0.09f, 1.00f);

// Scrollbars
style.Colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.05f, 0.05f, 0.05f, 0.50f);
style.Colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.26f, 0.36f, 0.56f, 0.90f);
style.Colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.36f, 0.46f, 0.66f, 0.90f);
style.Colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.46f, 0.56f, 0.76f, 1.00f);

// Coche et sliders
style.Colors[ImGuiCol_CheckMark]              = ImVec4(0.38f, 0.70f, 1.00f, 1.00f);
style.Colors[ImGuiCol_SliderGrab]             = ImVec4(0.35f, 0.65f, 1.00f, 1.00f);
style.Colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.45f, 0.75f, 1.00f, 1.00f);

// Boutons
style.Colors[ImGuiCol_Button]                 = ImVec4(0.16f, 0.18f, 0.22f, 1.00f);
style.Colors[ImGuiCol_ButtonHovered]          = ImVec4(0.24f, 0.28f, 0.34f, 1.00f);
style.Colors[ImGuiCol_ButtonActive]           = ImVec4(0.30f, 0.36f, 0.42f, 1.00f);

// Headers (ex: TreeNode)
style.Colors[ImGuiCol_Header]                 = ImVec4(0.20f, 0.22f, 0.26f, 1.00f);
style.Colors[ImGuiCol_HeaderHovered]          = ImVec4(0.28f, 0.32f, 0.38f, 1.00f);
style.Colors[ImGuiCol_HeaderActive]           = ImVec4(0.34f, 0.40f, 0.48f, 1.00f);

// Séparateurs
style.Colors[ImGuiCol_Separator]              = ImVec4(0.22f, 0.24f, 0.28f, 0.60f);
style.Colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.32f, 0.34f, 0.38f, 1.00f);
style.Colors[ImGuiCol_SeparatorActive]        = ImVec4(0.38f, 0.40f, 0.46f, 1.00f);

// Resize grip
style.Colors[ImGuiCol_ResizeGrip]             = ImVec4(0.30f, 0.60f, 1.00f, 0.30f);
style.Colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.30f, 0.60f, 1.00f, 0.60f);
style.Colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.30f, 0.60f, 1.00f, 0.90f);

// Tabs
style.Colors[ImGuiCol_Tab]                    = ImVec4(0.14f, 0.16f, 0.20f, 1.00f);
style.Colors[ImGuiCol_TabHovered]             = ImVec4(0.24f, 0.28f, 0.32f, 1.00f);
style.Colors[ImGuiCol_TabActive]              = orangeAccent;
style.Colors[ImGuiCol_TabUnfocused]           = ImVec4(0.12f, 0.14f, 0.18f, 1.00f);
style.Colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.18f, 0.20f, 0.24f, 1.00f);

}

HubInterface::~HubInterface()
{
}

void HubInterface::Render()
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
            
        glViewport(0, 0, 1920, 1080);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
        // ImGui new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        RenderMainDockSpace();
        ImVec2 displaySize = ImGui::GetIO().DisplaySize;
        ImVec2 windowSize =displaySize;
        ImVec2 centeredPos = ImVec2(
            (displaySize.x - windowSize.x) * 0.5f,
            (displaySize.y - windowSize.y) * 0.5f
        );

        ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);
        ImGui::SetNextWindowPos(centeredPos, ImGuiCond_Always);

        // UI
        ImGui::Begin("Hub Window", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);

        // Taille totale disponible
        ImVec2 avail = ImGui::GetContentRegionAvail();

        // Largeur du panneau gauche (fixe)
        float sidebarWidth = 200.0f;

        // Panel gauche
        ImGui::BeginChild("Sidebar", ImVec2(sidebarWidth, avail.y), true);
        ImGui::Text("Applications");
        ImGui::Separator();

        if (ImGui::Button("Pulse Forge", ImVec2(-1, 0))) { /* choix app */ }
        if (ImGui::Button("Settings", ImVec2(-1, 0))) { /* choix app */ }

        ImGui::EndChild();

        // Même ligne pour coller le panel central
        ImGui::SameLine();

        // Panel central (remplit le reste)
        ImGui::BeginChild("MainPanel", ImVec2(0, avail.y), true);
        // Contenu central vide pour l’instant
        ImGui::EndChild();

        ImGui::End();

        // render ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            
        // multi-viewport
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
            
        glfwSwapBuffers(window);
    }


}
