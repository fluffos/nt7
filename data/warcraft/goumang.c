// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("得瑟得瑟[2;37;0m[2;37;0m", ({"dsds"}));        
        set("gender", "女性");                
        set("long", "得瑟得瑟[2;37;0m
它是苟芒的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "goumang");
        set("owner_name", "苟芒");
        set_temp("owner", "goumang");
        set_temp("owner_name", "苟芒");
        ::setup();
}
