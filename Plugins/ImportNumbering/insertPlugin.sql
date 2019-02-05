insert into plugin (qualified_library_name, description) values( 'ObjectCube/plugin/ImportNumbering/libImportNumbering_Plugin.so', 'This is a plugin that groups images together based on import.' );

insert into plugin_tag_set (plugin_id, tag_set_type_id, tag_type_id, name, tag_set_name) values
( (select max(id) from plugin), 2, 2, 'Import.Number', 'Import Number');
