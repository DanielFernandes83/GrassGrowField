#include <iostream>
#include <time.h>

using namespace std;

//x rock
//. land
//+ grassed

#define MinFieldDimension 1
#define MaxFieldDimension 255 // max size 255 - use of unsigned char

class Field{
private: 
    char **field = new char*[field_length]; // 2D heap dynamic array
    int counter_rock = 0; //x rock
    int counter_land = 0; //. land
    int counter_grassed = 0; //+ grassed
    int field_length; //dimensions of the field to be input by user
    int field_width;     

public:
    Field(const int length, const int width ){ // field contructor  
        field_length = length;
        field_width = width;
        
        for( int aux= 0 ; aux < length; aux++) //created the 2D array
        field[aux] = new char [width];
        
        srand( (unsigned)time( NULL ) ); // fills the field with random information 
        for( unsigned char aux= 0; aux < field_length ; aux ++){
            for ( unsigned char aux1= 0; aux1 < field_width ; aux1 ++){
                switch((unsigned char) rand() % 3 ){
                    case 0 : field[aux][aux1] = 'x'; break;
                    case 1 : field[aux][aux1] = '.'; break;
                    default: field[aux][aux1] = '+'; 
                    }
            }
        }

    }

    ~Field(){
        for( int aux= 0 ; aux < field_length; aux++){ //delete the 2D array
            delete [] field[aux] ;
        } 
        delete [] field ;
        field = nullptr;
        cout << "memory free" << endl;
    }


    void field_print (){ // method to cout the field
        cout << "------------------------------------"<< endl;
        for( unsigned char aux= 0; aux < field_length ; aux ++){
            for ( unsigned char aux1= 0; aux1 < field_width ; aux1 ++){
                cout << field[aux][aux1] << " ";
            }
            cout << endl;
        }         
    }

    int field_refresh_and_summary (){ // monitors filed by counting the rock / land and grassed positions // also update 'G' status to '+'
        counter_rock = 0;
        counter_land = 0;
        counter_grassed= 0;
        for( unsigned char aux= 0; aux < field_length ; aux ++){
            for ( unsigned char aux1= 0; aux1 < field_width ; aux1 ++){
                switch (field[aux][aux1]){
                    case 'x':counter_rock ++; break;
                    case '.':counter_land ++; break;
                    default: counter_grassed++; field[aux][aux1] = '+';
                }
            }
        }
        cout << "# of rocks: " << counter_rock << endl ;
        cout << "# of land: " << counter_land << endl ;
        cout << "# of grassed: " << counter_grassed << endl ;
        return counter_grassed;
    }

    void field_grass_grow(){ // flow thtow the land positions and create a temp status 'G' on areas to be + after field_refresh_and_summary  ( required after field_grass_grow)
        for( unsigned char aux= 0; aux < field_length ; aux ++){
            for ( unsigned char aux1= 0; aux1 < field_width ; aux1 ++){
                if (field[aux][aux1] == '.'){ // 4 possibilities to grow
                    if ( (aux-1) > 0 ){
                        if (field[aux-1][aux1] == '+') field[aux][aux1] = 'G';
                    }

                    if ( (aux1-1) > 0 ){
                        if (field[aux][aux1-1] == '+') field[aux][aux1] = 'G';
                    }

                    if ( (aux+1) < field_length ){
                        if (field[aux+1][aux1] == '+') field[aux][aux1] = 'G';
                    }

                    if ( (aux1+1) < field_width ){
                        if (field[aux][aux1+1] == '+') field[aux][aux1] = 'G';
                    }
                } 
            }
        }
    }
};

// input field dimension from user with value validation
int read_field_dimension_from_user (const char* dimension, const int& min_value, const int& max_value){
    int aux = -1;
    while( aux <min_value || aux >max_value){
        cout <<"Please enter field " << dimension <<" ["<< min_value <<" - "<< max_value <<"]... ";
        cin >> aux;
        }
    return aux;
}

int main()
{   
    // user input field dimension
    int field_length= read_field_dimension_from_user( "lenght",MinFieldDimension, MaxFieldDimension);
    int field_width= read_field_dimension_from_user( "width",MinFieldDimension, MaxFieldDimension);

    Field land1( field_length,field_width ); // instance of the Feild class to be grassed
    land1.field_print();

    int grass_loops = 0; // counter of grass loop 
    int grass_areas_count = 0; // local variable for monitoring grasseing evoluction
    int new_grass_areas_count = 0; // local variable for monitoring grasseing evoluction

    new_grass_areas_count = land1.field_refresh_and_summary ();

    while ( new_grass_areas_count != grass_areas_count){ // keep grass grow until no more grow is detected
        grass_areas_count = new_grass_areas_count;
        cout << "------------------------------------"<< endl;
        cout << "# loops of grass grow : " << ++grass_loops << endl;
        land1.field_grass_grow();
        new_grass_areas_count = land1.field_refresh_and_summary ();
    }
    land1.field_print ();
    int var = 0 ;
    cin >> var;

    return 0;
}