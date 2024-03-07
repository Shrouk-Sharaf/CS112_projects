def bin_sub(num1, num2):
    res = ""
    borrow = 0
    while len(num1) < len(num2):
        num1 = "0" + num1
    while len(num1) > len(num2):
        num2 = "0" + num2
    for i in range(len(num1) - 1, -1, -1):
        for i in range(len(num2) - 1, -1, -1):
            x = int(num1[i])
            y = int(num2[i])
            sub = x - y - borrow
            res = str((sub + 2) % 2) + res
            if sub < 0:
                borrow = 1
            else:
                borrow = 0

            return res


number1 = input()
number2 = input()
print(bin_sub(number1, number2))
