// This program is a part of NITAN MudLIB 
// redl 2012/12/1 
#include <ansi.h>

inherit NPC;

void create()
{
        set_name(NOR "阿四" NOR, ({ "a si","si","npc_asi" }) );
        set("title", NOR "通吃帮和尚" NOR);
        set("nickname", MAG "拔毛剃刀" NOR);
        set("gender", "男性");
        set("age", 18);
        set("long", NOR"他就是江湖上赫赫有名的通吃帮不守戒律的和尚。\n"NOR);
        set("attitude", "peaceful");
        set("str", 26);
        set("con", 27);
        set("int", 21);
        set("dex", 20);
        set("per", 20);
       set("level", 45);
        set("combat_exp", 10000000);

        setup();

}
