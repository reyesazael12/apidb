#include "sysapp.hpp"
#include <iostream>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{	
        bool verbose = false;
        if(argc >1 )
        {
                if(strcmp(argv[1],"--verbose")==0)
                {
                        verbose = true;
                }
        }
        
	octetos::toolkit::clientdb::mysql::Datconnect mysqlConnector("192.168.0.101",3306,"sysappv2.alpha","develop","123456");  
        octetos::toolkit::clientdb::mysql::Connector connector; 
        bool flag = false;  
        try
        {
		flag = connector.connect(&mysqlConnector);
	}
	catch(octetos::toolkit::clientdb::SQLException& ex)
	{
		std::cerr<<ex.what()<< std::endl;
		return EXIT_FAILURE;
	}
        if(flag)
        {
                if(verbose)  printf("SQL Server version: %s\n", connector.serverDescription());
        }
        else
        {
                printf("Fallo la conexion el servidor.\n");
                        return EXIT_FAILURE;
        }
    
        srand (time(NULL));
	int random = rand() % 10000 + 1;
    
        sysapp::Persons person1;
        std::string n1 = "n1-";
        n1 += std::to_string(random);
        std::string ap = "ap-";
        ap += std::to_string(random);
        if(person1.insert(connector,n1,ap))
        {
		if(verbose)   std::cout << "Inserted "<< n1 << " " << ap << " de Mexico." << std::endl;
	}
	else
	{
		std::cerr << "Fail "<< n1 << std::endl;
		return EXIT_FAILURE;
	}
    
        if(connector.commit())
        {
		if(verbose)  std::cout << "Commit done " << std::endl;
	}
	else
	{
		std::cerr << "Commit fail"<< std::endl;
		return EXIT_FAILURE;
	}
	
        if(person1.shortname(connector))
        {
                if(verbose)   std::cout << ""<< person1.getName1() << " " << person1.getName3() << std::endl;
        }
        else
        {
                std::cout << "Fallo la descarga de person1" << std::endl;
		return EXIT_FAILURE;
        }

        if(verbose) std::cout << "Listando los que tiene 8 con 5 registro maximo." << std::endl;
        static std::vector<sysapp::Persons*>* lst = sysapp::Persons::select(connector,"name1 like 'n1-%8'",5);
        if(lst != NULL)
        {
                        for(auto p : *lst)
                        {
                        if(p->shortname(connector) and verbose)
                        {
                                if(verbose)  std::cout << ""<< p->getName1() << " " << p->getName3() << std::endl;
                        }
                        }
        }
        delete lst;
	
	
	connector.close();
	
	return EXIT_SUCCESS;
}

