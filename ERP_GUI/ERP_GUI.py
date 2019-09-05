import tkinter as tk
from tkinter import *
from tkinter import ttk
import subprocess
import sys, string, os
import numpy as np
import csv
import SettingsModule as settings
import matplotlib.pyplot as plt
import matplotlib
from shutil import copyfile
matplotlib.use("TkAgg")
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
#from matplotlib.backends.backend_tkagg import FigureCanvasAgg
from matplotlib.figure import Figure
import webbrowser


# TODO: variables should be put somewhere else
directory = os.getcwd()
fileRepository = "files"
runNumber = 0
buttonSize = [16,1]
individualCounter = 0


if (os.name == 'nt'):
	print("Running windows")
	directory = "C:/Program Files/V-REP3/V-REP_PRO_EDU"
else:
	print("Not running windows : make sure the directory variable is correctly set")
	directory = ''
	# set directory here for linux machines

def make_label(parent, img):
    label = Label(parent, image=img)
    label.pack()

# Information that can be used to store for loading an individual. 
class Individual:
	def __init__(self, num):
		self.num = num;
		self.genome = np.random.rand(1,10)
		self.genomeInformation = []
	def save(self, path):
		# TODO open csv
		a = 0

# Object to store individuals for a queue
class PopulationQueue:
	def __init__(self):
		self.individuals = []
	def addIndividualToQueue():
		self.individuals.append(Individual)

# Frame containing data 
class DataFrame(Frame):
	def __init__(self,parent):
		self.master = parent
		# load the maximum and average fitness of an evolutionary run
		Button(parent, text="Load Progression", height = buttonSize[1], command=self.plotRun).grid(row=1, column=0, sticky=W)
		self.imglabel = Label(self.master)
		self.imglabel.grid(row=2, column = 0)
	
	# lpots a specific run
	def plotRun(self):
		tk.Frame.__init__(self, self.master)

		data = []
		dataMax = []
		data25 = []
		data75 = []
		dataMin = []
		xData = []
		with open(directory + "/"+fileRepository+"/" + "SavedGenerations0.csv") as csv_file:
			csv_reader = csv.reader(csv_file, delimiter = ',')
			for n, row in enumerate(csv_reader):
				dataAll = []
				loadInd = True;
				for i, gib in enumerate(row):
					if (gib == "avg: "):
						data.append(float(row[i+1]))
						loadInd = False
					if gib == "fitness: ":
						dataMax.append(float(row[i+1]))
					if (i> 0 and loadInd == True):
						dataAll.append(float(row[i]))
				dataMin.append(min(dataAll))
				data25.append(np.percentile(dataAll,25))
				data75.append(np.percentile(dataAll,75))
				xData.append(n)
						# load individuals

		fig = plt.figure()
		ax = fig.add_subplot(1,1,1)
		ax.fill_between(xData,data25,data75, color ='blue', alpha = 0.4)#, c='blue', alpha=0.4)
		ax.plot(data, c = 'blue')
		ax.plot(dataMax, c = 'blue', alpha = 0.8)
		ax.plot(dataMin, c='blue', alpha = 0.8)
		ax.set_xlabel("generation")
		ax.set_ylabel("fitness")
		plt.show()

	def draw_figure(self,canvas, figure, loc=(0, 0)):
		""" Draw a matplotlib figure onto a Tk canvas

		loc: location of top-left corner of figure on canvas in pixels.
		Inspired by matplotlib source: lib/matplotlib/backends/backend_tkagg.py
		"""
		figure_canvas_agg = FigureCanvasTkAgg(figure)
		figure_canvas_agg.draw()
		figure_x, figure_y, figure_w, figure_h = figure.bbox.bounds
		figure_w, figure_h = int(figure_w), int(figure_h)
		photo = tk.PhotoImage(master=canvas, width=figure_w, height=figure_h)

		# Position: convert from top-left anchor to center anchor
		canvas.create_image(loc[0] + figure_w/2, loc[1] + figure_h/2, image=photo)

		# Unfortunately, there's no accessor for the pointer to the native renderer
		tkagg.blit(photo, figure_canvas_agg.get_renderer()._renderer, colormode=2)

		# Return a handle which contains a reference to the photo object
		# which must be kept live or else the picture disappears
		return photo

