#include "Application.hpp"

#include <src/Window/Implementations/SFML/SFMLWindow.hpp>
#include <src/Buttons/Input/ButtonInput.hpp>

Application::Application()
    : m_window(std::make_unique<SFMLWindow>(800, 600, "My window"))
    , m_slotMachine(SlotMachine::NewRandom(5, 10))
{}

Application::~Application()
{}

void Application::MainLoop()
{
    while (!m_window->IsClosed()) {
        m_window->DispatchEvents();
        
        ButtonInput::HandleWindowEvents(m_window.get());
        ButtonEvent event;
        while (ButtonInput::GetNextEvent(event)) {
            m_slotMachine->HandleButtonEvent(event);
        }

        m_slotMachine->Update();

        m_window->Render(*m_slotMachine);
    }
}