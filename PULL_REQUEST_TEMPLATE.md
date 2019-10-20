# Como usar branches?

O objetivo é trabalhar na branch \<development\>. Para mudar a working copy para a branch  \<development\> basta escrever o seguinte código no terminal:

`git checkout development`

depois deste comando, o git vai transferir as últimas atualizações do repositório na branch \<development\>. Comando útil para fazer isso manualmente:

`git pull origin development`

Sempre que começar a trabalhar numa nova feature ou bug fix é importante criar uma branch a partir de \<development>:

`git checkout -b nome_feature` 

este comando cria uma branch e faz o checkout automático para a branch criada.



A partir deste momento, o objetivo é trabalhar na feature e quando estiver pronta, juntar à \<development>.

- Comandos úteis:
  - `git commit -m "mensagem de commit"` comando para fazer commit, "snapshot" de alterações, i.e. savegame;
  - `git push origin nome_branch` comando para guardar os commits feitos no servidor



## Como juntar à branch principal?

Quando a feature estiver pronta, faz-se um "Pull Request" para fundir (merge) a branch criada com a principal.

Para isso, a nossa branch tem de estar no mínimo idêntica à superior para não causar conflitos.

No site do Repositório do GitHub [link](https://github.com/skdGT/ProjetoAEDA) tem uma opção para ver branches existentes, para fazer um Pull Request; clicar em "Pull Request" junto da branch que criamos previamente.



### Pull Requests

1. Fazer o 'compare' de \<development> com \<branch_criada> para não exportarmos as alterações para a branch principal \<master>

2. Detalhar o que foi feito, sucintamente, para que os outros membros possam entender a alteração, e eventualmente adicionar um dos membros como "reviewer" (isto envia uma notificação para o utilizador para que faça uma revisão do código no Pull Request, acelerando o processo)

3. Esperar que outro membro aprove o Pull Request
4. Lidar com eventuais conflitos de Merge
5. Eliminar branch criada (exite uma opção para isso no fim do merge)
6. Concluir Pull Request



### O que fazer depois?

1. `git checkout -b development` e `git pull origin development` para regressar à branch original e descarregar as alterações.
2. Trabalhar na próxima feature ou bug fix.