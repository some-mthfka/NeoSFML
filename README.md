# NeoSFML
Neovim GUI based on SFML

Even though only Windows is currently supported, adding support for Linux and Mac is planned (code was written with portability in mind).

##Installation instructions
1. Install Python 3.3.5.
  * Download at https://www.python.org/download/releases/3.3.5/

2. Install Pip for Python 3.3
  * Instructions: http://stackoverflow.com/questions/4750806/how-do-i-install-pip-on-windows
  * In short 
    * Download https://bootstrap.pypa.io/get-pip.py
    * Make sure Python33 is in your path. Or, if not, put get-pip.py in the Python33 folder. Run "python get-pip.py".

3. Install Python Neovim: `python -m pip install neovim`
4. Download and install Neovim for Windows. Make sure it's in your path. 
  * Instructions: https://github.com/neovim/neovim/wiki/Installing-Neovim 
5. Download NeoSFML (link coming soon) and run it.

##Compilation
* Boost's Locale library
* Python33
* SFML
* MinGW 4.9.2, earlier versions may work.
