#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <map>
#include <regex> //for date input validation
#include <limits>
#include <ctime>

using namespace std;


struct Staff {
    int id{};
    string name;
    string department;
    string shift;
};

struct Equipment {
    string name;
    string department;
    int quantity{};
};

struct LabResult {
    string patient_id;
    string test_type;
    string result;
    string technician;
    string date;
};

struct Medicine {
    string name;
    int quantity{};
};

struct appointment {
    string appointment_date, description;
};

// Placeholder structs to prevent compilation error
struct patient {
    string id;
    string name;
    int age{};
    appointment apt;
    // add more fields as needed
};

struct billing {
    string patient_id;
    double amount{};
    string status;
    // add more fields as needed
};

struct Feedback {
    string user_id;
    string type;
    int rating;
    string comment;
    string date;
};

// Placeholder functions
void load_staff_data() {}
void load_medicine_data() {}
void initializeDepartments() {}

vector<Staff> staff_list;
vector<Equipment> equipments;
vector<LabResult> lab_results;
vector<Medicine> pharmacy;

void add_staff() {
    Staff s;
    cout << "Enter Staff ID: "; cin >> s.id;
    cin.ignore();
    cout << "Enter Name: "; getline(cin, s.name);
    cout << "Enter Department: "; getline(cin, s.department);
    cout << "Enter Shift (Morning/Evening/Night): "; getline(cin, s.shift);
    staff_list.push_back(s);
    cout << "Staff added.\n";
}

void show_staff_by_id() {
    int id;
    cout << "Enter Staff ID: "; cin >> id;
    for (const auto& s : staff_list) {
        if (s.id == id) {
            cout << "ID: " << s.id << ", Name: " << s.name
                 << ", Department: " << s.department << ", Shift: " << s.shift << endl;
            return;
        }
    }
    cout << "Staff not found.\n";
}

void remove_staff() {
    int id;
    cout << "Enter Staff ID to remove: "; cin >> id;
    for (auto it = staff_list.begin(); it != staff_list.end(); ++it) {
        if (it->id == id) {
            staff_list.erase(it);
            cout << "Staff removed.\n";
            return;
        }
    }
    cout << "Staff not found.\n";
}

void staff_statistics() {
    map<string, int> department_count;
    map<string, map<string, int>> shift_count;
    for (const auto& s : staff_list) {
        department_count[s.department]++;
        shift_count[s.department][s.shift]++;
    }
    cout << "\nStaff Count by Department:\n";
    for (const auto& dept : department_count) {
        cout << dept.first << ": " << dept.second << endl;
    }
    cout << "\nStaff Shift Distribution by Department:\n";
    for (const auto& dept : shift_count) {
        cout << dept.first << ":\n";
        for (const auto& shift : dept.second) {
            cout << "  " << shift.first << ": " << shift.second << endl;
        }
    }
}

void staff_menu() {
    int ch;
    do {
        cout << "\n-- Staff Management --\n1. Add Staff\n2. Show Staff by ID\n3. Remove Staff\n4. View Statistics\n5. Back\nChoice: ";
        cin >> ch;
        switch (ch) {
            case 1: add_staff(); break;
            case 2: show_staff_by_id(); break;
            case 3: remove_staff(); break;
            case 4: staff_statistics(); break;
            default: cout << "Invalid Input!";
        }
    } while (ch != 5);
}

void add_lab_result() {
    LabResult l;
    cout << "Enter Patient ID: "; cin >> l.patient_id;
    cin.ignore();
    cout << "Test Type (CBC/MRI/CT/Blood Test/X-ray): "; getline(cin, l.test_type);
    cout << "Enter Result: "; getline(cin, l.result);
    cout << "Technician Name: "; getline(cin, l.technician);
    l.date = "2025-05-11"; // Placeholder for current date
    lab_results.push_back(l);
    cout << "Result saved.\n";
}

