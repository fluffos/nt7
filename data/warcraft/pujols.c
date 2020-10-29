// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("电网[2;37;0m[2;37;0m", ({"olusers"}));        
        set("gender", "男性");                
        set("long", "真牛的[2;37;0m
它是普候斯的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "pujols");
        set("owner_name", "普候斯");
        set_temp("owner", "pujols");
        set_temp("owner_name", "普候斯");
        ::setup();
}
