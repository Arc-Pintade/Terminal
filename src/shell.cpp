#include "../include/shell.hpp"

#include <iostream>

using namespace std;

Shell::Shell(){}

Shell::Shell(int width_user, int height_user, const string& userName_user){
    terminalWindow = new sf::RenderWindow(sf::VideoMode(600, 400), "SFML!");
    shell = Display(width_user, height_user, userName_user);
    terminalClock.restart();
    terminalText.setFillColor(sf::Color::Green);
    if (!terminalFont.loadFromFile("fonts/UbuntuMono-R.ttf")){
        // error...
    }
    terminalText.setFont(terminalFont);
    terminalText.setCharacterSize(14);
    terminalText.setPosition(20,10);
}

Shell::~Shell(){
    delete terminalWindow;
    cout<<"Shell Destruction"<<endl;
}

void Shell::quickCheck(const string& command){
    if(command == "exit")
        terminalWindow->close();
}

void Shell::startShell(){
    shell.writeLine("#########################");
    shell.writeLine("##    Hello World !    ##");
    shell.writeLine("#########################");
    shell.writeLine("");
}

void Shell::displayShell(){
    startShell();
    while (terminalWindow->isOpen()){
        sf::Event event;
        while (terminalWindow->pollEvent(event)){
            if (event.type == sf::Event::Closed)
                terminalWindow->close();
            if (event.type == sf::Event::TextEntered){
                shell.receiveInput(sf::String(event.text.unicode));
                quickCheck(shell.getInstruction());
                terminalClock.restart();
            }
        }
        terminalTime = terminalClock.getElapsedTime();
        terminalText.setString(shell.getDisplayBuffer(terminalTime.asSeconds()));
        terminalWindow->clear();

        terminalWindow->draw(terminalText);
        terminalWindow->display();
    }
}
