# push_swap :
#### reference: [english.subject.pdf](https://cdn.intra.42.fr/pdf/pdf/128392/en.subject.pdf)

inspired by [this-youtube-video](https://www.youtube.com/watch?v=2aMrmWOgLvU). and myself :D

### Program objective :
Considering 2 stacks, stack A, an unordered list of integers, and an empty stack B.\
Possible stack manipulation moves to order the digits on/to stack A and B:
- push first element 
	of A to B or B to A
- swap first 2 elements
	of A or/and B
- shift (rotate) up/down all elements
	of A or/and B
### The moves and output strings (to stdout) are: 
`["pa", "ra", "rb", "rr", "sa", "sb", "ss", "pb", "rra", "rrb", "rrr"]`\
NOTE: e.g. `rra` 'reverse' rotates stack A. `rr` and `rrr` is rotating ***both*** stacks at the same time.

### ALGORITHM ideas:

- depending on last/first few digits in a range, shrink that range and expand the coresponding consecutive range.
- in case of a good digit going bad, save from the 1 (or more) conflicting digits,
	the highest digit(s) on the END of stack.
- then at end of handling that range move back those digits and update range. find out if its worth it, if range min is close to targeted digit.

### ALGORITHM stages:
1. Splitting stage 1/2 (split into 3 at start,):
   - split stack A to B.
   - split range on A over and over until certain range size or TBD. 
   - rotating/pushing so stack A will remain the high half and B the low half.
   - (shrinking, expanding consecutive range if range endings and beginnings are in the wrong place.)
2. Splitting stage 2/2:
   - split stack B to A.
   - the same as stage 1 but from stack B's perspective. 

### ALGORITHM using raster way of splitting a range :
- instead of low/high halfs, we move ordered (or one swap move away) bi-sequential (even/odd) at end of both stacks with remainder on stack B so we can rrr+pa.\
  note: doing this layered obviously doesn't work (raster of a raster).
- 


```C
//DOUBLE CIRCULAR LINKED LIST as INTEGER ARRAY.
//
//	since the integer list has no duplicate numbers, we could state that indexes are values.
//	and that values are indexes to next/previous 'nodes' (not really nodes,
//		just values of consecutive next/previous digits.);
typedef struct s_stack
{
	size_t	size;		// size of list.
	size_t	next[size]	// values pointing to the next digit in the list;
	size_t	prev[size]	// values pointing to the previous digit in the list;
	size_t	a;			// index to beginning of stack A. prev[a] is the last item in stack A.
	size_t	b;			// index to beginning of stack B. initialised SIZE_MAX since it's empty.
	t_range			ranges[PS_RANGE_COUNT]; // range split can not happen more than 68 times
	unsigned char	ri;						// (ri >= 0 && ri < 69). nice
}	t_stack;

//during program digits will be handled
typedef struct s_range
{
	size_t	min;
	size_t	max;
	size_t	offset_min;	// offsets happen because a range may shrink.
	size_t	offset_max;	// 
}	t_range;

```

More efficient than linked list, but hard to follow sometimes, I strongly recommend double linked circular list, as it's easier to write/grasp.
