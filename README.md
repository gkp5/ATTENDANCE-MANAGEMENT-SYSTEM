# Attendance Management System

## Introduction
The **Attendance Management System** is a console-based program developed in **C** that allows students and teachers to efficiently manage attendance records. The system eliminates manual errors and ensures efficient record-keeping.

### Features
- **Student and Teacher Registration & Authentication**
- **Attendance Marking** for Each Day of the Month
- **Student Attendance Summary (Percentage Calculation)**
- **File Handling** for Persistent Data Storage
- **Teacher-Only Controls** (Mark Holidays, Remove Students, etc.)

## Objectives
The primary objectives of this system are:
- Automate the attendance marking process.
- Store attendance data persistently using files.
- Ensure only authorized users (teachers) can manage attendance records.
- Allow students to access their attendance summary.
- Enable teachers to mark holidays and delete students.

## Features & Functionalities

### A. User Roles
- **Teacher**: Can mark attendance, view attendance records, mark holidays, and remove students.
- **Student**: Can view their attendance summary (days present, attendance percentage).

### B. Attendance Management
- **Mark Attendance** → Teachers can mark students as present (1) or absent (0).
- **View Attendance** → Teachers can check attendance for a given day.
- **Student Attendance Summary** → Students can check their attendance percentage.

### C. File Handling
- Attendance data is saved in a text file (`data.txt`) and reloaded at startup to prevent data loss.

### D. Security & Access Control
- **Username & Password authentication** for teachers and students.
- **Only teachers** can modify attendance and remove students.

## System Implementation

| Component      | Details                    |
|---------------|----------------------------|
| Language      | C                           |
| Data Storage  | Text File (`data.txt`)      |
| User Interface | Console-Based (CLI)        |
| Authentication | Username & Password        |

### Core Functions

| Function           | Description                           |
|--------------------|-------------------------------------|
| `studentSignUp()`  | Registers a new student.           |
| `teacherSignUp()`  | Registers a new teacher.           |
| `studentLogin()`   | Authenticates a student.           |
| `teacherLogin()`   | Authenticates a teacher.           |
| `teacherMenu()`    | Displays the teacher’s dashboard.  |
| `markAttendance()` | Allows teachers to mark attendance.|
| `viewAttendance()` | Displays attendance records.       |
| `markHoliday()`    | Marks a specific day as a holiday. |
| `studentSummary()` | Shows a student’s attendance percentage. |
| `saveData()`       | Saves attendance and user data to a file. |
| `loadData()`       | Loads saved data from a file. |
| `deleteStudent()`  | Removes a student from the system. |

## Code Flow & Working

### A. User Registration & Login
- The program first asks whether the user is a student or a teacher.
- If the user signs up, their username and password are stored in a file.
- If the user logs in, their credentials are checked against saved records.

### B. Attendance Marking
- The teacher selects a date (1-31).
- For each student, the teacher enters `1` (Present) or `0` (Absent).
- Attendance is stored in the student’s record and saved in the file.

### C. Viewing Attendance
- Teachers can view attendance for a specific day.
- Students can check their total attendance percentage.

### D. Data Storage & Retrieval
- Data is saved in `data.txt` in the format:
  ```
  studentCount teacherCount
  studentUsername password attendanceData...
  teacherUsername password
  ```
- This data is loaded automatically when the program starts.

## Sample Test Cases

| Test Case           | Input            | Expected Output                 | Result |
|---------------------|-----------------|---------------------------------|--------|
| Student Sign Up    | `John, pass123`  | `Student registered`            | ✅ Pass |
| Student Login      | `John, pass123`  | `Login successful`              | ✅ Pass |
| Teacher Login      | `admin, admin123` | `Login successful`              | ✅ Pass |
| Mark Attendance    | `Day 5: John = 1` | `Attendance marked`             | ✅ Pass |
| View Attendance    | `Day 5`          | `John: Present`                 | ✅ Pass |
| Student Summary    | `John`           | `Total Days: 10, Present: 8, 80%` | ✅ Pass |
| Delete Student     | `John`           | `Student removed`               | ✅ Pass |

## Challenges & Fixes

| Issue                 | Solution Implemented |
|----------------------|--------------------|
| File Handling Errors | Added checks to handle missing files. |
| Invalid User Input   | Used input validation and error messages. |
| Duplicate Usernames  | Ensured unique usernames during sign-up. |

## Future Enhancements
- **Add a GUI** → Implement a graphical version using Tkinter (Python) or Qt (C++).
- **Use a Database** → Replace text files with MySQL or SQLite for secure storage.
- **Generate Reports** → Create Excel/PDF reports of attendance data.
- **Online Integration** → Implement a web-based portal for remote access.

## Conclusion
The **Attendance Management System** effectively automates the attendance process, eliminating manual errors.

### Key Benefits:
✅ Secure & Role-Based Access  
✅ Automated Attendance Tracking  
✅ Persistent Data Storage Using Files  
