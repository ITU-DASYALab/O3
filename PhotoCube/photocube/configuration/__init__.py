"""
This modules contains classes for handling configuration
files. These classes allows developers to read entries
within code.
"""
#imports
import re
from photocube.constants import DEFAULT_CONFIG_NAME


class ConfigurationException(Exception):
    """
    Exception class, used when something goes wrong in the configuration.
    """
    def __init__(self, value):
        self.value = value
    
    def __str__(self):
        return repr(self.value)


class Configuration:
    """
    Contains configuration files on the form:
    #comments
    key=value
    """
    print "Configuration"
    def __init__(self, config_file_name=None):
        
        if config_file_name is None:
            config_file_name = DEFAULT_CONFIG_NAME
        
        
        # Create instance of key/value dict.
        self.config_key_value = dict()
        
        # Read configuraion file.      
        try: 
            config_file_name = open(config_file_name)
        except: 
            raise ConfigurationException('Unable to open configuration file: ' + str(config_file_name))
        
        for line in config_file_name:
            # We ignore comment lines.
            if line.startswith('#'):
                continue
            
            if re.match('^\S+(\s+)?=(\s+)?\S+', line):
                line = line.strip()
                key = line.split('=')[0].lower().strip()
                val = line.split('=')[1].strip()
                self.config_key_value[key] = val


    def getConfigKeys(self):
        """
        Returns list of all the configuration keys available.
        """
        return self.config_key_value.keys()
            
            
    def add(self, key, value):
        """
        Adds new key/value pair to the configuration.
        """
        self.config_key_value[key.strip()] = str(value).strip()
    
    
    def getValue(self, key):
        """
        Gets value by a key. If the key is not in the keys, then an exception is thrown.
        """
        key = key.lower().strip()
        if key in self.getConfigKeys():
            return self.config_key_value[key]
        else:
            raise ConfigurationException('No entry for key: ' + key)

    def __getitem__(self, key):
        if key in self.config_key_value:
            return self.config_key_value[key]
        else:
            raise ConfigurationException('Key ' + key + ' not found in configuration set.')

    def __setitem__(self, key, value):
        self.config_key_value[key] = value
        


# Create singleton instance.
browser_config = Configuration()
