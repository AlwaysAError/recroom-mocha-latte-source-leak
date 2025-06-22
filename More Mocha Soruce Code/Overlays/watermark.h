#pragma once
#include "../Dependencies/Microsoft DirectX SDK/Include/xnamath.h"

#ifndef PROD
const char* buildver = "dev"; // #define PROD in logger.h for prod builds!!! (the builds we give out to the customers)
#else
#ifdef CHEAP
const char* buildver = "git";
#else
const char* buildver = "vip";
#endif
#endif

const std::string watermark = "MOCHA | That's ketamine, huh? (Huh), that's not enough (Schyeah) Tryna take care of me, no (Turn up), it's in my blood, uh v2.1.1-" + std::string(buildver) + "-" + std::string(TOSTRING(GIT_COMMIT_HASH));
ImVec2 watermarkSize{ 0, 0 };

ImVec2 dvdPos = ImVec2(100, 100);
ImVec2 dvdVelocity = ImVec2(1.5f, 1.5f);
ImVec4 dvdColor = ImVec4(1, 1, 1, 1);

bool firstexec = false;
std::string watermarkHash = "";
std::string CalculateMD5(const std::string& input) {
	CryptoPP::MD5 hash;
	std::string digest;

	CryptoPP::StringSource(
		input,                          // The input string to hash
		true,                           // Pump all data through the filter
		new CryptoPP::HashFilter(hash,  // Compute MD5 hash
			new CryptoPP::HexEncoder(   // Convert to hexadecimal
				new CryptoPP::StringSink(digest),  // Store result in digest
				false                   // Lowercase output
			)
		)
	);

	return digest;
}

void WaterMark() {

#ifdef PROD
	if (!firstexec)
	{
		watermarkHash = CalculateMD5(watermark);
		firstexec = true;
	}
	else
	{
		if (watermarkHash != CalculateMD5(watermark))
			exit(-1);
	}
#endif
	
	if ((watermarkSize.x == 0.0f) && (watermarkSize.y == 0)) { // so we don't calculate this every render lmao
		watermarkSize.y = ImGui::CalcTextSize(watermark.c_str()).y;
	}

	ImGui::SetNextWindowSize(watermarkSize); // size of watermark
	ImGui::SetNextWindowBgAlpha(0.75f);
	ImGui::SetNextWindowPos({ 0, 0 });
	ImGui::Begin("watermark", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs /*| ImGuiWindowFlags_NoBackground*/ | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBringToFrontOnFocus);

	/// purple
	//ImVec4 lightPurple = ImVec4(0.74f, 0.58f, 0.98f, 1.0f);
	//ImVec4 darkPurple = ImVec4(0.407843137f, 0.254901961f, 0.62745098f, 1.0f);

	/// red
	ImVec4 lightPurple = ImVec4(0.953f, 0.337f, 0.337f, 1.0f);
	ImVec4 darkPurple = ImVec4(0.498f, 0.035f, 0.035f, 1.0f);

	///blue
	//ImVec4 lightPurple = ImVec4(0.337f, 0.627f, 0.953f, 1.0f);
	//ImVec4 darkPurple = ImVec4(0.035f, 0.149f, 0.498f, 1.0f);

	//ImVec4 blue = ImVec4(0.2118f, 0.8314f, 1.0f, 1.0f);
	//ImVec4 pink = ImVec4(1.0f, 0.2118f, 0.8314f, 1.0f);

	GradientText(watermark.c_str(), 0.7, lightPurple, darkPurple);
	ImGui::End();

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGuiIO& io = ImGui::GetIO();
	ImGui::SetNextWindowSize(io.DisplaySize);
	ImGui::Begin("dvd watermark window", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoScrollbar);

	if (globals::Open) {

		ImGuiIO& io = ImGui::GetIO();
		ImVec2 screenSize = io.DisplaySize;

		ImVec2 textSize = ImGui::CalcTextSize("Mocha");

		dvdPos.x += dvdVelocity.x;
		dvdPos.y += dvdVelocity.y;

		if (dvdPos.x <= 0.0f || dvdPos.x + textSize.x >= screenSize.x)
		{
			dvdVelocity.x *= -1.0f;
			dvdColor = ImVec4((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1.0f); // Change color on bounce
		}

		if (dvdPos.y <= 0.0f || dvdPos.y + textSize.y >= screenSize.y)
		{
			dvdVelocity.y *= -1.0f;
			dvdColor = ImVec4((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1.0f); // Change color on bounce
		}

		ImGui::PushFont(pGui->m_Fonts.BigFont);
		ImGui::SetCursorPos(dvdPos);
		ImGui::TextColored(dvdColor, "Mocha");
		ImGui::PopFont();

	}

	ImGui::End();
}