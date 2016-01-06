//
//  main.cpp
//  Algolab_W2_Ex2
//
//  Created by Michal Porvaznik on 28/09/2014.
//  Copyright (c) 2014 Miso. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n; cin >> n;
    for (int test = 0; test < n; test++){
        
        vector< pair<int, int> > boats;
        int N; cin >> N;
        
        for (int i = 0; i < N; i++){
            pair<int,int> boat;
            int dummy;
            cin >> dummy >> boat.first;
            boat.second = dummy;
            boats.push_back(boat);
        }
        
        sort(boats.begin(), boats.end());
        
        int max_boats = 1, last_checked = 0, current = 0;
        int end, end_new = 0;
        
        end = boats[0].first;
        
        
        while (last_checked < N - 1){
            current = last_checked + 1;

            if (boats[current].first - end >= boats[current].second) {
                end = boats[current].first;
                last_checked = current;
            }
            else {
                end_new = end + boats[current].second;
                int j = current + 1;
                
                if (j >= N || boats[j].first >= end_new) { last_checked = current;}
                
                while (j < N && boats[j].first < end_new) {
                    if (boats[j].first - end >= boats[j].second) {
                        end_new = boats[j].first;
                    }
                    else if (end + boats[j].second < end_new) {
                        end_new = end + boats[j].second;
                    }
                    last_checked = j;
                    j++;
                }
                end = end_new;
            }
            max_boats++;
            
        }
        
        cout << max_boats << endl;
    }
   
    return 0;
}

