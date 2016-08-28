#include "audio.h"

Audio::Audio() {
  Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
}

Audio::~Audio() {
  Mix_HaltChannel(-1);
  Mix_HaltMusic();

  for (ChunkMap::iterator i = chunks.begin(); i != chunks.end(); ++i) {
    Mix_FreeChunk(i->second);
  }

  for (MusicMap::iterator i = musics.begin(); i != musics.end(); ++i) {
    Mix_FreeMusic(i->second);
  }

  Mix_CloseAudio();
}

void Audio::play_sample(const std::string& name) {
  Mix_Chunk* chunk = load_chunk(name);
  Mix_PlayChannel(-1, chunk, 0);
}

void Audio::play_music(const std::string& name) {
  Mix_Music* music = load_music(name);
  Mix_FadeInMusic(music, 1, FADE_TIME);
}

Mix_Chunk* Audio::load_chunk(const std::string& file) {
  const std::string path("content/" + file + ".wav");
  if (chunks.count(path) == 0) {
    Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
    chunks[path] = chunk;
  }

  return chunks[path];
}

Mix_Music* Audio::load_music(const std::string& file) {
  const std::string path("content/" + file + ".ogg");
  if (musics.count(path) == 0) {
    Mix_Music* music = Mix_LoadMUS(path.c_str());
    musics[path] = music;
  }

  return musics[path];
}
