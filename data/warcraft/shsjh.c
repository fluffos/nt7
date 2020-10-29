// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小鸟[2;37;0m[2;37;0m", ({"xbird"}));        
        set("gender", "男性");                
        set("long", "小鸟[2;37;0m
它是菲比菲比的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "shsjh");
        set("owner_name", "菲比菲比");
        set_temp("owner", "shsjh");
        set_temp("owner_name", "菲比菲比");
        ::setup();
}