class SimulationFrame(Frame):
	def __init__(self,parent):
		# Row is just defines the position of the buttons
		row = 0
		# Run evolution
		self.newRunNum = Button(parent, text="Run Evolution", command=self.clickRun, height = buttonSize[1], width = buttonSize[0])
		self.newRunNum.grid(column=0, row=row);
		self.master = parent # parent frame
		# Button to load the best individual
		row += 1
		self.recallB = Button(parent, text="Recall Best Individual", command=self.clickRecallBest, height = buttonSize[1], width = buttonSize[0])
		self.recallB.grid(column=0, row=row);
		row += 1
		# Button to run in parallel
		self.runPB = Button(parent, text="Run Parallel", command=self.clickRunParallel, height = buttonSize[1], width = buttonSize[0])
		self.runPB.grid(column=0,row=row);
		row += 1
		# Button to run on cluster TODO: add command function that can be used 
		self.runPB = Button(parent, text="Run on Cluster", height = buttonSize[1], width = buttonSize[0],bg="orange2")
		self.runPB.grid(column=0,row=row);
		row += 1
		# Specify the path to the savedGenerations .csv file
		self.pathGen = directory + '/' + fileRepository + '/' + 'SavedGenerations' + str(runNumber) +'.csv'

		self.loadPopulationLab = Label(parent, text="Specify experiment number", height = buttonSize[1])
		self.loadPopulationLab.grid(column=1, row=row-1, columnspan =2 );

		# Loading a population
		self.loadPopulationButton = Button(parent, text="Load Population", command=self.loadPopulation, height = buttonSize[1], width = buttonSize[0])
		self.loadPopulationButton.grid(column=0, row=row);
		
		# Specifying the run number of a population to load (/save) TODO: actually implement it
		self.popNumVar = IntVar(parent,0)
		self.popNumVar.trace("w", self.callback)
		self.popNumScale = Scale(parent, from_=0, to=99, orient=HORIZONTAL, variable = self.popNumVar)
		self.popNumScale.grid(column = 1, row = row)
		self.popNumText=Entry(parent, textvariable = self.popNumVar)
		self.popNumText.grid(column = 2, row = row)

		# Specify the number of cores of the machine. 
		row += 1
		self.coreNumberLabel = Label(parent, text="Specify dedicated number of cores")
		self.coreNumberLabel.grid(column = 1, row = row, columnspan =2)
		row+=1
		self.coreLabel = Label(parent, text="Number of cores")
		self.coreLabel.grid(column = 0, row = row)
		self.coreButton = Scale(parent, from_=0, to=32, orient=HORIZONTAL)
		self.coreButton.set(4)
		# row +=1
		self.coreButton.grid(column = 1, row = row, columnspan = 2)
		row += 1
		# For the repository
		# TODO: add a command that sets the repository
		self.repLab = Label(parent,text='repository')
		self.repLab.grid(column=0, row = row)
		self.repository=Entry(parent,width=30)
		row+=1
		self.repository.grid(column=0,row=row, columnspan = 1)
		self.repository.configure(text=directory)	
		row += 1

		# Just for some output statements
		self.con = Label(parent,text="Output")
		self.con.grid(column=0, row =row)
		#self.n_cores = 6
		#self.runB = Button(parent, text="Run Evolution", command=self.clickRun, height = buttonSize[1], width = buttonSize[0])

		# for queueing a population TODO
		self.popQueue = PopulationQueue()
		self.popQueueList = Listbox(parent, width =60)
		self.popQueueList.grid(column=3,row=2, columnspan = 4, rowspan = 6, sticky=E+W)
		self.popQueueList.bind('<<ListboxSelect>>',self.CurSelect)
		
		# TODO: placeholder for inspecting the genome based on whatever. This should call another python script but currently just loads an image
		self.inspect = Button(parent, text="Inspect Genome", command=self.inspectGenome, height = buttonSize[1], width = buttonSize[0])
		self.inspect.grid(column=4, row=0);
		# Loads the specific individual in V-REP
		self.inspect = Button(parent, text="Inspect in VREP", command=self.clickRecallBest, height = buttonSize[1], width = buttonSize[0])
		self.inspect.grid(column=3, row=0);
		
		# tracks which individual is selected
		self.selectedInd = self.popQueueList.curselection()

		#self.imglabel = Label(parent, text="Nothing to see here")
		#self.imageIsLoaded = False
		#self.imglabel.grid(column=4, row=2)

	def callback(self,*args):
		print("TODO: Adjust settings")
	def loadPopulation(self):
		# empty existing queue
		self.popQueue.individuals.clear()
		self.popQueueList.delete(0,self.popQueueList.size())
		self.pathGen = directory + '/' + fileRepository + '/' + 'SavedGenerations' + str(self.popNumVar.get()) +'.csv'
		
		# open csv and push the individuals to the individuals list
		data = []
		with open(self.pathGen, 'rt') as csvfile: 
			csvreader = csv.reader(csvfile, delimiter=',')
			for row in csvreader:
				data.append(row)
			#	print(row)
		finalDat = data[-1]
		readIndividual = False
		individuals = []
		for point in finalDat:
			if (readIndividual == True and len(point) > 0):
				#print(point)
				individuals.append(int(point))
			if (point == 'individuals: '):
				readIndividual = True
		
		# store genomes loaded from last population

		# Add the genomes to the simulated population queue
		for ind in individuals:
			self.popQueue.individuals.append(Individual(ind))
		for ind in self.popQueue.individuals:
			self.popQueueList.insert(END, "Genome " + str(ind.num)+ " - Fitness " + " ... DM ... Size ... ")
				
		print(individuals)

	def CurSelect(self, evt):
		value=str(self.popQueueList.get(self.popQueueList.curselection()))
		#print(value)
		self.selectedInd = self.popQueueList.curselection()

	def setRealWorldPointer(self, p):
		self.realWorldPointer = p
			
	def inspectGenome(self):
		print(self.popQueue.individuals[self.selectedInd[0]].genomeInformation)
		# TODO: Add function that will be useful to add a genome
		
	def onFrameConfigure(self, event):
		'''Reset the scroll region to encompass the inner frame'''
		self.canvas.configure(scrollregion=self.canvas.bbox("all"))
		
	def checkRepo(self,dir):
		# check if directory exists
		dir = dir + '/' + fileRepository + '/'
		if (os.path.isdir(dir)):
			print("main directory exists")
		else:
			print("main directory does not exist, creating directory " + dir)
			os.mkdir(dir)
		if (os.path.isdir(dir +"/genomes0")):
			print("genomes0 directory exists (this is where the genomes are stored")
		else: 
			print("genomes0 directory does not exist, making directory (this is where the genomes are stored")
			os.mkdir(dir + "/genomes0")

	def clickRun(self):
		self.con.configure(text="Starting Evolution")
		self.repository.configure(text=directory )
		self.checkRepo(directory)
		# TODO: connect headless variable to running the program in headless mode or not.
		try:
			if (os.name == 'nt'):
				subprocess.Popen([r""+ directory + "/vrep.exe", "-g0", "-g2", "-gfiles"])
			else:
				subprocess.Popen([r""+ directory + "/vrep.sh", "-g0", "-g2", "-gfiles"])
		except:
			print("Could not start an evolutionary run. Check if the directory is set correcty")

		# file = 'C:\\Program Files\\V-REP3\\V-REP_PRO_EDU\\vrep.exe'
		# os.system('"'+ file + '"' + ' -g10 - g2 -gfiles')

	def clickRecallBest(self):
		# Loads the best individual
		self.con.configure(text="RECALLING BEST")
		self.repository.configure(text=directory)
		if (os.name == 'nt'):
			subprocess.Popen([r""+ directory + "/vrep.exe", "-g0", "-g9", "-gfiles"])
		else:
			subprocess.Popen([r""+ directory + "/vrep.sh", "-g0", "-g9", "-gfiles"])
	
	def clickRunParallel(self):
		# Runs evolution in parallel
		self.con.configure(text="Starting Parallel Evolution")
		self.repository.configure(text=directory)
		self.checkRepo(directory)
		for i in range(self.coreButton.get()-1):
			#arguments = "-h -g" + str(i) + " -g2 -gfiles -gREMOTEAPISERVERSERVICE_"+ str(i + 1) +"_FALSE_FALSE"
			if (os.name == 'nt'):
				subprocess.Popen([r""+directory+"/vrep.exe","-h", "-g0" ,"-g1" ,"-gfiles", "-gREMOTEAPISERVERSERVICE_"+str(i+104000)+"_TRUE_TRUE"])
			else:
				subprocess.Popen([r""+directory+"/vrep.sh" ,"-h","-g0" ,"-g1" ,"-gfiles", "-gREMOTEAPISERVERSERVICE_"+str(i+104000)+"_TRUE_TRUE"])
		# -gREMOTEAPISERVERSERVICE_"+ str(i+1040000) + "_FALSE_FALSE"])
		if (os.name == 'nt'):
			# subprocess.Popen([r""+directory+"/programming/v_repExtER_Integration/x64/Debug/ERClient.exe",directory+"/files" ,"0" ,str(self.coreButton.get())])
			subprocess.Popen([r""+directory+"/programming/ER_Personal/x64/Debug/ERClient.exe",directory+"/files" ,"0" ,str(self.coreButton.get())])
		else:
			subprocess.Popen([r""+directory+"/programming/Cplusplus_Evolution/build/ERClient/ERClient", directory+"/files" ,"0" ,str(self.coreButton.get())])


