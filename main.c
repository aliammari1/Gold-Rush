#include "header.h"
int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    int game = 1, g = 0, s = 0, q = 0, n = 0, up = 2, c = 0, m = 1, t = 0;
    SDL_Event event1;
    SDL_Event event2;
    SDL_Surface *screen;
    logo logo;
    back backg;
    button play;
    button settings;
    button quit;
    button full_screen;
    image team_logo;
    image LOGO_GROUPE;
    image the_witcher;
    texte text;
    song song[5];
    Mix_Chunk *son;
    son = Mix_LoadWAV("videoplayback.wav");
    screen = SDL_SetVideoMode(1280, 639, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    init_button_play(&play);
    init_button_settings(&settings);
    init_button_quit(&quit);
    init_button_full_screen(&full_screen);
    init_image(&LOGO_GROUPE, 1, 523, "LOGO_GROUPE.jpg");
    init_image(&team_logo, 1, 450, "team_logo.png");
    init_image(&the_witcher, 0, 0, "witcher.jpg");
    init_back(&backg);
    init_texte(&text);
    init_logo(&logo);
    printf("Hi\n");
    init_back_music(song);
    while (game)
    {
        if (m = 1)
        {
            afficher_back(backg, screen);
            afficher_button(play, screen);
            afficher_button(settings, screen);
            afficher_button(quit, screen);
            afficher_image(LOGO_GROUPE, screen);
            afficher_image(team_logo, screen);
            afficher_logo(logo, screen);
            SDL_PollEvent(&event1);
            switch (event1.type)
            {
            case SDL_QUIT:
                game = 0;
                break;
            case SDL_KEYDOWN:
                switch (event1.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    game = 0;
                    break;
                case SDLK_r:
                    g = 0;
                    m = 1;
                    break;
                case SDLK_f:
                    SDL_WM_ToggleFullScreen(screen);
                    break;
                case SDLK_s:
                    s = 0;
                    m = 1;
                    break;
                case SDLK_UP:
                    scrolling_menu_UP(&play, &settings, &quit, &n);
                    n--;
                    break;
                case SDLK_DOWN:
                    scrolling_menu_DOWN(&play, &settings, &quit, &n);
                    n++;
                    break;
                case SDLK_RETURN:
                    if (play.frame == 1)
                        g = 1;
                    if (settings.frame == 1)
                        s = 1;
                    if (quit.frame == 1)
                        q = 1;
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if ((s == 0) && (g == 0))
                    if (event1.motion.x >= 565 && event1.motion.x <= 700 && event1.motion.y >= 530 && event1.motion.y <= 630)
                    {
                        Mix_PlayChannel(-1, son, 0);
                        q = 1;
                    }
                if (s == 0)
                    if (event1.motion.x >= 565 && event1.motion.x <= 723 && event1.motion.y >= 296 && event1.motion.y <= 366)
                    {
                        Mix_PlayChannel(-1, son, 0);
                        g = 1;
                    }
                if (g == 0)
                    if (event1.motion.x >= 485 && event1.motion.x <= 849 && event1.motion.y >= 416 && event1.motion.y <= 486)
                    {
                        Mix_PlayChannel(-1, son, 0);
                        s = 1;
                    }
                if (event1.motion.x >= 565 && event1.motion.x <= 723 && event1.motion.y >= 296 && event1.motion.y <= 366)
                {
                    Mix_PlayChannel(-1, son, 0);
                    SDL_WM_ToggleFullScreen(screen);
                }
                break;
            case SDL_MOUSEMOTION:
                if (event1.motion.x >= 565 && event1.motion.x <= 700 && event1.motion.y >= 530 && event1.motion.y <= 630)
                    quit.frame = 1;
                else
                    quit.frame = 0;
                if (event1.motion.x >= 565 && event1.motion.x <= 723 && event1.motion.y >= 296 && event1.motion.y <= 366)
                    play.frame = 1;
                else
                    play.frame = 0;
                if (event1.motion.x >= 485 && event1.motion.x <= 849 && event1.motion.y >= 416 && event1.motion.y <= 486)
                    settings.frame = 1;
                else
                    settings.frame = 0;
                if (event1.motion.x >= 565 && event1.motion.x <= 723 && event1.motion.y >= 296 && event1.motion.y <= 366)
                    full_screen.frame = 1;
                else
                    full_screen.frame = 0;
                break;
            }
        }
        if (g == 1)
        {
            m = 0;
            game = integration();
        }
        if (s == 1)
        {
            m = 0;
            afficher_image(the_witcher, screen);
            afficher_button(full_screen, screen);
            display_texte(text, screen);
            afficher_song(song, screen);
            play_music(song);
        }
        if (q == 1)
            game = 0;
        animation_back(&backg);
        animation_logo(&logo);
        if (logo.frame == 10)
            t++;
        if (t == 1)
        {
            logo_music();
            printf("Played\n");
            SDL_Delay(100);
        }
        SDL_Flip(screen);
    }
    TTF_CloseFont(text.font);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
