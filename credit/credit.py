import cs50
import sys


def main():
    # prompt for input
    number = cs50.get_int("Number: ")
    num_str = str(number)

    # check length
    length = len(num_str)

    if length < 13 or length >= 17:
        print("INVALID")
        sys.exit(0)

    num_list = []
    for num_char in num_str:
        num_list.append(int(num_char))

    # calc checksum
    # multiply every other digit by 2 starting with second to last digit
    # add those product digits together
    # add the sum to the sum of the digits that weren't multiplied by 2
    # if total's last digit is 0, number is valid

    sum = 0
    # drop last digit
    cropped_list = num_list[0:-1]
    # get every other digit starting from end
    cropped_list.reverse()
    new_list = cropped_list[0::2]
    for num in new_list:
        # multiply num by 2
        product = num * 2
        prod_str = str(product)

        # get product's digits
        digit1 = prod_str[0]
        digit2 = prod_str[1] if len(prod_str) > 1 else "0"

        # add digits to firstSum
        sum += int(digit1) + int(digit2)

    # get numbers from digits that weren't manipulated and add to sum
    num_list.reverse()
    untouched_list = num_list[0::2]
    for num in untouched_list:
        sum += num

    str_sum = str(sum)
    if str_sum[-1] != "0":
        print("INVALID")
        sys.exit(0)

    # get first and first 2 digits of number
    first_one = num_str[0]
    first_two = num_str[0:2]

    5673598276138003
    # check length & starting digits for matching card type
    # Print: AMEX, MASTERCARD, VISA, or INVALID
    if (first_two == "34" or first_two == "37") and (length >= 15 and length < 16):
        print("AMEX")
    elif (first_two >= "51" and first_two <= "55") and (length >= 16 and length < 17):
        print("MASTERCARD")
    elif (first_one == "4") and ((length >= 13 and length < 14) or (length >= 16 and length < 17)):
        print("VISA")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()
