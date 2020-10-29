// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m火狐[2;37;0m[2;37;0m", ({"redfox"}));        
        set("gender", "男性");                
        set("long", "$RED$火狐[2;37;0m
它是酸雨的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "suanyu");
        set("owner_name", "酸雨");
        set_temp("owner", "suanyu");
        set_temp("owner_name", "酸雨");
        ::setup();
}
