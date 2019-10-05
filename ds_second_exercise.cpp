#include <iostream>
#include <fstream>
#include <string.h>
// #include <boost/algorithm/string.hpp>
using namespace std ;
#define size 100

class SparseItem {
    public :
      int row ;
      int col ; 
      int value ; 
};

class SparseMatrix {
    private :
        int row ;
        int col ;
        int terms ;
        SparseItem arr[100] ;
    public :
        SparseMatrix(int , int , int , SparseItem[] ) ;
        SparseMatrix(){}
        ~SparseMatrix() ;
        void show() ;
        int get(int , int) ;
        SparseMatrix* transpose() ;
        void put(int , int , int) ;
        SparseMatrix add(SparseMatrix) ;
        void read_file() ;
        void write_file() ;
};

SparseMatrix::SparseMatrix(int row , int col ,int terms , SparseItem s[]){
    this->col = col; 
    this->row = row ;
    this->terms = terms ;
    for(int i= 0 ; i< terms ; i++){
        this->arr[i].row = s[i].row  ;
        this->arr[i].col = s[i].col  ;
        this->arr[i].value = s[i].value  ;
    }
}

void SparseMatrix::show(){
    int controller = 0 ;
    for (int i = 0; i < this->row; i++){
        for (int j = 0; j < this->col; j++){
            controller = 0;
            for (int k = 0; k < this->terms ; k++){
                if(this->arr[k].row == i && this->arr[k].col == j){
                    cout << this->arr[k].value << " " ;
                    controller = 1 ;
                    break ;
                }
            }
            if (controller == 0){
                cout << 0 << " " ;
            }
            controller = 0 ;
        }
        cout << endl ;
    }
}

int SparseMatrix::get(int row , int col){
    
    if (this->row <= row && row < 0 && this->col <= col && col < 0  ){
        throw "out of bounds" ;
        return -1 ;
    }
    
    for (int i = 0; i < this->terms ; i++){
        if (this->arr[i].col == col && this->arr[i].row == row){
            return this->arr[i].value ;
        }
        if (row > i){
            return 0 ;
        }
    }

    return 0 ;
}

SparseMatrix* SparseMatrix::transpose(){
    SparseItem *newArr = new SparseItem[this->terms] ;

    int counter = 0 ;
    for(int i = 0 ; i < this->col ; i++ ){
        for(int j = 0 ; j < this->terms ; j++){
            if(this->arr[j].col == i){
                newArr[counter].col = this->arr[j].row ;
                newArr[counter].row = this->arr[j].col ;
                newArr[counter].value = this->arr[j].value ;
                counter ++ ;
            } 
        }
    }

    SparseMatrix *newSparseMatrix = new SparseMatrix(this->col , this->row , this->terms , newArr);

    return newSparseMatrix;
} 

void SparseMatrix::put(int row , int col , int value){

    if(this->col <= col || col < 0 || this->row <= row || row < 0){
        throw "its not in matrix rage" ;
    }

    this->terms = this->terms + 1 ;
    SparseItem newArr[this->terms] ;
    int hold_pos ;
    for(int i = 0 ; i < this->terms - 1 ; i++){
        if (row == this->arr[i].row || row > this->arr[i].row){
            hold_pos = i ;
            newArr[i].row = row ;
            newArr[i].col = col ;
            newArr[i].value = value ;
            break;
        }
        newArr[i].row = this->arr[i].row ;
        newArr[i].col = this->arr[i].col ;
        newArr[i].value = this->arr[i].value ;
    }
    for (int i = hold_pos + 1 ; i < this->terms ; i++){
        newArr[i].row = this->arr[i].row ;
        newArr[i].col = this->arr[i].col ;
        newArr[i].value = this->arr[i].value ;
    }

    for (int i = 0; i < this->terms; i++){
        this->arr[i].row = newArr[i].row ;
        this->arr[i].col = newArr[i].col ;
        this->arr[i].value = newArr[i].value ;
    }
}

