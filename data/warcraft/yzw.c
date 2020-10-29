// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m睡袋[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "一只普通的睡袋[2;37;0m
它是毒乃的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yzw");
        set("owner_name", "毒乃");
        set_temp("owner", "yzw");
        set_temp("owner_name", "毒乃");
        ::setup();
}
