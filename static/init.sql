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

CREATE TABLE users
(
  uid       INTEGER PRIMARY KEY,
  username  TEXT,
  descr     TEXT
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

CREATE TABLE userAdm
(
  uid       INTEGER,
  key       TEXT,
  value     INTEGER,
  PRIMARY KEY(uid, key)
);

INSERT INTO users(uid, username, descr) VALUES
  (0, 'user', '');
INSERT INTO userAdm(uid, key, value) VALUES
  (0, 'div',  2);
INSERT INTO userAdm(uid, key, value) VALUES
  (0, 'mea',  2);
INSERT INTO userAdm(uid, key, value) VALUES
  (0, 'meaA', 2);
INSERT INTO userAdm(uid, key, value) VALUES
  (0, 'sys',  2);
INSERT INTO userAdm(uid, key, value) VALUES
  (0, 'sysA', 2);
INSERT INTO userAdm(uid, key, value) VALUES
  (0, 'sub',  2);

