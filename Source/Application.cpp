#include "Application.hpp"

#include <Source/Window/Implementations/SFML/SFMLWindow.hpp>
#include <Source/Buttons/Input/ButtonInput.hpp>
#include <Source/Config.hpp>

#include <chrono>
#include <iostream>

Application::Application()
    : m_window(std::make_unique<SFMLWindow>(
        cfg::WINDOW_WIDTH, cfg::WINDOW_HEIGHT, cfg::WINDOW_TITLE))
    , m_slotMachine(SlotMachine::NewRandom(cfg::NUM_SLOT_ROWS, cfg::NUM_SLOTS_IN_ROW))
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