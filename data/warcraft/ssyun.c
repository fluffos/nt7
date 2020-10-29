// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔幻骑[2;37;0m[2;37;0m", ({"mohuangqi"}));        
        set("gender", "女性");                
        set("long", "猫儿[2;37;0m
它是重温惜梦的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ssyun");
        set("owner_name", "重温惜梦");
        set_temp("owner", "ssyun");
        set_temp("owner_name", "重温惜梦");
        ::setup();
}
