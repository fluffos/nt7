// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "男性");                
        set("long", "白虎[2;37;0m
它是秦潮流的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "snga");
        set("owner_name", "秦潮流");
        set_temp("owner", "snga");
        set_temp("owner_name", "秦潮流");
        ::setup();
}
