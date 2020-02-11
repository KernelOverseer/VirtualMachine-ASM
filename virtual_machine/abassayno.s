.name "abassayno"
.comment "abassayno im9our fobassank"

start:
	sti r1, %:livenow, %1
livenow:
	live %0
	and r1, %0, r2
erase:
	sti r3, %:start, %0
	sti r3, %:start, %3
verif_champ_zjmp:
	ldi %:livenow, %1, r14
	and r14, r1, r14
	zjmp %:livenow
	and %0, %0, r13
	fork %:livenow
	and %0, %0, r13
	ld %0, r1
	zjmp %:livenow
