**Edge Cases for the Pipex Program**

### **Input/Output Edge Cases**
1. **Non-existent Infile** // passed
   - **Terminal**:
     ```bash
     < inputfiles/nonexistent.txt cat > outputfiles/output.txt
     ```
   - **Pipex**:
     ```bash
     ./pipex inputfiles/nonexistent.txt "cat" "cat" outputfiles/output.txt
     ```

2. **No Read Permission on Infile** // passed
   - **Terminal**:
     ```bash
     chmod -r inputfiles/noread.txt
     < inputfiles/noread.txt cat > outputfiles/output.txt
     ```
   - **Pipex**:
     ```bash
     ./pipex inputfiles/noread.txt "cat" "cat" outputfiles/output.txt
     ```

3. **Empty Infile**
   - **Terminal**:
     ```bash
     > inputfiles/empty.txt
     < inputfiles/empty.txt cat > outputfiles/output.txt
     ```
   - **Pipex**:
     ```bash
     ./pipex inputfiles/empty.txt "cat" "cat" outputfiles/output.txt
     ```

4. **Non-existent Outfile**
   - **Terminal**:
     ```bash
     < inputfiles/existing.txt cat > outputfiles/nonexistent/output.txt
     ```
   - **Pipex**:
     ```bash
     ./pipex inputfiles/existing.txt "cat" "cat" outputfiles/nonexistent/output.txt
     ```

5. **No Write Permission on Outfile**
   - **Terminal**:
     ```bash
     touch outputfiles/nowrite.txt && chmod -w outputfiles/nowrite.txt
     < inputfiles/existing.txt cat > outputfiles/nowrite.txt
     ```
   - **Pipex**:
     ```bash
     ./pipex inputfiles/existing.txt "cat" "cat" outputfiles/nowrite.txt
     ```

---

### **Command Edge Cases**
6. **First Command Not Found**
   - **Terminal**:
     ```bash
     < inputfiles/existing.txt nonexistentcmd | cat > outputfiles/output.txt
     ```
   - **Pipex**:
     ```bash
     ./pipex inputfiles/existing.txt "nonexistentcmd" "cat" outputfiles/output.txt
     ```

7. **Second Command Not Found**
   - **Terminal**:
     ```bash
     < inputfiles/existing.txt cat | nonexistentcmd > outputfiles/output.txt
     ```
   - **Pipex**:
     ```bash
     ./pipex inputfiles/existing.txt "cat" "nonexistentcmd" outputfiles/output.txt
     ```

8. **Both Commands Not Found**
   - **Terminal**:
     ```bash
     < inputfiles/existing.txt nonexistentcmd1 | nonexistentcmd2 > outputfiles/output.txt
     ```
   - **Pipex**:
     ```bash
     ./pipex inputfiles/existing.txt "nonexistentcmd1" "nonexistentcmd2" outputfiles/output.txt
     ```

9. **Executable Command Without Execution Permission**
   - **Terminal**:
     ```bash
     chmod -x inputfiles/script.sh
     < inputfiles/existing.txt ./inputfiles/script.sh > outputfiles/output.txt
     ```
   - **Pipex**:
     ```bash
     ./pipex inputfiles/existing.txt "./inputfiles/script.sh" "cat" outputfiles/output.txt
     ```

10. **Empty Command**
    - **Terminal**:
      ```bash
      < inputfiles/existing.txt "" | cat > outputfiles/output.txt
      ```
    - **Pipex**:
      ```bash
      ./pipex inputfiles/existing.txt "" "cat" outputfiles/output.txt
      ```

11. **Command with Arguments Containing Special Characters**
    - **Terminal**:
      ```bash
      < inputfiles/existing.txt grep "a.*b" > outputfiles/output.txt
      ```
    - **Pipex**:
      ```bash
      ./pipex inputfiles/existing.txt "grep 'a.*b'" "cat" outputfiles/output.txt
      ```

12. **Command with Absolute Path**
    - **Terminal**:
      ```bash
      < inputfiles/existing.txt /bin/cat > outputfiles/output.txt
      ```
    - **Pipex**:
      ```bash
      ./pipex inputfiles/existing.txt "/bin/cat" "cat" outputfiles/output.txt
      ```

