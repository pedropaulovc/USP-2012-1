#Comando inócuo para o octave não achar que o arquivo é um function script
1;

#[ind x] = simplex(A,b,c,m,n,print)

#TODO: Controlar erros de arredondamento
#Responsável por realizar as iteraćões do simplex usando tableau dados:
# - A: Matriz de coeficientes das restrićões
# - b: Vetor de independentes das restrićões
# - c: Vetor de custos
# - m: Número de linhas de A
# - n: Número de colunas de A
# - basicas: Vetor de variáveis básicas. Ex: Se x1, x4 e x2 estão na base 
# nesta ordem, então basicas == [1 4 2]
# - print: true para imprimir as iteraćões ou false caso contrário.
function [ind x] = fulltableau(A, b, c, m, n, basicas, print)
	eps = 0.0005
	invB = inv(A(:, basicas))
	sol = invB * b
	cB = c(basicas)
	custo = -cB' * sol
	U = invB * A
	custosRed = c' - cB' * U
	
	m = m + 1
	n = n + 1
	T = [custo custosRed; sol U]
	x = zeros(n - 1, 1)
	
	iter = 1
	while(true)
		#Encontrando coluna para entrar da base
		jPivo = 2
		while(jPivo <= n && T(1, jPivo) > -eps)
			jPivo = jPivo + 1
		endwhile
		
		#Todos os custos reduzidos são > 0. Solucão ótima encontrada
		if (jPivo > n)
			ind = 0
			for i = 2:m
				x(basicas(i - 1)) = T(i, 1)
			endfor

			imprime(T, m, n, iter, [-1 -1], basicas)
			return
		endif
		
		#Quais posićões da j-ésima coluna são positivas
		linhaPivo = []
		iPivo = -1
		for i = 2:m
			if (T(i, jPivo) > 0)
				cand = T(i, :) / T(i, jPivo)
				if(length(linhaPivo) == 0)
					linhaPivo = cand
					iPivo = i
				elseif(menorlexicografico(cand, linhaPivo))
					linhaPivo = cand
					iPivo = i
				endif
			endif
		endfor

		#Podemos reduzir o custo indefinidamente.
		if(iPivo == -1)
			ind = -1
			return
		endif

		#Encontramos o pivô. Imprimimos
		imprime(T, m, n, iter, [iPivo jPivo], basicas)

		#Pivotamos
		T(iPivo, :) = T(iPivo, :) / T(iPivo, jPivo)

		for i = 1:m
			if (i == iPivo)
				continue
			endif
			T(i, :) = T(i, :) - T(iPivo, :) * T(i, jPivo)
		endfor

		basicas(iPivo - 1) = jPivo - 1

		iter = iter + 1
	endwhile
		
endfunction

function [menor] = menorlexicografico(a, b)
	i = 1
	tam = min(length(a), length(b))
	while(i <= tam && a(i) == b(i))
		i = i + 1
	endwhile
	
	if (i <= tam)
		menor = a(i) < b(i)
	elseif (length(a) != length(b))
		menor = length(a) < length(b)
	else
		menor = false
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
	printf("Iteração %d\n", iter)
	printf("           |")
	for i =  1:n - 1
		printf(" x%-7d|", i)
	endfor
	printf("\n  ");
	
	for i =  1:n
		printf("%8.3f |", tableau(1, i))
	endfor
	printf("\n------------")
	for i = 1:n - 1
		printf("----------")
	endfor
	for i = 2:m
		printf("\nx%-1d", basicas(i - 1))
		for j = 1:n
			printf("%8.3f", tableau(i, j))
			if (i == pivo(1) & j == pivo(2))
				printf("*|")
			else
				printf(" |")
			endif
		endfor
	endfor
	printf("\n")
endfunction

c = [-10 -12 -12 0 0 0]'
A = [1 2 2 1 0 0;
	 2 1 2 0 1 0;
	 2 2 1 0 0 1]
b = [20 20 20]'

[ind x] = fulltableau(A, b, c, 3, 6, [4 5 6], false)
