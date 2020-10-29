// autoload.c
// From ES2
// Modified by Xiang for XKX (12/15/95)
// Modified by Lonely@NITAN (16/05/2009) 解决多个同一物品存储时候叠放问题

string *autoload;
void clean_up_autoload() { autoload = 0; }

void save_autoload()
{
        object ob;
        int i, j, n, f;
        mixed param;
        mixed *inv; 

        inv = all_inventory();

#ifndef NO_QUIT_DROP
        inv = filter_array(inv, (: $1->query_autoload() :));
#endif
        autoload = allocate(sizeof(inv));
        inv = unique_array(inv, (:  base_name($1) :));

        for( i=0, j=0; i<sizeof(inv); i++ ) {
                f = 0;
                for( n=0; n<sizeof(inv[i]); n++ ) {
                        ob = inv[i][n];
                        param = ob->query_autoload();

                        if( stringp(param) ) {
                                autoload[j] = base_name(ob);
                                autoload[j] += "##" + param;
                                f++;
                                j++;
                        }
                }

                f = sizeof(inv[i]) - f;
                if( f > 0 ) {
                        autoload[j] = base_name(ob);
                        autoload[j] += "**" + f;
                        j++;
                }
        }
        autoload = autoload[0..j-1];
        autoload -= ({ 0 });
}

void restore_autoload()
{
        int i;
        object ob;
        string file, err;
        mixed param;
        int has_dropped;

        if( !pointerp(autoload) ) return;

        has_dropped = 0;
        for( i = 0; i < sizeof(autoload); i++ ) {
                if( !autoload[i] || autoload[i] == "" )
                        continue;
                if( sscanf(autoload[i], "%s##%s", file, param) != 2 &&
                    sscanf(autoload[i], "%s**%d", file, param) != 2 ) {
                        file = autoload[i];
                        param = 0;
                }
                if( file_size(file + ".c") > 0 ) {
                        err = catch(call_other(file, "???"));
                        ob = find_object(file);
                } else {
                        err = 0;
                        ob = 0;
                }

                if( ob && !ob->is_no_clone()) ob = new(file);
                if( err || !ob || ob->is_no_clone() && environment(ob)) {
                        string temp;
                        if( file && sscanf(file, "/data/%*s/%s", temp) ) {
                                if (has_dropped) continue;
                                has_dropped++;
                                write("你发现有些东西已经没有用了，随手就扔掉了。\n");
                        } else
                                write("你觉得似乎失落了什么重要的东西，最好通知一下巫师。\n");
                        log_file("autoload", sprintf("Fail to autoload %s of %s, error %s(%s)\n",
                                 file, query("name", this_object()),
                                 query("id", this_object()),
                                 ob ? "The no clone object has existed" : err));
                        continue;
                }
                if( ob->is_no_clone() && ob->is_not_belong_me(this_object()) ) {
                        if( !environment(ob) ) destruct(ob);
                        continue;
                }

                export_uid(ob);
                if( !ob->is_character() )
                        ob->move(this_object(), 1);

                if( stringp(param) ) ob->autoload(param, this_object());
                else if( intp(param) && param > 1 ) {
                        param--;
                        if( param > 0 ) {
                                if( function_exists("query_amount", ob) )
                                        ob->set_amount(param+1);
                                else {
                                        for( int n=0; n<param; n++ ) {
                                                ob = new(file);
                                                export_uid(ob);
                                                if( !ob->is_character() )
                                                        ob->move(this_object(), 1);
                                        }
                                }
                        }
                }
        }
        clean_up_autoload();            // To save memory.
}

string *query_autoload_info()
{
        return autoload;
}

void set_autoload_info(string *data)
{
        autoload = data;
}
