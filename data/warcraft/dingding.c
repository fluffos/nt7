// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m丁[1;32m武[2;37;0m[2;37;0m", ({"dingwu"}));        
        set("gender", "男性");                
        set("long", "恩[2;37;0m
它是丁叮的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "dingding");
        set("owner_name", "丁叮");
        set_temp("owner", "dingding");
        set_temp("owner_name", "丁叮");
        ::setup();
}
