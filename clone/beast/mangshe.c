inherit SNAKE;
#include <ansi.h>

void create()
{
        set_name(HIG "蟒蛇" NOR, ({ "mang she", "mang", "she" }));
        set("long", HIG "这是一只昂首直立，吐着长舌芯的大蟒蛇。\n" NOR);

        set("age", 6);
        set("str", 50);
        set("dex", 20);
        set("con", 50);
        set("max_qi", 5000);
        set("max_jing", 5000);
        set("neili", 3000);
        set("max_neili", 3000);
        set("combat_exp", 300000);

        set("snake_poison", ([
                "level"  : 120,
                "perhit" : 10,
                "remain" : 50,
                "maximum": 50,
                "supply" : 1,
        ]));

        set("power", 45);
        set("item1", "/clone/quarry/item/sherou");
        set("item2", "/clone/quarry/item/shepi");

        set_temp("apply/force", 200);
        set_temp("apply/parry", 200);
        set_temp("apply/dodge", 200);
        set_temp("apply/attack", 180);
        set_temp("apply/defense", 180);
        set_temp("apply/unarmed_damage", 220);
        set_temp("apply/armor", 220);

        setup();
}

int convert(string arg)
{
        object me = this_player();
        object ob;

        if (arg!="snake" && arg!="she" && arg!="mang she") return 0;
        if( query("family/family_name", me) != "欧阳世家" )
                return notify_fail("你不能化蛇为杖。\n");

        return notify_fail("蟒蛇身子太过粗大，无法化为蛇杖。\n");
}