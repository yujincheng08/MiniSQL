'API' class has only one interface, i.e. 'execute(const Action&)'. This function receives a Action object produced by interpreter.
'API' will flush table in the case that:
1. 'API' object is deconstructed.
2. Insert or delete 1000 tuples consecutively.
3. Change to another table 
4. Before other operation that is not insert or delete
Before merging all parts together, several slight changes are needed:
1. 'class catalogManager' should add a funtion namely 'vector<string> GetAttrName()', and then set 'FindTableName()' as public function.
2. Add 'API' to the friend class of 'Column' and 'Condition'.
!!!Haven't add index related funtions