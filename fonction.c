#include "header.h"
void init_image(image *images, int x, int y, char path[])
{
    images->img = IMG_Load(path);
    images->pos.x = x;
    images->pos.y = y;
}
void init_button_play(button *play)
{
    int i;
    char nom_image[20];
    for (i = 0; i < 2; i++)
    {
        sprintf(nom_image, "play%d.png", i);
        play->img[i] = IMG_Load(nom_image);
    }
    play->frame = 0;
    play->pos.x = 565;
    play->pos.y = 296;
}
void init_button_settings(button *settings)
{
    int i;
    char path[20];
    for (i = 0; i < 2; i++)
    {
        sprintf(path, "settings%d.png", i);
        settings->img[i] = IMG_Load(path);
    }
    settings->frame = 0;
    settings->pos.x = 565;
    settings->pos.y = 416;
}
void init_button_quit(button *quit)
{
    int i;
    char path[20];
    for (i = 0; i < 2; i++)
    {
        sprintf(path, "quit%d.png", i);
        quit->img[i] = IMG_Load(path);
    }
    quit->frame = 0;
    quit->pos.x = 565;
    quit->pos.y = 530;
}
void init_button_full_screen(button *full_screen)
{
    int i;
    char nom_image[20];
    for (i = 0; i < 2; i++)
    {
        sprintf(nom_image, "fullscreen%d.png", i);
        full_screen->img[i] = IMG_Load(nom_image);
    }
    full_screen->frame = 0;
    full_screen->pos.x = 565;
    full_screen->pos.y = 296;
}
void init_back(back *backg)
{
    int i;
    char path[20];
    for (i = 0; i < 3; i++)
    {
        sprintf(path, "back%d.jpg", i);
        backg->img[i] = IMG_Load(path);
    }
    backg->frame = 0;
    backg->pos.x = 0;
    backg->pos.y = 0;
}
void init_logo(logo *logo)
{
    int i;
    char path[20];
    for (i = 0; i < 11; i++)
    {
        sprintf(path, "logo/logo%d.png", i);
        logo->img[i] = IMG_Load(path);
    }
    logo->frame = 0;
    logo->pos.x = 510;
    logo->pos.y = 0;
}
void init_texte(texte *text)
{
    text->pos.x = 300;
    text->pos.y = 500;
    text->textcolor.r = 255;
    text->textcolor.g = 0;
    text->textcolor.b = 0;
    text->font = TTF_OpenFont("arial.ttf", 50);
}
void display_texte(texte text, SDL_Surface *screen)
{
    text.surface_texte = TTF_RenderText_Solid(text.font, "Cantact Us at: esprit2122@esprit.tn", text.textcolor);
    SDL_BlitSurface(text.surface_texte, NULL, screen, &text.pos);
}
void scrolling_menu_UP(button *play, button *settings, button *quit, int *n)
{

    if ((*n) <= 0)
        (*n) = 1;
    if ((*n) == 1)
    {
        play->frame = 1;
        settings->frame = 0;
        quit->frame = 0;
    }
    if ((*n) == 2)
    {
        play->frame = 0;
        settings->frame = 1;
        quit->frame = 0;
    }
    if ((*n) == 3)
    {
        play->frame = 0;
        settings->frame = 0;
        quit->frame = 1;
    }
    printf("%d\n", *n);
}
void scrolling_menu_DOWN(button *play, button *settings, button *quit, int *n)
{
    if ((*n) >= 3)
        (*n) = 3;
    if ((*n) == 1)
    {
        play->frame = 1;
        settings->frame = 0;
        quit->frame = 0;
    }
    if ((*n) == 2)
    {
        play->frame = 0;
        settings->frame = 1;
        quit->frame = 0;
    }
    if ((*n) == 3)
    {
        play->frame = 0;
        settings->frame = 0;
        quit->frame = 1;
    }
}
void animation_back(back *backg)
{
    (backg->frame)++;
    if (backg->frame == 3)
        backg->frame = 0;
}
void animation_logo(logo *logo)
{
    (logo->frame)++;
    if ((logo->frame) < 10)
        SDL_Delay(100);
    else
        logo->frame = 10;
}
void afficher_logo(logo logo, SDL_Surface *screen)
{
    SDL_BlitSurface(logo.img[logo.frame], NULL, screen, &logo.pos);
}
void afficher_image(image images, SDL_Surface *screen)
{
    SDL_BlitSurface(images.img, NULL, screen, &images.pos);
}
void afficher_button(button buttons, SDL_Surface *screen)
{
    SDL_BlitSurface(buttons.img[buttons.frame], NULL, screen, &buttons.pos);
}
void afficher_back(back backg, SDL_Surface *screen)
{
    SDL_BlitSurface(backg.img[backg.frame], NULL, screen, &backg.pos);
}
void logo_music()
{
    Mix_Chunk *logo_music;
    logo_music = Mix_LoadWAV("audio.wav");
    Mix_PlayChannel(-1, logo_music, 0);
}
void back_music()
{
    Mix_Music *music;
    music = Mix_LoadMUS("Living Life In The Night - Cheriimoya- Sierra Kidd (Lyrics)[Mpgun.com].mp3");
    Mix_PlayMusic(music, 0);
}
void init_back_music(song song[])
{
    int i;
    char path[20];
    for (i = 0; i < 5; i++)
    {
        sprintf(path, "music/%d.mp3", i);
        song[i].music = Mix_LoadMUS(path);
    }
    for (i = 0; i < 5; i++)
    {
        sprintf(path, "song/song%d.png", i);
        song[i].songpic = IMG_Load(path);
    }
    for (i = 0; i < 5; i++)
    {
        song[0].pos.x = 150;
        if (i != 0)
            song[i].pos.x = song[i - 1].pos.x + 150;
        song[i].pos.y = 500;
    }
}
void afficher_song(song song[], SDL_Surface *screen)
{
    SDL_BlitSurface(song[0].songpic, NULL, screen, &song[0].pos);
    SDL_BlitSurface(song[1].songpic, NULL, screen, &song[1].pos);
    SDL_BlitSurface(song[2].songpic, NULL, screen, &song[2].pos);
    SDL_BlitSurface(song[3].songpic, NULL, screen, &song[3].pos);
    SDL_BlitSurface(song[4].songpic, NULL, screen, &song[4].pos);
}
void play_music(song song[])
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_KP1:
            Mix_PlayMusic(song[0].music, 0);
            break;
        case SDLK_KP2:
            Mix_PlayMusic(song[1].music, 0);
            break;
        case SDLK_KP3:
            Mix_PlayMusic(song[2].music, 0);
            break;
        case SDLK_KP4:
            Mix_PlayMusic(song[3].music, 0);
            break;
        case SDLK_KP5:
            Mix_PlayMusic(song[4].music, 0);
            break;
        }
        break;
    }
}
