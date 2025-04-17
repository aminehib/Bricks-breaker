#include <iostream>
#include "world.hpp"

using namespace std;

int main() {
    cout << "===== Test : Chargement du monde depuis world.dat =====" << endl;
    World world;
    init_world_from_file(&world, "world.dat");

    cout << "\n===== Affichage du monde (display) =====" << endl;
    display(&world);

    cout << "\n===== Test de read(world, 1, 1) =====" << endl;
    Block b = read(&world, 1, 1);
    switch (b) {
        case Empty:  cout << "Bloc = Empty" << endl; break;
        case Border: cout << "Bloc = Border" << endl; break;
        case Type1:  cout << "Bloc = Type1" << endl; break;
        case Type2:  cout << "Bloc = Type2" << endl; break;
        case Lose:   cout << "Bloc = Lose" << endl; break;
        default:     cout << "Bloc inconnu" << endl;
    }

    cout << "\n===== Test de write(world, 1, 1, Type2) =====" << endl;
    write(&world, 1, 1, Type2);
    cout << "Nouvel affichage après modification :" << endl;
    display(&world);

    cout << "\n===== Test des accès hors limites =====" << endl;
    read(&world, -1, 0);             // Lecture invalide
    write(&world, 1000, 1000, Type1); // Écriture invalide

    cout << "\n===== Libération de la mémoire (free_world) =====" << endl;
    free_world(&world);

    cout << "\n===== Test : Création manuelle d’un petit monde avec init_world =====" << endl;
    World w2;
    init_world(&w2, 4, 3);
    write(&w2, 1, 1, Type1);
    write(&w2, 2, 2, Border);
    display(&w2);
    free_world(&w2);

    return 0;
}
