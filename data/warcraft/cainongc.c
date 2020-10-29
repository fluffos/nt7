// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("菜农[2;37;0m[2;37;0m", ({"cainongd"}));        
        set("gender", "女性");                
        set("long", "菜农[2;37;0m
它是菜农才的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "cainongc");
        set("owner_name", "菜农才");
        set_temp("owner", "cainongc");
        set_temp("owner_name", "菜农才");
        ::setup();
}
