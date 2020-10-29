// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m大衍[1;36m分光兽[2;37;0m[2;37;0m", ({"hufei_dragon"}));        
        set("gender", "男性");                
        set("long", "一只神奇的小野兽。[2;37;0m
它是胡飞的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "hufei");
        set("owner_name", "胡飞");
        set_temp("owner", "hufei");
        set_temp("owner_name", "胡飞");
        ::setup();
}
