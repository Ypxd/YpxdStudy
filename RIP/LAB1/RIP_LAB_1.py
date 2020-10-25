# Калашников Артем Дмитриевич, ИУ5-53Б, решение биквадратного уравнения

def number(string):
    if string.isdigit():
       return True
    else:
        try:
            float(string)
            return True
        except ValueError:
            return False

print("Калашников Артем Дмитриевич, ИУ5-53Б, решение биквадратного уравнения\n")

print("Введите коэффициенты A, B, C уравнения вида: \
A * x^4 + B * x^2 + C = 0\n")
print("A, B, C - числа типа flost.\n")
Aper = input("A = ")
while number(Aper) != True:
    print("Введено не верное значение.")
    Aper = input("A = ")
    
Bper = input("B = ")
while number(Bper) != True:
    print("Введено не верное значение.")
    Bper = input("B = ")
    
Cper = input("C = ")
while number(Cper) != True:
    print("Введено не верное значение.")
    Cper = input("C = ")
    
Aper = float(Aper)
Bper = float(Bper)
Cper = float(Cper)

D = pow(Bper, 2) -(4 * Aper * Cper)
print()
print(D)

if Aper == 0:
    if Bper == 0:
        if Cper == 0:
            print("x может принять любое значение.\n")
        else:
            print("Нет решений.\n")
    else:
        x = -Cper / Bper
        if x < 0:
            print("Нет решений.\n")
        else:
            print("x = +-%.4f" % pow(x, 1/2))
else:
    if Bper == 0:
        x = -Cper / Aper
        if x < 0:
            print("Нет решений.\n")
        else:
            print("x = +-%.4f" % pow(x, 1/4))
    else:
        if D < 0:
            print("Нет решений.\n")
        else:
            FD = ((-Bper + pow(D, 1/2)) / (2 * Aper))
            print(FD)
            SD = ((-Bper - pow(D, 1/2)) / (2 * Aper))
            print(SD)
            if FD > 0 or SD > 0:
                if FD > 0:
                    print("x1 = +%.4f" % pow(FD, 1/2))
                    print("x2 = -%.4f" % pow(FD, 1/2))
                if SD > 0:
                    print("x3 = +%.4f" % pow(SD, 1/2))
                    print("x4 = -%.4f" % pow(SD, 1/2))
            else:
                print("Нет решений.\n")
            
                    
                
        
