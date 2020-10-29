// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m浴血麒麟[2;37;0m[2;37;0m", ({"pisena"}));        
        set("gender", "女性");                
        set("long", "首都师大[2;37;0m
它是品胜的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "pisen");
        set("owner_name", "品胜");
        set_temp("owner", "pisen");
        set_temp("owner_name", "品胜");
        ::setup();
}
