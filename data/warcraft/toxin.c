// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m小毛驴[2;37;0m[2;37;0m", ({"xiaomaolv"}));        
        set("gender", "女性");                
        set("long", "一只懒懒的小毛驴。[2;37;0m
它是胡子长的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "toxin");
        set("owner_name", "胡子长");
        set_temp("owner", "toxin");
        set_temp("owner_name", "胡子长");
        ::setup();
}
