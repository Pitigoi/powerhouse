# powerhouse - Process monitoring consumption energy
David Ioana
Lăscuzeanu Ștefan 
# Overview program
Afiseaza un meniu cu 3 optiuni:
1. Afiseza 50 dintre procesele care consuma cea mai multa energie, cate unul pe linie, in formatul:
	PID, CPU, GPU, MEM, TOTAL, BATTERY% si NAME
	PID - Pid-ul procesului
	CPU - Valoarea in Watts a consumului procesului pe componenta CPU
	GPU - Valoarea in Watts a consumului procesului pe componenta GPU
	MEM - Valoarea in Watts a consumului procesului pe componentele de memorie
	TOTAL - Valoarea in Watts a consumului procesului pe cele 3 componente de mai sus
	BATTERY% - Procentul din baterie pe care il consuma procesul
	NAME - Comanda rulata pentru acest proces
2. Afiseaza informatiile despre un proces cu PID-ul dat, in acelasi format ca mai sus
3. Ieșirea din program