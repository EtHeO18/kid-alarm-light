#include <vector>
#include "ProgramEntry.hpp"

class Program {
    private:

        std::vector<ProgramEntry*> program = {};

    public:
        ProgramEntry* currentEntry(uint8_t weekday, uint8_t hour, uint8_t minute, uint8_t second);
        void addEntry(ProgramEntry* entry);
        void addNewEntry(uint8_t weekday, uint8_t hour, uint8_t minute, uint8_t second, uint8_t R, uint8_t G, uint8_t B);
        void load();
        void save();
        Program();
        
};