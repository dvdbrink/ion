#include <ion/log.hpp>
#include <ion/sfx.hpp>

#include <chrono>
#include <thread>

using namespace ion;

int main()
{
    sfx::al::Device device;
    sfx::al::Context context(device);

    sfx::al::Sound sound("res/fire.ogg");
    log::out() << "Channels: " << sound.channel_count()
               << ", Samples: " << sound.sample_count()
               << ", Sample rate: " << sound.sample_rate();

    sfx::al::Buffer buffer;
    buffer.write(sound);

    sfx::al::Source source(buffer);
    source.play();

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    return 0;
}