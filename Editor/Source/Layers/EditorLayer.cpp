#include "EditorLayer.h"

#include <imgui.h>

namespace Sophon {
    EditorLayer::EditorLayer()
        : Layer("EditorLayer")
    {
    }

    void EditorLayer::OnAttach()
    {
        SFN_PROFILE_FUNCTION();

        // Load textures
        m_CheckerboardTexture = Texture2D::Create("Assets/Textures/Checkerboard.png");
        m_LogoTexture = Texture2D::Create("Assets/Textures/Opengl-logo.png");

        // Setup Framebuffer
        FramebufferSpecification fbSpec;
        fbSpec.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::Depth };
        fbSpec.Width = 1280;
        fbSpec.Height = 720;
        m_Framebuffer = Framebuffer::Create(fbSpec);

        m_EditorScene = CreateRef<Scene>();
        m_ActiveScene = m_EditorScene;

        m_EditorCamera = EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f);

        // TEMP ENTITY CREATION TESTING

        // Random shape sprites...
        auto redSquare = m_ActiveScene->CreateEntity("Red Square");
        auto& redSquareTransform = redSquare.GetComponent<TransformComponent>();
        redSquareTransform.Translation = { -1.0f, 0.0f, 0.1f };
        redSquareTransform.Scale = { 0.8f, 0.8f, 1.0f };
        SpriteRendererComponent redSquareSpriteRenderer { { 0.8f, 0.2f, 0.3f, 1.0f } };
        redSquare.AddComponent<SpriteRendererComponent>(redSquareSpriteRenderer);

        auto rotatedBlueSquare = m_ActiveScene->CreateEntity("Rotated Blue Square");
        auto& rotatedBlueSquareTransform = rotatedBlueSquare.GetComponent<TransformComponent>();
        rotatedBlueSquareTransform.Translation = { 0.5f, -0.5f, 0.1f };
        rotatedBlueSquareTransform.Scale = { 0.5f, 0.75f, 1.0f };
        rotatedBlueSquareTransform.Rotation = { 0.0f, 0.0f, 45.0f };
        SpriteRendererComponent rotatedBlueSquareSpriteRenderer { { 0.2f, 0.3f, 0.8f, 1.0f } };
        rotatedBlueSquare.AddComponent<SpriteRendererComponent>(rotatedBlueSquareSpriteRenderer);

        auto checkerBoard = m_ActiveScene->CreateEntity("Checkerboard");
        auto& checkerBoardTransform = checkerBoard.GetComponent<TransformComponent>();
        checkerBoardTransform.Translation = { 0.0f, 0.0f, 0.0f };
        checkerBoardTransform.Scale = { 5.0f, 5.0f, 1.0f };
        SpriteRendererComponent checkerBoardRenderer { { 0.9f, 0.8f, 0.7f, 1.0f } };
        checkerBoardRenderer.Texture = m_CheckerboardTexture;
        checkerBoardRenderer.TilingFactor = 5.0f;
        checkerBoard.AddComponent<SpriteRendererComponent>(checkerBoardRenderer);

        auto logo = m_ActiveScene->CreateEntity("Logo");
        auto& logoTransform = logo.GetComponent<TransformComponent>();
        logoTransform.Translation = { 0.0f, 0.0f, 0.2f };
        SpriteRendererComponent logoRenderer { m_LogoTexture };
        logo.AddComponent<SpriteRendererComponent>(logoRenderer);

        // Tile sprites ...
        for (float y = -5.0f; y < 5.0f; y += 0.5f) {
            for (float x = -5.0f; x < 5.0f; x += 0.5f) {
                auto tile = m_ActiveScene->CreateEntity(std::format("Tile {}:{}", x, y));
                auto& tileTransform = tile.GetComponent<TransformComponent>();
                tileTransform.Translation = { x, y, -0.1f };
                tileTransform.Scale = { 0.45f, 0.45f, 1.0f };
                SpriteRendererComponent tileRenderer { { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f } };
                tile.AddComponent<SpriteRendererComponent>(tileRenderer);
            }
        }
        //  END TEMP ENTITY CREATION TESTING
    }

    void EditorLayer::OnDetach()
    {
    }

    void EditorLayer::OnUpdate(Timestep ts)
    {
        SFN_PROFILE_FUNCTION();

        // Handle Window Resizing
        m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);

        if (FramebufferSpecification spec = m_Framebuffer->GetSpecification();
            m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
            (spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y)) {
            m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
            m_EditorCamera.SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);
        }

        // Reset the Renderer
        Renderer2D::ResetStats();
        m_Framebuffer->Bind();
        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        RenderCommand::Clear();

        // Clear our entityID attachment to -1
        m_Framebuffer->ClearAttachment(1, -1);

        // Run update/draw loops
        m_EditorCamera.OnUpdate(ts);
        m_ActiveScene->OnUpdateEditor(ts, m_EditorCamera);

        m_Framebuffer->Unbind();
    }

    void EditorLayer::OnImGuiRender()
    {
        SFN_PROFILE_FUNCTION();

        static bool dockspaceOpen = true;
        static bool opt_fullscreen_persistent = true;
        bool opt_fullscreen = opt_fullscreen_persistent;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen) {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->Pos);
            ImGui::SetNextWindowSize(viewport->Size);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("Sophon DockSpace", &dockspaceOpen, window_flags);
        ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO& io = ImGui::GetIO();
        ImGuiStyle& style = ImGui::GetStyle();
        float minWinSizeX = style.WindowMinSize.x;
        style.WindowMinSize.x = 370.0f;
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
            ImGuiID dockspace_id = ImGui::GetID("SophonDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        style.WindowMinSize.x = minWinSizeX;

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Exit"))
                    Application::Get().Close();

                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        ImGui::Begin("Stats");
        auto stats = Renderer2D::GetStats();
        ImGui::Text("Renderer2D Stats:");
        ImGui::Text("Draw Calls: %d", stats.DrawCalls);
        ImGui::Text("Quads: %d", stats.QuadCount);
        ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
        ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
        ImGui::End();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2 { 0, 0 });
        ImGui::Begin("Viewport");
        auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
        auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
        auto viewportOffset = ImGui::GetWindowPos();
        m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
        m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

        m_ViewportFocused = ImGui::IsWindowFocused();
        m_ViewportHovered = ImGui::IsWindowHovered();

        Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportHovered);

        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

        uint64_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
        ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2 { m_ViewportSize.x, m_ViewportSize.y }, ImVec2 { 0, 1 }, ImVec2 { 1, 0 });

        ImGui::End();
        ImGui::PopStyleVar();

        ImGui::End();
    }

    void EditorLayer::OnEvent(Event& e)
    {
        m_EditorCamera.OnEvent(e);

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<KeyPressedEvent>(SFN_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
        dispatcher.Dispatch<MouseButtonPressedEvent>(SFN_BIND_EVENT_FN(EditorLayer::OnMouseButtonPressed));
    }

    bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
    {
        return false;
    }

    bool EditorLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e)
    {
        return false;
    }
}
