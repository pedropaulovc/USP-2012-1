#Comando inócuo para o octave não achar que o arquivo é um function script
1;

function [ind x] = simplex(A,b,c,m,n,print)
	x = zeros(n, 1);
	for i = 1:m
		if(b(i) < 0)
			A(i, :) = A(i, :) * -1;
			b(i) = -b(i);
		endif
	endfor
	A = [A eye(m)];
	custoAux = [zeros(1, n) ones(1, m)]';
	basicas = zeros(1, m);
	for i = 1:m
		basicas(i) = n + i;
	endfor
	
	[ind T basicas] = fulltableau(A, b, custoAux, m, n + m, basicas, print);
	
	#Problema auxiliar de custo ótimo > 0. Problema original inviável.
	if(T(1, 1) < 0)
		ind = 1
		return
	endif
		
	i = 2
	while i <= m + 1
		if(basicas(i - 1) > n)
			j = 2;
			while(j <= n + 1 && T(i, j) == 0)
				j = j + 1;
			endwhile
			
			if(j > n + 1)
				T = [T(1:i - 1, :); T(i + 1:m + 1, :)];
				basicas = [basicas(1:i - 2) basicas(i: m)];
				m = m - 1;
				imprime(T, m + 1, n + m + 1, 0, [-1 -1], basicas);
				continue;
			else
				T(i, :) = T(i, :) / T(i, j);

				for k = 1:m + 1
					if (k == i)
						continue
					endif
					T(k, :) = T(k, :) - T(i, :) * T(k, j);
				endfor

				basicas(i - 1) = j - 1;
			endif
			imprime(T, m + 1, n + m + 1, 0, [-1 -1], basicas);
		endif
		
		i = i + 1;
	endwhile
	
	T = T(1:m + 1, 1:n + 1)
	T(1, 1) = -c(basicas)' * T(2:m + 1, 1)
	T(1, 2:n + 1) = c' - c(basicas)' * T(2:m+1, 2:n+1)
	
	
	
endfunction

function [T] = montartableau(A, b, c, m, n, basicas)
	invB = inv(A(:, basicas))
	sol = invB * b
	cB = c(basicas)
	custo = -cB' * sol
	U = invB * A
	custosRed = c' - cB' * U
	
	m = m + 1;
	n = n + 1;
	T = [custo custosRed; sol U];

endfunction

#Responsável por realizar as iteraćões do simplex usando tableau dados:
# - A: Matriz de coeficientes das restrićões
# - b: Vetor de independentes das restrićões
# - c: Vetor de custos
# - m: Número de linhas de A
# - n: Número de colunas de A
# - basicas: Vetor de variáveis básicas. Ex: Se x1, x4 e x2 estão na base 
# nesta ordem, então basicas == [1 4 2]
# - print: true para imprimir as iteraćões ou false caso contrário.
function [ind T basicas] = fulltableau(A, b, c, m, n, basicas, print)
	invB = inv(A(:, basicas))
	sol = invB * b
	cB = c(basicas)
	custo = -cB' * sol
	U = invB * A
	custosRed = c' - cB' * U
	
	m = m + 1;
	n = n + 1;
	T = [custo custosRed; sol U];
	
	iter = 1;
	while(true)
		#Encontrando coluna para entrar da base
		jPivo = 2;
		while(jPivo <= n && T(1, jPivo) >= 0)
			jPivo = jPivo + 1;
		endwhile
		
		#Todos os custos reduzidos são > 0. Solucão ótima encontrada
		if (jPivo > n)
			ind = 0;
			
			if(print)
				imprime(T, m, n, iter, [-1 -1], basicas);
			endif
			return
		endif
		
		#Quais posićões da j-ésima coluna são positivas
		linhaPivo = [];
		iPivo = -1;
		for i = 2:m
			if (T(i, jPivo) > 0)
				cand = T(i, :) / T(i, jPivo);
				if(length(linhaPivo) == 0)
					linhaPivo = cand;
					iPivo = i;
				elseif(menorlexicografico(cand, linhaPivo))
					linhaPivo = cand;
					iPivo = i;
				endif
			endif
		endfor

		#Podemos reduzir o custo indefinidamente.
		if(iPivo == -1)
			ind = -1;
			return;
		endif

		#Encontramos o pivô. Imprimimos
		if(print)
			imprime(T, m, n, iter, [iPivo jPivo], basicas);
		endif

		#Pivotamos
		T(iPivo, :) = T(iPivo, :) / T(iPivo, jPivo);

		for i = 1:m
			if (i == iPivo)
				continue;
			endif
			T(i, :) = T(i, :) - T(iPivo, :) * T(i, jPivo);
		endfor

		basicas(iPivo - 1) = jPivo - 1;

		iter = iter + 1;
	endwhile
		
endfunction

function [menor] = menorlexicografico(a, b)
	i = 1;
	tam = min(length(a), length(b));
	while(i <= tam && a(i) == b(i))
		i = i + 1;
	endwhile
	
	if (i <= tam)
		menor = a(i) < b(i);
	elseif (length(a) != length(b))
		menor = length(a) < length(b);
	else
		menor = false;
	endif
endfunction

#Responsável por imprimir na saída padrão uma iteraćão do método simplex segundo
#a especificaćão do EP. Parâmetros:
# - tableau: O tableau atual da iteraćão atual
# - m: Quantidade de linhas do tableau
# - n: Quantidade de colunas do tableau
# - iter: Número da iteraćão atual
# - pivo: Vetor indicando quais as coordenadas no tableau do pivô escolhido
# - basicas: Vetor de variáveis básicas. Ex: Se x1, x4 e x2 estão na base 
# nesta ordem, então basicas == [1 4 2]
#Observaćao: A funćão considera que o tableau inclui as 0-ésimas linha e coluna
#nessas primeiras.
function imprime(tableau, m, n, iter, pivo, basicas)
	printf("Iteracao %d\n", iter);
	printf("           |");
	for i =  1:n - 1
		printf(" x%-7d|", i);
	endfor
	printf("\n  ");
	
	for i =  1:n
		printf("%8.3f |", tableau(1, i));
	endfor
	printf("\n------------");
	for i = 1:n - 1
		printf("----------");
	endfor
	for i = 2:m
		printf("\nx%-1d", basicas(i - 1));
		for j = 1:n
			printf("%8.3f", tableau(i, j));
			if (i == pivo(1) & j == pivo(2))
				printf("*|");
			else
				printf(" |");
			endif
		endfor
	endfor
	printf("\n");
endfunction

c = [-10 -12 -12 0 0 0]';
A = [1 2 2 1 0 0;
	 2 1 2 0 1 0;
	 2 2 1 0 0 1];
b = [20 20 20]';

#[ind x] = fulltableau(A, b, c, 3, 6, [4 5 6], false)

c = [1 1 1 0]';
A = [1 2 3 0;
	 -1 2 6 0;
	 0 4 9 0;
	 0 0 3 1];
b = [3 2 5 1]';

[ind x] = simplex(A,b,c,4,4,true)
