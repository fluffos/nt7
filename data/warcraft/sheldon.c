// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("虚空[2;37;0m[2;37;0m", ({"gdragon"}));        
        set("gender", "男性");                
        set("long", "虚空[2;37;0m
它是谢尔顿的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "sheldon");
        set("owner_name", "谢尔顿");
        set_temp("owner", "sheldon");
        set_temp("owner_name", "谢尔顿");
        ::setup();
}
