/* 8 Queens Chess Problem */ 
// it is ok to use global variables in competitive programming
int x[9], TC, a, b, lineCounter;

bool place(int queen, int row) 
{ 
	// check previously placed queens 
	for (int prev = 1; prev <= queen - 1; prev++)
		// an infeasible solution if share same row or same diagonal
		if (x[prev] == row || (abs(x[prev] - row) == abs(prev - queen)))
			return false; 
	return true;
}
void NQueens(int queen) 
{ 
	for (int row = 1; row <= 8; row++) 
		// if can place this queen at this row? 
		if (place(queen, row)) { 
			// put this queen in this row 
			x[queen] = row; 
		// a candidate solution & (a, b) has 1 queen 
		if (queen == 8 && x[b] == a) { 
			printf("%2d %d", ++lineCounter, x[1]); 
			for (int j = 2; j <= 8; j++) printf(" %d", x[j]); 
			printf("\n"); 
		} 
		else NQueens(queen + 1); // recursively try next position }
	}
}
int main() 
{ 
	scanf("%d", &TC); 
	while (TC--) 
	{ 
		scanf("%d %d", &a, &b); 
		memset(x, 0, sizeof x); 
		lineCounter = 0; 
		printf("SOLN COLUMN\n"); 
		printf(" # 1 2 3 4 5 6 7 8\n\n"); 
		NQueens(1); // generate all possible 8! candidate solutions 
		if (TC) printf("\n"); 
	} 
	return 0; 
}
