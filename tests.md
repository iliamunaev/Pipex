## Pipex Test Commands

### 1. Basic Checks

#### Test 1
**Description**: Reads the file using `cat -e` (displays line endings with `$`) and pipes it to another `cat -e` before writing to the output file.
**Real Terminal**:
```bash
< infiles/basic.txt cat -e | cat -e > outfiles/outfile_real
```
**Pipex**:
```bash
./pipex infiles/basic.txt "cat -e" "cat -e" outfiles/outfile
```
**Real Terminal**:
```bash
diff -y outfiles/outfile_real outfiles/outfile
```

#### Test 2
**Description**: Executes `ls -la` (lists all files, including hidden ones) and pipes the output to `cat -e`.
**Real Terminal**:
```bash
< infiles/basic.txt ls -la | cat -e > outfiles/outfile_real
```
**Pipex**:
```bash
./pipex infiles/basic.txt "ls -la" "cat -e" outfiles/outfile
```

#### Test 3
**Description**: Executes `ls -l -a` (detailed listing of all files, including hidden ones) and pipes to `cat -e -n` (adds line numbers).
**Real Terminal**:
```bash
< infiles/basic.txt ls -l -a | cat -e -n > outfiles/outfile_real
```
**Pipex**:
```bash
./pipex infiles/basic.txt "ls -l -a" "cat -e -n" outfiles/outfile
```

#### Test 4
**Description**: Executes `ls -l -a -f` (detailed listing with no sorting) and pipes to `cat -e -n`.
**Real Terminal**:
```bash
< infiles/basic.txt ls -l -a -f | cat -e -n > outfiles/outfile_real
```
**Pipex**:
```bash
./pipex infiles/basic.txt "ls -l -a -f" "cat -e -n" outfiles/outfile
```

#### Test 5
**Description**: Executes `ls -laf` (lists all files, including hidden ones, without sorting) and pipes to `cat -e -n`.
**Real Terminal**:
```bash
< infiles/basic.txt ls -laf | cat -e -n > outfiles/outfile_real
```
**Pipex**:
```bash
./pipex infiles/basic.txt "ls -laf" "cat -e -n" outfiles/outfile
```

#### Test 6
**Description**: Uses `grep -A5 is` (searches for 'is' and displays 5 lines after each match) and pipes the result to `cat -e`.
**Real Terminal**:
```bash
< infiles/basic.txt grep -A5 is | cat -e > outfiles/nonexistingfile_real
```
**Pipex**:
```bash
./pipex infiles/basic.txt "grep -A5 is" "cat -e" outfiles/nonexistingfile
```

#### Test 7
**Description**: Reads the file with `cat -e` and searches for a non-existent word using `grep nonexistingword`.
**Real Terminal**:
```bash
< infiles/basic.txt cat -e | grep nonexistingword > outfiles/nonexistingfile_real
```
**Pipex**:
```bash
./pipex infiles/basic.txt "cat -e" "grep nonexistingword" outfiles/nonexistingfile
```

#### Test 8
**Description**: Uses an empty input file with `grep nonexistingword` and pipes the result to `cat -e`.
**Real Terminal**:
```bash
< infiles/empty.txt grep nonexistingword | cat -e > outfiles/outfile_real
```
**Pipex**:
```bash
./pipex infiles/empty.txt "grep nonexistingword" "cat -e" outfiles/outfile
```

#### Test 9
**Description**: Executes `sleep 3` (pauses for 3 seconds) and then runs `ls`.
**Real Terminal**:
```bash
< infiles/basic.txt sleep 3 | ls > outfiles/outfile_real
```
**Pipex**:
```bash
./pipex infiles/basic.txt "sleep 3" "ls" outfiles/outfile
```

#### Test 10
**Description**: Reads a large text file using `cat` and displays the first two lines with `head -2`.
**Real Terminal**:
```bash
< infiles/big_text.txt cat | head -2 > outfiles/outfile_real
```
**Pipex**:
```bash
./pipex infiles/big_text.txt "cat" "head -2" outfiles/outfile
```

---

### 2. Error Checking

#### Test 1 (Invalid Input File)
**Description**: Tests with a non-existent input file to check error handling.
**Real Terminal**:
```bash
< nonexistingfile cat -e | ls > outfiles/outfile_real
```
**Pipex**:
```bash
./pipex nonexistingfile "cat -e" "ls" outfiles/outfile
```

#### Test 2 (nonexisting Output File)
**Description**: Tests with a non-existent output file to check error handling.
**Real Terminal**:
```bash
< infiles/big_text.txt cat -e | ls > nonexistingfile_created
```
**Pipex**:
```bash
./pipex infiles/big_text.txt "cat -e" "ls" nonexistingfile_created
```

#### Test 3 (Input File Without Permissions)
**Description**: Tests with an input file that lacks read permissions.
**Setup**:
```bash
touch infiles/infile_without_permissions
chmod 000 infiles/infile_without_permissions
```
**Real Terminal**:
```bash
< infiles/infile_without_permissions cat -e | cat -e > outfiles/outfile_real
```
**Pipex**:
```bash
./pipex infiles/infile_without_permissions "cat -e" "cat -e" outfiles/outfile
```

#### Test 3 (Output File Without Permissions)
**Description**: Tests with an output file that lacks write permissions.
**Setup**:
```bash
touch outfiles/outfile_without_permissions
chmod 000 outfiles/outfile_without_permissions
```
**Real Terminal**:
```bash
< infiles/basic.txt cat -e | cat -e > outfiles/outfile_without_permissions
```
**Pipex**:
```bash
./pipex infiles/basic.txt "cat -e" "cat -e" outfiles/outfile_without_permissions
```

### Test 4 (Both invalid commands)
**Description**:
**Real Terminal**:
```bash
< infiles/basic.txt ls-l | grepzao x > outfiles/outfile
```
**Pipex**:
```bash
./pipex infiles/basic.txt "ls-l" "grepzao x" outfiles/outfile
```


