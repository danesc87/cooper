# COOPER
**Cooper** is a small TODO list written in CPP with SQLite as DB that has abstracted API from app itself which allows to developers to create a GUI over Cooper - CLI.
This app can *add*, *list*, *search* by coincidence or exact match and *delete* ToDo's from DB.

* Compile and Tests
* Add
* List
* Search
    * Coincidence
    * Exact Match
* Delete
* Update -> Not implemented Yet
* Logging -> Not Implemented Yet
* Debug
* Future features

## COMPILE AND TESTS
Cooper can be compiled with *cmake* or using a simple bash script called *build_and_test.sh*.

> Unit Tests are made using **Catch2**

#### CMAKE
In order to compile with *cmake* user should perform the following commando on terminal

```bash
mkdir build
cd build
cmake ..
make
```
> Inside build dir user will see cooper binary file and can execute it

To perform unit tests for *Cooper* user should compile first and then execute the following command on terminal

```bash
ctest
```
> This command should be executed on build dir

#### SCRIPT
*build_and_test.sh* can perform four actions, those are the following ones:

* build
* build-test
* test
* clean

##### build
This action creates *build* dir if it doesn't exists and then will compile *Cooper* and generate its binary file

```bash
./build_and_test.sh build
```

##### build-test
This action creates *build* dir if it doesn't exists and then will compile *Cooper* unit tests

```bash
./build_and_test.sh build-test
```
> Only compile Unit Tests for Cooper

##### test
This action executes unit tests for *Cooper*

```bash
./build_and_test test.sh
```

##### clean
This actions cleans everything and deletes *build* dir

```bash
./build_and_test.sh clean
```

## ADD
To add new ToDo to *Cooper* user need to execute the following command on 
terminal

```bash
./cooper a name:description
```
Examples

#### ToDo without description

```bash
./cooper a tests
```

If the name has spaces user can add it in the following way

```bash
./cooper a "call mom"
```

#### ToDo with description

```bash
./cooper a tests:sometest
```

If the name has spaces user can add it in the following way

```bash
./cooper a "call mom":"I need to call mom"
```

## LIST
If user wants to list all ToDo's user need to execute the following on terminal

```bash
./cooper l
```

Response will be

```bash
Name:        test
Description: 
Name:        test 1
Description: 
Name:        test 2
Description: test with description
```

## SEARCH
*Cooper* has two ways for search ToDo's 

### Coincidence
To search all ToDo's that has a coincidence with a provided name user need to execute the following command on terminal

```bash
./cooper s te
```

This will retrieve all ToDo's that contains *te* in its name

### Exact
To search all ToDo's with exact match user need to execute the following command on terminal

```bash
./cooper x test
```

This will retrieve all ToDo's that has name as *test*

## DELETE
*Cooper* can delete ToDo's from its DB, when user has more than one ToDo with the same name *Cooper* will delete the first one, in order to perform that task user need to execute the following command on terminal

```bash
./cooper d test
```

## DEBUG
In order to debug this app a parameter should be passed to *build_and_test.sh* script to create a binary that allows user to debug it

```bash
./build_and_test.sh build -DCMAKE_BUILD_TYPE=Debug
```

> After pass this argument user can debug the app with **GDB** directly or some IDE like **KDevelop**, **VSCode** with C/C++ plugins, etc

## Future Features
Some future features will be added on this app, those features are the following ones:

* Ability to update a ToDo
* Ability to Log some sutff with different levels
* Ability to configure some things
* Ability to delete a ToDo with name and description