void view_lab_results_by_patient() {
    string pid;
    cout << "Enter Patient ID: ";
    cin >> pid;
    bool found = false;
    for (const auto& l : lab_results) {
        if (l.patient_id == pid) {
            cout << "Test: " << l.test_type
                 << "\nResult: " << l.result
                 << "\nTechnician: " << l.technician
                 << "\nDate: " << l.date << "\n\n";
            found = true;
        }
    }
    if (!found) cout << "No tests found for this patient.\n";
}

void count_tests_by_category() {
    map<string, int> categories;
    for (const auto& l : lab_results) {
        categories[l.test_type]++;
    }
    cout << "Test Counts by Category:\n";
    vector<pair<string, int>> sorted(categories.begin(), categories.end());
    sort(sorted.begin(), sorted.end());
    for (const auto& category : sorted) {
        cout << category.first << ": " << category.second << endl;
    }
}

void add_equipment() {
    Equipment e;
    cin.ignore(); // ensure no leftover input
    cout << "Enter Equipment Name: "; getline(cin, e.name);
    cout << "Enter Department: "; getline(cin, e.department);
    cout << "Enter Quantity: "; cin >> e.quantity;
    equipments.push_back(e);
    cout << "Equipment added.\n";
}

void view_equipment_by_department() {
    string dept;
    cin.ignore();
    cout << "Enter Department: "; getline(cin, dept);
    bool found = false;
    for (const auto& e : equipments) {
        if (e.department == dept) {
            cout << "Name: " << e.name << "\nQuantity: " << e.quantity << endl;
            found = true;
        }
    }
    if (!found) cout << "No equipment found in this department.\n";
}

void lab_and_equipment_menu() {
    int choice;
    do {
        cout << "\n-- Lab and Equipment Management --\n";
        cout << "1. Add Lab Result\n2. View Lab Results by Patient\n3. Count Tests by Category\n4. Add Equipment\n5. View Equipment by Department\n6. Back\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1: add_lab_result(); break;
            case 2: view_lab_results_by_patient(); break;
            case 3: count_tests_by_category(); break;
            case 4: add_equipment(); break;
            case 5: view_equipment_by_department(); break;
            case 6: break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);
}

void view_medicines() {
    for (const auto& m : pharmacy) {
        cout << "Medicine: " << m.name << ", Quantity: " << m.quantity << endl;
    }
}

void check_medicine_availability() {
    string name;
    cin.ignore();
    cout << "Enter Medicine Name: "; getline(cin, name);
    for (const auto& m : pharmacy) {
        if (m.name == name) {
            cout << "Available Quantity: " << m.quantity << endl;
            return;
        }
    }
    cout << "Medicine not found.\n";
}

void dispense_medicine() {
    string name;
    int qty;
    cin.ignore();
    cout << "Enter Medicine Name: "; getline(cin, name);
    cout << "Enter Quantity to Dispense: "; cin >> qty;
    for (auto& m : pharmacy) {
        if (m.name == name) {
            if (m.quantity >= qty) {
                m.quantity -= qty;
                cout << "Medicine dispensed.\n";
            } else {
                cout << "Insufficient quantity.\n";
            }
            return;
        }
    }
    cout << "Medicine not found.\n";
}

void add_medicine() {
    Medicine m;
    cin.ignore();
    cout << "Enter Medicine Name: "; getline(cin, m.name);
    cout << "Enter Quantity: "; cin >> m.quantity;
    pharmacy.push_back(m);
    cout << "Medicine added.\n";
}

void remove_medicine() {
    string name;
    cin.ignore();
    cout << "Enter Medicine Name to Remove: "; getline(cin, name);
    for (auto it = pharmacy.begin(); it != pharmacy.end(); ++it) {
        if (it->name == name) {
            pharmacy.erase(it);
            cout << "Medicine removed.\n";
            return;
        }
    }
    cout << "Medicine not found.\n";
}

