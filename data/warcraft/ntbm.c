// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "男性");                
        set("long", "member zhuan 3 to ian[2;37;0m
它是果穗的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ntbm");
        set("owner_name", "果穗");
        set_temp("owner", "ntbm");
        set_temp("owner_name", "果穗");
        ::setup();
}
