**DIM0501 — Boas Práticas de Programação**

**Relatório do Projeto da Unidade 1 — AgendaFácil**

Prof. Marcus Terra   ·   DIMAp/UFRN   ·   Semestre 2026.1   ·   Entrega: 25/10/2026

| Integrantes (nome e matrícula) | Linguagem |
| :---- | :---- |
| Gabriel Soares Gomes (20250036690) <br> Luís Felipe Costa Barreto (20250030515) <br> Luís Antônio Santos Rabelo (20250029819) <br> Marcus Vinícius De Lima Souza (20250032716) <br> Davi Summer Silva Costa (20250033590)| C++ |
| **Repositório ou arquivo entregue** | https://github.com/Gabriel-Soares-Gomes/agenda-facil |
|  |  |

**Como usar este modelo:**  preencha as seis seções abaixo, apague os textos em itálico e entregue em PDF ou Markdown. O relatório inteiro deve caber em até quatro páginas — é um documento de decisões, não uma redação.

**1\. Diagnóstico do código-base**

*Liste pelo menos dez anomalias encontradas no código-base, com no mínimo uma em cada categoria do checklist da Aula 2\. Em "onde", aponte a função, a variável ou a linha — "está tudo errado" não é localização. Em "por que é um problema", escreva o efeito prático sobre quem vai ler ou manter o código, não a regra violada. Numere as anomalias: a seção 2 vai se referir a elas por número.*

| \# | Categoria | Anomalia e onde está | Por que é um problema |
| :---- | :---- | :---- | :---- |
| 1 | Adequação e lógica | Mistura de regras de negócio com I/O. As funções add e rem tem instruções de saída (cout << "Remarcado", etc.) embutidas. | Funções com dupla responsabilidade devem ser separadas em outras funções de responsabilidade única, impedindo readequação ou aproveitamento de interfaces gráficas. |
| 2 | Adequação e lógica | Falta de verificação de sobreposição parcial. Na função add e rem, o código checa apenas se o horário (h) é exatamente igual ao agendado. | Se um agendamento dura 60 minutos e começa às 14h, o sistema permite marcar outro no meio da consulta (ex: 14:30), pois o cálculo ignora a duração (dur) na colisão de horários |
| 3 | Manutenibilidade | Ao decorrer de todo o código são encontradas variáveis mal nomeadas, utilizando, na maioria das vezes, uma única letra. Exemplo: Todas as variáveis do struct e até o próprio struct "A". | Variáveis com nomes ruins e sem padrão carecem de significado, dificultando o entendimento de quem está lendo o código e prejudicando totalmente a manutenibilidade, já que agora, o tempo voltado a entender a lógica do código, foi tomado por entender o que cada letra significa. |
| 4 | Manutenibilidade | A função add tem quatro comandos if aninhados sucessivamente e um for. |  A função é difícil de ler, não retorna rápido e tenta fazer muitas validações acumuladas. |
| 5 | Manutenibilidade | Comentários explicando códigos confusos como: // adiciona na lista na função add e // remarca o atendimento em rem. | O nome da função já deve deixar claro o que ela faz. Comentários devem explicar os "porquês" das decisões técnicas e de negócio, e não narrar o que o código está fazendo. |
| 6 | Organização e estética | A lógica de varrer o vetor procurando um conflito de horário é idêntica dentro de add e repetida dentro de rem. |  Se a regra de verificação de horários mudar, o desenvolvedor terá que alterar esse trecho manualmente em cada aparição sua, o que facilita introdução de novos bugs. |
| 7 | Organização e estética | Código morto. Há uma função // void desmarcar(...) que foi totalmente comentada e abandonada no arquivo | Polui o código e cria confusão visual. Trechos inúteis ou deprecados devem ser deletados ou implementados de uma vez. |
| 8 | Programação defensiva e segurança | Captura de erros genéricos e sem tratamento adequado na função add. Com catch(...). | Como o erro não é capturado de forma específica, ele também não é tratado, então qualquer erro que seja capturado é abafado de forma silenciosa, podendo causar problemas maiores e inesperados. |
| 9 | Programação defensiva e segurança | Falta de validação de entradas. Não há verificação para garantir que o nome do paciente (p), o médico (pr) ou a data (d) não sejam strings vazias (""). | Parâmetros externos devem ser validados logo na entrada. Atualmente, o sistema permite marcar consultas com campos inexistentes
| 10 |  Desempenho e recursos | Busca sem interrupção. Nos laços for dentro de add e rem, o loop continua percorrendo o array inteiro mesmo após já ter encontrado uma colisão de horário (ok = false). |  Gera iterações desnecessárias. Faltou um comando break ou um return imediato após constatar que o horário já está ocupado. |

**2\. O que foi resolvido e o que ficou como dívida**

