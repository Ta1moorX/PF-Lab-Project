#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//1: defining structures (9 total)

// 1st struct: Student
typedef struct {
    char student_id[15];
    char name[50];
    char section[10];
    char batch[10];
    char campus[30];
    char address[100];
    long long cnic;
    char gender[10];
    char email[50];
} Student;

// 2nd struct: Transcript (Course Enrollment/Grade Record)
typedef struct { 
    char student_id[15];
    char course_code[10]; 
    char course_name[50]; 
    char section[10]; 
    int credit_hrs; 
    char grade[5]; 
} Transcript;

// 3rd struct: Teacher
typedef struct { 
    char teacher_name[50];
    char course[50]; 
    char sections[50]; 
} Teacher;

// 4th struct: Attendance
typedef struct {
    char student_id[15];
    char course_code[10]; 
    int lecture_no; 
    float duration; 
    int date; 
    char presence[15]; 
} Attendance;

// 5th struct: StudentMarks
typedef struct { 
    char student_id[15];
    char course_code[10];
    char marks_for[50]; 
    int weightage; 
    int obtained_marks; 
    int total_marks; 
    float average; 
    float minimum; 
    float maximum; 
} StudentMarks;

// 6th struct: RetakeRequest (Module 6)
typedef struct {
    char student_id[15];
    char course_code[10];
    char reason[100];
    char status[15];
} RetakeRequest;

// 7th struct: FinancialRecord (Module 8)
typedef struct {
    char student_id[15];
    char fee_type[50];
    int amount_due;
    int amount_paid;
    int date_paid;
    char status[15];
} FinancialRecord;

// 8th struct: CourseFeedback (Module 9)
typedef struct {
    char student_id[15];
    char course_code[10];
    char teacher_name[50];
    int rating_teaching;
    int rating_material;
    char comments[150];
} CourseFeedback;

// 9th Master Struct: SystemData (Module 10 - for file storage) stores all data of the other structs (students transcripts, teachers, attendance, marks, retake requests, financial records, feedback)
typedef struct {
    Student students[10];
    int student_count;
    
    Transcript course_transcripts[10];
    int course_enrollment_count;
    
    Teacher faculty[10];
    int teacher_count;
    
    Attendance lecture_attendance[10];
    int attendance_count;
    
    StudentMarks assessment_marks[10];
    int marks_count;

    RetakeRequest retake_requests[10];
    int retake_request_count;

    FinancialRecord financial_records[10];
    int financial_record_count;
    
    CourseFeedback feedback_records[10];
    int feedback_count;
} SystemData;

// 2: declaring global arrays and counters for all modules

Student students[10];
Transcript course_transcripts[10];
Teacher faculty[10];
Attendance lecture_attendance[10];
StudentMarks assessment_marks[10];
RetakeRequest retake_requests[10];
FinancialRecord financial_records[10];
CourseFeedback feedback_records[10];

int student_count = 0; 
int course_enrollment_count = 0; 
int teacher_count = 0; 
int attendance_count = 0; 
int marks_count = 0;
int retake_request_count = 0;
int financial_record_count = 0;
int feedback_count = 0;

// 3: function declarations for all modules
void display_menu();
int find_student_by_id(char student_id[]);
int find_enrollment(char student_id[], char course_code[]);
int find_teacher_by_name(char teacher_name[]);
int find_marks_record(char student_id[], char course_code[], char marks_for[]);
int find_retake_request(char student_id[], char course_code[]);
int find_financial_record(char student_id[], char fee_type[]);
void student_submenu();
void add_student();
void view_all_students();
void update_student_details(int index);
void delete_student_record(int index);
void course_enrollment_submenu();
void add_course_enrollment();
void view_all_enrollments();
void withdraw_student_from_course(int index);
float calculate_course_percentage(char student_id[], char course_code[]);
void calculate_and_update_grade();
void teacher_submenu();
void add_teacher();
void view_all_teachers();
void update_teacher_details(int index);
void delete_teacher_record(int index);
void attendance_submenu();
void mark_attendance();
void view_all_attendance();
void view_attendance_report();
void exam_results_submenu();
void add_exam_result();
void view_all_exam_results();
void update_marks_record(int index);
void view_result_summaries();
void retake_request_submenu();
void submit_retake_request();
void view_all_retake_requests();
void approve_reject_request(int index);
void transcript_submenu();
void generate_basic_transcript();
void financial_records_submenu();
void add_fee_record();
void view_all_financial_records();
void process_fee_payment(int index);
void check_student_dues();
void course_feedback_submenu();
void submit_feedback();
void view_all_feedback();
void view_average_ratings();
void file_storage_submenu();
void save_data_to_file();
void load_data_from_file();

// functions definitions from module 1 to module 10

// search functions for various modules
int find_student_by_id(char student_id[]) {
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].student_id, student_id) == 0) return i;
    }
    return -1;
}
int find_enrollment(char student_id[], char course_code[]) {
    for (int i = 0; i < course_enrollment_count; i++) {
        if (strcmp(course_transcripts[i].student_id, student_id) == 0 &&
            strcmp(course_transcripts[i].course_code, course_code) == 0) return i;
    }
    return -1;
}
int find_teacher_by_name(char teacher_name[]) {
    for (int i = 0; i < teacher_count; i++) {
        if (strcmp(faculty[i].teacher_name, teacher_name) == 0) return i;
    }
    return -1;
}
int find_marks_record(char student_id[], char course_code[], char marks_for[]) {
    for (int i = 0; i < marks_count; i++) {
        StudentMarks m = assessment_marks[i];
        if (strcmp(m.student_id, student_id) == 0 &&
            strcmp(m.course_code, course_code) == 0 &&
            strcmp(m.marks_for, marks_for) == 0) return i;
    }
    return -1;
}
int find_retake_request(char student_id[], char course_code[]) {
    for (int i = 0; i < retake_request_count; i++) {
        RetakeRequest r = retake_requests[i];
        if (strcmp(r.student_id, student_id) == 0 &&
            strcmp(r.course_code, course_code) == 0) return i;
    }
    return -1;
}
int find_financial_record(char student_id[], char fee_type[]) {
    for (int i = 0; i < financial_record_count; i++) {
        FinancialRecord f = financial_records[i];
        if (strcmp(f.student_id, student_id) == 0 &&
            strcmp(f.fee_type, fee_type) == 0) return i;
    }
    return -1;
}

