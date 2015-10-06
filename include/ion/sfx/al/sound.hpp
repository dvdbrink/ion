#pragma once

#include <string>
#include <vector>

namespace ion { namespace sfx { namespace al
{
    class Sound
    {
    public:
        Sound(const std::string&);
        virtual ~Sound();

        uint32_t channel_count() const;
        uint64_t sample_count() const;
        uint32_t sample_rate() const;

        const std::vector<int16_t>& samples() const;

    private:
        uint32_t _channel_count;
        uint64_t _sample_count;
        uint32_t _sample_rate;

        std::vector<int16_t> _samples;
    };
}}}