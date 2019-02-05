/*
 *  LanguageCommon.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 8.7.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_LANGUAGE_COMMON_
#define ObjectCube_LANGUAGE_COMMON_

#include <string>

using namespace std;

namespace ObjectCube
{
	
	class LanguageCommon 
	{
		friend class Hub;
		
	public:
		LanguageCommon() {;}
		virtual ~LanguageCommon() {;}
		
	protected:
		static int getLanguageId_() { return languageId_; }
		static void setLanguageId_( int languageId ) { languageId_ = languageId; }
		static string getLanguageIdParameterName() { return languageIdParameterName_; }
		
	private:
		static int languageId_;
		static string languageIdParameterName_;
		
	public:		
		enum LANGUAGE
		{
			ICELANDIC = 1,
			ENGLISH = 2
		};
	};	
	
}

#endif
