#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>
#include "State.h"
using namespace std;


vector<State> using_BFS(State initial,State goal,vector<pair<int,int> > goal_indices);
vector<State> using_DFS(State initial,State goal,vector<pair<int,int> > goal_indices);
vector<State> using_A_star(State initial,State goal,vector<pair<int,int> > goal_indices);
void display_state(State s);
bool is_the_goal(State temp,State goal);
bool exist_in_frontier_BFS(State n,queue<State> f);
bool exist_in_frontier_DFS(State n, stack<State> st);
bool exist_in_explored(State n, vector<State> v);
void display_explored(vector<State> v);
vector<pair<int,int> > indices_of_goal_state();
int main()
{

    /*int initial_matrix[3][3]={
        {1,2,5},
        {3,4,0},
        {6,7,8}
    };*/

    int initial_matrix[3][3]={
        {6,4,7},
        {8,5,0},
        {3,2,1}
    };

    /*int initial_matrix[3][3]={
        {1,0,3},
        {2,4,5},
        {6,7,8}
    };*/
    int goal_matrix[3][3]={
        {0,1,2},
        {3,4,5},
        {6,7,8}
    };
    State init;
    init.set_matrix(initial_matrix);
    init.cost=0;
    vector<pair<int,int> > indices_of_goal= indices_of_goal_state();
    init.set_manhattan(indices_of_goal);
    State goal;
    goal.set_matrix(goal_matrix);

    //vector<State> v=using_BFS(init,goal,indices_of_goal);
    //vector<State> v=using_DFS(init,goal,indices_of_goal);
    vector<State> v=using_A_star(init,goal,indices_of_goal);
    display_explored(v);
    return 0;
}
int get_min(vector<State> v){
    int min_val=v.at(0).cost+v.at(0).h;
    State min_st=v.at(0);
    int min_ind=0;
    for(int i=1;i<v.size();i++){
        if(v.at(i).cost+v.at(i).h<min_val){
            min_st=v.at(i);
            min_val=v.at(i).cost+v.at(i).h;
            min_ind=i;
        }
    }
    return min_ind;
}
bool lower_exists(State s,vector<State> frontier,vector<State> explored){
    for(int i=0;i<frontier.size();i++){
        if(is_the_goal(s,frontier.at(i)) && frontier.at(i).cost+frontier.at(i).h<=s.cost+s.h){
            return true;
        }
    }
    for(int i=0;i<explored.size();i++){
        if(is_the_goal(s,explored.at(i)) && explored.at(i).cost+explored.at(i).h<=s.cost+s.h){
            return true;
        }
    }
    return false;
}
vector<State> using_A_star(State initial,State goal,vector<pair<int,int> > goal_indices){

    /*parameters:
        -initial-->the initial state
        -goal-->the goal state
        -goal_indices-->the index of each cell, used to calculate h(n), ex: goal_indices[0]=(0,0) , goal_indices[8]=(2,2)
    */

    /*returns:
        -explored-->explored states
    */
    vector<State> frontier;
    vector<State> explored;
    frontier.push_back(initial);
    while(!frontier.empty()){
        //get index of state with minimum h
        int min_state_ind=get_min(frontier);
        State temp=frontier.at(min_state_ind);

        //remove this state from frontier
        frontier.erase(frontier.begin()+min_state_ind);

        //set its neighbors
        temp.set_neighbors(goal_indices);
        explored.push_back(temp);

        //loop over its neighbors
        for(int i=0;i<temp.neighbors.size();i++){

            //if it reaches the goal state, return success
            if(is_the_goal(temp.neighbors.at(i),goal)){
                explored.push_back(temp.neighbors.at(i));
                return explored;
            }

            //else
            temp.neighbors.at(i).set_manhattan(goal_indices);
            if(!lower_exists(temp.neighbors.at(i),frontier,explored)){
                frontier.push_back(temp.neighbors.at(i));
            }

        }
    }
    return explored;



}
vector<State> using_BFS(State initial,State goal,vector<pair<int,int> > goal_indices){

    queue<State> frontier;
    vector<State> explored;
    frontier.push(initial);
    int j=0;
    while(!frontier.empty()){
        State temp_state=frontier.front();
        frontier.pop();
        explored.push_back(temp_state);

        if(is_the_goal(temp_state,goal)){
            cout<<"Cost using BFS: "<<temp_state.cost<<endl;
            return explored;
        }
        temp_state.set_neighbors(goal_indices);
        vector<State> temp_neighbors=temp_state.neighbors;
        for(int i=0;i<temp_neighbors.size();i++){
            if(!exist_in_explored(temp_neighbors.at(i),explored) && !exist_in_frontier_BFS(temp_neighbors.at(i),frontier)){
                frontier.push(temp_neighbors.at(i));
            }
        }

    }
    return explored;


}

vector<State> using_DFS(State initial,State goal,vector<pair<int,int> > goal_indices){
    stack<State> frontier;
    frontier.push(initial);
    vector<State> explored;
    while(!frontier.empty()){
        State temp_state=frontier.top();
        frontier.pop();
        explored.push_back(temp_state);
        //check if temp_state is the goal state
        if(is_the_goal(temp_state,goal)){
            cout<<"Cost using DFS: "<<temp_state.cost<<endl;
            return explored;
        }
        temp_state.set_neighbors(goal_indices);
        vector<State> temp_neighbors=temp_state.neighbors;
        for(int i=0;i<temp_neighbors.size();i++){
            if(!exist_in_explored(temp_neighbors.at(i),explored) && !exist_in_frontier_DFS(temp_neighbors.at(i),frontier)){
                frontier.push(temp_neighbors.at(i));
            }
        }

    }

    return explored;
}

void display_explored(vector<State> v){
    for(int i=0;i<v.size();i++){
        display_state(v.at(i));
        cout<<"*********************************** h(n)= "<<v.at(i).h<<" **************"<<endl;
    }
}
void display_state(State s){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout<<s.matrix[i][j]<<" ";
        }
        cout<<endl;
    }
}
bool is_the_goal(State temp,State goal){

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(temp.matrix[i][j]!=goal.matrix[i][j]){
                return false;
            }
        }
    }
    return true;
}

bool exist_in_frontier_BFS(State n,queue<State> f){
        while(!f.empty()){
            State temp_state=f.front();
            f.pop();
            if(is_the_goal(n,temp_state)){
                return true;
            }
        }

    return false;
}
bool exist_in_frontier_DFS(State n, stack<State> st){
        while(!st.empty()){
            State temp_state=st.top();
            st.pop();
            if(is_the_goal(n,temp_state)){
                return true;
            }
        }

        return false;
}
bool exist_in_explored(State n, vector<State> v){

    for(int i=0;i<v.size();i++){
        if(is_the_goal(n,v.at(i))){
            return true;
        }
    }

    return false;
}


vector<pair<int,int> > indices_of_goal_state(){

    vector<pair<int,int> > v;
    for(int i=0;i<9;i++){
        pair<int,int> p;
        p.first=i/3;
        p.second=i%3;
        v.push_back(p);
    }
    return v;
}

