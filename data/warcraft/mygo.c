// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m噢哦[2;37;0m[2;37;0m", ({"ooo"}));        
        set("gender", "男性");                
        set("long", "噢哦[2;37;0m
它是宸骞的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "mygo");
        set("owner_name", "宸骞");
        set_temp("owner", "mygo");
        set_temp("owner_name", "宸骞");
        ::setup();
}
