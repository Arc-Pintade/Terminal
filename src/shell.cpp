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
        cout<<"No fonts !"<<endl;
    }
    terminalText.setFont(terminalFont);
    terminalText.setCharacterSize(14);
    terminalText.setPosition(20,10);
}

Shell::~Shell(){
    delete terminalWindow;
    cout<<"Shell Destruction"<<endl;
}

void Shell::startShell(){
    shell.writeLine("#########################");
    shell.writeLine("##    Hello World !    ##");
    shell.writeLine("#########################");
    shell.writeLine("");
}

void Shell::exitShell(){
    if(shell.getInstruction() == "exit" or shell.getInstruction() == "exit ")
        terminalWindow->close();
}

void Shell::printResults(){
    string out1 = "\n >> ";
    string out2 = "\n";
    if(shell.getInstruction() == "universal truth")
        shell.writeLine(out1+"greg = pute"+out2);
    else if(shell.getInstruction() == "pwd")
        shell.writeLine(out1+"fail"+out2);
    else if(shell.getInstruction() != "")
        shell.writeLine(out1+"unknown command %% Error_XX02Y9"+out2);
    shell.setInstruction("");
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
                exitShell();
                printResults();
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
