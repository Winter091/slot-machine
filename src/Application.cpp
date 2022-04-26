#include "Application.hpp"

#include <src/Window/Implementations/SFML/SFMLWindow.hpp>

Application::Application()
    : m_window(std::make_unique<SFMLWindow>(800, 600, "My window"))
{

}

Application::~Application()
{

}

void Application::MainLoop()
{
    SlotMachine machine = SlotMachine::NewRandom(5, 5);

    while (!m_window->IsClosed()) {
        m_window->DispatchEvents();
        m_window->Render(machine);
    }
}