#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <imgui-SFML.h>
#include <imgui.h>
#include "fonts/BungeeFont.hpp"
#include "fonts/JBmono.hpp"
#include <string>
#include <iostream>

const auto bungeeFontSize = sizeof(BungeeFont) / sizeof(BungeeFont[0]);
const auto jbMonoFontSize = sizeof(JBmono) / sizeof(JBmono[0]);

std::string title{"Hello World"};

int main() {
    sf::RenderWindow window
    (
        sf::VideoMode(1280, 720),
        title
    );
    window.setFramerateLimit(60);

    // Get the maximum screen width and height for the current monitor
    const size_t MAX_SCREEN_HEIGHT = sf::VideoMode::getFullscreenModes()[0].height;
    const size_t MAX_SCREEN_WIDTH = sf::VideoMode::getFullscreenModes()[0].width;
    std::cout << "Max screen width: " << (int)MAX_SCREEN_WIDTH << std::endl;
    std::cout << "Max screen height: " << (int)MAX_SCREEN_HEIGHT << std::endl;

    ImGui::SFML::Init(window);

    auto io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    // Calculate BungeeFont size (its binary data is in BungeeFont.hpp)
    // Type (BungeeFont) = unsigned char BungeeFont[]

    ImFontConfig config;
    config.FontDataOwnedByAtlas = false;
    config.GlyphExtraSpacing = ImVec2(1.0f, 1.0f);
    config.GlyphOffset = ImVec2(0.0f, 0.0f);
    config.RasterizerMultiply = 1.0f;
    io.Fonts->Clear();
    io.Fonts->AddFontFromMemoryTTF(JBmono, jbMonoFontSize, 16.0f, &config);
    io.Fonts->AddFontFromMemoryTTF(BungeeFont, bungeeFontSize, 18.0f, &config);

    ImGui::SFML::UpdateFontTexture();
    ImGui::StyleColorsDark();

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
//    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports;
    io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;
    io.ConfigWindowsResizeFromEdges = true;

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 0.1f;
    style.FrameRounding = 0.1f;

    bool show_sfmlControls = true;
    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event{};
        sf::Time deltaTime = deltaClock.restart();

        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaTime);
        // Setup the menu bar
        ImGui::SetNextWindowDockID(0, ImGuiCond_FirstUseEver);
        ImGui::PushFont(io.Fonts->Fonts[1]);
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("View")) {
                ImGui::MenuItem("SFML Controls", nullptr, &show_sfmlControls);
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
        ImGui::PopFont();
        if (show_sfmlControls) {
            ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_Always);
            ImGui::SetNextWindowDockID(0, ImGuiCond_FirstUseEver);
            ImGui::Begin("SFML controls", &show_sfmlControls);
            // Window title input
            if (ImGui::InputText("Title", title.data(), title.size() + 1)) {
                window.setTitle(title);
            }
//         Window size input
            static int width = window.getSize().x;
            static int height = window.getSize().y;

            if (ImGui::SliderInt("Width", &width, 1, MAX_SCREEN_WIDTH)) {
                window.setSize(sf::Vector2u(width, height));
            }
            if (ImGui::SliderInt("Height", &height, 1, MAX_SCREEN_HEIGHT)) {
                window.setSize(sf::Vector2u(width, height));
            }
            ImGui::End();
        }

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}