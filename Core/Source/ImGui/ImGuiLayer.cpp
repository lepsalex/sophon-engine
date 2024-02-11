#include "sfnpch.h"

#include "ImGuiLayer.h"

namespace Sophon {
ImGuiLayer::ImGuiLayer()
    : Layer("ImGuiLayer")
{
}

void ImGuiLayer::OnAttach()
{
}

void ImGuiLayer::OnDetach()
{
}

void ImGuiLayer::OnEvent(Event& e)
{
}
void ImGuiLayer::Begin()
{
}
void ImGuiLayer::End()
{
}
void ImGuiLayer::SetDarkThemeColors()
{
}
uint32_t ImGuiLayer::GetActiveWidgetID() const
{
    return 0;
}
}