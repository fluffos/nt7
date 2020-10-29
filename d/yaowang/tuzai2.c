#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "屠宰场");
        set("long", @LONG
这里是药王谷的屠宰场，是专门用来屠宰药王谷饲养的动物，
取药材用的，你可以把动物捉到这里，进行屠宰(sha)。
LONG );
        set("no_fight", 1);
        set("exits", ([
                "east" : __DIR__"tuzai1",
        ]));
        setup();
}

void init()
{
        add_action("do_sha", "sha");
}

int do_sha(string arg)
{
        object me, ob;
        int exp,pot;
        exp=8+random(12);
        pot=2+random(2);
        me=this_player();

        if( query("family/family_name", me) != "药王谷" || me->query_skill("medical",1)<60 )
        {
                return notify_fail("你还不会取药呢！不会杀动物？\n");
        }

        if( !arg || !objectp(ob = present(arg, environment(me))) )
                return notify_fail("指令格式：sha <ID> \n");

        if( !query("yaowang_zhuo", ob) )
                return notify_fail("这个东西不能在这里杀！\n");

        if( me->is_fighting() || me->is_busy() )
                return notify_fail("你正忙着呢！\n");

        if(random(3))
        {
              message_vision(HIR"$N把$n按在屠宰槽上，一刀砍了下去。\n"NOR, me, ob);
              message_vision(HIR"结果刀从$n身上滑了下来，$N差点伤了自己。\n"NOR, me, ob);
                 me->start_busy(1+random(2));
              return 1;
            }
        me->improve_skill("medical", ((int)me->query_skill("healing",1)/10));
        message_vision(HIR"$N把$n按在屠宰槽上，一刀砍了下去。\n"NOR, me, ob);
        ob->die();
        addn("combat_exp", exp, me);
        me->improve_potential(pot);
      tell_object(me,HIC "在屠宰过程中你对「基本医术」有了新的认识！\n" NOR);
              tell_object(me, HIC "你获得了" + chinese_number(exp) + 
                      "点经验和" + chinese_number(pot) + "点潜能。\n"NOR ); 
         me->start_busy(2);
        return 1;
}
