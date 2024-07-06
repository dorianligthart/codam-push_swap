```c
//be aware: pushA and pushB are push TO A/B, not FROM.
//easier reading.

/*Hard coded stacksize cases:
	2: solve3(A),
	3: solve3(A),
	4: TODO: make function to hardcode size 4,
	5: split / 2, A:3, B:2;		solve3(A), solve3(B), pushB, pushB.
	6: split / 2, A:3, B:3;		solve3(A), solve3(B), pushB, pushB, pushB.
	7: split / 3, A:3, B:2,2;	solve3(A), pushB, pushB, (swapAB), pushB, pushB.
	8: split / 3, A:3, B:2,3;	solve3(A), pushB, pushB, (swapA), solve3(B), pushB, pushB, pushB.
	9: split / 3, A:3, B:3,3;	solve3(A), pushB, pushB, pushB, solve3notempty(B),
								pushB, pushB, pushB, solve3(B), pushB, pushB, pushB.
	x > 9, use general algorithm....

Non empty stack rangesize cases:
rangesize=2 on stack A:
	A: [0, 1 ...] -> .
	A: [1, 0 ...] -> swapA.

rangesize=2 on stack B:
	B: [1, 0 ...] -> pushB, pushB.
	B: [0, 1 ...] -> swapB, pushB, pushB.

rangesize=3 on stack A:
	A: [0, 1, 2 ...] -> .
	A: [1, 0, 2 ...] -> swapA.
	A: [0, 2, 1 ...] -> rotA, swapA, revrotA.
	A: [1, 2, 0 ...] -> rotA, swapA, revrotA, swapA.
	A: [2, 0, 1 ...] -> swapA, rotA, swapA, revrotA.
	A: [2, 1, 0 ...] -> swapA, rotA, swapA, revrotA, swapA.

rangesize=3 on stack B:
	B: [2, 1, 0 ...] -> pushB, pushB, pushB.
	B: [2, 0, 1 ...] -> pushB, swapB, pushB, pushB.
	B: [1, 2, 0 ...] -> swapB, pushB, pushB, pushB.
	B: [0, 2, 1 ...] -> swapB, pushB, swapB, pushB, pushB.
	B: [1, 0, 2 ...] -> revrotB, swapB, pushB, rotB, pushB, pushB.
	B: [0, 1, 2 ...] -> revrotB, swapB, pushB, pushB, rotB, pushB.

rangesize=4 on stack A:
	A: [0, 1, 2, 3 ...] -> .
	A: [1, 0, 2, 3 ...] -> swapA.
	A: [0, 2, 1, 3 ...] -> rotA, swapA, revrotA.
	A: [1, 2, 0, 3 ...] -> rotA, swapA, revrotA, swapA.
	A: [2, 0, 1, 3 ...] -> swapA, rotA, swapA, revrotA.
	A: [2, 1, 0, 3 ...] -> swapA, rotA, swapA, revrotA, swapA.
	A: [0, 1, 3, 2 ...] -> rotA, rotA, swapA, revrotA, revrotA.
	A: [1, 0, 3, 2 ...] -> rotA, rotA, swapA, revrotA, revrotA, swapA.
	A: [0, 2, 3, 1 ...] -> rotA, rotA, swapA, revrotA, swapA, revrotA.
	A: [1, 2, 3, 0 ...] -> rotA, rotA, swapA, revrotA, swapA, revrotA, swapA.
	A: [2, 0, 3, 1 ...] -> swapA, rotA, rotA, swapA, revrotA, swapA, revrotA.
	A: [2, 1, 3, 0 ...] -> swapA, rotA, rotA, swapA, revrotA, swapA, revrotA, swapA.
	A: [0, 3, 1, 2 ...] -> rotA, swapA, rotA, swapA, revrotA, revrotA.
	A: [1, 3, 0, 2 ...] -> rotA, swapA, rotA, swapA, revrotA, revrotA, swapA.
	A: [0, 3, 2, 1 ...] -> rotA, swapA, rotA, swapA, revrotA, swapA, revrotA.
	A: [1, 3, 2, 0 ...] -> rotA, swapA, rotA, swapA, revrotA, swapA, revrotA, swapA.
	A: [2, 3, 0, 1 ...] -> rotA, swapA, rotA, swapA, revrotA, revrotA, swapA, rotA, swapA, revrotA.
	A: [2, 3, 1, 0 ...] -> rotA, swapA, rotA, swapA, revrotA, revrotA, swapA, rotA, swapA, revrotA, swapA.
	A: [3, 0, 1, 2 ...] -> swapA, rotA, swapA, rotA, swapA, revrotA, revrotA.
	A: [3, 1, 0, 2 ...] -> swapA, rotA, swapA, rotA, swapA, revrotA, revrotA, swapA.
	A: [3, 0, 2, 1 ...] -> swapA, rotA, swapA, rotA, swapA, revrotA, swapA, revrotA.
	A: [3, 1, 2, 0 ...] -> swapA, rotA, swapA, rotA, swapA, revrotA, swapA, revrotA, swapA.
	A: [3, 2, 0, 1 ...] -> swapA, rotA, swapA, rotA, swapA, revrotA, revrotA, swapA, rotA, swapA, revrotA.
	A: [3, 2, 1, 0 ...] -> swapA, rotA, swapA, rotA, swapA, revrotA, revrotA, swapA, rotA, swapA, revrotA, swapA.

rangesize=4 on stack B:
	B: [3, 2, 1, 0 ...] -> pushB, pushB, pushB, pushB.
	B: [3, 2, 0, 1 ...] -> pushB, pushB, swapB, pushB, pushB.
	B: [3, 1, 2, 0 ...] -> pushB, swapB, pushB, pushB, pushB.
	B: [3, 0, 2, 1 ...] -> pushB, swapB, pushB, swapB, pushB, pushB.
	B: [3, 1, 0, 2 ...] -> pushB, revrotB, swapB, pushB, rotB, pushB, pushB.
	B: [3, 0, 1, 2 ...] -> pushB, revrotB, swapB, pushB, pushB, rotB, pushB.
	B: [2, 3, 1, 0 ...] -> pushB, pushB, swapB, pushB, pushB.
	B: [2, 3, 0, 1 ...] -> pushB, pushB, swapAB, pushB, pushB.
	B: [1, 3, 2, 0 ...] -> revrotB, pushB, pushB, rotB, pushB, pushB.
	B: [0, 3, 2, 1 ...] -> revrotB, pushB, pushB, pushB, rotB, pushB.
	B: [1, 3, 0, 2 ...] -> pushB, pushB, swapAB, pushB, swapA, pushB. 
	B: [0, 3, 1, 2 ...] -> pushB, pushB, swapAB, pushB swapA, pushB, swapA.
	B: [2, 1, 3, 0 ...] -> pushB, rotB, pushB, revrotB, swapA, pushB, pushB. 
	B: [2, 0, 3, 1 ...] -> pushB, rotB, pushB, revrotB, swapAB, pushB, pushB.
	B: [1, 2, 3, 0 ...] -> pushB, rotA, pushB, pushB, revrotA, pushB.
	B: [0, 2, 3, 1 ...] -> rotB, pushB, pushB, revrotB, swapAB, pushB, pushB.
	B: [1, 0, 3, 2 ...] -> pushB, revrotAB, pushB, pushB, swapB, rotAB, pushB.
	B: [0, 1, 3, 2 ...] -> pushB, pushB, swapA, rotA, rotA, pushB, pushB, revrotA, revrotA.
	B: [2, 1, 0, 3 ...] -> pushB, pushB, rotAB, pushB, revrotB, swapA, revrotA, pushB.
	B: [2, 0, 1, 3 ...] -> pushB, pushB, swapB, pushB, swapA, rotA, swapA, pushB, revrotA.
	B: [1, 2, 0, 3 ...] -> pushB, pushB, swapAB, pushB, swapA, rotA, swapA, revrotA, pushB.
	B: [0, 2, 1, 3 ...] -> pushB, pushB, swapAB, pushB, swapA, rotA, swapA, pushB, revrotA.
	B: [1, 0, 2, 3 ...] -> pushB, pushB, swapB, rotA, rotA, pushB, pushB, revrotA, revrotA.
	B: [0, 1, 2, 3 ...] -> pushB, pushB, swapAB, rotA, rotA, pushB, pushB, revrotA, revrotA.
*/

/*Range Split Algorithm simplified example:

A range of digits can be:
H=high, M=medium, L=low;
t=range_threshold_reached (depending on argc).

stack A:						stack B:					Action:
[unordered_digits]				[empty]						argv to stack A.
[H]								[M, L]						split A in 3.
[HH]							[HL, M, L]					split A in 2.
[HHHt]							[HHLt, HL, M, L]			split A in 2.
[HHt]							[HL, M, L]					split A in 2.
[HLH, HHt]						[HLLt, M, L]				split B in 2.
[HLHHt, HHt]					[HLHLt, HLLt, M, L]			push B.
[HLHs, HHt]						[HLLt, M, L]				push B.
[HLLs, HLHs, HHt]				[M, L]						push B.
[H]								[M, L]						etc for medium/low digits...

Conclusion:
- Initially split A into 3 ranges if argc > 6.
- Need to split A range? push lower half to B.
- Need to split B range? push upper half to A.
- If range digit count gets under certain threshold,
	we solve range using different different algorithm.
*/

/*Range Solve Algorithm:
4 ways to bring number from B to A: ra+rb, ra+rrb, rra+rb, rra+rrb;
	use the fewest moves way.
	repeat this until range.min is reached.
*/
```


### old notes:

//ALGORITHM steps:
1.  divide stack A 1/2 to stack B (upper or lower half depending on: 
	if the result will be high to low or low to high(optional!)),
	then go through both stacks at same time to push
	to bottom of both stacks 2/4, 3/6, 4/8, 5/10 etc,
	so that a range is not bigger than PS_RA NGE_MIN.
    1.1 To be able to do this you need to know size % PS_RANGE_MIN and edit
	the ranges each time we do an iteration.
    1.2 
2.  pushA/rotateA/swapAB to stack B into the ranges.
    2.1 keep highest range on stack A.
3.  solve the (new) range on stack A, then rotate B until smallest/biggest range
	appears, push that range to stack A, sort range.
4.  repeat step 3 range->count - 1 amount of times.


find out what range size is best. 
Test 10times with 16 32 64 128 uints on stack B,
and range size 6 8 12 16 24 32, see the average, compare ratios between next/prev rs.
