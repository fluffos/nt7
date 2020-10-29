// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m火羽毛[2;37;0m[2;37;0m", ({"yumao"}));        
        set("gender", "男性");                
        set("long", "一根微不住道的羽毛，居然变成了麒麟[2;37;0m
它是羽梵的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jshzat");
        set("owner_name", "羽梵");
        set_temp("owner", "jshzat");
        set_temp("owner_name", "羽梵");
        ::setup();
}
