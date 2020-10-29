// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("二丫麒麟[2;37;0m[2;37;0m", ({"whbride"}));        
        set("gender", "女性");                
        set("long", "二丫麒麟[2;37;0m
它是吴二丫的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "whb");
        set("owner_name", "吴二丫");
        set_temp("owner", "whb");
        set_temp("owner_name", "吴二丫");
        ::setup();
}
