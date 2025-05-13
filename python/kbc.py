import random
import time 

questions_tier1=['''What is the capital of India
A.Mumbai
B.Delhi
C.Kolkata
D.Chennai''',
'''Which planet is known as the Red Planet?
A.Mars
B.Venus
C.Jupiter
D.Saturn''',
'''Who is the author of the Harry Potter series?
A.Stephen King
B.George R.R.Martin
C.J.K.Rowling
D.Dan Brown''',
'''What is the chemical symbol for water?
A.CH4
B.H2O
C.CO2
D.D2O''',
'''which animal is known as the 'King of the Jungle'?
A.Tiger
B.Elephant
C.Lion
D.Giraffe''',                                                   
'''What is the tallest mountain in the world?
A.Mount Everest
B.Himalaya
C.Kilimanjaro
D.Alps''',
'''Who is known as the Father of the Nation in India?
A.Geoge Washington
B.Narendra Modi
C.Nelson Mandela
D.Mahatma Gandhi''',
'''Which sport is known as the "Gentleman's Game"?
A.Cricket
B.Football
C.Tennis
D.Basketball''',
'''What is the national currency of Japan?
A.Rupees
B.Dollars
C.Yen
D.Euro''',
'''In which continent is the Sahara Desert located?
A.Asia
B.Europe
C.North America
D.Africa''']
answers_tier1=['B','A','C','B','C','A','D','A','C','D']
qa_list_tier1_dict=[{"question": q, "answer": a} for q, a in zip(questions_tier1, answers_tier1)]

questions_tier2 = [
    '''Which Mughal emperor built the Taj Mahal?
    A. Akbar
    B. Jahangir
    C. Shah Jahan
    D. Aurangzeb''',

    '''Who wrote the Indian national anthem?
    A. Bankim Chandra Chatterjee
    B. Rabindranath Tagore
    C. Sarojini Naidu
    D. Mahatma Gandhi''',

    '''Which planet is known as the Earth's twin?
    A. Mars
    B. Venus
    C. Jupiter
    D. Saturn''',

    '''Who was the first woman to win a Nobel Prize?
    A. Marie Curie
    B. Mother Teresa
    C. Jane Addams
    D. Irène Joliot-Curie''',

    '''Which element is said to keep bones strong?
    A. Iron
    B. Calcium
    C. Magnesium
    D. Zinc''',

    '''Who was the first President of India?
    A. Dr. Rajendra Prasad
    B. Dr. S. Radhakrishnan
    C. Dr. Zakir Hussain
    D. Dr. V. V. Giri''',

    '''Which Indian classical dance form originated in Tamil Nadu?
    A. Kathakali
    B. Bharatanatyam
    C. Kuchipudi
    D. Odissi''',

    '''What is the smallest country in the world?
    A. Monaco
    B. San Marino
    C. Liechtenstein
    D. Vatican City''',

    '''In which year did India gain independence from British rule?
    A. 1945
    B. 1947
    C. 1950
    D. 1952''',

    '''Which Indian scientist is known as the Missile Man of India?
    A. Vikram Sarabhai
    B. Homi J. Bhabha
    C. A.P.J. Abdul Kalam
    D. C.V. Raman'''
]

answers_tier2 = ['C', 'B', 'B', 'A', 'B', 'A', 'B', 'D', 'B', 'C']

qa_list_tier2_dict = [{"question": q, "answer": a} for q, a in zip(questions_tier2, answers_tier2)]

questions_tier3 = [
    '''Who among the following was a co-founder of the 'Swaraj Party'?
    A. Motilal Nehru
    B. Lala Lajpat Rai
    C. Subhas Chandra Bose
    D. Mahatma Gandhi''',

    '''Which city is known as the "Silicon Valley of India"?
    A. Hyderabad
    B. Chennai
    C. Mumbai
    D. Bengaluru''',

    '''Which Veda is a collection of spells and incantations?
    A. Rigveda
    B. Samaveda
    C. Atharvaveda
    D. Yajurveda''',

    '''Who composed the classical composition "Vande Mataram"?
    A. Bankim Chandra Chatterjee
    B. Rabindranath Tagore
    C. Swami Vivekananda
    D. Sarojini Naidu''',

    '''Which Indian state has the longest coastline?
    A. Maharashtra
    B. Gujarat
    C. Tamil Nadu
    D. Andhra Pradesh''',

    '''Who is the author of the book "The Argumentative Indian"?
    A. V.S. Naipaul
    B. Arundhati Roy
    C. Amartya Sen
    D. Salman Rushdie''',

    '''What is the name of India's first satellite?
    A. Aryabhata
    B. Bhaskara
    C. Rohini
    D. INSAT-1A''',

    '''Which organ in the human body is responsible for the production of insulin?
    A. Liver
    B. Pancreas
    C. Kidney
    D. Spleen''',

    '''Which battle marked the beginning of the Mughal Empire in India?
    A. Battle of Plassey
    B. First Battle of Panipat
    C. Battle of Haldighati
    D. Battle of Talikota''',

    '''Who was the first Indian woman to win an Olympic medal?
    A. P.T. Usha
    B. Mary Kom
    C. Karnam Malleswari
    D. Saina Nehwal'''
]

