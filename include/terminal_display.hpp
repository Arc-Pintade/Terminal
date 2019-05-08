#ifndef TERMINAL_DISPLAY_HPP
#define TERMINAL_DISPLAY_HPP

#include <string>
#include <vector>

class Input{

    protected :

        std::string currentLine;

        void deleteCharacters();
        void updateCurrentLine(char c);
        virtual void sendCommand(const std::string& command);

    public :

        Input();
        ~Input();

        std::string getCurrentLine();
        void receiveInput(const std::string& input);
};

class Display : public Input{

    private :

        std::string instruction;
        int width;
        int height;
        std::string userLog;
        std::string ioLog;
        std::vector<std::string> logLines;
        std::vector<std::string> ioLines;
        constexpr static const float FLASH_INTERVAL = .5f;

// virtual mother donc la fille prioritaire (override juste pour la compile 80)
        void sendCommand(const std::string& command) override;
        std::string countReturn(const std::string& s);

    public :

        Display();
        Display(int width_user, int height_user, const std::string& userLog_user);
        ~Display();

        void printResults();
        char getFlashingCursor(float time);
        void setInstruction(const std::string& command);
        std::string getInstruction();
        std::string getAllDisplayIOLines(float time);
        std::string getDisplayIOBuffer(float time);
        std::string getAllDisplayLogLines(float time);
        std::string getDisplayLogBuffer(float time);
        std::string returnLine(const std::string& word);
        std::string cutViewport(const std::string& lines);
        void clear();
        void writeLine(const std::string& line);

};



#endif
