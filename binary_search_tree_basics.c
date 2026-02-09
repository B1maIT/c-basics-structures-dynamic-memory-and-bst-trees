#include <stdio.h>
#include <stdlib.h>

struct wezel {
    int wartosc;
    struct wezel *rodzic;
    struct wezel *l_syn;
    struct wezel *p_syn;
};

struct wezel *root;

struct wezel* naj_lewo(struct wezel *start) {
    if (start->l_syn != NULL)
        return naj_lewo(start->l_syn);
    else
        return start;
}

struct wezel* szukaj(struct wezel *start, int wartosc) {
    if (start->wartosc == wartosc)
        return start;
    else if (wartosc < start->wartosc && start->l_syn != NULL)
        return szukaj(start->l_syn, wartosc);
    else if (wartosc > start->wartosc && start->p_syn != NULL)
        return szukaj(start->p_syn, wartosc);
    return NULL;
}

int dodawanie(int n, struct wezel *start) {
    if (root == NULL) {
        root = (struct wezel*)malloc(sizeof(struct wezel));
        root->wartosc = n;
        root->l_syn = NULL;
        root->p_syn = NULL;
        root->rodzic = NULL;
    } else if (n < start->wartosc) {
        if (start->l_syn != NULL) {
            dodawanie(n, start->l_syn);
        } else {
            struct wezel *nowy = (struct wezel*)malloc(sizeof(struct wezel));
            nowy->wartosc = n;
            nowy->l_syn = NULL;
            nowy->p_syn = NULL;
            nowy->rodzic = start;
            start->l_syn = nowy;
        }
    } else {
        if (start->p_syn != NULL) {
            dodawanie(n, start->p_syn);
        } else {
            struct wezel *nowy = (struct wezel*)malloc(sizeof(struct wezel));
            nowy->wartosc = n;
            nowy->l_syn = NULL;
            nowy->p_syn = NULL;
            nowy->rodzic = start;
            start->p_syn = nowy;
        }
    }
    return 0;
}

void in_order_tree_walk(struct wezel *start) {
    if (start->l_syn != NULL)
        in_order_tree_walk(start->l_syn);
    printf("%d\n", start->wartosc);
    if (start->p_syn != NULL)
        in_order_tree_walk(start->p_syn);
}

int main() {
    // Przyklad użycia:
    dodawanie(10, root);
    dodawanie(5, root);
    dodawanie(15, root);

    printf("Wypisanie wezlow drzewa w kolejnosci przechodzenia (in-order):\n");
    in_order_tree_walk(root);

    // Wyszukiwanie wezla o wartosci 5:
    struct wezel *szukany = szukaj(root, 5);
    if (szukany != NULL) {
        printf("Wyszukany wezel: %d\n", szukany->wartosc);
        printf("Przodkowie wezla %d:\n", szukany->wartosc);
        while (szukany->rodzic != NULL) {
            printf("%d\n", szukany->rodzic->wartosc);
            szukany = szukany->rodzic;
        }
    } else {
        printf("Wezel o wartosci 5 nie istnieje w drzewie.\n");
    }

    return 0;
}
