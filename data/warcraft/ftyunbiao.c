// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"yumao"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是运镖庚的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ftyunbiao");
        set("owner_name", "运镖庚");
        set_temp("owner", "ftyunbiao");
        set_temp("owner_name", "运镖庚");
        ::setup();
}
