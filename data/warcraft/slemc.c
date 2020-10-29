// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m麒麟兽[2;37;0m[2;37;0m", ({"qilinshou"}));        
        set("gender", "男性");                
        set("long", "麒麟兽[2;37;0m
它是落羽的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "slemc");
        set("owner_name", "落羽");
        set_temp("owner", "slemc");
        set_temp("owner_name", "落羽");
        ::setup();
}
