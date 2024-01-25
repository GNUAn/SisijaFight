// WhisperTranscriber.h
#ifndef WHISPER_TRANSCRIBER_H
#define WHISPER_TRANSCRIBER_H

#include <string>
#include <vector>

class WhisperTranscriber {
public:
    WhisperTranscriber(const std::string& model_path, bool use_gpu = true);
    void setLanguage(const std::string& language_code);
    std::string transcribe(const std::string& audio_path);
    ~WhisperTranscriber();

private:
    struct whisper_context* ctx;
    std::string language;
    bool use_gpu;

    void loadModel(const std::string& model_path);
    std::vector<float> loadWav(const std::string& filename);
};

#endif // WHISPER_TRANSCRIBER_H
