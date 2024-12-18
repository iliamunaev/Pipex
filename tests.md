
# **Test Cases for the Pipex Program**

## **Input/Output Edge Cases**

1. **Non-existent Infile** // passed
   - **Terminal**:
     ```bash
     < test_files/nonexistent.txt | ls > test_files/output.txt
     ```
   - **Pipex**:
     ```bash
     ./pipex test_files/nonexistent.txt "cat" "ls" test_files/output.txt
     ```

2. **Non-existent Outfile ** // passed
   - **Terminal**:
     ```bash
     < test_files/existing.txt cat | > test_files/nonexistent_output.txt
     ```
   - **Pipex**:
     ```bash
     ./pipex test_files/existing.txt "cat" "cat" test_files/nonexistent_output.txt
     ```

3. **No Read Permission on Infile** // passed
   - **Terminal**:
     ```bash
     chmod -r test_files/noread.txt
     < test_files/noread.txt cat | ls -l > test_files/output.txt
     ```
   - **Pipex**:
     ```bash
     ./pipex test_files/noread.txt "cat" "ls -l" test_files/output.txt
     ```

4. **No Write Permission on Outfile** // passed
   - **Terminal**:
     ```bash
     touch test_files/nowrite.txt && chmod -w test_files/nowrite.txt
     < test_files/existing.txt cat | > test_files/nowrite.txt
     ```
   - **Pipex**:
     ```bash
     ./pipex test_files/existing.txt "cat" "cat" test_files/nowrite.txt
     ```

5. **Not Empty Infile** // passed
   - **Terminal**:
     ```bash
     < test_files/existing.txt cat | > test_files/output.txt
     ```
   - **Pipex**:
     ```bash
     ./pipex test_files/existing.txt "cat" "cat" test_files/output.txt
     ```

## **Command Edge Cases**

6. **First Command Not Found** //
   - **Terminal**:
     ```bash
     < test_files/existing.txt nonexistentcmd | cat > test_files/output.txt
     ```
   - **Pipex**:
     ```bash
     ./pipex test_files/existing.txt "nonexistentcmd" "cat" test_files/output.txt
     ```
7. **Second Command Not Found** //
   - **Terminal**:
     ```bash
     < test_files/existing.txt cat | nonexistentcmd > test_files/output.txt
     ```
   - **Pipex**:
     ```bash
     ./pipex test_files/existing.txt "cat" "nonexistentcmd" test_files/output.txt
     ```

8. **Both Commands Not Found** //
   - **Terminal**:
     ```bash
     < test_files/existing.txt nonexistentcmd1 | nonexistentcmd2 > test_files/output.txt
     ```
   - **Pipex**:
     ```bash
     ./pipex test_files/existing.txt "nonexistentcmd1" "nonexistentcmd2" test_files/output.txt
     ```

9. **Empty First Command** //
    - **Terminal**:
      ```bash
      < test_files/existing.txt "" | cat > test_files/output.txt
      ```
    - **Pipex**:
      ```bash
      ./pipex test_files/existing.txt "" "cat" test_files/output.txt
      ```

10. **Empty Second Command** //
    - **Terminal**:
      ```bash
      < test_files/existing.txt cat | "" > test_files/output.txt
      ```
    - **Pipex**:
      ```bash
      ./pipex test_files/existing.txt "cat" "" test_files/output.txt
      ```

11. **Empty Both Commands** //
    - **Terminal**:
      ```bash
      < test_files/existing.txt "" | "" > test_files/output.txt
      ```
    - **Pipex**:
      ```bash
      ./pipex test_files/existing.txt "" "" test_files/output.txt
      ```

12. **Command with Arguments Containing Special Characters**  // ??? maybe no need to test
    - **Terminal**:
      ```bash
      < test_files/existing.txt grep "a.*b" > test_files/output.txt
      ```
    - **Pipex**:
      ```bash
      ./pipex test_files/existing.txt "grep 'a.*b'" "cat" test_files/output.txt
      ```

13. **Command Using Environment Variables** //
    - **Terminal**:
      ```bash
      < test_files/existing.txt env | grep PATH > test_files/output.txt
      ```
    - **Pipex**:
      ```bash
      ./pipex test_files/existing.txt "env" "grep PATH" test_files/output.txt
      ```


## **Pipe and Execution Edge Cases**

14. **Broken Pipe Handling** // 
    - **Terminal**:
      ```bash
      yes | head -n 2 > test_files/output.txt
      ```
    - **Pipex**:
      ```bash
      ./pipex test_files/existing.txt "yes" "head -n 2" test_files/output.txt
      ```

21. **Command Producing No Output**
    - **Terminal**:
      ```bash
      < test_files/existing.txt grep "nonexistentpattern" > test_files/output.txt
      ```
    - **Pipex**:
      ```bash
      ./pipex test_files/existing.txt "grep nonexistentpattern" "cat" test_files/output.txt
      ```

22. **Command Producing Excessive Output**
    - **Terminal**:
      ```bash
      yes > test_files/output.txt
      ```
    - **Pipex**:
      ```bash
      ./pipex test_files/existing.txt "yes" "cat" test_files/output.txt
      ```

---

