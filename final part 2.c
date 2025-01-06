#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ADMINS 100
#define MAX_EMPLOYEES 100
#define MAX_REQUESTS 100
#define ID_LEN 20
#define PASSWORD_LEN 20
#define NAME_LEN 50
#define DESIGNATION_LEN 50
#define REASON_LEN 100

// Struct for Admins
typedef struct {
    char id[ID_LEN];
    char password[PASSWORD_LEN];
} Admin;

// Struct for Employees
typedef struct {
    char id[ID_LEN];
    char password[PASSWORD_LEN];
    char name[NAME_LEN];
    int age;
    char designation[DESIGNATION_LEN];
    float salary;
    int experience; // New field for experience in years
} Employee;

// Struct for Leave/Permission Requests
typedef struct {
    char employee_id[ID_LEN];
    char type[10]; // "Leave" or "Permission"
    char reason[REASON_LEN];
    char status[10]; // "Pending", "Approved", "Rejected"
} Request;

Admin admins[MAX_ADMINS] = { {"admin", "admin123"} }; // Predefined admin
Employee employees[MAX_EMPLOYEES];
Request requests[MAX_REQUESTS];

int admin_count = 1;
int employee_count = 0;
int request_count = 0;

// Function prototypes
void admin_login();
void employee_login();
void admin_menu();
void employee_menu();
void add_admin();
void remove_admin(); // New function to remove admin
void update_admin(); // New function to update admin
void list_admins();
void add_employee();
void remove_employee();
void update_employee(); // New function to update employee
void view_employee_details(); // New function to view employee details
void list_employees();
void submit_request();
void view_requests();
void manage_request();
int authenticate_admin(const char *id, const char *password);
int authenticate_employee(const char *id, const char *password);