class MajorButtons(Frame):
	counter = 0
	def __init__(self,parent):
		Frame.__init__(self,parent)
		self.master = parent

		# Notebook has the four main tabs: simulation, settings, data analysis and real-world
		self.nb = ttk.Notebook(parent, width=800)
		nb = self.nb
		self.simulationFrame =  ttk.Frame(nb)
		self.settingsFrame =  ttk.Frame(nb)
		self.dataAnFrame =  ttk.Frame(nb)
		nb.add(self.simulationFrame, text="Initializer")
		nb.add(self.settingsFrame, text="Settings")
		nb.add(self.dataAnFrame, text="Data Analyser")
		#nb.select(self.settingsFrame)
		nb.enable_traversal()
		#nb.grid(column=0, row=0);
		nb.pack()

		# Actually instantiating all the windows:::::::::: 
		# settings is quite large so is imported
		self.settingsWindow = settings.Settings(self.settingsFrame, directory)
		self.simulationWindow = SimulationFrame(self.simulationFrame)
		self.dataWindow = DataFrame(self.dataAnFrame)
		self.nb.select(self.simulationFrame)

	def create_window(self):
		self.counter += 1
		t = Toplevel(self)
		t.wm_title("Window #%s" % self.counter)
		l = Label(t, text="This is window #%s" % self.counter)
		l.pack(side="top", fill="both", expand=True, padx=100, pady=100)

