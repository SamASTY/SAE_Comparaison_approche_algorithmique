cmake_minimum_required(VERSION 3.29)
project(Samm C)

set(CMAKE_C_STANDARD 11)

add_executable(Samm
        main.c
        Alphabet.c
        Vecteur.c
        Chevalets.c
        Rail.c
        En_jeu.c
        test.c
        Dictionnaire.c
)