#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <fstream>
#include <sstream>
#include <random>
#include <string>
#include <codecvt>
#include <io.h>

#define KANJI_MIN   19968
#define KANJI_MAX   40879

#define writestring         L"Write! 書け!: "
#define correctstring       L"Correct! 正解!"
#define incorrectstring     L"Incorrect! 違う!"
#define playagainstring     L"Again? もう一回？ (はい/いいえ): "


int main() {

    // Set stdout and stdin mode to WTEXT
    _setmode(_fileno(stdout), _O_WTEXT);
    _setmode(_fileno(stdin), _O_WTEXT);

    bool running = true;

    int scorecounter = 0;

    while (running) {

        bool again;

        again = false;

        std::random_device rd;  // a seed source for the random number engine
        std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()

        // Open file
        std::wfstream kanjifile("kanjibook.csv");
        kanjifile.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
        std::wstring kanjiline;

        std::wstring kanji;

        srand(gen());
        int randomkanjinumber = rand() % 2135;
        int lines = 0;

        for (lines = 0; getline(kanjifile, kanjiline); lines++) {
            // if lines = randomnumber store it to the write variable
            if (lines == randomkanjinumber) {
                kanji = kanjiline;
                std::wcout << "Jouyou kanji #" << lines << " " << kanji << std::endl;
                
            }
        }

        // Variable for input
        std::wstring write;

        std::wcout << writestring;

        std::wstring usertest;

        std::wcin >> write;
        if (write == kanji) {
            std::wcout << correctstring << std::endl;
            scorecounter++;
            std::wcout << "--------------------------" << std::endl;
        } else {
            std::wcout << incorrectstring << std::endl;
            std::wcout << "--------------------------" << std::endl;
            while (again != true) {
                std::wcout << "You scored: " << scorecounter << "!" << std::endl;
                std::wcout << playagainstring;
                std::wcin >> usertest;

                if (usertest == L"はい") {
                    again = true;
                } else if (usertest == L"いいえ") {
                    running = false;
                    return 0;
                } else {
                    std::wcout << L"それは理解できなかった。。。" << std::endl;
                }
            }
        }
    }

    return 0;
}