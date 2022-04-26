#include "Application.hpp"

#include <src/Window/Implementations/SFML/SFMLWindow.hpp>

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
        m_slotMachine->Update();
        m_window->Render(*m_slotMachine.get());
    }
}