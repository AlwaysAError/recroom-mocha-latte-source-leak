#pragma once

#include <vector>
#include <cmath>
#include <random>

struct Particle {
    float x, y;           // Position
    float vx, vy;         // Velocity
    ImVec4 color;         // Particle color
};

class ParticleSystem {
private:
    std::vector<Particle> particles;
    std::random_device rd;
    std::mt19937 gen;
    int currentParticleCount;

public:
    ParticleSystem() : gen(rd()), currentParticleCount(0) {
        InitializeParticles();
    }

    ~ParticleSystem() {
        particles.clear();
        particles.shrink_to_fit();
    }

    void InitializeParticles() {
        // Clear existing particles
        particles.clear();
        particles.shrink_to_fit();

        // Reserve space for maximum particles to prevent reallocation
        particles.reserve(globals::particles::maxParticles);

        // Initialize particles
        for (int i = 0; i < globals::particles::maxParticles; i++) {
            std::uniform_real_distribution<> disX(0, ImGui::GetIO().DisplaySize.x);
            std::uniform_real_distribution<> disY(0, ImGui::GetIO().DisplaySize.y);
            std::uniform_real_distribution<> disV(-globals::particles::particleSpeed, globals::particles::particleSpeed);

            Particle p;
            p.x = disX(gen);
            p.y = disY(gen);
            p.vx = disV(gen);
            p.vy = disV(gen);
            p.color = globals::particles::particleColor;
            particles.push_back(p);
        }
        currentParticleCount = globals::particles::maxParticles;
    }

    void Update(float deltaTime) {
        // Check if particle count changed
        if (currentParticleCount != globals::particles::maxParticles) {
            InitializeParticles();
        }

        // Update particle colors if they changed
        static ImVec4 lastParticleColor = globals::particles::particleColor;
        if (memcmp(&lastParticleColor, &globals::particles::particleColor, sizeof(ImVec4)) != 0) {
            for (auto& p : particles) {
                p.color = globals::particles::particleColor;
            }
            lastParticleColor = globals::particles::particleColor;
        }

        ImVec2 mousePos = ImGui::GetMousePos();
        ImVec2 screenSize = ImGui::GetIO().DisplaySize;

        for (auto& p : particles) {
            // Update position with current velocity
            p.x += p.vx * deltaTime;
            p.y += p.vy * deltaTime;

            // Mouse repulsion
            float dx = p.x - mousePos.x;
            float dy = p.y - mousePos.y;
            float distSq = dx * dx + dy * dy;

            if (distSq < globals::particles::mouseRepelRadius * globals::particles::mouseRepelRadius) {
                float dist = std::sqrt(distSq);
                if (dist < 1.0f) dist = 1.0f; // Prevent division by zero

                // Calculate repulsion force with exponential falloff
                float repelFactor = std::exp(-dist / (globals::particles::mouseRepelRadius * 0.3f));
                float force = globals::particles::mouseRepelStrength * repelFactor;

                // Add to existing velocity
                float angle = std::atan2(dy, dx);
                p.vx += std::cos(angle) * force;
                p.vy += std::sin(angle) * force;
            }

            // Limit velocity to maximum speed
            float speedSq = p.vx * p.vx + p.vy * p.vy;
            float maxSpeed = globals::particles::particleSpeed * 3.0f; // Allow higher speeds during repulsion
            if (speedSq > maxSpeed * maxSpeed) {
                float speed = std::sqrt(speedSq);
                p.vx = (p.vx / speed) * maxSpeed;
                p.vy = (p.vy / speed) * maxSpeed;
            }

            // Screen wrapping
            if (p.x < 0) {
                p.x = screenSize.x;
            }
            else if (p.x > screenSize.x) {
                p.x = 0;
            }

            if (p.y < 0) {
                p.y = screenSize.y;
            }
            else if (p.y > screenSize.y) {
                p.y = 0;
            }
        }
    }

    void Render(ImDrawList* drawList) {
        ImVec2 screenSize = ImGui::GetIO().DisplaySize;
        float time = ImGui::GetTime(); // Get current time for animation
        const float rainbowSpeed = 0.2f; // Adjust this to control animation speed

        // Draw connections
        for (size_t i = 0; i < particles.size(); i++) {
            for (size_t j = i + 1; j < particles.size(); j++) {
                float dx = particles[i].x - particles[j].x;
                float dy = particles[i].y - particles[j].y;
                float distSq = dx * dx + dy * dy;

                if (distSq < globals::particles::connectionRadius * globals::particles::connectionRadius) {
                    float alpha = 1.0f - std::sqrt(distSq) / globals::particles::connectionRadius;

                    ImVec4 lineColor;
                    if (globals::particles::rainbow) {
                        // Use the midpoint of the line for rainbow factor
                        float midX = (particles[i].x + particles[j].x) * 0.5f;
                        float midY = (particles[i].y + particles[j].y) * 0.5f;

                        // Create animated gradient based on position and time
                        float rainbowFactor = (midX / screenSize.x + midY / screenSize.y) * 0.5f;
                        rainbowFactor = fmodf(rainbowFactor + time * rainbowSpeed, 1.0f);
                        ImVec4 rainbowColor = GetRainbowColor(rainbowFactor);
                        lineColor = ImVec4(rainbowColor.x, rainbowColor.y, rainbowColor.z,
                            alpha * globals::particles::lineColor.w);
                    }
                    else {
                        lineColor = ImVec4(globals::particles::lineColor.x,
                            globals::particles::lineColor.y,
                            globals::particles::lineColor.z,
                            alpha * globals::particles::lineColor.w);
                    }

                    drawList->AddLine(
                        ImVec2(particles[i].x, particles[i].y),
                        ImVec2(particles[j].x, particles[j].y),
                        ImGui::GetColorU32(lineColor)
                    );
                }
            }
        }

        // Draw particles
        for (const auto& p : particles) {
            ImVec4 particleColor;
            if (globals::particles::rainbow) {
                // Create animated gradient based on position and time
                float rainbowFactor = (p.x / screenSize.x + p.y / screenSize.y) * 0.5f;
                rainbowFactor = fmodf(rainbowFactor + time * rainbowSpeed, 1.0f);
                ImVec4 rainbowColor = GetRainbowColor(rainbowFactor);
                particleColor = ImVec4(rainbowColor.x, rainbowColor.y, rainbowColor.z, p.color.w);
            }
            else {
                particleColor = p.color;
            }

            drawList->AddCircleFilled(
                ImVec2(p.x, p.y),
                globals::particles::circleSize,
                ImGui::GetColorU32(particleColor)
            );
        }
    }
};

// Global particle system instance
static ParticleSystem* g_particleSystem = nullptr;

void RenderParticles() {

    if (globals::Open && globals::particles::toggle) {

        // Initialize the particle system if it hasn't been created yet
        if (!g_particleSystem) {
            g_particleSystem = new ParticleSystem();
        }

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGuiIO& io = ImGui::GetIO();
        ImGui::SetNextWindowSize(io.DisplaySize);
        ImGui::Begin("Circles Window", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing);

        // Get the current window's draw list
        ImDrawList* drawList = ImGui::GetWindowDrawList();

        // Update and render the particle system
        static float lastTime = ImGui::GetTime();
        float currentTime = ImGui::GetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        g_particleSystem->Update(deltaTime);
        g_particleSystem->Render(drawList);

        ImGui::End();
    }
}

// Add this function to clean up the particle system when shutting down
void CleanupParticles() {
    if (g_particleSystem) {
        delete g_particleSystem;
        g_particleSystem = nullptr;
    }
}