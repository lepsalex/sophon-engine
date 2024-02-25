#include "sfnpch.h"
#include "Renderer/Renderer2D.h"

#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"
#include "Renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Sophon {
    struct Renderer2DData {
        Ref<VertexArray> QuadVertexArray;
        Ref<Shader> QuadShader;
        Ref<Texture2D> WhiteTexture;
    };

    static Renderer2DData s_Data;

    void Renderer2D::Init()
    {
        SFN_PROFILE_FUNCTION();

        s_Data.QuadVertexArray = VertexArray::Create();

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

        s_Data.QuadVertexArray->AddVertexBuffer(squareVertexBuffer);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        s_Data.QuadVertexArray->SetIndexBuffer(Sophon::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

        s_Data.WhiteTexture = Texture2D::Create();
        uint32_t whiteTextureData = 0xffffffff;
        s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

        s_Data.QuadShader = Shader::Create("Assets/Shaders/Texture.glsl");
        s_Data.QuadShader->Bind();
        s_Data.QuadShader->SetInt("u_Texture", 0);
    }

    void Renderer2D::Shutdown()
    {
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        SFN_PROFILE_FUNCTION();

        s_Data.QuadShader->Bind();
        s_Data.QuadShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
    }

    void Renderer2D::EndScene()
    {
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, rotation, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
    {
        SFN_PROFILE_FUNCTION();

        s_Data.QuadShader->SetFloat4("u_Color", color);
        s_Data.WhiteTexture->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        s_Data.QuadShader->SetMat4("u_Transform", transform);

        s_Data.QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, rotation, texture);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture)
    {
        SFN_PROFILE_FUNCTION();

        s_Data.QuadShader->SetFloat4("u_Color", glm::vec4(1.0f));
        texture->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        s_Data.QuadShader->SetMat4("u_Transform", transform);

        s_Data.QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
    }
}
