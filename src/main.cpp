#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <imgui-SFML.h>
#include <imgui.h>

#include "fonts/JBmono.hpp" // JetBrain Mono font(bin2hex)

constexpr double pi = 3.14159265358979323846;

struct PlayerMovement
{
    bool up, down, left, right;
    PlayerMovement() : up(false), down(false), left(false), right(false) {}
};

int getPointCount(const sf::RenderWindow &window, const sf::CircleShape &circle) {
    // Get the size of the window
    unsigned windowSize = window.getSize().x * window.getSize().y / 100000;

    // Get the radius of the circle
    float radius = circle.getRadius();

    // Calculate the number of points needed to approximate the circle
    int pcout = static_cast<int>(radius * windowSize / 10);
    std::cout << "Point Count: " << pcout << '\n';
    return pcout;
}

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
    void _updatePlayer_sprite();
    void imRender();
    void drawGrid();

    sf::RenderWindow mWindow;
    sf::CircleShape mPlayer;
    PlayerMovement mPlayerMovement;
    float mPlayerSpeed;
    sf::Clock mClock;
    ImGuiIO *io;
    int grid_size = 10;
    sf::Color gridColor;

};

Game::Game()
{
    mWindow.create(sf::VideoMode(640 * 2, 480 * 2), "SFML Game");
    mPlayerSpeed = 100.f * 2;
    mPlayer.setRadius(10.f);
    mPlayer.setPointCount(getPointCount(mWindow, mPlayer));
    mPlayer.setFillColor(sf::Color{100, 250, 50});
    mPlayer.setPosition(100.f, 100.f);
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
    // Make the font bold
//    font_config.GlyphExtraSpacing.x = 1.0f;
//    font_config.GlyphExtraSpacing.y = 1.0f;

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
    sf::Vector2f movement(0.f, 0.f);
    if (mPlayerMovement.left)
        movement.x -= mPlayerSpeed;
    if (mPlayerMovement.right)
        movement.x += mPlayerSpeed;
    if (mPlayerMovement.up)
        movement.y -= mPlayerSpeed;
    if (mPlayerMovement.down)
        movement.y += mPlayerSpeed;

    sf::Time dt = mClock.restart();
    ImGui::SFML::Update(mWindow, dt);
    mPlayer.move(movement * dt.asSeconds());
}

void Game::render()
{
    mWindow.clear();
    drawGrid();
    mWindow.draw(mPlayer);
    imRender();
    ImGui::SFML::Render(mWindow);
    mWindow.display();
}

void Game::handleKeyBoardInput(sf::Keyboard::Key key, bool isPressed)
{
    switch (key)
    {
        case sf::Keyboard::W:
            mPlayerMovement.up = isPressed;
            break;
        case sf::Keyboard::S:
            mPlayerMovement.down = isPressed;
            break;
        case sf::Keyboard::A:
            mPlayerMovement.left = isPressed;
            break;
        case sf::Keyboard::D:
            mPlayerMovement.right = isPressed;
            break;

        case sf::Keyboard::Equal:
            mPlayer.setRadius(mPlayer.getRadius() + 1);
            _updatePlayer_sprite();
            break;
        case sf::Keyboard::Dash:
            mPlayer.setRadius(mPlayer.getRadius() - 1);
            _updatePlayer_sprite();
            break;
        default:
            break;
    }
}

void Game::imRender() {
    ImGui::SetNextWindowSize(ImVec2(300, 150), ImGuiCond_FirstUseEver);
    ImGui::Begin("Game Settings");
    ImGui::SliderFloat("Player Speed", &mPlayerSpeed, 0.f, 500.f);
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
    _updatePlayer_sprite();
}

void Game::_updatePlayer_sprite() {
    mPlayer.setPointCount(getPointCount(mWindow, mPlayer));
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

int main() { return Game().run(); }
