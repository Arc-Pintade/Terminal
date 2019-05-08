#include "../include/shell.hpp"

#include <iostream>
#include <cmath>

using namespace std;

Shell::Shell(){}

Shell::Shell(int width_user, int height_user, const string& userName_user){
    terminalWindow = new sf::RenderWindow(sf::VideoMode(600, 400), "SFML!");
    shell = Display(width_user, height_user, userName_user);
    terminalClock.restart();
    terminalText[1].setFillColor(sf::Color(0,255,150));
    terminalText[0].setFillColor(sf::Color(0,255,0));
    if (!terminalFont.loadFromFile("fonts/UbuntuMono-R.ttf")){
        cout<<"No fonts !"<<endl;
    }
    for(int i=0; i<numberColor; ++i){
        terminalText[i].setFont(terminalFont);
        terminalText[i].setCharacterSize(14);
        terminalText[i].setPosition(20,10);
    }

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
    string prefix = " ";
    if(shell.getInstruction() == "greg")
        shell.writeLine(prefix+"greg = pute");
    else if(shell.getInstruction() == "pwd")
        shell.writeLine(prefix+"fail");
    else if(shell.getInstruction() == "chmod +x run"){
        shell.writeLine("#################");
        shell.writeLine("#### You win ####");
        shell.writeLine("#################");
    }
    else if(shell.getInstruction() != "")
        shell.writeLine(prefix+shell.getInstruction()+" : unknown command");
    shell.setInstruction("");
}

void Shell::displayShell(){
    array<string, numberColor> textDisplay;
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
        terminalWindow->clear();
        for(int i=0; i<numberColor; ++i){
            textDisplay = shell.getDisplayIOBuffer(terminalTime.asSeconds());
            terminalText[i].setString(textDisplay[i]);
            terminalWindow->draw(terminalText[i]);
        }

        terminalWindow->display();
    }
}
