// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m混沌[2;37;0m[2;37;0m", ({"little"}));        
        set("gender", "男性");                
        set("long", "长毛四足，如犬，有腹无五脏。抵触善人，凭依恶人![2;37;0m
它是小不点的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "micro");
        set("owner_name", "小不点");
        set_temp("owner", "micro");
        set_temp("owner_name", "小不点");
        ::setup();
}
