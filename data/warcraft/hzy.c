// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("五九式轻坦[2;37;0m[2;37;0m", ({"ybx"}));        
        set("gender", "男性");                
        set("long", "天朝国产坦克[2;37;0m
它是何琢言的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "hzy");
        set("owner_name", "何琢言");
        set_temp("owner", "hzy");
        set_temp("owner_name", "何琢言");
        ::setup();
}
