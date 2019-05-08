#ifndef VIRTUAL_ENVIRONMENT
#define VIRTUAL_ENVIRONMENT

#include <string>

class Object{

    protected :

        std::string name;

    public :

        Object(const std::string& name_user);

        virtual void setName(const std::string& name_user);
        virtual std::string getName();
};

class Folder : public Object{

    private :

        std::string name;

    public :

        Folder(const std::string& name_user, int numberOfFile_user);

        void setName(const std::string& name_user);
        std::string getName();

};

class File : public Object{

    private :

        std::string name;

    public :

        File(const std::string& name_user);

        void setName(const std::string& name_user);
        std::string getName();

};

#endif
