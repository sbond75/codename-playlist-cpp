#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "getch.h"

int main() {
  //use SDL because it supports 32 bit audio
  SDL_Init(SDL_INIT_AUDIO | SDL_INIT_TIMER);
  
  //Initialize SDL_mixer
  if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
  {
    return 1;
  }
  
  Mix_Music* music = Mix_LoadMUS( "/media/sebastian/Shared/Projects/Collaboration/Codename_Playlist/playlist/playlist/Season 1/Season 1/Episode 1 - Go Into My Hole.mp3" );

  // If there is no music playing
  if (Mix_PlayingMusic() == 0) {
    // Play the music
    if (Mix_PlayMusic(music, -1) == -1) {
      return 1;
    }
  }

  char userChoice;
  do {
    userChoice = getch();
    switch (userChoice) {
    case 'p':
      if (Mix_PausedMusic() == 0) {
        Mix_PauseMusic();
      }
      else {
        Mix_ResumeMusic();
      }
      break;
    }
  } while (userChoice != 'q');
  
  //While the user hasn't quit
//  bool quit = false;
//  SDL_Event event;
//  while( quit == false ) {
//    // While there's events to handle
//    while (SDL_PollEvent(&event)) {
//      switch (event.type) {
//      case SDL_MOUSEMOTION:
//        break;
//      }
//    }
//  }


  //Free the music
  Mix_FreeMusic( music );

  //Quit SDL_mixer
  Mix_CloseAudio();

  //Quit SDL
  SDL_Quit();
  
  return 0;
}