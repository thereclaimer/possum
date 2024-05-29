#pragma once

#include "possum-file-wav.hpp"

external PossumFileWav
possum_file_wav_from_memory(
    memory wav_file_memory,
    memory wav_data_memory_preallocated,
    u64    wav_memory_size_bytes) {

    //first, if we're less than the size of the header, this is
    //not a valid .wav file
    if (wav_memory_size_bytes <= POSSUM_FILE_WAV_HEADER_SIZE_BYTES) {
        return(NULL);
    }

    //copy the data
    memmove(
        wav_data_memory_preallocated,
        wav_file_memory,
        wav_memory_size_bytes);

    //this is a trivial file format, we can just cast the memory
    //directly to the wave header
    PossumFileWavHeaderPtr wav_header_ptr = (PossumFileWavHeaderPtr)wav_memory;

    //make sure the data is valid
    PossumFileWavHeader wav_header = *wav_header_ptr;
    b8 valid_riff_str = (wav_header.riff_str == POSSUM_FILE_WAV_ASCII_RIFF);
    b8 valid_wave_str = (wav_header.wave_str == POSSUM_FILE_WAV_ASCII_WAVE);
    b8 valid_fmt_str  = (wav_header.fmt_str  == POSSUM_FILE_WAV_ASCII_FMT0);
    b8 valid_data_str = (wav_header.data_str == POSSUM_FILE_WAV_ASCII_DATA);

    if (
        !valid_riff_str ||
        !valid_wave_str ||
        !valid_fmt_str  ||
        !valid_data_str) {

        return(NULL);
    }

    //the .wav data is at the end of the header
    memory wav_data = wav_memory + POSSUM_FILE_WAV_HEADER_SIZE_BYTES;

    //thats it we're done
    PossumFileWav wav = {0};
    wav.header = wav_header;
    wav.data   = wav_data;

    return(wav);
}