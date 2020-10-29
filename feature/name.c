// name.c
// Written by Lonely@chinamud.cn

// #pragma save_binary

#include <ansi.h>
#include <condition.h>

inherit F_NATURE;
nosave string *my_id;
string *my_id() { return my_id; }

void set_name(string name, string *id)
{
        string fullname;

        if( !stringp(name) ) {
                if( !stringp(fullname = query("surname")) )
                        fullname = "";

                if( stringp(query("purename")) )
                        fullname += query("purename");

                if( fullname == "" )
                        fullname = "无名氏";

                set("name", fullname);
        } else {
                set("name", name);
        }

        if( pointerp(id) ) {
                set("id", id[0]);
                my_id = id;
        }
}

void set_color(string color)
{
        string colorname;

        //colorname = color + query("name");
        colorname = color + filter_color(query("name"), 1);
        colorname = trans_color(colorname, 3);

        set("color", color);
        set("colorname", colorname + NOR);
}

int id(string str)
{
        string *applied_id;

        if( pointerp(my_id) && member_array(str, my_id)!=-1 ) {
                if( pointerp(applied_id = query_temp("apply/id"))
                &&  sizeof(applied_id) ) {
                        if (this_player() && !wizardp(this_player()) )
                                return 0;
                }
                return 1;
        }
        return 0;
}

string *parse_command_id_list()
{
/*
        string *applied_id;

        if( pointerp(applied_id = query_temp("apply/id"))
        &&  sizeof(applied_id) )
                return applied_id;
        else
*/
                return my_id;
}

varargs string name(int raw)
{
        string str, *mask;

        if( !raw && sizeof(mask = query_temp("apply/name")) )
                return mask[sizeof(mask)-1];
        else {
                if( stringp(str = query("name")) )
                        return str;
                else
                        return file_name(this_object());
        }
}

varargs string short(int raw)
{
        string str;
        string colorname;

        if( !stringp(colorname = query("colorname")) )
                colorname = name(raw);

        if( raw || !stringp(str = query("short")) )
                str = colorname + "(" + capitalize(query("id")) + ")";

        return str;
}

varargs string long(int raw)
{
        string str, extra, *mask;

        if( !raw && sizeof(mask = query_temp("apply/long")) )
                str = mask[sizeof(mask)-1];

        else if( !stringp(str = query("long")) )
                str = short(raw) + "。\n";

        if( stringp(extra = this_object()->extra_long()) )
                str += extra;

        return str;
}

varargs string query_idname(int raw)
{
        return query("name",this_object()) + "(" + (raw ? capitalize(query("id",this_object())) : query("id",this_object())) + ")";
}
