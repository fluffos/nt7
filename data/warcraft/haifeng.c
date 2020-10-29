// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("蓝蓝[2;37;0m[2;37;0m", ({"haishui"}));        
        set("gender", "男性");                
        set("long", "蓝色[2;37;0m
它是黄誉的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "haifeng");
        set("owner_name", "黄誉");
        set_temp("owner", "haifeng");
        set_temp("owner_name", "黄誉");
        ::setup();
}
