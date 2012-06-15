#Comando inócuo para o octave não achar que o arquivo é um function script
1;

#Definindo o epsilon utilizado pelo programa
eps = sqrt(eps);

#Responsável por dados os dados de entrada do problema executar o método simplex de
#duas fases e retornar:
# ind = 0 e a solução ótima x do PL
# ind = 1 se a solução for inviável
# ind = -1 se o custo ótimo for -INF.
# Nos casos de ind = 1 ou -1, x será um vetor de zeros com n posições.
#Parâmetros:
# - A: Matriz de coeficientes das restrições
# - b: Vetor de independentes das restrições
# - c: Vetor de custos
# - m: Número de linhas de A
# - n: Número de colunas de A
# - print: true para imprimir as iterações ou false caso contrário.
function [ind x] = simplex(A,b,c,m,n,print)
	x = zeros(n, 1);
	
	##FASE I
	if(print)
		printf("Simplex: Fase 1\n");
	endif
	
	#Passo 1 - Alteramos as restrições para que b >= 0
	for i = 1:m
		if(b(i) < 0)
			A(i, :) = A(i, :) * -1;
			b(i) = -b(i);
		endif
	endfor
	
	#Passo 2 - Montamos o tableau introduzindo as variáveis auxiliares e
	#o vetor de custos do problema auxiliar

	basicas = zeros(1, m)';
	for i = 1:m
		basicas(i) = n + i;
	endfor
	
	T = [-sum(b) -sum(A) zeros(1, m); b A eye(m)];
	
	#Resolvemos o problema auxiliar
	[ind T basicas] = fulltableau(T, m, n + m, basicas, print);
	
	#Passo 3 - Problema auxiliar de custo ótimo > 0. Problema original inviável.
	if(T(1, 1) < 0)
		ind = 1
		
		if(print)
			printf("Problema inviável.\n");
		endif
		return
	endif
	
	#Passo 4 - Removemos as variáveis auxiliares da base
	i = 2;
	while i <= m + 1
		#Se uma variável auxiliar está na base
		if(basicas(i - 1) > n)
			#Verificamos se na linha da variável auxiliar e nas colunas correspondentes
			#às variáveis originais há alguma posição com valor > 0
			j = 2;
			while(j <= n + 1 && T(i, j) == 0)
				j = j + 1;
			endwhile
			
			#Se todas as posições são iguais a zero, removemos a linha
			if(j > n + 1)
				T(i, :) = [];
				basicas(i - 1) = [];
				m = m - 1;
				continue;
			#Senão, pivotamos, fazendo entrar uma variável original no lugar de uma artificial
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
		endif
		
		i = i + 1;
	endwhile
	
	#FASE II
	if(print)
		printf("Simplex: Fase 2\n");
	endif

	#Passo 1 - Reaproveitamos o tableau obtido da fase I para a fase II. Removemos 
	#as variáveis auxiliares.
	T = T(1:m + 1, 1:n + 1);
	
	#Passo 2 - Computamos os custos reduzidos com o vetor de custos original
	T(1, 1) = -c(basicas)' * T(2:m + 1, 1);
	T(1, 2:n + 1) = c' - c(basicas)' * T(2:m+1, 2:n+1);
	
	#Passo 3 - Aplicamos o método simplex ao problema original
	[ind T basicas] = fulltableau(T, m, n, basicas, print);
	
	#Calculamos a resposta final
	for i = 1:m
		x(basicas(i)) = T(i + 1, 1);
	endfor
	
	if(print)
		if(ind == -1)
			printf("Custo ótimo é menos infinito\n");
		else
			printf("Solução ótima encontrada com custo %.3f:\n", -T(1,1));
			x
		endif
	endif
	
endfunction

#Responsável por realizar as iterações do simplex usando tableau dados:
# - T: Tableau precalculado (Vindo de montartableau() por exemplo)
# - m: Número de linhas do tableau menos 1
# - n: Número de colunas do tableau menos 1
# - basicas: Vetor de variáveis básicas. Ex: Se x1, x4 e x2 estão na base 
# nesta ordem, então basicas == [1 4 2]
# - print: true para imprimir as iterações ou false caso contrário.
function [ind T basicas] = fulltableau(T, m, n, basicas, print)
	m = m + 1;
	n = n + 1;
	
	iter = 1;
	while(true)
		#Encontrando variável para entrar da base via regra de Bland
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
		
		#Encontrando a variável para sair da base via regra de Bland.
		iPivo = -1; #Número da linha do pivô no tableau
		tetaPivo = -1; #Valor de teta para o pivô
		indicePivo = -1; #Índice da variável básica correspondente ao pivô
		
		for i = 2:m
			if (T(i, jPivo) <= 0)
				continue;
			endif
			
			cand = T(i, 1) / T(i, jPivo);
			if (iPivo == -1 || cand < tetaPivo || (cand == tetaPivo && basicas(i - 1) < indicePivo))
				tetaPivo = cand;
				indicePivo = basicas(i - 1);
				iPivo = i;
			endif
		endfor

		#Encontramos o pivô caso ele exista. Imprimimos
		if(print)
			imprime(T, m, n, iter, [iPivo jPivo], basicas);
		endif

		#Se não encontramos a linha do pivô, 
		#podemos reduzir o custo indefinidamente.
		if(iPivo == -1)
			ind = -1;
			return;
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


#Responsável por imprimir na saída padrão uma iteração do método simplex segundo
#a especificação do EP. Parâmetros:
# - tableau: O tableau atual da iteração atual
# - m: Quantidade de linhas do tableau
# - n: Quantidade de colunas do tableau
# - iter: Número da iteração atual
# - pivo: Vetor indicando quais as coordenadas no tableau do pivô escolhido
# - basicas: Vetor de variáveis básicas. Ex: Se x1, x4 e x2 estão na base 
# nesta ordem, então basicas == [1 4 2]
#Observaçao: A função considera que o tableau inclui as 0-ésimas linha e coluna
#nessas primeiras.
function imprime(tableau, m, n, iter, pivo, basicas)
	printf("Iteração %d\n", iter);
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
	printf("\n\n");
endfunction

function [comp] = compare(x, y)
	if abs(x - y) < eps
		comp = 0;
	elseif (x > y)
		comp = 1;
	else
		comp = -1;
	endif
endfunction

c = [-10 -12 -12 0 0 0]';
A = [1 2 2 1 0 0;
	 2 1 2 0 1 0;
	 2 2 1 0 0 1];
b = [20 20 20]';

c = [1 1 1 0]';
A = [1 2 3 0;
	 -1 2 6 0;
	 0 4 9 0;
	 0 0 3 1];
b = [3 2 5 1]';

A = [1 2 3 0;
	 -1 1 6 0;
	 1 4 3 0;
	 4 3 3 1];
b = [6 6 8 11]';
c = [1 1 1 5]';

A = [1 2 3 0;
	 -1 1 6 0;
	 1 4 3 0;
	 4 3 3 1];
b = [6 6 8 11]';
c = [1 1 1 5]';

A = [1 2 2 1 0 0;
	 2 1 2 0 1 0;
	 2 2 1 0 0 1];
b = [20 20 20]';
c = [-10 -12 -12 0 0 0]';

A = [1 1 1;
	 2 2 2;
	 3 3 3;
	 4 4 4];
b = [3 6 9 12]';
c = [1 1 1]';

[ind x] = simplex(A,b,c,4,3,true)
