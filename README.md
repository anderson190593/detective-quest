🕵️ Detective Quest – Julgamento Final em C
Este projeto representa o capítulo mais avançado do jogo educativo Detective Quest, desenvolvido em linguagem C. O jogador explora uma mansão representada por uma árvore binária, coleta pistas associadas a cômodos, organiza essas pistas em uma árvore de busca binária (BST) e associa cada pista a um suspeito por meio de uma tabela hash. Ao final, o jogador deve acusar o culpado com base nas evidências coletadas.

🎯 Objetivo
Consolidar conceitos fundamentais de estruturas de dados em C por meio de um jogo interativo e lógico. O projeto integra árvore binária, BST, tabela hash, alocação dinâmica, recursividade e controle de fluxo para simular uma investigação completa.

🛠️ Tecnologias Utilizadas
- Linguagem: C
- Bibliotecas: stdio.h, stdlib.h, string.h
- Ferramentas: compilador GCC ou qualquer ambiente C compatível

🧱 Estrutura do Código
O projeto é modularizado em funções específicas para garantir clareza e manutenção:
|  |  | 
| main() |  | 
| criarSala() |  | 
| explorarSalas() |  | 
| inserirPista() |  | 
| exibirPistas() |  | 
| inserirNaHash() |  | 
| encontrarSuspeito() |  | 
| verificarSuspeitoFinal() |  | 



📦 Estrutura dos Dados
Árvore Binária – Mansão
Cada sala é representada por uma struct com nome, pista e ponteiros para esquerda e direita.
Árvore BST – Pistas
As pistas coletadas são armazenadas em uma árvore binária de busca para exibição ordenada.
Tabela Hash – Suspeitos
Cada pista é associada a um suspeito por meio de uma tabela hash com tratamento de colisões por encadeamento.

🔍 Funcionalidades
- Navegação interativa pela mansão
- Coleta automática de pistas
- Organização de pistas em ordem alfabética
- Associação de pistas a suspeitos
- Julgamento final com verificação lógica
- Mensagens informativas e interface clara

🧪 Como Executar
- Clone o repositório:
git clone https://github.com/seu-usuario/detective-quest-final.git
cd detective-quest-final
- Compile o código:
gcc detective.c -o detective
- Execute o jogo:
./detective



📚 Aprendizado
Este projeto reforça:
- Estruturas de dados: árvore binária, BST, tabela hash
- Alocação dinâmica e manipulação de ponteiros
- Modularização e recursividade
- Lógica condicional e controle de fluxo
- Simulação de sistemas interativos em C

📄 Licença
Este projeto está licenciado sob a MIT License.
