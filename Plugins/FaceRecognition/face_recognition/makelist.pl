#!/usr/bin/perl

# File name: makelist.pl
# Date:      2011-07-23 16:18
# Author:    Kristján Rúnarsson


$rootDirName="croppedyale_faces";
opendir(my($dh), $rootDirName) or die("Could not open: $rootDirName");
my @subDirs = readdir($dh);
closedir($dh);

my @trainingFiles;
my @testFiles;

open(TRAINING, "+>trainingfiles.txt") or die "Unable to open test file.";
open(TEST, "+>testfiles.txt") or die "Unable to open test file.";

for my $currSubDir (@subDirs)
{
	if($currSubDir eq '.' || $currSubDir eq '..' || $currSubDir eq '.DS_Store'){
		next;
	}

	$currSubDirPath = './'.$rootDirName.'/'.$currSubDir;
	opendir(my($dh), $currSubDirPath) or die("Could not open: $currSubDirPath");
	my @files = readdir($dh);
	closedir($dh);


	$currDirFileCounter=0;
	for my $file (@files){
		if($file eq '.' || $file eq '..' || $file eq '.DS_Store'|| index($file, "png")>-1){
			next;
		}

		#print "number: ".$currDirFileCounter."\n";
		#print "boolean: ".($currDirFileCounter < 2)."\n";
		#print "file: ".$file."\n";
		#print "---------------\n";

		@tuple[0] = $currSubDir;
		@tuple[1] = $file;
		if($currDirFileCounter < 0){
			#push(@trainingFiles, [@tuple]);
			print TRAINING $currSubDir.";".$currSubDirPath."/".$file."\n";
		} else {
			#push(@testFiles, [@tuple]);
			print TEST $currSubDir.";".$currSubDirPath."/".$file."\n";
		}
		$currDirFileCounter++;
	}
}

close(TRAINING);
close(TEST);



#for($i=0; $i<scalar@trainingFiles; $i++)
#{
#	print $i." ".$trainingFiles[$i][0]." ".$trainingFiles[$i][1]."\n";
#}
