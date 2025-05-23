#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <fstream>
#include <sstream>
#include <random>
#include <string>
#include <codecvt>
#include <io.h>

#define writestring         L"Write! 書け!: "
#define correctstring       L"Correct! 正解!"
#define incorrectstring     L"Incorrect! 違う!"
#define playagainstring     L"Again? もう一回？ (はい/いいえ): "


int main() {

    // Set stdout and stdin mode to WTEXT
    _setmode(_fileno(stdout), _O_WTEXT);
    _setmode(_fileno(stdin), _O_WTEXT);

    bool running = true;

    int score = 0;

    while (running) {

        bool again;

        again = false;

        std::random_device rd;  // a seed source for the random number engine
        std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()

        // Open file
        std::wfstream kanjifile("databases/kanjibook.csv");
        kanjifile.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
        std::wstring kanjiline;

        std::wstring kanji;

        srand(gen());
        int randomkanjinumber = rand() % 2135;
        int linecounter = 0;

        for (linecounter = 0; getline(kanjifile, kanjiline); linecounter++) {
            // if linecounter = randomnumber store it to the write variable
            if (linecounter == randomkanjinumber) {
                kanji = kanjiline;
                std::wcout << "Jouyou kanji #" << linecounter << " " << kanji << std::endl;
                
            }
        }

        // Variable for input
        std::wstring write;

        std::wcout << writestring;

        std::wstring userinput;

        std::wcin >> write;
        if (write == kanji) {
            std::wcout << correctstring << std::endl;
            score++;
            std::wcout << "--------------------------" << std::endl;
        } else {
            std::wcout << incorrectstring << std::endl;
            std::wcout << "--------------------------" << std::endl;
            while (again != true) {
                std::wcout << "You scored: " << score << "!" << std::endl;
                std::wcout << playagainstring;
                std::wcin >> userinput;

                if (userinput == L"はい") {
                    score = 0;
                    again = true;
                } else if (userinput == L"いいえ") {
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