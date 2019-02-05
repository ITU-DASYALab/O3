begin;
DROP TABLE IF EXISTS plugin_tag_set CASCADE;
DROP TABLE IF EXISTS plugin CASCADE;
DROP TABLE IF EXISTS dimension CASCADE;
DROP TABLE IF EXISTS dimension_tag_object CASCADE;
DROP TABLE IF EXISTS object_tag CASCADE;
DROP TABLE IF EXISTS object CASCADE;
DROP TABLE IF EXISTS time_tag CASCADE;
DROP TABLE IF EXISTS date_tag CASCADE;
DROP TABLE IF EXISTS numerical_tag CASCADE;
DROP TABLE IF EXISTS rgb_tag CASCADE;
DROP TABLE IF EXISTS alphanumerical_tag CASCADE;
DROP TABLE IF EXISTS tag CASCADE;
DROP TABLE IF EXISTS tag_type CASCADE;
DROP TABLE IF EXISTS tag_set CASCADE;
DROP TABLE IF EXISTS tag_set_type CASCADE;
DROP TABLE IF EXISTS tag_set_access CASCADE;
DROP TABLE IF EXISTS filter_type CASCADE;
DROP TABLE IF EXISTS language CASCADE;
DROP TABLE IF EXISTS translation CASCADE;
commit;

begin;

create extension if not exists btree_gist;
create extension if not exists postgis;
create extension if not exists cube;

CREATE TABLE tag_set_access (
    id int PRIMARY KEY NOT NULL,
    description varchar(30) NOT NULL
);

CREATE UNIQUE INDEX tag_set_access_description_u ON tag_set_access ("description" ASC);

CREATE TABLE tag_set_type (
    id int PRIMARY KEY NOT NULL,
    description varchar(30) NOT NULL unique
);

CREATE UNIQUE INDEX tag_set_type_description_u ON tag_set_type ("description" ASC);

CREATE TABLE tag_set (
    id serial PRIMARY KEY NOT NULL,
    name varchar(250) NOT NULL,
    description varchar(500),
    type_id int NOT NULL references tag_set_type("id"),
    access_id int NOT NULL references tag_set_access("id")
);

CREATE UNIQUE INDEX tag_set_name_u ON tag_set ("name" ASC);

CREATE TABLE tag_type (
	id int PRIMARY KEY  NOT NULL, 
	description varchar(250) NOT NULL 
);

CREATE UNIQUE INDEX tag_type_description_u ON tag_type("description" ASC);

CREATE TABLE tag (
   	id serial PRIMARY KEY NOT NULL,
    tag_set_id int NOT NULL references tag_set("id"),
    type_id int NOT NULL references tag_type("id")
);

create index tag_tag_set_id_i on tag( "tag_set_id" );

CREATE TABLE rgb_tag (
	id int primary key not null references tag("id"),
	rgb cube,
	tag_set_id int not null references tag_set("id")
);

CREATE INDEX tag_rgb_id ON rgb_tag USING gist(rgb);

CREATE TABLE alphanumerical_tag (
	id int primary key not null references tag("id"),
	tag_string text not null,
	tag_set_id int not null references tag_set("id")
);

CREATE UNIQUE INDEX alphanum_tag_string_tag_set_u on alphanumerical_tag("tag_string", "tag_set_id");

create materialized view alphanumerical_tag_materialized_view as
select id, to_tsvector('english', tag_string) as tag_string, tag_set_id
from alphanumerical_tag; 


CREATE INDEX idx_fts_materialized_view_search ON alphanumerical_tag_materialized_view USING gin(tag_string);

CREATE TABLE numerical_tag (
	id int primary key not null references tag("id"),
	number int not null,
	tag_set_id int not null references tag_set("id")
);

CREATE UNIQUE INDEX numerical_tag_number_tag_set_u on numerical_tag("number", "tag_set_id" );

CREATE INDEX numerical_tag_number_id_i on numerical_tag( "number", "id" );

