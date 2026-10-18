int calculate(int num1, char symvol, int num2) {
  if (symvol == '+')
    return num1 + num2;
  if (symvol == '-')
    return num1 - num2;
  if (symvol == '*')
    return num1 * num2;
  if (symvol == '/') {
    if (num2 == 0)
      return 0;
    return num1 / num2;
  }
  return 0;
}
