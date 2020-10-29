// clone.c

inherit F_CLEAN_UP;

int main(object me, string file)
{
        object obj;
        string err, msg;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        seteuid(getuid());

        if( !file)file=query("cwf", me);
        if (! file)
                return notify_fail("你要复制什麽物件？\n");

        file=resolve_path(query("cwd", me),file);
        if (sscanf(file, "%*s.c") != 1) file += ".c";
        set("cwf", file, me);

        if (file_size(file) < 0)
                return notify_fail("没有这个档案(" + file + ")。\n");

        if (! SECURITY_D->valid_read(file, me, "clone"))
        {
                write("你没有权限操作这个对象。\n");
                return 1;
        }

        if (! find_object(file))
        {
                err = catch(call_other(file, "???"));
                if (err)
                {
                        write("载入失败：" + err + "\n");
                        return 1;
                }
        }

        if (! me->is_admin())
        {
                switch (SECURITY_D->query_site_privilege("clone"))
                {
                case "gift":
                        if (! sscanf(file, "/clone/special/%*s") &&
                            ! sscanf(file, "/clone/gift/%*s"))
                                return notify_fail("你不能复制这个物品。\n");
                        break;

                case "all":
                        break;

                default:
                        return notify_fail("你不能复制物品。\n");
                }

                if (! me->is_admin())
                        message_system(sprintf("%s(%s)复制了物品：%s(%s)。\n",
                                               me->name(1),query("id", me),
                                               filter_color(file->name(1)),query("id", get_object(file))));
        }

        seteuid(geteuid(me));

        err = catch(obj = new(file));
        if (err)
        {
                write("复制失败：" + err + "\n");
                return 1;
        }

        if (! objectp(obj))
        {
                write("你无法复制该物品。\n");
                return 1;
        }

        msg = "只见$N伸手凌空一指，变出了$n。\n";

        log_file("static/clone", sprintf("%s %-9s clone %s\n",
                                         log_time(), geteuid(me),
                                         base_name(obj)));
        if( !obj->is_character() && !query("no_get", obj) && obj->move(me) )
        {
                write(query("name", obj)+"复制成功，放在你的物品栏。\n");
                message_vision(msg + "\n", me, obj);
                return 1;
        }
        if (obj->move(environment(me)))
        {
                write(query("name", obj)+"复制成功，放在这个房间。\n");
                message_vision(msg + "\n", me, obj);
                return 1;
        }

        destruct(obj);
        return notify_fail("无法复制不能移动的物件(" + file + ")。\n");
}

int help(object me)
{
        write(@HELP
指令格式 : clone <档名>

利用此指令可复制任何能移动之物件(含人物)。

该命令在可以被授权使用的信息包括：gift、all。
HELP );
        return 1;
}
