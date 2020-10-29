// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;33m玄武大帝[2;37;0m[2;37;0m", ({"wugui"}));        
        set("gender", "男性");                
        set("long", "玄武大帝[2;37;0m
它是赵小庆的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "jolin");
        set("owner_name", "赵小庆");
        set_temp("owner", "jolin");
        set_temp("owner_name", "赵小庆");
        ::setup();
}
