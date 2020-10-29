// This program is a part of NT MudLIB

#define DATA_PATH               "/data/serial_number.o"

private mapping serial_number;

string query_serial_number(string key)
{
        if( !stringp(key) )
                return 0;
        
        serial_number[key] = count(serial_number[key], "+", 1);
        
        save_object(DATA_PATH);

        return serial_number[key];
}

void remove_serial_number(string key)
{
        if( !stringp(key) )
                return;
                
        map_delete(serial_number, key);
        
        save_object(DATA_PATH);
}

void create()
{
        if( !restore_object(DATA_PATH) )
        {
                serial_number = allocate_mapping(0);
                save_object(DATA_PATH);
        }
}

string query_name()
{
        return "序号系统(SERIAL_NUMBER_D)";
}
