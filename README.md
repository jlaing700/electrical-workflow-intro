#### Program Information  
This is a spin of the standard press button to blink written in pure C.  
Utilizing PCINT interrupts we can put the MCU to a light sleep mode (not implemented) while waiting for user input.  
Upon button press we exhibit one of 3 states:  
- Off (0% duty cycle)
- Dim (50% duty cycle)
- On  (100% duty cycle)  
  
Dimming and button debounce are done by counting Timer 0 overflows, where Timer 0 runs at a clk / 1024 prescale.  
The `TIMER0_OVF_vect` (overflow vector) increments a global counter (globee) until a set point (globee > OVF_DELAY)  
at which point a flag is set (bottle) and debounce conditional is partially satisfied, allowing another button press (falling only).  
  
Dimming is much the same whereby a single count of the global counter (globee) is required to increment/decrement the PWM duty cycle.  
Upon duty cycle change the global counter is cleared.  
  
Pin change interrupts are disabled while dimming so no user input can be entered until the fade loop terminates.  
This is done by clearing PCMSK2.  
  
PWM output is handled using TIMER2 and OCR2B (PD3) at a 1x prescalar. A very smooth LED fade is the result.  
  
This has been tested to work on Arduino Nano clone boards using the CH340G and old bootloader.  

### How to use  
# Pinout
- Input: PD2. A simple NO SPST tactile switch between PD2 and GND  
- Output:   PD3. An LED and 220R resistor in series from PD3 to GND.  

# This program can easily be uploaded in one of 2 ways:
- Compile, link, upload with the standard AVR toolchain (avr-gcc, avrdude)  
- Break the code into recurring and single use sections, then put the broken up code into Arduino IDE and press upload

## Compile Yourself (Linux)
- Compile:  `avr-gcc -O2 -mmcu=atmega328p ./main.c -o ./out.out`  
- Link:     `avr-objcopy -0 ihex out.out	.out.hex`  
- Upload:   `avrdude -C/etc/avrdude.conf -v -patmega328p -carduino -P/dev/ttyUSB0 -b57600 -D -Uflash:w:./.out.hex:i`  
  
# For more info please ping me in the discord, thank you.


--
  
  
  
  
Note: There are two methods in which you can publish your work through Github. 
1. Using Git Bash CD (Command Prompts)
2. Using GitHub Desktop app and GitHub website
Pick whichever you're comfortable with. If you're not a coding person, I recommend using the simpe GitHub Desktop method. 

Make sure you have created a GitHub account before you start. 

# 1. GitHub-Work-Flow-Intro-Project
Add a .txt file telling club members about you and what your goals are for Fall 2022 semester

## How to Contribute to the Repository
Here is a brief explanation on how to contribute to git and github

#### Git vs. Github
Git is a repository version control that is local to your computer only. This means only the user of the local computer has access to these files. It keeps track of any changes that are commited to it so that each iteration of a repo can be accessed. Be sure to update this each time you finish your work session for the day as it will act as a backup storage. Git is important for version control but also because this is where github will be pulling the files from whenever a "push" occurs. **You will need to install git onto your computer**

https://git-scm.com/downloads

Github is a cloud based repository viewer that allows a repository to be accessed via webapp. Github will act as a central location for all our individual tasks and develepments to be accessed from any computer connected to the internet. Changes should be comitted to Git first and then pushed to Github so anybody can access pull the changes to the repository.

#### Cloning
To make the initial link of a github repository onto your git, you must clone it. Here are the steps to doing so

1. Open git bash or linux terminal in the working directory of where you wish to store the repository files on your computer. This is can be done by right-clicking inside the folder you save the files and selecting "Git Bash Here"

2. Use the clone command to clone the github repository onto your git. It will automatically create a folder with the name of the repository with all of its contents
```
git clone https://github.com/Mechatronics-SDSU/electrical-workflow-intro.git
```

