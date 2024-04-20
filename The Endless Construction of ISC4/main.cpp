#include "Game.h"

int main() {
	Game game = Game();

	while (game.isRunning()) {
		game.pollEvents();
		game.update();
		game.render();
	}
}