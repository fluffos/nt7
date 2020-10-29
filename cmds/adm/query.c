// query.c

inherit F_CLEAN_UP;

class store {
        string name;
        string id;
        string *ids;
        string file;
        mapping data;
        mapping temp_data;
        int amount;
}

int main(object me, string arg)
{
        class store item;
        string target;
        mixed result;
        mixed obj;
        string *flist;
        string *ffile;
        string arg1, arg2;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        if (! me->is_admin())
                return 0;

        seteuid(getuid(me));

        if (! arg)
                return notify_fail("指令格式 : query all | <物件之名称或档名>\n" );
        target = arg;

        if (target == "all" || target == "ALL")
        {
                write(sprintf("目前数据库中保存的数据有：%d 项。\n",
                              sizeof(DBASE_D->query_save_dbase())));
                return 1;
        }

        if (sscanf(arg, "%s %s", arg1, arg2) == 2)
        {
                if (arg1 == "cruise")
                {
                        ffile = ({ });
                        flist = get_dir("/data/item/cruise/"); 
                        for (int i = 0; i < sizeof(flist); i++) 
                        {
                                string file;
                                file = "/data/item/cruise/" + flist[i]; 
                                obj = get_object(file);
                                result = DBASE_D->query_object_data(obj);
                                if( !mapp(result) || undefinedp(result["all"]) ) continue;
                                result = result["all"];
                                for (int j = 0; j < sizeof(result); j++) 
                                {
                                        item = new(class store);
                                        item = result[j];
                                        if( item->file == arg2 )
                                                ffile += ({ "/data/item/cruise/" + flist[i] });
                                }
                        }
                        write(sprintf("漫游包的数据中含有字符(%s)的物件如下：\n%O\n", arg2, ffile));
                        return 1;
                }
        }
        obj = find_object(target);

        if (! objectp(obj)) obj = present(target, me);
        if (! objectp(obj)) obj = present(target, environment(me));
        if (! objectp(obj)) obj = resolve_path(query("cwd", me), target);

        result = DBASE_D->query_object_data(obj);
        if (undefinedp(result))
                write("该物件在数据库中没有任何记录。\n");
        else
                write(sprintf("该物件(%O)保存的数据：\n%O\n", obj, result));

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : query all | <物件之名称或档名>

利用此一指令可以查询一个物件(object)保存在数据库中的记录。

参考资料：clear
HELP
    );
    return 1;
}
