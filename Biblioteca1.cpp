#include <iostream>
#include <string>
#include <cstring>
#include <regex>
#include <algorithm>

using namespace std;


struct CARTE {
    char titlu[24];
    string autor;
    int nrEx;
};


//Add Books method
void addBook(CARTE* carti, int* nrCarti) {
    // Declare the variables to store the book title, author, and number of copies
    char titlu[24];
    string autor;
    int nrEx=0;

    // Book Title Validation
    do {
        cout << "Titlu: ";
        cin.getline(titlu, 23);

        if (titlu[0] == '\0' || strlen(titlu) >= 23) {
            cout << "Eroare inputul nu poate fi fara date sau mai mare de 23 caractere, va rog reincercati" << endl;
        }

    } while (titlu[0] == '\0' || strlen(titlu) >= 23);

    // Input book author
    do {
        cout << "Autor: ";
        getline(cin, autor);

        if (autor.empty()) {
            cout << "Eroare inputul nu poate fi fara date, va rog reincercati" << endl;
        }
    } while (autor.empty());

    nrEx = 0;
   
    do {
        cout << "Nr Exemplare: ";
        cin >> nrEx;
        cin.ignore();
        if (nrEx <= 0) {
            cout << "Eroare: Numarul de carti trebuie sa fie > 0" << endl;
        }
    } while (nrEx <= 0);

    // if book data is valid, we add it to the list here
    strncpy_s(carti[*nrCarti].titlu, titlu, sizeof(carti[*nrCarti].titlu));
    carti[*nrCarti].autor = autor;
    carti[*nrCarti].nrEx = nrEx;

    //increment book counter
    (*nrCarti)++;
}

//trailing/ending spaces removal
void deleteBook(CARTE* carti, int* nrCarti, string autor) {
    // stergem spatiile de la inceputul si sfarsitul cuvantului
    autor.erase(0, autor.find_first_not_of(' ')); // trailing spaces
    autor.erase(autor.find_last_not_of(' ') + 1); // ending spaces

    // Gasim cartea pentru autorul dat
    int index = -1;
    for (int i = 0; i < *nrCarti; i++) {
        string bookAuthor = carti[i].autor;
        // scoatem spatiile de la inceput si sfarsit pentru Author
        bookAuthor.erase(0, bookAuthor.find_first_not_of(' ')); // trailing spaces
        bookAuthor.erase(bookAuthor.find_last_not_of(' ') + 1); // spatii la sfarsitul cuvantului

        if (bookAuthor == autor) {
            index = i;
            break;
        }
    }

    // If the book was not found, return
    if (index == -1) {
        cout << "Nu s-au gasit carti de autorul " + autor << endl;
        return;
    }

    // Remove the book from the array
    for (int i = index; i < *nrCarti - 1; i++) {
        carti[i] = carti[i + 1];
    }

    // Decrement the number of books
    (*nrCarti)--;
}
//method to compare books
int compare(const void* a, const void* b)
{
    const CARTE* cartiA = (const CARTE*)a;
    const CARTE* cartiB = (const CARTE*)b;
    return strcmp(cartiA->titlu, cartiB->titlu);
};

//method to list books
void listBooks(CARTE* carti, int* nrCarti) {
    if (*nrCarti == 0) {
        cout << "Nu s-au gasit carti" << endl;
        return;
    }
    std::qsort(carti, *nrCarti, sizeof(CARTE), compare);

    for (int i = 0; i < *nrCarti; i++) {
        cout << carti[i].titlu << " de " << carti[i].autor << " (" << carti[i].nrEx << " exemplare)" << endl;
    }
}


void listBookInfo(CARTE* carti, int* nrCarti, string autor) {
    // Find the book with the specified author
    int index = -1;
    for (int i = 0; i < *nrCarti; i++) {
        if (carti[i].autor == autor) {
            index = i;
            break;
        }
    }

    // If the book was not found, return
    if (index == -1) {
        cout << "Eroare, nu s-a gasit carti pentru autorul " + autor << endl;
        return;
    }

    // Print the book information
    cout << "Titlu: " << carti[index].titlu << endl;
    cout << "Autor: " << carti[index].autor << endl;
    cout << "Nr Exemplare: " << carti[index].nrEx << endl;
}



int main() {
    // Declare the array of books
    CARTE carti[100];

    // Declare the number of books
    int nrCarti = 0;
    char titlu[24] = {'a'};
    string autor;
    int nrEx = 0;
    int choice = 0;

    while (choice <1 || choice >4 ) {
        // Display the main menu
        cout << "1. Adauga Carte" << endl;
        cout << "2. Sterge Carte" << endl;
        cout << "3. Listeaza Carti Ordonate Alfabetic Dupa Titlu" << endl;
        cout << "4. Listeaza informatii carte (dupa autor)" << endl;
        cout << "5. Iesire Program" << endl;
        // Get the user's choice
        
        cout << "Alegeti din Meniu: ";
        cin >> choice;
        cin.ignore();
        if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        // Switch on the user's choice
        switch (choice) {
        case 1:
            cout << "Adaug o carte..." << endl;
            addBook(carti, &nrCarti);
            cout << "Carte adaugata cu succes!" << endl;
            break;
        case 2:
            cout << "Tastati numele autorului pe care doriti sa-l stergeti... ";
            getline(cin, autor);
            deleteBook(carti, &nrCarti, autor);
            break;
        case 3:
            cout << "Lista de carti ..." << endl;
            listBooks(carti, &nrCarti);
            cout << "Lista de carti ..." << endl;
            break;
        case 4:
            cout << "Tastati numele autorului pentru a a-i afisa cartile... ";
            getline(cin, autor);
            listBookInfo(carti, &nrCarti, autor);
            cout << "S-au afisat cartile pentru autorul " + autor;
            break;
        case 5:
            return 0;
        default:
            cout << "Alegeti intre 1-4, 5 pentru a iesi din program, va rog mai incercati" << endl;
            break;
        }
        // Reset choice to an invalid value
        choice = 0;
    }
    return 0;
}
