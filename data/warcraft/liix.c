// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("丫头[2;37;0m[2;37;0m", ({"xiaobb"}));        
        set("gender", "女性");                
        set("long", "一个萌丫头[2;37;0m
它是雨洗清晨的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "liix");
        set("owner_name", "雨洗清晨");
        set_temp("owner", "liix");
        set_temp("owner_name", "雨洗清晨");
        ::setup();
}