int main() {
    int choice;

    while (1) {
        printf("==========================================!!!!WELCOME TO EMPLOYEE MANAGEMENT SYSTEM!!!!=================================");
        printf("\n1. Admin Login\n2. Employee Login\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                admin_login();
                break;
            case 2:
                employee_login();
                break;
            case 3: {
                char feedback[REASON_LEN];
                printf("Exiting program. Please provide your feedback: ");
                fgets(feedback, REASON_LEN, stdin);
                feedback[strcspn(feedback, "\n")] = 0;
                printf("Thank you for your feedback: %s\n", feedback);
                printf("Goodbye!\n");
                exit(0);
            }
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void admin_login() {
    char id[ID_LEN], password[PASSWORD_LEN];

    printf("Enter Admin ID: ");
    fgets(id, ID_LEN, stdin);
    id[strcspn(id, "\n")] = 0;

    printf("Enter Password: ");
    fgets(password, PASSWORD_LEN, stdin);
    password[strcspn(password, "\n")] = 0;

    if (authenticate_admin(id, password)) {
        printf("Login successful.\n");
        admin_menu();
    } else {
        printf("Invalid credentials.\n");
    }
}

void employee_login() {
    char id[ID_LEN], password[PASSWORD_LEN];

    printf("Enter Employee ID: ");
    fgets(id, ID_LEN, stdin);
    id[strcspn(id, "\n")] = 0;

    printf("Enter Password: ");
    fgets(password, PASSWORD_LEN, stdin);
    password[strcspn(password, "\n")] = 0;

    if (authenticate_employee(id, password)) {
        printf("Login successful.\n");
        employee_menu();
    } else {
        printf("Invalid credentials.\n");
    }
}

void admin_menu() {
    int choice;

    while (1) {
        printf("\nAdmin Menu:\n");
        printf("1. Add Admin\n2. Remove Admin\n3. Update Admin\n4. List Admins\n");
        printf("5. Add Employee\n6. Remove Employee\n7. Update Employee\n8. List Employees\n");
        printf("9. View Requests\n10. Manage Requests\n11. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                add_admin();
                break;
            case 2:
                remove_admin();
                break;
            case 3:
                update_admin();
                break;
            case 4:
                list_admins();
                break;
            case 5:
                add_employee();
                break;
            case 6:
                remove_employee();
                break;
            case 7:
                update_employee();
                break;
            case 8:
                list_employees();
                break;
            case 9:
                view_requests();
                break;
            case 10:
                manage_request();
                break;
            case 11:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void employee_menu() {
    int choice;

    while (1) {
        printf("\nEmployee Menu:\n");
        printf("1. View My Details\n2. Submit Leave/Permission Request\n3. Update Details\n4. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                list_employees();
                break;
            case 2:
                submit_request();
                break;
            case 3:
                update_employee();
                break;
            case 4:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void add_admin() {
    if (admin_count >= MAX_ADMINS) {
        printf("Admin limit reached.\n");
        return;
    }

    printf("Enter new Admin ID: ");
    fgets(admins[admin_count].id, ID_LEN, stdin);
    admins[admin_count].id[strcspn(admins[admin_count].id, "\n")] = 0;

    printf("Enter new Admin Password: ");
    fgets(admins[admin_count].password, PASSWORD_LEN, stdin);
    admins[admin_count].password[strcspn(admins[admin_count].password, "\n")] = 0;

    admin_count++;
    printf("Admin added successfully.\n");
}

void remove_admin() {
    char id[ID_LEN];
    printf("Enter Admin ID to remove: ");
    fgets(id, ID_LEN, stdin);
    id[strcspn(id, "\n")] = 0;

    for (int i = 0; i < admin_count; i++) {
        if (strcmp(admins[i].id, id) == 0) {
            for (int j = i; j < admin_count - 1; j++) {
                admins[j] = admins[j + 1];
            }
            admin_count--;
            printf("Admin removed successfully.\n");
            return;
        }
    }

    printf("Admin not found.\n");
}

void update_admin() {
    char id[ID_LEN];
    printf("Enter Admin ID to update: ");
    fgets(id, ID_LEN, stdin);
    id[strcspn(id, "\n")] = 0;

    for (int i = 0; i < admin_count; i++) {
        if (strcmp(admins[i].id, id) == 0) {
            printf("Updating details for Admin ID: %s\n", id);

            printf("Enter new Admin Password: ");
            fgets(admins[i].password, PASSWORD_LEN, stdin);
            admins[i].password[strcspn(admins[i].password, "\n")] = 0;

            printf("Admin details updated successfully.\n");
            return;
        }
    }

    printf("Admin not found.\n");
}

void list_admins() {
    printf("\nList of Admins:\n");
    for (int i = 0; i < admin_count; i++) {
        printf("ID: %s\n", admins[i].id);
    }
}

void add_employee() {
    if (employee_count >= MAX_EMPLOYEES) {
        printf("Employee limit reached.\n");
        return;
    }

    printf("Enter new Employee ID: ");
    fgets(employees[employee_count].id, ID_LEN, stdin);
    employees[employee_count].id[strcspn(employees[employee_count].id, "\n")] = 0;

    printf("Enter new Employee Password: ");
    fgets(employees[employee_count].password, PASSWORD_LEN, stdin);
    employees[employee_count].password[strcspn(employees[employee_count].password, "\n")] = 0;

    printf("Enter Employee Name: ");
    fgets(employees[employee_count].name, NAME_LEN, stdin);
    employees[employee_count].name[strcspn(employees[employee_count].name, "\n")] = 0;

    printf("Enter Employee Age: ");
    scanf("%d", &employees[employee_count].age);
    getchar();

    printf("Enter Employee Designation: ");
    fgets(employees[employee_count].designation, DESIGNATION_LEN, stdin);
    employees[employee_count].designation[strcspn(employees[employee_count].designation, "\n")] = 0;

    printf("Enter Employee Salary: ");
    scanf("%f", &employees[employee_count].salary);
    getchar();

    printf("Enter Employee Experience (in years): ");
    scanf("%d", &employees[employee_count].experience);
    getchar();

    employee_count++;
    printf("Employee added successfully.\n");
}

void remove_employee() {
    char id[ID_LEN];
    printf("Enter Employee ID to remove: ");
    fgets(id, ID_LEN, stdin);
    id[strcspn(id, "\n")] = 0;

    for (int i = 0; i < employee_count; i++) {
        if (strcmp(employees[i].id, id) == 0) {
            for (int j = i; j < employee_count - 1; j++) {
                employees[j] = employees[j + 1];
            }
            employee_count--;
            printf("Employee removed successfully.\n");
            return;
        }
    }

    printf("Employee not found.\n");
}


void update_employee() {
    char id[ID_LEN];
    printf("Enter Employee ID to update: ");
    fgets(id, ID_LEN, stdin);
    id[strcspn(id, "\n")] = 0;

    for (int i = 0; i < employee_count; i++) {
        if (strcmp(employees[i].id, id) == 0) {
            printf("Updating details for Employee ID: %s\n", id);

            printf("Enter new Employee Name: ");
            fgets(employees[i].name, NAME_LEN, stdin);
            employees[i].name[strcspn(employees[i].name, "\n")] = 0;

            printf("Enter new Employee Age: ");
            scanf("%d", &employees[i].age);
            getchar();

            printf("Enter new Employee Designation: ");
            fgets(employees[i].designation, DESIGNATION_LEN, stdin);
            employees[i].designation[strcspn(employees[i].designation, "\n")] = 0;

            printf("Enter new Employee Salary: ");
            scanf("%f", &employees[i].salary);
            getchar();

            printf("Enter new Employee Experience (in years): ");
            scanf("%d", &employees[i].experience);
            getchar();

            printf("Employee details updated successfully.\n");
            return;
        }
    }

    printf("Employee not found.\n");
}

void list_employees() {
    printf("\nList of Employees:\n");
    for (int i = 0; i < employee_count; i++) {
        printf("ID: %s, Name: %s, Age: %d, Designation: %s, Salary: %.2f, Experience: %d years\n",
               employees[i].id, employees[i].name, employees[i].age,
               employees[i].designation, employees[i].salary, employees[i].experience);
    }
}

void submit_request() {
    if (request_count >= MAX_REQUESTS) {
        printf("Request limit reached.\n");
        return;
    }

    printf("Enter Request Type (Leave/Permission): ");
    fgets(requests[request_count].type, 10, stdin);
    requests[request_count].type[strcspn(requests[request_count].type, "\n")] = 0;

    printf("Enter Reason: ");
    fgets(requests[request_count].reason, REASON_LEN, stdin);
    requests[request_count].reason[strcspn(requests[request_count].reason, "\n")] = 0;

    printf("Enter Employee ID: ");
    fgets(requests[request_count].employee_id, ID_LEN, stdin);
    requests[request_count].employee_id[strcspn(requests[request_count].employee_id, "\n")] = 0;

    strcpy(requests[request_count].status, "Pending");
    request_count++;

    printf("Request submitted successfully.\n");
}

void view_requests() {
    printf("\nList of Requests:\n");
    for (int i = 0; i < request_count; i++) {
        printf("Employee ID: %s, Type: %s, Reason: %s, Status: %s\n",
               requests[i].employee_id, requests[i].type,
               requests[i].reason, requests[i].status);
    }
}

void manage_request() {
    char employee_id[ID_LEN];
    int choice;

    printf("Enter Employee ID for the request to manage: ");
    fgets(employee_id, ID_LEN, stdin);
    employee_id[strcspn(employee_id, "\n")] = 0;

    for (int i = 0; i < request_count; i++) {
        if (strcmp(requests[i].employee_id, employee_id) == 0) {
            printf("Request Found: Type: %s, Reason: %s, Status: %s\n",
                   requests[i].type, requests[i].reason, requests[i].status);

            printf("1. Approve\n2. Reject\nEnter your choice: ");
            scanf("%d", &choice);
            getchar();

            if (choice == 1) {
                strcpy(requests[i].status, "Approved");
                printf("Request approved.\n");
            } else if (choice == 2) {
                strcpy(requests[i].status, "Rejected");
                printf("Request rejected.\n");
            } else {
                printf("Invalid choice.\n");
            }

            return;
        }
    }

    printf("Request not found.\n");
}

int authenticate_admin(const char *id, const char *password) {
    for (int i = 0; i < admin_count; i++) {
        if (strcmp(admins[i].id, id) == 0 && strcmp(admins[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

int authenticate_employee(const char *id, const char *password) {
    for (int i = 0; i < employee_count; i++) {
        if (strcmp(employees[i].id, id) == 0 && strcmp(employees[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

