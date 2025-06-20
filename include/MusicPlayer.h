#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <random>
#include <atomic>
#include <filesystem>

class MusicPlayer
{
public:
    static MusicPlayer &getInstance();

    void start();
    void stop();
    void setVolume(float volume);
    void addMusicFile(const std::string &filePath);

    // Eliminar copias
    MusicPlayer(const MusicPlayer &) = delete;
    void operator=(const MusicPlayer &) = delete;

private:
    MusicPlayer();
    ~MusicPlayer();

    void playerThread();
    void loadMusicFiles();
    std::string getRandomMusicFile();

    std::vector<std::string> musicFiles;
    sf::Music music;
    std::thread playerThreadHandle;
    std::mutex musicMutex;
    std::atomic<bool> running;
    std::atomic<float> volume;
    std::random_device rd;
    std::mt19937 rng;
};

#endif // MUSICPLAYER_H