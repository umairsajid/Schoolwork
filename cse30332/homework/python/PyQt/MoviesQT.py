#John F. Lake, Jr. 
#My PyQt movies program

from PyQt4.QtCore import *
from PyQt4.QtGui import *
import os
import sys
import requests
import json

class MoviesQT(QMainWindow):
	def __init__(self):
		super(MoviesQT,self).__init__()
		self.setWindowTitle("Movie Recommender")
		self.resize(500,500)
		self.central = MoviesCentral(parent = self)
		self.setCentralWidget(self.central)
		self.SITE_URL = 'http://student00.cse.nd.edu:40001'
		self.RECOMMENDATIONS_URL = self.SITE_URL + '/recommendations/'

		#Set up exit action: 
		exitAction = QAction("Quit",self)
		self.connect(exitAction, SIGNAL("triggered()"), self.exit)
		
		#Set up set user action:
		viewProfAction = QAction("View Profile",self)
		self.connect(viewProfAction, SIGNAL("triggered()"),self.view_profile)
		setUserAction = QAction("Set User",self)
		self.connect(setUserAction, SIGNAL("triggered()"),self.set_user)

		

		#Set up menu bar: 
		self.file_menu = self.menuBar().addMenu("File")
		self.file_menu.addAction(exitAction)
		self.user_menu = self.menuBar().addMenu("User")
		self.user_menu.addAction(viewProfAction)
		self.user_menu.addAction(setUserAction)

		
	def exit(self):
		sys.exit(app.exec_())

	def view_profile(self):
		msgbox = QMessageBox()
		msgbox.setText("")
		msgbox.exec_()  # COME BACK THIS LINE IN A SECOND

	def set_user(self):
		input = QInputDialog()
		
		text,ok = input.getText(self, 'Set User','Enter the User ID:')
	
		if ok:	
			self.central.uid = int(text)
			self.central.movieTitle.setText(text)
		

class MoviesCentral(QWidget):
	def __init__(self,parent=None):
		super(MoviesCentral,self).__init__(parent)
		self.uid = 5
		self.show()
		self.movieTitle = QLabel("%s" % self.uid)

		layout = QGridLayout()
		layout.addWidget(self.movieTitle,3,0)
		self.setLayout(layout)

#Main function: 
if __name__ == "__main__":
	app = QApplication(sys.argv)
	gui = MoviesQT()
	gui.show()
	sys.exit(app.exec_())
