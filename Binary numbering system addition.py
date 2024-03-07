def bin_add(num1, num2):
    res = ""
    ov_flow = 0
    while len(num1) < len(num2):
        num1 = "0" + num1
    while len(num1) > len(num2):
        num2 = "0" + num2
    for i in range(len(num1) - 1, -1, -1):
        for i in range(len(num2) - 1, -1, -1):
            x = int(num1[i])
            y = int(num2[i])
            sum = x + y + ov_flow
            res = str(sum % 2) + res
            ov_flow = sum // 2
        if ov_flow > 0:
            res = "1" + res
        return res


number1 = input()
number2 = input()
print(bin_add(number1, number2))