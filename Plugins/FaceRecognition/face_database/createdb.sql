DROP TABLE IF EXISTS person;
DROP TABLE IF EXISTS face;
DROP TABLE IF EXISTS personNameSeq;
DROP TABLE IF EXISTS guiSeq;

CREATE TABLE IF NOT EXISTS person (
personSeqNum INTEGER NOT NULL PRIMARY KEY, 
realName TEXT NOT NULL UNIQUE);

CREATE TABLE IF NOT EXISTS personNameSeq (seqNum INTEGER);

INSERT INTO personNameSeq VALUES(0);

CREATE TABLE IF NOT EXISTS guiSeq (seqNum INTEGER);

INSERT INTO guiSeq VALUES(0);

CREATE TABLE IF NOT EXISTS face (
faceSeqNum INTEGER PRIMARY KEY AUTOINCREMENT, 
personSeqNum INTEGER, 
origImagePath TEXT NOT NULL, 
uLeftX INTEGER, 
uLeftY INTEGER, 
lRightX INTEGER, 
lRightY INTEGER, 
confirmed BOOLEAN NOT NULL,
training BOOLEAN NOT NULL,
recImagePath TEXT NOT NULL,
objectCubeID INTEGER,
FOREIGN KEY(personSeqNum) REFERENCES face(personSeqNum)); 

CREATE UNIQUE INDEX objectCube ON face (faceSeqNum,origImagePath,uLeftX,uLeftY,lRightX,lRightY);
