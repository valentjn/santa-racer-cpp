/*      
 *      Santa Racer
 *      setup.cpp
 *      
 *      Copyright (C) 2010 Julian Valentin.
 *      
 *      This program is free software: you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation, either version 3 of the License, or
 *      (at your option) any later version.
 *      
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      
 *      You should have received a copy of the GNU General Public License
 *      along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <fstream>

#include "globals.hpp"
#include "setup.hpp"
#include "config.hpp"
#include "random.hpp"
#include "sound.hpp"

namespace Santa {
    namespace Setup {
        struct setup_flags {
            bool sdl, audio, images, text, level, level_objects, chimneys,
                 sounds, music, highscores, game;
        };
        
        typedef struct setup_flags SetupFlags;
        
        SetupFlags setup_flags;
        
        SDL_Surface *screen;
        bool fullscreen;
        
        bool verbose;
        
        Game *game;
        
        SurfaceMap images;
        Text *text;
        int text_char_widths[96];
        
        ChunkMap sounds;
        Mix_Music *music;
        
        int **std_level_map;
        int std_level_width;
        int **std_level_objects_map;
        
        Chimney **chimneys;
        int chimney_count;
    }
}

void Santa::Setup::santa_setup(void) {
    int flags;
    std::string home_dir;
    
    atexit(santa_cleanup);
    
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        Output::fatal_error("unable to initalize SDL: %s\n", SDL_GetError());
    }
    setup_flags.sdl = true;
    
    SDL_WM_SetCaption("Santa Racer", "Santa Racer");
    SDL_ShowCursor(SDL_DISABLE);
    SDL_EnableUNICODE(1);
    
    flags = SDL_DOUBLEBUF | SDL_RESIZABLE;
    if (fullscreen) {
        flags |= SDL_FULLSCREEN;
    }
    screen = SDL_SetVideoMode(screen_width, screen_height, 16, flags);
    
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        Output::fatal_error("unable to initialize SDL_Mixer: %s\n",
                            Mix_GetError());
    }
    Mix_AllocateChannels(channel_count);
    setup_flags.audio = true;
    
    if (load_images()) {
        setup_flags.images = true;
    }
    if (load_text()) {
        setup_flags.text = true;
    }
    if (load_level()) {
        setup_flags.level = true;
    }
    if (load_level_objects()) {
        setup_flags.level_objects = true;
    }
    if (load_chimneys()) {
        setup_flags.chimneys = true;
    }
    if (load_sounds()) {
        setup_flags.sounds = true;
    }
    if (load_music()) {
        setup_flags.music = true;
    }
    
    home_dir = Config::get_home_dir();
    Config::set_config_dir((home_dir + "/.santa/").c_str());
    if (Config::load_highscores()) {
        setup_flags.highscores = true;
    }
    
    SDL_WM_SetIcon(images["icon"], NULL);
    
    Random::seed();
    Output::debug("loading game\n");
    game = new Game();
    game->init();
    setup_flags.game = true;
    
    Sound::play_music();
}

bool Santa::Setup::load_images(void) {
    DIR *d;
    struct dirent *entry;
    std::string filename;
    std::string basename;
    SDL_Surface *surface;
    
    d = opendir("./assets/images/");
    if (d == NULL) {
        Output::fatal_error("couldn't find assets/images directory\n");
    }
    
    Output::debug("reading images");
    
    while ((entry = readdir(d)) != NULL) {
        filename = std::string(entry->d_name);
        if (filename.length() > 4 &&
            filename.substr(filename.length() - 4) == ".tga") {
            Output::debug(" %s", filename.c_str());
            
            surface = IMG_Load(("./assets/images/" + filename).c_str());
            if (!surface) {
                Output::fatal_error("couldn't load image: %s\n",
                                    IMG_GetError());
            }
            
            basename = filename.substr(0, filename.length() - 4);
            images[basename] = surface;
        }
    }
    
    Output::debug("\n");
    
    closedir(d);
    
    return true;
}

bool Santa::Setup::load_text(void) {
    std::ifstream f;
    int i = 0;
    
    Output::debug("reading char_widths.txt\n");
    
    f.open("./assets/data/char_widths.txt", std::ios_base::in);
    while (f >> text_char_widths[i]) {
        i++;
    }
    f.close();
    
    if (i != 96) {
        Output::fatal_error("invalid format of char_widths.txt, expected 96 "
                            "values\n");
    }
    
    text = new Text(images["font"]);
    
    return true;
}

bool Santa::Setup::load_level(void) {
    std::ifstream f;
    int x;
    int y;
    int i;
    int tmp_int;
    
    Output::debug("reading level.txt\n");
    
    f.open("./assets/data/level.txt", std::ios_base::in);
    i = 0;
    while (f >> tmp_int) {
        i++;
    }
    f.close();
    
    std_level_width = i / std_level_height;
    std_level_map = new int*[std_level_height];
    
    f.open("./assets/data/level.txt", std::ios_base::in);
    
    for (y = 0; y < std_level_height; y++) {
        std_level_map[y] = new int[std_level_width];
        for (x = 0; x < std_level_width; x++) {
            f >> std_level_map[y][x];
            //Output::debug("%x, %i: %i\n", y, x, std_level_array[y][x]);
        }
    }
    
    //Output::debug("2,4: %i\n", std_level_array[2][4]);
    f.close();
    
    return true;
}

bool Santa::Setup::load_level_objects(void) {
    std::ifstream f;
    int x;
    int y;
    
    Output::debug("reading level_objects.txt\n");
    std_level_objects_map = new int*[std_level_height];
    
    f.open("./assets/data/level_objects.txt", std::ios_base::in);
    
    for (y = 0; y < std_level_height; y++) {
        std_level_objects_map[y] = new int[std_level_width];
        for (x = 0; x < std_level_width; x++) {
            f >> std_level_objects_map[y][x];
        }
    }
    
    f.close();
    
    return true;
}

bool Santa::Setup::load_chimneys(void) {
    std::ifstream f;
    int i;
    int tmp_int;
    
    int map_index;
    int x;
    int width;
    int y;
    
    Output::debug("reading chimneys.txt\n");
    
    f.open("./assets/data/chimneys.txt", std::ios_base::in);
    i = 0;
    while (f >> tmp_int) {
        i++;
    }
    f.close();
    
    chimney_count = i / 4;
    chimneys = new Chimney*[chimney_count];
    
    f.open("./assets/data/chimneys.txt", std::ios_base::in);
    
    for (i = 0; i < chimney_count; i++) {
        f >> map_index;
        f >> x;
        f >> width;
        f >> y;
        chimneys[i] = new Chimney(map_index, x, width, y);
    }
    
    f.close();
    
    return true;
}

bool Santa::Setup::load_sounds(void) {
    DIR *d;
    struct dirent *entry;
    std::string filename;
    std::string basename;
    Mix_Chunk *sound;
    
    d = opendir("./assets/sounds/");
    if (d == NULL) {
        Output::fatal_error("couldn't find assets/sounds directory\n");
    }
    
    Output::debug("reading sounds");
    while ((entry = readdir(d)) != NULL) {
        filename = std::string(entry->d_name);
        if (filename.length() > 4 &&
            filename.substr(filename.length() - 4) == ".wav") {
            Output::debug(" %s", filename.c_str());
            
            sound = Mix_LoadWAV(("./assets/sounds/" + filename).c_str());
            if (!sound) {
                Output::fatal_error("couldn't load sound: %s\n",
                                    Mix_GetError());
            }
            
            basename = filename.substr(0, filename.length() - 4);
            sounds[basename] = sound;
        }
    }
    Output::debug("\n");
    
    closedir(d);
    
    return true;
}

bool Santa::Setup::load_music(void) {
    Output::debug("reading music\n");
    
    music = Mix_LoadMUS("./assets/sounds/bgmusic.ogg");
    if (!music) {
        Output::fatal_error("couldn't load music: %s\n", Mix_GetError());
    }
    
    return true;
}

void Santa::Setup::santa_cleanup(void) {
    int y;
    int i;
    SurfaceMap::iterator surface_it;
    ChunkMap::iterator chunk_it;
    
    if (setup_flags.game) {
        Output::debug("freeing game\n");
        delete game;
        setup_flags.game = false;
    }
    
    if (setup_flags.highscores) {
        Output::debug("saving highscores\n");
        Config::save_highscores();
        Output::debug("freeing highscores\n");
        Config::free_highscores();
        setup_flags.highscores = false;
    }
    
    if (setup_flags.music) {
        Output::debug("freeing music\n");
        Mix_FreeMusic(music);
        setup_flags.music = false;
    }
    
    if (setup_flags.sounds) {
        Output::debug("freeing sounds");
        for (chunk_it = sounds.begin(); chunk_it != sounds.end(); chunk_it++) {
            Output::debug(" %s", chunk_it->first.c_str());
            Mix_FreeChunk(chunk_it->second);
        }
        Output::debug("\n");
        setup_flags.sounds = false;
    }
    
    if (setup_flags.level) {
        Output::debug("freeing level\n");
        for (y = 0; y < std_level_height; y++) {
            delete[] std_level_map[y];
        }
        delete[] std_level_map;
        setup_flags.level = false;
    }
    
    if (setup_flags.level_objects) {
        Output::debug("freeing level objects\n");
        for (y = 0; y < std_level_height; y++) {
            delete[] std_level_objects_map[y];
        }
        delete[] std_level_objects_map;
        setup_flags.level_objects = false;
    }
    
    if (setup_flags.chimneys) {
        Output::debug("freeing chimneys\n");
        for (i = 0; i < chimney_count; i++) {
            delete chimneys[i];
        }
        delete[] chimneys;
        setup_flags.chimneys = false;
    }
    
    if (setup_flags.text) {
        Output::debug("freeing text\n");
        delete text;
        setup_flags.text = false;
    }
    
    if (setup_flags.images) {
        Output::debug("freeing images");
        for (surface_it = images.begin(); surface_it != images.end();
             surface_it++) {
            Output::debug(" %s", surface_it->first.c_str());
            SDL_FreeSurface(surface_it->second);
        }
        Output::debug("\n");
        setup_flags.images = false;
    }
    
    if (setup_flags.audio) {
        Output::debug("closing audio\n");
        Mix_CloseAudio();
        setup_flags.audio = false;
    }
    
    if (setup_flags.sdl) {
        Output::debug("quitting sdl\n");
        SDL_Quit();
        setup_flags.sdl = false;
    }
}
