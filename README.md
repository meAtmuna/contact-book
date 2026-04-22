# Contact BooK (C)

A simple command-line contact book written in C.
This project lets you store, view and search contacts using a CSV file.

## Features
- Add new contacts
- List all saved contacts
- Search contacts by name 
- CSV file storage
- Handles commas inside input
- works on both Windows and Unix systems
- Clears terminal for better UI

## How it works
- All contacts are stored in a file:
    * contact_book_data.csv

- Each contact is saved like this:
    * "Name", "Address", "Email", "Number"

## How to run
1. Complile
    * gcc main.c -o contact_book

2. Run 
    * ./contact_book

- or with custom file:
    * ./contact_book myfile.csv

## Menu Options

* [A] Add contact
* [L] List contacts
* [S] Search Contacts
* [H] Help
* [Q] Quit

## Search
* you can search contacts by name
* partial match works
    * Example: typing Atmuna will match Atmuna Zulfi

# Notes 
* Commas in user input are replaced with ; to protect CSV format
* Quotes are used when saving data to properly handle complex input
* Custom CSV parser is used to correctly read fields inside quotes    

## What I Learned
* File handling in C(fopen, fprintf, fgets)
* structs and arrays
* Parsing CSV maually
* Handling edge cases like commas inside quotes
* Building a simple CLI menu