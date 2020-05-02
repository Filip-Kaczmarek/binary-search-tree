#include <iostream>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

void klawiatura(int n, int numbers[])
{
    for (int i = 0; i < n; i++)
    {
        cin >> numbers[i];
    }
}

void generator(int n, int numbers[])
{
    srand(time(nullptr));

    for (int i = 0; i < n; i++)
    {
        numbers[i] = rand() % 100;
    }
}

void plik_(int numbers[], int n)
{
    fstream plik;
    plik.open("numbers.txt", ios::in);
    while (!plik.eof())
    {
        for (int i = 0; i <= n; i++)
        {
            plik >> numbers[i];
        }
        plik.close();
    }
}

void InsertionSort(int seq[], int n)
{
    int i, j, curr;

    for (i = 1; i < n; i++)
    {
        j = i - 1;
        curr = seq[i];

        while (j >= 0 && seq[j] < curr)
        {
            seq[j + 1] = seq[j];
            j -= 1;
        }
        seq[j + 1] = curr;
    }
    return;
}

struct wezel
{
    wezel* up, * left, * right;
    int key;
};

void BST(wezel*& korzen, int k)
{
    wezel* w, * p;

    w = new wezel;           // Tworzymy dynamicznie nowy węzeł

    w->left = w->right = NULL; // Zerujemy wskazania synów
    w->key = k;                // Wstawiamy klucz.

    p = korzen;                  // Wyszukujemy miejsce dla w, rozpoczynając od korzenia

    if (p == NULL)                   // Drzewo puste? (if(!p))
        korzen = w;                // Jeśli tak, to w staje się korzeniem
    else
        while (true)            // Pętla nieskończona
            if (k < p -> key)       // W zależności od klucza idziemy do lewego lub
            {                      // prawego syna, o ile takowy istnieje
                if (p -> left == NULL)       // Jeśli lewego syna nie ma (if(!p->left)), 
                {
                    p -> left = w;       // to węzeł w staje się lewym synem
                    break;             // Przerywamy pętlę while
                }
                else p = p -> left;
            }
            else
            {
                if (p -> right == NULL)      // Jeśli prawego syna nie ma (if (!p->right)), 
                {
                    p -> right = w;      // to węzeł w staje się prawym synem
                    break;             // Przerywamy pętlę while
                }
                else p = p->right;
            }

    w->up = p;                // Ojcem węzła w jest zawsze węzeł wskazywany przez p
}


wezel* minBST(wezel* p) // Funkcja zwraca wskazanie węzła o najmniejszym kluczu.
{
    if (p != NULL)
    {
        while (p->left != NULL)
        {
            //cout << p->key << " -> ";
            p = p->left;
        }
        cout << p->key;
    }
    return p;
}

wezel* maxBST(wezel* p) // Funkcja zwraca wskazanie węzła o największym kluczu.
{
    if (p != NULL)
    {
        while (p->right != NULL)
        {
            cout << p->key << " -> ";
            p = p->right;
        }
    }
    cout << p->key << endl;
    return p;
}

void inorder(wezel* v)
{
    if (v != NULL)
    {
        inorder(v->left);       // przechodzimy lewe poddrzewo
        cout << v->key << " "; // odwiedzamy węzeł
        inorder(v->right);      // przechodzimy prawe poddrzewo
    }
}

void preorder(wezel* v)
{
    if (v != NULL)
    {
        cout << v->key << " "; // odwiedzamy węzeł
        preorder(v->left);      // przechodzimy lewe poddrzewo
        preorder(v->right);     // przechodzimy prawe poddrzewo
    }
}

void postorder_deleting(wezel* v)
{
    if (v != NULL)
    {
        postorder_deleting(v->left);     // przechodzimy lewe poddrzewo
        postorder_deleting(v->right);    // przechodzimy prawe poddrzewo
        delete v; // usuwamy węzeł
    }
}

wezel* finder(wezel* p, int k)
{
    while (p && p->key != k)
    {
        if (k < p->key)
        {
            p = p->left;
        }
        else
        {
            p = p->right;
        }
    }
    return p;
}

void rot_L(wezel*& korzen, wezel* A) // Rotacja w lewo
{
    wezel* B = A->right, * p = A->up;

    if (B)
    {
        A->right = B->left;
        if (A->right) A->right->up = A;

        B->left = A;
        B->up = p;
        A->up = B;

        if (p)
        {
            if (p->left == A) p->left = B; else p->right = B;
        }
        else korzen = B;
    }
}


