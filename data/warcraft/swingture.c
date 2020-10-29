// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("碧水金晶兽[2;37;0m[2;37;0m", ({"swing"}));        
        set("gender", "女性");                
        set("long", "碧水金晶兽[2;37;0m
它是邵流邵的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "swingture");
        set("owner_name", "邵流邵");
        set_temp("owner", "swingture");
        set_temp("owner_name", "邵流邵");
        ::setup();
}
