#include <stdio.h>
#include <stdlib.h>

#define WIDTH 40
#define HEIGHT 15

int main() {
    int ballX = WIDTH / 2, ballY = HEIGHT / 2;
    int ballDirX = 1, ballDirY = 1;
    int playerY = HEIGHT / 2;
    int aiY = HEIGHT / 2;
    int playerScore = 0, aiScore = 0;
    char input;

    // Game Loop
    while (1) {
        // Clear screen (portable)
        for(int i = 0; i < 25; i++) printf("\n");

        // Draw scores at top
        printf("PLAYER: %d\t\tAI: %d\n", playerScore, aiScore);

        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                if (y == 0 || y == HEIGHT - 1) printf("-");
                else if (x == 0 || x == WIDTH - 1) printf("|");
                else if (x == 2 && y == playerY) printf("I");
                else if (x == WIDTH - 3 && y == aiY) printf("A");
                else if (x == ballX && y == ballY) printf("O");
                else printf(" ");
            }
            printf("\n");
        }

        // Input
        printf("Move (w: up, s: down, q: quit): ");
        scanf(" %c", &input);

        if (input == 'w' && playerY > 1) playerY--;
        if (input == 's' && playerY < HEIGHT - 2) playerY++;

        if (input == 'q') {
            // Show final score when quitting
            printf("\nFinal Score:\n");
            printf("PLAYER: %d\n", playerScore);
            printf("AI: %d\n", aiScore);
            break;
        }

        // AI movement
        if (aiY < ballY && aiY < HEIGHT - 2) aiY++;
        else if (aiY > ballY && aiY > 1) aiY--;

        // Ball movement
        ballX += ballDirX;
        ballY += ballDirY;

        // Wall collision
        if (ballY <= 1 || ballY >= HEIGHT - 2)
            ballDirY *= -1;

        // Paddle collision
        if (ballX == 3 && ballY == playerY)
            ballDirX *= -1;

        if (ballX == WIDTH - 4 && ballY == aiY)
            ballDirX *= -1;

        // Scoring logic
        if (ballX <= 0) {
            aiScore++;   // AI scores
            ballX = WIDTH / 2;
            ballY = HEIGHT / 2;
            ballDirX = 1;
        }

        if (ballX >= WIDTH - 1) {
            playerScore++;  // Player scores
            ballX = WIDTH / 2;
            ballY = HEIGHT / 2;
            ballDirX = -1;
        }
    }

    printf("\nGame Over!\n");
    return 0;
}
