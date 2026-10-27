// ==========================================================
// Arquivo: agenda_base.cpp
// Autor: Equipe de estagiarios - 03/02/2024
// Alterado por: Joao - 15/05/2025
// Alterado por: Marina - 09/01/2026
// ==========================================================

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct A {
    string p;
    string pr;
    string d;
    int h;
    int dur;
    string st;
};

vector<A> ag;

void add(string p, string pr, string d, int h, int dur) {
    // adiciona na lista
    try {
        if (h >= 8) {
            if (h < 18) {
                if (dur > 0) {
                    bool ok = true;
                    for (int i = 0; i < ag.size(); i++) {
                        if (ag[i].d == d && ag[i].h == h && ag[i].pr == pr) {
                            ok = false;
                        }
                    }
                    if (ok) {
                        ag.push_back({p, pr, d, h, dur, "MARCADO"});
                        cout << "Atendimento marcado para " << p << endl;
                    } else {
                        cout << "Horario ocupado" << endl;
                    }
                }
            }
        }
    } catch (...) {
    }
}

void rem(string p, string d, int h, string nd, int nh) {
    // remarca o atendimento
    for (int i = 0; i < ag.size(); i++) {
        if (ag[i].p == p && ag[i].d == d && ag[i].h == h) {
            bool ok = true;
            for (int j = 0; j < ag.size(); j++) {
                if (ag[j].d == nd && ag[j].h == nh && ag[j].pr == ag[i].pr) {
                    ok = false;
                }
            }
            if (ok) {
                ag[i].d = nd;
                ag[i].h = nh;
                cout << "Remarcado" << endl;
            } else {
                cout << "Horario ocupado" << endl;
            }
        }
    }
}

// void desmarcar(string p, string d, int h) {
//     ag.erase(...);
// }

// TODO: rever isso depois (Joao, 2025)

void lst(string d) {
    // lista os atendimentos do mes
    for (int i = 0; i < ag.size(); i++) {
        if (ag[i].d == d) {
            cout << ag[i].h << " " << ag[i].p << " " << ag[i].pr << " "
                 << ag[i].st << endl;
        }
    }
}

int main() {
    add("Ana", "Dr. Silva", "2026-10-05", 9, 30);
    add("Bruno", "Dr. Silva", "2026-10-05", 9, 30);
    add("Carla", "Dra. Souza", "2026-10-05", 14, 60);
    rem("Ana", "2026-10-05", 9, "2026-10-06", 10);
    lst("2026-10-05");
    return 0;
}
