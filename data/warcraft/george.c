// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m真武麒麟[2;37;0m[2;37;0m", ({"geo"}));        
        set("gender", "男性");                
        set("long", "真武大帝的本命圣兽。[2;37;0m
它是风月无痕的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "george");
        set("owner_name", "风月无痕");
        set_temp("owner", "george");
        set_temp("owner_name", "风月无痕");
        ::setup();
}
