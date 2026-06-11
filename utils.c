/* SPDX-License-Identifier: Zlib */
#include "core.h"

/**
 * @brief Initialize a menu button with default values
 * @param button Pointer to MenuButton structure
 */
void initMenuButton(MenuButton *button)
{
    if (button == NULL) {
        return;
    }
    
    button->position.x = 0;
    button->position.y = 0;
    button->position.w = 158;
    button->position.h = 70;
    button->isHighlighted = 0;
    button->sprites[0] = NULL;  /* Normal state */
    button->sprites[1] = NULL;  /* Highlighted state */
}

/**
 * @brief Initialize menu background animation
 * @param background Pointer to MenuBackground structure
 */
void initMenuBackground(MenuBackground *background)
{
    if (background == NULL) {
        return;
    }
    
    background->position.x = 0;
    background->position.y = 0;
    background->position.w = SCREEN_WIDTH;
    background->position.h = SCREEN_HEIGHT;
    background->currentFrame = 0;
    
    for (int i = 0; i < 3; i++) {
        background->sprites[i] = NULL;
    }
}

/**
 * @brief Initialize menu logo animation
 * @param logo Pointer to MenuLogo structure
 */
void initMenuLogo(MenuLogo *logo)
{
    if (logo == NULL) {
        return;
    }
    
    logo->position.x = (SCREEN_WIDTH / 2) - 100;
    logo->position.y = 50;
    logo->position.w = 200;
    logo->position.h = 200;
    logo->currentFrame = 0;
    
    for (int i = 0; i < 11; i++) {
        logo->sprites[i] = NULL;
    }
}

/**
 * @brief Initialize menu text display
 * @param text Pointer to MenuText structure
 */
void initMenuText(MenuText *text)
{
    if (text == NULL) {
        return;
    }
    
    text->position.x = 0;
    text->position.y = 0;
    text->font = NULL;
    text->textSurface = NULL;
    text->textColor.r = 255;
    text->textColor.g = 255;
    text->textColor.b = 255;
    text->text[0] = '\0';
}

/**
 * @brief Render a menu button
 * @param button The button to render
 * @param screen The display surface
 */
void renderMenuButton(MenuButton button, SDL_Surface *screen)
{
    if (screen == NULL) {
        return;
    }
    
    /* Determine which sprite to render based on highlight state */
    SDL_Surface *spriteToRender = button.sprites[button.isHighlighted ? 1 : 0];
    if (spriteToRender != NULL) {
        SDL_BlitSurface(spriteToRender, NULL, screen, &button.position);
    }
}

/**
 * @brief Render the menu logo
 * @param logo The logo to render
 * @param screen The display surface
 */
void renderMenuLogo(MenuLogo logo, SDL_Surface *screen)
{
    if (screen == NULL || logo.sprites[logo.currentFrame] == NULL) {
        return;
    }
    
    SDL_BlitSurface(logo.sprites[logo.currentFrame], NULL, screen, &logo.position);
}

/**
 * @brief Render menu text
 * @param text The text to render
 * @param screen The display surface
 */
void renderMenuText(MenuText text, SDL_Surface *screen)
{
    if (screen == NULL || text.textSurface == NULL) {
        return;
    }
    
    SDL_BlitSurface(text.textSurface, NULL, screen, &text.position);
}

/**
 * @brief Animate menu background to next frame
 * @param background Pointer to MenuBackground structure
 */
void animateMenuBackground(MenuBackground *background)
{
    if (background == NULL) {
        return;
    }
    
    background->currentFrame = (background->currentFrame + 1) % 3;
}

/**
 * @brief Animate menu logo to next frame
 * @param logo Pointer to MenuLogo structure
 */
void animateMenuLogo(MenuLogo *logo)
{
    if (logo == NULL) {
        return;
    }
    
    logo->currentFrame = (logo->currentFrame + 1) % 11;
}

/**
 * @brief Handle scrolling menu items up
 * @param play Play button
 * @param settings Settings button
 * @param quit Quit button
 * @param selection Current selection index
 */
void scrollMenuUp(MenuButton *play, MenuButton *settings, MenuButton *quit, int *selection)
{
    if (selection == NULL) {
        return;
    }
    
    /* Deselect current button */
    if (*selection == 0 && play != NULL) {
        play->isHighlighted = 0;
    } else if (*selection == 1 && settings != NULL) {
        settings->isHighlighted = 0;
    } else if (*selection == 2 && quit != NULL) {
        quit->isHighlighted = 0;
    }
    
    /* Move to previous button */
    *selection = (*selection - 1 + 3) % 3;
    
    /* Highlight new button */
    if (*selection == 0 && play != NULL) {
        play->isHighlighted = 1;
    } else if (*selection == 1 && settings != NULL) {
        settings->isHighlighted = 1;
    } else if (*selection == 2 && quit != NULL) {
        quit->isHighlighted = 1;
    }
}

/**
 * @brief Handle scrolling menu items down
 * @param play Play button
 * @param settings Settings button
 * @param quit Quit button
 * @param selection Current selection index
 */
void scrollMenuDown(MenuButton *play, MenuButton *settings, MenuButton *quit, int *selection)
{
    if (selection == NULL) {
        return;
    }
    
    /* Deselect current button */
    if (*selection == 0 && play != NULL) {
        play->isHighlighted = 0;
    } else if (*selection == 1 && settings != NULL) {
        settings->isHighlighted = 0;
    } else if (*selection == 2 && quit != NULL) {
        quit->isHighlighted = 0;
    }
    
    /* Move to next button */
    *selection = (*selection + 1) % 3;
    
    /* Highlight new button */
    if (*selection == 0 && play != NULL) {
        play->isHighlighted = 1;
    } else if (*selection == 1 && settings != NULL) {
        settings->isHighlighted = 1;
    } else if (*selection == 2 && quit != NULL) {
        quit->isHighlighted = 1;
    }
}
