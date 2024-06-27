		/*place(ID)*/
place(adminOffice).
place(cafeteria).
place(engineeringBld).
place(library).
place(socialScienceBld).
place(lectureHall).
place(instituteY).
place(instituteX).

		/*route(placeID,placeID,time)*/

route(adminOffice,engineeringBld,3).
route(adminOffice,cafeteria,4).
route(adminOffice,library,1).

route(cafeteria,library,5).
route(cafeteria,adminOffice,4).
route(cafeteria,socialScienceBld,2).

route(engineeringBld,adminOffice,3).
route(engineeringBld,library,5).
route(engineeringBld,lectureHall,3).

route(library,adminOffice,1).
route(library,cafeteria,5).
route(library,engineeringBld,5).
route(library,instituteY,3).
route(library,socialScienceBld,2).

route(socialScienceBld,cafeteria,2).
route(socialScienceBld,library,2). 
route(socialScienceBld,instituteX,8).

route(lectureHall,engineeringBld,2).
route(lectureHall,instituteY,3).

route(instituteY,library,3).
route(instituteY,lectureHall,2).


route(instituteX,socialScienceBld,8).

		/*object(ID,weight,placeID,placeID,urgency,personID)*/
object(cay,1,cafeteria,engineeringBld,low,enes).
object(kitap,2,library,socialScienceBld,medium,kimse).
object(laptop,3,engineeringBld,lectureHall,high,kimse).
object(notes,2,library,instituteY,high,kimse).
object(computer,4,engineeringBld,instituteX,medium,kimse).
		
		
		/*personel(ID,capacity,workHour,currentDelivery,currentLocation)*/
personel(enes,8,22,cay,cafeteria).
personel(feridun,9,26,bos,library).
personel(yasir,10,30,bos,engineeringBld).



breadth_first_search(Start, End, Path, Distance) :-				% İki node arası yolu bulabilmek için hazırlanan bfs algoritmasının ilk adımı sonrası recursive
    DistanceRev is 0,
    bfs([(Start, [])], End, PathRev, DistanceRev,FinalDist),
    reverse(PathRev, Path),
    Distance is FinalDist,
    !.

bfs([], _, _, _) :- fail. 							% kuyrukta node yoksa basarısız olmustur
bfs([(Node, Path) | _], Node, [Node | Path], DistanceRev,FinalDist):-		% End node ile kuyruktaki node aynı ise döngü durur
    FinalDist is DistanceRev,
    !
    .
bfs([(Node, Path) | Queue], End, FinalPath, DistanceRev,FinalDist) :-		% recursive döngü içeren bfs kodu
    findall((NextNode, [Node | Path]),
            (route(Node, NextNode,_), \+ member(NextNode, [Node | Path])),
            NextNodes),
    route(Node,NextNode,Dist),
    route(Node, NextNode,_), \+ member(NextNode, [Node | Path]),
    NewDistance is Dist + DistanceRev,
    append(Queue, NextNodes, NewQueue),
    bfs(NewQueue, End, FinalPath, NewDistance,FinalDist),
    !
    .
can_be_delivered(Obje, Person):-				% obje gönderiliyorsa gönderen kişiyi dönderir
	object(Obje,_,_,_,_,Person),
	write("Tasıyan kısı --> "), write(Person) ,write("\n"),
	fail.
can_be_delivered(Obje, Person):-				% bu sorgu ile eğer bir obje taşınmıyorsa input olarak gönderilen kişi tarafından gönderip gönderilmeyeceği kontrol ediliyor   
	not(personel(_,_,_,Obje,_)),
	personel(Person,Cap,Sure,Siparis,CurrentLoc),
	not(object(Siparis,_,_,_,_,_)),	
	object(Obje,Agirlik,From,To,_,_),
	breadth_first_search(CurrentLoc,From,Path1, Time1),
	breadth_first_search(From, To,Path2, Time),
	TotalTime is Time1 + Time,
	Cap >= Agirlik,
	Sure >= TotalTime,
	write('\n\n'),write(Person), write(' tasıyabilir \nsüre --> ' ),write(TotalTime), write('\nalırken izlenen yol --> ' ), write(Path1), write('\ntasırken izlenen yol --> ' ), write(Path2), write('\n').

main_q(Obje) :-
    (   personel(Person, _, _, _, _),
        can_be_delivered(Obje, Person),
        fail
    ;   true
    ).
