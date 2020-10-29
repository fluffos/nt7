// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("睚在[2;37;0m[2;37;0m", ({"sfd"}));        
        set("gender", "男性");                
        set("long", "睚在[2;37;0m
它是械城的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "huangc");
        set("owner_name", "械城");
        set_temp("owner", "huangc");
        set_temp("owner_name", "械城");
        ::setup();
}
