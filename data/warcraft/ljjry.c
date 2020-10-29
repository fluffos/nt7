// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m跑的真快[2;37;0m[2;37;0m", ({"zhenkuai"}));        
        set("gender", "男性");                
        set("long", "就是跑得快[2;37;0m
它是跑得快的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "ljjry");
        set("owner_name", "跑得快");
        set_temp("owner", "ljjry");
        set_temp("owner_name", "跑得快");
        ::setup();
}
