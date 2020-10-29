// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火灵[2;37;0m[2;37;0m", ({"huoling"}));        
        set("gender", "男性");                
        set("long", "无[2;37;0m
它是古利斯的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kulic");
        set("owner_name", "古利斯");
        set_temp("owner", "kulic");
        set_temp("owner_name", "古利斯");
        ::setup();
}