class Window(Frame):
	def __init__(self, master=None):
		# master should be the TKinter root
		Frame.__init__(self,master)
		self.master = master
		# Major buttons is the root class for all the buttons
		self.mButtons = MajorButtons(self.master)
		self.init_window()

	def init_window(self):
		self.master.title("Ecosystem Manager GUI")
		#self.pack(fill=BOTH, expand=1)
		
		menu = Menu(self.master)
		self.master.config(menu=menu)
		
		# Basic menu buttnos on top of the window :::::::
		file = Menu(menu)
		file.add_command(label = "Exit", command = self.client_exit)
		menu.add_cascade(label="File", menu = file)

		edit = Menu(menu)
		edit.add_command(label="Undo")
		menu.add_cascade(label="Edit", menu = edit)

		edit = Menu(menu)
		edit.add_command(label="About")
		edit.add_command(label="Documentation", command = self.dochelper)
		menu.add_cascade(label="Help", menu = edit)

		# :::::::::::::::::::::::::::::::::::::::::::::::
		#quitButton = Button(self,text="Quit", command=self.client_exit)
		#quitButton.place(x=0,y=0)

	def client_exit(self):
		exit()
	def dochelper(self):
		url = "https://www.overleaf.com/read/xbkcjsdfjwhr"
		webbrowser.open(url)

# Page containing information about the settings
class SettingsPage(Frame):
	def __init__(self,parent):
		Frame.__init__(self, parent)
		label = Label(self,text="Settings", font=LARGE_FONT)

if __name__ == "__main__":
	print("directory = " + directory)
	# Initialize root of TKinter GUI
	root = Tk()
	root.geometry("800x600")
	# Window is the main class containing all the functionalities. Can be changed
	app = Window(root)
	root.mainloop()
	#window = Tk()
	#window.title("ARE Ecosystem Manager")


