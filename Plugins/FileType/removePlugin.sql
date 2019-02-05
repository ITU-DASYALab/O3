delete from plugin_tag_set where name like 'FileType%';

delete from plugin where qualified_library_name like '%libFileType_Plugin.so';
