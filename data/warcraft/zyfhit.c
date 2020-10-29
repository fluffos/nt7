// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[36m闲云野鹤[2;37;0m[2;37;0m", ({"zyfma"}));        
        set("gender", "男性");                
        set("long", "尘非尘的坐骑[2;37;0m
它是尘非尘的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zyfhit");
        set("owner_name", "尘非尘");
        set_temp("owner", "zyfhit");
        set_temp("owner_name", "尘非尘");
        ::setup();
}
