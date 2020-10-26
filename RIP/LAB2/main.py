#Калашников А. Д. ИУ-5 53Б ЛАБ2

from lab_python_oop.rectangle import Rectangle
from lab_python_oop.circle import Circle
from lab_python_oop.square import Square
from tkinter import*
import pickle



def main():
    starts = True
    getch = ''
    while starts:
        r = Rectangle("Желтый", 22, 22)
        c = Circle("Зеленый", 7)
        s = Square("Синий", 77)
        print('MENU:')
        putch = input('1 - вывести задание.\n'+
                      '2 - протестировать подключенную библиотеку(Tkinter).\n'+
                      '3 - выйти.'+
                      '\n'+
                      '\n')
        putch = int(putch)
        print()
        if putch == 3:
            starts = False
        elif putch == 1:
            print(r)
            print(c)
            print(s)
            a = str(r)
            print('')
        elif putch == 2:
            root = Tk()
            root.title('Проверка')
            root.minsize(800,600)
            root.configure(background='#ffffff')
            L = Label(root,bg='#ffffff',font=('Arial Black',22),text='Tkinter: провека.')
            L.place(x=22,y=0)
            root.mainloop()
        

if __name__ == "__main__":
    main()



