// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m伍黄[2;37;0m[2;37;0m", ({"matypet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是黄伍的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "maty");
        set("owner_name", "黄伍");
        set_temp("owner", "maty");
        set_temp("owner_name", "黄伍");
        ::setup();
}
