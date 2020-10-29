// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("逼[2;37;0m[2;37;0m", ({"aaabbb"}));        
        set("gender", "女性");                
        set("long", "逼[2;37;0m
它是龙斩的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "longzde");
        set("owner_name", "龙斩");
        set_temp("owner", "longzde");
        set_temp("owner_name", "龙斩");
        ::setup();
}
