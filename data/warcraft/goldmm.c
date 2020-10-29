// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("某某某[2;37;0m[2;37;0m", ({"goldmmm"}));        
        set("gender", "男性");                
        set("long", "某某某[2;37;0m
它是金妹的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "goldmm");
        set("owner_name", "金妹");
        set_temp("owner", "goldmm");
        set_temp("owner_name", "金妹");
        ::setup();
}
