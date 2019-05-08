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

void Display::sendCommand(const string& command){
    setInstruction(command);
    logLines.push_back(userLog+countReturn(command));
    ioLines.push_back(ioLog+command);
    currentLine = "";
}

Display::Display(){}

Display::Display(int width_user, int height_user, const string& userLog_user){
    instruction = "";
    width = width_user;
    height = height_user;
    userLog = userLog_user;
    ioLog = string(userLog.size(), ' ');
    logLines = vector<string>(0);
    ioLines = vector<string>(0);
}

Display::~Display(){
    cout<<"Display Destruction"<<endl;
}

void Display::setInstruction(const string& command){
    instruction = command;
}

string Display::getInstruction(){
    return instruction;
}


string Display::getAllDisplayIOLines(float time){
    string output = "";
    for(string line : ioLines)
        output += line + '\n';
    output += ioLog + getCurrentLine();
    output += getFlashingCursor(time);
    return output;
}

string Display::getAllDisplayLogLines(float time){
    string output = "";
    for(string line : logLines)
        output += line + '\n';
    output += userLog + countReturn(getCurrentLine());
    //output += getFlashingCursor(time);
    return output;
}

string Display::getDisplayIOBuffer(float time){
    string lines = getAllDisplayIOLines(time);
    string wrappedLines = returnLine(lines);
    string viewportLines = cutViewport(wrappedLines);
    return viewportLines;
}

string Display::getDisplayLogBuffer(float time){
    string lines = getAllDisplayLogLines(time);
    string wrappedLines = returnLine(lines);
    string viewportLines = cutViewport(wrappedLines);
    return viewportLines;
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
    logLines.clear();
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
    logLines.push_back(countReturn(line));
    ioLines.push_back(line);
}
