// WhisperTranscriber.cpp
#include "Transcriber.hpp"
#include "whisper.h"
#include <fstream>
#include <stdexcept>
#include <cstdint>
#include <cstring>
#include <vector>

WhisperTranscriber::WhisperTranscriber(const std::string& model_path, bool use_gpu) : use_gpu(use_gpu), ctx(nullptr) {
    loadModel(model_path);
}

void WhisperTranscriber::loadModel(const std::string& model_path) {
    if (this->ctx) {
        whisper_free(this->ctx); // Free previous context if exists
    }

    struct whisper_context_params cparams;
    cparams.use_gpu = this->use_gpu;
    this->ctx = whisper_init_from_file_with_params(model_path.c_str(), cparams);

    if (this->ctx == nullptr) {
        throw std::runtime_error("Failed to initialize Whisper context with model: " + model_path);
    }

    this->language = "en"; // Default language
}

void WhisperTranscriber::setLanguage(const std::string& language_code) {
    this->language = language_code;
}

std::string WhisperTranscriber::transcribe(const std::string& audio_path) {
    auto pcmf32 = loadWav(audio_path); // Load WAV file into vector<float>

    whisper_full_params wparams = whisper_full_default_params(WHISPER_SAMPLING_GREEDY);
    wparams.language = this->language.c_str();

    if (whisper_full_parallel(this->ctx, wparams, pcmf32.data(), pcmf32.size(), 1) != 0) {
        throw std::runtime_error("Failed to process audio");
    }

    std::string transcription = ""; // Extract transcription from ctx

    return transcription;
}

WhisperTranscriber::~WhisperTranscriber() {
    if (this->ctx) {
        whisper_free(this->ctx);
    }
}

std::vector<float> WhisperTranscriber::loadWav(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    // Read WAV header
    char buffer[44];
    file.read(buffer, 44);

    // Check if the file is a valid WAV file
    if (std::strncmp(buffer, "RIFF", 4) != 0 || std::strncmp(buffer + 8, "WAVE", 4) != 0) {
        throw std::runtime_error("Invalid WAV file: " + filename);
    }

    // Extract audio format details
    int16_t audioFormat = *reinterpret_cast<int16_t*>(buffer + 20);
    int16_t numChannels = *reinterpret_cast<int16_t*>(buffer + 22);
    int32_t sampleRate = *reinterpret_cast<int32_t*>(buffer + 24);
    int16_t bitsPerSample = *reinterpret_cast<int16_t*>(buffer + 34);

    // Only handle uncompressed PCM, mono
    if (audioFormat != 1 || numChannels != 1) {
        throw std::runtime_error("Unsupported WAV format (only uncompressed PCM mono supported)");
    }

    // Determine the number of samples
    int32_t dataSize = *reinterpret_cast<int32_t*>(buffer + 40);
    size_t numSamples = dataSize / (bitsPerSample / 8);

    // Read and convert samples
    std::vector<float> samples(numSamples);
    for (size_t i = 0; i < numSamples; ++i) {
        if (bitsPerSample == 16) {
            int16_t sample;
            file.read(reinterpret_cast<char*>(&sample), sizeof(sample));
            samples[i] = sample / 32768.0f; // Normalize 16-bit PCM
        }
        else {
            throw std::runtime_error("Unsupported bit depth (only 16-bit supported)");
        }
    }

    return samples;
}
