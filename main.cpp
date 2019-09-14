#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <signal.h>

static void s_signal_handler (int signal_value)
{
  if (signal_value == SIGINT) {
    puts("A");
  }
}

static void s_catch_signals (void)
{
  struct sigaction action;
  action.sa_handler = s_signal_handler;
  action.sa_flags = 0;
  sigemptyset (&action.sa_mask);
  sigaction (SIGINT, &action, NULL);
  sigaction (SIGTERM, &action, NULL);
}

int main() {
  s_catch_signals ();
  
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
  
  while (true) {
    
    SDL_Delay(16);
  }
  
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