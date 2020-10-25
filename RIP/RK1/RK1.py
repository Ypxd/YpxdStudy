#Калашников Артем ИУ5 53б РК1
# используется для сортировки
from operator import itemgetter

class Computer:

    def __init__(self, id, name):
        self.id = id
        self.name = name

class Programm:

    def __init__(self, id, name,size, id_of_computer):
        self.id = id
        self.name = name
        self.size = size
        self.comp_id = id_of_computer

class Programm_Computer:
    
    def __init__(self, id_of_computer, id_of_Programm):
        self.id_of_computer = id_of_computer
        self.id_of_Programm = id_of_Programm

Computer = [
    Computer(1, 'Первый компьтер'),
    Computer(2, 'Второй компьютер'),
    Computer(3, 'Третий компьютер'),


    Computer(11, 'Четвертый компьютер'),
    Computer(22, 'Пятый компьютер'),
    Computer(33, 'Шестой компьютер')
]

Programm = [
    Programm(1,'MS Office Word',  2200, 1),
    Programm(2,'Visual studio', 2500, 3),
    Programm(3,'MS Office Power Point', 2200, 3),
    Programm(4,'Pycharm', 5000, 2),
    Programm(5,'Blender', 8000, 3)
]

Programm_Computer = [
    Programm_Computer(1,1),
    Programm_Computer(2,2),
    Programm_Computer(3,3),
    Programm_Computer(3,4),
    Programm_Computer(5,5),

    

    Programm_Computer(11,1),
    Programm_Computer(22,2),
    Programm_Computer(33,3),
    Programm_Computer(33,4),
    Programm_Computer(33,5)
]

def main():
    

    
    one_to_many = [( b.name, b.size, a.name) 
        for a in Computer 
        for b in Programm 
        if b.comp_id == a.id]
    
    # Соединение данных многие-ко-многим
    many_to_many_temp = [(c.name, d.id_of_computer, d.id_of_Programm) 
        for c in Computer 
        for d in Programm_Computer 
        if c.id == d.id_of_computer]
    
    many_to_many = [(b.name, b.size, name_of_computer) 
        for name_of_computer, id_of_computer, id_of_Programm in many_to_many_temp
        for b in Programm if b.id== id_of_Programm]

    print('Задание В1')
    first_res = {} 

    for l in Programm:
        if 'M' == l.name[0]:
            programm = list((filter(lambda i: i[0] == l.name, one_to_many)))
            l_comp_names = [f[2] for f in programm]
            first_res[l.name] = l_comp_names

    print(first_res)
    
    
    
    print('\nЗадание B2')
    second_res_unsort = []
    
    for d in Computer:
        
        programm = list(filter(lambda i: i[2]==d.name, one_to_many))
         
        if len(programm) > 0:
            second_res_unsort.append((d.name, min([a[1] for a in programm])))
    second_res = sorted(second_res_unsort, key=itemgetter(1))
    print(second_res)

    print('\nЗадание B3')
    third_res = sorted(many_to_many, key=itemgetter(0))
    print(third_res)


if __name__ == '__main__':
    main()
