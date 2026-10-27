#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Agendamento {
    string paciente;
    string profissional;
    string data;
    int hora;
    int duracao;
    string status;
};

vector<Agendamento> ag;

void agendar_consulta(string paciente, string profissional, string data, int hora, int duracao) {
    try {
        if (hora >= 8) {
            if (hora < 18) {
                if (duracao > 0) {
                    bool ok = true;
                    for (int i = 0; i < ag.size(); i++) {
                        if (ag[i].data == data && ag[i].hora == hora && ag[i].profissional == profissional) {
                            ok = false;
                        }
                    }
                    if (ok) {
                        ag.push_back({paciente, profissional, data, hora, duracao, "MARCADO"});
                        cout << "Atendimento marcado para " << paciente << endl;
                    } else {
                        cout << "Horario ocupado" << endl;
                    }
                }
            }
        }
    } catch (...) {
    }
}

void remover_agendamento(string paciente, string data, int hora, string nova_data, int nova_hora) {
    for (int i = 0; i < ag.size(); i++) {
        if (ag[i].paciente == paciente && ag[i].data == data && ag[i].hora == hora) {
            bool ok = true;
            for (int j = 0; j < ag.size(); j++) {
                if (ag[j].data == nova_data && ag[j].hora == nova_hora && ag[j].profissional == ag[i].profissional) {
                    ok = false;
                }
            }
            if (ok) {
                ag[i].data = nova_data;
                ag[i].hora = nova_hora;
                cout << "Remarcado" << endl;
            } else {
                cout << "Horario ocupado" << endl;
            }
        }
    }
}

void listar_agendamentos(string data) {
    for (int i = 0; i < ag.size(); i++) {
        if (ag[i].data == data) {
            cout << ag[i].hora << " " << ag[i].paciente << " " << ag[i].profissional << " "
                 << ag[i].status << endl;
        }
    }
}

int main() {
    agendar_consulta("Ana", "Dr. Silva", "2026-10-05", 9, 30);
    agendar_consulta("Bruno", "Dr. Silva", "2026-10-05", 9, 30);
    agendar_consulta("Carla", "Dra. Souza", "2026-10-05", 14, 60);
    remover_agendamento("Ana", "2026-10-05", 9, "2026-10-06", 10);
    listar_agendamentos("2026-10-05");
    return 0;
}
