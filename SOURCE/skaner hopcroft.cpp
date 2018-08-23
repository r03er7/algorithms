/*
   1993 ACM Finals, Problem H, Scanner
   Ed Karrels, Aug. 1996
*/


#include <stdio.h>

void PrintGrid(int grid[][10]) {
   int i, j;
   for (i=0; i<10; i++) {
      for (j=0; j<15; j++) {
	 putchar(grid[j][i] ? '#' : '.');
      }
      putchar('\n');
   }
   putchar('\n');
}

int Comb(int a[], int n) {
   int i;
   if (n==0) return -1;
   if (a[0]) {
      i = Comb(a+1, n-1);
      if (i==-1) return -1;
      a[0] = 0;
      a[i-1] = 1;
      return i;
   } else {
      for (i=1; i<n && !a[i]; i++);
      if (i==n) {
	 return -1;
      } else {
	 a[i-1] = 1;
	 a[i] = 0;
	 return i;
      }
   }
}

int Check(int sensor[], int grid[15][10], int lvl) {
   int i,j,k,m,c, x, y;
   if (lvl < 14) {

         /* lower left diagonal */
      x = lvl;
      y = 0;
      c = 0;
      while (x>=0 && y<10) {
	 c += grid[x][y];
	 x--; y++;
      }
      if (c != sensor[lvl+10]) return 0;

         /* upper left diagonal */
      x = lvl;
      y = 9;
      c = 0;
      while (x>=0 && y>=0) {
	 c += grid[x][y];
	 x--; y--;
      }
      if (c != sensor[lvl+49]) return 0;

   } else {

      for (i=0; i<10; i++) {
            /* lower left diagonal */
	 x = i+5;
	 y = 9;
	 c = 0;
	 while (x<15 && y>=0) {
	    c += grid[x][y];
	    x++; y--;
	 }
	 if (c != sensor[i+24]) return 0;

            /* upper left diagonal */
	 x = 14;
	 y = 9-i;
	 c = 0;
	 while (x>=0 && y>=0) {
	    c += grid[x][y];
	    x--; y--;
	 }
	 if (c != sensor[i+63]) return 0;

	 c = 0;
	 for (j=0; j<15; j++) {
	    c += grid[j][i];
	 }
	 if (c != sensor[i]) return 0;

      }
   }

   return 1;
}



int Try(int sensor[], int grid[15][10], int lvl) {
   int j;
   if (lvl == 15) return 1;

   for (j=0; j<10; j++) {
      grid[lvl][j] = (j < (10 - sensor[lvl+34]) ? 0 : 1);
   }

/*
   printf("Trying lvl %d\n", lvl);
   PrintGrid(grid);
*/


   do {
      if (Check(sensor, grid, lvl)) {
	 if (Try(sensor, grid, lvl+1)) return 1;
      }
   } while (-1 != Comb(grid[lvl], 10));

   return 0;
}


int main(void) {
   int grid[15][10];
   int i, j;
   char c;
    int n_images, image_no;
    FILE *plik=fopen("skaner.txt","r");

    fscanf(plik, "%d%c", &n_images, &c);
   int sensor[73];


   for (image_no=0; image_no<n_images; image_no++) {

      for (i=0; i<73; i++) {
          fscanf(plik, "%d%c", &sensor[i], &c);
	// scanf("%d", &sensor[i]);
      }

      if (Try(sensor, grid, 0))
	 PrintGrid(grid);

   }


   return 0;
}
