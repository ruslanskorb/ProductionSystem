
//
//  main.cpp
//  ProductionSystem
//
//  Created by Ruslan Skorb on 12/4/12.
//  Copyright (c) 2012 Ruslan Skorb. All rights reserved.
//

#include <cstdio>
#include <vector>

using namespace std;

void outputDualVectorTo(FILE* out, vector< vector<int> > v)
{
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            fprintf(out, "%d ", v[i][j]);
        }
        fprintf(out, "\n");
    }
}

vector<vector<int>> originalStateVector(FILE *in)
{
    vector<vector<int>> stateVector;
    
    int n, m;
    fscanf(in, "%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        vector<int> v;
        for (int j = 0; j < m; j++) {
            v.push_back(0);
        }
        stateVector.push_back(v);
    }
    
    return stateVector;
}

vector<int> initialField(FILE *in)
{
    vector<int> field;
    
    int ni, mi;
    fscanf(in, "%d %d", &ni, &mi);
    
    field.push_back(ni);
    field.push_back(mi);
    
    return field;
}

vector<int> finiteField(FILE *in)
{
    vector<int> field;
    
    int ni, mi;
    fscanf(in, "%d %d", &ni, &mi);
    
    field.push_back(ni);
    field.push_back(mi);
    
    return field;
}

vector<vector<vector<int>>> productionRules(FILE *in)
{
    vector<vector<vector<int>>> rules;
    
    int count;
    fscanf(in, "%d", &count);
    
    for (int i = 0; i < count; i++) {
        int currentFieldNi, currentFieldMi;
        int targetFieldNi, targetFieldMi;
        
        fscanf(in, "%d %d", &currentFieldNi, &currentFieldMi);
        fscanf(in, "%d %d", &targetFieldNi, &targetFieldMi);
        
        vector<int> v;
        
        v.push_back(currentFieldNi);
        v.push_back(currentFieldMi);
        
        vector<int> v2;
        
        v2.push_back(targetFieldNi);
        v2.push_back(targetFieldMi);
        
        vector<vector<int>> iter;
        
        iter.push_back(v);
        iter.push_back(v2);
        
        rules.push_back(iter);
    }
    
    return rules;
}

vector<vector<int>> targetFields(vector<int> currentField, vector<vector<vector<int>>> productionRules)
{
    vector<vector<int>> tFields;
    
    for (int i = 0; i < productionRules.size(); i++) {
        vector<vector<int>> iter = productionRules[i];
        vector<int> curField = iter[0];
        if (curField[0] == currentField[0] && curField[1] == currentField[1]) {
            tFields.push_back(iter[1]);
        }
    }
    
    return tFields;
}

int main(int argc, const char * argv[])
{
    FILE *in = fopen("/Users/ruslan/Developer/ProductionSystem/ProductionSystem/input.txt", "r");
    
    vector<vector<int>> stateVector = originalStateVector(in);
    vector<int> vInitialField = initialField(in);
    vector<int> vFiniteField = finiteField(in);
    vector<vector<vector<int>>> rules = productionRules(in);
    
    fclose(in);
    
    stateVector[vInitialField[0]][vInitialField[1]] = 1;
    
    bool isTheEnd = false;
    
    vector<int> currentField = vInitialField;
    
    FILE *out = fopen("/Users/ruslan/Developer/ProductionSystem/ProductionSystem/output.txt", "w");
    
    do {
        fprintf(out, "originalStateVector:\n");
        outputDualVectorTo(out, stateVector);
        
        fprintf(out, "\nCurrent field:\n");
        fprintf(out, "%d %d\n", currentField[0], currentField[1]);
        
        vector<int> targetField;
        vector<vector<int>> tFields = targetFields(currentField, rules);
        
        fprintf(out, "\nTarget fields:\n");
        for (int i = 0; i < tFields.size(); i++) {
            vector<int> targetField = tFields[i];
            fprintf(out, "%d %d\n", targetField[0], targetField[1]);
        }
        
        for (int i = 0; i < tFields.size(); i++) {
            if (stateVector[tFields[i][0]][tFields[i][1]] == 0) {
                targetField = tFields[i];
                stateVector[tFields[i][0]][tFields[i][1]] = 1;
                break;
            }
        }
        if (targetField.size() != 0) {
            currentField = targetField;
            if (currentField[0] == vFiniteField[0] && currentField[1] == vFiniteField[1]) {
                printf("Finite field!");
                isTheEnd = true;
            }
        } else {
            printf("Finite field not available!");
            isTheEnd = true;
        }
        
        fprintf(out, "\n\n");
    } while (!isTheEnd);
    
    fclose(out);
    
    return 0;
}























