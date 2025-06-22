#pragma once

#include <vector>
#include <chrono>

struct Notification
{
	ImTextureID icon;
	std::string msg;
	ImVec4 icon_color;
	float duration; // sec
};

struct ImNotify
{
public: // uselss but i use it as a separator for functions & variables
	bool Initialize()
	{
		notification_start_time = std::chrono::steady_clock::now();
		start_animation = false;
		yMulti = 0.0f;
		return true;
	}

	void Render()
	{
		if (!notification_queue.empty())
		{
			ImGuiStyle& style = ImGui::GetStyle();
			ImGuiIO& io = ImGui::GetIO(); (void)io;

			Notification& current_notification = notification_queue.front();

			auto now = std::chrono::steady_clock::now();
			float elapsed_time = std::chrono::duration<float>(now - notification_start_time).count();

			if (elapsed_time > current_notification.duration)
			{
				notification_queue.erase(notification_queue.begin());
				if (!notification_queue.empty())
				{
					notification_start_time = std::chrono::steady_clock::now();
				}

				return;
			}

			ImVec2 NotifySize = ImVec2(ImGui::GetFontSize() + style.ItemSpacing.x, 0) + ImGui::CalcTextSize(current_notification.msg.c_str()) + style.WindowPadding * 2;

			ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2 - NotifySize.x / 2, 0), ImGuiCond_Once);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.0f);
			ImGui::Begin("Notification", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoInputs);
			ImGui::PopStyleVar();
			{
				if (start_animation)
				{
					yMulti = min(yMulti + ImGui::GetIO().DeltaTime * 1.0f, 1);
					
					if (yMulti == 1)
					{
						start_animation = false;
					}
				}

				ImGui::SetWindowPos(ImVec2(ImGui::GetWindowPos().x, -NotifySize.y + (NotifySize.y + 10) * yMulti));
				ImGui::SetWindowSize(NotifySize);

				ImGui::Image(current_notification.icon, ImVec2(ImGui::GetFontSize(), ImGui::GetFontSize()), ImVec2(0, 0), ImVec2(1, 1), current_notification.icon_color);
				ImGui::SameLine();
				ImGui::Text("%s", current_notification.msg.c_str());
			}
			ImGui::End();
		}
	}

	template<ImVec4 icon_color, float duration>
	void PushNotification(ImTextureID icon, std::string message)
	{
		// Check for existing notification with the same message
		bool found = false;
		for (auto& notification : notification_queue)
		{
			if (notification.msg.find(message) == 0) // Starts with the same message
			{
				found = true;

				// Check if it already has a counter (e.g., [x2], [x3], ...)
				size_t xPos = notification.msg.find(" [x");
				if (xPos != std::string::npos)
				{
					// Find the closing bracket
					size_t closeBracket = notification.msg.find("]", xPos);
					if (closeBracket != std::string::npos)
					{
						// Extract the number and increment it
						std::string counterStr = notification.msg.substr(xPos + 3, closeBracket - (xPos + 3));
						int counter = std::stoi(counterStr);
						counter++;
						notification.msg = message + " [x" + std::to_string(counter) + "]";
					}
				}
				else
				{
					// Append [x2] if no counter exists
					notification.msg += " [x2]";
				}
				break;
			}
		}

		// If no existing notification with the same message, add a new one
		if (!found)
		{
			Notification new_notification{ icon, message, icon_color, duration };
			notification_queue.push_back(new_notification);

			start_animation = true;
			yMulti = 0.0f;

			if (notification_queue.size() == 1)
			{
				notification_start_time = std::chrono::steady_clock::now();
			}
		}
	}

public:
	std::vector<Notification> notification_queue;
	std::chrono::steady_clock::time_point notification_start_time;
	bool start_animation;
	float yMulti;
};