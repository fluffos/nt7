// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火[2;37;0m[2;37;0m", ({"huo"}));        
        set("gender", "男性");                
        set("long", "$HIR$火[2;37;0m
它是韶华的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "baishou");
        set("owner_name", "韶华");
        set_temp("owner", "baishou");
        set_temp("owner_name", "韶华");
        ::setup();
}