*Uma linha por anomalia da seção 1, usando o mesmo número. Deixar algo por resolver é legítimo — desde que seja uma decisão consciente e justificada, e não um esquecimento. Dívida técnica declarada vale mais que dívida técnica escondida.*

| \# | Situação | Como foi resolvida, ou por que ficou |
| :---- | :---- | :---- |
| 1 | Regras de negócio com I/O | Criação de um método separado para validar dados |
| 2 | Conflito de horários de consultas | Método de validação verifica se há conflitos |
| 3 | Variáveis mal nomeadas | Mudança dos nomes de variáveis para esclarecer seus significados no código |
| 4 | Muitos if's aninhados | Separação dos if's para tratarem cláusulas de guarda e retornarem mais cedo |
| 5 | Comentários vagos | Criação de documentação de API e refatoração dos nomes dos métodos |
| 6 | Lógica de percorrer vetor repetida | Lógica implementada uma vez no método de validação |
| 7 | Código morto | Código defasado foi deletado |
| 8 | Catches genéricos | Catches agora capturam erros específicos |
| 9 | Parâmetros sem validação | Parâmetros passam por uma validação antes de entrarem na lógica principal |
| 10 | Busca sem interrupção | Os laços de repetição são interrompidos quando não é preciso mais percorrer a lista  |

*Preencha a coluna "Situação" com Resolvida ou Dívida assumida.*

**3\. Decisões de projeto**

*Registre de duas a quatro decisões que o código sozinho não explica: por que este tipo de dado e não outro, por que lançar exceção em vez de devolver valor padrão, por que separar em três funções e não em uma. O que se avalia aqui é a justificativa, não a escolha — quase sempre há mais de uma resposta defensável.*

| Decisão tomada | Alternativa descartada | Por que decidimos assim |
| :---- | :---- | :---- |
| Lançar invalid_argument quando o dado é inválido ou há conflito de horário | Manter o try { ... } catch (...) {} com if aninhados, que ignorava o erro sem avisar. | Na falha silenciosa, quem chama não sabe se a consulta foi marcada. |
| Extrair validar_dados e reutilizá-la em agendar_consulta e remarcar_agendamento | Repetir as validações e o laço de conflito dentro de cada função, como em add e rem | Há uma única fonte das regras (horário, duração, data, nomes, conflito) |
| Passar o vector<Agendamento> por parâmetro (const& quando só lê) | Vetor global ag	 | A dependência fica explícita e não há estado escondido. |
|  |  |  |

**4\. Mudanças de comportamento**

*A Etapa 4 muda, de propósito, o que o sistema faz com entradas inválidas. Registre cada mudança aqui. O caminho feliz não entra nesta tabela: se ele mudou, houve um erro de refatoração.*

| Entrada ou situação | O que acontecia antes | O que acontece agora |
| :---- | :---- | :---- |
| Hora de início < 8 ou ≥ 18 | Nada: nenhuma mensagem e nenhum agendamento (o catch (...) vazio engolia o caso) | Exceção "Hora fora do horário permitido: X" |
| Hora de início = 17 | Aceita (h < 18) | 	Rejeitada (hora >= HORARIO_FIM, com HORARIO_FIM = 17) |
| Hora + duração passando das 18h (ex.: 17h com 90 min) | Aceito, sem checagem	 | Exceção "Duração e horário do agendamento excedem as 18h" |
| Data fora do padrão AAAA-MM-DD ao agendar | Aceita e gravada como veio | Exceção "Data inválida: ..." |
|  |  |  |

**5\. Como executar e gerar a documentação**

| Item | Resposta |
| :---- | :---- |
| Comando para compilar e executar | $ g++ agenda_base.cpp -o agenda && ./agenda |
| Comando para gerar a documentação de API | $ doxygen Doxyfile |
| Onde a documentação gerada ficou no repositório | docs/html |
| Saída do programa de demonstração |  |

Saída: 

Agendamento realizado para Ana<br>
Erro: Agendamento já existe para o mesmo profissional e horário<br>
Agendamento realizado para Carla<br>
Remarcado com sucesso<br>
14:00 | Carla | Dra. Souza | Marcado<br>


**6\. Uso de ferramentas de IA**

| Pergunta | Resposta |
| :---- | :---- |
| Foram usadas ferramentas de IA neste trabalho? | (   ) Não        ( X ) Sim |
| Em quais etapas, e para quê? | Foi utilizado IA para a geração do texto base do relatório |

*O uso é permitido. O professor pode pedir que qualquer integrante explique qualquer trecho do código entregue.*

**Conferência antes de enviar**

**☐**  O programa de demonstração compila e roda, e imprime a mesma saída do código-base.

**☐**  Toda anomalia da seção 1 aparece na seção 2, resolvida ou declarada como dívida.

**☐**  O README permite que outra pessoa execute o projeto sem perguntar nada.

**☐**  Os textos em itálico deste modelo foram apagados.

*Código que funciona mas não se explica não está pronto.*