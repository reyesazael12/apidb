#include <cctype>
#include <fstream>
#include <cassert>
#include <sstream> 

#include "analyzer.hpp"
namespace octetos
{
namespace apidb
{	
	
	

	
	std::ostream& Analyzer::getErrorMessage()
	{
		return *errorMessages;
	}		
	std::ostream& Analyzer::getOutputMessage()
	{
		return *outputMessages;
	}
	Analyzer::~Analyzer()
	{
                if(outputMessages != NULL)
                {
                        outputMessages = NULL;                        
                }
                if(errorMessages != NULL)
                {
                        errorMessages = NULL;                        
                }
	}
	Analyzer::Analyzer(const ConfigureProject& config,octetos::toolkit::clientdb::Connector* conn) : configureProject(config), connector(conn)
	{
	}
	OutputLenguajes Analyzer::getOutputLenguaje() const
	{
		return configureProject.outputLenguaje;
	}
	std::map<const char*,symbols::Tables*,symbols::cmp_str> Analyzer::copyListTable() const
	{
		return spacies;
	}	
	const std::map<const char*,symbols::Tables*,symbols::cmp_str>& Analyzer::getListTableConst() const
	{
		return spacies;
	}
	std::map<const char*,symbols::Tables*,symbols::cmp_str>& Analyzer::getListTable() 
	{
		return spacies;
	}		
	const std::string& Analyzer::getNameProject()
	{
		return configureProject.name;
	}		
	/*const std::string& Analyzer::getDirectoryProject()
	{
		return configureProject.directory;
	}*/	
	InputLenguajes Analyzer::getInputLenguaje()const
	{
		return configureProject.inputLenguaje;
	}
}
}
