// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m玄武龟[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "成天睡觉[2;37;0m
它是黄大的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "wyrsxq");
        set("owner_name", "黄大");
        set_temp("owner", "wyrsxq");
        set_temp("owner_name", "黄大");
        ::setup();
}
