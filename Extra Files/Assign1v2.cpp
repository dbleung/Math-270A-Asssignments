#include <iostream>   // For C++ input/output
#include <vector>     // For STL vectors
#include <cstdio>     // For C input/output
#include <cmath>      // For math functions
using namespace std; // Using the "standard" (std) standard template library components

/**
  Instances of class TriOperator are linear operators whose apply member function
  multiplies a tri-diagonal matrix with an input vector. 

  The tri-diagonal matrix associated with the class instance is 
  specified by it's lower diagonal, diagonal and upper diagonal entries, e.g.

   n X n tridiagonal matrix T where n = systemSize


       T =  |  diag[0]  upDiag[0]                                  |
            |loDiag[0]    diag[1] upDiag[1]                        |
            |           loDiag[1]                                  |
            |                *       *       *                     |
            |                   *         *        *               |
            |                loDiag[n-3]   diag[n-2]  upDiag[n-2]  |
            |                             loDiag[n-2]   diag[n-1]  |



  Currently, STL (Standard Template Library) vectors are used to store
  the diagonals that define the non-zero values of T

  Version: Friday Sept 29 2017 01:50:45 PM PST 
 */
class TriOperator
{
public:

    /// Null Constructor -- called when you declare an instance

    TriOperator()
    {initialize();};

    /// Copy constructor (creates duplicate of T)

    TriOperator(const TriOperator& T) // called when you declare an instance with an existing instance, & is pass be ref, memory
    {initialize(T);};


    /**
    This constructor initializes the internal class data with entries
    of the n X n tridiagonal matrix T associated with the entries in
    the lower diagonal (loDiag), diagonal (diag), and upper diagonal (upDiag).
    */

    TriOperator(long systemSize, vector<double>& loDiag, vector<double>& diag,
               vector<double>& upDiag)
    {
        initialize(systemSize,loDiag,diag,upDiag);
    }

    // Default destructor

    virtual ~TriOperator(){};

    /// Null initializer, resizes the internal arrays to zero length

    void initialize()
    {
        systemSize = 0;
        loDiag.clear();
        diag.clear();
        upDiag.clear();

    };

    ///  Copy initializer. Duplicates the entries of T

    void initialize(const TriOperator& T) // note: & is pass by reference, but putting a class in a variable declaration??
    {
        systemSize = T.systemSize;
        loDiag     = T.loDiag;
        diag       = T.diag;
        upDiag     = T.upDiag;
    };


    /**
    This initializer initializes the internal class data with entries
    of the n X n tridiagonal matrix T associated with the entries in
    the lower diagonal (loDiag), diagonal (diag), and upper diagonal (upDiag).
    */

    void initialize(long systemSize, vector<double>& loDiag,
              vector<double>& diag, vector<double>& upDiag)
    {
        this->systemSize = systemSize;
        this->loDiag     = loDiag;
        this->diag       = diag;
        this->upDiag     = upDiag;
    }

    /**
     The apply operator evaluates

     vOut = T*vIn

     where T is the tri-diagonal operator specified by the class constructor
     or initializer.

     Currently no bounds checking is performed.

    */


    void apply(vector<double>& vIn, vector<double>& vOut) //why don't you need to input diag, etc
		//(because it's in"internal data below"
    {
    long i;
    
    if(systemSize == 1)
    {
    vOut[0] = diag[0]*vIn[0]; return;
    }

    vOut[0] = diag[0]*vIn[0] + upDiag[0]*vIn[1];

    for(i = 1; i < systemSize-1; i++)
    {
    vOut[i] = loDiag[i-1]*vIn[i-1] + diag[i]*vIn[i] + upDiag[i]*vIn[i+1];
    }

    i = systemSize-1;
    vOut[i] = loDiag[i-1]*vIn[i-1] + diag[i]*vIn[i];
    }


    // Internal data


    long        systemSize;
    vector<double>  loDiag;
    vector<double>    diag;
    vector<double>  upDiag;

};

class TriSolver
{
public:

	/// Null Constructor -- called when you declare an instance

	TriSolver()
	{
		initialize();
	};

	/// Copy constructor (creates duplicate of T)

	TriOperator(const TriOperator& T) // called when you declare an instance with an existing instance, & is pass be ref, memory
	{
		initialize(T);
	};


	/**
	This constructor initializes the internal class data with entries
	of the n X n tridiagonal matrix T associated with the entries in
	the lower diagonal (loDiag), diagonal (diag), and upper diagonal (upDiag).
	*/

	TriOperator(long systemSize, vector<double>& loDiag, vector<double>& diag,
		vector<double>& upDiag)
	{
		initialize(systemSize, loDiag, diag, upDiag);
	}

	// Default destructor

	virtual ~TriOperator() {};

	/// Null initializer, resizes the internal arrays to zero length

	void initialize()
	{
		systemSize = 0;
		loDiag.clear();
		diag.clear();
		upDiag.clear();

	};

	///  Copy initializer. Duplicates the entries of T

	void initialize(const TriOperator& T) // note: & is pass by reference, but putting a class in a variable declaration??
	{
		systemSize = T.systemSize;
		loDiag = T.loDiag;
		diag = T.diag;
		upDiag = T.upDiag;
	};


	/**
	This initializer initializes the internal class data with entries
	of the n X n tridiagonal matrix T associated with the entries in
	the lower diagonal (loDiag), diagonal (diag), and upper diagonal (upDiag).
	*/

