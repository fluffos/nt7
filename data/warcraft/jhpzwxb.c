// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m炽羽[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "男性");                
        set("long", "朱鸟、朱雀，南方神也。[2;37;0m
它是陆羽的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "jhpzwxb");
        set("owner_name", "陆羽");
        set_temp("owner", "jhpzwxb");
        set_temp("owner_name", "陆羽");
        ::setup();
}
