# Directory Structure

```
Loan-Management-System-Experiment/
├── API keys/                  # API keys and related info
├── Benchmarks/                # Benchmarking and performance notes
├── Csv Files For Analysis/    # CSVs for data analysis
├── Documentation/             # Design docs, UML, and notes
├── Header Files/              # C++ header files
├── Src/                       # Main source code (C++, Python, web, tests)
│   ├── Web Ui Related FIles/  # Flask app, templates, static files
│   ├── Test Files/            # C++ test source files
│   ├── sqlite3 Executables/   # SQLite3 binaries/objects
│   ├── deprecated files/      # Deprecated/legacy code
│   ├── dll_file_testing_folder/ # DLL test scripts
│   ├── Folder with Generated Data/ # Generated data for testing
│   ├── Tools still in production to be used later/ # WIP tools
│   ├── indefinitely postponed/ # Experimental or postponed code
│   ├── Database files/        # Database files
│   ├── analysis_experiment.py # Data analysis/ML
│   ├── client.py              # CLI client
│   ├── header_file_for_server_and_cli.py # Python interface to C++ DLL
│   ├── loanManagementLibraryForServer.cpp # C++ main source
│   ├── makefile               # Build instructions
│   ├── requirements.txt       # Python dependencies
│   ├── server.py              # Python server
│   ├── use_predictors.py      # ML predictors
│   └── ...                    # Other scripts and files
├── LICENSE
├── README.md
└── ...
```
# Loan-Management-System-Experiment

This project experiments with Python and C++ features to create a Loan Management System for secured personal loans. It serves as a proof of concept, exploring trade-offs in readability, maintainability, and scalability. The system combines a C++ backend (as a DLL) with Python for both command-line and web-based interfaces, and uses SQLite for persistent storage. The project also includes data analysis and machine learning components in Python.

## Features

- Server-client architecture with a C++ backend (DLL) integrated via Python socket.
- Real-time economic data integration using external APIs for dynamic applicant scoring.
- Flask-based web application for a user-friendly interface.
- In-depth data analysis and automated report generation.
- Machine learning algorithms in Python to predict loan acceptance scores and decisions.
- CRUD-based SQLite3 database management accessible from both Python and C++.
- Data generation for testing and analysis.
- Exporting data to CSV for analysis in Excel or Python.
- Linear/matrix algebra optimizations for loan scoring.
- Improved database insert speed.

## Extending Features

- Planned: SQLite3 C++ database abstraction.
- Planned: Enhanced risk assessment methods utilizing statistical analysis (pending completion of a basic C++ statistics library).

## Dependencies

1. C++ compiler (MINGW) version 11
2. Make (or CMake for the cmake branch)
3. Python 3.8 and above
4. SQLite3 database
5. Included logger for debugging
6. Alpha Vantage API key (optional, for real-time economic data)

## Installation

1. Install Python, create a virtual environment, and install the requirements from the `requirements.txt` file.
2. Install a Mingw compiler and add it to your PATH.
3. Install make and add it to your PATH manually, or use Chocolatey to add it automatically.
4. (Optional) Obtain a free Alpha Vantage API key for up-to-date federal funds rate and related metrics. You may also use default rate values without an API key.
5. Add the SQLite3 header file into the header files folder, or unzip the provided archive.

## Compilation Instructions

### Compile the C++ Library (DLL)
1. Open a terminal in the project root directory.
2. Run:
    ```
    make
    ```
   or, if using CMake:
    ```
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```
3. The compiled DLL will be placed in the appropriate output directory.

### Compile Individual C++ Files (if needed)
You can also compile individual C++ files using g++:
```
g++ -shared -o loan_management.dll -I"Header Files" Src/*.cpp -lstdc++fs
```
Adjust the paths as needed for your setup.

## Running and Testing

### Run the Python CLI
```
python Src/header_file_for_server_and_cli.py
```

### Run the Web Application
```
python Src/Web\ Ui\ Related\ FIles/flask_client.py
```
Then open your browser to `http://127.0.0.1:5000/`.

### Run Unit Tests

Currently, there is no formal Python test suite.

For C++:
```
make runtests
```
This will build and run all C++ unit tests as defined in the makefile.

## Contributing

Contributions are welcome! Please open issues or submit pull requests for improvements, bug fixes, or new features.

 

