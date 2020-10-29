// This program is a part of NT MudLIB

// valid_compile: controls whether or not an file can be compiled
int valid_compile(string file)
{
#ifndef BINARY_SUPPORT
        return 1;
#else
        if( !find_object(VERSION_D) )
                return 1;

        /*
        if( VERSION_D->is_release_server() )
                return 1;
        */

        // 巫师目录下（分站）开放给编译
        if( sscanf(file, "/u/%*s") ||
            sscanf(file, "/u/%*s/%s", file) )
                return 1;

        return file_valid(file) == 1;
#endif
}
