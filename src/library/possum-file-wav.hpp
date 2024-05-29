#ifndef POSSUM_FILE_WAV_HPP
#define POSSUM_FILE_WAV_HPP

#include <string.h>

#include "possum-types.hpp"

struct  PossumFileWavHeader;
typedef PossumFileWavHeader* PossumFileWavHeaderPtr; 

struct  PossumFileWav;
typedef PossumFileWav* PossumFileWavPtr;

struct PossumFileWavHeader {
    u32 riff_str;           // "RIFF"
    u32 file_size;          // overall file size
    u32 wave_str;           // "WAVE"
    u32 fmt_str;            // "fmt\0"
    u32 format_data_length; // length of format data as listed
    u16 type_of_format;     // format type (1=PCM)
    u16 number_of_channels; // channels
    u32 sample_rate;        // samples per second, Hz
    u32 byte_rate;          // (sample rate * bits per sample * channels) / 8        
    u16 block_align;        // (BitsPerSample * Channels) / 8.1 – 8 bit mono2 – 8 bit stereo/16 bit mono4 – 16 bit stereo
    u16 bits_per_sample;    // bits per sample
    u32 data_str;           // "data"
    u32 data_size;          // data size bytes
};

#define POSSUM_FILE_WAV_HEADER_SIZE_BYTES sizeof(PossumFileWavHeader)

#define POSSUM_FILE_WAV_ASCII_RIFF 0x52494646
#define POSSUM_FILE_WAV_ASCII_WAVE 0x57415645
#define POSSUM_FILE_WAV_ASCII_FMT0 0x666d7400
#define POSSUM_FILE_WAV_ASCII_DATA 0x64617461

struct PossumFileWav {
    PossumFileWavHeaderPtr header;
    memory                 data;
};

api PossumFileWav
possum_file_wav_from_memory(
    memory wav_file_memory,
    memory wav_data_memory,
    u64    wav_memory_size_bytes);


#endif //POSSUM_FILE_WAV_HPP