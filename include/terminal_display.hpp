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
        std::vector<std::string> logLines;
        constexpr static const float FLASH_INTERVAL = .5f;

// virtual mother donc la fille prioritaire (override juste pour la compile 80)
        void sendCommand(const std::string& command) override;

    public :

        Display();
        Display(int width_user, int height_user, const std::string& userLog_user);
        ~Display();

        char getFlashingCursor(float time);
        void setInstruction(const std::string& command);
        std::string getInstruction();
        std::string getAllDisplayLines(float time);
        std::string getDisplayBuffer(float time);
        std::string returnLine(const std::string& word);
        std::string cutViewport(const std::string& lines);
        void clear();
        void writeLine(const std::string& line);

};



#endif
