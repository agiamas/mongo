

s = new ShardingTest( "diffservers1" , 2 );

assert.eq( 2 , s.config.servers.count() , "server count wrong" );
assert.eq( 2 , s._connections[0].getDB( "config" ).servers.count() , "where are servers!" );
assert.eq( 0 , s._connections[1].getDB( "config" ).servers.count() , "shouldn't be here" );

test1 = s.getDB( "test1" ).foo;
test1.save( { a : 1 } );
test1.save( { a : 2 } );
test1.save( { a : 3 } );
assert( 3 , test1.count() );

s.stop();

