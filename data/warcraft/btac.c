// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("土豪[2;37;0m[2;37;0m", ({"btaclong"}));        
        set("gender", "男性");                
        set("long", "使用手册[2;37;0m
它是泥潭捌的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "btac");
        set("owner_name", "泥潭捌");
        set_temp("owner", "btac");
        set_temp("owner_name", "泥潭捌");
        ::setup();
}
