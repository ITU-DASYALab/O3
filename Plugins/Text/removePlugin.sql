delete from plugin_tag_set where name like 'Text%';

delete from plugin where qualified_library_name like '%libText_Plugin.so';
