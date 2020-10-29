// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老胡老过户[2;37;0m[2;37;0m", ({"jianhua"}));        
        set("gender", "男性");                
        set("long", "老胡老过户[2;37;0m
它是何剑华的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "hejh");
        set("owner_name", "何剑华");
        set_temp("owner", "hejh");
        set_temp("owner_name", "何剑华");
        ::setup();
}
