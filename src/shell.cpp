#include "../include/shell.hpp"

#include <iostream>

using namespace std;
using namespace sf;

Shell::Shell(){}

Shell::Shell(int width_user, int height_user, const string& userName_user){
    int n=3;
    terminalWindow = new RenderWindow(VideoMode(600, 400), "SFML!");
    shell = Display(width_user, height_user, userName_user);
    terminalClock.restart();

    terminalFont = vector<Text>(n);
    terminalText[0].setFillColor(Color::Green);
    terminalText[1].setFillColor(Color::Blue);
    terminalText[2].setFillColor(Color::Red);
    if (!terminalFont.loadFromFile("fonts/UbuntuMono-R.ttf")){
        cout<<"No fonts !"<<endl;
    }
    for(int i=0; i<n; ++i){
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
        Event event;
        while (terminalWindow->pollEvent(event)){
            if (event.type == Event::Closed)
                terminalWindow->close();
            if (event.type == Event::TextEntered){
                shell.receiveInput(String(event.text.unicode));
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
