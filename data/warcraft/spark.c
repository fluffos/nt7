// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m火德星君[2;37;0m[2;37;0m", ({"sparker"}));        
        set("gender", "女性");                
        set("long", "火鸟[2;37;0m
它是铁蛋的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "spark");
        set("owner_name", "铁蛋");
        set_temp("owner", "spark");
        set_temp("owner_name", "铁蛋");
        ::setup();
}
