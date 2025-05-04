#from PyQt5.QtWidgets import QApplication, QPushButton, QMainWindow
#from PyQt5.QtGui import QPainter, QFont, QBrush, QPen
#from PyQt5.QtCore import QRect

from PyQt5.QtCore import * 
from PyQt5.QtGui import * 
from PyQt5.QtWidgets import *

import sys


class MyWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setGeometry(200,200,1100,600)
        self.setWindowTitle("Supervisório Sinaleira")
        self.meuBotao = QPushButton("teste", self)
        self.meuBotao.clicked.connect(self.redesenhaTudo)
        #TODOS OS SINAIS
        self.s1vermelho  = 0
        self.s1amarelo   = 0
        self.s1verde     = 0

        self.s2vermelho  = 1
        self.s2amarelo   = 0
        self.s2verde     = 0

        self.s3vermelho  = 0
        self.s3amarelo   = 0
        self.s3verde     = 0

        self.s4vermelho  = 0
        self.s4amarelo   = 0
        self.s4verde     = 0

        self.s5vermelho  = 0
        self.s5amarelo   = 1
        self.s5verde     = 1

    def redesenhaTudo(self):
        #self.meuX = self.meuX + 37    #teste... muda a posicao da sinaleira
        self.s2vermelho = 0
        self.s1amarelo = 1
        self.repaint()


    def paintEvent(self, paintEvent):
        self.painter = QPainter(self)
        self.desenhaUmaSinaleira(self.painter, 150, 100, self.s1vermelho, self.s1amarelo, self.s1verde)
        self.desenhaUmaSinaleira(self.painter, 325, 100, self.s2vermelho, self.s2amarelo, self.s2verde)
        self.desenhaUmaSinaleira(self.painter, 500, 100, self.s3vermelho, self.s3amarelo, self.s3verde)
        self.desenhaUmaSinaleira(self.painter, 675, 100, self.s4vermelho, self.s4amarelo, self.s4verde)
        self.desenhaUmaSinaleira(self.painter, 850, 100, self.s5vermelho, self.s5amarelo, self.s5verde)
        #print("REDESENHANDO")
        self.painter.end()


    def desenhaUmaSinaleira(self, painter, x, y, vermelho, amarelo, verde):

        self.painter.setFont(QFont("Arial", 30))

        self.myBrush = QBrush()
        self.minhaPen = QPen(Qt.black, 2)
        self.painter.setBrush(self.myBrush)
        self.painter.setPen(self.minhaPen)
        self.painter.drawRect(x,y,100,350)

        if (vermelho == 1): self.myBrush = QBrush(Qt.red)
        else: self.myBrush = QBrush()
        self.minhaPen = QPen(Qt.red, 5)
        self.painter.setBrush(self.myBrush)
        self.painter.setPen(self.minhaPen)
        self.painter.drawEllipse(QPoint(x+50,y+50), 50, 50)

        if (amarelo == 1): self.myBrush = QBrush(Qt.yellow)
        else: self.myBrush = QBrush()
        self.minhaPen = QPen(Qt.yellow, 5)
        self.painter.setBrush(self.myBrush)
        self.painter.setPen(self.minhaPen)
        self.painter.drawEllipse(QPoint(x+50,y+175), 50, 50)

        if (verde == 1): self.myBrush = QBrush(Qt.green)
        else: self.myBrush = QBrush()
        self.minhaPen = QPen(Qt.green, 5)
        self.painter.setBrush(self.myBrush)
        self.painter.setPen(self.minhaPen)
        self.painter.drawEllipse(QPoint(x+50,y+300), 50, 50)

        

app = QApplication(sys.argv)
window = MyWindow()
#window = QWidget()
window.show() 
app.exec()
