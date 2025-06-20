#include "../include/MusicPlayer.h"
#include <iostream>
#include <chrono>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

MusicPlayer &MusicPlayer::getInstance()
{
    static MusicPlayer instance;
    return instance;
}

MusicPlayer::MusicPlayer() : running(false),
                             volume(70.0f),
                             rd(),
                             rng(rd())
{

    loadMusicFiles();
}

MusicPlayer::~MusicPlayer()
{
    stop();
}

void MusicPlayer::loadMusicFiles()
{
    const std::string mediaPath = "media/";

    try
    {
        if (fs::exists(mediaPath))
        {
            for (const auto &entry : fs::directory_iterator(mediaPath))
            {
                const auto &path = entry.path();
                if (path.extension() == ".ogg" ||
                    path.extension() == ".wav" ||
                    path.extension() == ".flac")
                {
                    musicFiles.push_back(path.string());
                }
            }
        }

        if (musicFiles.empty())
        {
            std::cerr << "Advertencia: No se encontraron archivos de música en la carpeta media/\n";
        }
    }
    catch (const fs::filesystem_error &e)
    {
        std::cerr << "Error al leer la carpeta media/: " << e.what() << "\n";
    }
}

void MusicPlayer::start()
{
    if (running)
        return;

    running = true;
    playerThreadHandle = std::thread(&MusicPlayer::playerThread, this);
}

void MusicPlayer::stop()
{
    if (running)
    {
        running = false;
        if (playerThreadHandle.joinable())
        {
            playerThreadHandle.join();
        }
    }
}

void MusicPlayer::setVolume(float vol)
{
    volume = std::clamp(vol, 0.0f, 100.0f);
    if (music.getStatus() == sf::Music::Playing)
    {
        music.setVolume(volume);
    }
}

void MusicPlayer::addMusicFile(const std::string &filePath)
{
    std::lock_guard<std::mutex> lock(musicMutex);
    musicFiles.push_back(filePath);
}

std::string MusicPlayer::getRandomMusicFile()
{
    std::lock_guard<std::mutex> lock(musicMutex);

    if (musicFiles.empty())
    {
        return "";
    }

    std::uniform_int_distribution<size_t> dist(0, musicFiles.size() - 1);
    return musicFiles[dist(rng)];
}

void MusicPlayer::playerThread()
{
    while (running)
    {
        std::string musicFile = getRandomMusicFile();

        if (musicFile.empty())
        {
            // Esperar antes de reintentar si no hay archivos
            std::this_thread::sleep_for(std::chrono::seconds(5));
            continue;
        }

        {
            std::lock_guard<std::mutex> lock(musicMutex);
            if (!music.openFromFile(musicFile))
            {
                std::cerr << "Error al cargar archivo de música: " << musicFile << "\n";
                continue;
            }

            music.setLoop(false);
            music.setVolume(volume);
            music.play();
        }

        // Reproducir hasta que termine o se detenga
        while (running && music.getStatus() == sf::Music::Playing)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    // Asegurarse de detener la música al salir
    music.stop();
}