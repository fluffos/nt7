// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[36m真武剑[2;37;0m[2;37;0m", ({"yitianjian"}));        
        set("gender", "男性");                
        set("long", "真武剑[2;37;0m
它是武当太极的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "wdtaiji");
        set("owner_name", "武当太极");
        set_temp("owner", "wdtaiji");
        set_temp("owner_name", "武当太极");
        ::setup();
}
