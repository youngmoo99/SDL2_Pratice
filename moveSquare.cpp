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
    if (SDL_Init(SDL_INIT_VIDEO) < 0) { //SDL_INIT_VIDEO 윈도우/렌더링 시스템 사용하겠다, 프로그램 시작 시 1회만 호출
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // 윈도우 생성
    //SDL2 렌더링 구조
    SDL_Window* window = SDL_CreateWindow("Move Square!",
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
    SDL_Rect rect = { 100, 100, RECT_SIZE, RECT_SIZE }; //왼쪽 상단 모서리의 x좌표, 왼쪽 상단 모서리의 y좌표, 가로길이, 세로 길이

    bool isRunning = true;
    SDL_Event event;

    // 게임 루프
    while (isRunning) {
        while (SDL_PollEvent(&event)) { //이벤트 처리
            if (event.type == SDL_QUIT)
                isRunning = false;

            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) //esc키
                isRunning = false;
        }

        const Uint8* keys = SDL_GetKeyboardState(NULL); //키 입력 처리
        if (keys[SDL_SCANCODE_LEFT] && rect.x > 0) rect.x -= SPEED; // 좌
        if (keys[SDL_SCANCODE_RIGHT] && rect.x + rect.w < WINDOW_WIDTH ) rect.x += SPEED; // 우
        if (keys[SDL_SCANCODE_UP] && rect.y > 0)    rect.y -= SPEED; // 상
        if (keys[SDL_SCANCODE_DOWN] && rect.y + rect.h < WINDOW_HEIGHT)  rect.y += SPEED; // 하

        // 렌더링
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // 배경: 흰색
        SDL_RenderClear(renderer); //SDL_RenderClear → 화면(배경) 지우기

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // 사각형: 빨간색
        SDL_RenderFillRect(renderer, &rect); //SDL_RenderFillRect → 사각형 그리기

        SDL_RenderPresent(renderer); //SDL_RenderPresent → 그린 걸 화면에 반영(화면 출력)

        SDL_Delay(16); // 약 60FPS
    }

    // 종료 처리
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}