#include "RPNCalc.h"

namespace SK_CALC
{

//-----------------------------------------------------------------------------
//		Class:			CRPNCalc
//		Method:			CRPNCalc(bool on)
//
//		Description:	constructor
// 
//		Parameters:		bool on -- whether calculator is on
// 
//		Returns:        n/a
//
//		History Log:
//						5/21/2014 SK completed version 1.0
// ----------------------------------------------------------------------------
	CRPNCalc::CRPNCalc(bool on)
	{
		//initialize all booleans
		m_error = false;
		m_helpOn = true;
		m_programRunning = false;
		//sets all registers to 0
		for (short i = 0; i < NUMREGS; i++)
			m_registers[i] = 0.0;
		
		if (m_on)
			run();
	} 
//-----------------------------------------------------------------------------
//		Class:			CRPNCalc
//		Method:			void run()
//
//		Description:	runs the calculator
// 
//		Parameters:		none
// 
//		Returns:        n/a
//
//		History Log:
//						5/21/2014 SK completed version 1.0
// ----------------------------------------------------------------------------
	void CRPNCalc::run()
	{
		print(cout);

		while (m_on)
		{
			input(cin);
			print(cout);
		}
	}
//-----------------------------------------------------------------------------
//		Class:			CRPNCalc
//		Method:			void print(ostream& ostr)
//
//		Description:	print method
// 
//		Parameters:		ostream& ostr -- stream to print to
// 
//		Returns:        n/a
//
//		History Log:
//						5/21/2014 SK completed version 1.0
// ----------------------------------------------------------------------------
	void CRPNCalc::print(ostream& ostr)
	{
		system("cls"); //clear screen after each print
		//print header and menu:
		ostr << "Welcome to RPN Programmable Calculator by Sarah Kazemian!" 
			<< endl << endl;
		if (m_helpOn)
			ostr << helpMenu << endl;
		ostr << line;

		if (!m_stack.empty())
			ostr <<  m_stack.front() << endl << endl;
		if (m_error)
		{
			ostr << "<<error>>" << endl;
			m_error = false;
		}

	}
//-----------------------------------------------------------------------------
//		Class:			CRPNCalc
//		Method:			void input(istream& istr)
//
//		Description:	input method
// 
//		Parameters:		istream& istr -- stream to read from
// 
//		Returns:        n/a
//
//		History Log:
//						5/21/2014 SK completed version 1.0
// ----------------------------------------------------------------------------
	void CRPNCalc::input(istream& istr)
	{
		istr >> m_buffer;
		m_instrStream.str(m_buffer);

		parse();
	}
//-----------------------------------------------------------------------------
//		Class:			CRPNCalc
//		Method:			void add()
//
//		Description:	method to add two numbers
// 
//		Parameters:		none
// 
//		Returns:        n/a
//
//		History Log:
//						6/2/2014 SK completed version 1.0
// ----------------------------------------------------------------------------
	void CRPNCalc::add()
	{
		double result = 0;
		if (binary_prep())
		{
			result = m_stack.at(1) + m_stack.at(0);
			m_stack.pop_front();
			m_stack.pop_front();
			m_stack.push_front(result);
		}
	}
//-----------------------------------------------------------------------------
//		Class:			CRPNCalc
//		Method:			void binary_prep(double& d1, double& d2)
//
//		Description:	method to prepare two numbers for an operation
// 
//		Parameters:		double& d1  -- the first number
	//					double& d2 -- the second number
// 
//		Returns:        n/a
//
//		History Log:
//						5/31/2014 SK completed version 1.0
// ----------------------------------------------------------------------------
	bool CRPNCalc::binary_prep()
	{
		if (m_stack.size() < 2)
		{
			m_error = true;
			return false;
		}
		else
			return true;
	}
//-----------------------------------------------------------------------------
//		Class:			CRPNCalc
//		Method:			void clearEntry()
//
//		Description:	method to clear one entry
// 
//		Parameters:		none
// 
//		Returns:        n/a
//
//		History Log:
//						5/21/2014 SK completed version 1.0
// ----------------------------------------------------------------------------
	void CRPNCalc::clearEntry()
	{
		m_stack.pop_front();
	}
//-----------------------------------------------------------------------------
//		Class:			CRPNCalc
//		Method:			void clearAll()
//
//		Description:	method to clear all entries
// 
//		Parameters:		none
// 
//		Returns:        n/a
//
//		History Log:
//						5/21/2014 SK completed v 1.0
//						6/2/2014 SK completed v 1.1
// ----------------------------------------------------------------------------
	void CRPNCalc::clearAll()
	{
		while (!m_stack.empty())
			m_stack.pop_front();
	}
//-----------------------------------------------------------------------------
//		Class:			CRPNCalc
//		Method:			void divide()
//
//		Description:	method to divide
// 
//		Parameters:		none
// 
//		Returns:        n/a
//
//		History Log:
//						5/21/2014 SK completed version 1.0
// ----------------------------------------------------------------------------
	void CRPNCalc::divide()
	{
		double result = 0;
		if (binary_prep())
		{
			if (m_stack.front() == 0) //doesn't allow division by zero
			{
				m_error = true;
				m_stack.pop_front();
			}
			else
			{
			result = m_stack.at(1) / m_stack.at(0);
			m_stack.pop_front();
			m_stack.pop_front();
			m_stack.push_front(result);
			}
		}
	}
//-----------------------------------------------------------------------------
//		Class:			CRPNCalc
//		Method:			void exp()
//
//		Description:	method to raise a number to a power
// 
//		Parameters:		none
// 
//		Returns:        n/a
//
//		History Log:
//						5/21/2014 SK completed version 1.0
// ----------------------------------------------------------------------------
	void CRPNCalc::exp()
	{
		double result = 0;
		if (binary_prep())
		{
			result = pow(m_stack.at(1), m_stack.at(0));
			m_stack.pop_front();
			m_stack.pop_front();
			m_stack.push_front(result);
		}
	}
//-----------------------------------------------------------------------------
//		Class:			CRPNCalc
//		Method:			void getReg(int reg)
//
//		Description:	get the value in a register
// 
//		Parameters:		int reg
// 
//		Returns:        n/a
//
//		History Log:
//						6/2/2014 SK completed version 1.0
//-----------------------------------------------------------------------------
	void CRPNCalc::getReg(int reg)
	{
		if (reg >= 0 && reg < NUMREGS)
			m_stack.push_front(m_registers[reg]);
		else
			m_error = true;
	}
//-----------------------------------------------------------------------------
//		Class:			CRPNCalc
//		Method:			void loadProgram()
//
//		Description:	method to load a program
// 
//		Parameters:		none
// 
//		Returns:        n/a
//
//		History Log:
//						6/2/2014 SK completed version 1.0
// ----------------------------------------------------------------------------
	void CRPNCalc::loadProgram()
	{
		ifstream ifs;
		string fileName;
		bool fileOkay = false;

		while (!fileOkay) //reprompt until file can be opened
		{
			cout << "Please enter program file:  ";
			cin >> fileName;

			if (fileName == "x" || fileName == "X")
				break;

			ifs.open(fileName.c_str());

			if(ifs.is_open())
			{
				fileOkay = true;
				m_program.clear(); //clear out any existing program

				while (!ifs.eof()) //until the eof is reached
				{
					for (string currentLine; getline(ifs, currentLine); )
						//add lines to the program
						m_program.push_back(currentLine); 
				}
			}

			else
			{
				cout << "Could not open file " << fileName << "." << endl;
				cin.ignore(256,'\n');
			}	
			ifs.close(); //close the file
		}

	}
//-----------------------------------------------------------------------------
//		Class:			CRPNCalc
//		Method:			void mod()
//
//		Description:	modulus method
// 
//		Parameters:		none
// 
//		Returns:        n/a
//
//		History Log:
//						6/2/2014 SK completed version 1.0
// ----------------------------------------------------------------------------
	void CRPNCalc::mod()
	{
		double result = 0;
		if (binary_prep())
		{
			result = fmod(m_stack.at(1), m_stack.at(0));
			m_stack.pop_front();
			m_stack.pop_front();
			m_stack.push_front(result);
		}
	}
//-----------------------------------------------------------------------------
//		Class:			CRPNCalc
//		Method:			void multiply()
//
//		Description:	multiplication method
// 
//		Parameters:		none
// 
//		Returns:        n/a
//
//		History Log:
//						6/2/2014 SK completed version 1.0
// ----------------------------------------------------------------------------
	void CRPNCalc::multiply()
	{
		double result = 0;
		if (binary_prep())
		{
			result = m_stack.at(1) * m_stack.at(0);
			m_stack.pop_front();
			m_stack.pop_front();
			m_stack.push_front(result);
		}
	}
//-----------------------------------------------------------------------------
//		Class:			CRPNCalc
//		Method:			void neg()
//
//		Description:	changes the sign of the top number
// 
//		Parameters:		none
// 
//		Returns:        n/a
//
//		History Log:
//						6/2/2014 SK completed version 1.0
// ----------------------------------------------------------------------------
	void CRPNCalc::neg()
	{
		if (unary_prep())
			*m_stack.begin() *= negOne;
	}
//-----------------------------------------------------------------------------
//		Class:			CRPNCalc
//		Method:			void parse()
//
//		Description:	method to parse the entered data
// 
//		Parameters:		none
// 
//		Returns:        n/a
//
//		History Log:
//						6/2/2014 SK completed version 1.0
// ----------------------------------------------------------------------------
	void CRPNCalc::parse()
	{
		string s = m_instrStream.str();
		// If s contains ANY char that is not a number, assume it is a symbol
		if (s.find_first_not_of("1234567890.") != s.npos) 
		{	
			switch(toupper(s[0]))
			{
			case '+': 
				add(); 
				break;
			case '-': 
				subtract(); 
				break;
			case '*': 
				multiply(); 
				break;
			case '/': 
				divide(); 
				break;
			case '^': 
				exp(); 
				break;
			case '%': 
				mod(); 
				break;
			case 'C': 
				if (toupper(s[1]) == 'E')
					clearEntry();
				else
					clearAll();
				break;
			case 'D': 
				rotateDown(); 
				break;
			case 'F': 
				saveToFile();
				break;
			case 'G': 
				getReg(s[1] - '0');
				break;
			case 'H': 
				m_helpOn = !m_helpOn;
				break;
			case 'L': 
				loadProgram(); 
				break;
			case 'M': 
				neg(); 
				break;
			case 'P': 
				recordProgram(); 
				break;
			case 'R': 
				runProgram(); 
				break;
			case 'S': 
				setReg(s[1] - '0');
				break;
			case 'U': 
				rotateUp(); 
				break;
			case 'X': 
				m_on = false;
				break;
			default:
				m_error = true;
				break;
			}
		}
		else //all chars are numbers or decimal point
			m_stack.push_front(stof(s.c_str()));
			
	}
//-----------------------------------------------------------------------------
//		Class:			CRPNCalc
//		Method:			void recordProgram()
//
//		Description:	method to record a program
// 
//		Parameters:		none
// 
//		Returns:        n/a
//
//		History Log:
//						6/2/2014 SK completed version 1.0
// ----------------------------------------------------------------------------
	void CRPNCalc::recordProgram()
	{
		string currentLine;
		bool recording = true;
		int lineNum = 0;

		m_program.clear(); //clear out any existing program

		while (recording)
		{
			cout << lineNum++ << "> "; // 0>  etc...
			cin >> currentLine;

			if (currentLine == "P" || currentLine == "p")
				recording = false;
			else
				m_program.push_back(currentLine); //add line
		}

	}
//-----------------------------------------------------------------------------
//		Class:			CRPNCalc
//		Method:			void rotateUp()
//
//		Description:	method to rotate the bottom number up
// 
//		Parameters:		none
// 
//		Returns:        n/a
//
//		History Log:
//						6/2/2014 SK completed version 1.0
// ----------------------------------------------------------------------------
	void CRPNCalc::rotateUp()
	{
		if (!m_stack.empty())
		{
			double moveNum = m_stack.back();
			m_stack.pop_back();
			m_stack.push_front(moveNum);
		}
		else
			m_error = true;
	}
//-----------------------------------------------------------------------------
//		Class:			CRPNCalc
//		Method:			void rotateDown()
//
//		Description:	method to rotate the top number down
// 
//		Parameters:		none
// 
//		Returns:        n/a
//
//		History Log:
//						6/2/2014 SK completed version 1.0
// ----------------------------------------------------------------------------
	void CRPNCalc::rotateDown()
	{
		if (!m_stack.empty())
		{
			double moveNum = m_stack.front();
			m_stack.pop_front();
			m_stack.push_back(moveNum);
		}
		else
			m_error = true;
	}
//-----------------------------------------------------------------------------
//		Class:			CRPNCalc
//		Method:			void runProgram()
//
//		Description:	method to run a program
// 
//		Parameters:		none
// 
//		Returns:        n/a
//
//		History Log:
//						6/2/2014 SK completed version 1.0
// ----------------------------------------------------------------------------
	void CRPNCalc::runProgram()
	{
		while (!m_program.empty())
		{
			//take program strings one at a time and parse them:
			m_instrStream.str(m_program.front());
			m_program.pop_front();
			
			parse();
		}
	}
//-----------------------------------------------------------------------------
//		Class:			CRPNCalc
//		Method:			void saveToFile()
//
//		Description:	method to save a program to a file
// 
//		Parameters:		none
// 
//		Returns:        n/a
//
//		History Log:
//						6/2/2014 SK completed version 1.0
// ----------------------------------------------------------------------------
	void CRPNCalc::saveToFile()
	{
		ofstream outFile;
		string fileName;
		bool fileOkay = false;

		while (!fileOkay) //reprompt until file can be opened
		{
			cout << "Please enter file to save program to:  ";
			cin >> fileName;
			outFile.open(fileName.c_str());

			if(outFile.is_open())
			{
				fileOkay = true;

				while (!m_program.empty())
				{
					outFile << m_program.front() << endl;
					m_program.pop_front();
				}
			}

			else
			{
				cout << "Could not open file " << fileName << "." << endl;
				cin.ignore(256,'\n');
			}	
		}
		cout << "Saved program to file " << fileName << "." << endl;
		cin.get();

		outFile.close(); //close the file
	}
//-----------------------------------------------------------------------------
//		Class:			CRPNCalc
//		Method:			void setReg()
//
//		Description:	method to set a register
// 
//		Parameters:		int reg -- register
// 
//		Returns:        n/a
//
//		History Log:
//						6/2/2014 SK completed version 1.0
// ----------------------------------------------------------------------------
	void CRPNCalc::setReg(int reg)
	{
		if (reg >= 0 && reg < NUMREGS)
			m_registers[reg] = m_stack.front();
		else
			m_error = true;
	}
//-----------------------------------------------------------------------------
//		Class:			CRPNCalc
//		Method:			void subtract()
//
//		Description:	subtraction method
// 
//		Parameters:		none
// 
//		Returns:        n/a
//
//		History Log:
//						6/2/2014 SK completed version 1.0
// ----------------------------------------------------------------------------
	void CRPNCalc::subtract()
	{
		double result = 0;
		if (binary_prep())
		{
			result = m_stack.at(1) - m_stack.at(0);
			m_stack.pop_front();
			m_stack.pop_front();
			m_stack.push_front(result);
		}
	}
//-----------------------------------------------------------------------------
//		Class:			CRPNCalc
//		Method:			bool unary_prep(double& d)
//
//		Description:	prepare for a unary operation
// 
//		Parameters:		double& d
// 
//		Returns:        bool -- true if successful, false otherwise
//
//		History Log:
//						6/2/2014 SK completed version 1.0
// ----------------------------------------------------------------------------
	bool CRPNCalc::unary_prep()
	{
		if (m_stack.empty())
			return false;
		else
			return true;
	}
//-----------------------------------------------------------------------------
//		Class:			CRPNCalc
//		Method:			ostream &operator <<(ostream &ostr, CRPNCalc &calc)
//
//		Description:	extraction operator
// 
//		Parameters:		ostream &ostr
//						CRPNCalc &calc
// 
//		Returns:        ostream &ostr
//
//		History Log:
//						6/2/2014 SK completed version 1.0
// ----------------------------------------------------------------------------
	ostream &operator <<(ostream &ostr, CRPNCalc &calc)
	{
		calc.print(cout);
		return ostr;
	}
//-----------------------------------------------------------------------------
//		Class:			CRPNCalc
//		Method:			istream &operator >>(istream &istr, CRPNCalc &calc)
//
//		Description:	insertion operator
// 
//		Parameters:		istream &istr
//						CRPNCalc &calc
// 
//		Returns:        istream &istr
//
//		History Log:
//						6/2/2014 SK completed version 1.0
// ----------------------------------------------------------------------------
	istream &operator >>(istream &istr, CRPNCalc &calc)
	{
		calc.input(cin);
		return istr;
	}
}
