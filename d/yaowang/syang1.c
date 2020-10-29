#include <ansi.h>
inherit ROOM;
string* npcs = ({
        __DIR__"npc/xiong",
        __DIR__"npc/he",
        __DIR__"npc/lu",
        __DIR__"npc/xie",
        __DIR__"npc/she",
});
void create()
{
        set("short", "饲养场");
        set("long",@LONG
这里是药王谷的饲养场，用于饲养一些可以取药材的动物，你可以把动物
捉(zhuo)到屠宰场去杀了取药。
LONG );
        set("exits", ([
                  "south" : __DIR__"syang",
        ]));
        set("objects", ([
        npcs[random(sizeof(npcs))] :random(2),
        npcs[random(sizeof(npcs))] :random(2),
        npcs[random(sizeof(npcs))] :random(2),
        npcs[random(sizeof(npcs))] :random(2),
        npcs[random(sizeof(npcs))] :random(2),
        ]) );
        setup();
}

void init()
{
        add_action("do_zhiliao", "zhuo");
}

int do_zhiliao(string arg)
{
        object me, ob;
          int lvl,exp,pot;
          exp=8+random(12);
          pot=2+random(6);
        me=this_player();
        lvl=me->query_skill("hunting");
        if( query("family/family_name", me) != "药王谷"
         || lvl < 60 ) 
        {               return notify_fail("你还不会狩猎技巧呢！捉动物干什么？\n");
        }

        if( !arg || !objectp(ob = present(arg, environment(me))) )
                return notify_fail("指令格式：zhuo <ID> \n");

       if( query("owner", ob) == query("id", me) )
                   return notify_fail("你已经捉到"+ob->name()+"了！\n");

        if( query("owner", ob) && query("owner", ob) != query("id", me) )
                      return notify_fail(ob->name()+"已经是人家的了！\n");
        if( !query("yaowang_zhuo", ob) )
                return notify_fail("这个东西不能捉！\n");

        if( me->is_fighting() || me->is_busy() )
                return notify_fail("你正忙着呢！\n");
          if (random(lvl)>lvl*2/3)
        {       
        ob->set_leader(me);
        me->start_busy(2);
        message_vision("$N对$n召唤了两声，$n就乖乖得跟着$N。\n", me, ob);
                me->improve_skill("hunting",(query("int", me)/6));
                write(HIC "你在召唤过程中对于狩猎技巧有了些体会。\n" NOR);
                   set("owner",query("id",  me), ob);
                     addn("combat_exp", exp, me);
                     me->improve_potential(pot);
                     tell_object(me, HIC "你获得了" + chinese_number(exp) + 
                             "点经验和" + chinese_number(pot) + "点潜能。\n"NOR );
        }else 
        {       
        message_vision("$N对$n召唤了两声，$n根本就不理$N。\n", me, ob);
          me->start_busy(random(2));
        }

        return 1;
}
