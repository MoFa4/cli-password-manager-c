# Mini-Pass – Simple Command-Line Password Manager

A lightweight CLI tool written in C to store, list, and retrieve account credentials.

## Features
- Add new accounts
- List all stored sites & usernames
- Retrieve password for a site
- Data persists in `pass.dat` file

## Usage

```bash
make                # compile
./mini-pass add github.com mduser secret123
./mini-pass list
./mini-pass get github.com
