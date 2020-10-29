// update.c
// updated by doing

#include <runtime_config.h>
#include <getconfig.h>
#include <ansi.h>

inherit F_CLEAN_UP;

protected int update_player(object me);

void create()
{
        seteuid(getuid());
}


int main(object me, string file)
{
        int i;
        object obj, *inv;
        string err;
        string bin_file;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        seteuid(geteuid(me));

        if (! file) file = query("cwf", me);
        if (! file)
                return notify_fail("你要重新编译什麽档案？\n");

        if ((obj = present(file, environment(me))) && playerp(obj) ||
            (obj = find_player(file)) && playerp(obj))
                return update_player(obj);

        if (file == "me")
                return update_player(me);
        else
        {
                file = resolve_path(query("cwd", me), file);
                if (! sscanf(file, "%*s.c")) file += ".c";
        }

        if (file_size(file) == -1)
                return notify_fail("没有这个档案。\n");

        set("cwf", file, me);

        if (obj = find_object(file))
        {
                if (obj == environment(me))
                {
                        if (file_name(obj) == VOID_OB)
                                return notify_fail("你不能在 VOID_OB 里重新编译 VOID_OB。\n");
                        inv = all_inventory(obj);
                        i = sizeof(inv);
                        while (i--)
                                if (playerp(inv[i]) || inv[i]->is_chatter() ||
                                    query_temp("owner", inv[i]) )
                                        // 玩家、聊天魂魄、有主的物品或人物
                                        inv[i]->move(VOID_OB, 1);
                                else    inv[i] = 0;
                }

                if (obj == find_object(VERSION_D) &&
                    VERSION_D->is_release_server())
                {
                        // 如果是版本发布的服务器，则删除
                        // VERSION_D 的 bin 代码，因为在没有
                        // VERSION_D 的时候 driver 是不予编译的。
                        bin_file = "/binaries" + base_name(obj) + ".b";
                        write("Remove: " + bin_file + "\n");
                        rm(bin_file);
                }
                seteuid(getuid());
                destruct(obj);
        }

        if (obj) return notify_fail("无法清除旧程式码。\n");

        write("重新编译 " + file + "：");
        err = catch(call_other(file, "???"));
        if (err)
                write(sprintf( "发生错误：\n%s\n", err));
        else
        {
                write("成功！\n");
                if ((i = sizeof(inv)) && (obj = find_object(file)))
                        while (i--)
                                if (inv[i]) inv[i]->move(obj, 1);
        }

        return 1;
}

protected int update_player(object me)
{
        object env, link_ob, obj;
        object *ob, *dob;
        mapping equip;
        int i;

        if (me->is_chatter())
                return notify_fail("你不能更新聊天ID。\n");

        if (wiz_level(me) > wiz_level(this_player()))
                return notify_fail("你没有权限更新这个人物。\n");

        seteuid(getuid());
        env = environment(me);

        // First, create the new body.
        link_ob=query_temp("link_ob", me);
        if (! link_ob)
        {
                link_ob = new(LOGIN_OB);
                set("id",query("id",  me), link_ob);
                if (! link_ob->restore())
                {
                        write("找不到该玩家的存盘数据。\n");
                        return 1;
                }
                if (interactive(me))
                        set_temp("ip_number", query_ip_number(me), link_ob);
        }

        if( query("id", link_ob) != getuid(me) )
        {
                write (sprintf("连接对象的ID(%s)和用户的ID(%s)不相同，不能"
                       "更新该玩家。\n",query("id", link_ob),getuid(me)));
                return 1;
        }

        obj = LOGIN_D->make_body(link_ob);
        if (! obj) return 0;

        // Save the data and exec the player to his/her link object.
        ob = all_inventory(me);
        equip = ([ ]);
        for (i = 0; i < sizeof(ob); i++)
                equip += ([ ob[i] : query("equipped", ob[i]) ]);
        ob->move(VOID_OB);

        // 保存用户的进度
        me->save();

        // 如果在线，移动互动对象
        if (interactive(me))
                exec(link_ob, me);
        destruct(me);

        // Restore new body and exec to it via enter_world in LOGIN_D
        obj->restore();
        LOGIN_D->enter_world(link_ob, obj, 1, 1);
        dob = all_inventory(obj);
        for (i = 0; i < sizeof(dob); i++)
                destruct(dob[i]);

        write("身体更新完毕。\n\n");
        obj->move(env);
        ob->move(obj);

        if (! interactive(obj))
                destruct(link_ob);

        for (i = 0; i < sizeof(ob); i++)
        {
                if (equip[ob[i]] == "worn")
                        ob[i]->wear();
                if (equip[ob[i]] == "wielded")
                        ob[i]->wield();
        }
        obj->write_prompt();

        return 1;
}

int help(object me)
{
  write(@HELP
指令格式 : update <档名|here|me|玩家名>

这个指令可以更新档案, 并将新档的内容载入记忆体内. 若目标为
'here' 则更新所在环境. 若目标为 'me' 则更新自己的人物. 若目
标为玩家则可更新玩家物件.

HELP
    );
    return 1;
}