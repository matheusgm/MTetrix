#ifndef AUDIOSETTINGS_H
#define AUDIOSETTINGS_H

class AudioSettings
{
public:
    AudioSettings();
    virtual ~AudioSettings();

    // Variables
    float soundVolume;

    // Functions
    void saveToFile(const std::string path);
    void loadFromFile(const std::string path);
};
#endif
