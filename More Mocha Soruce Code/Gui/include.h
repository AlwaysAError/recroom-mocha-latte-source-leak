static auto Checkbox = [&](const char* label, bool* value)
	{
		ImGui::PushID(label);
		ImGui::Checkbox(label, value);
		ImGui::PopID();
		ImGui::Spacing();
	};

ImVec4 HSVToRGB(float h, float s, float v)
{
	int h_i = static_cast<int>(h * 6.0f);
	float f = h * 6.0f - h_i;
	float p = v * (1.0f - s);
	float q = v * (1.0f - f * s);
	float t = v * (1.0f - (1.0f - f) * s);

	switch (h_i % 6) {
	case 0: return ImVec4(v, t, p, 1.0f);
	case 1: return ImVec4(q, v, p, 1.0f);
	case 2: return ImVec4(p, v, t, 1.0f);
	case 3: return ImVec4(p, q, v, 1.0f);
	case 4: return ImVec4(t, p, v, 1.0f);
	case 5: return ImVec4(v, p, q, 1.0f);
	default: return ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // Default to white
	}
}

void RainbowText(const char* text, float speed, ImVec2* position = nullptr, float opacity = 1.0f)
{
	if (position) {
		ImGui::SetCursorPos(*position);
	}

	float time = ImGui::GetTime() * speed;
	float gradientStep = 1.0f / strlen(text);

	for (int i = 0; i < strlen(text); ++i)
	{
		float hue = fmodf(time - static_cast<float>(i) * gradientStep, 1.0f);
		ImVec4 color = HSVToRGB(hue, 1.0f, 1.0f);
		color.w = opacity; // Adjust opacity

		ImGui::PushStyleColor(ImGuiCol_Text, color);
		ImGui::Text("%c", text[i]);
		ImGui::SameLine(0, 0);
		ImGui::PopStyleColor();
	}
	ImGui::NewLine(); // Move to next line after text
}


ImVec4 InterpolateColor(const ImVec4& color1, const ImVec4& color2, float t)
{
	float inverse_t = 1.0f - t;
	return ImVec4(
		inverse_t * color1.x + t * color2.x,
		inverse_t * color1.y + t * color2.y,
		inverse_t * color1.z + t * color2.z,
		color1.w);
}


void GradientText(const char* text, float speed, const ImVec4& color1, const ImVec4& color2, ImVec2* position = nullptr)
{
	if (position) {
		ImGui::SetCursorPos(*position);
	}

	float time = ImGui::GetTime() * speed;
	float gradientStep = 1.0f / strlen(text);

	for (int i = 0; i < strlen(text); ++i)
	{
		float t = fmodf(time - i * gradientStep, 2.0f);  // Smoothly varying 't' from 0 to 2

		if (t > 1.0f)
			t = 2.0f - t;  // Reverse 't' for the second half of the cycle

		ImVec4 color = InterpolateColor(color1, color2, t);

		ImGui::PushStyleColor(ImGuiCol_Text, color);
		ImGui::Text("%c", text[i]);
		ImGui::SameLine(0, 0);
		ImGui::PopStyleColor();
	}
	ImGui::NewLine(); // Move to next line after text
}

void DrawOutlinedText(const char* text, ImVec2 pos = ImGui::GetCursorScreenPos(), ImU32 outline_color = ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), float outline_thickness = 1.0f) {
	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	// Draw outline in 8 directions
	draw_list->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(pos.x - outline_thickness, pos.y), outline_color, text);
	draw_list->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(pos.x + outline_thickness, pos.y), outline_color, text);
	draw_list->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(pos.x, pos.y - outline_thickness), outline_color, text);
	draw_list->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(pos.x, pos.y + outline_thickness), outline_color, text);
	draw_list->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(pos.x - outline_thickness, pos.y - outline_thickness), outline_color, text);
	draw_list->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(pos.x + outline_thickness, pos.y - outline_thickness), outline_color, text);
	draw_list->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(pos.x - outline_thickness, pos.y + outline_thickness), outline_color, text);
	draw_list->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(pos.x + outline_thickness, pos.y + outline_thickness), outline_color, text);
}

#include "PlayerList/Sections/Exploits.h"
#include "PlayerList/Sections/Fun.h"
#include "PlayerList/Sections/Misc.h"
#include "PlayerList/Sections/PlayerInfo.h"
#include "PlayerList/Sections/Teleports.h"
#include "PlayerList/Sections/Test.h"
#include "PlayerList/PlayerList.h"
#include "playerlist.h"
#include "CppExplorer.h"