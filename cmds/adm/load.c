// load.c

#include <ansi.h>;

int main(object me, string arg)
{
        object user, where;
        string msg;
        
        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;


        if (! arg) return 0;
        if (wiz_level(me) < wiz_level(arg))
                return notify_fail("你不能装载巫师级别比你高的玩家。\n");

        where = environment(me);

        user = new(USER_OB);
        seteuid(arg);
        export_uid(user);
        user->set_name("", ({ arg }));
#ifdef DB_SAVE
        set_temp("restore_mysql", 1, user);
#endif
        if (! user->restore())
        {
                destruct(user);
                return notify_fail("没有这个玩家。\n");
        }
        user->setup();
        
        if( !stringp(msg=query("env/msg_clone", me)) )
        if( query("outdoors", where) || query("exits", where) )
                msg = HIM"$N掏出一砣泥巴，吐了两口口水,捏啊捏。。。捏了半天捏出一个$n。\n"NOR;

        message_vision(msg + "\n", me, user);
        user->move(where);
        return 1;
}
