// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m绿毛龟[2;37;0m[2;37;0m", ({"haigui"}));        
        set("gender", "女性");                
        set("long", "一只海龟[2;37;0m
它是龙骨的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "longgu");
        set("owner_name", "龙骨");
        set_temp("owner", "longgu");
        set_temp("owner_name", "龙骨");
        ::setup();
}
