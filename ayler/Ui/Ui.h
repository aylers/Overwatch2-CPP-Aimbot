#pragma once
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_dx11.h"
#include "../ImGui/imgui_impl_win32.h"
#include "../ImGui/imgui_impl_win32.h"
#include "../ImGui/imgui_impl_dx11.h"
#include "../ImGui/imgui_internal.h"


#include "../Cheat/Cheat.h"

namespace Ui {
    int tab = 0;
    bool Checkbox(const char* label, bool* v) {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

        // Increase the radius size for a bigger circle
        const float radius = style.FramePadding.y + 6; // Adjust radius as needed
        const ImVec2 pos = window->DC.CursorPos;
        // Increase the total size of the checkbox, which includes the circle and padding
        ImU32 frame_co2 = IM_COL32(98, 0, 255, 255);

        const ImVec2 size = ImVec2(2 * radius + style.FramePadding.x * 2.0f, 2 * radius + style.FramePadding.y * 2.0f);
        const ImRect bb(pos, ImVec2(pos.x + size.x + label_size.x + style.ItemInnerSpacing.x, pos.y + size.y));
        ImGui::ItemSize(bb, style.FramePadding.y);
        if (!ImGui::ItemAdd(bb, id))
            return false;

        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held);
        if (pressed) {
            *v = !(*v);
            ImGui::MarkItemEdited(id);
        }

        const ImU32 col_bg = ImGui::GetColorU32(hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
        const ImU32 col_fg = frame_co2;

        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        // Center the circle in the bounding box vertically
        ImVec2 circle_center = ImVec2(bb.Min.x + radius, bb.Min.y + bb.GetSize().y * 0.5f);

        draw_list->AddCircleFilled(circle_center, radius, col_bg);
        if (*v) {
            // Smaller circle for checked state
            draw_list->AddCircleFilled(circle_center, radius - 4, col_fg);
        }

        // Render the label next to the checkbox
        // Align the text vertically centered with the checkbox
        ImGui::RenderText(ImVec2(circle_center.x + radius + style.ItemInnerSpacing.x, circle_center.y - label_size.y * 0.5f), label);

        return pressed;
    }

    void ApplyCustomStyle() {
        ImGuiStyle* style = &ImGui::GetStyle();

        style->ChildBorderSize = 0.2f;

        // Base window background color, a deep dark purple
        ImVec4 clearColor = ImVec4(0.13f, 0.11f, 0.20f, 1.00f); // Equivalent to a darker #221C33

        // Base color for highlights and active elements, a rich and bright purple
        ImVec4 highlightColor = ImVec4(0.58f, 0.29f, 0.88f, 1.00f); // Equivalent to #9447E1
        ImVec4 highlightHovered = ImVec4(0.68f, 0.39f, 0.98f, 1.00f); // Brighter than #AE63FA
        ImVec4 highlightActive = ImVec4(0.78f, 0.49f, 1.00f, 1.00f); // Even brighter, near full saturation

        style->Colors[ImGuiCol_WindowBg] = clearColor;
        style->Colors[ImGuiCol_Border] = highlightColor;

        // Headers
        style->Colors[ImGuiCol_Header] = highlightColor;
        style->Colors[ImGuiCol_HeaderHovered] = highlightHovered;
        style->Colors[ImGuiCol_HeaderActive] = highlightActive;

        // Buttons
        style->Colors[ImGuiCol_Button] = highlightColor;
        style->Colors[ImGuiCol_ButtonHovered] = highlightHovered;
        style->Colors[ImGuiCol_ButtonActive] = highlightActive;

        // Frame BG (for widgets like sliders, input text, etc.)
        style->Colors[ImGuiCol_FrameBg] = highlightColor;
        style->Colors[ImGuiCol_FrameBgHovered] = highlightHovered;
        style->Colors[ImGuiCol_FrameBgActive] = highlightActive;

        // Text
        style->Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f); // White for contrast

        // Other elements you might want to style
        style->Colors[ImGuiCol_Separator] = highlightColor;
        style->Colors[ImGuiCol_SeparatorHovered] = highlightHovered;
        style->Colors[ImGuiCol_SeparatorActive] = highlightActive;

        style->Colors[ImGuiCol_ScrollbarBg] = clearColor; // Background of scrollbar
        style->Colors[ImGuiCol_ScrollbarGrab] = highlightColor; // Scrollbar grab
        style->Colors[ImGuiCol_ScrollbarGrabHovered] = highlightHovered; // Hovered
        style->Colors[ImGuiCol_ScrollbarGrabActive] = highlightActive; // Active

        // Customize rounding and borders as needed
        style->WindowRounding = 5.0f; // Adjust rounding of windows
        style->FrameRounding = 4.0f; // Adjust rounding of frames
        style->GrabRounding = 4.0f; // Adjust rounding of grabbable elements like sliders

        // Adjust padding, item spacing, etc., as desired
        style->WindowPadding = ImVec2(15, 15); // Padding within a window
        style->FramePadding = ImVec2(5, 5); // Padding within a frame
        style->ItemSpacing = ImVec2(12, 8); // Spacing between items

        // Ensure your theme applies consistently across your UI
    }



	void DrawUI()
	{
        ApplyCustomStyle();
        ImGui::SetNextWindowSize(ImVec2(701, 472));
        ImGui::Begin("#test", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
        ImGui::BeginChild("##Left", ImVec2(150, ImGui::GetContentRegionAvail().y), true);
        {
            ImGui::SetCursorPosY(10);
            ImGui::SetCursorPosX(ImGui::GetContentRegionMax().x / 4.5);


            ImGui::Separator();
            ImGui::SetCursorPosY(125);
            if (ImGui::Button("Aimbot", ImVec2(ImGui::GetContentRegionAvail().x, 35)))
                tab = 0;
                    
            if (ImGui::Button("RCS", ImVec2(ImGui::GetContentRegionAvail().x, 35)))
                tab = 1;


            ImGui::SetCursorPosY(ImGui::GetContentRegionMax().y - 75);
            ImGui::Separator();
            ImGui::SetCursorPosY(ImGui::GetContentRegionMax().y - 50);
            if (ImGui::Button("Save CFG", ImVec2(ImGui::GetContentRegionAvail().x, 35)))
            {
                cfg.SaveConfig(settings, "C:\\AylersConfig\\Ayler.cfg");
            }

        }
        ImGui::EndChild();
        {
            ImGui::SameLine(0);
            ImGui::SameLine();
        }
        ImGui::BeginChild("##Right", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
        {
            switch (tab)
            {
            case 0:

                Ui::Checkbox("Enabled", &settings.enabled);
                ImGui::SliderFloat("Smoothing", &settings.smoothing, 0.01f, 1.0f, "% .01f");
                ImGui::SliderFloat("Fov", &settings.fov, 10, 300, "%1.f");
                ImGui::SliderInt("Update Interval", &settings.updateInterval, 0, 100);
                ImGui::SliderInt("Color Tolerance", &settings.colorTolerance, 0, 100);
                break;
            case 1:
                break;
            case 2:
                break;
            default:
                break;
            }
        }
        ImGui::EndChild();

        ImGui::End();
	}
}