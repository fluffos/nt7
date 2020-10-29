// Code of ShenZhou
// new_snake.c 
// maco

#include <ansi.h>

inherit SNAKE;

void create()
{
        set_name("小蛇", ({ "snake" }) );
        set("long", "由欧阳世家白驼山庄培养出来的新生小蛇，到底会是什麽蛇，经过code才知道。\n");
        set("unit", "条");
        set("age", 1);
        set("attitude", "peaceful");

        set("auto_follow",0);
        set("wildness", 90);

        set("str", 20);
        set("cor", 20);
        set("dex", 20);

        set("snake_poison", ([
                "level"  : 50,
                "perhit" : 25,
                "remain" : 50,
                "maximum": 50,
                "supply" : 2,
        ]));
        
        set("combat_exp", 100000);

        set_temp("apply/attack", 40);
        set_temp("apply/damage", 40);
        set_temp("apply/armor", 60);

        set_skill("dodge", 10);
        set_skill("parry", 10);
        set_skill("force", 10);

        setup();
}

void init()
{
        ::init();
        add_action("convert","bian");
}


int convert(string arg)
{
        object me = this_player();
        object ob;

        if (arg!="snake" && arg!="she") return 0;
        if( query("family/family_name", me) != "欧阳世家" )
                return notify_fail("你不能化蛇为杖。\n");

        return notify_fail(this_object()->name()+"出生不久，身子太小，还不能化为蛇杖。\n");
}