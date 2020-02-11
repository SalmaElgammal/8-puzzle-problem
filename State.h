#ifndef STATE_H
#define STATE_H
#include <vector>
#include <iostream>

using namespace std;

class State
{
    public:
        int matrix[3][3]={0};
        vector<State> neighbors;
        int cost;
        int h;
        //void set_neighbors();
        //void set_matrix(int A[3][3]);



        void set_matrix(int A[3][3]){
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    matrix[i][j]=A[i][j];
                }
            }
        }
        void set_manhattan(vector<pair<int,int> > goal){
            int n;
            h=0;
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    n=matrix[i][j];
                    h+=abs(i-goal.at(n).first)+abs(j-goal.at(n).second);
                }
            }

        }


        void set_neighbors(vector<pair<int,int> > goal){
            int n[3][3];

            //get index of blank cell
            int blank_i,blank_j;
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    if(matrix[i][j]==0){
                        blank_i=i;
                        blank_j=j;
                    }
                }
            }

            if(blank_i>0){
                for(int i=0;i<3;i++){
                    for(int j=0;j<3;j++){
                        n[i][j]=matrix[i][j];
                    }
                }
                int temp=n[blank_i][blank_j];
                n[blank_i][blank_j]=n[blank_i-1][blank_j];
                n[blank_i-1][blank_j]=temp;
                State n1;
                n1.set_matrix(n);
                n1.cost=cost+1;
                n1.set_manhattan(goal);
                neighbors.push_back(n1);
            }
            if(blank_j>0){
                for(int i=0;i<3;i++){
                    for(int j=0;j<3;j++){
                        n[i][j]=matrix[i][j];
                    }
                }
                int temp=n[blank_i][blank_j];
                n[blank_i][blank_j]=n[blank_i][blank_j-1];
                n[blank_i][blank_j-1]=temp;
                State n1;
                n1.cost=cost+1;
                n1.set_matrix(n);
                n1.set_manhattan(goal);
                neighbors.push_back(n1);
            }
            if(blank_i<2){
                for(int i=0;i<3;i++){
                    for(int j=0;j<3;j++){
                        n[i][j]=matrix[i][j];
                    }
                }
                int temp=n[blank_i][blank_j];
                n[blank_i][blank_j]=n[blank_i+1][blank_j];
                n[blank_i+1][blank_j]=temp;
                State n1;
                n1.set_matrix(n);
                n1.cost=cost+1;
                n1.set_manhattan(goal);
                neighbors.push_back(n1);
            }
            if(blank_j<2){
                for(int i=0;i<3;i++){
                    for(int j=0;j<3;j++){
                        n[i][j]=matrix[i][j];
                    }
                }
                int temp=n[blank_i][blank_j];
                n[blank_i][blank_j]=n[blank_i][blank_j+1];
                n[blank_i][blank_j+1]=temp;
                State n1;
                n1.set_matrix(n);
                n1.cost=cost+1;
                n1.set_manhattan(goal);
                neighbors.push_back(n1);
            }
        }

    protected:

    private:
};


#endif // STATE_H
