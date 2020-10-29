// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m玄[37m武[2;37;0m[2;37;0m", ({"tortoise"}));        
        set("gender", "女性");                
        set("long", "一只大大的乌龟。[2;37;0m
它是灭尼妹的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "miemei");
        set("owner_name", "灭尼妹");
        set_temp("owner", "miemei");
        set_temp("owner_name", "灭尼妹");
        ::setup();
}
