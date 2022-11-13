def main():
    # loop prompt until input between 1 and 8 inclusive
    height = get_height()

    # for each row
    hashes = 1
    spaces = height - 1

    for i in range(height):
        # print # of spaces before the left pyramid
        print_space(spaces)
        # print # of hashes representing the left pyramid
        print_hash(hashes)
        # print 2 spaces
        print("  ", end="")
        # print # of hashes representing right pyramid
        print_hash(hashes)
        hashes += 1
        spaces -= 1
        print()


def get_height():
    h = -1
    while h < 1 or h > 8:
        try:
            h = int(input("Height:\n"))
        except ValueError:
            h = int(input("Height:\n"))

    return h


def print_hash(n):
    # function for number of times to print #
    for i in range(n):
        print("#", end="")


def print_space(n):
    # function for number of times to print blank space
    for i in range(n):
        print(" ", end="")


if __name__ == "__main__":
    main()