void rot_R(wezel*& korzen, wezel* A) // Rotacja w prawo
{
    wezel* B = A->left, * p = A->up;

    if (B)
    {
        A->left = B->right;
        if (A->left) A->left->up = A;

        B->right = A;
        B->up = p;
        A->up = B;

        if (p)
        {
            if (p->left == A) p->left = B; else p->right = B;
        }
        else korzen = B;
    }
}


unsigned log(unsigned x) // Funkcja oblicza 2^log2 ( x ). Liczba ta jest potrzebna do wyznaczenia ilości obrotów przy pierwszym obiegu algorytmu.
                            //To wartość binarna n + 1, w której pozostawiono najstarszy bit o wartości 1, a pozostałe bity wyzerowano.
{
    unsigned y = 1;

    while ((x = x >> 1) > 0)
    {
        y = y << 1;
    }
    return y;
}

void DSW(wezel*& korzen) // Procedura DSW równoważy drzewo BST
{
    unsigned n, i, s;
    wezel* p;

    n = 0;
    p = korzen;                     
    while (p != NULL)                      // Dopóki jesteśmy w drzewie
        if (p->left)                 // Jeśli przetwarzany węzeł ma lewego syna, 
        {
            rot_R(korzen, p);         // to obracamy wokół niego drzewo w prawo
            p = p->up;
        }
        else
        {
            n++;                        // Inaczej zwiększamy licznik węzłów
            p = p->right;               // i przesuwamy się do prawego syna
        }
                                // Teraz z listy tworzymy drzewo BST
    s = n + 1 - log(n + 1);     // Wyznaczamy początkową liczbę obrotów

    p = korzen;                       // Rozpoczynamy od początku drzewa
    for (i = 0; i < s; i++)        // Zadaną liczbę razy
    {
        rot_L(korzen, p);            // co drugi węzeł obracamy w lewo
        p = p->up->right;
    }

    n -= s;                         // Wyznaczamy kolejne liczby obrotów

    while (n > 1)                  // Powtarzamy procedurę obrotów węzłów
    {
        n >>= 1;                      // Jednakże wyznaczając za każdym razem
        p = korzen;                     // odpowiednio mniejszą liczbę obrotów, która
        for (i = 0; i < n; i++)      // maleje z potęgami 2.
        {
            rot_L(korzen, p);
            p = p->up->right;
        }
    }
}

wezel* next(wezel* p)
{
    wezel* r;

    if (p != NULL)
    {
        if (p->right)
        {
            return minBST(p->right);
        }
        else
        {
            r = p->up;
            while (r != NULL && (p == r->right))
            {
                p = r;
                r = r->up;
            }
            return r;
        }
    }
    return p;
}

void removing(wezel*& korzen, wezel* A)
{
    wezel* B, * C;

    if (A != NULL)
    {

        if (A->left == NULL|| A->right == NULL) // Jeśli A nie ma synów lub ma tylko jednego, to B wskazuje A
        {
            B = A;
        }
        else // Inaczej B wskazuje następnik A
        {
            B = next(A);
        }

        // C wskazuje syna B lub NULL

        if (B->left != NULL)
        {
            C = B->left;
        }
        else
        {
            C = B->right;
        }

        // Jeśli syn B istnieje, to zastąpi B w drzewie

        if (C != NULL)
        {
            C->up = B->up;
        }

        // B zostaje zastąpione przez C w drzewie

        if (B->up == NULL)
        {
            korzen = C;
        }
        else if (B == B->up->left)
        {
            B->up->left = C;
        }
        else
        {
            B->up->right = C;
        }
        // Jeśli B jest następnikiem A, to kopiujemy dane

        if (B != A) A->key = B->key;

        delete B;

    }
}