// module 1 : student information management
void add_student() {
    if (student_count >= 10) { printf("\nERROR: Maximum student capacity (10) reached.\n"); return; }
    printf("\n--- Entering New Student Information ---\n");
    Student *s = &students[student_count];
    while (getchar() != '\n'); 
    printf("Enter Student ID (e.g., 25K0096): "); scanf("%s", s->student_id); while (getchar() != '\n');
    printf("Enter Name (use '_' instead of spaces): "); scanf("%s", s->name); while (getchar() != '\n');
    printf("Enter Section (e.g., BAI-1B): "); scanf("%s", s->section); while (getchar() != '\n');
    printf("Enter Batch (e.g., 2025): "); scanf("%s", s->batch); while (getchar() != '\n');
    printf("Enter Campus: "); scanf("%s", s->campus); while (getchar() != '\n');
    printf("Enter Address (use '_' instead of spaces): "); scanf("%s", s->address); while (getchar() != '\n');
    printf("Enter Gender (Male/Female): "); scanf("%s", s->gender); while (getchar() != '\n');
    printf("Enter Email: "); scanf("%s", s->email); while (getchar() != '\n');
    printf("Enter CNIC (13 digits, no dashes): ");
    if (scanf("%lld", &s->cnic) != 1) { printf("\nWARNING: Invalid CNIC format. Student record discarded.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n');
    student_count++;
    printf("\nSuccess! Student **%s** (%s) added. Total Students: %d\n", s->name, s->student_id, student_count);
}
void view_all_students() {
    if (student_count == 0) { printf("\nINFO: The student record system is currently **empty**.\n"); return; }
    printf("\n========================================================\n");
    printf("           Currently Stored Student Records (%d)\n", student_count);
    printf("========================================================\n");
    for (int i = 0; i < student_count; i++) {
        Student s = students[i];
        printf("\n--- Record %d ---\n", i + 1);
        printf("ID/Name:     %s - %s\n", s.student_id, s.name);
        printf("Batch/Sec:   %s (%s)\n", s.batch, s.section);
        printf("Campus/Gen:  %s, %s\n", s.campus, s.gender);
        printf("CNIC:        %lld\n", s.cnic);
        printf("Email:       %s\n", s.email);
    }
    printf("========================================================\n");
}
void update_student_details(int index) {
    int field_choice;
    Student *s = &students[index];
    printf("\n--- Updating Student: %s (%s) ---\n", s->name, s->student_id);
    printf("Which field do you want to update?\n");
    printf("   1. Name (Current: %s)\n", s->name); printf("   2. Section (Current: %s)\n", s->section);
    printf("   3. Batch (Current: %s)\n", s->batch); printf("   4. Campus (Current: %s)\n", s->campus);
    printf("   5. Address (Current: %s)\n", s->address); printf("   6. CNIC (Current: %lld)\n", s->cnic);
    printf("   7. Gender (Current: %s)\n", s->gender); printf("   8. Email (Current: %s)\n", s->email);
    printf("   9. Cancel Update\n"); printf("Enter choice (1-9): ");
    if (scanf("%d", &field_choice) != 1) { printf("\nWARNING: Invalid input. Update cancelled.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n'); printf("\n");
    switch (field_choice) {
        case 1: printf("Enter NEW Name: "); scanf("%s", s->name); printf("Success: Name updated.\n"); break;
        case 2: printf("Enter NEW Section: "); scanf("%s", s->section); printf("Success: Section updated.\n"); break;
        case 3: printf("Enter NEW Batch: "); scanf("%s", s->batch); printf("Success: Batch updated.\n"); break;
        case 4: printf("Enter NEW Campus: "); scanf("%s", s->campus); printf("Success: Campus updated.\n"); break;
        case 5: printf("Enter NEW Address: "); scanf("%s", s->address); printf("Success: Address updated.\n"); break;
        case 6: 
            printf("Enter NEW CNIC: ");
            if (scanf("%lld", &s->cnic) != 1) { printf("\nERROR: Invalid CNIC format. Update failed.\n"); } else { printf("Success: CNIC updated.\n"); }
            break;
        case 7: printf("Enter NEW Gender: "); scanf("%s", s->gender); printf("Success: Gender updated.\n"); break;
        case 8: printf("Enter NEW Email: "); scanf("%s", s->email); printf("Success: Email updated.\n"); break;
        case 9: printf("Update cancelled. Returning to submenu.\n"); break;
        default: printf("\nERROR: Invalid field choice. Update cancelled.\n");
    }
    while (getchar() != '\n'); 
}
void delete_student_record(int index) {
    if (index < 0 || index >= student_count) { printf("\nERROR: Invalid index provided for deletion.\n"); return; }
    printf("\nALERT: Deleting record for Student ID: %s, Name: %s...\n", students[index].student_id, students[index].name);
    for (int i = index; i < student_count - 1; i++) { students[i] = students[i + 1]; }
    student_count--;
    printf("Success: Record deleted successfully! Total Students: %d\n", student_count);
}
void student_submenu() {
    int sub_choice; char search_id[15]; int found_index;
    printf("\n--- Student Information Module ---\n");
    printf("   1. Add New Student\n"); printf("   2. View All Students\n");
    printf("3. Update Student Details\n"); printf("4. Delete Student Record\n");
    printf("   5. Back to Main Menu\n"); printf("Enter submenu choice (1-5): ");
    if (scanf("%d", &sub_choice) != 1) { printf("\nWARNING: Invalid input. Returning to main menu.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n');
    switch (sub_choice) {
        case 1: add_student(); break;
        case 2: view_all_students(); break;
        case 3:
            printf("\n--- Update Student Details ---\n"); printf("Enter Student ID to update: "); scanf("%s", search_id); while (getchar() != '\n');
            found_index = find_student_by_id(search_id);
            if (found_index != -1) { printf("\nSuccess: Student ID %s found! Loading update menu...\n", search_id); update_student_details(found_index); } else { printf("\nERROR: Student ID %s not found in records.\n", search_id); }
            break;
        case 4:
            printf("\n--- Delete Student Record ---\n"); printf("Enter Student ID to delete: "); scanf("%s", search_id); while (getchar() != '\n'); 
            found_index = find_student_by_id(search_id);
            if (found_index != -1) { delete_student_record(found_index); } else { printf("\nERROR: Student ID %s not found in records. Deletion cancelled.\n", search_id); }
            break;
        case 5: break;
        default: printf("\nERROR: Invalid submenu choice.\n");
    }
}

// module 2 : course enrollment management

void add_course_enrollment() {
    char student_id_input[15]; int student_exists_index;
    if (course_enrollment_count >= 10) { printf("\nERROR: Maximum course capacity (10) reached.\n"); return; }
    printf("\n--- Course Enrollment System ---\n"); printf("Enter Student ID to enroll in a course: ");
    if (scanf("%s", student_id_input) != 1) { printf("\nWARNING: Invalid ID input. Enrollment cancelled.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n');
    student_exists_index = find_student_by_id(student_id_input); 
    if (student_exists_index == -1) { printf("\nERROR: Student ID %s not found. Enrollment cancelled.\n", student_id_input); return; }
    Transcript *t = &course_transcripts[course_enrollment_count];
    strcpy(t->student_id, student_id_input);
    printf("Student %s is enrolled. Enter Course Details:\n", students[student_exists_index].name);
    printf("Enter Course Code (e.g., CL1000): "); scanf("%s", t->course_code); while (getchar() != '\n'); 
    printf("Enter Course Name: "); scanf("%s", t->course_name); while (getchar() != '\n');
    printf("Enter Section (e.g., BAI-1B): "); scanf("%s", t->section); while (getchar() != '\n');
    printf("Enter Credit Hours (int): ");
    if (scanf("%d", &t->credit_hrs) != 1) { printf("\nWARNING: Invalid Credit Hours. Enrollment cancelled.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n');
    strcpy(t->grade, "N/A");
    course_enrollment_count++;
    printf("\nSuccess! Student %s enrolled in course **%s**. Total Enrollments: %d\n", t->student_id, t->course_code, course_enrollment_count);
}
void view_all_enrollments() {
    if (course_enrollment_count == 0) { printf("\nINFO: The course enrollment record system is currently **empty**.\n"); return; }
    printf("\n========================================================\n");
    printf("         Current Course Enrollments (%d)\n", course_enrollment_count);
    printf("========================================================\n");
    for (int i = 0; i < course_enrollment_count; i++) {
        Transcript t = course_transcripts[i];
        printf("\n--- Enrollment Record %d ---\n", i + 1);
        printf("Student ID:    %s\n", t.student_id);
        printf("Course Code:   %s\n", t.course_code);
        printf("Course Name:   %s\n", t.course_name);
        printf("Section:       %s\n", t.section);
        printf("Credit Hrs:    %d\n", t.credit_hrs);
        printf("Current Grade: %s\n", t.grade);
    }
    printf("========================================================\n");
}
void withdraw_student_from_course(int index) {
    if (index < 0 || index >= course_enrollment_count) { printf("\nERROR: Invalid index provided for withdrawal.\n"); return; }
    printf("\nALERT: Withdrawing student %s from course %s...\n", course_transcripts[index].student_id, course_transcripts[index].course_code);
    for (int i = index; i < course_enrollment_count - 1; i++) { course_transcripts[i] = course_transcripts[i + 1]; }
    course_enrollment_count--;
    printf("Success: Withdrawal successful! Total Enrollments: %d\n", course_enrollment_count);
}

float calculate_course_percentage(char student_id[], char course_code[]) {
    int total_weightage = 0;
    float cumulative_weighted_score = 0.0;

    for (int i = 0; i < marks_count; i++) {
        StudentMarks m = assessment_marks[i];

        if (strcmp(m.student_id, student_id) == 0 && 
            strcmp(m.course_code, course_code) == 0) 
        {
            float score_contribution = ((float)m.obtained_marks / m.total_marks) * m.weightage;
            
            cumulative_weighted_score += score_contribution;
            total_weightage += m.weightage;
        }
    }
    
    if (total_weightage != 100) {
        if (total_weightage > 0) {
            return (cumulative_weighted_score / total_weightage) * 100.0;
        } else {
            return 0.0;
        }
    }
    
    return cumulative_weighted_score;
}

void calculate_and_update_grade() {
    char search_student_id[15];
    char search_course_code[10];
    int enrollment_index;
    
    printf("\n--- Calculate Final Grade and Update Transcript ---\n");
    printf("Enter Student ID: "); scanf("%s", search_student_id); while (getchar() != '\n');
    printf("Enter Course Code: "); scanf("%s", search_course_code); while (getchar() != '\n');

    enrollment_index = find_enrollment(search_student_id, search_course_code);
    if (enrollment_index == -1) {
        printf("\nERROR: Enrollment record for %s in %s not found.\n", search_student_id, search_course_code);
        return;
    }
    
    float final_percentage = calculate_course_percentage(search_student_id, search_course_code);
    
    Transcript *t = &course_transcripts[enrollment_index];
    char new_grade[5];
    
    if (final_percentage >= 89.5) {
        strcpy(new_grade, "A+");
    } else if (final_percentage >= 85.5) {
        strcpy(new_grade, "A");
    } else if (final_percentage >= 81.5) {
        strcpy(new_grade, "A-");
    } else if (final_percentage >= 77.5) {
        strcpy(new_grade, "B+");
    } else if (final_percentage >= 73.5) {
        strcpy(new_grade, "B");
    } else if (final_percentage >= 69.5) {
        strcpy(new_grade, "B-");
    } else if (final_percentage >= 65.5) {
        strcpy(new_grade, "C+");
    } else if (final_percentage >= 61.5) {
        strcpy(new_grade, "C");
    } else {
        strcpy(new_grade, "F"); 
    }

    strcpy(t->grade, new_grade);

    printf("\nSuccess! Grade calculated for **%s** in %s.\n", search_student_id, search_course_code);
    printf("   Final Percentage: %.2f%%\n", final_percentage);
    printf("   Final Grade Assigned: **%s**\n", t->grade);
}


void course_enrollment_submenu() {
    int sub_choice; char search_student_id[15]; char search_course_code[10]; int found_index;
    printf("\n--- Course Enrollment Module ---\n");
    printf("   1. Enroll Student in Course\n"); 
    printf("   2. View All Enrollments\n");
    printf("   3. Withdraw Student from Course\n");
    printf("   4. Calculate Final Grade and Update Transcript\n");
    printf("   5. Back to Main Menu\n");
    printf("Enter submenu choice (1-5): ");
    if (scanf("%d", &sub_choice) != 1) { printf("\nWARNING: Invalid input. Returning to main menu.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n'); 
    switch (sub_choice) {
        case 1: add_course_enrollment(); break;
        case 2: view_all_enrollments(); break;
        case 3:
            printf("\n--- Withdraw Student from Course ---\n");
            printf("Enter Student ID: "); scanf("%s", search_student_id); while (getchar() != '\n');
            printf("Enter Course Code: "); scanf("%s", search_course_code); while (getchar() != '\n');
            found_index = find_enrollment(search_student_id, search_course_code);
            if (found_index != -1) { withdraw_student_from_course(found_index); } else { printf("\nERROR: Enrollment record for Student ID %s in Course %s not found. Withdrawal cancelled.\n", search_student_id, search_course_code); }
            break;
        case 4: 
            calculate_and_update_grade(); 
            break;
        case 5: break;
        default: printf("\nERROR: Invalid submenu choice.\n");
    }
}
// module 3 : teacher information management

void add_teacher() {
    if (teacher_count >= 10) { printf("\nERROR: Maximum faculty capacity (10) reached.\n"); return; }
    printf("\n--- Entering New Teacher Information ---\n");
    Teacher *t = &faculty[teacher_count];
    while (getchar() != '\n'); 
    printf("Enter Teacher Name (use '_' for spaces): "); scanf("%s", t->teacher_name); while (getchar() != '\n');
    printf("Enter Assigned Course Name/Code: "); scanf("%s", t->course); while (getchar() != '\n');
    printf("Enter Assigned Sections (e.g., BAI-1A_BAI-1B): "); scanf("%s", t->sections); while (getchar() != '\n');
    teacher_count++;
    printf("\nSuccess! Teacher **%s** added to faculty. Total Teachers: %d\n", t->teacher_name, teacher_count);
}
void view_all_teachers() {
    if (teacher_count == 0) { printf("\nINFO: The faculty record system is currently **empty**.\n"); return; }
    printf("\n========================================================\n");
    printf("              Current Faculty Records (%d)\n", teacher_count);
    printf("========================================================\n");
    for (int i = 0; i < teacher_count; i++) {
        Teacher t = faculty[i];
        printf("\n--- Record %d ---\n", i + 1);
        printf("Name:        %s\n", t.teacher_name);
        printf("Course:      %s\n", t.course);
        printf("Sections:    %s\n", t.sections);
    }
    printf("========================================================\n");
}
void update_teacher_details(int index) {
    int field_choice; Teacher *t = &faculty[index];
    printf("\n--- Updating Assignment for Teacher: %s ---\n", t->teacher_name);
    printf("   1. Assigned Course (Current: %s)\n", t->course);
    printf("   2. Assigned Sections (Current: %s)\n", t->sections);
    printf("   3. Cancel Update\n"); printf("Enter choice (1-3): ");
    if (scanf("%d", &field_choice) != 1) { printf("\nWARNING: Invalid input. Update cancelled.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n'); printf("\n");
    switch (field_choice) {
        case 1: printf("Enter NEW Course Name/Code: "); scanf("%s", t->course); printf("Success: Course updated for %s.\n", t->teacher_name); break;
        case 2: printf("Enter NEW Sections: "); scanf("%s", t->sections); printf("Success: Sections updated for %s.\n", t->teacher_name); break;
        case 3: printf("Update cancelled. Returning to submenu.\n"); break;
        default: printf("\nERROR: Invalid field choice. Update cancelled.\n");
    }
    while (getchar() != '\n'); 
}
void delete_teacher_record(int index) {
    if (index < 0 || index >= teacher_count) { printf("\nERROR: Invalid index provided for deletion.\n"); return; }
    printf("\nALERT: Deleting record for Teacher Name: %s, Course: %s...\n", faculty[index].teacher_name, faculty[index].course);
    for (int i = index; i < teacher_count - 1; i++) { faculty[i] = faculty[i + 1]; }
    teacher_count--;
    printf("Success: Teacher record deleted successfully! Total Teachers: %d\n", teacher_count);
}
void teacher_submenu() {
    int sub_choice; char search_name[50]; int found_index;
    printf("\n--- Teacher Information Module ---\n");
    printf("   1. Add New Teacher\n"); printf("   2. View All Teachers\n");
    printf("   3. Update Teacher Assignment\n"); printf("   4. Delete Teacher Record\n");
    printf("   5. Back to Main Menu\n"); printf("Enter submenu choice (1-5): ");
    if (scanf("%d", &sub_choice) != 1) { printf("\nWARNING: Invalid input. Returning to main menu.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n'); 
    switch (sub_choice) {
        case 1: add_teacher(); break;
        case 2: view_all_teachers(); break;
        case 3:
            printf("\n--- Update Teacher Assignment ---\n"); printf("Enter Teacher Name to update (use '_' for spaces): "); scanf("%s", search_name); while (getchar() != '\n');
            found_index = find_teacher_by_name(search_name);
            if (found_index != -1) { printf("\nSuccess: Teacher **%s** found! Loading update menu...\n", search_name); update_teacher_details(found_index); } else { printf("\nERROR: Teacher **%s** not found in records.\n", search_name); }
            break;
        case 4:
            printf("\n--- Delete Teacher Record ---\n"); printf("Enter Teacher Name to delete (use '_' for spaces): "); scanf("%s", search_name); while (getchar() != '\n'); 
            found_index = find_teacher_by_name(search_name);
            if (found_index != -1) { delete_teacher_record(found_index); } else { printf("\nERROR: Teacher **%s** not found in records. Deletion cancelled.\n", search_name); }
            break;
        case 5: break;
        default: printf("\nERROR: Invalid submenu choice.\n");
    }
}

// module 4 : attendance management

void mark_attendance() {
    char student_id_input[15]; char course_code_input[10]; int student_exists_index;
    if (attendance_count >= 10) { printf("\nERROR: Maximum attendance capacity (10) reached.\n"); return; }
    printf("\n--- Mark Attendance System ---\n"); printf("Enter Student ID: ");
    if (scanf("%s", student_id_input) != 1) { printf("\nWARNING: Invalid ID input. Operation cancelled.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n');
    student_exists_index = find_student_by_id(student_id_input); 
    if (student_exists_index == -1) { printf("\nERROR: Student ID %s not found. Attendance marking cancelled.\n", student_id_input); return; }
    Attendance *a = &lecture_attendance[attendance_count];
    strcpy(a->student_id, student_id_input);
    printf("Student %s found. Enter Lecture Details:\n", students[student_exists_index].name);
    printf("Enter Course Code for lecture: "); scanf("%s", course_code_input); while (getchar() != '\n');
    strcpy(a->course_code, course_code_input);
    printf("Enter Lecture Number (int): ");
    if (scanf("%d", &a->lecture_no) != 1) { printf("\nWARNING: Invalid Lecture Number. Record discarded.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n');
    printf("Enter Date (YYYYMMDD): ");
    if (scanf("%d", &a->date) != 1) { printf("\nWARNING: Invalid Date format. Record discarded.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n');
    printf("Enter Presence (Present/Absent/Late): "); scanf("%s", a->presence); while (getchar() != '\n');
    a->duration = 2.0; 
    attendance_count++;
    printf("\nSuccess! Attendance recorded for Student %s in %s (Lec %d). Total Records: %d\n", a->student_id, a->course_code, a->lecture_no, attendance_count);
}
void view_all_attendance() {
    if (attendance_count == 0) { printf("\nINFO: The attendance record system is currently **empty**.\n"); return; }
    printf("\n========================================================\n");
    printf("              Current Attendance Records (%d)\n", attendance_count);
    printf("========================================================\n");
    for (int i = 0; i < attendance_count; i++) {
        Attendance a = lecture_attendance[i];
        printf("\n--- Record %d ---\n", i + 1);
        printf("Student ID:    %s\n", a.student_id);
        printf("Course/Lec:    %s (Lec %d)\n", a.course_code, a.lecture_no);
        printf("Date:          %d\n", a.date);
        printf("Status:        **%s**\n", a.presence);
    }
    printf("========================================================\n");
}
void view_attendance_report() {
    char course_code_input[10];
    printf("\n--- Course Attendance Report ---\n"); printf("Enter Course Code for report: ");
    if (scanf("%s", course_code_input) != 1) { printf("\nWARNING: Invalid input. Operation cancelled.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n');
    if (attendance_count == 0) { printf("\nINFO: No attendance records exist yet.\n"); return; }
    typedef struct { char student_id[15]; int present_count; int total_lectures; int found; } StudentReport;
    StudentReport report[10] = {0}; int report_index = 0;
    for (int i = 0; i < attendance_count; i++) {
        Attendance a = lecture_attendance[i];
        if (strcmp(a.course_code, course_code_input) == 0) {
            int student_found_in_report = -1;
            for (int j = 0; j < report_index; j++) {
                if (strcmp(report[j].student_id, a.student_id) == 0) { student_found_in_report = j; break; }
            }
            if (student_found_in_report == -1) {
                if (report_index < 10) {
                    strcpy(report[report_index].student_id, a.student_id); report[report_index].total_lectures = 1; 
                    if (strcmp(a.presence, "Present") == 0) { report[report_index].present_count = 1; } else { report[report_index].present_count = 0; }
                    report_index++;
                }
            } else {
                report[student_found_in_report].total_lectures++;
                if (strcmp(a.presence, "Present") == 0) { report[student_found_in_report].present_count++; }
            }
        }
    }
    if (report_index == 0) { printf("\nERROR: No attendance records found for course **%s**.\n", course_code_input); return; }
    printf("\n========================================================\n");
    printf("     Attendance Report for Course: **%s**\n", course_code_input);
    printf("========================================================\n");
    printf("ID          | Present | Total | Percentage\n");
    printf("------------|---------|-------|------------\n");
    for (int i = 0; i < report_index; i++) {
        StudentReport r = report[i];
        float percentage = (float)r.present_count / r.total_lectures * 100.0;
        printf("%-11s | %-7d | %-5d | %.2f%%\n", r.student_id, r.present_count, r.total_lectures, percentage);
    }
    printf("========================================================\n");
}
void attendance_submenu() {
    int sub_choice;
    printf("\n--- Attendance Management Module ---\n");
    printf("   1. Mark Attendance for a Student\n"); printf("   2. View All Attendance Records\n");
    printf("   3. View Attendance Report\n"); printf("   4. Back to Main Menu\n");
    printf("Enter submenu choice (1-4): ");
    if (scanf("%d", &sub_choice) != 1) { printf("\nWARNING: Invalid input. Returning to main menu.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n'); 
    switch (sub_choice) {
        case 1: mark_attendance(); break;
        case 2: view_all_attendance(); break;
        case 3: view_attendance_report(); break;
        case 4: break; 
        default: printf("\nERROR: Invalid submenu choice.\n");
    }
}

// module 5 : exam results management

void add_exam_result() {
    char student_id_input[15]; char course_code_input[10]; int student_exists_index;
    if (marks_count >= 10) { printf("\nERROR: Maximum marks capacity (10) reached.\n"); return; }
    printf("\n--- Add Exam Result System ---\n"); printf("Enter Student ID: ");
    if (scanf("%s", student_id_input) != 1) { printf("\nWARNING: Invalid ID input. Operation cancelled.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n');
    student_exists_index = find_student_by_id(student_id_input); 
    if (student_exists_index == -1) { printf("\nERROR: Student ID %s not found. Operation cancelled.\n"); return; }
    printf("Student %s found. Enter Course Code for marks entry: ", students[student_exists_index].name);
    scanf("%s", course_code_input); while (getchar() != '\n');
    StudentMarks *m = &assessment_marks[marks_count];
    strcpy(m->student_id, student_id_input); strcpy(m->course_code, course_code_input);
    printf("\n--- Entering Assessment Details ---\n");
    printf("Marks For (e.g., Mid1, Final): "); scanf("%s", m->marks_for); while (getchar() != '\n');
    printf("Total Marks for this assessment (int): ");
    if (scanf("%d", &m->total_marks) != 1) { printf("\nWARNING: Invalid Total Marks. Record discarded.\n"); while (getchar() != '\n'); return; } while (getchar() != '\n');
    printf("Weightage (e.g., 20%% as 20): ");
    if (scanf("%d", &m->weightage) != 1) { printf("\nWARNING: Invalid Weightage. Record discarded.\n"); while (getchar() != '\n'); return; } while (getchar() != '\n');
    printf("Obtained Marks (int): ");
    if (scanf("%d", &m->obtained_marks) != 1) { printf("\nWARNING: Invalid Obtained Marks. Record discarded.\n"); while (getchar() != '\n'); return; } while (getchar() != '\n');
    m->average = 0.0; m->minimum = 0.0; m->maximum = 0.0;
    marks_count++;
    printf("\nSuccess! Marks (%d/%d) recorded for Student %s in %s (%s). Total Records: %d\n", m->obtained_marks, m->total_marks, m->student_id, m->course_code, m->marks_for, marks_count);
}
void view_all_exam_results() {
    if (marks_count == 0) { printf("\nINFO: The exam results record system is currently **empty**.\n"); return; }
    printf("\n========================================================\n");
    printf("         Current Exam Results Records (%d)\n", marks_count);
    printf("========================================================\n");
    printf("ID         | Course | Assessment | Marks | Weightage\n");
    printf("-----------|--------|------------|-------|-----------\n");
    for (int i = 0; i < marks_count; i++) {
        StudentMarks m = assessment_marks[i];
        printf("%-10s | %-6s | %-10s | %-5d | %-8d%%\n", m.student_id, m.course_code, m.marks_for, m.obtained_marks, m.weightage);
    }
    printf("========================================================\n");
}
void update_marks_record(int index) {
    int field_choice; StudentMarks *m = &assessment_marks[index];
    printf("\n--- Editing Result for Student: %s in %s (%s) ---\n", m->student_id, m->course_code, m->marks_for);
    printf("Current Marks: %d / %d (Weightage: %d%%)\n", m->obtained_marks, m->total_marks, m->weightage);
    printf("\nWhich field do you want to update?\n");
    printf("   1. Obtained Marks\n"); printf("   2. Total Marks\n");
    printf("   3. Weightage\n"); printf("   4. Cancel Edit\n"); printf("Enter choice (1-4): ");
    if (scanf("%d", &field_choice) != 1) { printf("\nWARNING: Invalid input. Update cancelled.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n'); printf("\n");
    switch (field_choice) {
        case 1:
            printf("Enter NEW Obtained Marks (out of %d): ", m->total_marks);
            if (scanf("%d", &m->obtained_marks) != 1) { printf("\nERROR: Invalid input. Update failed.\n"); } else { printf("Success: Obtained Marks updated.\n"); }
            break;
        case 2:
            printf("Enter NEW Total Marks: ");
            if (scanf("%d", &m->total_marks) != 1) { printf("\nERROR: Invalid input. Update failed.\n"); } else { printf("Success: Total Marks updated.\n"); }
            break;
        case 3:
            printf("Enter NEW Weightage (%%): ");
            if (scanf("%d", &m->weightage) != 1) { printf("\nERROR: Invalid input. Update failed.\n"); } else { printf("Success: Weightage updated.\n"); }
            break;
        case 4: printf("Edit cancelled. Returning to submenu.\n"); break;
        default: printf("\nERROR: Invalid field choice. Update cancelled.\n");
    }
    while (getchar() != '\n'); 
}
void view_result_summaries() {
    char search_course_code[10]; char search_marks_for[50]; int count = 0; int total_sum = 0;
    int current_max = -1; int current_min = 99999; int total_possible_marks = 0;
    printf("\n--- View Result Summaries ---\n");
    if (marks_count == 0) { printf("\nINFO: No exam results have been recorded yet.\n"); return; }
    printf("Enter Course Code for summary: "); scanf("%s", search_course_code); while (getchar() != '\n');
    printf("Enter Assessment Name (e.g., Mid1, Final): "); scanf("%s", search_marks_for); while (getchar() != '\n');
    for (int i = 0; i < marks_count; i++) {
        StudentMarks m = assessment_marks[i];
        if (strcmp(m.course_code, search_course_code) == 0 && strcmp(m.marks_for, search_marks_for) == 0) {
            count++; total_sum += m.obtained_marks;
            if (m.obtained_marks > current_max) { current_max = m.obtained_marks; }
            if (m.obtained_marks < current_min) { current_min = m.obtained_marks; }
            if (total_possible_marks == 0) { total_possible_marks = m.total_marks; }
        }
    }
    if (count == 0) { printf("\nERROR: No results found for assessment **%s** in course **%s**.\n", search_marks_for, search_course_code); } 
    else {
        float average = (float)total_sum / count;
        printf("\n========================================================\n");
        printf("     Summary for %s in %s (Total Students: %d)\n", search_marks_for, search_course_code, count);
        printf("========================================================\n");
        printf("Total Possible Marks:  %d\n", total_possible_marks);
        printf("Class Average Marks:   %.2f\n", average);
        printf("Maximum Marks Scored:  %d\n", current_max);
        printf("Minimum Marks Scored:  %d\n", current_min);
        printf("========================================================\n");
    }
}
void exam_results_submenu() {
    int sub_choice; char search_student_id[15]; char search_course_code[10]; char search_marks_for[50]; int found_index;
    printf("\n--- Exam Results Module ---\n");
    printf("   1. Add New Exam Result\n"); printf("   2. View All Results\n");
    printf("   3. Update/Edit Result\n"); printf("   4. View Result Summaries\n");
    printf("   5. Back to Main Menu\n"); printf("Enter submenu choice (1-5): ");
    if (scanf("%d", &sub_choice) != 1) { printf("\nWARNING: Invalid input. Returning to main menu.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n'); 
    switch (sub_choice) {
        case 1: add_exam_result(); break;
        case 2: view_all_exam_results(); break;
        case 3:
            printf("\n--- Update/Edit Exam Result ---\n"); printf("Enter Student ID: "); scanf("%s", search_student_id); while (getchar() != '\n');
            printf("Enter Course Code: "); scanf("%s", search_course_code); while (getchar() != '\n');
            printf("Enter Assessment Name (e.g., Mid1, Final): "); scanf("%s", search_marks_for); while (getchar() != '\n');
            found_index = find_marks_record(search_student_id, search_course_code, search_marks_for);
            if (found_index != -1) { printf("\nSuccess: Marks record found! Loading update menu...\n"); update_marks_record(found_index); } else { printf("\nERROR: Marks record not found.\n"); }
            break;
        case 4: view_result_summaries(); break;
        case 5: break; 
        default: printf("\nERROR: Invalid submenu choice.\n");
    }
}

// module 6 : exam retake request management

void submit_retake_request() {
    char student_id_input[15]; int student_exists_index;
    if (retake_request_count >= 10) { printf("\nERROR: Maximum retake request capacity (10) reached.\n"); return; }
    printf("\n--- Submit Exam Retake Request ---\n"); printf("Enter Your Student ID: ");
    if (scanf("%s", student_id_input) != 1) { printf("\nWARNING: Invalid ID input. Operation cancelled.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n');
    student_exists_index = find_student_by_id(student_id_input); 
    if (student_exists_index == -1) { printf("\nERROR: Student ID %s not found. Request cancelled.\n"); return; }
    RetakeRequest *r = &retake_requests[retake_request_count];
    strcpy(r->student_id, student_id_input); strcpy(r->status, "Pending");
    printf("Requesting student %s. Enter details:\n", students[student_exists_index].name);
    printf("Enter Course Code for retake: "); scanf("%s", r->course_code); while (getchar() != '\n');
    printf("Enter Reason (use '_' for spaces, max 100 chars): "); scanf("%s", r->reason); while (getchar() != '\n');
    retake_request_count++;
    printf("\nSuccess! Retake request for course **%s** submitted. Status: %s. Total Requests: %d\n", r->course_code, r->status, retake_request_count);
}
void view_all_retake_requests() {
    if (retake_request_count == 0) { printf("\nINFO: There are **no retake requests** in the system.\n"); return; }
    printf("\n========================================================\n");
    printf("         Current Exam Retake Requests (%d)\n", retake_request_count);
    printf("========================================================\n");
    printf("No | Student ID | Course | Status   | Reason\n");
    printf("---|------------|--------|----------|----------------------------------\n");
    for (int i = 0; i < retake_request_count; i++) {
        RetakeRequest r = retake_requests[i];
        printf("%-2d | %-10s | %-6s | %-8s | %s\n", i + 1, r.student_id, r.course_code, r.status, r.reason);
    }
    printf("========================================================\n");
}
void approve_reject_request(int index) {
    int admin_choice; RetakeRequest *r = &retake_requests[index];
    printf("\n--- Reviewing Request %d ---\n", index + 1);
    printf("Student: %s\n", r->student_id); printf("Course:  %s\n", r->course_code);
    printf("Reason:  %s\n", r->reason); printf("Current Status: **%s**\n", r->status);
    printf("\nAction:\n"); printf("   1. Approve\n"); printf("   2. Reject\n");
    printf("   3. Cancel Review\n"); printf("Enter choice (1-3): ");
    if (scanf("%d", &admin_choice) != 1) { printf("\nWARNING: Invalid input. Review cancelled.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n'); 
    switch (admin_choice) {
        case 1: strcpy(r->status, "Approved"); printf("Success: Request **APPROVED**.\n"); break;
        case 2: strcpy(r->status, "Rejected"); printf("Success: Request **REJECTED**.\n"); break;
        case 3: printf("Review cancelled. Status remains **%s**.\n", r->status); break;
        default: printf("\nERROR: Invalid choice. Status remains **%s**.\n", r->status);
    }
    while (getchar() != '\n');
}
void retake_request_submenu() {
    int sub_choice; char search_student_id[15]; char search_course_code[10]; int found_index;
    printf("\n--- Exam Retake Request System ---\n");
    printf("   1. Submit New Retake Request\n"); printf("   2. View All Retake Requests\n");
    printf("   3. Approve/Reject Request (Admin)\n"); printf("   4. Back to Main Menu\n");
    printf("Enter submenu choice (1-4): ");
    if (scanf("%d", &sub_choice) != 1) { printf("\nWARNING: Invalid input. Returning to main menu.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n'); 
    switch (sub_choice) {
        case 1: submit_retake_request(); break;
        case 2: view_all_retake_requests(); break;
        case 3:
            printf("\n--- Approve/Reject Request ---\n"); printf("Enter Student ID: "); scanf("%s", search_student_id); while (getchar() != '\n');
            printf("Enter Course Code: "); scanf("%s", search_course_code); while (getchar() != '\n');
            found_index = find_retake_request(search_student_id, search_course_code);
            if (found_index != -1) { approve_reject_request(found_index); } else { printf("\nERROR: Request for Student ID %s in Course %s not found.\n", search_student_id, search_course_code); }
            break;
        case 4: break; 
        default: printf("\nERROR: Invalid submenu choice.\n");
    }
}

// module 7 : transcript generation

void generate_basic_transcript() {
    char search_student_id[15]; int student_index; int courses_found_count = 0;
    printf("\n--- Transcript Generator ---\n"); printf("Enter Student ID to generate transcript: ");
    if (scanf("%s", search_student_id) != 1) { printf("\nWARNING: Invalid ID input. Operation cancelled.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n');
    student_index = find_student_by_id(search_student_id);
    if (student_index == -1) { printf("\nERROR: Student ID %s not found in records.\n", search_student_id); return; }
    Student s = students[student_index];
    printf("\n========================================================\n");
    printf("         ACADEMIC TRANSCRIPT (UNOFFICIAL)\n");
    printf("========================================================\n");
    printf("Student Name:    %s\n", s.name); printf("Student ID:      %s\n", s.student_id);
    printf("Batch/Section:   %s / %s\n", s.batch, s.section); printf("Campus:          %s\n", s.campus);
    printf("--------------------------------------------------------\n"); printf("COURSE ENROLLMENT HISTORY:\n");
    printf("--------------------------------------------------------\n");
    printf("Code     | Course Name                        | Credit | Grade\n");
    printf("---------|------------------------------------|--------|--------\n");
    for (int i = 0; i < course_enrollment_count; i++) {
        Transcript t = course_transcripts[i];
        if (strcmp(t.student_id, search_student_id) == 0) {
            courses_found_count++;
            printf("%-8s | %-34s | %-6d | %-6s\n", t.course_code, t.course_name, t.credit_hrs, t.grade);
        }
    }
    if (courses_found_count == 0) { printf("--- No course enrollment records found for this student. ---\n"); }
    printf("========================================================\n");
}
void transcript_submenu() {
    int sub_choice;
    printf("\n--- Transcript Generator Module ---\n");
    printf("   1. Generate Basic Transcript (Student & Enrollment Data)\n");
    printf("   2. Generate Full Transcript (Includes Marks/Attendance - Not Implemented)\n");
    printf("   3. Back to Main Menu\n"); printf("Enter submenu choice (1-3): ");
    if (scanf("%d", &sub_choice) != 1) { printf("\nWARNING: Invalid input. Returning to main menu.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n'); 
    switch (sub_choice) {
        case 1: generate_basic_transcript(); break;
        case 2: printf("\n-- Full Transcript (Requires GPA/Attendance Aggregation) --\n"); break;
        case 3: break; 
        default: printf("\nERROR: Invalid submenu choice.\n");
    }
}

// module 8 : financial management

void add_fee_record() {
    char student_id_input[15]; int student_exists_index;
    if (financial_record_count >= 10) { printf("\nERROR: Maximum financial capacity (10) reached.\n"); return; }
    printf("\n--- Add New Fee Record ---\n"); printf("Enter Student ID: ");
    if (scanf("%s", student_id_input) != 1) { printf("\nWARNING: Invalid ID input. Operation cancelled.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n');
    student_exists_index = find_student_by_id(student_id_input); 
    if (student_exists_index == -1) { printf("\nERROR: Student ID %s not found. Record cancelled.\n"); return; }
    FinancialRecord *f = &financial_records[financial_record_count];
    strcpy(f->student_id, student_id_input);
    printf("Record for student %s. Enter details:\n", students[student_exists_index].name);
    printf("Fee Type (e.g., Tuition_Fee): "); scanf("%s", f->fee_type); while (getchar() != '\n');
    printf("Amount DUE (int): ");
    if (scanf("%d", &f->amount_due) != 1) { printf("\nWARNING: Invalid amount. Record discarded.\n"); while (getchar() != '\n'); return; } while (getchar() != '\n');
    printf("Amount PAID (int, enter 0 if none paid): ");
    if (scanf("%d", &f->amount_paid) != 1) { printf("\nWARNING: Invalid amount. Record discarded.\n"); while (getchar() != '\n'); return; } while (getchar() != '\n');
    if (f->amount_paid >= f->amount_due) { strcpy(f->status, "Cleared"); } else if (f->amount_paid > 0) { strcpy(f->status, "Partial"); } else { strcpy(f->status, "Pending"); }
    printf("Date of Payment (YYYYMMDD, enter 0 if no payment): ");
    if (scanf("%d", &f->date_paid) != 1) { printf("\nWARNING: Invalid date. Using 0.\n"); f->date_paid = 0; } while (getchar() != '\n');
    financial_record_count++;
    printf("\nSuccess! Fee record for **%s** created. Status: %s. Total Records: %d\n", f->fee_type, f->status, financial_record_count);
}
void view_all_financial_records() {
    if (financial_record_count == 0) { printf("\nINFO: There are **no financial records** in the system.\n"); return; }
    printf("\n========================================================\n");
    printf("         Current Fees & Financial Records (%d)\n", financial_record_count);
    printf("========================================================\n");
    printf("ID         | Fee Type          | Due ($) | Paid ($) | Pending ($) | Status   \n");
    printf("-----------|-------------------|---------|----------|-------------|----------\n");
    for (int i = 0; i < financial_record_count; i++) {
        FinancialRecord f = financial_records[i];
        int pending = f.amount_due - f.amount_paid;
        printf("%-10s | %-17s | %-7d | %-8d | %-11d | %-8s \n", f.student_id, f.fee_type, f.amount_due, f.amount_paid, pending, f.status);
    }
    printf("========================================================\n");
}
void process_fee_payment(int index) {
    int payment_amount; FinancialRecord *f = &financial_records[index];
    int pending_dues = f->amount_due - f->amount_paid;
    printf("\n--- Process Payment for Record: %s (%s) ---\n", f->student_id, f->fee_type);
    printf("Amount Due: %d | Amount Paid: %d | Remaining Dues: %d\n", f->amount_due, f->amount_paid, pending_dues);
    if (pending_dues <= 0) { printf("INFO: This fee record is already **CLEARED**. No further payment needed.\n"); return; }
    printf("Enter Payment Amount received (int): ");
    if (scanf("%d", &payment_amount) != 1) { printf("\nERROR: Invalid input. Payment cancelled.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n');
    f->amount_paid += payment_amount;
    if (f->amount_paid >= f->amount_due) { strcpy(f->status, "Cleared"); } else if (f->amount_paid > 0) { strcpy(f->status, "Partial"); } else { strcpy(f->status, "Pending"); }
    f->date_paid = 20251125; 
    printf("\nSuccess: Payment successful! New Amount Paid: %d.\n", f->amount_paid);
    printf("   Updated Status: **%s**.\n", f->status);
}
void check_student_dues() {
    char search_student_id[15]; int student_index; int total_remaining_dues = 0; int records_found = 0;
    printf("\n--- Check Dues for Student ---\n"); printf("Enter Student ID to check dues: ");
    if (scanf("%s", search_student_id) != 1) { printf("\nWARNING: Invalid ID input. Operation cancelled.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n');
    student_index = find_student_by_id(search_student_id);
    if (student_index == -1) { printf("\nERROR: Student ID %s not found in student records.\n", search_student_id); return; }
    for (int i = 0; i < financial_record_count; i++) {
        FinancialRecord f = financial_records[i];
        if (strcmp(f.student_id, search_student_id) == 0) {
            records_found++; int pending = f.amount_due - f.amount_paid; total_remaining_dues += pending;
        }
    }
    printf("\n========================================================\n");
    printf("       Dues Summary for: %s\n", students[student_index].name);
    printf("========================================================\n");
    if (records_found == 0) { printf("INFO: No financial records found for this student.\n"); } 
    else {
        printf("Total Financial Records Tracked: %d\n", records_found);
        printf("Total Amount Owed (Remaining Dues): **%d**\n", total_remaining_dues);
        if (total_remaining_dues > 0) { printf("ALERT: Student has outstanding balance.\n"); } else { printf("Success: All recorded dues are cleared.\n"); }
    }
    printf("========================================================\n");
}
void financial_records_submenu() {
    int sub_choice; char search_student_id[15]; char search_fee_type[50]; int found_index;
    printf("\n--- Fees & Financial Records Module ---\n");
    printf("   1. Add New Fee Record/Dues\n"); printf("   2. View All Financial Records\n");
    printf("   3. Process Fee Payment (Update Record)\n"); printf("   4. Check Dues for Student\n");
    printf("   5. Back to Main Menu\n"); printf("Enter submenu choice (1-5): ");
    if (scanf("%d", &sub_choice) != 1) { printf("\nWARNING: Invalid input. Returning to main menu.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n'); 
    switch (sub_choice) {
        case 1: add_fee_record(); break;
        case 2: view_all_financial_records(); break;
        case 3:
            printf("\n--- Process Fee Payment ---\n"); printf("Enter Student ID: "); scanf("%s", search_student_id); while (getchar() != '\n');
            printf("Enter Fee Type (e.g., Tuition_Fee): "); scanf("%s", search_fee_type); while (getchar() != '\n');
            found_index = find_financial_record(search_student_id, search_fee_type);
            if (found_index != -1) { process_fee_payment(found_index); } else { printf("\nERROR: Financial record for %s (%s) not found.\n", search_student_id, search_fee_type); }
            break;
        case 4: check_student_dues(); break;
        case 5: break; 
        default: printf("\nERROR: Invalid submenu choice.\n");
    }
}

// module 9 : course feedback management

void submit_feedback() {
    char student_id_input[15]; int student_exists_index;
    if (feedback_count >= 10) { printf("\nERROR: Maximum feedback capacity (10) reached.\n"); return; }
    printf("\n--- Submit Course Feedback ---\n"); printf("Enter Your Student ID: ");
    if (scanf("%s", student_id_input) != 1) { printf("\nWARNING: Invalid ID input. Operation cancelled.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n');
    student_exists_index = find_student_by_id(student_id_input); 
    if (student_exists_index == -1) { printf("\nERROR: Student ID %s not found. Submission cancelled.\n"); return; }
    CourseFeedback *f = &feedback_records[feedback_count];
    strcpy(f->student_id, student_id_input);
    printf("Feedback for student %s. Enter details:\n", students[student_exists_index].name);
    printf("Enter Course Code (e.g., CL1000): "); scanf("%s", f->course_code); while (getchar() != '\n');
    printf("Enter Teacher Name (use '_' for spaces): "); scanf("%s", f->teacher_name); while (getchar() != '\n');
    printf("\nRatings (1=Poor, 5=Excellent):\n");
    printf("Teaching Quality (1-5): ");
    if (scanf("%d", &f->rating_teaching) != 1 || f->rating_teaching < 1 || f->rating_teaching > 5) { printf("\nWARNING: Invalid rating. Using 1.\n"); f->rating_teaching = 1; } while (getchar() != '\n');
    printf("Course Material (1-5): ");
    if (scanf("%d", &f->rating_material) != 1 || f->rating_material < 1 || f->rating_material > 5) { printf("\nWARNING: Invalid rating. Using 1.\n"); f->rating_material = 1; } while (getchar() != '\n');
    printf("Enter Comments (use '_' for spaces, max 150 chars): "); scanf("%s", f->comments); while (getchar() != '\n');
    feedback_count++;
    printf("\nSuccess! Feedback for course **%s** submitted. Total Feedback: %d\n", f->course_code, feedback_count);
}
void view_all_feedback() {
    if (feedback_count == 0) { printf("\nINFO: There are **no feedback records** in the system.\n"); return; }
    printf("\n========================================================\n");
    printf("         Current Course Feedback Records (%d)\n", feedback_count);
    printf("========================================================\n");
    printf("ID | Course | Teacher          | Teaching | Material | Comments\n");
    printf("---|--------|------------------|----------|----------|----------------------------------\n");
    for (int i = 0; i < feedback_count; i++) {
        CourseFeedback f = feedback_records[i];
        printf("%-2d | %-6s | %-16s | %-8d | %-8d | %s\n", i + 1, f.course_code, f.teacher_name, f.rating_teaching, f.rating_material, f.comments);
    }
    printf("========================================================\n");
}
void view_average_ratings() {
    char search_course_code[10]; int count = 0; int total_teaching_sum = 0; int total_material_sum = 0;
    printf("\n--- View Average Ratings by Course ---\n");
    if (feedback_count == 0) { printf("\nINFO: No feedback has been submitted yet.\n"); return; }
    printf("Enter Course Code for average rating report: ");
    if (scanf("%s", search_course_code) != 1) { printf("\nWARNING: Invalid input. Operation cancelled.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n');
    for (int i = 0; i < feedback_count; i++) {
        CourseFeedback f = feedback_records[i];
        if (strcmp(f.course_code, search_course_code) == 0) {
            count++; total_teaching_sum += f.rating_teaching; total_material_sum += f.rating_material;
        }
    }
    if (count == 0) { printf("\nERROR: No feedback found for course **%s**.\n", search_course_code); } 
    else {
        float avg_teaching = (float)total_teaching_sum / count;
        float avg_material = (float)total_material_sum / count;
        printf("\n========================================================\n");
        printf("     Average Feedback for Course: %s (N=%d)\n", search_course_code, count);
        printf("========================================================\n");
        printf("Average Teaching Quality (1-5):  %.2f\n", avg_teaching);
        printf("Average Course Material (1-5):   %.2f\n", avg_material);
        printf("========================================================\n");
    }
}
void course_feedback_submenu() {
    int sub_choice;
    printf("\n--- Course Feedback Module ---\n");
    printf("   1. Submit New Feedback\n"); printf("   2. View All Feedback Records\n");
    printf("   3. View Average Ratings by Course\n"); printf("   4. Back to Main Menu\n");
    printf("Enter submenu choice (1-4): ");
    if (scanf("%d", &sub_choice) != 1) { printf("\nWARNING: Invalid input. Returning to main menu.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n'); 
    switch (sub_choice) {
        case 1: submit_feedback(); break;
        case 2: view_all_feedback(); break;
        case 3: view_average_ratings(); break;
        case 4: break; 
        default: printf("\nERROR: Invalid submenu choice.\n");
    }
}

// module 10 : file-based data storage

void save_data_to_file() {
    FILE *fp; SystemData data;
    memcpy(&data.students, students, sizeof(Student) * student_count); data.student_count = student_count;
    memcpy(&data.course_transcripts, course_transcripts, sizeof(Transcript) * course_enrollment_count); data.course_enrollment_count = course_enrollment_count;
    memcpy(&data.faculty, faculty, sizeof(Teacher) * teacher_count); data.teacher_count = teacher_count;
    memcpy(&data.lecture_attendance, lecture_attendance, sizeof(Attendance) * attendance_count); data.attendance_count = attendance_count;
    memcpy(&data.assessment_marks, assessment_marks, sizeof(StudentMarks) * marks_count); data.marks_count = marks_count;
    memcpy(&data.retake_requests, retake_requests, sizeof(RetakeRequest) * retake_request_count); data.retake_request_count = retake_request_count;
    memcpy(&data.financial_records, financial_records, sizeof(FinancialRecord) * financial_record_count); data.financial_record_count = financial_record_count;
    memcpy(&data.feedback_records, feedback_records, sizeof(CourseFeedback) * feedback_count); data.feedback_count = feedback_count;

    fp = fopen("ums_data.bin", "wb");
    if (fp == NULL) { printf("\nERROR: Could not open file for saving data.\n"); return; }
    fwrite(&data, sizeof(SystemData), 1, fp);
    fclose(fp);
    printf("\nSuccess! All data saved to **ums_data.bin**.\n");
}
void load_data_from_file() {
    FILE *fp; SystemData data;
    fp = fopen("ums_data.bin", "rb");
    if (fp == NULL) { printf("\nINFO: No previous save file (**ums_data.bin**) found. Starting fresh.\n"); return; }
    fread(&data, sizeof(SystemData), 1, fp);
    fclose(fp);

    student_count = data.student_count; memcpy(students, data.students, sizeof(Student) * student_count);
    course_enrollment_count = data.course_enrollment_count; memcpy(course_transcripts, data.course_transcripts, sizeof(Transcript) * course_enrollment_count);
    teacher_count = data.teacher_count; memcpy(faculty, data.faculty, sizeof(Teacher) * teacher_count);
    attendance_count = data.attendance_count; memcpy(lecture_attendance, data.lecture_attendance, sizeof(Attendance) * attendance_count);
    marks_count = data.marks_count; memcpy(assessment_marks, data.assessment_marks, sizeof(StudentMarks) * marks_count);
    retake_request_count = data.retake_request_count; memcpy(retake_requests, data.retake_requests, sizeof(RetakeRequest) * retake_request_count);
    financial_record_count = data.financial_record_count; memcpy(financial_records, data.financial_records, sizeof(FinancialRecord) * financial_record_count);
    feedback_count = data.feedback_count; memcpy(feedback_records, data.feedback_records, sizeof(CourseFeedback) * feedback_count);

    printf("\nSuccess! Data loaded from **ums_data.bin**.\n");
    printf("   Total records loaded: %d students, %d enrollments, etc.\n", student_count, course_enrollment_count);
}
void file_storage_submenu() {
    int sub_choice;
    printf("\n--- File-Based Data Storage Module ---\n");
    printf("   1. Save All Data to File\n"); printf("   2. Load All Data from File\n");
    printf("   3. Back to Main Menu\n"); printf("Enter submenu choice (1-3): ");
    if (scanf("%d", &sub_choice) != 1) { printf("\nWARNING: Invalid input. Returning to main menu.\n"); while (getchar() != '\n'); return; }
    while (getchar() != '\n'); 
    switch (sub_choice) {
        case 1: save_data_to_file(); break;
        case 2: load_data_from_file(); break;
        case 3: break; 
        default: printf("\nERROR: Invalid submenu choice.\n");
    }
}

// 5. Main Menu

void display_menu() {
    printf("\n========================================================\n");
    printf("        WELCOME TO FAST NUCES UMS (V2.1)\n");
    printf("        University Management System\n");
    printf("========================================================\n");
    printf("   1. Student Information Module\n");
    printf("   2. Course Enrollment Module\n");
    printf("   3. Teacher Information Module\n");
    printf("   4. Attendance Management\n");
    printf("   5. Exam Results Module\n");
    printf("   6. Exam Retake Request System\n");
    printf("   7. Transcript Generator\n");
    printf("   8. Fees & Financial Records\n");
    printf("   9. Course Feedback Module\n");
    printf("  10. File-Based Data Storage\n");
    printf("  11. Exit System\n");
    printf("========================================================\n");
    printf("Enter your choice (1-11): ");
}

int main() {
    int choice;
    
    load_data_from_file();
    
    do {
        display_menu();
        if (scanf("%d", &choice) != 1) {
            printf("\nWARNING: Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            choice = 0; 
            continue;
        }
        while (getchar() != '\n');
        switch (choice) {
            case 1: student_submenu(); break;
            case 2: course_enrollment_submenu(); break;
            case 3: teacher_submenu(); break;
            case 4: attendance_submenu(); break;
            case 5: exam_results_submenu(); break;
            case 6: retake_request_submenu(); break;
            case 7: transcript_submenu(); break;
            case 8: financial_records_submenu(); break;
            case 9: course_feedback_submenu(); break;
            case 10: file_storage_submenu(); break;
            case 11:
                save_data_to_file();
                printf("\nExiting FAST NUCES UMS. Goodbye!\n");
                break;
            default:
                printf("\nERROR: Invalid choice. Please enter a number between 1 and 11.\n");
        }
        if (choice != 11) {
            printf("\nPress ENTER to return to the main menu...");
            getchar(); 
        }
    } while (choice != 11);
    return 0;
}