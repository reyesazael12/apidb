
/**
 * 
 *  This file is part of apidb.
 * 
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * */

#include "apidb.hpp" 

#include <iostream>
#include <list>

int main()
{	
    //std::cout<<"Creating driver..."<<std::endl;
	apidb::MySQLDriver driver;
    //std::cout<<"Listing..."<<std::endl;
	if(driver.read())
	{
        //std::cout<<"Listing done."<<std::endl;
		if(driver.getListTable()->size() == 0)
		{            
			std::cout<< "no hay elemtos" <<std::endl;
		}
		else if(driver.getListTable()->size() == 1)
		{
			std::cout<< "\nHay " <<driver.getListTable()->size() <<" elemento."<<std::endl;
            for (apidb::internal::Table* n : *(driver.getListTable())) 
            {
                std::cout<<"" << n->table_name <<std::endl;
                for(apidb::internal::Table::Attribute* m : n->attributes)
                {
                    std::cout<<"  " << m->name<<std::endl;
                }
            }
		}	
		else if(driver.getListTable()->size() > 1)
		{
			std::cout<< "\nHay " <<driver.getListTable()->size() <<" elementos"<<std::endl;
            for (apidb::internal::Table* n : *(driver.getListTable())) 
            {
                std::cout<<" "<< n->table_name <<std::endl;
                for(apidb::internal::Table::Attribute* m : n->attributes)
                {
                    std::cout<<"  "<< m->name<<std::endl;
                }
            }
		}		
	}
	else
    {
        std::cerr<<"Not parsin phase"<<std::endl;
    }
	
	
	
	return 0;	
}