CREATE TABLE date_tag (
	id int primary key not null references tag("id"),
	tag_date varchar(150) not null,
	tag_set_id int not null references tag_set("id")
);

CREATE UNIQUE INDEX date_tag_date_tag_set_u on date_tag( "tag_date", "tag_set_id" );

CREATE INDEX date_tag_date_id_i on date_tag( "tag_date", "id" );

CREATE TABLE time_tag (
	id int primary key not null references tag("id"),
	tag_time varchar(150) not null,
	tag_set_id int not null references tag_set("id")
);

CREATE UNIQUE INDEX time_tag_time_tag_set_u on time_tag( "tag_time", "tag_set_id" );

CREATE INDEX time_tag_time_id_i on time_tag( "tag_time", "id" );

CREATE TABLE object(
    id serial PRIMARY KEY NOT NULL,    
	qualified_name varchar(150) NOT NULL,
	thumbnail varchar(150),
	file_type varchar(10)
);

CREATE UNIQUE INDEX object_qualified_name_u on object("qualified_name");

CREATE TABLE object_tag (
    object_id int NOT NULL references object("id"),
    tag_id int NOT NULL references tag("id"),
    confirmed int,
    upper_left_x int,
    upper_left_y int,
    lower_right_x int,
    lower_right_y int,
    PRIMARY KEY( "object_id", "tag_id")
);

CREATE INDEX tag_id_u on object_tag("tag_id");

CREATE TABLE dimension (
	id serial NOT NULL,
	node_id int not null,
	tag_set_id int not null references tag_set("id"),
	tag_id int not null references tag("id"),
	child_category_title varchar(50),
	left_border int not null,
	right_border int not null,
	primary key("id", "node_id")
);

CREATE UNIQUE INDEX dimension_id_tag_id_u on dimension("id", "tag_id");

CREATE TABLE dimension_tag_object (
	id serial NOT NULL,
	dimension_id int NOT NULL,
	node_id int not null,
	tag_id int not null references tag("id"),
	object_id int not null references object("id"),
	upper_left_x int,
    upper_left_y int,
    lower_right_x int,
    lower_right_y int,
	confirmed int,
	left_border int not null,
	right_border int not null,
	primary key("id", "dimension_id")
);

CREATE TABLE plugin (
	id serial PRIMARY KEY NOT NULL , 
	qualified_library_name varchar(150) NOT NULL, 
	description varchar(500)
);

CREATE UNIQUE INDEX plugin_name_u ON plugin("qualified_library_name" ASC);

CREATE TABLE plugin_tag_set(
	id serial PRIMARY KEY NOT NULL , 
	plugin_id int not null references plugin("id"),
	tag_set_type_id int not null references tag_set_type("id"),
	tag_type_id int not null references tag_type("id"),
	name varchar(100) not null,
	tag_set_name varchar(100) not null,
	tag_set_id int references tag_set("id")
);

CREATE UNIQUE INDEX plugin_tag_set_plugin_name_u on plugin_tag_set( "plugin_id", "name" );

CREATE UNIQUE INDEX plugin_tag_set_id_name_u on plugin_tag_set( "plugin_id", "tag_set_name" );

CREATE TABLE filter_type (
	id int PRIMARY KEY  NOT NULL, 
	description varchar(30) NOT NULL 
);

CREATE UNIQUE INDEX filter_type_description_u ON filter_type ("description" ASC);

CREATE TABLE language (
	id int PRIMARY KEY NOT NULL, 
	description varchar(100) NOT NULL 
);

CREATE UNIQUE INDEX language_description_u ON language("description" ASC);

CREATE TABLE translation (
    id serial primary key not null,
    entity_name varchar(50) not null,
    entity_id int not null,
    language_id int not null references language("id"),
    translated_text varchar(100) not null
);

end;

--Insert Data
begin;
INSERT INTO tag_set_access values(1, 'System');
INSERT INTO tag_set_access values(2, 'User');