SparseMatrix SparseMatrix::add(SparseMatrix second_matrix){
    int counter = 0 ;
    SparseItem added_matrix[this->terms + second_matrix.terms] ;
    bool controller_for_this_arr = false ;
    bool controller_for_second_matrix_arr = false ;
    for(int i = 0 ; i < this->row ; i++){
        for(int j = 0 ; j < this->terms ; j++ ){
            if (i == this->arr[j].row){
                for(int k = 0 ; k < second_matrix.terms ; k++ ){
                    if (this->arr[j].row == second_matrix.arr[k].row &&
                       this->arr[j].col == second_matrix.arr[k].col){
                        (added_matrix+counter)->value = 0 ;
                        (added_matrix+counter)->col = this->arr[j].col ; 
                        (added_matrix+counter)->row = this->arr[j].row ;
                        (added_matrix+counter)->value = this->arr[j].value + second_matrix.arr[k].value ;
                        controller_for_this_arr = true ;
                        break ;
                    }
                }
                if (controller_for_this_arr == false){
                    (added_matrix+counter)->value = 0 ;
                    (added_matrix+counter)->col = this->arr[j].col ; 
                    (added_matrix+counter)->row = this->arr[j].row ;
                    (added_matrix+counter)->value += this->arr[j].value ;
                }
                controller_for_this_arr = false ;
                counter++ ;
            }
        }
        for(int j = 0 ; j < second_matrix.terms ; j++ ){
            if (i == second_matrix.arr[j].row){
                for(int k = 0 ; k < this->terms ; k++ ){
                    if (this->arr[k].col == second_matrix.arr[j].col &&
                       this->arr[k].row == second_matrix.arr[j].row){
                        controller_for_second_matrix_arr = true ;
                        break ;
                    }
                }
                if (!controller_for_second_matrix_arr)
                {
                    (added_matrix+counter)->value = 0 ;
                    (added_matrix+counter)->col = second_matrix.arr[j].col; 
                    (added_matrix+counter)->row = second_matrix.arr[j].row ;
                    (added_matrix+counter)->value += second_matrix.arr[j].value ;
                    counter++ ;
                }
                controller_for_second_matrix_arr = false ;
            }
        }
    }
    SparseMatrix matrix = SparseMatrix(this->row , this->col , counter ,added_matrix) ;
    return matrix ;
} 

void SparseMatrix::read_file(){
    ifstream fin ;
    fin.open("matrix.txt");
    int col = 0 ;
    int row = 0 ;
    SparseItem arr[size] ;
    int terms = 0 ;
    int col_holder = 0 ;
    while (fin){
        string line ;
        getline(fin , line) ;
        if(line.length() == 0 ){
            break ;
        }
        for(int i = 0 ; i < line.length() ; i++ ){
            if(line[i] != '0' && line[i] != ' ') {
                this->arr[terms].row = row ;
                this->arr[terms].col = col ;
                this->arr[terms].value = (int)line[i] - '0' ;  
                terms++ ;
                col++ ;
            }
            if (line[i] == '0')
            {
                col++ ;
            }
        }
        col_holder = col ;
        col = 0 ;
        row++;
    }
    this->row = row  ;
    this->col = col_holder ;
    this->terms = terms ;
    fin.close() ;
}
void SparseMatrix::write_file(){
    ofstream fin ;
    fin.open("matrix.txt");
    for(int i = 0 ; i < row ; i++){
        for(int j = 0 ; j <  col ; j++){
            int controller = 0;
            for( int k = 0 ; k < terms ; k++ ){
                if(arr[k].col == j && arr[k].row == i){
                    fin << arr[k].value  << " ";
                    controller = 1;
                    break;
                }
            }
            if(controller == 0){
                fin << "0 ";
            }
        }
        fin << "\n";
    }
    fin.close() ;
}

SparseMatrix::~SparseMatrix(){
    cout << "destructor called" << endl ;
}


int main(void){
    SparseItem s , s1 ,s2 ,s3 , s4,s5,s6 ,s7 ;
    s.col = 0 ;
    s.row = 0 ;
    s.value = 1 ;
    s1.col = 0 ;
    s1.row = 1 ;
    s1.value = 1 ;
    s2.col = 1 ;
    s2.row = 2 ;
    s2.value = 1 ;
    s3.col = 2 ;
    s3.row = 2 ;
    s3.value = 1 ;
    s4.col = 1 ;
    s4.row = 0 ;
    s4.value = 1 ;
    s5.col = 1 ;
    s5.row = 1 ;
    s5.value = 1 ;
    s6.col = 1 ;
    s6.row = 2 ;
    s6.value = 2 ;
    s7.col = 2 ;
    s7.row = 2 ;
    s7.value = 1 ;


    SparseItem arr[]= {s ,s1 ,s2 ,s3 };
    SparseItem arr1[] = {s4 ,s5 ,s6 ,s7 } ;

    SparseMatrix sss = SparseMatrix(3,3,4,arr);
    sss.write_file();
   
}