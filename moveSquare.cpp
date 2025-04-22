#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdio.h>

#pragma comment(lib, "SDL2.lib")

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int RECT_SIZE = 50;
const int SPEED = 5;

int main(int argc, char* argv[])
{
    // SDL 초기화
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // 윈도우 생성
    SDL_Window* window = SDL_CreateWindow("사각형 움직이기!",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (!window) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // 렌더러 생성
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 사각형 초기 위치
    SDL_Rect rect = { 100, 100, RECT_SIZE, RECT_SIZE };

    bool isRunning = true;
    SDL_Event event;

    // 게임 루프
    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                isRunning = false;

            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                isRunning = false;
        }

        const Uint8* keys = SDL_GetKeyboardState(NULL); //상하좌우
        if (keys[SDL_SCANCODE_LEFT])  rect.x -= SPEED;
        if (keys[SDL_SCANCODE_RIGHT]) rect.x += SPEED;
        if (keys[SDL_SCANCODE_UP])    rect.y -= SPEED;
        if (keys[SDL_SCANCODE_DOWN])  rect.y += SPEED;

        // 렌더링
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // 배경: 흰색
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // 사각형: 빨간색
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);

        SDL_Delay(16); // 약 60FPS
    }

    // 종료 처리
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}