// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "男性");                
        set("long", "member zhuan 3 to ian[2;37;0m
它是希志的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ntbk");
        set("owner_name", "希志");
        set_temp("owner", "ntbk");
        set_temp("owner_name", "希志");
        ::setup();
}
