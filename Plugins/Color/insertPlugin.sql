insert into plugin (qualified_library_name, description) values( '/ObjectCube/plugin/Color/libColor_Plugin.so', 'This is a plugin that calculates average rgb values for images.' );

insert into plugin_tag_set (plugin_id, tag_set_type_id, tag_type_id, name, tag_set_name) values
( (select max(id) from plugin), 2, 2, 'Average.Red', 'Average Red');

insert into plugin_tag_set (plugin_id, tag_set_type_id, tag_type_id, name, tag_set_name) values
( (select max(id) from plugin), 2, 2, 'Average.Blue', 'Average Blue');

insert into plugin_tag_set (plugin_id, tag_set_type_id, tag_type_id, name, tag_set_name) values
( (select max(id) from plugin), 2, 2, 'Average.Green', 'Average Green');
