#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <imgui-SFML.h>
#include <imgui.h>

#include "fonts/JBmono.hpp" // JetBrain Mono font(bin2hex)

// Function that maps a pointer from a Color to a float (for ImGui)
float *colorToFloat(sf::Color &color) {
    // Do NOT use reinterpret_cast<float*>(&color) as it will not work, it will only convert the first byte of the color
    // (which is the red component) to a float
    static float colorFloat[4] = {color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f};
    return colorFloat;
}

class Game
{
public:
    Game();
    ~Game();
    int run();
private:
    void processEvents();
    void update();
    void render();
    void handleKeyBoardInput(sf::Keyboard::Key key, bool isPressed);
    void onResize(sf::Event::SizeEvent size);
    void imRender();
    void drawGrid();

    sf::RenderWindow mWindow;
    sf::Clock mClock;
    ImGuiIO *io;
    int grid_size = 10;
    sf::Color gridColor;

};

Game::Game()
{
    mWindow.create(sf::VideoMode(640 * 2, 480 * 2), "SFML Game");
    mWindow.setVerticalSyncEnabled(true);
    gridColor = sf::Color{100, 100, 100};
    ImGui::SFML::Init(mWindow, false);
    io = &ImGui::GetIO();
    io->IniFilename = nullptr;
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io->ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports;
    io->ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;

    // Calculate the size of the font
    /*
     unsigned char JBmono[] = { 0x00, 0x01, 0x00, ...};
     */
    ImFontConfig font_config;
    font_config.FontDataOwnedByAtlas = false;

    io->Fonts->AddFontFromMemoryTTF(JBmono, sizeof(JBmono), 16.5f, &font_config);
    ImGui::SFML::UpdateFontTexture();
}

void Game::processEvents()
{
    sf::Event event{};
    while (mWindow.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);
        if (io->WantCaptureKeyboard || io->WantCaptureMouse)
            return;
        switch (event.type)
        {
            case sf::Event::KeyPressed:
                handleKeyBoardInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handleKeyBoardInput(event.key.code, false);
                break;
            case sf::Event::Closed:
                mWindow.close();
                break;
            case sf::Event::Resized:
                onResize(event.size);
                break;
            case sf::Event::LostFocus:
            case sf::Event::GainedFocus:
                mClock.restart();
                break;
            default:
                break;
        }
    }
}

void Game::update()
{
    ImGui::SFML::Update(mWindow, mClock.restart());
}

void Game::render()
{
    mWindow.clear();
    drawGrid();
    imRender();
    ImGui::SFML::Render(mWindow);
    mWindow.display();
}

void Game::handleKeyBoardInput(sf::Keyboard::Key key, bool isPressed)
{
    return; // Nothing to be done
    switch (key)
    {
        default:
            break;
    }
}

void Game::imRender() {
    ImGui::SetNextWindowSize(ImVec2(300, 150), ImGuiCond_FirstUseEver);
    ImGui::Begin("Game Settings");
    auto colorFloat = colorToFloat(gridColor);
    if (ImGui::ColorEdit4("Grid Color", colorFloat, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoAlpha)) {
        gridColor = sf::Color(colorFloat[0] * 255, colorFloat[1] * 255, colorFloat[2] * 255, colorFloat[3] * 255);
    }
    ImGui::SliderInt("Grid Size", &grid_size, 1, 100);
    ImGui::End();
    if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}

int Game::run()
{
    mClock.restart(); // Needed because of the time between the constructor and the first frame

    while (mWindow.isOpen())
    {
        processEvents();
        update();
        render();
    }

    return 0;
}

void Game::onResize(sf::Event::SizeEvent size) {
    mWindow.setView(sf::View(sf::FloatRect(0, 0, size.width, size.height)));
}

void Game::drawGrid() {
    // Draw a grid for reference
    sf::Vector2u windowSize = mWindow.getSize();
    sf::VertexArray grid(sf::Lines, 2 * (windowSize.x + windowSize.y));
    for (int i = 0; i < windowSize.x; i += grid_size) {
        grid.append(sf::Vertex(sf::Vector2f(i, 0), gridColor));
        grid.append(sf::Vertex(sf::Vector2f(i, windowSize.y), gridColor));
    }
    for (int i = 0; i < windowSize.y; i += grid_size) {
        grid.append(sf::Vertex(sf::Vector2f(0, i), gridColor));
        grid.append(sf::Vertex(sf::Vector2f(windowSize.x, i), gridColor));
    }
    mWindow.draw(grid);
}

Game::~Game() {
    ImGui::SFML::Shutdown();
}

int main() {
    return Game().run();
}
