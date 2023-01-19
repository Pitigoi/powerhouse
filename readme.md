# powerhouse - Process monitoring consumption energy
David Ioana & Lăscuzeanu Ștefan 
# Overview program
Afiseaza un meniu cu 3 optiuni:
1. Afiseza 50 dintre procesele care consuma cea mai multa energie, cate unul pe linie, in formatul:<br>
	PID, CPU, GPU, MEM, TOTAL, BATTERY% si NAME<br>
	PID - Pid-ul procesului<br>
	CPU - Valoarea in Watts a consumului procesului pe componenta CPU<br>
	GPU - Valoarea in Watts a consumului procesului pe componenta GPU<br>
	MEM - Valoarea in Watts a consumului procesului pe componentele de memorie<br>
	TOTAL - Valoarea in Watts a consumului procesului pe cele 3 componente de mai sus<br>
	BATTERY% - Procentul din baterie pe care il consuma procesul<br>
	NAME - Comanda rulata pentru acest proces<br>
2. Afiseaza informatiile despre un proces cu PID-ul dat, in acelasi format ca mai sus
3. Ieșirea din program


//Impartirea codului:
Ioana: Battery, GPU, main + functii adaugate in celelalte clase marcate intre //Ioana code // (logica componentelor si proceselor in relatie cu bateria + logica GPU)

Stefan: cpu, mem, proc, procman, hwman (logica proceselor in relatie cu componentele + logica CPU si MEM)
