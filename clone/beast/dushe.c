#include <ansi.h>
inherit SNAKE;

void create()
{
        set_name(HIG "毒蛇" NOR, ({ "du she", "du", "she" }));
        set("long", HIG "一支昂首吐信的毒蛇正虎视眈眈地盯著你。\n" NOR);

        set("age", 1);
        set("str", 15);
        set("dex", 25);
        set("max_qi", 500);
        set("max_ging", 500);
        set("combat_exp", 5000);

        set("snake_poison", ([
                "level"   : 80,
                "remain"  : 20,
                "maximum" : 20,
                "perhit"  : 10,
                "supply"  : 1,
        ]));

        set("power", 12);
        set("item1", "/clone/quarry/item/sherou");
        set("item2", "/clone/herb/shedan");

        set_temp("apply/dodge", 50);
        set_temp("apply/defense", 100);
        set_temp("apply/unarmed_damage", 50);

        setup();
}

int convert(string arg)
{
        object me = this_player();
        object ob;

        if (arg!="snake" && arg!="du she") return 0;
        if( query("family/family_name", me) != "欧阳世家" )
                return notify_fail("你不能化蛇为杖。\n");
        if (random(me->query_skill("training",1)) <20) {
                kill_ob(me);
                return 1;
        }
        message_vision("$N左手按住毒蛇的头，右手轻抚其七寸，口中念念有词，片刻间将蛇化为一根蛇杖。\n",
                me,);
                ob = new("/d/baituo/obj/shezhang");
        ob->move(environment(this_object()));
        destruct(this_object());
        return 1;
}