#include <ion/sfx/al/sound.hpp>

#include <stb/vorbis.c>

#include <stdexcept>

namespace ion { namespace sfx { namespace al
{
    Sound::Sound(const std::string& fileName) :
        _channel_count(0),
        _sample_count(0),
        _sample_rate(0)
    {
        stb_vorbis* file = stb_vorbis_open_filename(const_cast<char*>(fileName.c_str()), 0, 0);
        if (file)
        {
            stb_vorbis_info info = stb_vorbis_get_info(file);
            _channel_count = info.channels;
            _sample_rate = info.sample_rate;

            int samples = stb_vorbis_stream_length_in_samples(file) * _channel_count;
            _sample_count  = samples;
            _samples.resize(samples);

            stb_vorbis_get_samples_short_interleaved(file, _channel_count, &_samples.front(), samples);

            stb_vorbis_close(file);
        }
        else
        {
            throw std::runtime_error("Unable to open audio file");
        }
    }

    Sound::~Sound()
    {

    }

    uint32_t Sound::channel_count() const
    {
        return _channel_count;
    }

    uint64_t Sound::sample_count() const
    {
        return _sample_count;
    }

    uint32_t Sound::sample_rate() const
    {
        return _sample_rate;
    }

    const std::vector<int16_t> &Sound::samples() const
    {
        return _samples;
    }
}}}