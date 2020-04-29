from cs50 import get_float
import math



# cash = get_float("Change owed: ")
# while cash <0:
#     cash = get_float("Change owed: ")
# print(f"Sis owes you ${cash}.")

# cash=cash*100
# coins = [25,10,5,1]
# owed = 0

# for i in range (len(coins)):
#     owed += math.floor(cash/coins[i])
#     cash = cash % coins[i]

# print(f"Sis gives you {owed} coins")

#### pjerdove blabla
cash = -1
while cash <0:
    cash = get_float("Change owed: ")
print(f"Sis owes you ${cash}.")

cash=cash*100
coins = [25,10,5,1]
owed = 0

for coin in coins:
    owed += math.floor(cash/coin)
    cash = cash % coin


print(f"Sis gives you {owed} coins")



