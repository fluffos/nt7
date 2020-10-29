// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("响尾蛇[2;37;0m[2;37;0m", ({"danshui"}));        
        set("gender", "男性");                
        set("long", "响尾蛇[2;37;0m
它是黄花菜的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "dandan");
        set("owner_name", "黄花菜");
        set_temp("owner", "dandan");
        set_temp("owner_name", "黄花菜");
        ::setup();
}
