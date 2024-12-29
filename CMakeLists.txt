cmake_minimum_required(VERSION 3.29)
project(Samm C)

set(CMAKE_C_STANDARD 11)

add_executable(Samm main.c
        main.c
        Alphabet.c
        Vecteur.c
        Chevalets.c
        Rail.c
        En_jeu.c
        test_alphabet_chevalet.c
        Dictionaire.c
)
