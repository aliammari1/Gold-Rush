#include "header.h"

int integration()
{
        printf("HI\n");
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_Surface *screen = NULL;
        SDL_Surface *backg;
        Personne p, p2;
        Ennemi e;
        Time temps;
        Time tempsenig;
        map m;
        Background B;
        SDL_Event event;
        int continuer = 0, n = 0, ms, k = 0, direction, pasmouv = 10, co, c, minitach;
        Uint32 t_prev = 0, dt = 0, start;
        const int FPS = 30;
        const int speed = 5;
        bool b[4] = {0, 0, 0, 0};
        screen = SDL_SetVideoMode(1280, 419, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
        SDL_Surface *Masque = SDL_LoadBMP("backgroundmasque.bmp");
        initEnnemi(&e);
        initPerso(&p);
        initPerso2(&p2);

        initBackground(&B);
        inittemps(&temps);
        inittempsenig(&tempsenig);
        initialiser_map(&m, screen);
        do
        {
                printf("1 joueur | 2 joueurs:\n");
                scanf("%d", &n);
        } while ((n < 0) || (n > 2));
        if (n == 2)
        {
                initpartage1(&B, &p);
                initpartage2(&B, &p2);
        }
        while (continuer == 0)
        {
                start = SDL_GetTicks();
                t_prev = SDL_GetTicks();
                SDL_PollEvent(&event);
                switch (event.type)
                {
                case SDL_QUIT:
                        continuer = 1;
                        break;
                case SDL_KEYDOWN:
                        switch (event.key.keysym.sym)
                        {
                        case SDLK_k:
                                minitach = minitache();
                                break;
                        case SDLK_ESCAPE:
                                continuer = 1;
                                break;
                        case SDLK_d:
                                p2.vX += 0.01;
                                p2.d = 0;
                                p2.direction = 1;
                                break;
                        case SDLK_a:
                                p2.vX += 0.01;
                                p2.d = 1;
                                p2.direction = 3;
                                break;
                        case SDLK_w:
                                p2.up = 1;
                                if (p2.d == 0)
                                        p2.direction = 4;
                                if (p2.d == 1)
                                        p2.direction = 5;
                                break;
                        case SDLK_RIGHT:
                                p.vX += 0.01;
                                p.d = 0;
                                p.direction = 1;
                                b[0] = 1;
                                break;
                        case SDLK_LEFT:
                                p.vX += 0.01;
                                p.d = 1;
                                p.direction = 3;
                                b[1] = 1;
                                break;
                        case SDLK_DOWN:
                                b[3] = 1;
                                break;
                        case SDLK_UP:
                                p.up = 1;
                                if (p.d == 0)
                                        p.direction = 4;
                                if (p.d == 1)
                                        p.direction = 5;
                                b[2] = 1;
                                break;
                        }
                        break;
                case SDL_KEYUP:
                        switch (event.key.keysym.sym)
                        {
                        case SDLK_a:
                                p2.vX -= 0.005;
                                p2.direction = 0;
                                break;
                        case SDLK_d:
                                p2.vX -= 0.005;
                                p2.direction = 2;
                                break;
                        case SDLK_w:
                                if (p2.up == 0)
                                {
                                        if (p2.d == 0)
                                                p2.direction = 0;
                                        if (p2.d == 1)
                                                p2.direction = 2;
                                }
                                break;
                        case SDLK_RIGHT:
                                p.vX -= 0.005;
                                p.direction = 0;
                                break;
                        case SDLK_LEFT:
                                p.vX -= 0.005;
                                p.direction = 2;
                                break;
                        case SDLK_UP:
                                if (p.up == 0)
                                {
                                        if (p.d == 0)
                                                p.direction = 0;
                                        if (p.d == 1)
                                                p.direction = 2;
                                }
                                break;
                        }
                        break;
                }
                if (SDL_GetTicks() - start > 200)
                {
                        deplacerIA(&e, p);
                        start = SDL_GetTicks();
                }
                scrolling(&B, b, pasmouv);
                afficherBack(&B, screen);
                animation_clouds(&B, screen);
                co = collisionPP(&p, Masque);
                if ((co == 1) || (co == 2))
                        continuer = 1;
                SDL_Flip(screen);
                p.vX -= 0.001;
                if (n == 2)
                        p2.vX -= 0.001;
                dt = 1;
                deplacerPerso(&p, dt);
                if (n == 2)
                        deplacerPerso(&p2, dt);
                if (p.up == 1)
                {
                        if ((p.pos_relative.x) <= 20)
                                saut(&p);
                        else
                        {
                                p.pos.y += -15;
                                p.pos_relative.x = -20;
                                p.up = 0;
                        }
                }
                if (n == 2)
                {
                        if (p2.up == 1)
                        {
                                if ((p2.pos_relative.x) <= 20)
                                        saut(&p2);
                                else
                                {
                                        p2.pos.y += -15;
                                        p2.pos_relative.x = -20;
                                        p2.up = 0;
                                }
                        }
                }
                printf("acc%f\n", p.vX);
                printf("pos%d\n", p.pos.y);

                animerPerso(&p);
                if (n == 2)
                        animerPerso(&p2);
                animerEnnemi(&e);
                afficherPerso(p, screen);
                if (n == 2)
                        afficherPerso(p2, screen);

                afficherEnnemi(e, screen);
                SDL_Flip(screen);

                dt = SDL_GetTicks() - t_prev;

                c = collisionBB(p, e);
                if (c == 1)
                        enigme_jeu();

                printf("HI\n");
                update_time(&temps);
                perso_map(&m, &p);
                displaytime(temps, screen);
                affiche_map(&m, screen, &p);
                if (n == 2)
                        afficherpartage(&B, screen);
                SDL_Flip(screen);
        }
        SDL_Quit();
}
