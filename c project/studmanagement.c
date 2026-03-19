 #include<stdio.h>
#include<string.h>
struct Student{
    int roll;
    char name[50];
    char address[100];
    char faculty[20];
    char phone[15];
};

void add() {
    FILE *fp = fopen("student.dat","ab");
    struct Student s;

printf("          ADD STUDENT RECORD\n");
 printf("----------------------------------------------------------\n");
 printf("  Roll No   : ");
 scanf("%d", &s.roll);
 printf("  Name      : "); 
 scanf(" %[^\n]", s.name);
 printf("  Phone     : "); 
 scanf("%s", s.phone);
 printf("  Faculty   : ");
 scanf(" %[^\n]", s.faculty);
 printf("  Address   : ");
 scanf(" %[^\n]", s.address);
 printf("\n");
 printf("----------------------------------------------------------\n");
    fwrite(&s,sizeof(s),1,fp);
    fclose(fp);
    printf("  Student added successfully!\n");
}

void display() {
    FILE *fp = fopen("student.dat","rb");
    struct Student s[100],temp;
    int c=0,i,j;
    if (fp == NULL) {
        printf("No records of student found.");
        return;
    }
    while (fread(&s[c], sizeof(struct Student),1,fp)) {
        c++;
    }
    fclose(fp);
    if (c==0) {
        printf("No records found.");
        return;
    }
    for(i=0;i<c-1;i++) {
        for(j=0;j<c-i-1;j++) {
            if(strcmp(s[j].name,s[j+1].name)>0){
                temp = s[j];
                s[j] = s[j+1];
                s[j+1] = temp;
            }
        }
    }
    printf("-----------------------------------------------\n");
    printf("            STUDENT MANAGEMENT SYSTEM\n");
    printf("\n");
    printf("  %-6s %-20s %-15s %-15s %-s\n","Roll", "Name", "Phone", "Faculty", "Address");
printf("----------------------------------------------------------\n");
for (i = 0; i < c; i++) {
    printf("  %-6d %-20s %-15s %-15s %-s\n",s[i].roll, s[i].name, s[i].phone, s[i].faculty, s[i].address);
}
    printf("----------------------------------------------------------\n");
printf("  Total Students: %d\n", c);
printf("----------------------------------------------------------\n");
printf("\n  Press Enter to return to main menu...");
getchar();
getchar();
}

void update() {
    FILE *fp = fopen("student.dat", "rb+");
    struct Student s;
    int roll, found = 0;
    printf("Enter Roll Number to update: ");
    scanf("%d", &roll);
    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("Enter new Name: ");
            scanf(" %[^\n]", s.name);
            printf("Enter new Faculty: ");
            scanf(" %[^\n]", s.faculty);
            printf("Enter new Address: ");
            scanf(" %[^\n]s", s.address);
            printf("Enter new Phone number: ");
            scanf(" %[^\n]s", s.phone);
            fseek(fp,-sizeof(s), SEEK_CUR);
            fwrite(&s,sizeof(s), 1, fp);
            found = 1;
            printf("Record updated successfully!\n");
            break;
        }
    }
    if(!found) printf("Student not found!\n");
    fclose(fp);
}
void delete() {
    FILE *fp = fopen("student.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    struct Student s;
    int roll, found = 0;
    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll);
    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            found = 1;
            continue;
        }
        fwrite(&s, sizeof(s), 1, temp);
    }
    fclose(fp);
    fclose(temp);
    remove("student.dat");
    rename("temp.dat","student.dat");
    if(found) printf("Student deleted successfully!\n");
    else printf("Student not found!\n");
}
int main(){
    int choice;
    do{
    printf("        STUDENT MANAGEMENT SYSTEM\n");
    printf("  [1]  Add Student\n");
    printf("  [2]  Display All Students\n");
    printf("  [3]  Update Student\n");
    printf("  [4]  Delete Student\n");
    printf("  [5]  Exit\n\n");
    printf("  Enter your choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                add(); 
                break;
             case 2: 
                display(); 
                break;
            case 3: 
                update(); 
                break;
            case 4:
                delete(); 
                break;
            case 5: 
                printf("BYE BYE!\n"); 
                break;
            default: 
                printf("Invalid choice!(Press between 1-5)\n");
        }
    } while (choice!= 5);
    return 0;
}