void pharmacy_menu() {
    int choice;
    do {
        cout << "\n-- Pharmacy Management --\n";
        cout << "1. View Medicines\n2. Check Medicine Availability\n3. Dispense Medicine\n4. Add Medicine\n5. Remove Medicine\n6. Back\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1: view_medicines(); break;
            case 2: check_medicine_availability(); break;
            case 3: dispense_medicine(); break;
            case 4: add_medicine(); break;
            case 5: remove_medicine(); break;
            case 6: break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);
}
bool switchInputCheck() {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Please try again." << endl;
        return true;
    }
    return false;
}
// Function to trim leading and trailing whitespace
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    size_t last = str.find_last_not_of(" \t\r\n");

    if (first == string::npos || last == string::npos)
        return "";

    return str.substr(first, last - first + 1);
}

int main() {
    constexpr int MAX_RECORDS = 100;
    patient patients[MAX_RECORDS];
    billing billings[MAX_RECORDS];
    int patient_count = 0, billing_count = 0;
    string patient_id, line;

    // Read patient records from file
    fstream patientCheck("Patient Record.txt", ios::in);
    if (patientCheck.is_open()) {
        getline(patientCheck, line); // Skip header
        while (getline(patientCheck, line)) {
            stringstream ss(line);
            getline(ss, patients[patient_count].name, '\t');
            patients[patient_count].name = trim(patients[patient_count].name);
            getline(ss, patients[patient_count].id, '\t');
            patients[patient_count].id = trim(patients[patient_count].id);
            ss >> patients[patient_count].age;
            patient_count++;
        }
        patientCheck.close();
    }

    // Read appointment file
    fstream appointmentCheck("Appointments.txt", ios::in);
    if (appointmentCheck.is_open()) {
        getline(appointmentCheck, line); // Skip header
        while (getline(appointmentCheck, line)) {
            stringstream ss(line);
            string pid, appt_date, appt_descr;
            getline(ss, pid, '\t');
            getline(ss, appt_date, '\t');
            getline(ss, appt_descr, '\t');

            // Remove trailing/leading whitespace (if any)
            pid.erase(remove(pid.begin(), pid.end(), ' '), pid.end());
            appt_date.erase(remove(appt_date.begin(), appt_date.end(), ' '), appt_date.end());

            for (int i = 0; i < patient_count; ++i) {
                if (patients[i].id == pid) {
                    patients[i].apt.appointment_date = appt_date;
                    patients[i].apt.description = appt_descr;
                    break;
                }
            }
        }
        appointmentCheck.close();
    }

    while (true) {
        int choice1;
        cout << "\nWelcome to the Hospital Management System" << endl;
        cout << "1. Patient Management" << endl;
        cout << "2. Staff Management" << endl;
        cout << "3. Lab and Equipment Management" << endl;
        cout << "4. Pharmacy Management" << endl;
        cout << "5. Billing Management" << endl;
        cout << "6. Reports and Statistics" << endl;
        cout << "7. Feedback" << endl;
        cout << "8. Exit" << endl;
        cout << "Please enter your choice: ";
        cin >> choice1;
        switch (choice1) {
            case 1: {
                cout << "Patient Management" << endl;
                int choice2;
                cout << "1. Patient Registration" << endl;
                cout << "2. Schedule Appointment" << endl;
                cout << "3. Check Appointment Records" << endl;
                cout << "4. Electronic Medical Records" << endl;
                cout << "5. Exit" << endl;
                cout << "Please enter your choice: ";
                cin >> choice2;
                if (switchInputCheck()) continue;

                switch (choice2) {
                    case 1: {
                        cout << "Patient Registration" << endl;
                        if (patient_count < MAX_RECORDS) {
                            cout << "Enter Patient Name: ";
                            cin.ignore();
                            getline(cin, patients[patient_count].name);

                            cout << "Enter Patient ID: ";
                            cin >> patients[patient_count].id;

                            bool exists = false;
                            for (int i = 0; i < patient_count; i++) {
                                if (patients[i].id == patients[patient_count].id) {
                                    exists = true;
                                    break;
                                }
                            }
                            if (exists) {
                                cout << "Patient ID already exists. Please enter a different ID." << endl;
                                break;
                            }

                            cout << "Enter Patient Age: ";
                            cin >> patients[patient_count].age;
                            fstream patient_file;
                            patient_file.open("Patient Record.txt", ios::app);
                            if (patient_file.is_open()) {
                                if (patient_count == 0) {
                                    patient_file << left;
                                    patient_file << setw(32) << "Patient Name" << "\t"
                                                 << setw(10) << "ID" << "\t"
                                                 << setw(3) << "Age" << "\n";
                                    fstream appointment_file;
                                    appointment_file.open("Appointments.txt", ios::out);
                                    if (appointment_file.is_open()) {
                                        appointment_file << left;
                                        appointment_file << setw(10) << "Patient ID" << "\t"
                                                         << setw(20) << "Appointment Date" << "\t"
                                                         << setw(100) << "Description" << endl;
                                        appointment_file.close();
                                    }
                                    else {
                                        cout << "Failed to open Appointments.txt";
                                        return 1;
                                    }
                                }

                                patient_file << left;
                                patient_file << setw(32) << patients[patient_count].name << "\t"
                                             << setw(10) << patients[patient_count].id << "\t"
                                             << setw(3) << patients[patient_count].age << "\n";
                                patient_file.close();
                            }

                            cout << "Patient registered successfully!" << endl;
                            cout << "Patient ID: " << patients[patient_count].id << endl;
                            patient_count++;
                        } else {
                            cout << "Patient records are full." << endl;
                        }
                        break;
                    }
                    case 2: {
                        cout << "Schedule Appointment" << endl;
                        cout << "Enter Patient ID: ";
                        cin >> patient_id;
                        bool found = false;
                        for (int i = 0; i < patient_count; i++) {
                            if (patients[i].id == patient_id) {
                                found = true;
                                cout << "Enter Appointment Date (YYYY-MM-DD): ";
                                string date_input;
                                cin >> date_input;
                               // ??????
                                regex date_pattern(R"(\d{4}-\d{2}-\d{2})");
                                while (!regex_match(date_input, date_pattern)) {
                                    cout << "Invalid date format. Please enter the date in YYYY-MM-DD format: ";
                                    cin >> date_input;
                                }
                                patients[i].apt.appointment_date = date_input;
                                cout << "Enter a brief description of the patient: ";
                                cin.ignore();
                                getline(cin, patients[i].apt.description);

                                fstream set_appointment("Appointments.txt", ios::app);
                                if (set_appointment.is_open()) {
                                    set_appointment << left;
                                    set_appointment << setw(10) << patients[i].id << '\t'
                                                    << setw(20) << patients[i].apt.appointment_date << '\t'
                                                    << setw(150) << patients[i].apt.description << '\n';
                                    cout << "Appointment scheduled successfully!" << endl;
                                    set_appointment.close();
                                } else {
                                    cout << "Failed to schedule appointment, try again!" << endl;
                                }
                                break;
                            }
                        }
                        if (!found) {
                            cout << "Patient not found." << endl;
                        }
                        break;
                    }
                    case 3: {
                        cout << "Check Appointment Records" << endl;
                        cout << "Enter Patient ID to view appointment records: ";
                        cin >> patient_id;
                        bool found = false;
                        for (int i = 0; i < patient_count; i++) {
                            if (patients[i].id == patient_id) {
                                found = true;
                                cout << "Patient ID: " << patients[i].id << '\n'
                                     << "Patient Name: " << patients[i].name << '\n';
                                if (patients[i].apt.appointment_date.empty()) {
                                    cout << "No appointment scheduled." << '\n';
                                } else {
                                    cout << "Appointment Date: " << patients[i].apt.appointment_date << '\n';
                                }
                                break;
                            }
                        }
                        if (!found) {
                            cout << "No records found for this Patient ID." << endl;
                        }
                        break;
                    }
                    case 4:
                        cout << "Electronic Medical Records\n" << endl;
                        cout << "Which record would you like to see\n";
                        cout << "1. Patient Record\n"
                             << "2. Appointment Record\n"
                             << "3. Exit\n";
                        int choice9;
                        cin >> choice9;
                        if(cin.fail()){
                            cout << "Invalid Input! Try Again.\n";
                        }
                        switch(choice9){
                            case 1:
                                cout << left;
                                cout << setw(32) << "Patient Name" << " | "
                                     << setw(10) << "ID" << " | "
                                     << setw(3)  << "Age\n";

                                for(int i=0; i<patient_count; i++){
                                    cout << left;
                                    cout << setw(32) << patients[i].name << " | "
                                         << setw(10) << patients[i].id << " | "
                                         << setw(3)  << patients[i].age << '\n';
                                }
                                break;
                            case 2:
                                cout << left;
                                cout << setw(32) << "Name" << " | "
                                     << setw(10) << "ID" << " | "
                                     << setw(20) << "Appointment Date" << " | "
                                     << setw(150) << "Description" <<'\n';
                                for(int i=0; i < patient_count; i++){
                                    cout << left;
                                    cout << setw(32) << patients[i].name << " | "
                                         << setw(10) << patients[i].id << " | "
                                         << setw(20) << patients[i].apt.appointment_date << " | "
                                         << setw(100) << patients[i].apt.description << endl;
                                }
                                break;
                            case 3:
                                cout << "Exiting the program...";
                                return 0;
                            default:
                                cout << "Invalid choice. Please try again.";
                        }
                        break;
                    case 5:
                        cout << "Exiting..." << endl;
                        return 0; // Exit the program
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                }
                break;
            }

case 2:
    staff_menu();
    break;

case 3:
    lab_and_equipment_menu();
    break;

case 4:
    pharmacy_menu();
    break;

case 5:
    while (true)
    {
        int choice4;
        cout << "\n========== Billing Management ==========" << endl;
        cout << "1. Generate Bill" << endl;
        cout << "2. Insurance Claims" << endl;
        cout << "3. Payment Processing" << endl;
        cout << "4. View All Billing Records" << endl;
        cout << "5. Exit to Main Menu" << endl;
        cout << "========================================" << endl;
        cout << "Please enter your choice: ";
        cin >> choice4;

        switch (choice4)
        {
        case 1:
            cout << "\n--- Generate Bill ---" << endl;
            cout << "Enter Patient ID: ";
            cin >> billings[billing_count].patient_id;

            {
                bool patient_found = false;
                for (int i = 0; i < patient_count; i++)
                {
                    if (patients[i].id == billings[billing_count].patient_id)
                    {
                        patient_found = true;
                        break;
                    }
                }

                if (!patient_found)
                {
                    cout << "Patient not found. Please register the patient first." << endl;
                    break;
                }

                cout << "Enter Bill Amount: ";
                while (!(cin >> billings[billing_count].amount) || billings[billing_count].amount <= 0)
                {
                    cout << "Invalid amount. Please enter a positive number: ";
                    cin.clear();
                    cin.ignore();
                }

                billings[billing_count].status = "Unpaid";

                fstream billingFile("Billing Records.txt", ios::in | ios::out | ios::app);
                if (billingFile.is_open())
                {
                    billingFile.seekp(0, ios::end);
                    if (billingFile.tellp() == 0)
                    {
                        billingFile << "Patient ID\tAmount\tStatus\n";
                    }
                    billingFile << billings[billing_count].patient_id << "\t"
                                << fixed << setprecision(2) << billings[billing_count].amount << "\t"
                                << billings[billing_count].status << "\n";
                    billingFile.close();
                }
                else
                {
                    cout << "Error: Unable to open billing file." << endl;
                }

                cout << "Bill generated successfully!" << endl;
                billing_count++;
            }
            break;

        case 2:
            cout << "\n--- Insurance Claims ---" << endl;
            cout << "Enter Patient ID: ";
            cin >> patient_id;
            {
                bool bill_found = false;
                for (int i = 0; i < billing_count; i++)
                {
                    if (billings[i].patient_id == patient_id)
                    {
                        bill_found = true;
                        cout << "Processing insurance claim for Patient ID: " << patient_id << endl;
                        cout << "Bill Amount: " << fixed << setprecision(2) << billings[i].amount << endl;
                        cout << "Insurance claim approved for the full amount." << endl;
                        billings[i].status = "Paid (Insurance)";
                        break;
                    }
                }

                if (!bill_found)
                {
                    cout << "No bill found for the given Patient ID." << endl;
                }
            }
            break;

        case 3:
            cout << "\n--- Payment Processing ---" << endl;
            cout << "Enter Patient ID: ";
            cin >> patient_id;
            {
                bool bill_found = false;
                for (int i = 0; i < billing_count; i++)
                {
                    if (billings[i].patient_id == patient_id)
                    {
                        bill_found = true;
                        cout << "Processing payment for Patient ID: " << patient_id << endl;
                        cout << "Bill Amount: " << fixed << setprecision(2) << billings[i].amount << endl;

                        float payment;
                        cout << "Enter payment amount: ";
                        while (!(cin >> payment) || payment <= 0)
                        {
                            cout << "Invalid amount. Please enter a positive number: ";
                            cin.clear();
                            cin.ignore();
                        }

                        if (payment >= billings[i].amount)
                        {
                            cout << "Payment successful! Change: " << fixed << setprecision(2) << (payment - billings[i].amount) << endl;
                            billings[i].status = "Paid";
                        }
                        else
                        {
                            cout << "Insufficient payment. Please pay the full amount." << endl;
                        }
                        break;
                    }
                }

                if (!bill_found)
                {
                    cout << "No bill found for the given Patient ID." << endl;
                }
            }
            break;

        case 4:
            cout << "\n--- View All Billing Records ---" << endl;
            if (billing_count == 0)
            {
                cout << "No billing records found." << endl;
            }
            else
            {
                cout << left << setw(15) << "Patient ID"
                     << setw(10) << "Amount"
                     << setw(15) << "Status" << endl;
                cout << "----------------------------------------" << endl;
                for (int i = 0; i < billing_count; i++)
                {
                    cout << left << setw(15) << billings[i].patient_id
                         << setw(10) << fixed << setprecision(2) << billings[i].amount
                         << setw(15) << billings[i].status << endl;
                }
            }
            break;

        case 5:
            cout << "Exiting Billing Management..." << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }

        char next_action;
        cout << "\nWould you like to return to Billing Management (B) or Main Menu (M)? ";
        cin >> next_action;
        if (next_action == 'M' || next_action == 'm')
        {
            break;
        }
    }
    break;

case 6:
{
    cout << "Reports and Analytics" << endl;
    int choice5;
    cout << "1. Patient Statistics" << endl;
    cout << "2. Staff Performance" << endl;
    cout << "3. Financial Reports" << endl;
    cout << "4. Exit" << endl;
    cout << "Please enter your choice: ";
    cin >> choice5;

    switch (choice5)
    {
    case 1:
        cout << "Patient Statistics" << endl;
        // Add code
        break;
    case 2:
        cout << "Staff Performance" << endl;
        // Add code
        break;
    case 3:
        cout << "Financial Reports" << endl;
        // Add code
        break;
    case 4:
        cout << "Exiting..." << endl;
        return 0;
    default:
        cout << "Invalid choice. Please try again." << endl;
    }
    break;
}

case 7:
{
    cout << "Feedback" << endl;
    int choice6;
    cout << "1. Patient Feedback" << endl;
    cout << "2. Staff Feedback on Management" << endl;
    cout << "3. Exit" << endl;
    cout << "Please enter your choice: ";
    cin >> choice6;

switch (choice6)
{
case 7:
{
    cout << "Feedback" << endl;
    int choice6;
    cout << "1. Patient Feedback" << endl;
    cout << "2. Staff Feedback on Management" << endl;
    cout << "3. Exit" << endl;
    cout << "Please enter your choice: ";
    cin >> choice6;

    switch (choice6)
    {
    case 1: {
        cout << "Patient Feedback" << endl;
        string pid;
        cout << "Enter Patient ID: ";
        cin >> pid;
        
        bool found_patient = false;
        for(int i=0; i<patient_count; i++) {
            if(patients[i].id == pid) {
                found_patient = true;
                Feedback fb;
                fb.user_id = pid;
                
                cout << "Rate our service (1-5): ";
                while(!(cin >> fb.rating) || fb.rating < 1 || fb.rating > 5) {
                    cout << "Invalid! Enter 1-5: ";
                    cin.clear();
                    cin.ignore();
                }
                
                cin.ignore();
                cout << "Comments (optional): ";
                getline(cin, fb.comment);
                
                // Get current date
                time_t now = time(0);
                tm* t = localtime(&now);

                char buf[20];
                strftime(buf, sizeof(buf), "%Y-%m-%d", t);
                fb.date = buf;
                
                // Save to file
                fstream file("Feedback.txt", ios::app);
                if(file.is_open()) {
                    if(file.tellp() == 0)
                        file << "ID\tType\tRating\tComment\tDate\n";
                    
                    file << pid << "\tPatient\t" 
                         << fb.rating << "\t"
                         << fb.comment << "\t"
                         << fb.date << "\n";
                    cout << "Thank you!\n";
                }
                break;
            }
        }
        if(!found_patient) {
            cout << "Patient not found!\n";
        }
        break;
    }
    
    case 2: {
        cout << "Staff Feedback on Management" << endl;
        int sid;
        cout << "Enter Staff ID: ";
        cin >> sid;
        
        bool found_staff = false;
        for(const auto& s : staff_list) {
            if(s.id == sid) {
                found_staff = true;
                Feedback fb;
                fb.user_id = to_string(sid);
                
                cout << "Rate management (1-5): ";
                while(!(cin >> fb.rating) || fb.rating < 1 || fb.rating > 5) {
                    cout << "Invalid! Enter 1-5: ";
                    cin.clear();
                    cin.ignore();
                }
                
                cin.ignore();
                cout << "Suggestions (optional): ";
                getline(cin, fb.comment);
                
                // Get current date
                time_t now = time(0);
                tm* t = localtime(&now);
                char buf[20];
                strftime(buf, sizeof(buf), "%Y-%m-%d", t);
                fb.date = buf;
                
                // Save to file
                fstream file("Feedback.txt", ios::app);
                if(file.is_open()) {
                    if(file.tellp() == 0)
                        file << "ID\tType\tRating\tComment\tDate\n";
                    
                    file << sid << "\tStaff\t" 
                         << fb.rating << "\t"
                         << fb.comment << "\t"
                         << fb.date << "\n";
                    cout << "Thank you!\n";
                }
                break;
            }
        }
        if(!found_staff) cout << "Staff not found!\n";
        break;
    }
    
    case 3:
        cout << "Exiting Feedback menu..." << endl;
        break;
    
    default:
        cout << "Invalid choice. Please try again." << endl;
    }
}
case 8:
    cout << "Exiting..." << endl;
    return 0;

default:
    cout << "Invalid choice. Please try again." << endl;
}
