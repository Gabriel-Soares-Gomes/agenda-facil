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

    for (const Agendamento& agendamento : agendamentos) {
        if (agendamento.data == data && agendamento.hora == hora && agendamento.profissional == profissional) throw invalid_argument("Agendamento já existe para o mesmo profissional e horário");
    }
}

void agendar_consulta(string paciente, string profissional, string data, int hora, int duracao) {
    validar_dados(paciente, profissional, data, hora, duracao);
    Agendamento novo_agendamento = {paciente, profissional, data, hora, duracao, "Marcado"};
    agendamentos.push_back(novo_agendamento);
    cout << "Agendamento realizado para " << paciente << endl;
}

void remarcar_agendamento(string paciente, string data, int hora, string nova_data, int nova_hora) {
    Agendamento agendamento_a_remarcar;
    bool horario_ocupado = false;
    for (Agendamento& agendamento : agendamentos) {
        if (agendamento.paciente == paciente && agendamento.data == data && agendamento.hora == hora) {
            agendamento_a_remarcar = agendamento;
            break;
        }
    }
    if (!(agendamento_a_remarcar.paciente.empty())) throw invalid_argument("Agendamento não encontrado para o paciente " + paciente + " na data " + data + " e hora " + to_string(hora));
    validar_dados(agendamento_a_remarcar.paciente, agendamento_a_remarcar.profissional, nova_data, nova_hora, agendamento_a_remarcar.duracao);
    agendamento_a_remarcar.data = nova_data;
    agendamento_a_remarcar.hora = nova_hora;
    cout << "Remarcado" << endl;
}

void listar_agendamentos(string data) {
    if (!regex_match(data, data_padrao)) throw invalid_argument("Data inválida: " + data);

    for (const Agendamento& agendamento : agendamentos) {
        if (agendamento.data == data) {
            cout << agendamento.hora << " " << agendamento.paciente << " " << agendamento.profissional << " " << agendamento.status << endl;
        }
    }
}

int main() {
    agendar_consulta("Ana", "Dr. Silva", "2026-10-05", 9, 30);
    agendar_consulta("Bruno", "Dr. Silva", "2026-10-05", 9, 30);
    agendar_consulta("Carla", "Dra. Souza", "2026-10-05", 14, 60);
    remarcar_agendamento("Ana", "2026-10-05", 9, "2026-10-06", 10);
    listar_agendamentos("2026-10-05");
    return 0;
}
