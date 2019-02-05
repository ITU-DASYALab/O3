delete from plugin_tag_set where name like 'FaceRec%';

delete from plugin where qualified_library_name like '%libFaceRecognition_Plugin.so';
