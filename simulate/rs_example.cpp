#include <iostream>
#include <fstream>
#include <vector>
#include "../include/PFE.hpp"
#include "../include/EFE.hpp"
#include "../include/DFT.hpp"
#include "../include/helpers.hpp"
#include "../include/ReedSolomon.hpp"
#include <string>
#include <fstream>
#include <streambuf>


using namespace std;



// define static variables 

typedef int el_t;
template<> int PFE<el_t>::prime = 929;
template<> boost::bimap<el_t,el_t> PFE<el_t>::exp_el = boost::bimap<el_t,el_t>();

typedef PFE<el_t> pfe;

template<> polynomial<pfe> EFE<pfe>::prim_poly = polynomial<pfe>();
template<> unsigned EFE<pfe>::m = 1;

 template<class cf_t> 
    ostream &operator<<(ostream &stream, const vector<cf_t>& x) 
    { 
	for(unsigned i = 0; i<x.size(); ++i) stream << x[i] << "  ";
	return stream; // must return stream 
    }; 




int main(int ac, char* av[])
{
//see https://en.wikipedia.org/wiki/Reed–Solomon_error_correction#Example_3

// initialize the inner code	
pfe::initialize_exp_el(3);
typedef EFE<pfe> efe;

const int prime = PFE<el_t>::prime;

const unsigned N = 7; // Block Length
const unsigned K = 3; // Message Length


// primitive element of the inner code 
const pfe A = pfe(3);
typedef DFT_PRIM<pfe> dftpfe;
dftpfe dftpfe_d(N,A);

RScode<pfe,dftpfe> innercode(N,K,A,dftpfe_d);
pfe message[] = {1,2,3};
vector<pfe> message_vector(message, message+3);
vector<pfe> encoded_vector, decoded_vector;
innercode.RS_systematic_encode(message_vector, encoded_vector);
cout << encoded_vector << endl;
encoded_vector[3].element = 456;
encoded_vector[4].element = 123;
innercode.RSdecode(decoded_vector, encoded_vector);
cout << decoded_vector << endl;
}
