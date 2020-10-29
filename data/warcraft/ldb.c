// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m大白马[2;37;0m[2;37;0m", ({"horse"}));        
        set("gender", "男性");                
        set("long", "纯种[2;37;0m
它是吕洞宾的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ldb");
        set("owner_name", "吕洞宾");
        set_temp("owner", "ldb");
        set_temp("owner_name", "吕洞宾");
        ::setup();
}
