#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <random>
#include <vector>
#include <algorithm>

//defining struct
struct CARTE {
    char titlu[24];
    std::string autor;
    int nrEx;
    // Define the '<' operator for CARTE
    bool operator<(const CARTE& other) const {
        return strcmp(titlu, other.titlu) < 0;
    }
};


//creating single linked list
std::list<CARTE> books;

//================================START Populate list with 20 books==========================================================
void GenereazaCarti() {
    char titluri[200][23] = {
        "The Great Gatsby", "To Kill a Mockingbird", "1984", "The Catcher in the Rye", "Animal Farm",
        "Pride and Prejudice", "Brave New World", "The Hobbit", "Fahrenheit 451", "Moby-Dick",
        "War and Peace", "Madame Bovary", "The Odyssey", "Ulysses", "Don Quixote",
        "Wuthering Heights", "The Iliad", "Beowulf", "Invisible Man", "Beloved",
        "Ion", "Rascoala", "Padurea Spanzuratilor","Amintiri din Copilarie",
        "Harap-Alb", "Scrisoarea a III-a"
    };

    std::string autori[] = {
        "F. Scott Fitzgerald", "Harper Lee", "George Orwell", "J.D. Salinger",
        "Jane Austen","Aldous Huxley", "J.R.R. Tolkien",
        "Ray Bradbury","Herman Melville","Leo Tolstoy",
        "Gustave Flaubert","Homer","James Joyce",
        "Miguel de Cervantes","Emily Bronte",
        "Homer","Anonymous","Ralph Ellison",
        "Toni Morrison","Ioan Slavici",
        "Liviu Rebreanu","Marin Preda","Mihai Eminescu",
        "Ion Creanga"
    };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disEx(1, 100);

    // Get the minimum size between titluri and autori
    int size = std::min(sizeof(titluri) / sizeof(titluri[0]), sizeof(autori) / sizeof(autori[0]));

    for (int i = 0; i < size; ++i) {
        CARTE carte;
        strncpy_s(carte.titlu, sizeof(carte.titlu), titluri[i], _TRUNCATE);
        carte.autor = autori[i];
        carte.nrEx = disEx(gen);

        books.push_front(carte);

        std::cout << "Am Adaugat Carte: "
            << carte.titlu << ", "
            << carte.autor << ", "
            << carte.nrEx << std::endl;
    }

    std::cout << "\nNr Total de carti adaugate: "
        << std::distance(books.begin(), books.end()) << std::endl;
}

//================================END Populate list with books============================================================

//================================START Add New book START==========================================================
void AdaugaCarteNoua() {
    CARTE carte;
    std::string input;
    bool valid;

    // Ask for the title
    do {
        std::cout << "Introduceti titlul (max 23 caractere, nu poate fi gol, nu poate exista deja in lista): ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, input);
        valid = input.length() <= 23 && !input.empty();

        // Check if the title is already in the list
        for (const auto& book : books) {
            if (strcmp(book.titlu, input.c_str()) == 0) {
                valid = false;
                std::cout << "Cartea exista deja, va rog introduceti alta carte." << std::endl;
                break;
            }
        }

        if (!valid) {
            std::cout << "Titlu incorect. va rog reincercati (max 23 caractere, nu poate fi gol, nu poate exista deja in lista)." << std::endl;
        }
    } while (!valid);

    strncpy_s(carte.titlu, sizeof(carte.titlu), input.c_str(), _TRUNCATE);

    // Ask for the author
    do {
        std::cout << "Introduceti numele autorului (nu poate fi gol): ";
        std::getline(std::cin, carte.autor);
        valid = !carte.autor.empty();

        if (!valid) {
            std::cout << "Date incorecte. Reincercati." <<std::endl;
        }
    } while (!valid);

    // Ask for the number of copies
    do {
        std::cout << "Introduceti nr de exemplare (nr intreg pozitiv): ";
        std::getline(std::cin, input);
        carte.nrEx = std::stoi(input);
        valid = carte.nrEx > 0;

        if (!valid) {
            std::cout << "Date incorecte. Mai incercati." << std::endl;
        }
    } while (!valid);

    // Add the book to the list
    books.push_front(carte);

    // Print the added book
    std::cout << "Adaugat Carte: "
        << carte.titlu << ", "
        << carte.autor << ", "
        << carte.nrEx << std::endl;
}
//================================END Add new book method============================================================


