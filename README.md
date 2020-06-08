# minishell
* parsing steps: https://mywiki.wooledge.org/BashParser
* redirections + generell bash guide: https://catonmat.net/bash-one-liners-explained-part-three
* pipes: https://stackoverflow.com/questions/7281894/how-do-i-chain-stdout-in-one-child-process-to-stdin-in-another-child-in-c?noredirect=1&lq=1 
* bash doc: https://tiswww.case.edu/php/chet/bash/bashref.html#Shell-Syntax
* make own shell: https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
* process doc: http://openbook.rheinwerk-verlag.de/linux_unix_programmierung/Kap07-000.htm#RxxKap07000040001DB1F02D100
* git info: https://bit.ly/2QPNmFc

## PARSING

* split comands input into tokens on unescaped semicolons/spaces
* replace environment variables
* split comands on unescaped pipes and save new outputs
* encode redirections and save the filenames
* remove quotes and backslash characters from token

## USAGE
* run make command in shell
* execute with ./minishell
