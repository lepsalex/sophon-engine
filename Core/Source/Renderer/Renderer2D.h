#pragma once

#include "Renderer/OrthographicCamera.h"

#include "Renderer/Texture.h"

namespace Sophon {
    class Renderer2D {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();

        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
        {
            DrawQuad(position, size, 0.0f, color);
        }
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
        {
            DrawQuad(position, size, 0.0f, color);
        }
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
        {
            DrawQuad(position, size, 0.0f, texture);
        }
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
        {
            DrawQuad(position, size, 0.0f, texture);
        }

        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture);
    };
}
