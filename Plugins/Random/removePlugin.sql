delete from plugin_tag_set where name like 'Random.Number%';

delete from plugin where qualified_library_name like '%libRandom_Plugin.so';
