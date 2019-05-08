#include "terminalDisplay.hpp"
#include <SFML/Graphics.hpp>

class Shell{

    private :

        int terminalWidth;
        int terminalHeight;
        std::string userName;

        sf::RenderWindow *terminalWindow;
        sf::Time terminalTime;
        sf::Clock terminalClock;
        sf::Font terminalFont;
        sf::Text terminalText;
        Display shell;

    public :

        Shell();
        Shell(int width_user, int height_user, const std::string& terminalName_user);
        ~Shell();

        void displayShell();
        void quickCheck(const std::string& command);
        void startShell();

};