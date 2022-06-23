#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class Queue {
private:

    struct el {
        int i;
        int j;
        el* next;
    };
    int n;
    el* Q;
    el* Qend;

public:

    Queue() {
        n = 0;
        Q = nullptr;
        Qend = nullptr;
    }

    void push(int a, int b) {
        el* p = new el;
        p->i = a;
        p->j = b;
        p->next = nullptr;

        if (Q == nullptr) {
            Q = p;
            Qend = p;
        }
        else {
            Qend->next = p;
            Qend = p;
        }
        n++;
    }

    void top(int &a, int &b) {
        a = Q->i;
        b = Q->j;
    }

    void pop() {
        el* p = Q;
        Q = Q->next;
        delete p;
        n--;
    }

    int size() {
        return n;
    }

    /*void print_Q() {
        for (el* p = Q;p != nullptr; p = p->next) {
            cout << p->i << " " << p->j << endl;
        }
    }*/
};

int main()
{
    setlocale(LC_ALL, "ru");

    char** L = new char* [500];
    for (int i = 0;i < 500;i++)L[i] = new char[500];
    int i = 0, j = 0, s_i, s_j, f_i, f_j, n, m, metka, a, b;
    FILE* f = fopen("L.txt", "r");

    if (f == nullptr) {
        cout << "файл L.txt не найден!" << endl;
        return -1;
    }
    else {
        char c;
        while ((c = fgetc(f)) != EOF) {
            if (c == 's') {
                s_i = i;
                s_j = j;
            }
            if (c == 'f') {
                f_i = i;
                f_j = j;
            }
            if (c == '\n') {
                L[i][j] = '\0';
                i++;
                j = 0;
            }
            else {
                L[i][j] = c;
                j++;
            }
        }
        L[i][j] = '\0';
    }
    n = i + 1;
    m = j;

    int** M = new int* [n];
    for (i = 0;i < n;i++) {
        M[i] = new int[m];
        for (j = 0;j < m;j++)M[i][j] = 0;
    }
    

    metka = 2;
    M[s_i][s_j] = metka - 1;
    Queue q;
    q.push(s_i, s_j);
    bool existence_of_a_path = false;

    while (q.size() != 0) {
        q.top(a, b);

        if (a == f_i && b == f_j) {
            existence_of_a_path = true;
            break;
        }

        for (i = a - 1;i < a + 2;i++)
            for (j = b - 1;j < b + 2;j++)
                if (M[i][j] == 0 && L[i][j] != '#') {
                    q.push(i, j);
                    M[i][j] = metka;
                }
        metka++;
        q.pop();
    }
    
    ofstream fout("L_out.txt");

    if (existence_of_a_path) {
        a = f_i; 
        b = f_j;

        while (M[a][b]!=1) {
            int min_i = a, min_j = b;

            for (i = a - 1;i < a + 2 && f;i++)
                for (j = b - 1;j < b + 2 && f;j++)
                    if (M[i][j] < M[min_i][min_j] && M[i][j]!=0) {
                        min_i = i;
                        min_j = j;
                    }

            L[min_i][min_j] = '*';
            a = min_i; b = min_j;
        }
    }
    else fout << "нет пути! " << endl;

    for (i = 0;i < n;i++) {
        for (j = 0;j < m;j++) {
            fout << L[i][j];
        }
        fout << endl;
    }
    fout << endl;
}