//================================START Delete books filtered by author method START==========================================================
void StergeCartiDupaAutor() {
    std::string autor;
    bool valid;

    // Input autor
    do {
        std::cout << "Introduceti numele autorului (nu poate fi gol): ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Adaugă această linie
        std::getline(std::cin, autor);
        valid = !autor.empty();

        if (!valid) {
            std::cout << "Autor invalid. Va rugam sa incercati din nou." << std::endl;
        }
    } while (!valid);

    // // Go through the list and remove books by the author
    for (auto it = books.begin(); it != books.end(); /* no increment here */) {
        if (it->autor == autor) {
            std::cout << "Carte stearsa: "
                << it->titlu << ", "
                << it->autor << ", "
                << it->nrEx << std::endl;

            it = books.erase(it); // erase returnează iteratorul care urmează elementului eliminat
        }
        else {
            ++it; //erase returns the iterator following the removed element
        }
    }
}
//================================END Delete books filtered by author method END============================================================

//================================START List all books in alphabetical order START==========================================================
void ListeazaToateCartile() {
    // Sort the list
    books.sort();

    // Print the sorted list
    for (const auto& carte : books) {
        std::cout << "Carte: " << carte.titlu << " - Autor: " << carte.autor << " - Nr Exemplare:  " << carte.nrEx << std::endl;
    }
}
//================================END List all books in alphabetical order END============================================================


//================================START List all books filtered by author START==========================================================
void ListeazaCartileUnuiAutor() {
    std::string autor;
    bool valid;

    // Ask for the author
    do {
        std::cout << "Va rog introduceti autorul pentru care vreti sa gasesc toate cartile: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Add this line
        std::getline(std::cin, autor);
        valid = !autor.empty();

        if (!valid) {
            std::cout << "Autor invalid. Va rog sa incercati din nou." << std::endl;
        }
    } while (!valid);

    // Go through the list and print books by the author
    bool found = false;
    for (const auto& book : books) {
        if (book.autor == autor) {
            found = true;
            std::cout << "Carte: " << book.titlu << " - Nr Exemplare: " << book.nrEx << std::endl;
        }
    }

    if (!found) {
        std::cout << "Nu avem carti scrise de autorul " << autor << " in biblioteca." << std::endl;
    }
}
//================================END List all books filtered by author END==========================================================

int main() {
    GenereazaCarti();
    int choice;
    do {
        std::cout << "1) Genereaza Carti" << std::endl;
        std::cout << "2) Adauga carte noua" << std::endl;
        std::cout << "3) Sterge carti dupa autor" << std::endl;
        std::cout << "4) Listeaza toate cartile ordonate alfabetic dupa titlu" << std::endl;
        std::cout << "5) Listeaza cartile unui anumit autor" << std::endl;
        std::cout << "6) Iesire program" << std::endl;
        std::cout << "Alegeti o optiune: ";
        std::cin >> choice;
        switch (choice) {
        case 1:
            GenereazaCarti();
            //std::cin.ignore();
            break;
        case 2:
            AdaugaCarteNoua();
            break;
        case 3:
            StergeCartiDupaAutor();
            //std::cin.ignore();
            break;
        case 4:
            ListeazaToateCartile();
            //std::cin.ignore();
            break;
        case 5:
            ListeazaCartileUnuiAutor();
            //std::cin.ignore();
            break;
        default:
            std::cout << "Input invalid, va rog alegeti intre 1-6" << std::endl;
            std::cin.ignore();
            break;
        }
    } while (choice != 6);

    return 0;
}
