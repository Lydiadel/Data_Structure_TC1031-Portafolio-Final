bool isPalindrome(int x) {
  if (x < 0){
    return false;
  }
  double inverted = 0;
  int base = x;
  while(base != 0) {
    inverted *= 10;
    inverted += base%10;
    base = base/10;
  }
  return x == inverted;
}
