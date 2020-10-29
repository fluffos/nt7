// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("乌龟蛋[2;37;0m[2;37;0m", ({"wgwgwg"}));        
        set("gender", "男性");                
        set("long", "慢慢爬啊~爬 [2;37;0m
它是冰煅的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "lxddong");
        set("owner_name", "冰煅");
        set_temp("owner", "lxddong");
        set_temp("owner_name", "冰煅");
        ::setup();
}