13. **Command with Relative Path**
    - **Terminal**:
      ```bash
      < inputfiles/existing.txt ./inputfiles/relativescript.sh > outputfiles/output.txt
      ```
    - **Pipex**:
      ```bash
      ./pipex inputfiles/existing.txt "./inputfiles/relativescript.sh" "cat" outputfiles/output.txt
      ```

14. **Command Using Environment Variables**
    - **Terminal**:
      ```bash
      < inputfiles/existing.txt env | grep PATH > outputfiles/output.txt
      ```
    - **Pipex**:
      ```bash
      ./pipex inputfiles/existing.txt "env" "grep PATH" outputfiles/output.txt
      ```

15. **Command That Exits with Non-Zero Status Code**
    - **Terminal**:
      ```bash
      < inputfiles/existing.txt grep "nonexistentpattern" | cat > outputfiles/output.txt
      ```
    - **Pipex**:
      ```bash
      ./pipex inputfiles/existing.txt "grep nonexistentpattern" "cat" outputfiles/output.txt
      ```

---

### **Pipe and Execution Edge Cases**
16. **No Input Redirection** (Missing infile)
    - **Terminal**:
      ```bash
      cat | cat > outputfiles/output.txt
      ```
    - **Pipex**:
      ```bash
      ./pipex "" "cat" "cat" outputfiles/output.txt
      ```

17. **No Output Redirection** (Missing outfile)
    - **Terminal**:
      ```bash
      < inputfiles/existing.txt cat
      ```
    - **Pipex**:
      ```bash
      ./pipex inputfiles/existing.txt "cat" "cat" ""
      ```

18. **Broken Pipe Handling**
    - **Terminal**:
      ```bash
      yes | head -n 1 > outputfiles/output.txt
      ```
    - **Pipex**:
      ```bash
      ./pipex inputfiles/existing.txt "yes" "head -n 1" outputfiles/output.txt
      ```

19. **Huge Input File**
    - **Terminal**:
      ```bash
      < inputfiles/hugefile.txt cat > outputfiles/output.txt
      ```
    - **Pipex**:
      ```bash
      ./pipex inputfiles/hugefile.txt "cat" "cat" outputfiles/output.txt
      ```

20. **Large Output File**
    - **Terminal**:
      ```bash
      < inputfiles/existing.txt yes > outputfiles/largefile.txt
      ```
    - **Pipex**:
      ```bash
      ./pipex inputfiles/existing.txt "yes" "cat" outputfiles/largefile.txt
      ```

21. **Command Producing No Output**
    - **Terminal**:
      ```bash
      < inputfiles/existing.txt grep "nonexistentpattern" > outputfiles/output.txt
      ```
    - **Pipex**:
      ```bash
      ./pipex inputfiles/existing.txt "grep nonexistentpattern" "cat" outputfiles/output.txt
      ```

22. **Command Producing Excessive Output**
    - **Terminal**:
      ```bash
      yes > outputfiles/output.txt
      ```
    - **Pipex**:
      ```bash
      ./pipex inputfiles/existing.txt "yes" "cat" outputfiles/output.txt
      ```

---

### **Memory and Resource Edge Cases**
23. **Multiple Processes Competing for System Resources**
24. **File Descriptor Leak Test**
25. **Memory Leak Test** (using `valgrind`)

---

### **Signal Handling Edge Cases**
26. **SIGINT Handling (Ctrl+C)**
27. **SIGPIPE Handling**
28. **SIGSEGV Handling** (Segmentation fault protection)
29. **Invalid Input for Execve** (e.g., `NULL` path or corrupted command)

---

### **Environment Edge Cases**
30. **Empty PATH Environment Variable**
31. **PATH Environment Variable Missing**
32. **PATH Contains Invalid Directories**
33. **Command Using Custom Environment Variables**

---

### **Concurrency Edge Cases**
34. **Multiple Instances of Pipex Running Simultaneously**
35. **Race Condition on File Access**