INSERT INTO tag_set_type values(1, 'Alphanumerical tag-set');
INSERT INTO tag_set_type values(2, 'Numerical tag-set');
INSERT INTO tag_set_type values(3, 'Date tag-set');
INSERT INTO tag_set_type values(4, 'Time tag-set');
INSERT INTO tag_set_type values(5, 'RGB tag-set');

INSERT INTO tag_type values(1, 'Alphanumerical tag');
INSERT INTO tag_type values(2, 'Numerical tag');
INSERT INTO tag_type values(3, 'Date tag');
INSERT INTO tag_type values(4, 'Time tag');
INSERT INTO tag_type values(5, 'RGB tag');

INSERT INTO FILTER_TYPE VALUES( 1, 'Tag filter');
INSERT INTO FILTER_TYPE VALUES( 2, 'Dimension filter');
INSERT INTO FILTER_TYPE VALUES( 3, 'Numerical range filter');
INSERT INTO FILTER_TYPE VALUES( 4, 'Time range filter');
INSERT INTO FILTER_TYPE VALUES( 5, 'Date range filter');

INSERT INTO LANGUAGE VALUES( 1, 'Íslenska');
INSERT INTO LANGUAGE VALUES( 2, 'English');

-- Uncategorized support
INSERT INTO tag_set ( "name", "description", "type_id", "access_id" ) values( 'UNCATEGORIZED', 'A system tag-set for the Uncategorized tag', 1, 1);
INSERT INTO tag ("tag_set_id", "type_id") values( ( select max("id") from tag_set ), 1);
INSERT INTO alphanumerical_tag values( (select max("id") from tag), 'Uncategorized', (select max("id") from tag_set));

INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'TagType', 1, 1, 'Texta tag' );
INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'TagType', 2, 1, 'Númerískt tag' );
INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'TagType', 3, 1, 'Dagsetningar tag' );
INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'TagType', 4, 1, 'Tíma tag' );
INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'TagType', 5, 1, 'RGB tag' );
INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'TagType', 1, 2, 'Alphanumerical tag' );
INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'TagType', 2, 2, 'Numerical tag' );
INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'TagType', 3, 2, 'Date tag' );
INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'TagType', 4, 2, 'Time tag' );
INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'TagType', 5, 2, 'RGB tag' );

INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'TagSetType', 1, 1, 'Texta tag-sett' );
INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'TagSetType', 2, 1, 'Númerískt tag-sett' );
INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'TagSetType', 3, 1, 'Dagsetningar tag-sett' );
INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'TagSetType', 4, 1, 'Tíma tag-sett' );
INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'TagSetType', 5, 1, 'RGB tag-sett' );
INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'TagSetType', 1, 2, 'Alphanumerical tag-set' );
INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'TagSetType', 2, 2, 'Numerical tag-set' );
INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'TagSetType', 3, 2, 'Date tag-set' );
INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'TagSetType', 4, 2, 'Time tag-set' );
INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'TagSetType', 5, 2, 'RGB tag-set' );

INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'TagSetAccessType', 1, 1, 'Kerfis aðgangur' );
INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'TagSetAccessType', 2, 1, 'Notenda aðgangur' );
INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'TagSetAccessType', 1, 2, 'System access' );
INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'TagSetAccessType', 2, 2, 'User access' );

INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'FilterType', 1, 1, 'Tag filter' );
INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'FilterType', 2, 1, 'Víddar filter' );
INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'FilterType', 3, 1, 'Númerabils filter' );
INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'FilterType', 4, 1, 'Tímabils filter' );
INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'FilterType', 5, 1, 'Dagsetningarbils filter' );
INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'FilterType', 1, 2, 'Tag filter' );
INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'FilterType', 2, 2, 'Dimensional filter' );
INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'FilterType', 3, 2, 'Numerical range filter' );
INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'FilterType', 4, 2, 'Time range filter' );
INSERT INTO TRANSLATION( "entity_name", "entity_id", "language_id", "translated_text") VALUES( 'FilterType', 5, 2, 'Date range filter' );

end;