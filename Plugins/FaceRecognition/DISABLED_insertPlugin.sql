insert into plugin (qualified_library_name, description) values( 'ObjectCube/plugin/FaceRecognition/libFaceRecognition_Plugin.so', 'This is a plugin that recognizes faces in photograpsh.' );

insert into plugin_tag_set (plugin_id, tag_set_type_id, tag_type_id, name, tag_set_name) values
( (select max(id) from plugin), 1, 1, 'FaceRec.Person', 'Person');

