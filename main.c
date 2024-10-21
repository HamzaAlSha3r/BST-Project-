// project 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 50
typedef struct BST * ptr;
typedef struct BST * tree;
struct BST {
    int id;
    char  name_st [size] ;
    char city [size];
    int id_class;
    char date_of_enrollment [size];
    ptr left;
    ptr right ;
};
void printStdInf(tree T)
{
    if (T != NULL)
    {
        printf(" ID : %d \t ",T->id );
        printf(" Name :%s \t ",T->name_st );
        printf("city name : %s \t ",T->city );
        printf(" ID_class : %d ",T->id_class );
        printf(" DATE OF enrollment : %s \t ",T->date_of_enrollment );
        printf("\n");
    }else
        printf("empty");
}
// find minumum in BST
ptr find_min( tree T)
{
    if ( T == NULL ) //empty tree
        return NULL;
    else
    if ( T->left == NULL ) //node itself
        return ( T );
    else
        return ( find_min ( T->left )); //find min recursive
}
// find maximum in BST
ptr find_max( tree T)
{
    if ( T != NULL )
        while ( T->right != NULL )
            T = T->right;
    return T;
}
// dellete node in BST by his Id
ptr delete ( tree T, int id)
{
    tree tmp_cell, child;
    if ( T == NULL )
        printf( "Element not found" );

    else if ( id < T->id)

        T->left = delete(T->left, id);

    else if ( id > T->id)

        T->right = delete(T->right, id);

    else if ( T->left && T->right ) //found element and has (right ,left) elements
    {
        tmp_cell = find_min(T->right);
        T->id = tmp_cell->id;
        T->right = delete(T->right, T->id);
    }
    else
    {
        tmp_cell = T;
        if ( T->left == NULL)
            child = T->right;
        if (T->right == NULL)
            child = T->left;
        free ( tmp_cell);
        return child;
    }
    return T;
}
// method insert for any BST
ptr insert ( struct BST * T, int id , char  name_st [size] ,char city [size] , int id_class ,char date_of_enrollment [size])
{ //Tree empty, insert first element
    if ( T == NULL ) {
        T = ( ptr) malloc (sizeof(struct BST));
        if ( T == NULL )
            printf (" Out of space!!!");
        else
        {
            T->id = id;
            strcpy(T->name_st,name_st);
            strcpy(T->city,city);
            T->id_class=id_class;
            strcpy(T->date_of_enrollment,date_of_enrollment);
            T->left = T->right = NULL;
        }
    }
    else //Tree not empty, check to insert to left or right.
    if ( id < T->id)
        T->left = insert ( T->left , id , name_st  , city  ,  id_class , date_of_enrollment );
    else
    if ( id > T->id)
        T->right = insert(T->right, id , name_st  , city  ,  id_class , date_of_enrollment );
    return T;
}
// method to insert by name for alphabetical order help
ptr insert_by_name (tree T ,int id , char  name_st [size] ,char city [size] , int id_class ,char date_of_enrollment [size]){
    if ( T == NULL ) {
        T = ( ptr) malloc (sizeof(struct BST));
        if ( T == NULL )
            printf (" Out of space!!!");
        else
        {
            T->id = id;
            strcpy(T ->name_st,name_st);
            strcpy(T ->city,city);
            T ->id_class=id_class;
            strcpy(T ->date_of_enrollment,date_of_enrollment);
            T ->left = T ->right = NULL;

        }
    }else{
        //Tree not empty, check to insert to left or right.
    if (strcmp(name_st, T->name_st) < 0)// name_st < T->name_st
        T->left = insert_by_name( T->left , id , name_st  , city  ,  id_class , date_of_enrollment );
    else if ( strcmp(name_st, T->name_st) > 0) // name_st > T->name_st
        T->right = insert_by_name(T->right, id , name_st  , city  ,  id_class , date_of_enrollment );}
    return T;
}
// method to search in BST
ptr find( int id, tree T)
{
    if(T==NULL)
        return NULL;
    if ( id < T->id)//greater than x move to right
        return ( find (id, T->left));
    else //Less than x move to left
    if ( id > T->id )
        return ( find ( id, T->right));
    else
        return T;
}
//inorder print
void traversal_in(tree T)
{
    if ( T == NULL)
        return;
    traversal_in(T->left);
    printf(" ID : %d \t ",T->id );
    printf(" Name :%s \t ",T->name_st );
    printf("city name : %s \t  ",T->city );
    printf(" ID_class : %d \t ",T->id_class );
    printf(" DATE OF enrollment : %s \t  ",T->date_of_enrollment );
    printf("\n");
    traversal_in(T->right);
}
// method to vist all node by post order(left..right..root) to store in new tree to alphabetical order help
ptr traversal_post (tree T ,tree new ){
    if ( T != NULL){
        traversal_post(T->left,new);
        new = insert_by_name(new ,T->id,T->name_st,T->city,T->id_class,T->date_of_enrollment);
        traversal_post(T->right,new);
    }
    return new;
}
// in order on file output
void inorder_file (tree t , FILE * fout){
    if(t==NULL)
        return;
    inorder_file(t->left,fout);
    fprintf(fout," Id : %d  ",t->id);
    fprintf(fout," name student : %s  ",t->name_st);
    fprintf(fout," city : %s  ",t->city);
    fprintf(fout,"id class : %d ",t->id_class);
    fprintf(fout,"date : %s ",t->date_of_enrollment);
    fprintf(fout,"\n");
    fprintf(fout,"\n");
    inorder_file(t->right,fout);
}
//inorder print
void traversal_in_city(tree T , char city [])
{
    if ( T == NULL)
        return;
    traversal_in_city(T->left,city);
    if(strcmp(T->city,city)==0){
        printf(" ID : %d \t ",T->id );
        printf(" Name :%s \t ",T->name_st );
        printf("city name : %s \t  ",T->city );
        printf(" ID_class : %d \t ",T->id_class );
        printf(" DATE OF enrollment : %s \t  ",T->date_of_enrollment );
        printf("\n");
    }
    traversal_in_city(T->right,city);
}
//inorder print
void traversal_in_id(tree T , int id_class)
{
    if ( T == NULL)
        return;
    traversal_in_id(T->left,id_class);
    if(T->id_class==id_class){
        printf(" ID : %d \t ",T->id );
        printf(" Name :%s \t ",T->name_st );
        printf("city name : %s \t  ",T->city );
        printf(" ID_class : %d \t ",T->id_class );
        printf(" DATE OF enrollment : %s \t  ",T->date_of_enrollment );
        printf("\n");
    }
    traversal_in_id(T->right,id_class);
}
//method to read data of student
ptr read_data (struct BST * T){
    tree new =NULL;
   FILE *fin = fopen("students.data.txt","r");
    int id ; char  name_st [size] ;char city [size] ; int id_class ;char date_of_enrollment [size];
    while (fscanf(fin," %d %s %s %d %s",&id,&name_st,&city,&id_class,&date_of_enrollment)!=EOF){
        new =insert(new,id,name_st,city,id_class,date_of_enrollment);
    }
    fclose(fin);
    return new;
}
int main() {
    struct BST * T1 = NULL ;
    tree new =NULL;
    tree new1 = NULL;
    tree new2 =NULL;
    ptr student =NULL;
    FILE * fout;
    int id ;char  name_st [size] ;char city [size] ;int id_class ;char date_of_enrollment [size];
    int ID_search ,ID_delet , temp_cheak ,ID_class;
    char city_cheak [size];
    T1= read_data(T1);
    printf(" Welcome to the school system \n \n");
    int cheak=0;
    while (cheak != 8){
        printf("Enter the number of the operation you want to perform (1-8) .. \n");
        printf("1.Insert a student with all its associated data \n");
        printf("2.Find a student by his/her student ID, and support updating of the student info if found \n");
        printf("3.List all students in lexicographic order of their names \n");
        printf("4.Search for a city and list all students from that city in lexicographic order of their names \n");
        printf("5.List all students by their class in lexicographic order of their names \n");
        printf("6.Delete a student given his/her student ID \n");
        printf("7.Save all students in file students data \n");
        printf("8.Exit \n");
        scanf("%d",&cheak);
        switch (cheak) {
            case 1:
                printf("Enter ID : ");
                scanf("%d",&id);
                printf("Enter name :");
                scanf("%s",&name_st);
                printf("Enter city :");
                scanf("%s",&city);
                printf("Enter id_class :");
                scanf("%d",&id_class);
                printf("Enter date_of_enrollmen :");
                scanf("%s",&date_of_enrollment);
                T1= insert(T1,id,name_st,city,id_class,date_of_enrollment);
                printf("\n");
                printf("student's information has been added \n");
                break;
            case 2:
                printf("Enter the student number you want to search for : ");
                scanf("%d",&ID_search);
                printf("\n");
                student = find(ID_search,T1) ;
                if(student){
                    printStdInf(student);
                    printf("Do you want to modify the data of the number you searched for ? .. 1 : yes  0 : NO \n");
                    scanf("%d",&temp_cheak);
                    if(temp_cheak){
                        printf("Enter new name Or keep the previous value by entering it again :");
                        scanf("%s",&name_st);
                        strcpy(student ->name_st ,name_st ) ;
                        printf("\n");
                        printf("Enter new city Or keep the previous value by entering it again :");
                        scanf("%s",&city);
                        strcpy(student ->city ,city ) ;
                        printf("\n");
                        printf("Enter new id_class Or keep the previous value by entering it again :");
                        scanf("%d",&id_class);
                        student ->id_class=id_class;
                        printf("\n");
                        printf("Enter new date_of_enrollmen Or keep the previous value by entering it again :");
                        scanf("%s",&date_of_enrollment);
                        strcpy(student ->date_of_enrollment ,date_of_enrollment ) ;
                        printf("\n");
                    } else
                        printf("search is done \n");
                }else
                    printf("the student not found \n ");
                break;
            case 3:
                traversal_in(traversal_post(T1,new));
                break;
            case 4:
                printf("Enter the name of the city you want  \n");
                scanf("%s",&city_cheak);
                traversal_in_city(traversal_post(T1,new1),city_cheak);
                break;
            case 5:
                printf("Enter number of class to show all student in this class :  ");
                scanf("%d",&ID_class);
                printf(" student in the class [%d] : \n",ID_class);
                traversal_in_id(traversal_post(T1,new2),ID_class);
                printf("\n");
                break;
            case 6:
                printf("Enter the student number you want to delete : \n");
                scanf("%d",&ID_delet);
                T1= delete(T1,ID_delet);
                printf("delete studend has number [%d] done \n",ID_delet);
                break;
            case 7:
                fout = fopen("output.txt","w");
                inorder_file(T1,fout);
                fclose(fout);
                break;
            default:
                   printf("please enter number of oprations... \n");
                   break;
        }
    }
    printf("Goodbye , the service has ended \n");
    return 0;
}