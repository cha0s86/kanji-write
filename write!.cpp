#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <random>
#include <io.h>

#define KANJI_MIN   19968
#define KANJI_MAX   40879

#define writeeng        L"Write!: "
#define seikaieng       L"Correct!"
#define incorrecteng    L"Incorrect!"
#define playagaineng    L"Do you want to play again? (Y/N): "

#define writefi         L"Kirjoita!: "
#define seikaifi        L"Oikein!"
#define incorrectfi     L"Väärin!"
#define playagainfi     L"Haluatko pelata uudestaan? (K/E): "

#define writejp         L"書け!: "
#define seikaijp        L"正解!"
#define incorrectjp     L"違う!"
#define playagainjp     L"もう一回？ (はい/いいえ): "


int main() {

    // Set stdout and stdin mode to WTEXT
    _setmode(_fileno(stdout), _O_WTEXT);
    _setmode(_fileno(stdin), _O_WTEXT);

    std::wstring writestring;
    std::wstring correctstring;
    std::wstring incorrectstring;
    std::wstring playagainstring;

    std::wcout << L"Select language (en|fi|jp?): ";
    std::wstring language;
    std::wcin >> language;

    if (language == L"en") {
        writestring     = writeeng;
        correctstring    = seikaieng;
        incorrectstring = incorrecteng;
        playagainstring = playagaineng;
    } else if (language == L"fi") {
        writestring     = writefi;
        correctstring    = seikaifi;
        incorrectstring = incorrectfi;
        playagainstring = playagainfi;
    } else if (language == L"jp") {
        writestring     = writejp;
        correctstring    = seikaijp;
        incorrectstring = incorrectjp;
        playagainstring = playagainjp;
    }

    bool running = true;

    while (running) {

        bool again;

        again = false;

        std::random_device rd;  // a seed source for the random number engine
        std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    
        srand(gen());
        
        int randomkanji = rand() % 0x51AF + 0x4E00;

        std::wcout << wchar_t(randomkanji) << std::endl;

        // Variable for input
        wchar_t  write;

        std::wcout << writestring;

        std::wstring usertest;

        std::wcin >> write;
        if (write == wchar_t(randomkanji)) {
            std::wcout << correctstring << std::endl;
        } else {
            std::wcout << incorrectstring << std::endl;
            while (again != true) {
                std::wcout << playagainstring;
                std::wcin >> usertest;
                if (language == L"en") {
                    if (usertest == L"Y" || usertest == L"y") {
                        again = true;
                    } else if (usertest == L"N" || usertest == L"n") {
                        running = false;
                        return 0;
                    } else {
                        std::wcout << L"I didn\'t understand that..." << std::endl;
                    }
                }

                else if (language == L"fi") {
                    if (usertest == L"K" || usertest == L"k") {
                        again = true;
                    } else if (usertest == L"E" || usertest == L"e") {
                        running = false;
                        return 0;
                    } else {
                        std::wcout << L"En ymmärtänyt tuota..." << std::endl;
                    }
                }

                if (language == L"jp") {
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
    }

    return 0;
}