	void initialize(long systemSize, vector<double>& loDiag,
		vector<double>& diag, vector<double>& upDiag)
	{
		this->systemSize = systemSize;
		this->loDiag = loDiag;
		this->diag = diag;
		this->upDiag = upDiag;
	}

	/**
	The apply operator evaluates

	vOut = T*vIn

	where T is the tri-diagonal operator specified by the class constructor
	or initializer.

	Currently no bounds checking is performed.

	*/


	void apply(vector<double>& vIn, vector<double>& vOut) //why don't you need to input diag, etc
														  //(because it's in"internal data below"
	{
		long i;

		if (systemSize == 1)
		{
			vOut[0] = diag[0] * vIn[0]; return;
		}

		vOut[0] = diag[0] * vIn[0] + upDiag[0] * vIn[1];

		for (i = 1; i < systemSize - 1; i++)
		{
			vOut[i] = loDiag[i - 1] * vIn[i - 1] + diag[i] * vIn[i] + upDiag[i] * vIn[i + 1];
		}

		i = systemSize - 1;
		vOut[i] = loDiag[i - 1] * vIn[i - 1] + diag[i] * vIn[i];
	}


	// Internal data


	long        systemSize;
	vector<double>  loDiag;
	vector<double>    diag;
	vector<double>  upDiag;

};
// A specification of TriSolver class with "nothing in it". It's just
// a temporary specification with the absolutely minimum number
// of member functions implemented that will allow this
// program to compile and run.
//
// Since the apply member function of this
// version is just the identity, the errors in the
// computed solution of the linear system will be non-trivial.
//
// You will need to replace this class with your version of the
// TriSolver class as described in Assignment 1.
//


//
// Local utility function to set up the coefficients for the
// discrete system.
//
void setUpSystem(double h, double alpha, double beta, long M,
vector<double>& loDiag, vector<double>& diag, vector<double>& upDiag)
{
    loDiag.resize(M);
    upDiag.resize(M);
    diag.resize(M+1);

    long i;

    // First equation is the identity

    i = 0;
    diag[0]   =  1.0;
    upDiag[0] =  0.0;

    // Interior equation coefficients associated with a standard
    // second order finite difference approximation

    for(long i = 1; i < M; i++)
    {
    loDiag[i-1] =  alpha/(h*h);
    upDiag[i]   =  alpha/(h*h);
    diag[i]     = -2.0*alpha/(h*h) + beta;
    }


    // Last equation is the identity

    i          =    M;
    diag[M]    =  1.0;
    loDiag[M-1] = 0.0;
}


// Exact solution for problem (a)

double Exact_a(double x)
{
    return 1.0 + x;
}

int main()
{
    TriOperator tOperator;  // instantiate a forward operator --- calls null constructor
    TriSolver     tSolver;  // instantiate a forward operator inverse operator

    long   M      =   10; // 10 panels
    double alpha  =  2.0; // coefficients
    double beta   =  0.0;

    double xMin   =  0.0; // limits of the domain
    double xMax   =  1.0;
    double h      = (xMax-xMin)/(double)M;


    vector<double> loDiag;   // instantiating arrays for coefficients
    vector<double> upDiag;
    vector<double> diag;


    double u0; //what are these used for?
    double u1;


    vector<double> f(M+1,0.0);      // declaring solution and right hand side vectors
    vector<double> u(M+1,0.0);      // and initializing to zero.
    vector<double> fStar(M+1,0.0);

    double fErrorMax;


    // Assign boundary values to first and last element of right hand side

    f[0] =  1.0; //Change this based on BC
    f[M] =  2.0;


    for(long i = 1; i < M; i++)
    {
        f[i] = 0.0; // change this based on RHS of equation
    }

    // Setting up system. Outputs loDiag,diag,upDiag based on coefficients and number of panels

    setUpSystem(h, alpha, beta, M, loDiag, diag, upDiag); // finds loDiag, diag, and upDiag based of coefficients

    // Initializing the forward operator 

    tOperator.initialize(M+1,loDiag,diag,upDiag);

    // Initializing the inverse operator

    tSolver.initialize(M+1,loDiag,diag,upDiag);

    // Applying inverse

    tSolver.apply(f,u);

    // Applying forward operator to the result (to evaluate the residual): what is fstar? value of T*u from calculated u

    tOperator.apply(u,fStar); // outputs new fstar based on forward operator based on solution u just solved for

    // Determining the size of the residual and the size of the error

    double aErrorMax = 0.0; //solution error
    fErrorMax = 0.0; //residual error
    double errVal;
    double x;

    for(long i = 0; i <= M; i++)
    {
        x = xMin + i*h;
		//find max error with u (solution error)
        errVal = fabs(u[i] - Exact_a(x));

        if(aErrorMax < errVal) {
			aErrorMax = errVal;
		}
		//Now do the same thing with f (residual error)
        errVal = fabs(fStar[i] - f[i]);

        if(fErrorMax < errVal) {
			fErrorMax = errVal;
		}
    }


    // C style output using printf

    printf("(a) Residual error %20.15e \n",fErrorMax);
    printf("(a) Solution error %20.15e \n",aErrorMax);

    // C++ style output using the cout iostream

    cout.setf(ios::scientific); // Scientific notation
    cout.precision(15);         // 15 digits

    cout << endl;
    cout << "(a) Residual error " << fErrorMax << endl;
    cout << "(a) Solution error " << aErrorMax << endl;


    return 0;
}
