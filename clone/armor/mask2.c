// mask.c
//
#include <ansi.h>
#include <armor.h>

inherit MYMASK;

void create()
{
        set_name(NOR + WHT "人皮面具" NOR, ({ "renpi mask", "renpi", "mask" }) );
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "个");
                set("long", "这似乎是一个由人皮制成的面具。\n"
                            "使用方法：pretend <人物ID>\n"
                            "取消方法：pretend cancel\n");
                
                set("value", 10000);
                set("armor_prop/dex", 5);
                set("armor_prop/int", 5);
                set("no_upd", 1);// 不能用莫邪符升级，以免丢失特殊功能
        }
        setup();
}

int query_autoload()
{
        return 1;
}

void init()
{
        add_action("do_pretend", "pretend");
}

int do_pretend(string arg)
{
        object who;
        object me;
        string *mask;
        string pshort;

        if (! arg)
                return notify_fail("你想假装谁？\n");

        me = this_player();
        if (arg == "none" || arg == "cancel")
        {
                if (! query_temp("owner"))
                        return notify_fail("你现在并没有使用面具。\n");

                me->delete_temp("apply/name");
                me->delete_temp("apply/short");
                me->delete_temp("apply/long");
                me->delete_temp("apply/mask2_flag"); // 是否是mask2.c的标志
                message_vision("$N从脸上取下了一个人皮面具。\n", me);
                return 1;
        }
        
/*
        if (me->query_skill("pretending", 1) < 100)
                return notify_fail("你拿着面具摸来摸去，就是不会使用。\n");

        if (me->query("age") >= 60 &&
            ! me->query("special_skill/youth"))
                return notify_fail("你太老了，难以扮得像。\n");
*/
        if (! objectp(who = present(arg, environment(me))) || 
            ! living(who))
                return notify_fail("你想假装谁？\n");

        if (wizardp(who))
                return notify_fail("你无法假扮巫师。\n");

        if (! who->query("can_speak"))
                return notify_fail("假扮" + who->name() + "？好像太难了点。\n");

        // 因为呼叫short()有时候会表述对方的状态，所以不直接
        // 拷贝who->short()，而是直接看复制对方的应用short()，
        // 如果没有就复制对方的真实short()。
        if (sizeof(mask = who->query_temp("apply/short")))
                pshort = mask[sizeof(mask) - 1];
        else
                pshort = who->short(1);

        write("你开始假装" + who->name() + "。\n");
        me->set_temp("apply/name", ({ who->name() }));
        me->set_temp("apply/short", ({ pshort }));
        me->set_temp("apply/long", ({ who->long() }));
        me->set_temp("apply/mask2_flag", 1);
        set_temp("owner", me);
        return 1;
}

int move(mixed dest)
{
        object me;

        if (me = query_temp("owner"))
        {
                me->delete_temp("apply/name");
                me->delete_temp("apply/short");
                me->delete_temp("apply/long");
                me->delete_temp("apply/mask2_flag");
                delete_temp("owner");
        }

        return ::move(dest);
}

