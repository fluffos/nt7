// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m河河[2;37;0m[2;37;0m", ({"hehe"}));        
        set("gender", "女性");                
        set("long", "$HIR$河河[2;37;0m
它是黄河的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "huanghe");
        set("owner_name", "黄河");
        set_temp("owner", "huanghe");
        set_temp("owner_name", "黄河");
        ::setup();
}
