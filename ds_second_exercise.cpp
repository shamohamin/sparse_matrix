#include <iostream>
using namespace std ;


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
        SparseItem *arr ;
    public :
        SparseMatrix(int , int , int) ;
        ~SparseMatrix() ;
        void show() ;
        int get(int , int) ;
        SparseMatrix* transpose() ;
        void put(int , int , int) ;
        SparseMatrix* add(SparseMatrix) ;
};

SparseMatrix::SparseMatrix(int row , int col ,int terms){
    this->col = col; 
    this->row = row ;
    this->terms = terms ;
    this->arr = new SparseItem[terms] ;
}

void SparseMatrix::show(){
    int controller = 0 ;
    for (int i = 0; i < this->row; i++){
        for (int j = 0; j < this->col; j++){
            for (int k = 0; k < this->terms ; k++){
                if(this->arr[k].row == i && this->arr[k].col == j){
                    cout << 1 << " " ;
                    controller = 1 ;
                    break ;
                }
            }
            if (controller == 0){
                cout << 0  << " ";
            }
        }
        controller = 0 ;
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
            } 
        }
    }

    SparseMatrix *newSparseMatrix = new SparseMatrix(this->col , this->row , this->terms);

    return newSparseMatrix;
} 

void SparseMatrix::put(int row , int col , int value){
    this->terms = this->terms + 1 ;
    SparseItem * newArr = new SparseItem[this->terms] ;
    for(int i = 0 ; i < this->terms - 1 ; i++){
        if (row == this->arr[i].row){
            
        }
    }
}

SparseMatrix* SparseMatrix::add(SparseMatrix second_matrix) {
    SparseItem *addedMatrix ;
    int counter = 0 ;
    for(int i = 0 ; i < this->terms ; i++){
        addedMatrix->col = this->arr[i].col ;
        addedMatrix->row = this->arr[i].row ;
        addedMatrix->value = this->arr[i].value ;
    }

    for(int i = 0 ; i < second_matrix.terms ; i++){
         if (addedMatrix->col == second_matrix.arr[i].col &&
            addedMatrix->row == second_matrix.arr[i].row){
            addedMatrix->value += second_matrix.arr[i].value ;
        }else{
            addedMatrix->col = second_matrix.arr[i].col ; 
            addedMatrix->row = second_matrix.arr[i].row ;
            addedMatrix->value = second_matrix.arr[i].value ;
            counter++ ;
        }
    }

    SparseMatrix *matrix = new SparseMatrix(this->row , this->col ,
    this->terms + counter) ;

    return matrix ;

} 


SparseMatrix::~SparseMatrix(){
    delete [] this->arr ;
}
