// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("北月[2;37;0m[2;37;0m", ({"sdg"}));        
        set("gender", "女性");                
        set("long", "as [2;37;0m
它是扬子江的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "yls");
        set("owner_name", "扬子江");
        set_temp("owner", "yls");
        set_temp("owner_name", "扬子江");
        ::setup();
}
