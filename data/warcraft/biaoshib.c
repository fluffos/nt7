// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("骠骑[2;37;0m[2;37;0m", ({"xbiaoshib"}));        
        set("gender", "女性");                
        set("long", "骠骑[2;37;0m
它是镖师二的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "biaoshib");
        set("owner_name", "镖师二");
        set_temp("owner", "biaoshib");
        set_temp("owner_name", "镖师二");
        ::setup();
}
