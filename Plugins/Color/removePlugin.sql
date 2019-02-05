delete from plugin_tag_set where name like 'Average.Red';
delete from plugin_tag_set where name like 'Average.Blue';
delete from plugin_tag_set where name like 'Average.Green';

delete from plugin where qualified_library_name like '%libColor_Plugin.so';
