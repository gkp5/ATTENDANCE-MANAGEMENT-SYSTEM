#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
#define MAX_DAYS 31

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int attendance[MAX_DAYS]; // 1 = present, 0 = absent
} Student;

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} Teacher;

Student students[MAX_USERS];
Teacher teachers[MAX_USERS];
int studentCount = 0, teacherCount = 0;
int holidays[MAX_DAYS] = {0}; // 1 = Holiday, 0 = Normal day

// Function Prototypes
void studentSignUp();
void teacherSignUp();
int studentLogin();
int teacherLogin();
void teacherMenu();
void markAttendance();
void viewAttendance();
void markHoliday();
void studentSummary(int studentIndex);
void saveData();
void loadData();
void deleteStudent();

void studentSignUp() {
    if (studentCount >= MAX_USERS) {
        printf("Student limit reached!\n");
        return;
    }

    printf("Enter student username: ");
    scanf("%s", students[studentCount].username);

    printf("Enter student password: ");
    scanf("%s", students[studentCount].password);

    memset(students[studentCount].attendance, 0, sizeof(students[studentCount].attendance));
    studentCount++;

    printf("Student registered successfully!\n");
    saveData();
}

void teacherSignUp() {
    if (teacherCount >= MAX_USERS) {
        printf("Teacher limit reached!\n");
        return;
    }

    printf("Enter teacher username: ");
    scanf("%s", teachers[teacherCount].username);

    printf("Enter teacher password: ");
    scanf("%s", teachers[teacherCount].password);

    teacherCount++;
    printf("Teacher registered successfully!\n");
    saveData();
}

int studentLogin() {
    char username[MAX_USERNAME_LENGTH], password[MAX_PASSWORD_LENGTH];
    printf("Enter student username: ");
    scanf("%s", username);

    printf("Enter student password: ");
    scanf("%s", password);

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].username, username) == 0 &&
            strcmp(students[i].password, password) == 0) {
            return i; // Return student index
        }
    }
    return -1;
}

int teacherLogin() {
    char username[MAX_USERNAME_LENGTH], password[MAX_PASSWORD_LENGTH];
    printf("Enter teacher username: ");
    scanf("%s", username);

    printf("Enter teacher password: ");
    scanf("%s", password);

    for (int i = 0; i < teacherCount; i++) {
        if (strcmp(teachers[i].username, username) == 0 &&
            strcmp(teachers[i].password, password) == 0) {
            return i;
        }
    }
    return -1;
}

// Function that runs the teacher menu after login
void teacherMenu() {
    int choice;
    while (1) {
        printf("\n===== Teacher Menu =====\n");
        printf("1. Mark Attendance\n");
        printf("2. View Attendance Records\n");
        printf("3. Mark a Holiday\n");
        printf("4. Delete a Student\n");
        printf("5. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: markAttendance(); break;
            case 2: viewAttendance(); break;
            case 3: markHoliday(); break;
            case 4: deleteStudent(); break;
            case 5: return;
            default: printf("Invalid choice! Try again.\n");
        }
    }
}

void markAttendance() {
    int day, choice;
    printf("Enter date to mark attendance (1-31): ");
    scanf("%d", &day);
    
    if (day < 1 || day > MAX_DAYS || holidays[day - 1] == 1) {
        printf("Invalid date or marked as a holiday!\n");
        return;
    }

    for (int i = 0; i < studentCount; i++) {
        printf("%s (1 = Present, 0 = Absent): ", students[i].username);
        scanf("%d", &choice);
        students[i].attendance[day - 1] = choice;
    }

    printf("Attendance marked successfully!\n");
    saveData();
}

void viewAttendance() {
    int day;
    printf("Enter date to view attendance (1-31): ");
    scanf("%d", &day);

    if (day < 1 || day > MAX_DAYS) {
        printf("Invalid date!\n");
        return;
    }

    printf("\nAttendance for Day %d:\n", day);
    for (int i = 0; i < studentCount; i++) {
        printf("%s: %s\n", students[i].username, students[i].attendance[day - 1] ? "Present" : "Absent");
    }
}

void studentSummary(int studentIndex) {
    int present = 0, totalDays = 0;

    printf("\nAttendance Summary for %s:\n", students[studentIndex].username);
    for (int i = 0; i < MAX_DAYS; i++) {
        if (holidays[i] == 0) {
            totalDays++;
            if (students[studentIndex].attendance[i]) present++;
        }
    }

    printf("Total Days: %d, Attended: %d, Percentage: %.2f%%\n", totalDays, present, (totalDays == 0) ? 0 : ((float)present / totalDays) * 100);
}

void markHoliday() {
    int day;
    printf("Enter date to mark as holiday (1-31): ");
    scanf("%d", &day);

    if (day < 1 || day > MAX_DAYS) {
        printf("Invalid date!\n");
        return;
    }

    holidays[day - 1] = 1;
    printf("Holiday marked on Day %d.\n", day);
    saveData();
}

void saveData() {
    FILE *file = fopen("data.txt", "w");
    if (!file) return;

    fprintf(file, "%d %d\n", studentCount, teacherCount);
    for (int i = 0; i < studentCount; i++) {
        fprintf(file, "%s %s ", students[i].username, students[i].password);
        for (int j = 0; j < MAX_DAYS; j++) {
            fprintf(file, "%d ", students[i].attendance[j]);
        }
        fprintf(file, "\n");
    }

    for (int i = 0; i < teacherCount; i++) {
        fprintf(file, "%s %s\n", teachers[i].username, teachers[i].password);
    }

    fclose(file);
}

void deleteStudent() {
    char username[MAX_USERNAME_LENGTH];
    printf("Enter student username to delete: ");
    scanf("%s", username);

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].username, username) == 0) {
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            printf("Student removed!\n");
            saveData();
            return;
        }
    }
    printf("Student not found!\n");
}

void loadData() {
    FILE *file = fopen("data.txt", "r");
    if (!file) {
        printf("No existing data found.\n");
        return;
    }

    fscanf(file, "%d %d", &studentCount, &teacherCount);
    for (int i = 0; i < studentCount; i++) {
        fscanf(file, "%s %s", students[i].username, students[i].password);
        for (int j = 0; j < MAX_DAYS; j++) {
            fscanf(file, "%d", &students[i].attendance[j]);
        }
    }

    for (int i = 0; i < teacherCount; i++) {
        fscanf(file, "%s %s", teachers[i].username, teachers[i].password);
    }

    fclose(file);
}


int main() {
    int choice;
    loadData();

    while (1) {
        printf("\n===== Attendance System =====\n");
        printf("1. Student Sign Up\n");
        printf("2. Teacher Sign Up\n");
        printf("3. Student Login\n");
        printf("4. Teacher Login\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: studentSignUp(); break;
            case 2: teacherSignUp(); break;
            case 3: {
                int studentIndex = studentLogin();
                if (studentIndex != -1) studentSummary(studentIndex);
                else printf("Invalid credentials!\n");
                break;
            }
            case 4: if (teacherLogin() != -1) teacherMenu(); break;
            case 5: return 0;
            default: printf("Invalid choice! Please try again.\n");
        }
    }
}
