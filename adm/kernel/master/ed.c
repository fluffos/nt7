// This program is a part of NT MudLIB

// save_ed_setup and restore_ed_setup are called by the ed to maintain
// individual options settings. These functions are located in the master
// object so that the local admins can decide what strategy they want to use.
// 储存一个使用者的编辑程式设定或组态设定
int save_ed_setup(object user, int code)
{
        string file;

        if( !intp(code) ) return 0;

        file = user_path(getuid(user)) + ".edrc";
        efun::rm(file);

        return efun::write_file(file, code + "");
}

// Retrieve the ed setup. No meaning to defend this file read from
// unauthorized access.
// 取得使用者的编辑程式设定 (setup) 或组态设定
int retrieve_ed_setup(object user)
{
        string file;
        int code;

        file = user_path(getuid(user)) + ".edrc";
        if( file_size(file) <= 0 )
                return 0;

        sscanf(read_file(file), "%d", code);
        return code;
}

// called if a user connection is broken while in the editor; allows
// the mudlib to save the changes in an alternate file without modifying
// the original
// 使用者不正常断线时，备份其编辑内容
string get_save_file_name(string file, object user)
{
        return sprintf("%s.%d", file, time());
}

// make_path_absolute: This is called by the driver to resolve path names in ed.
// 让 ed() 转换欲读写档案的相对路径名称为绝对路径名称
string make_path_absolute(string file)
{
        file = resolve_path((string)query("cwd", this_player()), file);
        return file;
}
