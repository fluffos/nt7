// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m朱雀[2;37;0m[2;37;0m", ({"bzq"}));        
        set("gender", "女性");                
        set("long", "$HIR$朱雀[2;37;0m
它是王零小的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "bxh");
        set("owner_name", "王零小");
        set_temp("owner", "bxh");
        set_temp("owner_name", "王零小");
        ::setup();
}
