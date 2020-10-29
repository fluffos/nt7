// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("感恩[2;37;0m[2;37;0m", ({"unarmedblong"}));        
        set("gender", "男性");                
        set("long", "夺候[2;37;0m
它是空手河脯的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "unarmedb");
        set("owner_name", "空手河脯");
        set_temp("owner", "unarmedb");
        set_temp("owner_name", "空手河脯");
        ::setup();
}
