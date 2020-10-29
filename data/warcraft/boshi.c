// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[41m[1;37m自行车[2;37;0m[2;37;0m", ({"bike"}));        
        set("gender", "男性");                
        set("long", "山地自行车[2;37;0m
它是搏屎的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "boshi");
        set("owner_name", "搏屎");
        set_temp("owner", "boshi");
        set_temp("owner_name", "搏屎");
        ::setup();
}
