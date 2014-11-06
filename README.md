This set of files contains an algorithm for generating Possibilistic Armstrong Relations from Database schema. The main function is largely ad-hoc code for performance testing. FuncDep and Attribues are class file which represent sets of attributes and functional dependencies. Schema reader is the file which reads from a database schema and then computes the armstrong relation from that description of the database. 

The file format for a database schema is:

A list of attributes, line seperated:
A blank line:
A single integer representing certainty degree:
A list of functional dependencies, line separated. 
Each functional dependency is of the form: 
Antecedent : Consequent: Certainty (colon separated)
Within each section, individual attributes are comma separated. An example is given in example.txt
