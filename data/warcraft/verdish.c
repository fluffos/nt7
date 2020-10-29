// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"paul"}));        
        set("gender", "男性");                
        set("long", "嘻嘻哈哈[2;37;0m
它是西帅的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "verdish");
        set("owner_name", "西帅");
        set_temp("owner", "verdish");
        set_temp("owner_name", "西帅");
        ::setup();
}
