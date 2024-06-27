classify(A,B,C,D,Cicek):-
	A =< 5.0,
	B =< 3.5,
	C = _,
	D = _,
	Cicek = 'Iris-setosa'
.
classify(A,B,C,D,Cicek):-
	A > 5.0,
	B =< 3.5,
	C = _,
	D = _,
	Cicek = 'Iris-versicolor'
.
classify(A,B,C,D,Cicek):-
	A = _,
	B > 3.5,
	C = _,
	D = _,
	Cicek = 'Iris-virginica'
.
