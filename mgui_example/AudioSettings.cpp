#include "stdafx.h"
#include "AudioSettings.h"

AudioSettings::AudioSettings()
{
    this->soundVolume = 100.f;
}

AudioSettings::~AudioSettings()
{
}

// Functions
void AudioSettings::saveToFile(const std::string path)
{
    std::ofstream ofs(path);

    if (ofs.is_open()) {
        ofs << this->soundVolume;
    }

    ofs.close();
}
void AudioSettings::loadFromFile(const std::string path)
{
    std::ifstream ifs(path);

    if (ifs.is_open()) {
        ifs >> this->soundVolume;
    }

    ifs.close();
}

