#include "../include/terminal_display.hpp"

#include <iostream>
#include <cmath>

using namespace std;

//________________________________ Input _____________________________________//

Input::Input(){
    currentLine = "";
}

Input::~Input(){
    cout<<"Input Destruction"<<endl;
}

void Input::deleteCharacters(){
    if(currentLine.length() > 0)
        currentLine.pop_back();
}

void Input::updateCurrentLine(char c){
    if(c == '\b')
        deleteCharacters();
    else if(c == '\n' or c == '\r')
        sendCommand(currentLine);
    else
        currentLine += c;
}

void Input::sendCommand(const string& command){
    cout<<command<<endl;
    currentLine = "";
}

string Input::getCurrentLine(){
    return currentLine;
}

void Input::receiveInput(const string& input){
    for(char c : input)
        updateCurrentLine(c);
}

//________________________________ Display ___________________________________//

Display::Display(){}

Display::Display(int width_user, int height_user, const string& userLog_user){
    instruction = "";
    width = width_user;
    height = height_user;
    ioInput[0] = userLog_user;
    ioInput[1] = string(ioInput[0].size(), ' ');
    for(int i=0; i<numberColor; ++i)
        ioLines[i] = vector<string>(0);
}

Display::~Display(){
    cout<<"Display Destruction"<<endl;
}

void Display::sendCommand(const string& command){
    setInstruction(command);
    ioLines[0].push_back(ioInput[0]+countReturn(command));
    ioLines[1].push_back(ioInput[1]+command);
    currentLine = "";
}

void Display::setInstruction(const string& command){
    instruction = command;
}

string Display::getInstruction(){
    return instruction;
}

array<string, numberColor> Display::getAllDisplayIOLines(float time){
    array<string, numberColor> foo;
    for(int i=0; i<numberColor; ++i){
        foo[i] = "";
        for(string line : ioLines[i])
            foo[i] += line + '\n';
    }
    foo[0] += ioInput[0] + countReturn(getCurrentLine());
    foo[1] += ioInput[1] + getCurrentLine();
    foo[1] += getFlashingCursor(time);
    return foo;
}

array<string, numberColor> Display::getDisplayIOBuffer(float time){
    array<string, numberColor> foo;
    foo = getAllDisplayIOLines(time);
    for(int i=0; i<numberColor; ++i){
        foo[i] = returnLine(foo[i]);
        foo[i] = cutViewport(foo[i]);
    }
    return foo;
}

string Display::returnLine(const string& word){
    string output = "";
    int column = 1;
    for(char c : word){
        if(column == width){
            output += '\n';
            output += c;
            column = 1;
        }
        else if(c == '\n'){
            output += '\n';
            column = 1;
        }
        else{
            output += c;
            ++column;
        }
    }
    return output;
}

string Display::cutViewport(const string& lines){
    string output = "";
    int rowCount = 1;
    for(int i = lines.length()-1; i>=0; i--){
        if(rowCount > height)
            return output;
        if(lines[i] == '\n')
            rowCount++;
        output = lines[i] + output;
    }
    return output;
}

char Display::getFlashingCursor(float time){
    if(time - floor(time) <= FLASH_INTERVAL)
        return '_';
    else
        return ' ';
}

void Display::clear(){
    for(int i=0; i<numberColor; ++i)
        ioLines[i].clear();
}

string Display::countReturn(const string& s)
{
    string empty = "";
    for (char c : s)
        if (c == '\n')
            empty += '\n';
    return empty;
}

void Display::writeLine(const string& line){
    ioLines[0].push_back(countReturn(line));
    ioLines[1].push_back(line);
}
