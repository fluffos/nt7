//checkobj  查询物品分布
// Smallfish@Huaxia

inherit F_CLEAN_UP;

string check_room(string file);
string check_obj(string file);
string base_environment(object ob);

int main(object me,string arg)
{
        string file,info;
        object ob;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        seteuid(geteuid(me));
        if (!arg)
                return notify_fail("指令格式：checkobj <物品文件>|<房间文件>\n");

        file=resolve_path(query("cwd", me),arg);
        if (file_size(file) < 0)
        {
                ob = present(arg, me);
                if (! ob) ob = present(arg, environment(me));
                if (! ob) return notify_fail("没有这个档案。\n");
                file = base_name(ob) + ".c";
        }

        if (!objectp(ob = load_object(file)))
                return notify_fail("无法根据" + file + "生成物品。\n");

        if (ob->is_character())
        {
                if (!userp(ob))
                        destruct(ob);
                return notify_fail("这是一个人物物品。\n");
        }

        if ((int)ob->query_max_encumbrance() == 100000000000)   //是房间
                info = check_room(file);
        else
                info = check_obj(file);

        if (clonep(ob))
                destruct(ob);

        me->start_more(info);

        return 1;
}

string check_room(string file)
{
        object room;
        mapping ob_list, ob;
        string *list;
        int i,have_living;
        string msg,base_env,info;

        room = load_object(file);

        if (!room)
                return "检查" + file + "出错。\n";

        msg = "这是一个房间：" + file + "，名称：" + room->short() + "\n";
        msg += "------------------------------------------------------------------------\n";
        ob_list=query("objects", room);
        if( !mapp(ob_list) ) 
        {
                msg += "这个房间没有任何物品。\n";
                return msg;
        }

        have_living = 0;
        if( mapp(ob=query_temp("objects", room)) )
        {
                list = keys(ob);
                for (i = 0;i <sizeof(list);i++)
                {
                        if (!ob[list[i]])
                                continue;
                        if (ob[list[i]]->is_character())
                                continue;
                        if (!environment(ob[list[i]]))
                                continue;
                        base_env = base_environment(ob[list[i]]);
                        msg += "活的物品：" + ob[list[i]]->short() + "，在" + base_env + "。\n";
                        have_living = 1;
                }
        }

        if (!have_living)
                msg += "这个房间目前没有活的物品。\n";

        list = keys(ob_list);

        for (i = 0;i < sizeof(list);i++)
        {
                msg += "------------------------------------------------------------------------\n";
                info = check_obj(list[i]);
                if (!info) continue;
                msg += info;
        }

        if (clonep(room))
                destruct(room);

        return msg;
}

string check_obj(string file)
{
        object ob,*ob_list;
        string msg,base_env,*list;
        int i,count;
        mapping obj_env;

        ob = load_object(file);
        if (!ob)
                return "检查" + file + "出错。\n";

        if (ob->is_character())
        {
                if (clonep(ob))
                        destruct(ob);
                return 0;
        }

        msg = "物品：" + file + "，名称：" + ob->short() + "\n";

        if (clonep(ob))
                destruct(ob);

        ob_list = children(file);

        if (!sizeof(ob_list))
        {
                msg += "这个文件没有任何复制物品。\n";
                return msg;
        }

        obj_env = ([]);
        for (i = 0;i < sizeof(ob_list);i ++)
        {
                if (!ob_list[i])
                        continue;
                if (!environment(ob_list[i]))
                        continue;
                base_env = base_environment(ob_list[i]);
                if (undefinedp(obj_env[base_env]))
                        obj_env[base_env] = 1;
                else
                        obj_env[base_env] += 1;
        }

        count = 0;
        list = keys(obj_env);
        for (i = 0;i < sizeof(list);i++)
        {
                msg += sprintf("%-20s:%d\n",list[i],obj_env[list[i]]);
                count += obj_env[list[i]];
        }

        msg += "总共" + chinese_number(count) + "个物品。\n";

        obj_env = 0;
        return msg;
}

string base_environment(object ob)
{
        int i = 0;
        object env;
        env = environment(ob);
        while(objectp(env) && clonep(env) && !env->is_character())
        {
                i ++;
                if (i > 20) break;
                if (environment(env))
                        env = environment(env);
                else
                        break;
        }
        if (!env)
                return "不知名的地方";
        if (!clonep(env) || env->is_chat_room())
                return env->short() + "(" + base_name(env) + ")";
        else
                return env->name(1)+"("+query("id", env)+")";
}

int help(object me)
{
write(@HELP
指令格式 : checkobj <物品>|<房间>

查询指定的物品分布情况。
如果查询房间，则显示房间所有固有物品的分布情况。
HELP
    );
    return 1;
}