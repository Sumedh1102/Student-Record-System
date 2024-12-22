#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    char first_name[50];
    char last_name[50];
    int roll_no;
    char class[10];
    float percentage;
};

void addstudent();
void studentrecord();
void searchstudent();
void deletestudent();

int main() {
    int choice;
    while (1) {
        printf("\n\t\t\t\t----STUDENT DATABASE SYSTEM-----");
        printf("\n\n1. Add Student Records");
        printf("\n2. View Student Records");
        printf("\n3. Search Student");
        printf("\n4. Delete Records");
        printf("\n5. Exit");
        printf("\n--------------------------------------");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addstudent();
                break;
            case 2:
                studentrecord();
                break;
            case 3:
                searchstudent();
                break;
            case 4:
                deletestudent();
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

void addstudent() {
    struct student info;
    FILE *fp;
    char another = 'y';

    fp = fopen("students.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (another == 'y' || another == 'Y') {
        printf("\nEnter First Name: ");
        scanf("%s", info.first_name);
        printf("Enter Last Name: ");
        scanf("%s", info.last_name);
        printf("Enter Roll Number: ");
        scanf("%d", &info.roll_no);
        printf("Enter Class: ");
        scanf("%s", info.class);
        printf("Enter Percentage: ");
        scanf("%f", &info.percentage);

        fwrite(&info, sizeof(info), 1, fp);

        printf("Do you want to add another record? (y/n): ");
        scanf(" %c", &another);
    }

    fclose(fp);
    printf("Student record(s) added successfully!\n");
}

void studentrecord() {
    struct student info;
    FILE *fp;

    fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("Error opening file or no records found!\n");
        return;
    }

    printf("\n\t\tStudent Records\n");
    printf("----------------------------------------\n");
    while (fread(&info, sizeof(info), 1, fp)) {
        printf("Name: %s %s\n", info.first_name, info.last_name);
        printf("Roll Number: %d\n", info.roll_no);
        printf("Class: %s\n", info.class);
        printf("Percentage: %.2f\n", info.percentage);
        printf("----------------------------------------\n");
    }

    fclose(fp);
}

void searchstudent() {
    struct student info;
    FILE *fp;
    int roll_no, found = 0;

    fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("Error opening file or no records found!\n");
        return;
    }

    printf("Enter Roll Number to search: ");
    scanf("%d", &roll_no);

    while (fread(&info, sizeof(info), 1, fp)) {
        if (info.roll_no == roll_no) {
            printf("\nStudent Found:\n");
            printf("Name: %s %s\n", info.first_name, info.last_name);
            printf("Roll Number: %d\n", info.roll_no);
            printf("Class: %s\n", info.class);
            printf("Percentage: %.2f\n", info.percentage);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with Roll Number %d not found!\n", roll_no);
    }

    fclose(fp);
}

void deletestudent() {
    struct student info;
    FILE *fp, *temp;
    int roll_no, found = 0;

    fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("Error opening file or no records found!\n");
        return;
    }

    temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Error opening temporary file!\n");
        fclose(fp);
        return;
    }

    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll_no);

    while (fread(&info, sizeof(info), 1, fp)) {
        if (info.roll_no == roll_no) {
            found = 1;
        } else {
            fwrite(&info, sizeof(info), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found) {
        printf("Student with Roll Number %d deleted successfully!\n", roll_no);
    } else {
        printf("Student with Roll Number %d not found!\n", roll_no);
    }
}
