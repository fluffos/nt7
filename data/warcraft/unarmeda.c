// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("舒化[2;37;0m[2;37;0m", ({"unarmedalong"}));        
        set("gender", "男性");                
        set("long", "小莲蓬[2;37;0m
它是空手大道的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "unarmeda");
        set("owner_name", "空手大道");
        set_temp("owner", "unarmeda");
        set_temp("owner_name", "空手大道");
        ::setup();
}
