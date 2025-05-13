import pandas as pd
import numpy as np

dict1 ={
    "name": ["harry", "john","cart","nord"],
    "age": [25, 30, 35, 40],
    "city": ["new york", "chicago", "los angeles", "miami"],
    "country": ["usa", "usa", "usa", "usa"],
    "salary":[30,40,20,11]
}
df=pd.DataFrame(dict1)
df.loc[len(df)]=["dev",18,"Hyderabad","India",0.001]
df.index=['first','second','third','fourth','fifth']
print(df)
df.to_csv('students.csv')
# print(df.describe())
companies=pd.read_excel('companiesunicorn.xlsx')
# print(companies)
# print(companies.loc[5,'COMPANIES'])
# companies.loc[5,'COMPANIES']='Zomato(food delivery)'
# print(companies.loc[5,'COMPANIES'])