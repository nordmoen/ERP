# Evolutionary Robotics Plugin for V-REP

This plugin for V-REP is an abstraction of the evolutionary robotics plugin that was developed during my PhD on evolving Modular Robots. 
This plugin contains a simple evolutionary algorithm, encodings that can create modular robots, a simple control architecture, and the possibility to evolve fixed morphology robots in V-REP.
It also contains a small GUI that can be opened using python 3 and the TKinter package. 

For more information about the science behind the plugin, find my PhD dissertation at: https://en.itu.dk/~/media/en/research/phd-programme/phd-defences/2018/phd-thesis-final-version-frank-veenstra-pdf.pdf?la=en 

## Getting Started

These instructions will get the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

V-REP : http://www.coppeliarobotics.com/downloads.html 

C++ desktop development Visual Studio (If you don't have it, visual studio will prompt you to install)

Clone repository in user specified directory the "programming" folder which can be found in the main directory of V-REP

Note: the when running evolution you can not quit the simulator directly. On windows you can unhide V-REP's console window by going to tools->usersetting and unchecking the hide console window checkbox. Closing the console window will close V-REP. 

(Windows): Visual Studio 2017 or higher

(Linux) : Cmake

(Linux) : IDE such as CLion


#### Using the GUI

- Python3

### Installing

#### Compiling the code (Windows) 

(1) Making sure all the files are in the a folder in the "programming" directory, open the Visual Studio solution file ("v_repExtER.sln") with Visual Studio. You should see two projects called "ERClient" and "v_repExtER". 

v_repExtER is the main plugin used in V-REP and ERClient can be used to parallelize the evolutionary algorithm by opening and communicating with multiple V-REP instances. 

(2) Right click on the solution in the solution explorer and press "retarget solution" in order to use the toolset version of Visual Studio that you have installed.
You should now be able to compile both projects by pressing "build all". 

(3.1) move the "catModel.ttm" and "Servo_Module.ttm" files to the in the "models" directory.

(3.2) move the "DefaultERLight.ttt" file to the "scenes" folder. 

(4) In order to run an evolutionary experiment, you can run the v_repExtER project. However, before you can run the plugin you need to specify the "Command" and the "Command Arguments" when running the code in debugging mode. 
You can set these variables by right clicking the v_repExtER project in solution explorer -> properties, and going to the "debugging" tab. In command you can add "../../vrep.exe" . In command arguments you should add "-g0 -g2 -gfiles". 

(5) You can now run v_repExtER in debugging mode and you should see some robots evolving. 

If nothing happens or an error pops up, it might be due to the settings file not being properly deleted (see "Running evolutionary experiments" below)

When building and running this project it should generate a .dll plugin and start V-REP with a few arguments that tells it to run an evolutionary experiment.
However, in order to store all the data of an evolutionary run, you are required to create a directory in the V-REP main directory called "files" which should contain a subdirectoy called "genomes0". 
This additional step is not needed when the GUI is used (The GUI automatically generates these folders).

#### Compiling the code (Linux)

You can use CMake to compile the code on Linux. (also on windows if you're not using visual studio)

(1) Once the files are downloaded create a "build" directory in the folder of the downloaded files.

(2) cd to this "build" directory and run "cmake ../" . 

(3) run "make" to compile the code

(4) After compilation, move the lib_vrepExtER.so file in the main directory of V-REP. 

(5.1) move the "catModel.ttm" and "Servo_Module.ttm" files to the in the "models" directory.

(5.2) move the "DefaultERLight.ttt" file to the "scenes" folder. 

(6) You can now open V-REP with the arguments -g0 and -g2 to see some robots evolving. : "./vrep.sh -g0 -g2"

If nothing happens or an error pops up, it might be due to the settings file not being properly deleted (see "Running evolutionary experiments" below)

The first three arguments you give to V-REP should tell the plugin (1) the experiment number, (2) the running mode, and (3) the location of the saved files. 
The location of the saved files can be specified by giving the third argument like "-gfiles". It will search for the "files" directory and store data here. 
You can also use an absolute path for the third argument.  

#### Running the GUI

Running the GUI requires Python3 and several python packages such as numpy, matplotlib and tkinter.
Once these packages are installed you can run the GUI by opening the "ERP_GUI.py" file (You will also be notified about which packages are missing when you're trying to run it).
You will need to give main directory of V-REP to this python file in line 29 or 32 depending on whether you're running windows or linux. 
A folder called "files" and a subfolder in this folder called "genomes0", will automatically be generated in the main folder of V-REP when pressing the run evolution button. 
You can also run evolution in a parallelized way but the GUI needs to know where it can find the "ERClient" application. 
You can change the "directoryInProgramming" variable in "ERP_GUI.py" from "ERP" to the name of the repository you created. 
You can now press the "Run parallel" button in the GUI to see open multiple V-REP instances. 

Note, everything in the GUI that is colored orange is non-functional. 

## Running evolutionary experiments

Note, when you already ran some evolutionary experiments, it is likely that you can find the file "settings0.csv" in the "files" repository inside the V-REP main directory (files is automatically generated). 
This file also keeps track where evolution has left off and can currently not continue where left off (bug). Please do remove the "settings0.csv" before running an experiment. 

To evolve modular robots, you can open the python 3 GUI by simply running "ERP_GUI.py". 
(windows) Alternatively, you can also open the GUI by opening the visual studio solution file: "ERP_GUI.sln"

To do a simple evolutionary experiment, you can press the "Run Evolution" button in the "Initializer" tab. 
You can distribute the evolutionary run over multiple cores by pressing the "Run Parallel" button. See "Running the GUI" if the "Run Parallel" button doesn't work.
When pressing the run parallel button the GUI will open one client application that manages the evolutionary algorithm and the genomes, and <number of cores> -1 VREP instances to which the client sends genomes to evaluate.
To see the best individual that has evolved so far, press the "Recall Best Individual" button. This will open V-REP and tells the plugin to load the best individual when you press play.

To see how evolution is progressing, you can open the data analyser tab and press the "Load Progression" button. 
This should create a plot from data in the file "SavedGenerations0.csv" (located in the files repository) which stores all the fitness values of the individuals that have been evaluated. 
The three lines of the plot depict the maximum fitness, average fitness and the minimum fitness of each generation. The filled color between two lines depicts the 25 and 75 percentiles.

## Structure of the code

For this plugin, the "v_repExtER.cpp" file is the main file that communicates with the other classes of the program. 
This file initializes the other classes and communicates with the plugin by calling the three functions "ER_VREP::startSimulation()", "ER_VREP::handleSimulation()" and "ER_VREP::endOfSimulation()".
The startOfSimulation contains some conditional statements that will automatically create a "phenotype" from a "genotype" created by the evolutionary algorithm. 
The handleSimulation function updates the created robot every simulation frame. The endOfSimulation function calls a fitness function for the created robot that will give a performance measure of the robot. 

There are several factory patterns in the code that are responsible for creating the (1) evolutionary algorithm, (2) morphology of the robot, (3) the controllers of the robot, 
(4) the neurons that can be incorporated in the controllers, (5) the modules of the robot, and (6) the environment that the robot will roam in.
For more information you can contact me, I will soon upload documentation as well.  

### Break down

## Development

## Deployment

## Contributing

## Known bugs

There is currently unfortunately no way to stop the evolution once it is running on a linux machine. Right now, "killall -9 vrep" is the unelegant way of stopping it. 
You can also specify the maximum number of generations after which VREP will stop automatically.

## Versioning

## Authors

* **Frank Veenstra** - *Initial work* - (https://github.com/FrankVeenstra)

[contributors]
Andres Faina

Edgar Buchanan

Wei Li

Matteo De Carlo

## License

This project is licensed under the GNU License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

Thanks to the IT University of Copenhagen, the project Flora-Robotica, Edinburgh Napier University and the Autonomous Robot Evolution project for supporting the development of this software package. 
    
