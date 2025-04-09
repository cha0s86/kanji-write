#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <random>
#include <io.h>

#define KANJI_MIN   19968
#define KANJI_MAX   40879

int main() {

    // Set stdout and stdin mode to WTEXT
    _setmode(_fileno(stdout), _O_WTEXT);
    _setmode(_fileno(stdin), _O_WTEXT);

    bool running = true;

    while (running) {

        bool again;

        again = false;

        std::random_device rd;  // a seed source for the random number engine
        std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    
        srand(gen());
        
        int randomkanji = rand() % 20911 + 19968;

        std::wcout << wchar_t(randomkanji) << std::endl;

        // Variable for input
        wchar_t write;

        std::wcout << L"Write!　書け！: ";

        wchar_t usertest;

        std::wcin >> write;
        if (write == randomkanji) {
            std::wcout << L"Correct!　正解！" << std::endl;
        } else {
            std::wcout << L"Incorrect!　違う！" << std::endl;
            while (again != true) {
                std::wcout << L"Do you want to play again? (Y/N): ";
                std::wcin >> usertest;
                if (usertest == L'Y' || usertest == L'\xff39' || usertest == L'y' || usertest == L'\xff59') {
                    again = true;
                } else if (usertest == L'N' || usertest == L'\xff2e' || usertest == L'n' || usertest == L'\xff4e') {
                    running = false;
                    return 0;
                } else {
                    std::wcout << L"I didn't understand that..." << std::endl;
                }
            }
        }
    }

    return 0;
}