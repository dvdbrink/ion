#include <ion/gfx.hpp>
#include <ion/math.hpp>
#include <ion/wnd.hpp>

int main()
{
    bool running = true;

    ion::wnd::Window wnd(800, 600, "ion-gfx-example");
    wnd.on_closed([&](const ion::wnd::Closed &) { running = false; });

    auto& ctx = wnd.context();
    ctx.vertical_sync(true);

    ion::gfx::gl::Shader vs
    (
        ion::gfx::gl::Shader::Vertex,
        GLSL
        (
            in vec2 position;
            in vec4 color;
            out vec4 ex_Color;
            void main(void)
            {
                gl_Position = vec4(position, 0, 1);
                ex_Color = color;
            }
        )
    );
    ion::gfx::gl::Shader fs
    (
        ion::gfx::gl::Shader::Fragment,
        GLSL
        (
            in vec4 ex_Color;
            out vec4 color;
            void main(void)
            {
                color = ex_Color;
            }
        )
    );
    ion::gfx::gl::Program program(vs, fs);

    struct Vertex
    {
        ion::math::Vector2f position;
        ion::gfx::Color color;
    };

    std::vector<Vertex> vertices =
    {
        {{-.5f, -.5f}, ion::gfx::Color::Red},
        {{ .5f, -.5f}, ion::gfx::Color::Green},
        {{ .0f,  .5f}, ion::gfx::Color::Blue}
    };

    ion::gfx::gl::VertexBuffer vb;
    vb.data(&vertices.front(), sizeof(Vertex) * vertices.size(), ion::gfx::BufferUsage::StaticDraw);

    ion::gfx::gl::VertexArray va;
    va.attribute(vb, {program.attribute("position"), 2, ion::Type::Float, sizeof(Vertex), 0});
    va.attribute(vb, {program.attribute("color"), 4, ion::Type::Float, sizeof(Vertex), 8});

    while (running)
    {
        wnd.process_events();

        program.use();
        va.draw(vb, ion::gfx::PrimitiveType::Triangles, 0, vertices.size());

        ctx.swap_buffers();
    }

    return 0;
}