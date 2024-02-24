#include <Sophon.h>

class ExampleLayer : public Sophon::Layer {
public:
    ExampleLayer()
        : Layer("Example")
        , m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
        , m_CameraPosition(0.0f, 0.0f, 0.0f)
        , m_CameraSpeed(2.0f)
    {
        // TODO: TEMP RENDERING TEST START
        m_TriangleVertexArray = Sophon::VertexArray::Create();
        float triangle_vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.9f, 0.4f, 0.4f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.4f, 0.9f, 0.4f, 1.0f,
            0.0f, 0.5f, 0.0f, 0.4f, 0.4f, 0.9f, 1.0f, // clang-format-ignore
        };

        auto triangleVertexBuffer = Sophon::VertexBuffer::Create(triangle_vertices, sizeof(triangle_vertices));
        triangleVertexBuffer->SetLayout(Sophon::BufferLayout {
            { Sophon::BufferElement(Sophon::ShaderDataType::Float3, "a_Position") },
            { Sophon::BufferElement(Sophon::ShaderDataType::Float4, "a_Color") } });
        m_TriangleVertexArray->AddVertexBuffer(triangleVertexBuffer);

        uint32_t triangleIndices[3] = { 0, 1, 2 };
        m_TriangleVertexArray->SetIndexBuffer(Sophon::IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t)));

        m_SquareVertexArray = Sophon::VertexArray::Create();
        float square_vertices[5 * 4] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f // clang-format-ignore
        };

        auto squareVertexBuffer = Sophon::VertexBuffer::Create(square_vertices, sizeof(square_vertices));
        squareVertexBuffer->SetLayout(Sophon::BufferLayout {
            { Sophon::BufferElement(Sophon::ShaderDataType::Float3, "a_Position") },
            { Sophon::BufferElement(Sophon::ShaderDataType::Float2, "a_TexCoord") } });
        m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);
        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        m_SquareVertexArray->SetIndexBuffer(Sophon::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

        auto flatColorShader = m_ShaderLibrary.Load("Assets/Shaders/FlatColor.glsl");
        auto textureShader = m_ShaderLibrary.Load("Assets/Shaders/Texture.glsl");

        m_Texture = Sophon::Texture2D::Create("Assets/Textures/Checkerboard.png");
        m_LogoTexture = Sophon::Texture2D::Create("Assets/Textures/Opengl-logo.png");

        textureShader->Bind();
        textureShader->SetInt("u_Texture", 0);
        // TODO: TEMP RENDERING TEST END
    }

    void OnUpdate(Sophon::Timestep ts) override
    {
        // CAMERA MOVE TEST
        if (Sophon::Input::IsKeyPressed(Sophon::Key::Left))
            m_CameraPosition.x -= m_CameraSpeed * ts;

        if (Sophon::Input::IsKeyPressed(Sophon::Key::Right))
            m_CameraPosition.x += m_CameraSpeed * ts;

        if (Sophon::Input::IsKeyPressed(Sophon::Key::Up))
            m_CameraPosition.y += m_CameraSpeed * ts;

        if (Sophon::Input::IsKeyPressed(Sophon::Key::Down))
            m_CameraPosition.y -= m_CameraSpeed * ts;

        // TODO: TEMP RENDERING TEST START
        Sophon::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        Sophon::RenderCommand::Clear();

        m_Camera.SetPosition(m_CameraPosition);

        Sophon::Renderer::BeginScene(m_Camera);

        // Get the shaders
        auto textureShader = m_ShaderLibrary.Get("Texture");
        auto flatColorShader = m_ShaderLibrary.Get("FlatColor");

        // Draw the checkerboard
        m_Texture->Bind();
        auto squareScale = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));
        glm::vec3 squarePos(0.0f, 0.0f, 0.0f); // anything below Z=0.0f gets clipped
        Sophon::Renderer::Submit(textureShader, m_SquareVertexArray, glm::translate(glm::mat4(1.0f), squarePos) * squareScale);

        // Draw the logo on top
        m_LogoTexture->Bind();
        auto logoScale = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));
        glm::vec3 logoPos(0.0f, 0.0f, 0.1f); // z-indexed draw order
        Sophon::Renderer::Submit(textureShader, m_SquareVertexArray, glm::translate(glm::mat4(1.0f), logoPos) * logoScale);

        // Draw the triangle with a flat color to the side
        flatColorShader->Bind();
        flatColorShader->SetFloat4("u_Color", m_FlatShaderColor);
        auto triangleScale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
        glm::vec3 trianglePos(-0.3f, -0.3f, 0.2f); // z-indexed draw order
        Sophon::Renderer::Submit(flatColorShader, m_TriangleVertexArray, glm::translate(glm::mat4(1.0f), trianglePos) * triangleScale);

        Sophon::Renderer::EndScene();
        // TODO: TEMP RENDERING TEST END
    }

    void OnEvent(Sophon::Event& event) override
    {
    }

private:
    // TODO: TEMP RENDERING TEST START
    Sophon::ShaderLibrary m_ShaderLibrary;
    Sophon::Ref<Sophon::VertexArray> m_TriangleVertexArray;
    Sophon::Ref<Sophon::VertexArray> m_SquareVertexArray;
    Sophon::Ref<Sophon::Texture2D> m_Texture, m_LogoTexture;
    Sophon::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraSpeed;
    glm::vec4 m_FlatShaderColor = { 0.2f, 0.3f, 0.8f, 1.0f };
    // TODO: TEMP RENDERING TEST END
};

class App : public Sophon::Application {
public:
    App()
    {
        PushLayer(new ExampleLayer());
    }

    ~App()
    {
    }
};

Sophon::Application* Sophon::CreateApplication()
{
    return new App();
}
