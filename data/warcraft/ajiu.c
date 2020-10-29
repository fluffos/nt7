// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m凯利布鲁克[2;37;0m[2;37;0m", ({"buluke"}));        
        set("gender", "女性");                
        set("long", "凯利布鲁克，绝代妖姬，世界级的女神![2;37;0m
它是南宫九的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "ajiu");
        set("owner_name", "南宫九");
        set_temp("owner", "ajiu");
        set_temp("owner_name", "南宫九");
        ::setup();
}
