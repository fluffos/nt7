// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m白虎[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "女性");                
        set("long", "白虎[2;37;0m
它是妃月的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "slemb");
        set("owner_name", "妃月");
        set_temp("owner", "slemb");
        set_temp("owner_name", "妃月");
        ::setup();
}
