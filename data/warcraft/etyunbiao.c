// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"yumao"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是运镖戊的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "etyunbiao");
        set("owner_name", "运镖戊");
        set_temp("owner", "etyunbiao");
        set_temp("owner_name", "运镖戊");
        ::setup();
}
