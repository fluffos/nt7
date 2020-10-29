// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("坐骑撒[2;37;0m[2;37;0m", ({"zuoqisa"}));        
        set("gender", "男性");                
        set("long", "请描述魔幻兽：(不可加颜色)[2;37;0m
它是丹王蛾的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ceshier");
        set("owner_name", "丹王蛾");
        set_temp("owner", "ceshier");
        set_temp("owner_name", "丹王蛾");
        ::setup();
}
