// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[41;1m[1;34m太古[1;32m始祖[1;33m圣麟[2;37;0m[2;37;0m", ({"ancient"}));        
        set("gender", "男性");                
        set("long", "太古始祖圣麟 天地初开时孕育的第一只麒麟[2;37;0m
它是盘古的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "pangu");
        set("owner_name", "盘古");
        set_temp("owner", "pangu");
        set_temp("owner_name", "盘古");
        ::setup();
}
