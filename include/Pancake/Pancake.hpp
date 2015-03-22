#ifndef DTE_HPP
#define DTE_HPP

#include <string>

union SDL_Event;

namespace pcke
{
    class Pancake
    {
        public:
            Pancake();
            Pancake(int major, int minor);
            Pancake(const Pancake&) = delete;
            Pancake(Pancake&&) = delete;
            ~Pancake();

            Pancake& operator =(const Pancake&) = delete;
            Pancake& operator =(Pancake&&) = delete;

            int getMajorVersion();
            int getMinorVersion();

            bool pollEvents(SDL_Event& event);

            void setApplicationName(const std::string& name);
            void setOrganizationName(const std::string& name);

            const std::string& getApplicationName() const;
            const std::string& getOrganizationName() const;

            std::string getBasePath() const;
            std::string getDataPath() const;

        private:
            std::string application_, organization_;
    };
}

#endif // DTE_HPP
