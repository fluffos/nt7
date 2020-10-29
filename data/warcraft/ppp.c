// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "女性");                
        set("long", "朱雀[2;37;0m
它是绿茶婊的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ppp");
        set("owner_name", "绿茶婊");
        set_temp("owner", "ppp");
        set_temp("owner_name", "绿茶婊");
        ::setup();
}
