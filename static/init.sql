CREATE TABLE divisions
(
  id        INTEGER PRIMARY KEY, 
  ident     TEXT, 
  name      TEXT
);

CREATE TABLE measures
(
  id        INTEGER PRIMARY KEY, 
  ident     TEXT, 
  name      TEXT
);

CREATE TABLE systems
(
  id        INTEGER PRIMARY KEY, 
  ident     TEXT, 
  name      TEXT
);
CREATE TABLE submissions
(
  id        INTEGER PRIMARY KEY, 
  measure   INTEGER, 
  count     INTEGER, 
  date0     DATE, 
  date1     DATE
);

CREATE TABLE measureAdm
(
  division  INTEGER,
  measure   INTEGER,
  weight    DOUBLE,
  PRIMARY KEY(division, measure)
);

CREATE TABLE systemAdm
(
  division  INTEGER,
  system    INTEGER,
  weight    DOUBLE,
  PRIMARY KEY(division, system)
);
