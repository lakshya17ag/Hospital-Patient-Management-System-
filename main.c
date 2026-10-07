#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void addPatient() {
    struct Patient p;
    FILE *fp = fopen("patients.dat", "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Patient ID: ");
    scanf("%d", &p.id);
    printf("Enter Name: ");
    scanf(" %[^\n]s", p.name);
    printf("Enter Age: ");
    scanf("%d", &p.age);
    printf("Enter Diagnosis/Disease: ");
    scanf(" %[^\n]s", p.disease);
    printf("Enter Phone Number: ");
    scanf(" %[^\n]s", p.phone);
    
    // Default initialization for new patients
    strcpy(p.assignedDoctor, "Not Assigned");
    p.roomCharges = 0.0;
    p.medicineFees = 0.0;
    p.totalBill = 0.0;

    fwrite(&p, sizeof(struct Patient), 1, fp);
    fclose(fp);
    printf("Patient record added successfully!\n");
}

void viewPatients() {
    struct Patient p;
    FILE *fp = fopen("patients.dat", "rb");
    if (fp == NULL) {
        printf("No patient records found.\n");
        return;
    }

    printf("\n============================= PATIENT RECORDS =============================\n");
    while (fread(&p, sizeof(struct Patient), 1, fp)) {
        printf("ID: %d | Name: %s | Age: %d | Disease: %s | Phone: %s\n", 
               p.id, p.name, p.age, p.disease, p.phone);
        printf("Doctor: %s | Room Charges: $%.2f | Med Fees: $%.2f | Total Bill: $%.2f\n",
               p.assignedDoctor, p.roomCharges, p.medicineFees, p.totalBill);
        printf("---------------------------------------------------------------------------\n");
    }
    fclose(fp);
}

void searchPatient() {
    int id, found = 0;
    struct Patient p;
    FILE *fp = fopen("patients.dat", "rb");
    if (fp == NULL) {
        printf("No records to search.\n");
        return;
    }

    printf("Enter Patient ID to search: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(struct Patient), 1, fp)) {
        if (p.id == id) {
            printf("\nRecord Found:\n");
            printf("ID: %d\nName: %s\nAge: %d\nDisease: %s\nPhone: %s\n", 
                   p.id, p.name, p.age, p.disease, p.phone);
            printf("Assigned Doctor: %s\n", p.assignedDoctor);
            printf("Financial Balance: Room: $%.2f | Meds: $%.2f | Total Due: $%.2f\n", 
                   p.roomCharges, p.medicineFees, p.totalBill);
            found = 1;
            break;
        }
    }
    if (!found) printf("Patient with ID %d not found.\n", id);
    fclose(fp);
}

void assignDoctor() {
    int id, found = 0;
    struct Patient p;
    FILE *fp = fopen("patients.dat", "rb+");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("Enter Patient ID to assign a doctor: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(struct Patient), 1, fp)) {
        if (p.id == id) {
            printf("Patient Found: %s\n", p.name);
            printf("Enter Doctor's Name: ");
            scanf(" %[^\n]s", p.assignedDoctor);

            fseek(fp, -sizeof(struct Patient), SEEK_CUR);
            fwrite(&p, sizeof(struct Patient), 1, fp);
            found = 1;
            printf("Doctor '%s' assigned successfully!\n", p.assignedDoctor);
            break;
        }
    }
    if (!found) printf("Patient with ID %d not found.\n", id);
    fclose(fp);
}

void manageBilling() {
    int id, found = 0;
    struct Patient p;
    FILE *fp = fopen("patients.dat", "rb+");
    if (fp == NULL) {
        printf("No records found to bill.\n");
        return;
    }

    printf("Enter Patient ID for billing management: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(struct Patient), 1, fp)) {
        if (p.id == id) {
            printf("Patient Found: %s\n", p.name);
            printf("Enter Room/Ward Charges: ");
            scanf("%f", &p.roomCharges);
            printf("Enter Pharmacy/Medicine Fees: ");
            scanf("%f", &p.medicineFees);

            // Compute cumulative summary
            p.totalBill = p.roomCharges + p.medicineFees;

            fseek(fp, -sizeof(struct Patient), SEEK_CUR);
            fwrite(&p, sizeof(struct Patient), 1, fp);
            found = 1;
            printf("Billing metrics updated successfully! Total Due: $%.2f\n", p.totalBill);
            break;
        }
    }
    if (!found) printf("Patient with ID %d not found.\n", id);
    fclose(fp);
}

void updatePatient() {
    int id, found = 0;
    struct Patient p;
    FILE *fp = fopen("patients.dat", "rb+");
    if (fp == NULL) {
        printf("No records found to update.\n");
        return;
    }

    printf("Enter Patient ID to update core information: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(struct Patient), 1, fp)) {
        if (p.id == id) {
            printf("Enter New Name: ");
            scanf(" %[^\n]s", p.name);
            printf("Enter New Age: ");
            scanf("%d", &p.age);
            printf("Enter New Disease: ");
            scanf(" %[^\n]s", p.disease);
            printf("Enter New Phone Number: ");
            scanf(" %[^\n]s", p.phone);

            fseek(fp, -sizeof(struct Patient), SEEK_CUR);
            fwrite(&p, sizeof(struct Patient), 1, fp);
            found = 1;
            printf("Patient variables updated successfully!\n");
            break;
        }
    }
    if (!found) printf("Patient with ID %d not found.\n", id);
    fclose(fp);
}

void deletePatient() {
    int id, found = 0;
    struct Patient p;
    FILE *fp = fopen("patients.dat", "rb");
    if (fp == NULL) {
        printf("No records found to close/delete.\n");
        return;
    }

    FILE *temp = fopen("temp.dat", "wb");
    if (temp == NULL) {
        printf("Allocation processing error!\n");
        fclose(fp);
        return;
    }

    printf("Enter Patient ID to discharge/delete: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(struct Patient), 1, fp)) {
        if (p.id == id) {
            found = 1;
        } else {
            fwrite(&p, sizeof(struct Patient), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);
    remove("patients.dat");
    rename("temp.dat", "patients.dat");

    if (found) printf("Patient records closed and dropped cleanly.\n");
    else printf("Patient with ID %d not found.\n", id);
}

int main() {
    int choice;
    while (1) {
        printf("\n=== Enterprise Hospital Patient Management Dashboard ===\n");
        printf("1. Add Patient\n");
        printf("2. View All Patients\n");
        printf("3. Search Patient by ID\n");
        printf("4. Assign Care Doctor\n");
        printf("5. Update Billing / Invoicing\n");
        printf("6. Update Patient Info\n");
        printf("7. Discharge Patient (Delete Record)\n");
        printf("8. Exit Application\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: searchPatient(); break;
            case 4: assignDoctor(); break;
            case 5: manageBilling(); break;
            case 6: updatePatient(); break;
            case 7: deletePatient(); break;
            case 8: exit(0);
            default: printf("Invalid option selected. Try again.\n");
        }
    }
    return 0;
}
