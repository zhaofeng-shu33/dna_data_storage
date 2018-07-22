#include <iostream>
#include <vector>
#include "../include/PFE.hpp"
#include <string>
#include <streambuf>


using namespace std;



// define static variables 

typedef int el_t;
template<> int PFE<el_t>::prime = 7;
template<> boost::bimap<el_t,el_t> PFE<el_t>::exp_el = boost::bimap<el_t,el_t>();

typedef PFE<el_t> pfe;


template<class cf_t> 
    ostream &operator<<(ostream &stream, const vector<cf_t>& x) 
    { 
	for(unsigned i = 0; i<x.size(); ++i) stream << x[i] << "  ";
	return stream; // must return stream 
    }; 




int main(int ac, char* av[])
{
pfe::initialize_exp_el(3);

const int prime = PFE<el_t>::prime;


// primitive element of the inner code 
for(int i = 1; i < prime; i++)
   cout << i << ' ' << pfe(i).order() << endl;

}
