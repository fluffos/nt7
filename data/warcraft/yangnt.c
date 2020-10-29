// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m圣兽玄武[2;37;0m[2;37;0m", ({"xuanwu"}));        
        set("gender", "男性");                
        set("long", "这是杨老大的宠物-圣兽玄武[2;37;0m
它是杨泥巴的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "yangnt");
        set("owner_name", "杨泥巴");
        set_temp("owner", "yangnt");
        set_temp("owner_name", "杨泥巴");
        ::setup();
}
