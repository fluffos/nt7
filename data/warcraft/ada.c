// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火凤凰[2;37;0m[2;37;0m", ({"phoenix"}));        
        set("gender", "女性");                
        set("long", "火凤凰[2;37;0m
它是柳岩的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ada");
        set("owner_name", "柳岩");
        set_temp("owner", "ada");
        set_temp("owner_name", "柳岩");
        ::setup();
}
