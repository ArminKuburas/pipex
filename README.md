# pipex
## Description
This repository will hold everything I have done for the project pipex. This project aims to mimick the behaviors of the terminal pipe. So for example wherein a terminal you would write < infile cmd1 | cmd2 > outfile here you go ./pipex infile cmd1 cmd2 outfile. Simple as that. The main difficulties of this project for me were learning all of the new external functions we are allowed to use for it and the affects of taking a break mid-project. I decided I wanted to do the bonus early on but the mid-project break as well as some of the complexities involved made me rethink that decision. I might come back to this project later in the year to do the bonus for it. I'll have to replicate parts of it anyway.

## Table of Contents

- [pipex](#pipex)
- [Description](#Description)
- [Knowledge Gained](#Knowledge-Gained)
- [Installation](#Installation)
- [Usage](#usage)
- [Inspirations And Thank Yous](#inspirations-and-thank-you)

### Knowledge-Gained

I learnt a lot from this project. As stated earlier it was primarily the use of external functions but also some core concepts were refined as well. I will describe these below:

1.  First one of the things I learnt about was the environment variables and in general the environment term in terminals
     - So from my understanding the env variable that we use is some sort of value that affects how processes and programs run on a maschine.
     - Examples of env variables is the PATH. This is one I use extensively in this project. PATH specifies directories to search for executable files such as terminal commands like ls or awk.
2.  The second important thing I learnt about is processes and how they function up to some point anyway.
     - For example I use pid_t a lot which is a integer type used to represent process IDs. This way I was able to keep track of each process and use functions such as waitpid to wait until specific processes finished their tasks.
3.  The main and most important external functions I used were  
