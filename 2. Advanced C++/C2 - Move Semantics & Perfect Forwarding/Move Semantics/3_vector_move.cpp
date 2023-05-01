#include <iostream>
#include <vector>
#include <string>


class Move_Vector {
    public:
        Move_Vector(std::string* ID){

            this->DEFAULT += " of " + *ID;
            this->ID = ID;
            
            std::cout << "Default Constructor with ID " << *ID << std::endl;
        }

        Move_Vector(Move_Vector&& other){
            
            this->ID = other.ID;
            // this->DEFAULT = std::move(other.DEFAULT);

            other.ID = nullptr;
            
            std::cout << "Moving Constructor with ID " << *ID << std::endl;
        }

        Move_Vector& operator=(Move_Vector&& other){
            std::cout << "Moving Assignment Operator from ID " << *other.ID << " to ID " << *this->ID << std::endl;
            
            if(this != &other){
                delete ID;

                ID = other.ID;
                DEFAULT = other.DEFAULT;

                other.ID = nullptr;
            }


            return *this;
        }

        ~Move_Vector(){
            std::cout << "Destructor Called with ID " << ID << std::endl;

            delete ID;
        }
        
        void display(){
            std::cout << std::endl << "Default: " << this->DEFAULT << std::endl;
            std::cout << "ID: " << *ID << std::endl << std::endl;
        }
    
    private:
        std::string DEFAULT = "DEFAULT";
        std::string* ID = &DEFAULT;
};


int main(){

    std::vector<std::string*> ID;
    std::vector<Move_Vector> Example;

    for(int i = 0; i < 5; i++){
        ID.push_back(
            new std::string(
                "Object-" + std::to_string(i)
            )
        );
    }

    /* for(auto each : ID){
        std::cout << "Pushing " << each << std::endl;
        
        // Pushing a new `Move_Vector` object into the `Example` vector, using a pointer to a string as
        // e argument for the constructor. However, this can lead to unexpected behavior because the
        // ove_Vector` class takes ownership of the string pointer and deletes it in its destructor.
        // multiple `Move_Vector` objects are created with the same string pointer, they will all
        // y to delete it, leading to undefined behavior.
        Example.push_back(
            Move_Vector{each}
        );

        std::cout << "Done" << std::endl << std::endl;
    } */

    Move_Vector a{ID[0]};
    Move_Vector b{ID[1]};
    Move_Vector c{ID[2]};
    Move_Vector d{ID[3]};
    Move_Vector e{ID[4]};

    b = std::move(a);
    c = std::move(d);

    c.display();

    return 0;
}