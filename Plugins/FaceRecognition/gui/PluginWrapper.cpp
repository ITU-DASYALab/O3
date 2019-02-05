/*
Project: hsimage
File: PluginWrapper.cpp
Developer: Hlynur Sigurþórsson (hlynursigurthorsson@gmail.com)
Timestamp: Fall, 2011.
*/

#include "../face_database/MySQLite.h"
#include "PluginWrapper.h"
#include <iostream>
#include <stdexcep>


// Global static pointer used to ensure a single instance of the class.
PluginWrapper* PluginWrapper::m_pInstance = NULL;


PluginWrapper* PluginWrapper::instance() {
    if (!m_pInstance){
        m_pInstance = new PluginWrapper();
	}
    return m_pInstance;
}


int PluginWrapper::get_unique_id()
{
        MySQLite db;

        db.beginTransaction();

        int newSeqNum = -1;
        try
        {
                stringstream select;
                select << "select * from guiSeq;";

                char** result =  db.getTable(select.str());

                int oldSeqNum = atoi(result[1]);

                newSeqNum = oldSeqNum + 1;

                stringstream update;
                update << "UPDATE guiSeq SET seqNum="<< newSeqNum << " WHERE seqNum=" << oldSeqNum ;

                db.getTable(update.str());
        }
        catch(runtime_error e)
        {
                db.rollbackTransaction();
                throw e;
        }

        db.commitTransaction();

        return newSeqNum;
}


