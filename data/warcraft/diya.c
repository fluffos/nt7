// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("一只小白虎[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "男性");                
        set("long", "一只小白虎[2;37;0m
它是塔斯利亚的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "diya");
        set("owner_name", "塔斯利亚");
        set_temp("owner", "diya");
        set_temp("owner_name", "塔斯利亚");
        ::setup();
}
