# Hospital Patient Management System

A console-based **Hospital Patient Management System** developed in **C programming language**. The system allows hospital staff to manage patient records, doctor assignments, billing information, and patient discharge records using file handling.

## Features

* Add new patient records
* View all registered patients
* Search patients by Patient ID
* Assign a doctor to a patient
* Manage room and medicine billing
* Automatically calculate total bills
* Update patient information
* Discharge/delete patient records
* Persistent data storage using binary files
* Simple menu-driven command-line interface

## Technology Used

| Technology           | Purpose                         |
| -------------------- | ------------------------------- |
| C                    | Core programming language       |
| GCC                  | C compiler                      |
| File Handling        | Persistent patient data storage |
| Binary File (`.dat`) | Patient record database         |
| Structures           | Patient data organization       |

## Patient Data Structure

Each patient record contains:

```c
struct Patient {
    int id;
    char name[50];
    int age;
    char disease[50];
    char phone[15];
    char assignedDoctor[50];
    float roomCharges;
    float medicineFees;
    float totalBill;
};
```

### Stored Information

* Patient ID
* Patient Name
* Age
* Diagnosis/Disease
* Phone Number
* Assigned Doctor
* Room/Ward Charges
* Medicine/Pharmacy Fees
* Total Bill

## Menu Options

When the application starts, the following menu is displayed:

```text
=== Enterprise Hospital Patient Management Dashboard ===

1. Add Patient
2. View All Patients
3. Search Patient by ID
4. Assign Care Doctor
5. Update Billing / Invoicing
6. Update Patient Info
7. Discharge Patient (Delete Record)
8. Exit Application
```

### 1. Add Patient

Allows the user to register a new patient.

The system collects:

* Patient ID
* Name
* Age
* Disease/Diagnosis
* Phone Number

New patients initially have:

```text
Doctor: Not Assigned
Room Charges: 0
Medicine Fees: 0
Total Bill: 0
```

The record is then stored in `patients.dat`.

### 2. View All Patients

Displays all patient records stored in the database.

Example:

```text
ID: 101 | Name: Rahul Sharma | Age: 25 | Disease: Fever | Phone: 9876543210
Doctor: Dr. Kumar | Room Charges: $500.00 | Med Fees: $250.00 | Total Bill: $750.00
```

### 3. Search Patient

Searches for a specific patient using the Patient ID.

If the patient exists, the complete record is displayed.

If the patient does not exist:

```text
Patient with ID 101 not found.
```

### 4. Assign Care Doctor

Allows a doctor to be assigned to an existing patient.

The patient is searched using Patient ID, after which the doctor's name can be entered.

### 5. Update Billing / Invoicing

Allows hospital staff to enter:

* Room/Ward Charges
* Pharmacy/Medicine Fees

The total bill is calculated automatically:

```text
Total Bill = Room Charges + Medicine Fees
```

For example:

```text
Room Charges   = $500
Medicine Fees  = $250
----------------------
Total Bill     = $750
```

### 6. Update Patient Info

Allows modification of:

* Patient Name
* Age
* Disease
* Phone Number

The patient's ID, assigned doctor, and billing information remain unchanged.

### 7. Discharge Patient

Removes a patient record from the database.

A temporary file called `temp.dat` is used during the deletion process. All records except the selected patient are copied into the temporary file, after which the original database is replaced.

### 8. Exit

Terminates the application.

---

# Installation

## Prerequisites

Install a C compiler such as:

* GCC
* MinGW
* Clang
* Visual Studio C compiler

For Windows, **MinGW/GCC** is recommended for a simple command-line setup.

## Clone the Project

If the project is hosted on GitHub:

```bash
git clone <YOUR-GITHUB-REPOSITORY-URL>
cd Hospital-Patient-Management
```

## Compile

Using GCC:

```bash
gcc main.c -o hospital
```

For additional warnings:

```bash
gcc -Wall -Wextra -std=c11 main.c -o hospital
```

## Run on Windows

```bash
hospital.exe
```

or:

```bash
.\hospital.exe
```

## Run on Linux/macOS

```bash
./hospital
```

---

# Example Workflow

A typical workflow can be:

