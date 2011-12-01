DROP FUNCTION create_rule_e2d(text, text, text, text, text);

DROP FUNCTION r_create_user() CASCADE;
DROP FUNCTION r_update_user() CASCADE;
DROP FUNCTION r_delete_user() CASCADE;
DROP FUNCTION r_modify_user() CASCADE;

DROP TABLE  divisions CASCADE;
DROP TABLE  measures;
DROP TABLE  systems;
DROP TABLE  submissions;
DROP TABLE  users;

DROP TABLE  measureAdm;
DROP TABLE  systemAdm;
DROP TABLE  userAdm;

-- ########################################### RS ########################################### --
-- #                                         macros                                         # --
-- ########################################################################################## --

CREATE FUNCTION create_rule_e2d(rep_t text, t text, k0 text, k1 text, v0 text)
  RETURNS VOID AS $$
  BEGIN
    EXECUTE 'CREATE RULE '||rep_t||' AS
      ON INSERT TO '||t||'
      WHERE EXISTS
        (SELECT 1 FROM '||t||'
          WHERE '||k0||' = NEW.'||k0||'
            AND '||k1||' = NEW.'||k1||')
      DO INSTEAD
        (UPDATE '||t||'
            SET '||v0||' = NEW.'||v0||'
          WHERE '||k0||' = NEW.'||k0||'
            AND '||k1||' = NEW.'||k1||');';
  END; $$ LANGUAGE plpgsql;

-- ########################################### RS ########################################### --
-- #                                       divisions                                        # --
-- ########################################################################################## --

CREATE TABLE divisions
(
  id        BIGSERIAL PRIMARY KEY,
  ident     TEXT, 
  name      TEXT
);

-- ########################################### RS ########################################### --
-- #                                        measures                                        # --
-- ########################################################################################## --

CREATE TABLE measures
(
  id        BIGSERIAL PRIMARY KEY,
  ident     TEXT, 
  name      TEXT
);

CREATE TABLE measureAdm
(
  division  BIGINT,
  measure   BIGINT,
  weight    FLOAT8,
  PRIMARY KEY(division, measure)
);

-- ########################################################################################## --

SELECT create_rule_e2d('replace_measureAdm', 'measureAdm', 'division', 'measure', 'weight');

-- ########################################### RS ########################################### --
-- #                                        systems                                         # --
-- ########################################################################################## --

CREATE TABLE systems
(
  id        BIGSERIAL PRIMARY KEY,
  ident     TEXT, 
  name      TEXT
);

CREATE TABLE systemAdm
(
  division  BIGINT,
  system    BIGINT,
  weight    FLOAT8,
  PRIMARY KEY(division, system)
);

-- ########################################################################################## --

SELECT create_rule_e2d('replace_systemAdm', 'systemAdm', 'division', 'system', 'weight');

-- ########################################### RS ########################################### --
-- #                                      submissions                                       # --
-- ########################################################################################## --

CREATE TABLE submissions
(
  id        BIGSERIAL PRIMARY KEY,
  measure   BIGINT,
  count     BIGINT,
  date0     DATE, 
  date1     DATE
);

-- ########################################### RS ########################################### --
-- #                                         users                                          # --
-- ########################################################################################## --

CREATE TABLE users
(
  uid       BIGSERIAL PRIMARY KEY,
  username  TEXT,
  descr     TEXT
);

CREATE TABLE userAdm
(
  uid       BIGINT,
  key       TEXT,
  value     INTEGER,
  value1    TEXT,
  PRIMARY KEY(uid, key)
);

-- ########################################################################################## --

SELECT create_rule_e2d('replace_userAdm', 'userAdm', 'uid', 'key', 'value');

-- ########################################### RS ########################################### --
-- #                                         admin                                          # --
-- ########################################################################################## --

INSERT INTO users(uid, username, descr)
  VALUES(1, current_user, 'Administratorius');
INSERT INTO userAdm(uid, key, value) VALUES
  (1, 'usr',  2),
  (1, 'usrA', 2);

-- ########################################################################################## --

CREATE FUNCTION r_create_user()
  RETURNS TRIGGER AS $$ BEGIN
    EXECUTE 'CREATE ROLE '||NEW.username||' WITH LOGIN PASSWORD ''12345''';
    INSERT INTO userAdm(uid, key, value) VALUES
      (NEW.uid, 'div',  0),
      (NEW.uid, 'mea',  0),
      (NEW.uid, 'meaA', 0),
      (NEW.uid, 'sys',  0),
      (NEW.uid, 'sysA', 0),
      (NEW.uid, 'sub',  0),
      (NEW.uid, 'usr',  0),
      (NEW.uid, 'usrA', 0);
    RETURN NULL;
  END; $$ LANGUAGE plpgsql;

CREATE FUNCTION r_update_user()
  RETURNS TRIGGER AS $$ BEGIN
    EXECUTE 'ALTER ROLE '||username||' RENAME TO '||NEW.username;
    RETURN NULL;
  END; $$ LANGUAGE plpgsql;

CREATE FUNCTION r_delete_user()
  RETURNS TRIGGER AS $$ BEGIN
    EXECUTE 'DROP ROLE '||NEW.username;
    DELETE FROM userAdm WHERE uid = NEW.uid;
    RETURN NULL;
  END; $$ LANGUAGE plpgsql;

CREATE FUNCTION r_modify_user()
  RETURNS TRIGGER AS $$
  DECLARE
    t TEXT;
    u TEXT;
  BEGIN
    SELECT username INTO u FROM users WHERE uid = NEW.uid;

    t = CASE
      WHEN NEW.key = 'div'  THEN 'divisions'
      WHEN NEW.key = 'mea'  THEN 'measures'
      WHEN NEW.key = 'meaA' THEN 'measureAdm'
      WHEN NEW.key = 'sys'  THEN 'systems'
      WHEN NEW.key = 'sysA' THEN 'systemAdm'
      WHEN NEW.key = 'sub'  THEN 'submissions'
      WHEN NEW.key = 'usr'  THEN 'users'
      WHEN NEW.key = 'usrA' THEN 'userAdm'
      ELSE NULL
    END;

    IF t IS NOT NULL THEN
      EXECUTE 'REVOKE ALL ON TABLE '||t||' FROM '||u||';';
      IF NEW.value = 2 THEN
        EXECUTE 'GRANT ALL ON TABLE '||t||' TO '||u||';';
      ELSE
        EXECUTE 'GRANT SELECT ON TABLE '||t||' TO '||u||';';
      END IF;
    END IF;

    RETURN NULL;
  END; $$ LANGUAGE plpgsql;

-- ########################################################################################## --

CREATE TRIGGER user_insert AFTER INSERT ON users
  FOR EACH ROW EXECUTE PROCEDURE r_create_user();
CREATE TRIGGER user_update AFTER DELETE ON users
  FOR EACH ROW EXECUTE PROCEDURE r_update_user();
CREATE TRIGGER user_delete AFTER UPDATE ON users
  FOR EACH ROW EXECUTE PROCEDURE r_delete_user();
CREATE TRIGGER user_modify AFTER INSERT OR UPDATE ON userAdm
  FOR EACH ROW EXECUTE PROCEDURE r_modify_user();

-- ########################################################################################## --