#### Branching
Every repository, in our case **GitHub_Work_Flow_Intro_Project**, has a **main** branch where the most up-to-date ready to ship version is held. This is to ensure there is always a deployable version at any point in the development and maintenance cycle. When new features or additions are being developed, typically a new branch is created with the name of that feature. This allows for a new location that new code, PCB designs, and updates can be saved without affecting the **main** branch. In our case, there currently exists a branch for each seperate piece to the project. Once one of the features/branches has been thoroughly tested and is stable, that branch is merged into the **main** branch. What this will do is copy all files from the initial development branch and merge them into the **main** branch so it becomes the most up-to-date version with these new features.

Here is an example of how to create a new branch off of main. Please use the following naming format for the branch **[Your_Name]_[Description of Branch]**

#### Creating a New Branch Example


Create a new branch off of **electrical-workflow-intro** called "Tristan_dev"

```
git checkout -b Tristan_dev main
```

#### Git Workflow

Here is a step by step explanation of how a typical worksession goes

1. Open git bash or linux terminal in the working directory of where you store the repository files on your computer. This is can be done by right-clicking inside the folder you save the files and selecting "Git Bash Here"


2. Pull any and all changes from the github repository **main** to be saved into your local git. Note you must enter the exact branches you wish to update your local version of to the github version. See step 3 on how to change current branch. 
```
git pull
```

3. Enter the exact branch you wish to do development in. Important to do this step as failure to do so may result in conflicts
```
git checkout [Name_of_Branch]
```

4. Start developing as you normally do until you are all finished


5. Add the specific files that were worked on
```
git add file.txt

or

git add -A
```

6. Commit the changes to the added files to the local git with a message of what was changed. It is important to add a message as the commit will open up VIM expecting you to write a message in. **To avoid this issue, be sure to write the message in the initial commit command**
```
git commit -m "Programmed the Arduino to blink an LED every 5 seconds"
```


7. Push these commits in your local git to the github so everyone can pull these changes to their local computers
```
git push origin [Name_of_Branch]
```

8. A pop window will appear prompting for you github login information. Enter you username into the first window and click submit, then enter you password into the second window and click submit.
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

# 2. GitHub-Work-Flow-Intro-Project Using GitHub Desktop App: https://desktop.github.com/
Download and install GitHub Desktop App on your computer, make sure you're using the same account for both GitHub website and GitHub Desktop App. 

## There are a total of 3 steps on how to Contribute to the Repository:
1. Cloning
2. Branching
3. Pushing 


Cloning and Branching are usually only done once. 

To contribute to a Repository, you must clone it on your local computer. 

Branching is creating a version of that clone in order to push any work you've done petaining the intruction of that Repository. 

Pushing is uploading your files/work you've done to GitHub where anyone who has access to the Repository can see your files that you pushed. 


In these steps below, l'll show you how to do all that using GitHub Desktop app and GitHub website. 

1. Create a text file on your desktop. Within the text file, tell us about you and what your goals are for Fall 2022 semester. For more brownie points, add in any particular interests that you would like to work with/learn more about in our electrical team. 

Now that your text file is ready to be shared on GitHub, we'll first have to add yourself to this repository to create a branch. 

A branch is a cloned version of a repository. In this case, we'll create a branch named after your name (e.g: Fadi_dev) of this repository.

Within this new branch that you will create, you will be able to add in any files that pertains to the repository instructions. 

(More information about GitHub, Branching, and Cloning can be found in the sections above in method 1)

2. To add yourself to the repository, navigate and press the main branch on the GitHub website. 
Navigate to "Code" --> "Open with GitHub Desktop". From there, GitHub desktop will clone the repository of main branch. After the clone has finished, you will now be able to create your own personal branch. 
On the GitHub Desktop app, navigate to "Current branch" and press "New branch". Create a branch named after your name (e.g: Fadi_dev). 

Congratualtions, you now have your own personal branch of this repository. 

3. After you have made your branch, navigate to it and press, you will notice that the README.md instructions are cloned to your branch. 
Next step is to add your .txt file that you have already made on your desktop. All thats left to do is to upload your .txt file to github **while** you're in your created branch (this is important). 

Once you've uploaded your text file, you should be able to see what you've wrote down on GitHub. Anyone who has access to this repository is also able to see it. 

**If you have any questions, reach out to Fadi on Discord**
