// This program is a part of NITAN MudLIB 
// redl 2012/12/1 
#include <ansi.h>

inherit NPC;

void create()
{
        set_name(NOR "小七" NOR, ({ "xiao qi","qi","npc_xiaoqi" }) );
        set("title", NOR "通吃帮护法" NOR);
        set("nickname", MAG "野人" NOR);
        set("gender", "男性");
        set("age", 18);
        set("long", NOR"他就是江湖上赫赫有名的通吃帮口吃的小七。\n"NOR);
        set("attitude", "peaceful");
        set("str", 28);
        set("con", 29);
        set("int", 18);
        set("dex", 22);
        set("per", 23);

                set("level", 50);
        set("combat_exp", 10000000);

        setup();

}