```text
Start Application
       │
       ▼
   Add Patient
       │
       ▼
 Patient Record
       │
       ├──────────────► Assign Doctor
       │
       ├──────────────► Update Patient Information
       │
       ├──────────────► Manage Billing
       │
       ▼
 Search / View Patient
       │
       ▼
 Discharge Patient
       │
       ▼
     Exit
```

# File Handling

The application uses binary file handling to store patient records.

### Add Records

```c
fopen("patients.dat", "ab");
```

The `ab` mode opens the file for binary append.

### Read Records

```c
fopen("patients.dat", "rb");
```

The `rb` mode opens the database for binary reading.

### Update Records

```c
fopen("patients.dat", "rb+");
```

The `rb+` mode allows existing records to be read and modified.

### Delete Records

A temporary file is used:

```text
patients.dat
     │
     ▼
  Read Records
     │
     ▼
  Skip Selected Patient
     │
     ▼
   temp.dat
     │
     ▼
Replace patients.dat
```

---

# Concepts Demonstrated

This project demonstrates several fundamental concepts of C programming:

* Structures
* Functions
* Pointers
* File handling
* Binary files
* `fread()`
* `fwrite()`
* `fseek()`
* `fopen()`
* `fclose()`
* `remove()`
* `rename()`
* Conditional statements
* Loops
* Switch-case
* Dynamic record management

# Algorithms Used

## Patient Search

**Input:** Patient ID

**Process:**

1. Open `patients.dat`.
2. Read each patient record.
3. Compare the stored ID with the requested ID.
4. If a match is found, display the patient.
5. Otherwise continue searching.
6. Display "not found" if no matching record exists.

**Time Complexity:** `O(n)`

where `n` is the number of patient records.

## Patient Deletion

**Input:** Patient ID

**Process:**

1. Open the existing patient database.
2. Create `temp.dat`.
3. Read each patient.
4. Skip the patient whose ID matches the requested ID.
5. Copy all other records to `temp.dat`.
6. Delete the original database.
7. Rename `temp.dat` to `patients.dat`.

**Time Complexity:** `O(n)`

# Data Persistence

Patient information is stored in:

```text
patients.dat
```

Therefore, patient records remain available after the application is closed and restarted.

> Do not manually edit `patients.dat` because it is a binary file.

# Limitations

This is an educational console-based project and has some limitations:

* No graphical user interface
* No login/authentication system
* No role-based access control
* No MySQL/database server
* No encryption of patient information
* No appointment management
* No doctor database
* No pharmacy inventory
* No payment gateway
* Limited input validation
* Single-user local file storage

# Future Enhancements

The project can be extended into a complete hospital management system by adding:

### 1. Doctor Management

* Add doctors
* Update doctor information
* Doctor availability
* Doctor specialization
* Patient-doctor relationships

### 2. Appointment Management

* Schedule appointments
* Cancel appointments
* Appointment history
* Doctor availability

### 3. Hospital Departments

Examples:

```text
Cardiology
Neurology
Orthopedics
Emergency
Radiology
Pediatrics
General Medicine
```

### 4. Advanced Billing

* Consultation fees
* Room charges
* Laboratory charges
* Surgery charges
* Medicine expenses
* Discounts
* Tax calculation
* Payment status
* Printable invoices

### 5. Database Integration

The file-based system can later be migrated to:

```text
C Application
      │
      ▼
Database API
      │
      ▼
MySQL / PostgreSQL
```

### 6. User Authentication

Different roles can be introduced:

```text
Administrator
     │
     ├── Manage Patients
     ├── Manage Doctors
     └── Manage Staff

Doctor
     │
     ├── View Patients
     └── Update Diagnosis

Receptionist
     │
     ├── Register Patients
     └── Manage Appointments

Billing Staff
     │
     └── Manage Billing
```

### 7. Graphical/Web Interface

The C application can eventually be connected to a modern frontend such as:

```text
React.js
     │
     ▼
Backend API
     │
     ▼
Hospital Database
```


# Disclaimer

This project is intended for **educational and demonstration purposes**. It should not be used as a production hospital information system without implementing appropriate security, authentication, authorization, data protection, auditing, backup, validation, and regulatory compliance mechanisms.

# Author
- Lakshya Agarwal
**Hospital Patient Management System**

Developed as a C programming project.


