#One method is to replace every character with another by using replace. It is very long.
#Another method is to use a for loop to iterate through the string and replace each character with a character pushed forward by the key.It is a good method 
#The third method is to use the ord() and chr() functions to convert the characters and then reversing the order.Best method so far.


#method 2

import string

# Extended alphabet list to include all printable characters
alphabets = list(string.ascii_letters + string.digits + string.punctuation + ' ')

def encrypt(text,shift):
  cipher_text=""
  for letter in text:
    position=alphabets.index(letter)
    new_position=position+shift
    new_letter=alphabets[new_position]
    cipher_text+=new_letter
  print(f"The encoded text is {cipher_text}")

def decrypt(text,shift):
  cipher_text=""
  for letter in text:
    position=alphabets.index(letter)
    new_position=position-shift
    new_letter=alphabets[new_position]
    cipher_text+=new_letter
  print(f"The decoded text is {cipher_text}")


#method 3 


def encryption(text):
  encrypt=[ord(i) for word in text for i in word]
  encrypt.reverse()
  encrypt=[i+7 for i in encrypt]
  decrypt="".join([chr(i) for i in encrypt])
  print(f"The encrypted text is {decrypt}")


def decryption(text):
  decrypt=[ord(i) for word in text for i in word]
  decrypt.reverse()
  decrypt=[i-7 for i in decrypt]
  decrypt = "".join([chr(int(round(i))) for i in decrypt])
  print(f"The decrypted text is {decrypt}")

#finishing the code 

def secret_code():
  while True:
  
    direction=input("Type 'encode' to encrypt using cipher, 'decode' to decrypt using cipher\n"
      "or type 'encryption' to encrypt using ord() and 'decryption' to decrypt using ord()\n"
      "and type 'exit' to exit the program\n").lower()
  
    
  
    
    if direction.lower()== "encode":
      text=input("Type your message to encrypt:\n")
      shift=int(input("Type the shift number:\n"))
      encrypt(text,shift)
  
    
    elif direction.lower()=="decode":
      text=input("Type the encrypted  message:\n")
      shift=int(input("Type the shift number:\n"))
      decrypt(text,shift)
  
    
    elif direction.lower()=="encryption":
      text=input("Type your message to encrypt:\n")
      encryption(text)
  
    
    elif direction.lower()=="decryption":
      text=input("Type your encrypted message:\n")
      decryption(text)
  
  
    elif direction.lower()=="exit":
      print("Thank you for using the program")
      return True
      quit()


secret_code()




