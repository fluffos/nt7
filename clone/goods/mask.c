// mask.c
//

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(WHT "面具" NOR, ({ "mian ju", "mask" }) );
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "个");
                set("super_mask", 1);
                set("long", "这似乎是一个由人皮制成的面具。\n");
                set("value", 10000);
        }
        set("auto_load", 1);
        setup();
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

                delete_temp("apply/name", me);
                delete_temp("apply/id", me);
                delete_temp("apply/short", me);
                delete_temp("apply/long", me);
                message_vision("$N从脸上取下了一个人皮面具。\n", me);
                return 1;
        }

        if (me->query_skill("pretending", 1) < 100)
                return notify_fail("你拿着面具摸来摸去，就是不会使用。\n");

        if( query("age", me) >= 60 && 
            !query("special_skill/youth", me) )
                return notify_fail("你太老了，难以扮得像。\n");

        if (me->query_condition("killer"))
                return notify_fail("通缉犯无法戴面具。\n");

        if( sscanf(base_name(environment(me)), "/maze/battle%*s") )
                return notify_fail("战场里无法戴面具。\n");

        if (! objectp(who = present(arg, environment(me))) || 
            ! living(who))
                return notify_fail("你想假装谁？\n");

        if (wizardp(who))
                return notify_fail("你无法假扮巫师。\n");

        if( !query("can_speak", who) )
                return notify_fail("假扮" + who->name() + "？好像太难了点。\n");

        // 因为呼叫short()有时候会表述对方的状态，所以不直接
        // 拷贝who->short()，而是直接看复制对方的应用short()，
        // 如果没有就复制对方的真实short()。
        if( sizeof(mask=query_temp("apply/short", who)) )
                pshort = mask[sizeof(mask) - 1];
        else
                pshort = who->short(1);

        write("你开始假装" + who->name() + "。\n");
        set_temp("apply/name", ({who->name()}), me);
        set_temp("apply/id", who->parse_command_id_list(), me);
        set_temp("apply/short", ({pshort}), me);
        set_temp("apply/long", ({who->long()}), me);
        set_temp("owner", me);
        return 1;
}

int move(mixed dest)
{
        object me;

        if (me = query_temp("owner"))
        {
                delete_temp("apply/name", me);
                delete_temp("apply/id", me);
                delete_temp("apply/short", me);
                delete_temp("apply/long", me);
                delete_temp("owner");
        }

        return ::move(dest);
}
void remove(string euid) 
{
        object me;

        if (me = query_temp("owner"))
        {
                delete_temp("apply/name", me);
                delete_temp("apply/id", me);
                delete_temp("apply/short", me);
                delete_temp("apply/long", me);
                delete_temp("owner");
        }
        ::remove(euid);
}
