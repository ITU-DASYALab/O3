delete from plugin_tag_set where name like 'Exif%';

delete from plugin where qualified_library_name like '%libEXIF_Plugin.so';
