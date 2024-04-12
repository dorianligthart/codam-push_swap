# push_swap :
#### [subject_PFD_link](https://cdn.intra.42.fr/pdf/pdf/128392/en.subject.pdf)
TODO: Check and implement something like this [algorithm youtube video](https://www.youtube.com/watch?v=2aMrmWOgLvU).

```C
//double linked circular list as triple array.
typedef struct s_ps_stack
{
	unsigned int	*stack;
	unsigned int	*next;
	unsigned int	*prev;
	unsigned int	size;
	unsigned int	ptr;
}	t_ps_stack;
```

More efficient than linked list, but hard to follow sometimes, I strongly recommend double linked circular list. This is a pain to implement, but worth.
