#include <iostream>
#include <string>
#include <vector>
#include <regex>
using namespace std;

const unsigned short int HORARIO_INICIO = 8;
const unsigned short int HORARIO_FIM = 17;
const unsigned short int MINS_POR_PERIODO = 15;
//Padrão de data: AAAA-MM-DD
const regex data_padrao(R"(^\d{4}-\d{2}-\d{2}$)");

struct Agendamento {
    string paciente;
    string profissional;
    string data;
    int hora;
    int duracao;
    string status;
};

vector<Agendamento> agendamentos;

void validar_dados(string paciente, string profissional, string data, int hora, int duracao){
    if (hora < HORARIO_INICIO or hora >= HORARIO_FIM) throw invalid_argument("Hora fora do horário permitido: " + to_string(hora));

    unsigned short int hora_fim = hora + duracao / 60;
    if (hora_fim > 18) throw invalid_argument("Duração e horário do agendamento excedem as 18h");

    unsigned short int qntd_periodos = duracao / MINS_POR_PERIODO;
    if (qntd_periodos < 1 or qntd_periodos > 8) throw invalid_argument("Duração do agendamento fora do intervalo permitido: " + to_string(duracao));

    if (!regex_match(data, data_padrao)) throw invalid_argument("Data inválida: " + data);

    if (paciente.empty() or profissional.empty()) throw invalid_argument("Paciente ou profissional não podem ser vazios");

    for (Agendamento agendamento : agendamentos) {
        if (agendamento.data == data && agendamento.hora == hora && agendamento.profissional == profissional) throw invalid_argument("Agendamento já existe para o mesmo profissional e horário");
    }
}

void agendar_consulta(string paciente, string profissional, string data, int hora, int duracao) {
    validar_dados(paciente, profissional, data, hora, duracao);
    Agendamento novo_agendamento = {paciente, profissional, data, hora, duracao, "Marcado"};
    agendamentos.push_back(novo_agendamento);
    cout << "Agendamento realizado para " << paciente << endl;
}

void remover_agendamento(string paciente, string data, int hora, string nova_data, int nova_hora) {
    for (int i = 0; i < agendamentos.size(); i++) {
        if (agendamentos[i].paciente == paciente && agendamentos[i].data == data && agendamentos[i].hora == hora) {
            bool ok = true;
            for (int j = 0; j < agendamentos.size(); j++) {
                if (agendamentos[j].data == nova_data && agendamentos[j].hora == nova_hora && agendamentos[j].profissional == agendamentos[i].profissional) {
                    ok = false;
                }
            }
            if (ok) {
                agendamentos[i].data = nova_data;
                agendamentos[i].hora = nova_hora;
                cout << "Remarcado" << endl;
            } else {
                cout << "Horario ocupado" << endl;
            }
        }
    }
}

void listar_agendamentos(string data) {
    for (int i = 0; i < agendamentos.size(); i++) {
        if (agendamentos[i].data == data) {
            cout << agendamentos[i].hora << " " << agendamentos[i].paciente << " " << agendamentos[i].profissional << " "
                 << agendamentos[i].status << endl;
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
