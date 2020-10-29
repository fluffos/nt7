#include <ansi.h>
inherit SNAKE;

void create()
{
        set_name(HIR "腹蛇" NOR, ({ "fu she", "fu", "she" }));
        set("long", HIR "只见它全身血红，头呈三角，长蛇吞吐，嗤嗤做响。\n" NOR);

        set("age", 3);
        set("str", 35);
        set("dex", 50);
        set("max_qi", 1500);
        set("max_ging", 1500);
        set("combat_exp", 150000);

        set("snake_poison", ([
                "level"  : 120,
                "perhit" : 10,
                "remain" : 50,
                "maximum": 50,
                "supply" : 1,
        ]));

        set("power", 22);
        set("item1", "/clone/quarry/item/sherou");
        set("item2", "/clone/herb/shedan");

        set_temp("apply/parry", 100);
        set_temp("apply/dodge", 100);
        set_temp("apply/attack", 80);
        set_temp("apply/defense", 100);
        set_temp("apply/unarmed_damage", 80);
        set_temp("apply/armor", 100);

        setup();
}

int convert(string arg)
{
        object me = this_player();
        object ob;

        if (arg!="snake" && arg!="she" && arg!="fu she" && arg!="fu") return 0;
        if( query("family/family_name", me) != "欧阳世家" )
                return notify_fail("你不能化蛇为杖。\n");
        if (random(me->query_skill("training",1)) <20) {
                kill_ob(me);
                return 1;
        }
        message_vision("$N左手按住蝮蛇的头，右手轻抚其七寸，口中念念有词，片刻间将蛇化为一根蛇杖。\n",
                me,);
                ob = new("/d/baituo/obj/shezhang");
        ob->move(environment(this_object()));
        destruct(this_object());
        return 1;
}