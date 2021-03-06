// engine.cpp

#include "stdafx.h"
#include "engine.h"
#include "../util/file.h"

namespace mongo {
    
    Scope::Scope(){
    }

    Scope::~Scope(){
    }

    ScriptEngine::ScriptEngine(){
    }

    ScriptEngine::~ScriptEngine(){
    }

    int Scope::invoke( const char* code , const BSONObj& args, int timeoutMs ){
        ScriptingFunction func = createFunction( code );
        uassert( "compile failed" , func );
        return invoke( func , args, timeoutMs );
    }

    bool Scope::execFile( const string& filename , bool printResult , bool reportError , bool assertOnError, int timeoutMs ){
        
        path p( filename );
        if ( is_directory( p ) ){
            cerr << "can't read directory [" << filename << "]" << endl;
            if ( assertOnError )
                assert( 0 );
            return false;
        }
         
        File f;
        f.open( filename.c_str() );
        
        char * data = (char*)malloc( f.len() + 1 );
        data[f.len()] = 0;
        
        f.read( 0 , data , f.len() );
        
        return exec( data , filename , printResult , reportError , assertOnError, timeoutMs );
    }



    ScriptEngine * globalScriptEngine;
}
