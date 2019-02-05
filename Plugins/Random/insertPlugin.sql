insert into plugin (qualified_library_name, description) values( 'ObjectCube/plugin/Random/libRandom_Plugin.so', 'This is a plugin that assigns a random integer value to images' );

insert into plugin_tag_set (plugin_id, tag_set_type_id, tag_type_id, name, tag_set_name) values
( (select max(id) from plugin), 2, 2, 'Random.Number.1', 'Random Number 1');

insert into plugin_tag_set (plugin_id, tag_set_type_id, tag_type_id, name, tag_set_name) values
( (select max(id) from plugin), 2, 2, 'Random.Number.2', 'Random Number 2');
