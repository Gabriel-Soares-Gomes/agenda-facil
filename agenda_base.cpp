#include <iostream>
#include <string>
#include <vector>
#include <regex>
using namespace std;

const unsigned short int HORARIO_INICIO = 8;
const unsigned short int HORARIO_FIM = 17;
const unsigned short int MINS_POR_PERIODO = 15;
//Padrão de data: AAAA-MM-DD / YYYY-MM-DD
const regex data_padrao(R"(^\d{4}-\d{2}-\d{2}$)");

struct Agendamento {
    string paciente;
    string profissional;
    string data;
    int hora;
    int duracao;
    string status;
};

/**
 * @brief Valida os dados de um agendamento, verificando horários, duração, formato da data e conflitos com outros agendamentos.
 * @param paciente Nome do paciente.
 * @param profissional Nome do profissional.
 * @param data Data do agendamento no formato AAAA-MM-DD.
 * @param hora Hora do agendamento (em formato 24h).
 * @param duracao Duração do agendamento em minutos.
 * @param agendamentos Lista de agendamentos existentes para verificar conflitos.
 * @throws std::invalid_argument Se algum dos dados for inválido ou se houver conflito com outro agendamento existente.
 */
void validar_dados(string paciente, string profissional, string data, int hora, int duracao, const vector<Agendamento>& agendamentos){
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

/**
 * @brief Agenda uma consulta para um paciente com um profissional específico em uma data e hora determinadas.
 * @param paciente Nome do paciente.
 * @param profissional Nome do profissional.
 * @param data Data do agendamento no formato AAAA-MM-DD.
 * @param hora Hora do agendamento (em formato 24h).
 * @param duracao Duração do agendamento em minutos.
 * @param agendamentos Lista de agendamentos existentes para verificar conflitos.
 * @throws std::invalid_argument Se algum dos dados for inválido ou se houver conflito com outro agendamento existente.
 */
void agendar_consulta(string paciente, string profissional, string data, int hora, int duracao, vector<Agendamento>& agendamentos) {
    validar_dados(paciente, profissional, data, hora, duracao, agendamentos);
    Agendamento novo_agendamento = {paciente, profissional, data, hora, duracao, "Marcado"};
    agendamentos.push_back(novo_agendamento);
    cout << "Agendamento realizado para " << paciente << endl;
}

/**
 * @brief Remarca um agendamento existente para uma nova data e hora.
 * @param paciente Nome do paciente.
 * @param data Data do agendamento no formato AAAA-MM-DD.
 * @param hora Hora do agendamento (em formato 24h).
 * @param nova_data Nova data do agendamento no formato AAAA-MM-DD.
 * @param nova_hora Nova hora do agendamento (em formato 24h).
 * @param agendamentos Lista de agendamentos existentes para verificar conflitos.
 * @throws std::invalid_argument Se o agendamento não for encontrado ou se os novos dados forem inválidos.
 */
void remarcar_agendamento(string paciente, string data, int hora, string nova_data, int nova_hora, vector<Agendamento>& agendamentos) {
    Agendamento* agendamento_encontrado = nullptr;
    for (Agendamento& agendamento : agendamentos) {
        if (agendamento.paciente == paciente && agendamento.data == data && agendamento.hora == hora) {
            agendamento_encontrado = &agendamento;
            break;
        }
    }
    if (agendamento_encontrado == nullptr) {
        throw invalid_argument("Agendamento não encontrado para o paciente " + paciente + " na data " + data + " e hora " + to_string(hora));
    }
    validar_dados(agendamento_encontrado->paciente, agendamento_encontrado->profissional, nova_data, nova_hora, agendamento_encontrado->duracao, agendamentos);
    agendamento_encontrado->data = nova_data;
    agendamento_encontrado->hora = nova_hora;
    cout << "Remarcado com sucesso" << endl;
}

/**
 * @brief Lista todos os agendamentos para uma data específica.
 * @param data Data dos agendamentos no formato AAAA-MM-DD.
 * @param agendamentos Lista de agendamentos existentes.
 * @throws std::invalid_argument Se a data for inválida.
 */
void listar_agendamentos(string data, const vector<Agendamento>& agendamentos) {
    if (!regex_match(data, data_padrao)) throw invalid_argument("Data inválida: " + data);

    for (const Agendamento& agendamento : agendamentos) {
        if (agendamento.data == data) {
            cout << agendamento.hora << ":00 | " << agendamento.paciente << " | " << agendamento.profissional << " | " << agendamento.status << endl;
        }
    }
}

int main() {
    vector<Agendamento> agendamentos;
    try {agendar_consulta("Ana", "Dr. Silva", "2026-10-05", 9, 30, agendamentos);} catch (const invalid_argument& e) {cout << "Erro: " << e.what() << endl;}
    try{agendar_consulta("Bruno", "Dr. Silva", "2026-10-05", 9, 30, agendamentos);} catch (const invalid_argument& e) {cout << "Erro: " << e.what() << endl;}
    try{agendar_consulta("Carla", "Dra. Souza", "2026-10-05", 14, 60, agendamentos);} catch (const invalid_argument& e) {cout << "Erro: " << e.what() << endl;}
    try{remarcar_agendamento("Ana", "2026-10-05", 9, "2026-10-06", 10, agendamentos);} catch (const invalid_argument& e) {cout << "Erro: " << e.what() << endl;}
    try{listar_agendamentos("2026-10-05", agendamentos);} catch (const invalid_argument& e) {cout << "Erro: " << e.what() << endl;}
    return 0;
}