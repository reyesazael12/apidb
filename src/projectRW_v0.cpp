
#include <cctype>
#include <fstream>
#include <cassert>
#include <sstream> 
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <map>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <filesystem>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>


#include "common.hpp"
#include "apidb.hpp"

#define BUFFERSIZE 1024
#define COPYMORE 0644

namespace apidb
{        
	bool ConfigureProject::saveConfig()
	{
		xmlDocPtr doc  = xmlNewDoc((const xmlChar *)"1.0");
		xmlNodePtr root_node = xmlNewNode(NULL, (const xmlChar *)"project");
		xmlDocSetRootElement(doc, root_node);
		
		xmlNewChild(root_node, NULL, (const xmlChar *)"name", (const xmlChar *)name.c_str());
		//xmlNewChild(root_node, NULL, (const xmlChar *)"directory", (const xmlChar *)directory.c_str());
				
		xmlNodePtr version_node = xmlNewChild(root_node, NULL, (const xmlChar *)"version", NULL);
		xmlNewChild(version_node, NULL, (const xmlChar *)"major", (const xmlChar *)std::to_string(version.getMajor()).c_str());
		xmlNewChild(version_node, NULL, (const xmlChar *)"minor", (const xmlChar *)std::to_string(version.getMinor()).c_str());
		xmlNewChild(version_node, NULL, (const xmlChar *)"patch", (const xmlChar *)std::to_string(version.getPatch()).c_str());
		//xmlNewChild(version_node, NULL, (const xmlChar *)"stage", (const xmlChar *)version.stage );
		
		xmlNodePtr db_node = xmlNewChild(root_node, NULL, (const xmlChar *)"ConectorDB", NULL);
		if(inputLenguaje == apidb::InputLenguajes::MySQL)
		{
			//toolkit::clientdb::DatconectionMySQL* dat = (toolkit::clientdb::DatconectionMySQL*)connector;
			xmlNewChild(db_node, NULL, (const xmlChar *)"host", (const xmlChar *)conectordb->getHost().c_str());
			xmlNewChild(db_node, NULL, (const xmlChar *)"port", (const xmlChar *)std::to_string(conectordb->getPort()).c_str());
			xmlNewChild(db_node, NULL, (const xmlChar *)"nameDB", (const xmlChar *)conectordb->getDatabase().c_str());
			xmlNewChild(db_node, NULL, (const xmlChar *)"user", (const xmlChar *)conectordb->getUser().c_str());
			xmlNewChild(db_node, NULL, (const xmlChar *)"pw", (const xmlChar *)conectordb->getPassword().c_str());
		}
		else
                {
                        return false;
                }
		
                std::string dirProy = "";
		if((directory.empty()) || (directory.compare(".") == 0))
		{
			dirProy = "apidb";
		}
		else
                {
                        dirProy = directory + "/apidb";
                }
                
                struct stat st = {0};
                if (stat(dirProy.c_str(), &st) == -1) 
                {
                        mkdir(dirProy.c_str(), 0700);
                }
                
                std::ofstream verFile (dirProy + "/version");
                verFile << apidb::getPakageVersion().toString()<< std::endl;
                verFile.flush();
                verFile.close();
                
                std::string xmlFile = dirProy + "/main.xml";                
		int ret = xmlSaveFormatFileEnc(xmlFile.c_str(), doc, "UTF-8", 1);	
		xmlFreeDoc(doc);
		xmlCleanupParser();
		if( ret == -1) return false;  
                             
                
		return true;
	}

	bool ConfigureProject::checkXML(xmlTextReaderPtr reader)
	{
		/*const xmlChar *name;
        name = xmlTextReaderConstName(reader);
        if(strcmp((const char*)name,"project") != 0)
        {
        	return false;
        }
        
        xmlTextReaderRead(reader);
        xmlTextReaderRead(reader);
        name = xmlTextReaderConstName(reader);
        if(strcmp((const char*)name,"name") != 0)
        {
        	return false;
        }*/
        
        
        
        return true;
	}
	
