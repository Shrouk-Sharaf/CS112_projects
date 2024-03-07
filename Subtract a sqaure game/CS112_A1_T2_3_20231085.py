# program: the code aims to create an interactive and engaging text-based game where players compete to strategically
#         remove items from a pile, with the ultimate goal of being the player to remove the last item and win the game.
# Author: Shrouk Sayed Ahmed Mohammed
# Version: 1.0
# Function to get a valid integer input from the user
def get_valid_input(o):
    while True:
        try:
            user_input = int(input(o))
            return user_input
        except ValueError:
            print("Please enter a valid integer.")


# Print the game title and options
print("                                                 *** Subtract a square game ***\n")
print("A) Start the game\nB) Check the game instructions")
# Initialize the 'case' variable to True
case = True
score_player_1 = 0  # Player scores initialization
score_player_2 = 0
# Main loop to handle user input
while case:  # Outer loop condition based on 'case'
    # Get user choice
    choice = input()
    # Start the game
    if choice == "a" or choice == "A":
        player_1 = input("Player 1: enter your name ")  # get players' names
        player_2 = input("Player 2: enter your name ")
        while True:
            # Get the initial pile size
            pile = get_valid_input("Enter the number of starting pile\n")
            # Ensure the pile is not a perfect square
            while pile ** 0.5 == int(pile ** 0.5):
                pile = get_valid_input("It's a square number, Enter another one.\n")
            # Game loop for each turn
            while pile > 0:
                print("Current pile =", pile)
                # Player 1's turn
                x = get_valid_input(player_1 + ", Enter your square number.\n")
                # Validate Player 1's input
                while not (1 <= x <= pile and x ** 0.5 == int(x ** 0.5)):
                    x = get_valid_input("Please enter a valid square number.\n")
                # Update the pile after Player 1's move
                pile -= x
                # Check if Player 1 wins
                if pile == 0:
                    print(player_1 + " Wins!!!")
                    score_player_1 += 1
                    print("Scores: " + player_1 + " - " + str(score_player_1) + ", " + player_2 + " - " + str(
                        score_player_2))
                    choice = input("Do you want to start a new game?\nA)Yes\nB)No\n")
                    if choice == "a" or choice == "A":
                        case = True
                        break
                    elif choice == "b" or choice == "B":
                        # Set 'case' to False to terminate the entire game
                        case = False
                        break
                print("Current pile =", pile)
                # Player 2's turn
                y = get_valid_input(player_2 + ", Enter your square number.\n")
                # Validate Player 2's input
                while not (1 <= y <= pile and y ** 0.5 == int(y ** 0.5)):
                    y = get_valid_input("Please enter a valid square number.\n")
                # Update the pile after Player 2's move
                pile -= y
                # Check if Player 2 wins
                if pile == 0:
                    print(player_2 + " Wins!!!")
                    score_player_2 += 1
                    print("Scores: " + player_1 + " - " + str(score_player_1) + ", " + player_2 + " - " + str(
                        score_player_2))
                    # Check whether the user wants to start a new game or not
                    choice = input("Do you want to start a new game?\nA)Yes\nB)No\n")
                    if choice == "a" or choice == "A":
                        case = True
                        break
                    elif choice == "b" or choice == "B":
                        case = False
                        # Set 'case' to False to terminate the entire game
                        break
            if not case:
                break
    # Check the game instructions
    elif choice == "b" or choice == "B":
        print("The instructions are the following:\n1) The Game should be played by 2 players."
              "\n2) First, you have to put a starting value for the pile."
              "\n3) Second, the players take turns removing valid non-zero square numbers from the pile."
              "\n4) The player removing the last coin wins.")
        print("If you want to start playing, Press \"A\".")
        case = True
    # Handle invalid choices
    else:
        print("Please, enter a valid choice.")
        case = True
