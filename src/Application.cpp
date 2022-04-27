#include "Application.hpp"

#include <src/Window/Implementations/SFML/SFMLWindow.hpp>
#include <src/Buttons/Input/ButtonInput.hpp>

#include <chrono>
#include <iostream>

Application::Application()
    : m_window(std::make_unique<SFMLWindow>(800, 600, "My window"))
    , m_slotMachine(SlotMachine::NewRandom(5, 25))
{}

Application::~Application()
{}

void Application::MainLoop()
{
    auto prevTime = std::chrono::high_resolution_clock::now();
    
    while (!m_window->IsClosed()) {
        auto currTime = std::chrono::high_resolution_clock::now();
        float dt = (currTime - prevTime).count() / 1'000'000.0f;
        prevTime = currTime;

        m_window->DispatchEvents();
        
        ButtonInput::HandleWindowEvents(m_window.get());
        ButtonEvent event;
        while (ButtonInput::GetNextEvent(event)) {
            m_slotMachine->HandleButtonEvent(event);
        }

        m_slotMachine->Update(dt);

        m_window->Render(*m_slotMachine);
    }
}