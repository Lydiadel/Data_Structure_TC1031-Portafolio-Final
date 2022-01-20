bool isValid(string s) {
    vector<char> stack;
    for (char x : s){
        if (x == ')' || x == ']' || x == '}'){
            if (stack.size() == 0){
               return false;
            }
            char c = stack.back();
            stack.pop_back();
            if (x == ')' && c != '('){
                return false;
            }
            if (x == ']' && c != '['){
                return false;
            }
            if (x == '}' && c != '{'){
                return false;
            }
        } else {
            stack.push_back(x);
        }
    }
    return stack.size() == 0;
}