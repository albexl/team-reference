//Hanoi Towers

void move( int n, char from, char to, char aux ) {

  if ( n == 1 )
       printf( "Move disk from %c to %c\n", from, to );
  else {
    move( n - 1, from, aux, to );
    printf( "Move disk from %c to %c\n", from, to );
    move( n - 1, aux, to, from );
  }
}