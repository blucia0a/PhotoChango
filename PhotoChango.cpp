/*
 *  PhotoChango.cpp
 *  Sin
 *
 *  Created by blucia0a on 8/25/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#include "SinGen.h"
#include "FrameAcquirer.h"

int main(int argc, char *argv[]){
	
	fprintf(stderr,"PhotoChango - Brandon Lucia 2011 - Audiolyze the world! [http://cs.washington.edu/homes/blucia0a]\n");
	
	SinGen *s = new SinGen();
	s->setup();
	s->sstart();
	
	FrameAcquirer *f = new FrameAcquirer(s);
}

