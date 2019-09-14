#include "filesystem.h"
#include "getch.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <unordered_map>

int main() {
  //use SDL because it supports 32 bit audio
  SDL_Init(SDL_INIT_AUDIO | SDL_INIT_TIMER);
  
  //Initialize SDL_mixer
  if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
  {
    return 1;
  }
  
  fs::path p("/media/sebastian/Shared/Projects/Collaboration"
             "/Codename_Playlist/playlist/playlist/Season 1/Season 1/");
  std::vector<fs::path> files;
  get_all(p, ".mp3", files);
  
  if (files.size() == 0) {
    puts("No music found. Exiting.");
    return 0;
  }
  
  //Load the first song.
  
  size_t currentMusicIndex = 0;
  std::unordered_map<std::string, Mix_Music*> loadedMusic; //Music cache
  fs::path current = files.at(currentMusicIndex);
  //TODO: alphabetical order for numerical differences (i.e. episode 1, 2, 3,
  // to 10 and 11 doesnt work. maybe use track number metadata
  //std::sort( files.begin(), files.end() );

  auto printPlaylist = [&]() {
    for (const fs::path& p : files) {
      std::cout << p << std::endl;
    }
  };
  
  printPlaylist();
  //puts(current.c_str());
  //return 0;
  Mix_Music* music = Mix_LoadMUS(current.c_str());
  loadedMusic.insert(std::make_pair(current.string(), music));

  // If there is no music playing
  if (Mix_PlayingMusic() == 0) {
    // Play the music
    if (Mix_PlayMusic(music, -1) == -1) {
      return 1;
    }
  }
  
  auto skip = [&]() {
    currentMusicIndex++;
    if (currentMusicIndex > files.size()) {
      currentMusicIndex = 0;
    }
    
    auto it = loadedMusic.find(files.at(currentMusicIndex).string());
    Mix_Music* music;
    if (it != loadedMusic.end()) {
      music = it->second;
    }
    else {
      music = Mix_LoadMUS(files.at(currentMusicIndex).c_str());
    }
    // Play the music
    if (Mix_PlayMusic(music, -1) == -1) {
      throw 1;
    }
  };

  auto shuffle = [&]() {
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(files), std::end(files), rng);
    currentMusicIndex = SIZE_MAX; //make it overflow
    skip();
  };
  
  char userChoice;
  do {
    userChoice = getch();
    switch (userChoice) {
    case 'p': //pause
      if (Mix_PausedMusic() == 0) {
        Mix_PauseMusic();
      }
      else {
        Mix_ResumeMusic();
      }
      break;
    case 'n': //"next"
      skip();
      break;
    case 's': //shuffle
      shuffle();
      printPlaylist();
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