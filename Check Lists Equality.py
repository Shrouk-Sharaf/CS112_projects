# Author: Shrouk Sayed Ahmed Mohammed

# Make a function to check if the entered lists are equal
def check_equality():
    # Get the two lists from the user
    lst_1 = input("Please enter list 1: ")
    lst_2 = input("Please enter list 2: ")

    # Check if the lengths are the same
    if len(lst_1) != len(lst_2):
        return "Lists are not equal"

    # set a dictionary for repeated digits in list 1
    repeated = {}
    # iterate through each digit in list 1
    for i in lst_1:
        # if the digit already exists, we add the 1 to the count
        if i in repeated:
            repeated[i] += 1
        # if the digit doesn't exist, we add the digit and set its count to 1
        else:
            repeated[i] = 1

    # Subtract repeated digit in list2
    # If any count becomes negative or if a digit is missing, return "Lists are not equal"
    for i in lst_2:
        exist = False
        for digit in repeated:
            if digit == i and repeated[digit] > 0:
                repeated[digit] -= 1
                exist = True
                break
        if not exist:
            return "Lists are not equal"
    return "Lists are equal"


print(check_equality())