answers_tier3 = ['A', 'D', 'C', 'A', 'B', 'C', 'A', 'B', 'B', 'C']

qa_list_tier3_dict = [{"question": q, "answer": a} for q, a in zip(questions_tier3, answers_tier3)]

questions_tier4 = [
    '''Who was the first person to win two Nobel Prizes?
    A. Albert Einstein
    B. Linus Pauling
    C. Marie Curie
    D. Frederick Sanger''',

    '''Which of these ancient texts is written in Sanskrit?
    A. Quran
    B. Bible
    C. Torah
    D. Rigveda''',

    '''Which Indian mathematician is known for his contributions to number theory and mathematical analysis?
    A. C.R. Rao
    B. S. Ramanujan
    C. Harish-Chandra
    D. D.R. Kaprekar''',

    '''In which year did the Battle of Plassey take place?
    A. 1757
    B. 1764
    C. 1775
    D. 1781''',

    '''Who was the first Chief Justice of India?
    A. H.J. Kania
    B. M. Patanjali Sastri
    C. Mehr Chand Mahajan
    D. Sudhi Ranjan Das'''
]

answers_tier4 = ['C', 'D', 'B', 'A', 'A']


qa_list_tier4_dict = [{"question": q, "answer": a} for q, a in zip(questions_tier4, answers_tier4)]
def kbc_game():
    print("Welcome to Kaun Banega Crorepati!")
    print("You will be asked a series of questions. Answer them correctly to win the game.")
    print("To exit with the money type 'exit'")
    print("Let's begin!")


amount=[1000,2000,3000,5000,10000,20000,40000,80000,160000,320000,640000,1250000,2500000,5000000,10000000,70000000]
def ask_random_question(qa_list):
    # Select a random question-answer pair
    qa = random.choice(qa_list)
    question=qa["question"]
    answer=qa["answer"]
    qa_list.remove(qa)
    print(question)
    time.sleep(3)
    Milestone1=10000
    Milestone2=320000
    Milestone3=10000000
    initial_amount=0
    final_amount=70000000
    current_amount=0
   

    # Get the user's answer
    user_answer = input("Your answer: ")
    for i in amount:
       
        if user_answer.strip().upper() == answer:
            print("Correct!")
            print(f"Congratulations your current reward is : Rupees {i}")
            current_amount=i
            amount.remove(i)
            if i in (Milestone1, Milestone2, Milestone3,final_amount):
                print("Congratulations!!You have reached the milestone")
                initial_amount=i
                if i==Milestone1:
                    print("You have reached the milestone of Rupees 10000")
                if i==Milestone2:
                    print("You have reached the milestone of Rupees 320000")
                if i==Milestone3:
                    print("You have reached the milestone of Rupees 10000000")
                if i==final_amount:
                    print(f"Congratulations!!You have reached the final milestone of Rupees {final_amount}")
                    print("You have won the game!")
                    print("Thank you for playing KBC")
                
            
            time.sleep(2)
            break

        elif user_answer.strip().lower()=="exit":
            print("You have exited the game")
            
            print(f"Congratulations your current reward is : Rupees {current_amount}")
            print("Thank you for playing Kaun Banega Crorepati!")
            quit()
        else:
            print(f"Wrong! The correct answer is {qa['answer']}.")
            print("You have lost the game")
            print("You shall recieved the amount depending upon your milestone")
            print("You shall recieve the amount of Rupees",initial_amount)
            print("Thank you for playing Kaun Banega Crorepati!")
            quit()
            
            
        
           
kbc_game()
time.sleep(2)
print("Tier 1")
time.sleep(1)

(ask_random_question(qa_list_tier1_dict))
(ask_random_question(qa_list_tier1_dict))
(ask_random_question(qa_list_tier1_dict))
(ask_random_question(qa_list_tier1_dict))
(ask_random_question(qa_list_tier1_dict))

print("End of tier1")

time.sleep(2)

print("Tier 2")
time.sleep(2)

(ask_random_question(qa_list_tier2_dict))
(ask_random_question(qa_list_tier2_dict))
(ask_random_question(qa_list_tier2_dict))
(ask_random_question(qa_list_tier2_dict))
(ask_random_question(qa_list_tier2_dict))

print("End of tier2")
time.sleep(2)

print("Tier 3")

time.sleep(2)

(ask_random_question(qa_list_tier3_dict))
(ask_random_question(qa_list_tier3_dict))
(ask_random_question(qa_list_tier3_dict))
(ask_random_question(qa_list_tier3_dict))
(ask_random_question(qa_list_tier3_dict))

print("End of tier3")
time.sleep(2)

print('''Welcome to the final round
This is the moment you have been waiting for
the 70000000 rupees question. ''')
time.sleep(2)
(ask_random_question(qa_list_tier4_dict))
