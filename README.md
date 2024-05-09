# push_swap :
#### [subject_PFD_link](https://cdn.intra.42.fr/pdf/pdf/128392/en.subject.pdf)
TODO: Check and implement something like this [algorithm youtube video](https://www.youtube.com/watch?v=2aMrmWOgLvU).

```C
//DOUBLE CIRCULAR LINKED LIST, VIEWED AS ARRAYS.
//	- next[argc], values pointing to the next in the list;
//	- prev[argc], values pointing to the previous in the list;
//
//	indexes are values, values are indexes to next/previous 'nodes';
typedef struct s_ps_stack
{
	size_t	a;
	size_t	b;
	size_t	size;
}	t_ps_stack;
```

More efficient than linked list, but hard to follow sometimes, I strongly recommend double linked circular list, as it's easier to write/grasp.