    bool ConfigureProject::getProjectNodes(xmlTextReaderPtr reader)
    {
        xmlTextReaderRead(reader);
        xmlTextReaderRead(reader);
        xmlTextReaderRead(reader);
        const xmlChar *name = xmlTextReaderConstName(reader);
        if(strcmp((const char*)name,"#text") == 0)
        {
            //std::cout<<"Find text."<<std::endl;   
            this->name = (const char*)xmlTextReaderConstValue(reader);
        }
                 
        
        xmlTextReaderRead(reader);
        xmlTextReaderRead(reader);
        xmlTextReaderRead(reader);
        xmlTextReaderRead(reader);
        xmlTextReaderRead(reader);
        name = xmlTextReaderConstName(reader);
        if(strcmp((const char*)name,"major") == 0)
        {
            xmlTextReaderRead(reader);
        }
        else
        {
            return true;
        }
        name = xmlTextReaderConstName(reader);
        short major = 0;
        if(strcmp((const char*)name,"#text") == 0)
        {  
            major = atoi((const char*)xmlTextReaderConstValue(reader));
        }
        

        xmlTextReaderRead(reader);
        xmlTextReaderRead(reader);
        xmlTextReaderRead(reader);
        name = xmlTextReaderConstName(reader);    
        if(strcmp((const char*)name,"minor") == 0)
        {
            xmlTextReaderRead(reader);
        }
        else
        {
            return true;
        }  
        name = xmlTextReaderConstName(reader);
        short minor = 0;
        if(strcmp((const char*)name,"#text") == 0)
        {
            minor = atoi((const char*)xmlTextReaderConstValue(reader));
        }
        

        xmlTextReaderRead(reader);
        xmlTextReaderRead(reader);
        xmlTextReaderRead(reader);
        xmlTextReaderRead(reader);
        xmlTextReaderRead(reader);
        name = xmlTextReaderConstName(reader);
        if(strcmp((const char*)name,"patch") == 0)
        {
            xmlTextReaderRead(reader);
        }
        else
        {
            return true;
        }
        name = xmlTextReaderConstName(reader);
        short patch = 0;
        if(strcmp((const char*)name,"#text") == 0)
        {
            patch = atoi((const char*)xmlTextReaderConstValue(reader));
        }
        
        this->version.setNumbers(major,minor,patch);
       // this->version.setStage(toolkit::Version::Stage::alpha);
        
        xmlTextReaderRead(reader);
        xmlTextReaderRead(reader);
        xmlTextReaderRead(reader);
        xmlTextReaderRead(reader);
        xmlTextReaderRead(reader);
        name = xmlTextReaderConstName(reader);
        if(strcmp((const char*)name,"host") == 0)
        {
            xmlTextReaderRead(reader);
        }
        else
        {
            return true;
        }
        name = xmlTextReaderConstName(reader);
        std::string host = "";
        if(strcmp((const char*)name,"#text") == 0)
        {
            host = (const char*)xmlTextReaderConstValue(reader);
        }
        
        xmlTextReaderRead(reader);
        xmlTextReaderRead(reader);
        xmlTextReaderRead(reader);
        name = xmlTextReaderConstName(reader);
        if(strcmp((const char*)name,"port") == 0)
        {
            xmlTextReaderRead(reader);
        }
        else
        {
            return true;
        }
        name = xmlTextReaderConstName(reader);
        int port = 0;
        if(strcmp((const char*)name,"#text") == 0)
        {
            port = atoi((const char*)xmlTextReaderConstValue(reader));
        }
        
        xmlTextReaderRead(reader);
        xmlTextReaderRead(reader);
        xmlTextReaderRead(reader);
        name = xmlTextReaderConstName(reader);
        if(strcmp((const char*)name,"nameDB") == 0)
        {
            xmlTextReaderRead(reader);
        }
        else
        {
            return true;
        }
        name = xmlTextReaderConstName(reader);
        std::string database = "";
        if(strcmp((const char*)name,"#text") == 0)
        {
            database = (const char*)xmlTextReaderConstValue(reader);
        }
        
        xmlTextReaderRead(reader);
        xmlTextReaderRead(reader);
        xmlTextReaderRead(reader);
        name = xmlTextReaderConstName(reader);
        if(strcmp((const char*)name,"user") == 0)
        {
            xmlTextReaderRead(reader);
        }
        else
        {
            return true;
        }
        name = xmlTextReaderConstName(reader);
        std::string user = "";
        if(strcmp((const char*)name,"#text") == 0)
        {
            user = (const char*)xmlTextReaderConstValue(reader);
        }
        
        xmlTextReaderRead(reader);
        xmlTextReaderRead(reader);
        xmlTextReaderRead(reader);
        name = xmlTextReaderConstName(reader);
        if(strcmp((const char*)name,"pw") == 0)
        {
            xmlTextReaderRead(reader);
        }
        else
        {
            return true;
        }
        name = xmlTextReaderConstName(reader);
        std::string password = "";
        if(strcmp((const char*)name,"#text") == 0)
        {
            password = (const char*)xmlTextReaderConstValue(reader);
        }
        
        conectordb = new toolkit::clientdb::mysql::Datconnect(host,port,database,user,password);
        
        return true;
    }


    bool ConfigureProject::processNode(xmlTextReaderPtr reader) 
    {
        const xmlChar *name = xmlTextReaderConstName(reader);

        if(xmlTextReaderNodeType(reader) == 1) //es d apertura?
        {        	
            if(checkXML(reader))
            {
                //std::cout<<(const char*)name<<std::endl;
                getProjectNodes(reader);
            }
            else
            {
            	std::cerr << "El XML no cumple con el formato requerido(el roden de los nodos es importante)" << std::endl;
            	return false;
            }
        }
        else if( xmlTextReaderNodeType(reader) == 15) //es d cerradura?
        {
            //stack.pop_front();
        }
        
        return true;
    }
    
}