// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("龙猫[2;37;0m[2;37;0m", ({"longcat"}));        
        set("gender", "女性");                
        set("long", "伸开双手 我就是风 梦是世界 最最不同的时空[2;37;0m
它是阿喵的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "cat");
        set("owner_name", "阿喵");
        set_temp("owner", "cat");
        set_temp("owner_name", "阿喵");
        ::setup();
}
