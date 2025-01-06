

# Employee Management System

This project is a **Employee Management System** implemented in C, designed for use by HR teams, employees, and IT admins. It facilitates secure authentication, CRUD operations for admins and employees, and submission/management of leave or permission requests.

## Features

### Admin Features
- **Login**: Secure admin authentication.
- **Add Admin**: Register a new admin.
- **Remove Admin**: Delete an existing admin.
- **Update Admin**: Modify an admin’s details.
- **List Admins**: Display all registered admins.
- **Manage Employees**:
  - Add, remove, update, and view employee details.
- **Manage Requests**:
  - View and approve/reject employee requests.

### Employee Features
- **Login**: Secure employee authentication.
- **View Details**: Display personal and professional information.
- **Submit Request**: Apply for leave or permission.
- **Update Details**: Modify personal details.
- **View Requests**: Check request status.

## System Design

### Struct Definitions
1. **Admin**: Stores admin credentials (`id`, `password`).
2. **Employee**: Holds personal and professional details (`id`, `name`, `age`, `designation`, etc.).
3. **Request**: Captures leave/permission requests (`employee_id`, `type`, `reason`, `status`).

### Flow Diagram
1. **Login → Menu → Operations (CRUD or Requests)**  
2. **Requests → Status Update → Notifications**

### SDLC Phases
1. **Requirements Gathering**:  
   - Stakeholders: HR team, employees, and IT admins.  
   - Functional Requirements: Login, CRUD operations, request handling.  
   - Non-functional Requirements: Scalability (100+ records), secure authentication.
   
2. **System Design**: Defined struct types for admin, employee, and request handling, with detailed flow and logic.

3. **Implementation**:  
   - Language: C.  
   - Key Modules:
     - `authenticate_admin()`, `authenticate_employee()`: Secure login.  
     - `add_admin()`, `remove_admin()`, `update_admin()`: Admin management.  
     - `add_employee()`, `remove_employee()`, `update_employee()`: Employee management.  
     - `submit_request()`, `manage_request()`: Request handling.

4. **Testing**:  
   - **Unit Testing**: Verified individual functions like `add_admin()`, `submit_request()`.  
   - **Integration Testing**: End-to-end workflow testing, including:
     - Employee login → Submit request → Admin approval.
   - **Edge Cases**:
     - Exceeding record capacity.
     - Invalid credentials.
     - Requests for non-existent employees.

5. **Deployment and Maintenance**:  
   - Compile and deploy the program as an executable.  
   - Provide user documentation.  
   - Regularly monitor and update the system.

## How to Run
1. Compile the C program using a GCC compiler:
   ```bash
   gcc -o employee_management employee_management.c
   ```
2. Run the executable:
   ```bash
   ./employee_management
   ```

## Future Enhancements
- Introduce a GUI for better user interaction.
- Add email notifications for request approvals/rejections.
- Enable data storage in a database or external file for persistence.
