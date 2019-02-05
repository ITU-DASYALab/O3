-- Insert Plugin
insert into plugin (qualified_library_name, description) values( 'ObjectCube/plugin/FileType/libFileType_Plugin.so', 'This is a plugin that extracts Text information from Text file' );

-- Insert tag sets
insert into plugin_tag_set (plugin_id, tag_set_type_id, tag_type_id, name, tag_set_name) values
( (select max(id) from plugin), 1, 1, 'FileType', 'Type of file');