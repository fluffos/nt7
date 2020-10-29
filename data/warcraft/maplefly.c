// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m蓝火[2;37;0m[2;37;0m", ({"flym"}));        
        set("gender", "女性");                
        set("long", "蓝火[2;37;0m
它是风飞的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "maplefly");
        set("owner_name", "风飞");
        set_temp("owner", "maplefly");
        set_temp("owner_name", "风飞");
        ::setup();
}
