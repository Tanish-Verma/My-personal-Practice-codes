def compare_strings(str1, str2):
    """
    Compares two strings and returns True if they are equal, otherwise False.
    """
    return str1 == str2

# Example usage
if __name__ == "__main__":
    string1 = input("Enter the first string: ")
    string2 = input("Enter the second string: ")

    if compare_strings(string1, string2):
        print("The strings are equal.")
    else:
        print("The strings are not equal.")
