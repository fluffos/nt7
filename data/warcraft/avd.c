// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "女性");                
        set("long", "白虎[2;37;0m
它是段衣的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "avd");
        set("owner_name", "段衣");
        set_temp("owner", "avd");
        set_temp("owner_name", "段衣");
        ::setup();
}
