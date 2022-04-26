#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <memory>

#include <src/Window/IWindow.hpp>

class Application
{
public:
    Application();
    ~Application();

    void MainLoop();
    
private:
    std::unique_ptr<IWindow> m_window;
    std::unique_ptr<SlotMachine> m_slotMachine;
};

#endif
