#include <iostream>
#include <cstdio>

//#include <cppunit/extensions/TestFactoryRegistry.h>
//#include <cppunit/ui/text/TestRunner.h>

#include "UnitTests/SetupDataStorage.h"
#include "UnitTests/TestIds.h"

#include "LayerShared/Exception.h"
#include "LayerShared/Parameters.h"
#include "LayerShared/DebugInfo.h"

#include "Hub.h"

//DEBUG
//#include <fstream>

using namespace ObjectCube;

//Counting files: find . "(" -name "*.h" -or -name "*.cpp" ")" | wc -l
//Counting lines of code: find . "(" -name "*.h" -or -name "*.cpp" ")" -print | xargs wc -l

//File and line count is only for ObjectCube, not python wrapper code or plugins

// Date			Lines		Files

// 2010-02-18	 5.673
// 2010-02-20	 6.786
// 2010-03-25	 9.270
// 2010-03-30	11.438
// 2010-05-04	17.576		251
// 2010-06-07	20.879		290
// 2010-07-07	22.280		300 (This month mostly went into python wrapping and linux porting)
// 2010-07-09	22.521		314	(Last day before vacation)
// 2010-09-03	26.553		391 (After the large query generation refactoring)
// 2010-09-07	30.779		427	(After adding support for MonetDB)
// 2010-11-02	38.027		493
// 2010-11-18	38,667		495
// 2010-12-30	39,676		499

//Consider moving all pointers to TR1 std::shared_ptr<>
// #include <tr1/memory>, std::shared_ptr<>

#include "TagSet/AlphanumericalTagSet.h"
#include "TagSet/NumericalTagSet.h"
#include "Tag/AlphanumericalTag.h"
#include "DataAccess/Factories/TagSetDataAccessFactory.h"
#include "DataAccess/Root/TagSetDataAccess.h"
#include "Converters/TagSetConverter.h"

#include "Tag/AlphanumericalTag.h"
#include "Filters/DimensionFilter.h"

namespace ObjectCube 
{
	
class DebugTest
{
public:
	static void test()
	{
		//cout << "Start setDataAccessType" << endl;
		//Hub::setDataAccessType( Hub::POSTGRESQL );
        //cout << "End setDataAccessType" << endl;
        
        cout << "Start getHub" << endl;
        Hub* hub = Hub::getHub();
        cout << "End getHub" << endl;
        /*
        TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
        
        PersistentDimension* dimension = tagSet->getPersistentDimension( TEST_HIERARCHY_ID );
        PersistentHierarchyNode* node = dimension->getPersistentRoot();
        DimensionFilter filter( *node, tagSet->getId() );

        State state = State::getState();
        MultiDimensionalView mdv = state.getMultiDimensionalView();
    */
        
        try
        {
        //    Object created( "/PhotoCube/Pictures/Laugavegur/IMG_0075.jpg" );
            Object created( "/Image/mynd2.png" );
            Object returned = created.create();
            //returned.pluginProcess();
            
            
            //const_cast<ObjectTag*>( &returned.getTags()[1] )->confirmTagging();
          /*
            ObjectTag tagging = returned.getTags()[1];
            
            TagSet* tagSet = hub->getTagSet( tagging.getTag()->getTagSetId() );
            const Tag* tag = tagSet->fetchOrAddTag( "Gísli" );
            returned.updateTagging( tagging, tag );
            */
       
        }
        catch( ObjectCube::Exception e )
        {
            cerr << "Exception caught (main), location: " << e.where() << ".  What: " << e.what() << endl;
        }
        catch( exception e) 
        {
            fprintf(stderr, "Exception caught (main): %s \n", e.what() );
        }
        catch (...) 
        {
            fprintf( stderr, "Unknown error caught (main) \n");
        }

    
    }
};
	
}
/*
void unitTests()
{
	DebugInfo::getDebugInfo()->output( "main", "unitTests", "Starting cleanup!" );
	SetupDataStorage::getSetupDataStorage()->cleanup(); //Deletes test data, here for safety in case of crashes, post unit test cleanup should do the job in normal circumstances.
	DebugInfo::getDebugInfo()->output( "main", "unitTests", "Starting setup!" );
	SetupDataStorage::getSetupDataStorage()->setup(); //Inserts fresh data to test against
	
	CppUnit::TextUi::TestRunner runner;
	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
	runner.addTest( registry.makeTest() );
	runner.run();
		
	DebugInfo::getDebugInfo()->output( "main", "unitTests", "Starting post-test cleanup!" );
	//SetupDataStorage::getSetupDataStorage()->cleanup();
}
*/
int main (int argc, char * const argv[]) 
{
   try 
	{
		if( argc == 2 )
		{
			cout << "#" << argv[
                                1] << "#" << endl;
			if( string(argv[1]) == string("/parameters") )
			{
				cout << "ObjectCube supports the following parameters:\n";
				cout << "-SQLite\n";
				cout << "\tThe name of a SQLite DB and its path in a single string\n";
				cout << "-dataAccessType\n";
				cout << "\t1=Canned, 2=SQLite\n";
				cout << "-language\n";
				cout << "\t1=Icelandic, 2=English\n";
				cout << endl;
				cout << "Example:\n";
				cout << "./ObjectCube -SQLite ../Database/ObjectCubeDB -dataAccessType 2 -language 1 -unitTestObjectPath /Users/someuser/Dropbox/SQLite/UnitTest\n\n";
				return 0;
			}
		}
		
		//Parameters::getParameters()->process( argc, argv );
		
		//unitTests();
		//DebugInfo::getDebugInfo()->output("main", "End", "All tests were completed!" );
		
		DebugTest::test();
		
	}
	catch( ObjectCube::Exception e )
	{
		cerr << "Exception caught (main), location: " << e.where() << ".  What: " << e.what() << endl;
	}
	catch( exception e) 
	{
		fprintf(stderr, "Exception caught (main): %s \n", e.what() );
		return -1;
	}
	catch (...) 
	{
		fprintf( stderr, "Unknown error caught (main) \n");
		return -1;
	}
    return 0;
}












