// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m红红红红马[2;37;0m[2;37;0m", ({"xief"}));        
        set("gender", "男性");                
        set("long", "一匹马[2;37;0m
它是伯赏坤育的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "scdyxief");
        set("owner_name", "伯赏坤育");
        set_temp("owner", "scdyxief");
        set_temp("owner_name", "伯赏坤育");
        ::setup();
}
