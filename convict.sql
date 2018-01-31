PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE User(Id INTEGER PRIMARY KEY,Name TEXT);
INSERT INTO "User" VALUES(1,'Gabriel');
INSERT INTO "User" VALUES(2,'Cristiane');
CREATE TABLE UserProgress(
  Id INTEGER PRIMARY KEY,
  UserSet INTEGER,
  UserSetPosition INTEGER
);
INSERT INTO "UserProgress" VALUES(1,1,1);
INSERT INTO "UserProgress" VALUES(2,1,1);
INSERT INTO "UserProgress" VALUES(3,1,1);
INSERT INTO "UserProgress" VALUES(4,1,1);
INSERT INTO "UserProgress" VALUES(5,1,1);
INSERT INTO "UserProgress" VALUES(6,1,1);
CREATE TABLE Status(
  Id INTEGER PRIMARY KEY,
  Routine INTEGER,
  Pushups INTEGER,
  Squats INTEGER,
  Pullups INTEGER,
  LegRaises INTEGER,
  Bridges INTEGER,
  HandstandPushups INTEGER
);
INSERT INTO "Status" VALUES(1,2,8,8,1,8,1,1);
CREATE TABLE Routine(Id INTEGER PRIMARY KEY,Name TEXT);
INSERT INTO "Routine" VALUES(1,'new blood');
INSERT INTO "Routine" VALUES(2,'good behavior');
INSERT INTO "Routine" VALUES(3,'veterano');
CREATE TABLE Day(Id INTEGER PRIMARY KEY, Name TEXT);
INSERT INTO "Day" VALUES(1,'Seg');
INSERT INTO "Day" VALUES(2,'Ter');
INSERT INTO "Day" VALUES(3,'Qua');
INSERT INTO "Day" VALUES(4,'Qui');
INSERT INTO "Day" VALUES(5,'Sex');
INSERT INTO "Day" VALUES(6,'Sab');
INSERT INTO "Day" VALUES(7,'Dom');
CREATE TABLE Movement(Id INTEGER PRIMARY KEY, Name TEXT);
INSERT INTO "Movement" VALUES(1,'Pushups');
INSERT INTO "Movement" VALUES(2,'Squats');
INSERT INTO "Movement" VALUES(3,'Pullups');
INSERT INTO "Movement" VALUES(4,'LegRaises');
INSERT INTO "Movement" VALUES(5,'Bridges');
INSERT INTO "Movement" VALUES(6,'HandstandPushups');
CREATE TABLE Pushups(Id INTEGER PRIMARY KEY, Name TEXT);
INSERT INTO "Pushups" VALUES(1,'wall pushups');
INSERT INTO "Pushups" VALUES(2,'incline pushups');
INSERT INTO "Pushups" VALUES(3,'kneeling pushups');
INSERT INTO "Pushups" VALUES(4,'half pushups');
INSERT INTO "Pushups" VALUES(5,'full pushups');
INSERT INTO "Pushups" VALUES(6,'close pushups');
INSERT INTO "Pushups" VALUES(7,'uneven pushups');
INSERT INTO "Pushups" VALUES(8,'1/2 one-arm pushups');
INSERT INTO "Pushups" VALUES(9,'lever pushups');
INSERT INTO "Pushups" VALUES(10,'one-arm pushups');
CREATE TABLE Squats(Id INTEGER PRIMARY KEY, Name TEXT);
INSERT INTO "Squats" VALUES(1,'shoulderstand squats');
INSERT INTO "Squats" VALUES(2,'jackknife squats');
INSERT INTO "Squats" VALUES(3,'supported squats');
INSERT INTO "Squats" VALUES(4,'half squats');
INSERT INTO "Squats" VALUES(5,'full squats');
INSERT INTO "Squats" VALUES(6,'close squats');
INSERT INTO "Squats" VALUES(7,'uneven squats');
INSERT INTO "Squats" VALUES(8,'1/2 one-leg squats');
INSERT INTO "Squats" VALUES(9,'assisted one-leg squats');
INSERT INTO "Squats" VALUES(10,'one-leg squats');
CREATE TABLE Pullups(Id INTEGER PRIMARY KEY, Name TEXT);
INSERT INTO "Pullups" VALUES(1,'vertical pullups');
INSERT INTO "Pullups" VALUES(2,'horizontal pullups');
INSERT INTO "Pullups" VALUES(3,'jackknife pullups');
INSERT INTO "Pullups" VALUES(4,'half pullups');
INSERT INTO "Pullups" VALUES(5,'full pullups');
INSERT INTO "Pullups" VALUES(6,'close pullups');
INSERT INTO "Pullups" VALUES(7,'uneven pullups');
INSERT INTO "Pullups" VALUES(8,'1/2 one-arm pullups');
INSERT INTO "Pullups" VALUES(9,'assisted one-arm pullups');
INSERT INTO "Pullups" VALUES(10,'one-arm pullups');
CREATE TABLE LegRaises(Id INTEGER PRIMARY KEY, Name TEXT);
INSERT INTO "LegRaises" VALUES(1,'knee tucks');
INSERT INTO "LegRaises" VALUES(2,'flat knee raises');
INSERT INTO "LegRaises" VALUES(3,'flat bent leg raises');
INSERT INTO "LegRaises" VALUES(4,'flat frog raises');
INSERT INTO "LegRaises" VALUES(5,'flat straight leg raises');
INSERT INTO "LegRaises" VALUES(6,'hanging knee raises');
INSERT INTO "LegRaises" VALUES(7,'hanging bent leg raises');
INSERT INTO "LegRaises" VALUES(8,'hanging frog raises');
INSERT INTO "LegRaises" VALUES(9,'partial straight leg raises');
INSERT INTO "LegRaises" VALUES(10,'hanging straight leg raises');
CREATE TABLE Bridges(Id INTEGER PRIMARY KEY, Name TEXT);
INSERT INTO "Bridges" VALUES(1,'short bridges');
INSERT INTO "Bridges" VALUES(2,'straight bridges');
INSERT INTO "Bridges" VALUES(3,'angled bridges');
INSERT INTO "Bridges" VALUES(4,'head bridges');
INSERT INTO "Bridges" VALUES(5,'half bridges');
INSERT INTO "Bridges" VALUES(6,'full bridges');
INSERT INTO "Bridges" VALUES(7,'wall walking bridges(down)');
INSERT INTO "Bridges" VALUES(8,'wall walking bridges(up)');
INSERT INTO "Bridges" VALUES(9,'closing bridges');
INSERT INTO "Bridges" VALUES(10,'stand-to-stand bridges');
CREATE TABLE HandstandPushups(Id INTEGER PRIMARY KEY, Name TEXT);
INSERT INTO "HandstandPushups" VALUES(1,'wall headstands');
INSERT INTO "HandstandPushups" VALUES(2,'crow stands');
INSERT INTO "HandstandPushups" VALUES(3,'wall handstands');
INSERT INTO "HandstandPushups" VALUES(4,'half handstand pushups');
INSERT INTO "HandstandPushups" VALUES(5,'handstand pushups');
INSERT INTO "HandstandPushups" VALUES(6,'close handstand pushups');
INSERT INTO "HandstandPushups" VALUES(7,'uneven handstand pushups');
INSERT INTO "HandstandPushups" VALUES(8,'1/2 one-arm handstand pushups');
INSERT INTO "HandstandPushups" VALUES(9,'lever handstand pushups');
INSERT INTO "HandstandPushups" VALUES(10,'one-arm handstand pushups');
CREATE TABLE Set1(Id INTEGER PRIMARY KEY, Rest INTEGER, Set1 INTEGER, Set2 INTEGER, Set3 INTEGER, Set4 INTEGER, Set5 INTEGER, Set6 INTEGER, Set7 INTEGER, Set8 INTEGER);
INSERT INTO "Set1" VALUES(1,60,2,3,2,2,3,0,0,0);
INSERT INTO "Set1" VALUES(2,60,3,4,2,3,4,0,0,0);
INSERT INTO "Set1" VALUES(3,60,4,5,4,4,5,0,0,0);
INSERT INTO "Set1" VALUES(4,60,4,6,4,4,6,0,0,0);
INSERT INTO "Set1" VALUES(5,60,5,6,4,4,7,0,0,0);
INSERT INTO "Set1" VALUES(6,60,5,7,5,5,8,0,0,0);
INSERT INTO "Set1" VALUES(7,60,10,12,7,7,9,0,0,0);
INSERT INTO "Set1" VALUES(8,60,10,12,8,8,12,0,0,0);
INSERT INTO "Set1" VALUES(9,60,11,13,9,9,13,0,0,0);
INSERT INTO "Set1" VALUES(10,60,12,14,11,10,16,0,0,0);
INSERT INTO "Set1" VALUES(11,60,14,16,12,12,18,0,0,0);
INSERT INTO "Set1" VALUES(12,60,16,18,13,13,20,0,0,0);
INSERT INTO "Set1" VALUES(13,60,17,19,15,15,20,0,0,0);
INSERT INTO "Set1" VALUES(14,45,10,10,13,13,10,10,9,25);
INSERT INTO "Set1" VALUES(15,45,13,13,15,15,12,12,10,30);
INSERT INTO "Set1" VALUES(16,60,17,19,15,15,20,0,0,0);
INSERT INTO "Set1" VALUES(17,45,10,10,13,13,10,10,9,25);
INSERT INTO "Set1" VALUES(18,45,13,13,15,15,12,12,10,30);
CREATE TABLE Set2(Id INTEGER PRIMARY KEY, Rest INTEGER, Set1 INTEGER, Set2 INTEGER, Set3 INTEGER, Set4 INTEGER, Set5 INTEGER, Set6 INTEGER, Set7 INTEGER, Set8 INTEGER);
INSERT INTO "Set2" VALUES(1,60,6,6,4,4,5,0,0,0);
INSERT INTO "Set2" VALUES(2,60,6,8,6,6,7,0,0,0);
INSERT INTO "Set2" VALUES(3,60,8,10,7,7,10,0,0,0);
INSERT INTO "Set2" VALUES(4,60,9,11,8,8,11,0,0,0);
INSERT INTO "Set2" VALUES(5,60,10,12,9,9,13,0,0,0);
INSERT INTO "Set2" VALUES(6,60,12,13,10,10,15,0,0,0);
INSERT INTO "Set2" VALUES(7,60,12,17,13,13,17,0,0,0);
INSERT INTO "Set2" VALUES(8,60,14,19,14,14,19,0,0,0);
INSERT INTO "Set2" VALUES(9,60,16,21,15,15,21,0,0,0);
INSERT INTO "Set2" VALUES(10,60,18,22,16,16,25,0,0,0);
INSERT INTO "Set2" VALUES(11,60,20,25,20,20,28,0,0,0);
INSERT INTO "Set2" VALUES(12,60,23,28,23,23,33,0,0,0);
INSERT INTO "Set2" VALUES(13,60,28,35,25,22,35,0,0,0);
INSERT INTO "Set2" VALUES(14,45,18,18,20,20,14,14,16,40);
INSERT INTO "Set2" VALUES(15,45,18,18,20,20,17,17,20,45);
INSERT INTO "Set2" VALUES(16,60,28,35,25,22,35,0,0,0);
INSERT INTO "Set2" VALUES(17,45,18,18,20,20,14,14,16,40);
INSERT INTO "Set2" VALUES(18,45,18,18,20,20,17,17,20,45);
CREATE TABLE Set3(Id INTEGER PRIMARY KEY, Rest INTEGER, Set1 INTEGER, Set2 INTEGER, Set3 INTEGER, Set4 INTEGER, Set5 INTEGER, Set6 INTEGER, Set7 INTEGER, Set8 INTEGER);
INSERT INTO "Set3" VALUES(1,60,10,12,7,7,9,0,0,0);
INSERT INTO "Set3" VALUES(2,60,10,12,8,8,12,0,0,0);
INSERT INTO "Set3" VALUES(3,60,11,15,9,9,13,0,0,0);
INSERT INTO "Set3" VALUES(4,60,14,14,10,10,15,0,0,0);
INSERT INTO "Set3" VALUES(5,60,14,16,12,12,17,0,0,0);
INSERT INTO "Set3" VALUES(6,60,16,17,14,14,20,0,0,0);
INSERT INTO "Set3" VALUES(7,60,14,18,14,14,20,0,0,0);
INSERT INTO "Set3" VALUES(8,60,20,25,15,15,25,0,0,0);
INSERT INTO "Set3" VALUES(9,60,22,30,20,20,28,0,0,0);
INSERT INTO "Set3" VALUES(10,60,21,25,21,21,32,0,0,0);
INSERT INTO "Set3" VALUES(11,60,25,29,25,25,36,0,0,0);
INSERT INTO "Set3" VALUES(12,60,29,33,29,29,40,0,0,0);
INSERT INTO "Set3" VALUES(13,60,36,40,30,24,40,0,0,0);
INSERT INTO "Set3" VALUES(14,45,19,19,22,22,18,18,22,45);
INSERT INTO "Set3" VALUES(15,45,20,20,24,24,20,20,22,50);
INSERT INTO "Set3" VALUES(16,60,36,0,30,24,40,0,0,0);
INSERT INTO "Set3" VALUES(17,45,19,19,22,22,18,18,22,45);
INSERT INTO "Set3" VALUES(18,45,20,20,24,24,20,20,22,50);
CREATE TABLE Set0(Id INTEGER PRIMARY KEY, Description TEXT, Set1 INTEGER, Set2 INTEGER, Set3 INTEGER);
INSERT INTO "Set0" VALUES(1,'Beginner',10,0,0);
INSERT INTO "Set0" VALUES(2,'Intermediate',20,20,0);
INSERT INTO "Set0" VALUES(3,'Progression',40,40,40);
CREATE TABLE Progress(Routine INTEGER, Day INTEGER, Movement INTEGER);
INSERT INTO "Progress" VALUES(1,1,1);
INSERT INTO "Progress" VALUES(1,1,4);
INSERT INTO "Progress" VALUES(1,5,3);
INSERT INTO "Progress" VALUES(1,5,2);
INSERT INTO "Progress" VALUES(2,1,1);
INSERT INTO "Progress" VALUES(2,1,4);
INSERT INTO "Progress" VALUES(2,3,3);
INSERT INTO "Progress" VALUES(2,3,2);
INSERT INTO "Progress" VALUES(2,5,6);
INSERT INTO "Progress" VALUES(2,5,5);
INSERT INTO "Progress" VALUES(3,1,3);
INSERT INTO "Progress" VALUES(3,2,5);
INSERT INTO "Progress" VALUES(3,3,6);
INSERT INTO "Progress" VALUES(3,4,4);
INSERT INTO "Progress" VALUES(3,5,2);
INSERT INTO "Progress" VALUES(3,6,1);
CREATE TABLE ProgressionIndex(
  Id INTEGER PRIMARY KEY,
  Pushups INTEGER,
  Squats INTEGER,
  Pullups INTEGER,
  LegRaises INTEGER,
  Bridges INTEGER,
  HandstandPushups INTEGER
);
INSERT INTO "ProgressionIndex" VALUES(1,5,5,5,5,1,1);
COMMIT;
