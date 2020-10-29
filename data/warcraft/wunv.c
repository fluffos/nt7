// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("保时捷[2;37;0m[2;37;0m", ({"bsj"}));        
        set("gender", "男性");                
        set("long", "好车[2;37;0m
它是舞女的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wunv");
        set("owner_name", "舞女");
        set_temp("owner", "wunv");
        set_temp("owner_name", "舞女");
        ::setup();
}
