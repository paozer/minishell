The minishell project aims for students to recreate a simplified yet useable shell. Introduced/refined concepts include signals, processes, file descriptors, environment variables, Termcap library...

This project is subject to 42's norm which restricts naming conventions, function and line lenghts and more. Some weird sections may therefore be the result of said norm.

The final version of the project was rated 109/115 by three fellow students.
This minishell was a team effort from [pminne](https://github.com/M-Philippe) and myself.

### Features
#### subject requirements
* builtins: echo (with -n), cd (only relative/absolute paths), pwd/export/unset/env/exit (w/o options)
* display a prompt while waiting for input
* ; separates commands like in bash
* ' and " act like in bash except for multiline commands
* <, > and >> act like in bash except for file descriptor aggreation
* | act like in bash
* environment variables and $? act like in bash
* ctrl-C, ctrl-D and ctrl-\ act like in bash
#### subject bonus part
* line edition
* left/right cursor movement
* up/down arrows for command history and subsequent line edition
* goto start/end of a line w/ home/end keys

#### additional features
* variable declaration w/o export (`$ my_var=my_value`)
* ctrl-L to clear the screen
* the prompt displays the current directory name and git information if applicable
* cd implicitly by entering the desired directory name

### Installation
Our minishell should play nicely on MacOS and Linux.
Copy paste the following command in your shell and execute it.

`git clone https://github.com/paozer/minishell && cd minishell && make && ./minishell`

### Resources
* [bash reference](https://www.tiswww.case.edu/php/chet/bash/bashref.html)
* [shell tutorial](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
* [parsing](https://www.mywiki.wooledge.org/BashParser)
* [i/o redirections](https://www.catonmat.net/bash-one-liners-explained-part-three)
* [process piping](https://www.stackoverflow.com/questions/7281894/how-do-i-chain-stdout-in-one-child-process-to-stdin-in-another-child-in-c?noredirect=1&lq=1)
* [processes (german)](http://www.openbook.rheinwerk-verlag.de/linux_unix_programmierung/Kap07-000.htm#RxxKap07000040001DB1F02D100)
