// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m天龙[2;37;0m[2;37;0m", ({"long"}));        
        set("gender", "女性");                
        set("long", "龙[2;37;0m
它是老刀把子的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "daoba");
        set("owner_name", "老刀把子");
        set_temp("owner", "daoba");
        set_temp("owner_name", "老刀把子");
        ::setup();
}
