#include <iostream>
#include <string>
#include <cmath>


using namespace std;

//get line function
int get_line_sum(string line)
{

    //initiate sum(total)
    int total = 0;
    
    //loop through input string
    for (char num: line)
    {
        //make sure it is a digit
        if (isdigit(num))
        {
            int inum = num - '0';
            //if it is a digit, add it to sum
            total += inum;
        }
    }
    
    return total;
}

char get_next_state(string hood, string rules)
{
    //https://www.cplusplus.com/reference/string/string/find/ Documentation for find function
    int index = rules.find(hood);
    //if the neighborhood has an index in the rules return its value (8 indexs over)
    if (index != static_cast<int>(string::npos))
    {
        return static_cast<char>(rules.at(index+7));
    }
    
    //only returns 0 if neighborhood is not defined in rules
    else
    {
        return '0';
    }
    
}

void update_line(string &line, string rules)
{
    //cell number counter
    string updated_line = "";

    //first neighborhood
    updated_line += get_next_state(line.at(line.length()-1)+line.substr(0,2),rules);

    //middle neighborhoods
    for (int i = 0; i <= static_cast<int>(line.length() - 3); i++)
    {
        char updated_cell = get_next_state(line.substr(i,3),rules);
        updated_line = updated_line + updated_cell;
    }
    
    //last neighborhood
    updated_line = updated_line + get_next_state(line.substr(line.length()-2,2)+line.at(0),rules);
    //cout << updated_line << endl;
    line = updated_line;
    
}

string run_cellular_automata(string rules, int iter, string start)
{
    //dedclare temporary line
    string cells = start;

    //declare final output to be updated
    string output = cells + " sum = " + to_string(get_line_sum(cells)) + "\n";

    //loop until number of iterations are complete
    for (int i = 0; i < (iter - 1); i++)
    {
        //update the line, calculate its sum, and append it to final output
        update_line(cells, rules);
        int total = get_line_sum(cells);
        output = output + cells + " sum = " + to_string(total) + '\n';
    }

    return output;
}


int main()
{
    //declare raw input, rules, starting line, and number of iterations
    string raw, input_line, rules, start, iter;
    //int iter;


    while (getline(cin, input_line))
    {
        if(input_line.empty())
        {
            break;
        }
        else
        {
            raw += input_line;
        }
    }

    


    //break up raw input into repective values
    string current = "!";
    int pos = 0;

    while (current != ".")
    {
        current = raw[pos];
        rules += current;
        pos += 1;
    }

    pos += 1;

    while(current != "\n")
    {
        current = raw[pos];
        iter += current;
        pos += 1;
    }

    int cycles = stoi(iter);
    
    start = raw.substr(pos);
    
    //temporary holder for outputs
    string x;

    //store output in x
    x = run_cellular_automata(rules, cycles, start);

    //output
    cout << x;

    return 0;
}