int main()
{
    int n = 0;
    int wejscie;
    string sort;
    wezel* korzen = NULL;
    wezel* p = NULL;
    int min, max, k, deleting, wybor=1;

    cout.setf(ios::fixed);

    cout << "Wybierz sposob utworzenia ciagu liczb: \n" << "1. Z klawiatury \n" << "2. Generator losowy \n" << "3. Z pliku \n" << "Wpisz nr 1, 2 lub 3: ";
    cin >> wejscie;
    while ((wejscie != 1) && (wejscie != 2) && (wejscie != 3))
    {
        cout << "Wpisz nr 1, 2 lub 3: ";
        cin >> wejscie;
    }

    cout << "Podaj n: ";
    cin >> n;
    while (n <= 0 || n > 5000)
    {
        cout << "Podaj n: ";
        cin >> n;
    }

    int* numbers = new int[n];

    if (wejscie == 1)
    {
        klawiatura(n, numbers);
    }

    else if (wejscie == 2)
    {
        generator(n, numbers);
    }

    else
    {
        plik_(numbers, n);
    }

    cout << "Posortowac ciag liczb? ('T'-tak, 'N'-nie): ";
    cin >> sort;
    while (sort != "T" && sort != "N")
    {
        cout << "Wpisz T lub N: ";
        cin >> sort;
    }

    if (sort == "T")
        InsertionSort(numbers, n);

    for (int i = 0; i < n; i++)
    {
        k = numbers[i];
        BST(korzen, k);
    }

    while (wybor == 1 || wybor == 2 || wybor == 3 || wybor == 4 || wybor == 5 || wybor == 6 || wybor == 7)
    {
        cout << "\nWybierz co chcesz zrobic z drzewem: \n"
            << "1. Wyszukanie w drzewie elementu o najmniejszej i najwiekszej wartosci i wypisanie sciezki poszukiwania \n"
            << "2. Wypisanie wszystkich elementow drzewa w porzadku rosnacym (in - order) \n"
            << "3. Wypisanie wszystkich elementow drzewa w porzadku pre-order \n"
            << "4. Wypisanie w porzadku pre-order poddrzewa, ktorego korzen (klucz) podaje uzytkownik \n"
            << "5. Rownowazenie drzewa przez rotacje (algorytm DSW) \n"
            << "6. Usuniecie elementu drzewa o wartosci klucza podanej przez uzytkownika (uzytkownik wpisuje ile wezłow chce usunac i podaje wartosci kluczy), \n"
            << "7. Usuniecie calego drzewa element po elemencie metoda post-order \n";
        cout << "8. Wyjscie \n";
        cout <<"Wpisz nr operacji (1-7): ";
        cin >> wybor;

        if (wybor == 1)
        {
            if (korzen != NULL)
            {
                cout << "Sciezka poszukiwania min: ";
                min = (minBST(korzen)->key); // Odczytujemy klucz minimalny
                cout << "\nSciezka poszukiwania max: ";
                max = (maxBST(korzen)->key); // Odczytujemy klucz maksymalny
            }
            cout << "Najmniejszy element: " << min << endl;
            cout << "Najwiekszy element: " << max << endl;
        }

        if (wybor == 2)
        {
            cout << "Przejscie in order: ";
            inorder(korzen);
        }

        if (wybor == 3)
        {
            cout << "Przejscie pre order: ";
            preorder(korzen);
        }

        if (wybor == 4)
        {
            cout << "Podaj klucz: \n";
            cin >> k;
            p = finder(korzen, k);
            while (p->key != k)
            {
                cout << "Podaj klucz: \n";
                cin >> k;
                p = finder(korzen, k);
            }
            preorder(p);
        }

        if (wybor == 5)
        {
            DSW(korzen);
        }

        if (wybor == 6)
        {
            cout << "Podaj ilosc elementow do usuniecia: ";
            cin >> deleting;
            while (deleting < 0 || deleting > n)
            {
                cout << "Podaj ilosc elementow do usuniecia: ";
                cin >> deleting;
            }

            for (int j = 0; j < deleting; j++)
            {
                cout << "Podaj element do usuniecia: ";
                cin >> k;
                removing(korzen, finder(korzen, k));
            }
        }

        if (wybor == 7)
        {
            cout << "Usuwanie post order: \n";
            postorder_deleting(korzen);
            cout << "Drzewo zostalo usuniete.";
            break;
        }
    }

    /*auto start = std::chrono::high_resolution_clock::now();
    if (korzen != NULL)
    {
        DSW(korzen);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    cout << endl << "Czas wykonania: " << duration_cast<std::chrono::nanoseconds> (stop - start).count() << " ns \n";*/
    postorder_deleting(korzen);
    return 0;
}