#include "../data/controls.hpp"
#include "../data/graphics.hpp"
#include <array>
#include <cstdlib>
#include <string>
#include <vector>
#include <filesystem> // for handling file paths and directories for the games
#include <iostream>

// make a test main menu

std::vector<std::string> directories(std::string path){
    std::vector<std::string> result;
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_directory()) {
            result.push_back(entry.path().string());
        }
    }
    return result;
}

void launch(const std::string& path){
    // look for a launch.exe 
    std::filesystem::path launchPath = std::filesystem::path(path) / "launch.exe";
    if (std::filesystem::exists(launchPath)) {
        std::system(launchPath.string().c_str());
    }else{
        std::cerr << "launch.exe not found in " << path << ", please make sure it exists." << std::endl;
    }
}

int main() {
    gph::window gameWindow;
    gameWindow.create(800, 600, "RPG");

    sf::RenderWindow& renderWindow = gameWindow.getRenderWindow();
    sf::Font font;
    constexpr std::array fontPaths{
        "C:/Windows/Fonts/arial.ttf",
        "C:/Windows/Fonts/segoeui.ttf"
    };

    bool fontLoaded = false;
    for (const char* path : fontPaths) {
        if (font.openFromFile(path)) {
            fontLoaded = true;
            break;
        }
    }
    if (!fontLoaded) {
        std::cerr << "Could not load a menu font from the Windows Fonts folder.\n";
        return 1;
    }

    std::vector<std::string> gamePaths;
    for (const std::string& path : directories(".")) {
        if (std::filesystem::exists(std::filesystem::path(path) / "launch.exe")) {
            gamePaths.push_back(path);
        }
    }

    std::vector<std::string> menuItems;
    for (const std::string& path : gamePaths) {
        menuItems.push_back(std::filesystem::path(path).filename().string());
    }
    if (gamePaths.empty()) {
        menuItems.push_back("No games found (add a folder with launch.exe)");
    }
    menuItems.push_back("Quit");

    std::size_t selected = 0;
    sf::Text title(font, "Main Menu", 42);
    title.setPosition({40.f, 30.f});

    std::vector<sf::Text> labels;
    labels.reserve(menuItems.size());
    for (std::size_t i = 0; i < menuItems.size(); ++i) {
        labels.emplace_back(font, menuItems[i], 24);
        labels.back().setPosition({72.f, 140.f + static_cast<float>(i) * 64.f});
    }

    while (renderWindow.isOpen()) {
        while (const auto event = renderWindow.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                renderWindow.close();
            }

            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->code == sf::Keyboard::Key::Escape) {
                    renderWindow.close();
                } else if (key->code == sf::Keyboard::Key::Down) {
                    selected = (selected + 1) % menuItems.size();
                } else if (key->code == sf::Keyboard::Key::Up) {
                    selected = (selected + menuItems.size() - 1) % menuItems.size();
                } else if (key->code == sf::Keyboard::Key::Enter) {
                    if (selected < gamePaths.size()) {
                        launch(gamePaths[selected]);
                    } else if (menuItems[selected] == "Quit") {
                        renderWindow.close();
                    }
                }
            }

            if (const auto* click = event->getIf<sf::Event::MouseButtonPressed>()) {
                const float mouseX = static_cast<float>(click->position.x);
                const float mouseY = static_cast<float>(click->position.y);
                for (std::size_t i = 0; i < labels.size(); ++i) {
                    const sf::FloatRect bounds = labels[i].getGlobalBounds();
                    if (bounds.contains({mouseX, mouseY})) {
                        selected = i;
                        if (selected < gamePaths.size()) {
                            launch(gamePaths[selected]);
                        } else if (menuItems[selected] == "Quit") {
                            renderWindow.close();
                        }
                        break;
                    }
                }
            }
        }

        renderWindow.clear(sf::Color(24, 27, 36));
        renderWindow.draw(title);
        for (std::size_t i = 0; i < labels.size(); ++i) {
            labels[i].setFillColor(i == selected ? sf::Color(255, 220, 120) : sf::Color::White);
            renderWindow.draw(labels[i]);
        }
        renderWindow.display();
    }

    return 0;
}
