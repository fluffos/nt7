// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m血[35m麒麟[2;37;0m[2;37;0m", ({"cql"}));        
        set("gender", "男性");                
        set("long", "这是一头浑身沾满鲜血的麒麟[2;37;0m
它是王大的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "coeuvre");
        set("owner_name", "王大");
        set_temp("owner", "coeuvre");
        set_temp("owner_name", "王大");
        ::setup();
}
