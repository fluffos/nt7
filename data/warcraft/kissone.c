// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("傲之追猎者[2;37;0m[2;37;0m", ({"scp"}));        
        set("gender", "男性");                
        set("long", "这个主人很懒，什么都没留下。[2;37;0m
它是挪威小鸟的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kissone");
        set("owner_name", "挪威小鸟");
        set_temp("owner", "kissone");
        set_temp("owner_name", "挪威小鸟");
        ::setup();
}
