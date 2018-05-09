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
#include "toolkit.hpp"

#include <iostream>
#include <mysql/my_global.h>
#include <mysql/mysql.h>

namespace apidb
{
    void internal::Table::import(void* r)
    {
        MYSQL_ROW* row = (MYSQL_ROW*)r;
        Attribute* attrribute = new Attribute();
        
        attrribute->name = (*row)[0];
        attrribute->type = (*row)[1];
        std::string requiered = (*row)[2];
        if(requiered.compare("YES"))
        {
            attrribute->required = true;
        }
        else if(requiered.compare("NO"))
        {
            attrribute->required = false;
        }
        attributes.push_back(attrribute);
    }
    
	void internal::RowsShowTables::import(void* r)
	{
		MYSQL_ROW* row = (MYSQL_ROW*)r;		
		Table* prw = new Table();
		prw->table_name = (*row)[0];
		push_back(prw);
	}
}
