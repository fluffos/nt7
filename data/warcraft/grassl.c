// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("爱巧[2;37;0m[2;37;0m", ({"lqiao"}));        
        set("gender", "女性");                
        set("long", "巧[2;37;0m
它是啊艹的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "grassl");
        set("owner_name", "啊艹");
        set_temp("owner", "grassl");
        set_temp("owner_name", "啊艹");
        ::setup();
}
