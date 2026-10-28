# AgendaFácil

Sistema de agendamento simplificado, em C++, desenvolvido para a disciplina de Boas Práticas de Programação (DIM0501, DIMAp/UFRN, 2026.1), com o Prof. Marcus Terra.

## O que é

O sistema permite agendar, remarcar e listar consultas de pacientes com profissionais. Os dados são validados antes de cada operação:

- horário de início entre 8h e 17h (exclusive), com término até as 18h;
- duração de 15 a 120 minutos, em múltiplos de 15;
- data no formato `AAAA-MM-DD`;
- paciente e profissional não vazios;
- sem conflito de horário para o mesmo profissional.

Dados inválidos lançam `std::invalid_argument` com uma mensagem descritiva.

## Como compilar e executar

```bash
g++ agenda_base.cpp -o agenda && ./agenda
```

## Como gerar a documentação

Com o [Doxygen](https://www.doxygen.nl/) instalado:

```bash
doxygen Doxyfile
```

A documentação é gerada em `docs/html`. Abra `docs/html/index.html` no navegador.
Em seguida percorra o caminho `docs/html` para visualizar a documentação.

## Autores

- Gabriel Soares Gomes
- Luís Felipe Costa Barreto
- Luís Antônio Santos Rabelo
- Marcus Vinícius De Lima Souza
- Davi Summer Silva Costa