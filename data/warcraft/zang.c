// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m拖鞋[2;37;0m[2;37;0m", ({"ttt"}));        
        set("gender", "女性");                
        set("long", "不就是拖鞋吗？！[2;37;0m
它是葬心的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zang");
        set("owner_name", "葬心");
        set_temp("owner", "zang");
        set_temp("owner_name", "葬心");
        ::setup();
}
