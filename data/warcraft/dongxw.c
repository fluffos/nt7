// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m小宛[2;37;0m[2;37;0m", ({"dongxws"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是董小宛的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "dongxw");
        set("owner_name", "董小宛");
        set_temp("owner", "dongxw");
        set_temp("owner_name", "董小宛");
        ::setup();
}
