#include <iostream>
#include <ui/ui.hpp>

int main() {
    if (!ui::init()) {
        std::cerr << ":(  Failed to init" << std::endl;
        return EXIT_FAILURE;
    }
    auto* window = new ui::Window();
    if (!window->initialized()) {
        std::cerr << ":(  Failed to init window" << std::endl;
        return EXIT_FAILURE;
    }
    window->run();
    delete window;
    ui::cleanup();
    return EXIT_SUCCESS;
}