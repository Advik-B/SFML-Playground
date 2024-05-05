#include "Game.cpp"
#include "Button.cpp"

int main() {
    Game game;
    while (game.running()) {
        game.update();
        game.render();
    }
    return 0;
}