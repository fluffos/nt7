// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老狗故事[2;37;0m[2;37;0m", ({"lgjs"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是老狗拾的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lgj");
        set("owner_name", "老狗拾");
        set_temp("owner", "lgj");
        set_temp("owner_name", "老狗拾");
        ::setup();
}
