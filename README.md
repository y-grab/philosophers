# philosophers

One or more philosophers sit at a round table. There is a large bowl of spaghetti in the middle of the table. The philosophers alternatively **eat**, **think**, or **sleep**. None of them should do more than one activity at the same time. There are also forks on the table. There are as many forks as philosophers. A philosopher has to take their right and their left forks to eat, one in each hand. When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again. The simulation stops when a philosopher dies of starvation or when every philosopher has eaten certain number of times (optional parameter).  

The specific rules are:  
- Each philosopher should be a thread.  
- To prevent philosophers from duplicating forks, you should protect the forks state with a mutex for each of them.  
- Any state change of a philosopher should display a message formatted as follows:  
> timestamp_in_ms X action  

X is the number of a philosopher  
- A displayed message should not be mixed up with another messages.  
- A message announcing a philosopher died should be displayed no more than 10 ms after the actual death.

For more information see [subject](https://github.com/y-grab/philosophers/blob/main/subject/philo_subject.pdf)
