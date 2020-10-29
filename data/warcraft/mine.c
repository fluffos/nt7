// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m玄龟[2;37;0m[2;37;0m", ({"xuan_gui"}));        
        set("gender", "男性");                
        set("long", "如烟如雾，似乎没有实体的圣兽[2;37;0m
它是楼颖的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "mine");
        set("owner_name", "楼颖");
        set_temp("owner", "mine");
        set_temp("owner_name", "楼颖");
        ::setup();
}
