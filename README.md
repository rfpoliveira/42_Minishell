# 42_Minishell

This was a team based project wish was made by myself and my colleague [Joana](https://github.com/Joana-pcm) wish did an amazing job.

The objective was making a version of shell with some directives that can be checked in the subject with more detail but in resume we handled signals, redirects, pipes, expansions, enviromental variables, heredocs and some built ins like echo, export, env, cd etc. We handled both absolute and relative paths in cd, the expansions of '~' and the terminal prompt, all of which were not needed in the subject but we thought it made sense and elevated the project.
we both handled exit codes and error mensages just like bash does.
All this with no leaks or invalid reads while dinamic allocating all the memory we needed.

I was responsable for the parsing of the commands, expansions, signals, prompt and parsing the informacion from the user in a organized way to the user. Joana handleded the pipes, redirections, heredocs and built ins.

The project made us understand the way bash works in a very very deep way, the way redirections work, how pipes work, how to fork processes and use that to our advantage, how to handle multiple fd's and signals both in a single and multiple processes and how exit codes were made and how it can help us.
