# push_swap :
#### [subject_PFD_link](https://cdn.intra.42.fr/pdf/pdf/128392/en.subject.pdf)
TODO: Check and implement something like this [algorithm youtube video](https://www.youtube.com/watch?v=2aMrmWOgLvU).

```C
//bytes malloc'ed: 3 * sizeof(int) * (argc  + 1)
//               + 2 * sizeof(int)
//               + 2 * sizeof(int *);
//
//double linked circular list as triple array.
//sizeof(stack) = 3 * argc * sizeof(int);
//sizeof(next) = sizeof(int *);
//sizeof(prev) = sizeof(int *);
typedef struct s_ps_stacks
{
	unsigned int	*stack;
	unsigned int	*next;
	unsigned int	*prev;
	unsigned int	a_ptr;
	unsigned int	a_ptr;
}	t_ps_stacks;
```

More efficient than linked list, but hard to follow sometimes, I strongly recommend double linked circular list, as it's easier to write/grasp.
