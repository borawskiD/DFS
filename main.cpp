#include <iostream>
#include <vector>
#include <math.h>
/* tworzymy strukture wezla, kazdy wezel sklada sie z zawartosci (dane), oraz wskaznikow
   do dwoch kolejnych wezlow (lewy i prawy) */
struct Wezel{
    Wezel *lewy;
    Wezel *prawy;
    char dane;
};
/* Tworzenie struktury drzewa - liscie
   wypelniamy NULLami liscie, poniewaz nie maja potomkow */
Wezel G = {NULL, NULL, 'G'};
Wezel H = {NULL, NULL, 'H'};
Wezel I = {NULL, NULL, 'I'};
Wezel J = {NULL, NULL, 'J'};
Wezel K = {NULL, NULL, 'K'};
//a rodzicow juz mozemy podporzadkowac do dzieci, zgodnie ze struktura drzewa
Wezel D = {&H, &I, 'D'};
Wezel E = {&J, NULL, 'E'};
Wezel F = {&K, NULL, 'F'};
Wezel B = {&D, &E, 'B'};
Wezel C = {&F,&G, 'C' };
//korzen
Wezel A = {&B, &C, 'A'};
/* funkcja wyswietlajaca drzewo w czytelny dla czlowieka sposob
 * przyjmuje vector, czyli wygodna implementacje listy w cpp
 * jej działanie opiera sie na dostosowaniu ilosci spacji i zlamanych linii
 * do poziomu w ktorym aktualnie sie znajdujemy, im nizszy tym oczywiscie spacji przed
 * zawartoscia liscia bedzie coraz mniej, zgodnie z outputem:
     A

    B   C

  D  E  F  G

 H I J K
 */
void wyswietl_drzewo(std::vector<Wezel> *wezly){
    int j = 0;
    for (int i = 0; i<wezly -> size(); i++){
        if (i+1 == pow(2,j)){
            j++;
        }
    }
    int jj = j;
    j = 0;
    for (int i = 0; i<wezly -> size(); i++){
        if (i + 1 == pow (2,j)){
            std::cout<< std::endl <<std::endl;
            j++;
            jj--;
        }
        for (int k = 0; k <= jj+(wezly ->size()-i)/10; k++){
            std::cout <<" ";
        }
        std::cout << (*wezly)[i].dane;
    }
}
/* funkcja preorder zgodnie z nazwa odpowiada za przeszukanie drzewa metoda pre-order
 * idziemy od korzenia, po kolei odczytujac wartosci - to istotne, poniewaz w nastepnych
 * funkcjach juz w ten sposob nie bedziemy dzialac.
 * Idziemy az do krancowego lewego dziecka, aby nastepnie przejsc do prawego dziecka, i tak systematycznie
 * przesuwamy sie az do krancowego prawego dziecka, co konczy nasze przeszukiwanie.
 * Ta metoda wydaje sie najbardziej intuicyjna, w zasadzie idziemy po wlasnych sladach. */

void preorder(Wezel *v){
    //sprawdzamy czy v nie wskazuje na null
    if(v){
        //wyswietlam dane z aktualnego wezla v
        std::cout << v -> dane << " ";
        //rekurencyjnie przechodze najpierw do lewego potomka, a pozniej do prawego.
        preorder(v->lewy);
        preorder(v->prawy);
    }
}
/* Inorder natomiast jest diametralnie inny, poniewaz jako pierwsze przetworzone bedzie dopiero lewe skrajne dziecko.
 * Pozniej troche "rakiem" wycofujemy sie, najpierw do rodzica, a pozniej przeszukujemy prawego potomka. Widac to rowniez
 * w kodzie, poniewaz dopiero po przejsciu rekurencji przez lewych potomkow wyswietlamy zawartosc. */
void inorder(Wezel *v){
    if (v) {
        inorder(v -> lewy);
        std::cout << v -> dane << " ";
        inorder(v -> prawy);
    }
}
/* post-order iteruje po potomkach, dopoki istnieja to nie wyswietla zawartosci, tak jak w kodzie jest widoczne:
 * cout wykonywany jest dopiero po skonczeniu rekursji po lewym potomku i (!) po prawym. */
void postorder(Wezel *v){
    if (v){
        postorder(v -> lewy);
        postorder(v -> prawy);
        std::cout << v -> dane << " ";
    }
}
int main() {
    //tworze nowa strukture vectora
    std::vector<Wezel> *wezly = new std::vector<Wezel>();
    //a tutaj po prostu wypelniam strukture elementami drzewa
    wezly ->push_back(A);
    wezly ->push_back(B);
    wezly ->push_back(C);
    wezly ->push_back(D);
    wezly ->push_back(E);
    wezly ->push_back(F);
    wezly ->push_back(G);
    wezly ->push_back(H);
    wezly ->push_back(I);
    wezly ->push_back(J);
    wezly ->push_back(K);
    //wyswietlanie drzewa
    wyswietl_drzewo(wezly);
    //i wywolanie konkretnych funkcji z opisem
    std::cout<<std::endl<<"Pre-order: " << std::endl;
    preorder(&A);

    std::cout<<std::endl<<"In-order: " << std::endl;
    inorder(&A);

    std::cout<<std::endl<<"Post-order: " << std::endl;
    postorder(&A);

    return 0;
}

/* DOMINIK BORAWSKI
A1 215IC */
/*
     A

    B   C

  D  E  F  G

 H I J K
Pre-order:
A B D H I E J C F K G
In-order:
H D I B J E A K F C G
Post-order:
H I D J E B K F G C A
*/