delete from plugin_tag_set where name like 'Import.Number';

delete from plugin where qualified_library_name like '%libImportNumbering_Plugin.so';
