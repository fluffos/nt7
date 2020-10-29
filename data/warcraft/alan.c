// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小猫[2;37;0m[2;37;0m", ({"mao"}));        
        set("gender", "女性");                
        set("long", "一只温顺的小猫[2;37;0m
它是书兰的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "alan");
        set("owner_name", "书兰");
        set_temp("owner", "alan");
        set_temp("owner_name", "书兰");
        ::setup();
}
