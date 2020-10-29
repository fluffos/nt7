// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m金翅大鹏[2;37;0m[2;37;0m", ({"keka"}));        
        set("gender", "女性");                
        set("long", "xxx[2;37;0m
它是莫愁的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "kek");
        set("owner_name", "莫愁");
        set_temp("owner", "kek");
        set_temp("owner_name", "莫愁");
        ::setup();
}
